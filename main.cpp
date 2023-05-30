#include <iostream>
#include "University.h"
#include "DataIO.h"
#include "Page.h"
#include "User.h"

using namespace std;



int main() {
    University* university = new University();
    User* user = new User();
    Admin* admin = new Admin();
    Feedback* feedback = new Feedback();
    Favourite* favourite = new Favourite();

    StartPage* startPage = new StartPage(university, user, admin, feedback, favourite);
    UserPage* userPage = new UserPage(university, user, admin, feedback, favourite);
    AdminPage* adminPage = new AdminPage(university, user, admin, feedback, favourite);
    startPage->DisplayStartPage(userPage, adminPage);
    delete user;
    delete admin;
    delete university;
    delete feedback;
    delete favourite;
    return 0;
}