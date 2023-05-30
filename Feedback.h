//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_FEEDBACK_H
#define ASSIGNMENT_FEEDBACK_H
#include "User.h"
#include "Admin.h"
#include "University.h"
#include <ctime>

using namespace std;

struct FeedbackNode{
    string feedbackID;
    UserNode* feedbackUser;
    AdminNode* replyAdmin;
    UniversityNode* feedbackUniversity;
    string feedback;
    string reply;
    tm* feedbackDatetime;
    tm* replyDatetime;
    FeedbackNode * prevFeedback;
    FeedbackNode * nextFeedback;
    FeedbackNode * childFeedback;
};

class Feedback {
    private:
        FeedbackNode* feedbackHead = nullptr;
        FeedbackNode* feedbackTail = nullptr;
        int feedbackSize = 0;
    public:
        Feedback();
        ~Feedback();
        FeedbackNode* createFeedbackNode(string data[], User userClass, Admin adminClass, University uniClass);
        void appendNewFeedbackNode();
        void appendChildFeedbackNode();
};


#endif //ASSIGNMENT_FEEDBACK_H
