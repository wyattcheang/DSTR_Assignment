//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Feedback.h"


FeedbackNode *Feedback::createFeedbackNode(string data[], User userClass, Admin adminClass, University uniClass) {
    FeedbackNode* newFeedbackNode = new FeedbackNode;
    newFeedbackNode->feedbackDatetime = new tm;
    newFeedbackNode->replyDatetime = new tm;
    newFeedbackNode->feedbackID = data[0];
    newFeedbackNode->feedbackUser = userClass.searchUser(data[1]);
    newFeedbackNode->replyAdmin = adminClass.searchAdminUser(data[2]);
    newFeedbackNode->feedbackUniversity = uniClass.searchUniversity(data[3]);
    newFeedbackNode->feedback = data[4];
    newFeedbackNode->reply = data[5];
    strptime(data[6].c_str(), "%Y-%m-%d %H:%M:%S", newFeedbackNode->feedbackDatetime);
    strptime(data[7].c_str(), "%Y-%m-%d %H:%M:%S", newFeedbackNode->replyDatetime);
    return newFeedbackNode;
}
