//
// Created by Wyatt Cheang on 16/03/2023.
//

#include <sstream>
#include <iostream>
#include <filesystem>
#include "DataIO.h"
#include "University.h"

using namespace std;

#ifndef _FILE_PATH_H
#define _FILE_PATH_H

#ifdef _WIN32
const string filePath = "C:\\Users\\joeyk\\Source\\Repos\\DSTR_Assignment\\csvFiles\\";
#else
const string filePath = "csvFiles/";
#endif

#endif // _FILE_PATH_H


void DataIO::ReadUniversity(University* head) {

    fstream file;
    file.open(filePath + "data.csv", ios::in);
    string data[21];
    size_t repPosition;

    if (file.is_open()) {
        // ReadUniversity header
        for (int i = 0; i < 21; i++) {
            if (i == 20) {
                getline(file, data[i]);
                if (data[20].back() == '\r')  //remove '\r' at the last of the string
                    (data[20]).erase(data[20].end() - 1);
            }
            else
                getline(file, data[i], ',');
        }
        head->addUniHeader(data);

        while (file.good() && !file.eof()) {
            // get the 1st data data, if the data is empty, it will break the loop
            getline(file, data[0], ',');
            if (data[0].empty()) break;

            for (int i = 1; i < 21; i++) {
                // get each cells
                if (i != 20) getline(file, data[i], ',');
                else {
                    getline(file, data[i]);
                    data[20].erase(data[i].end() - 1);
                }

                // Data Manipulation

                if (data[i] == "") data[i] = "0";
                if (data[i] == "-") data[i] = "-1";
                if (data[i].front() == ' ') data[i].erase(data[i].begin());

                // continue read the university name if it is contain ',' character
                string temp;
                if (data[i][0] == '"' && data[i].back() != '"') {
                    do {
                        getline(file, temp, ',');
                        data[i] = data[i] + "," + temp;
                    } while (temp.back() != '"');
                }

                // remove extra '"' symbol for the institutionName's name
                if (data[i].front() == '"' && data[i].back() == '"') {
                    data[i].erase(data[i].begin());
                    data[i].erase(data[i].end() - 1);
                    while ((repPosition = data[i].find("\"\"")) != string::npos)
                        data[i].replace(repPosition, 2, "\"");
                }
            }
            // get a new node returned by passing the string array
            UniversityNode* add = head->createNewUniversityNode(data);

            // append the new node to the end of the list
            head->appendUniList(add);
        }
    }
    else
        cout << "Could not open the file\n";
}

void DataIO::ReadUser(User* head) {
    string column[5];
    fstream file;
    file.open(filePath + "user.csv", ios::in);

    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            if (i == 4) {
                getline(file, *(column + i));
                if (column[4].back() == '\r')  //remove '\r' at the last of the string
                    (column[4]).erase(column[4].end() - 1);
            }
            else
                getline(file, column[i], ',');
        }

        head->addUserHeader(column);

        while (file.good()) {

            getline(file, *(column + 0), ',');
            if ((column + 0)->empty()) break;

            for (int i = 1; i < 5; i++) {
                if (i != 4) getline(file, column[i], ',');
                else
                    getline(file, column[i]);
                if (column[i].back() == '\r')  //remove '\r' at the last of the string
                    (column[i]).erase(column[i].end() - 1);
            }
            UserNode* add = head->createUserNode(column);
            head->appendUserNode(add);
        }
    }
    else {
        cout << "Could not open the file\n";
    }
    file.close();
}

void DataIO::ReadAdmin(Admin* head) {
    string column[3];
    fstream file;
    file.open(filePath + "admin.csv", ios::in);

    if (file.is_open()) {
        for (int i = 0; i < 3; i++) {
            if (i == 2) {
                getline(file, *(column + i));
                if (column[2].back() == '\r')  //remove '\r' at the last of the string
                    (column[2]).erase(column[2].end() - 1);
            }
            else
                getline(file, column[i], ',');
        }

        while (file.good()) {

            getline(file, *(column + 0), ',');
            if ((column + 0)->empty()) break;

            for (int i = 1; i < 3; i++) {
                if (i != 2) getline(file, column[i], ',');
                else
                    getline(file, column[i]);
                if (column[i].back() == '\r')  //remove '\r' at the last of the string
                    (column[i]).erase(column[i].end() - 1);
            }

            head->appendAdminNode(column);
        }
    }
    else {
        cout << "Could not open the file\n";
    }
    file.close();
}

void DataIO::ReadFeedback(Feedback* head) {

}

void DataIO::ReadFavourite(Favourite* head) {
    string column[2];
    fstream file;
    file.open(filePath + "favourite.csv", ios::in);

    if (file.is_open()) {
        for (int i = 0; i < 2; i++) {
            if (i == 1) {
                getline(file, *(column + i));
                if (column[1].back() == '\r')  //remove '\r' at the last of the string
                    (column[1]).erase(column[1].end() - 1);
            }
            else
                getline(file, column[i], ',');
        }

        while (file.good()) {

            getline(file, *(column + 0), ',');
            if ((column + 0)->empty()) break;

            for (int i = 1; i < 2; i++) {
                if (i != 1) getline(file, column[i], ',');
                else
                    getline(file, column[i]);
                if (column[i].back() == '\r')  //remove '\r' at the last of the string
                    (column[i]).erase(column[i].end() - 1);
            }

            FavouriteNode* add = head->createFavouriteNode(column);
            head->appendFavouriteNode(add);
        }
    }
    else {
        cout << "Could not open the file\n";
    }
    file.close();
}

void DataIO::SaveUser(UserNode* head) {
    ofstream file(filePath + "user.csv");
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }
    UserNode* temp = head;
    file << "User ID,Username,Password,Last Login Datetime, LastLogout Datetime\n";
    while (temp != nullptr) {
        char login[20];
        char logout[20];
        strftime(login, 20, "%Y-%m-%d %H:%M:%S", temp->lastTimeLogin);
        strftime(logout, 20, "%Y-%m-%d %H:%M:%S", temp->lastTimeLogout);
        string date1(login);
        string date2(logout);

        file << temp->userID << ',';
        file << temp->username << ',';
        file << temp->password << ',';
        file << login << ',';
        file << logout << '\n';
        temp = temp->nextUser;
    }
    file.close();
}

void DataIO::SaveFavourite(FavouriteNode* head) {
    ofstream file(filePath + "favourite.csv", ios::app);
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }
    FavouriteNode* temp = head;
    while (temp != nullptr) {
        file << temp->favUniversity << ',';
        file << temp->favUser << '\n';
        temp = temp->nextFav;
    }
    file.close();
}

void DataIO::SaveFeedback(FeedbackNode* head) {
    ofstream file(filePath + "feedback.csv", ios::app);
    if (!file.is_open()) {
        cout << "Could not open file." << endl;
        return;
    }
    FeedbackNode* temp = head;
    while (temp != nullptr) {
        file << temp->feedbackID << ',';
        file << temp->feedbackUser << ',';
        file << temp->replyAdmin << ',';
        file << temp->feedbackUniversity << ',';
        file << temp->feedback << ',';
        file << temp->reply << ',';
        file << temp->feedbackDatetime << ',';
        file << temp->replyDatetime << '\n';
    }
    file.close();
}

tm* DataIO::StringToTime(const string& dateString) {
    tm* tm = new struct tm;
    std::istringstream ss(dateString);
    ss >> std::get_time(tm, "%Y-%m-%d %H:%M:%S"); // or just %T in this case
    return tm;
}

string DataIO::getCurrentTime() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    return DataIO::TimeToString(localTime);
}

string DataIO::TimeToString(tm *time) {
    char buffer[20];
    strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", time);
    string date(buffer);
    return date;
}

void DataIO::printStringCentered(const string& text) {
    int lineLength = 100;
    int textLength = text.length();
    int leftPadding = (lineLength - textLength) / 2;
    cout << setw(leftPadding) << "" << text  << endl;
}

void DataIO::printSelectUniversityAttributeMenu(){
    cout << "(1) Rank" << endl;
    cout << "(2) Name" << endl;
    cout << "(3) Country" << endl;
    cout << "(4) Country Code" << endl;
    cout << "(5) AR (Academic Reputation) Score" << endl;
    cout << "(6) AR (Employer Reputation) Rank" << endl;
    cout << "(7) ER (Employer Reputation) Score" << endl;
    cout << "(8) ER (Employer Reputation) Rank" << endl;
    cout << "(9) FSR (Faculty/Student Ratio) Score" << endl;
    cout << "(10) FSR (Faculty/Student Ratio) Rank" << endl;
    cout << "(11) CPF (Citations per Faculty) Score" << endl;
    cout << "(12) CPF (Citations per Faculty) Rank" << endl;
    cout << "(13) IFR (International Faculty Ratio) Score" << endl;
    cout << "(14) IFR (International Faculty Ratio) Rank" << endl;
    cout << "(15) ISR (International Student Ratio) Score" << endl;
    cout << "(16) ISR (International Student Ratio) Rank" << endl;
    cout << "(17) IRN (International Research Network) Score" << endl;
    cout << "(18) IRN (International Research Network) Rank" << endl;
    cout << "(19) GER (Employment Outcome) Score" << endl;
    cout << "(20) GER (Employment Outcome) Rank" << endl;
    cout << "(21) Score Scaled" << endl;
    cout << endl << "Enter you selection: ";
}

void DataIO::selectSortMethodMenu(){
    cout << "Select sort method: " << endl;
    cout << "(1) Merge Sort" << endl;
    cout << "(2) Quick Sort" << endl;
    cout << endl << "Enter you selection: ";
}

void DataIO::selectSearchMethodMenu(){
    cout << "Select search method: " << endl;
    cout << "(1) Linear Search" << endl;
    cout << "(2) Binary Search" << endl;
    cout << endl << "Enter you selection: ";
}