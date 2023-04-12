//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Admin.h"


void Admin::adminLogin() {

}

AdminNode *Admin::createAdminNode(string *data) {
    AdminNode * newAdminNode = new AdminNode;
    newAdminNode->adminID = data[0];
    newAdminNode->username = data[1];
    newAdminNode->password = data[2];
    newAdminNode->nextAdmin = nullptr;
    return newAdminNode;
}

void Admin::appendAdminNode(string *data) {
    AdminNode * newAdminNode = createAdminNode(data);
    if (this->adminTail == nullptr){
        this->adminHead = this->adminTail = newAdminNode;
        adminSize++;
        return;
    }
    this->adminTail->nextAdmin = newAdminNode;
    this->adminTail = newAdminNode;
    adminSize++;
}

AdminNode* Admin::searchAdminUser(string username) {
    AdminNode* temp = this->adminHead;
    if (temp == nullptr) return nullptr;
    while (temp != nullptr){
        if (temp->username == username){
            return temp;
        }
        temp = temp->nextAdmin;
    }
    return nullptr;
}

