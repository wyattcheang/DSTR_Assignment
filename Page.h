//
// Created by Wyatt Cheang on 27/03/2023.
//

#ifndef ASSIGNMENT_PAGE_H
#define ASSIGNMENT_PAGE_H

#include "University.h"
#include "User.h"
#include "Admin.h"
#include "Feedback.h"
#include "Favourite.h"


class BasePage {
protected:
    University* university;
    User* user;
    Admin* admin;
    Feedback* feedback;
    Favourite* favourite;

public:
    BasePage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
};

class FavouritePage : public BasePage {
public:
    FavouritePage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
    void DisplayAdminPage();
};

class FeedbackPage : public BasePage {
public:
    FeedbackPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
    void DisplayAdminFeedbackPage();
    void UserAddFeedbackPage();
    void UserReviewFeedbackPage();
};

class UserPage : public BasePage {
    public:
        UserPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
        void DisplayUserPage(FeedbackPage* feedbackPage, FavouritePage* favouritePage);
};

class AdminPage : public BasePage {
    public:
        AdminPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
        void DisplayAdminPage(FeedbackPage* feedbackPage, FavouritePage* favouritePage);
};

class StartPage : public BasePage {
public:
    StartPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
    void DisplayStartPage(UserPage* userPage, AdminPage* adminPage, FeedbackPage* feedbackPage, FavouritePage* favouritePage);
};

#endif //ASSIGNMENT_PAGE_H