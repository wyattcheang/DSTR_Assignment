//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_FEEDBACK_H
#define ASSIGNMENT_FEEDBACK_H
#include "User.h"
#include "Admin.h"
#include "University.h"
#include <ctime>
#include <string>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

struct FeedbackNode{
    string feedbackID;
    UniversityNode* feedbackUniversity;
    UserNode* feedbackUser;
    tm* feedbackDatetime;
    string feedback;

    AdminNode* replyAdmin;
    tm* replyDatetime;
    string reply;

    FeedbackNode * prevFeedback;
    FeedbackNode * nextFeedback;
    FeedbackNode * parentFeedback;
    FeedbackNode * childFeedback;
};

class Feedback {
private:
    FeedbackNode* feedbackHead = nullptr;
    FeedbackNode* feedbackTail = nullptr;
    int feedbackSize = 0;
public:
    Feedback(User* userClass, Admin* adminClass, University* uniClass);
    ~Feedback();
    FeedbackNode* getHead();
    FeedbackNode* getTail();
    FeedbackNode* createFeedbackNode(string data[], User *userClass, Admin *adminClass, University *uniClass);
    FeedbackNode* createNewFeedbackNode(string feedbackID, string feedback, UserNode *user, UniversityNode *uni);
    void appendFeedbackNode(FeedbackNode *newFeedbackNode);
    void appendListFeedbackNode(string feedback, UserNode *user, UniversityNode *uni);
    void appendChildFeedbackNode(FeedbackNode *parentNode, string feedback);
    void appendFeedbackNode(string feedback, UserNode *user, UniversityNode *uni);
    void replyFeedback(FeedbackNode *parentNode, AdminNode *admin, string reply);
    int getFeedbackSize();
    void setFeedbackHead(FeedbackNode *feedbackHead);

    void printFeedback(FeedbackNode *feedbackNode);
    FeedbackNode* getUserNextFeedback(UserNode *user, FeedbackNode *feedbackNode);
    FeedbackNode* getChildFeedback(FeedbackNode *feedbackNode);
};


#endif //ASSIGNMENT_FEEDBACK_H
