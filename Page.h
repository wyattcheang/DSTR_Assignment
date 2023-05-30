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

class UserPage : public BasePage {
    public:
        UserPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
        void DisplayUserPage();
};

class AdminPage : public BasePage {
    public:
        AdminPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
        void DisplayAdminPage();
};


class StartPage : public BasePage {
public:
    StartPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite);
    void DisplayStartPage(UserPage* userPage, AdminPage* adminPage);
};

#endif //ASSIGNMENT_PAGE_H