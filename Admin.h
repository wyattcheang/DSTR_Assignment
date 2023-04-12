//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_ADMIN_H
#define ASSIGNMENT_ADMIN_H

#include <string>

using namespace std;

struct AdminNode{
    string adminID;
    string username;
    string password;
    AdminNode* nextAdmin;
};

class Admin {
    private:
        AdminNode* adminHead = nullptr;
        AdminNode* adminTail = nullptr;
        AdminNode* loginAdmin = nullptr;
        int adminSize = 0;
    public:

    void adminLogin();
        AdminNode* createAdminNode(string data[]);
        void appendAdminNode(string data[]);
        AdminNode* searchAdminUser(string username);
        //Required Functions
};


#endif //ASSIGNMENT_ADMIN_H
