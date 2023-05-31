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
    int lastFeedbackID = 0;
public:
    Feedback(User* userClass, Admin* adminClass, University* uniClass);
    ~Feedback();

    int getLastFeedbackID();
    void setLastFeedbackID(int lastFeedbackID);
    
    FeedbackNode* createNewFeedbackNode(string feedbackID, string feedback, UserNode *user, UniversityNode *uni);
    void appendFeedbackNode(string feedback, UserNode *user, UniversityNode *uni);
    void appendParentFeedbackNode(string feedback, UserNode *user, UniversityNode *uni);
    void appendChildFeedbackNode(FeedbackNode *parentNode, string feedback);
    void replyFeedback(FeedbackNode *parentNode, AdminNode *admin, string reply);
    void updateParentNodePosition(FeedbackNode *feedbackNode);

    FeedbackNode* getUserPrevFeedback(UserNode *user, FeedbackNode *feedbackNode);
    FeedbackNode* getUserNextFeedback(UserNode *user, FeedbackNode *feedbackNode);
    FeedbackNode* getChildFeedback(FeedbackNode *feedbackNode);
    
    void printFeedback(FeedbackNode *feedbackNode);
    
    FeedbackNode* createFeedbackNode(string data[], User *userClass, Admin *adminClass, University *uniClass);
    void appendFeedbackNode(FeedbackNode *newFeedbackNode);

    FeedbackNode *getFeedbackHead() const;

    FeedbackNode *getFeedbackTail() const;

    void setFeedbackTail(FeedbackNode *feedbackTail);
};


#endif //ASSIGNMENT_FEEDBACK_H
