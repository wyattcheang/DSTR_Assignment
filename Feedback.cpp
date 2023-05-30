//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Feedback.h"
#include "DataIO.h"

Feedback::Feedback(User* userClass, Admin* adminClass, University* uniClass) {
    feedbackHead = nullptr;
    feedbackTail = nullptr;
    feedbackSize = 0;
    DataIO::ReadFeedback(this, userClass, adminClass, uniClass);
}

Feedback::~Feedback() {
    DataIO::SaveFeedback(this->feedbackHead);
}

FeedbackNode* Feedback::getHead() {
    return this->feedbackHead;
}

FeedbackNode* Feedback::getTail() {
    return this->feedbackTail;
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

    // newFeedbackNode->replyAdmin = adminClass.searchAdminUser(data[2]);
    // newFeedbackNode->replyDatetime = new tm;
    // newFeedbackNode->replyDatetime = DataIO::StringToTime(data[7]);
    // newFeedbackNode->reply = data[5];
    newFeedbackNode->replyAdmin = nullptr;
    newFeedbackNode->replyDatetime = new tm;
    newFeedbackNode->reply = "NULL";

    newFeedbackNode->prevFeedback = nullptr;
    newFeedbackNode->nextFeedback = nullptr;
    newFeedbackNode->parentFeedback = nullptr;
    newFeedbackNode->childFeedback = nullptr;


//    strptime(data[6].c_str(), "%Y-%m-%d %H:%M:%S", newFeedbackNode->feedbackDatetime);
//    strptime(data[7].c_str(), "%Y-%m-%d %H:%M:%S", newFeedbackNode->replyDatetime);
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
    int newFeedbackIDNum = stoi(newFeedbackNode->feedbackID.substr(2, 6));
    int tailFeedbackIDNum = stoi(this->feedbackTail->feedbackID.substr(2, 6));
    if(newFeedbackIDNum - tailFeedbackIDNum == 100) {
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

// append parent feedback node
// input: feedback(string), user(UserNode *), uni(UniversityNode *)
void Feedback::appendListFeedbackNode(string feedback, UserNode *user, UniversityNode *uni) {
    string feedbackID;
    if(this->feedbackHead == nullptr)
        feedbackID = "FB000101";
    else {
        string lastFeedbackID = this->feedbackTail->feedbackID;
        int lastFeedbackIDNum = stoi(lastFeedbackID.substr(2, 6));
        std::stringstream temp;
        temp << setw(6) << setfill('0') << to_string(lastFeedbackIDNum + 100);
        feedbackID = "FB" + temp.str();
    }
    FeedbackNode* newNode = createNewFeedbackNode(feedbackID, feedback, user, uni);
    if(this->feedbackHead == nullptr) {
        this->feedbackHead = this->feedbackTail = newNode;
        feedbackSize++;
        return;
    }
    this->feedbackTail->nextFeedback = newNode;
    newNode->prevFeedback = this->feedbackTail;
    this->feedbackTail = newNode;
    feedbackSize++;
}

// append new node as child of parent node
// input: parentNode(FeedbackNode *), feedback(string)
void Feedback::appendChildFeedbackNode(FeedbackNode *parentNode, string feedback) {
    string parentFeedbackID = parentNode->feedbackID;
    int parentFeedbackIDNum = stoi(parentFeedbackID.substr(2, 6));
    string childFeedbackID = "FB" + to_string(parentFeedbackIDNum + 1);
    FeedbackNode* newNode = createNewFeedbackNode(childFeedbackID, feedback, parentNode->feedbackUser, parentNode->feedbackUniversity);
    parentNode->childFeedback = newNode;
    newNode->parentFeedback = parentNode;
    feedbackSize++;
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
    appendListFeedbackNode(feedback, user, uni);
}

// only used when admin reply feedback
// input: feedbackNode(FeedbackNode *), admin(AdminNode *), reply(string)
void Feedback::replyFeedback(FeedbackNode *feedbackNode, AdminNode *admin, string reply) {
    feedbackNode->replyAdmin = admin;
    string time = DataIO::getCurrentTime();
    feedbackNode->replyDatetime = DataIO::StringToTime(time);
    feedbackNode->reply = reply;
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

// get next feedback of user on another university
// input: user(UserNode *), feedbackNode(FeedbackNode *)
FeedbackNode* Feedback::getUserNextFeedback(UserNode *user, FeedbackNode *feedbackNode) {
    FeedbackNode* temp;
    if(feedbackNode == nullptr)
        temp = this->feedbackHead;
    else
        temp = feedbackNode->nextFeedback;

    while(temp != nullptr) {
        if(temp->feedbackUser == user) {
            return temp;
        }
        temp = temp->nextFeedback;
    }
    return nullptr;
}

// get child feedback of parent feedback
// input: feedbackNode(FeedbackNode *)
FeedbackNode* Feedback::getChildFeedback(FeedbackNode *feedbackNode) {
    return feedbackNode->childFeedback;
}