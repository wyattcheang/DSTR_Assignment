//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_USER_H
#define ASSIGNMENT_USER_H

#include <string>

using namespace std;

struct UserNode{
    string userID;
    string username;
    string password;
    tm* lastTimeLogin;
    tm* lastTimeLogout;
    UserNode* nextUser;
};

class User {
    private:
        UserNode *userHead = nullptr;
        UserNode *userTail = nullptr;
        UserNode *loginUser = nullptr;
        string *userHeader = new string[5];
        int userSize = 0;
    public:
        User();
        ~User();
        void addUserHeader(string[]);
        void userRegister();
        void userLogin();
        bool usernameValidation(string username);
        bool checkPasswordFormat(string password);
        UserNode* createUserNode(string data[]);
        void appendUserNode(UserNode* newNode);
        void displayUser();
        UserNode* searchUser(string username);
};


#endif //ASSIGNMENT_USER_H
