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
        static void ReadFeedback(Feedback* head);
        static void ReadFavourite(Favourite* head);
        static tm* StringToTime(string dateString);
};

#endif //ASSIGNMENT_DATAIO_H
