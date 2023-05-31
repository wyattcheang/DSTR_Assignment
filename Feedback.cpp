//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Feedback.h"
#include "DataIO.h"

Feedback::Feedback(User* userClass, Admin* adminClass, University* uniClass) {
    this->feedbackHead = nullptr;
    this->feedbackTail = nullptr;
    this->feedbackSize = 0;
    this->lastFeedbackID = 0;
    DataIO::ReadFeedback(this, userClass, adminClass, uniClass);
}

Feedback::~Feedback() {
    DataIO::SaveFeedback(this->feedbackHead);
}

int Feedback::getLastFeedbackID() {
    return lastFeedbackID;
}

void Feedback::setLastFeedbackID(int lastFeedbackID) {
    Feedback::lastFeedbackID = lastFeedbackID;
}

// used when user create new feedback
// input: feedbackID(string), feedback(string), user(UserNode *), uni(UniversityNode *)
FeedbackNode* Feedback::createNewFeedbackNode(string feedbackID, string feedback, UserNode *user, UniversityNode *uni) {
    FeedbackNode* newFeedbackNode = new FeedbackNode;
    newFeedbackNode->feedbackID = feedbackID;
    newFeedbackNode->feedbackUniversity = uni;

    newFeedbackNode->feedbackUser = user;
    newFeedbackNode->feedbackDatetime = new tm;
    newFeedbackNode->feedbackDatetime = DataIO::StringToTime(DataIO::getCurrentTime());
    newFeedbackNode->feedback = feedback;

    newFeedbackNode->replyAdmin = nullptr;
    newFeedbackNode->replyDatetime = new tm;
    newFeedbackNode->reply = "NULL";

    newFeedbackNode->prevFeedback = nullptr;
    newFeedbackNode->nextFeedback = nullptr;
    newFeedbackNode->parentFeedback = nullptr;
    newFeedbackNode->childFeedback = nullptr;

    return newFeedbackNode;
}

// given user and uni, decide whether should append parent or child feedback node
// input: feedback(string), user(UserNode *), uni(UniversityNode *)
void Feedback::appendFeedbackNode(string feedback, UserNode *user, UniversityNode *uni) {
    FeedbackNode *temp = this->feedbackHead;
    while(temp != nullptr) {
        if(temp->feedbackUser == user && temp->feedbackUniversity == uni) {
            appendChildFeedbackNode(temp, feedback);
            return;
        }
        temp = temp->nextFeedback;
    }
    appendParentFeedbackNode(feedback, user, uni);
}

// append parent feedback node
// input: feedback(string), user(UserNode *), uni(UniversityNode *)
void Feedback::appendParentFeedbackNode(string feedback, UserNode *user, UniversityNode *uni) {
    string feedbackID;
    if(this->feedbackHead == nullptr) {
        feedbackID = "FB000101";
        this->lastFeedbackID++;
    }else {
        this->lastFeedbackID++;
        stringstream temp;
        temp << setw(4) << setfill('0') << to_string(this->lastFeedbackID);
        feedbackID = "FB" + temp.str() + "01";
    }
    FeedbackNode* newNode = createNewFeedbackNode(feedbackID, feedback, user, uni);
    if(this->feedbackHead == nullptr) {
        this->feedbackHead = this->feedbackTail = newNode;
        feedbackSize++;
        return;
    }
    this->feedbackHead->prevFeedback = newNode;
    newNode->nextFeedback = this->feedbackHead;
    this->feedbackHead = newNode;
    feedbackSize++;
}

// append new node as child of parent node
// input: parentNode(FeedbackNode *), feedback(string)
void Feedback::appendChildFeedbackNode(FeedbackNode *parentNode, string feedback) {
    while(parentNode->childFeedback != nullptr) {
        parentNode = parentNode->childFeedback;
    }
    string parentFeedbackID = parentNode->feedbackID;
    int parentFeedbackIDNum = stoi(parentFeedbackID.substr(2, 6));
    stringstream temp;
    temp << setw(6) << setfill('0') << to_string(parentFeedbackIDNum + 1);
    string childFeedbackID = "FB" + temp.str();
    FeedbackNode* newNode = createNewFeedbackNode(childFeedbackID, feedback, parentNode->feedbackUser, parentNode->feedbackUniversity);
    parentNode->childFeedback = newNode;
    newNode->parentFeedback = parentNode;
    feedbackSize++;
    updateParentNodePosition(newNode);
}

// only used when admin reply feedback
// input: feedbackNode(FeedbackNode *), admin(AdminNode *), reply(string)
void Feedback::replyFeedback(FeedbackNode *feedbackNode, AdminNode *admin, string reply) {
    feedbackNode->replyAdmin = admin;
    string time = DataIO::getCurrentTime();
    feedbackNode->replyDatetime = DataIO::StringToTime(time);
    feedbackNode->reply = reply;
    updateParentNodePosition(feedbackNode);
}

// move feedback parent node to head of list
// input: feedbackNode(FeedbackNode *)
void Feedback::updateParentNodePosition(FeedbackNode *feedbackNode) {
    while(feedbackNode->parentFeedback != nullptr) {
        feedbackNode = feedbackNode->parentFeedback;
    }
    if(this->feedbackHead == feedbackNode) {
        return;
    }else if(feedbackNode->prevFeedback != nullptr && feedbackNode->nextFeedback != nullptr) {
        feedbackNode->prevFeedback->nextFeedback = feedbackNode->nextFeedback;
        feedbackNode->nextFeedback->prevFeedback = feedbackNode->prevFeedback;
    }else if(this->feedbackTail == feedbackNode) {
        feedbackNode->prevFeedback->nextFeedback = nullptr;
        this->feedbackTail = feedbackNode->prevFeedback;
    }
    feedbackNode->prevFeedback = nullptr;
    feedbackNode->nextFeedback = this->feedbackHead;
    this->feedbackHead->prevFeedback = feedbackNode;
    this->feedbackHead = feedbackNode;
}


// get older feedback of user on another university
// input: user(UserNode *), feedbackNode(FeedbackNode *)
FeedbackNode* Feedback::getUserPrevFeedback(UserNode *user, FeedbackNode *feedbackNode) {
    if(feedbackNode == nullptr)
        feedbackNode = this->feedbackHead;
    else {
        while(feedbackNode->parentFeedback != nullptr) {
            feedbackNode = feedbackNode->parentFeedback;
        }
        feedbackNode = feedbackNode->nextFeedback;
    }

    while(feedbackNode != nullptr) {
        if(feedbackNode->feedbackUser == user) {
            return feedbackNode;
        }
        feedbackNode = feedbackNode->nextFeedback;
    }
    return nullptr;
}


// get newer feedback of user on another university
// input: user(UserNode *), feedbackNode(FeedbackNode *)
FeedbackNode* Feedback::getUserNextFeedback(UserNode *user, FeedbackNode *feedbackNode) {
    if(feedbackNode == nullptr)
        feedbackNode = this->feedbackTail;
    else {
        while(feedbackNode->parentFeedback != nullptr) {
            feedbackNode = feedbackNode->parentFeedback;
        }
        feedbackNode = feedbackNode->prevFeedback;
    }

    while(feedbackNode != nullptr) {
        if(feedbackNode->feedbackUser == user) {
            return feedbackNode;
        }
        feedbackNode = feedbackNode->prevFeedback;
    }
    return nullptr;
}

// get child feedback of parent feedback
// input: feedbackNode(FeedbackNode *)
FeedbackNode* Feedback::getChildFeedback(FeedbackNode *feedbackNode) {
    while(feedbackNode->childFeedback != nullptr) {
        feedbackNode = feedbackNode->childFeedback;
    }
    return feedbackNode;
}

// print parent feedback and all child feedback
// input: feedbackNode(FeedbackNode *)
void Feedback::printFeedback(FeedbackNode *feedbackNode) {
    cout << left;
    cout << string(100, '=') << endl;
    cout << "Feedback ID: " << feedbackNode->feedbackID.substr(0, 6) << "\t\t | ";
    cout << "University: " << feedbackNode->feedbackUniversity->institutionName << endl;
    cout << "User: " << setw(20) << feedbackNode->feedbackUser->username << endl;

    while(feedbackNode != nullptr) {
        cout << string(100, '-') << endl;
        cout << DataIO::TimeToString(feedbackNode->feedbackDatetime) << endl;
        cout << "User: " << endl;
        cout << feedbackNode->feedback << endl << endl;

        if(feedbackNode->replyAdmin != nullptr) {
            cout << DataIO::TimeToString(feedbackNode->replyDatetime) << endl;
            cout << "Admin: " << endl;
            cout << feedbackNode->reply << endl;
        }else{
            cout << "Admin: " << endl;
            cout << "Not yet reply" << endl;
        }
        feedbackNode = feedbackNode->childFeedback;
    }
    cout << string(100, '=') << endl;
}


// only used when reading file
// input: data[](string), userClass(User *), adminClass(Admin *), uniClass(University *)
// data[0] = feedbackID
// data[1] = feedbackUsername
// data[2] = replyAdminUsername
// data[3] = feedbackUniversityRank
// data[4] = feedback
// data[5] = reply
// data[6] = feedbackDatetime
// data[7] = replyDatetime
FeedbackNode* Feedback::createFeedbackNode(string data[], User *userClass, Admin *adminClass, University *uniClass) {

    FeedbackNode* newFeedbackNode = new FeedbackNode;
    newFeedbackNode->feedbackID = data[0];
    newFeedbackNode->feedbackUser = userClass->searchUserID(data[1]);
    if (data[2] != "NULL") {
        newFeedbackNode->replyAdmin = adminClass->searchAdminID(data[2]);
    } else {
        newFeedbackNode->replyAdmin = nullptr;
    }
    newFeedbackNode->feedbackUniversity = uniClass->searchUniversity(data[3]);
    newFeedbackNode->feedback = data[4];
    newFeedbackNode->reply = data[5];

    newFeedbackNode->feedbackDatetime = new tm;
    newFeedbackNode->feedbackDatetime = DataIO::StringToTime(data[6]);
    newFeedbackNode->replyDatetime = new tm;
    newFeedbackNode->replyDatetime = DataIO::StringToTime(data[7]);

    newFeedbackNode->prevFeedback = nullptr;
    newFeedbackNode->nextFeedback = nullptr;
    newFeedbackNode->parentFeedback = nullptr;
    newFeedbackNode->childFeedback = nullptr;

    return newFeedbackNode;
}

// only used when reading file
// input: newFeedbackNode(FeedbackNode *)
void Feedback::appendFeedbackNode(FeedbackNode *newFeedbackNode) {
    if(this->feedbackTail == nullptr) {
        this->feedbackHead = this->feedbackTail = newFeedbackNode;
        feedbackSize++;
        return;
    }
//    int newFeedbackIDNum = stoi(newFeedbackNode->feedbackID.substr(2, 6));
//    int tailFeedbackIDNum = stoi(this->feedbackTail->feedbackID.substr(2, 6));
    string feedbackChildIDNum = newFeedbackNode->feedbackID.substr(6, 2);
    if(feedbackChildIDNum == "01") {
        this->feedbackTail->nextFeedback = newFeedbackNode;
        newFeedbackNode->prevFeedback = this->feedbackTail;
        this->feedbackTail = newFeedbackNode;
        feedbackSize++;
    }else {
        FeedbackNode *temp = this->feedbackTail;
        while(temp->childFeedback != nullptr) {
            temp = temp->childFeedback;
        }
        temp->childFeedback = newFeedbackNode;
        newFeedbackNode->parentFeedback = temp;
    }
}

FeedbackNode *Feedback::getFeedbackHead() const {
    return feedbackHead;
}

FeedbackNode *Feedback::getFeedbackTail() const {
    return feedbackTail;
}

void Feedback::setFeedbackTail(FeedbackNode *feedbackTail) {
    Feedback::feedbackTail = feedbackTail;
}


