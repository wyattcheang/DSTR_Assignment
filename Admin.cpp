//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Admin.h"
#include "DataIO.h"
#include "User.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <utility>
#include <sstream>
#include <regex>
using namespace std;


AdminNode* Admin::createAdminNode(string data[]) {
    AdminNode* newAdminNode = new AdminNode;
    newAdminNode->adminID = data[0];
    newAdminNode->username = data[1];
    newAdminNode->password = data[2];
    newAdminNode->nextAdmin = nullptr;
    return newAdminNode;
}

void Admin::appendAdminNode(string data[]) {
    AdminNode* newAdminNode = createAdminNode(data);
    if (this->adminTail == nullptr) {
        this->adminHead = this->adminTail = newAdminNode;
        adminSize++;
        return;
    }
    this->adminTail->nextAdmin = newAdminNode;
    this->adminTail = newAdminNode;
    adminSize++;
}

//Admin::Admin() {
//    DataIO::ReadAdmin(this);
//}

AdminNode* Admin::searchAdminUser(string username) {
    AdminNode* temp = this->adminHead;
    if (temp == nullptr) return nullptr;
    while (temp != nullptr) {
        if (temp->username == username) {
            return temp;
        }
        temp = temp->nextAdmin;
    }
    return nullptr;
}

void Admin::modifyUsername() {
    string username, newUsername, password, newPass, newPass2;
    User user;
    //UserNode* theUser;
    cout << "Enter current username: " << endl;
    cin >> username;
    UserNode* foundUser = user.searchUser(username);
    if (foundUser == nullptr) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Account doesn't exist!" << endl;
    }
    else {
        while (foundUser != nullptr) {
            if (foundUser->username == username) {
                cout << "Enter new username: " << endl;
                cin >> newUsername;
                if (!user.usernameValidation(newUsername)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
        }
        foundUser->username = newUsername;
        cout << "Username modified successfully!" << endl;
    }
}

void Admin::modifyUserPassword() {
    string username, newUsername, password, newPass, newPass2;
    User user;
    //UserNode* theUser;
    cout << "Enter current username: " << endl;
    cin >> username;
    UserNode* foundUser = user.searchUser(username);
    if (foundUser == nullptr) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Account doesn't exist!" << endl;
    }
    else {
        while (foundUser != nullptr) {
            if (foundUser->username == username) {
                cout << "Enter current password: " << endl;
                cin >> password;
                UserNode* foundUser2 = user.searchUserPass(password);
                if (foundUser2 != nullptr && foundUser2->password == password) {
                    cout << "Enter new password: " << endl;
                    cin >> newPass;
                    if (!user.checkPasswordFormat(newPass)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Check your password format!" << endl;
                        continue;
                    }
                    else {
                        cout << "Re-enter your new password: ";
                        cin >> newPass2;
                        if (newPass != newPass2) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Password not matched!" << endl;
                            continue;
                        }
                    }
                    foundUser2->password = newPass;
                    cout << "Password modified successfully! " << endl;
                }
                else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid current password!" << endl;
                }
                break;
            }
        }
    }
}


void Admin::adminLogin() {
    DataIO data;
    User user;
    data.ReadAdmin(this);
    string name, pass;
    while (true) {
        cout << string(100, '*') << endl;
        DataIO::printStringCentered("Admin Login!");
        cout << string(100, '*') << endl << endl;
        cout << "Enter admin username: ";
        cin >> name;
        AdminNode* theAdmin = searchAdminUser(name);
        if (theAdmin == nullptr) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Account doesn't exist!" << endl;
        }
        else {
            for (int i = 0; i <= 3; i++) {
                cout << "Enter your password: ";
                cin >> pass;
                if (pass != theAdmin->password) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error password!";
                    cout << 3 - i << " time attempt left.\n\n" << endl;
                }
                else {
                    cout << endl;
                    loginAdmin = theAdmin;
                    break;
                }
            }
            if (loginAdmin != nullptr) {
                break;
            }
            else {
                cout << "Too many attempt! Please try again!\n\n";
            }
        }
    }
}

void Admin::adminLogout() {
    loginAdmin = nullptr;
    cout << string(100, '*') << endl;
    DataIO::printStringCentered("Logout Successfully!");
    cout << string(100, '*') << endl << endl;
}

AdminNode *Admin::getLoginAdmin() const {
    return loginAdmin;
}


