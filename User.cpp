//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "User.h"
#include "DataIO.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <utility>
#include <sstream>
#include <regex>
using namespace std;

User::User() {
    DataIO::ReadUser(this);
}

User::~User() {
    DataIO::SaveUser(this->userHead);
}

UserNode* User::searchUser(string username) {
    UserNode* temp = this->userHead;
    if (temp == nullptr) return nullptr;
    while (temp != nullptr) {
        if (temp->username == username) {
            return temp;
        }
        else {
            temp = temp->nextUser;
        }
    }
    return nullptr;
}

UserNode* User::searchUserPass(string password) {
    UserNode* temp = this->userHead;
    if (temp == nullptr) return nullptr;
    while (temp != nullptr) {
        if (temp->password == password) {
            return temp;
        }
        else {
            temp = temp->nextUser;
        }
    }
    return nullptr;
}

UserNode* User::createUserNode(string data[]) {
    UserNode* newUserNode = new UserNode;
    newUserNode->lastTimeLogin = new tm;
    newUserNode->lastTimeLogout = new tm;
    newUserNode->userID = data[0];
    newUserNode->username = data[1];
    newUserNode->password = data[2];
    newUserNode->lastTimeLogin = DataIO::StringToTime(data[3]);
    newUserNode->lastTimeLogout = DataIO::StringToTime(data[4]);
    //    strptime(data[3].c_str(), "%Y-%m-%d %H:%M:%S", newUserNode->lastTimeLogin);
    //    strptime(data[4].c_str(), "%Y-%m-%d %H:%M:%S", newUserNode->lastTimeLogout);
    newUserNode->nextUser = nullptr;
    return newUserNode;
}

void User::appendUserNode(UserNode* newNode) {
    if (this->userTail == nullptr) {
        this->userHead = this->userTail = newNode;
        userSize++;
        return;
    }
    this->userTail->nextUser = newNode;
    this->userTail = newNode;
    userSize++;
}

void User::displayUser() {
    UserNode* current = userHead;
    int width[4] = { 9, 20, 19, 19 };

    cout << string(83, '-') << endl;
    cout << " | ";
    cout << left << setw(9) << *userHeader << " | ";
    cout << left << setw(20) << *(userHeader + 1) << " | ";
    cout << left << setw(19) << *(userHeader + 3) << " | ";
    cout << left << setw(20) << *(userHeader + 4) << " | ";
    cout << endl;
    cout << string(83, '-') << endl;

    while (current != nullptr) {
        // Convert std::tm to string
        char login[20];
        char logout[20];

        strftime(login, 20, "%Y-%m-%d %H:%M:%S", current->lastTimeLogin);
        strftime(logout, 20, "%Y-%m-%d %H:%M:%S", current->lastTimeLogout);
        string date1(login);
        string date2(logout);

        cout << " | ";
        cout << left << setw(9) << current->userID << " | ";
        cout << left << setw(20) << current->username << " | ";
        cout << right << setw(19) << date1 << " | ";
        cout << right << setw(20) << date2 << " | ";
        //        cout << right << setw(20) << int(second)/86400 << " | ";
        current = current->nextUser;
        cout << endl;
    }
    cout << string(83, '-') << endl;
    cout << "Number of user shown: " << userSize << endl;
}

void User::addUserHeader(string header[]) {
    for (int i = 0; i < 5; i++) {
        *(userHeader + i) = header[i];
    }
}

void User::userRegister() {
    string name, pass, pass2;
    while (true) {
        cout << "Enter the username: ";
        cin >> name;
        if (!usernameValidation(name)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        while (true) {
            cout << "Enter your password: ";
            cin >> pass;
            if (!checkPasswordFormat(pass)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Check your password format!" << endl;
                continue;
            }
            else {
                cout << "Re-enter your password: ";
                cin >> pass2;
                if (pass != pass2) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Passwords not same!" << endl;
                    continue;
                }
            }
            break;
        }
        break;
    }

    if (cin.fail()) {
        cout << "Error input!" << endl;
        userRegister();
    }

    if (pass != pass2) {
        cout << "Passwords not same!" << endl;
        userRegister();
    }
    else {

    }

    // Generator UserID according to size of user
    stringstream ss;
    ss << "U" << setw(8) << setfill('0') << (userSize + 1);
    string userid = ss.str();
    string data[5] = { userid, name, pass, "", "" };

    UserNode* newUserNode = createUserNode(data);
    appendUserNode(newUserNode);
}

bool User::usernameValidation(string username) {
    regex pattern("^[a-zA-Z0-9_]{4,20}$");
    if (!regex_match(username, pattern)) {
        cout << "Username cannot contain special characters!" << endl;
        return false;
    }
    else {
        if (userHead == nullptr)
            return true;
        else {
            UserNode* temp = userHead;
            while (temp->nextUser != nullptr) {
                if (temp->username == username) {
                    cout << "Username existed! Please try another username." << endl;
                    return false;
                }
                temp = temp->nextUser;
            }
        }
    }
    return true;
}

bool User::checkPasswordFormat(string password) {
    regex pattern("^(?=.?[A-Z])(?=.?[a-z])(?=.?[0-9])(?=.?[#?!@$%^&*-]).{8,20}$");
    if (!regex_match(password, pattern)) {
        return false;
    }
    return true;
}

void User::deleteInactiveUsers() {
    // Get the current date in %Y-%m-%d format
    time_t currentTime = time(nullptr);
    tm* currentDate = localtime(&currentTime);
    ostringstream oss;
    oss << put_time(currentDate, "%Y-%m-%d");
    string currentDateString = oss.str();

    // Traverse the linked list to delete inactive users
    UserNode* current = userHead;
    UserNode* previous = nullptr;

    while (current != nullptr) {
        // Extract the date from the last logout date and time saved in user.csv in %Y-%m-%d format
        tm* lastLogoutDate = current->lastTimeLogout;
        ostringstream logoutDateStream;
        logoutDateStream << std::put_time(lastLogoutDate, "%Y-%m-%d");
        string lastLogoutDateString = logoutDateStream.str();

        // Get the difference between the extracted last logout date and the current date
        tm lastLogout = {};
        istringstream(lastLogoutDateString) >> get_time(&lastLogout, "%Y-%m-%d");
        time_t lastLogoutTime = mktime(&lastLogout);
        double daysSinceLogout = difftime(currentTime, lastLogoutTime) / (24 * 60 * 60);

        // Check if the days since logout equals or exceeds 1 year (365 days)
        if (daysSinceLogout >= 365) {
            // Delete the inactive user
            if (previous == nullptr) {
                // User is at the head of the list
                userHead = current->nextUser;
            }
            else {
                // User is in the middle or at the tail of the list
                previous->nextUser = current->nextUser;
                if (current == userTail) {
                    userTail = previous;
                }
            }
            UserNode* nextNode = current->nextUser;
            delete current;
            current = nextNode;

            userSize--;
        }
        else {
            previous = current;
            current = current->nextUser;
        }
    }
    cout << "Users who have been inactive for 1 year and above have been deleted." << endl;
    DataIO::SaveUser(userHead);
}

void User::userLogin() {
    string name, pass;
    while (true) {
        cout << "User Login" << endl;
        cout << "Enter username: ";
        cin >> name;
        UserNode* theUser = searchUser(name);
        if (theUser == nullptr) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Account doesn't exist!" << endl;
        }
        else {
            for (int i = 0; i <= 3; i++) {
                cout << "Enter your password: ";
                cin >> pass;
                if (pass != theUser->password) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error password!";
                    cout << 3 - i << " time attempt left.\n\n" << endl;
                }
                else {
                    this->loginUser = theUser;
                    string loginTime = DataIO::getCurrentTime();
                    loginUser->lastTimeLogin = DataIO::StringToTime(loginTime);
                    cout << "Login Time: " << DataIO::TimeToString(loginUser->lastTimeLogin) << endl;
                    break;
                }
            }
            if (loginUser != nullptr) {
                break;
            }
            else {
                cout << "Too many attempt! Please try again!\n\n";
            }
        }
    }
}

void User::userLogout() {
    string logoutTime = DataIO::getCurrentTime();
    loginUser->lastTimeLogout = DataIO::StringToTime(logoutTime);
    cout << "Successfully Logout!" << endl;
    cout << "Logout Time: " << DataIO::TimeToString(loginUser->lastTimeLogout) << endl;
    loginUser = nullptr;
}

UserNode *User::getLoginUser() const {
    return loginUser;
}

void User::setLoginUser(UserNode *loginUser) {
    User::loginUser = loginUser;
}




