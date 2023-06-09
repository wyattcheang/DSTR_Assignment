//
// Created by Wyatt Cheang on 16/03/2023.
//

#ifndef ASSIGNMENT_DATAIO_H
#define ASSIGNMENT_DATAIO_H

#include <iostream>
#include <fstream>
#include "University.h"
#include "User.h"
#include "Admin.h"
#include "Feedback.h"
#include "Favourite.h"

using namespace std;

class DataIO {
public:
    static void ReadUniversity(University* head);

    static void ReadUser(User* head);
    static void SaveUser(UserNode* head);

    static void ReadAdmin(Admin* head);

    static void ReadFeedback(Feedback* feedbackClass, User* userClass, Admin* adminClass, University* uniClass);
    static void SaveFeedback(FeedbackNode* head);

    static void ReadFavourite(Favourite* head, University* uniClass, User* userClass);
    static void SaveFavourite(FavouriteNode* head);

    static string getCurrentTime();
    static tm* StringToTime(const string& dateString);
    static string TimeToString(tm* time);

    static void printStringCentered(const string& text);
    static void printAlert(const string& text);
    static void printSelectUniversityAttributeMenu();
    static void selectSortMethodMenu();
    static void selectSearchMethodMenu();

};

#endif //ASSIGNMENT_DATAIO_H