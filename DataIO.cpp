//
// Created by Wyatt Cheang on 16/03/2023.
//

#include <sstream>
#include <iostream>
#include "DataIO.h"
#include "University.h"

using namespace std;

void DataIO::ReadUniversity(University* head) {
    fstream file;
    file.open("csvFiles/data.csv", ios::in);
    string data[21];
    size_t repPosition;

    if(file.is_open()){
        // ReadUniversity header
        for (int i = 0; i < 21; i++) {
            if (i == 20) {
                getline(file, data[i]);
                if (data[20].back() == '\r')  //remove '\r' at the last of the string
                    (data[20]).erase(data[20].end() - 1);
            }else
                getline(file, data[i], ',');
        }
        head->addUniHeader(data);

        while(file.good() && !file.eof()){
            // get the 1st data data, if the data is empty, it will break the loop
            getline(file, data[0], ',');
            if (data[0].empty()) break;

            for(int i = 1; i < 21; i++){
                // get each cells
                if (i != 20) getline(file, data[i], ',');
                else {
                    getline(file, data[i]);
                    data[20].erase(data[i].end() - 1);
                }

                // Data Manipulation

                if(data[i] == "") data[i] = "0";
                if(data[i] == "-") data[i] = "-1";
                if(data[i].front() == ' ') data[i].erase(data[i].begin());

                // continue read the university name if it is contain ',' character
                string temp;
                if (data[i][0] == '"' && data[i].back() != '"') {
                    do {
                        getline(file, temp, ',');
                        data[i] = data[i] + "," + temp;
                    } while(temp.back() != '"');
                }

                // remove extra '"' symbol for the institutionName's name
                if(data[i].front() == '"' && data[i].back() == '"') {
                    data[i].erase(data[i].begin());
                    data[i].erase(data[i].end() - 1);
                    while ((repPosition = data[i].find("\"\"")) != string::npos)
                        data[i].replace(repPosition, 2, "\"");
                }
            }
            // get a new node returned by passing the string array
            UniversityNode *add = head->createNewUniversityNode(data);

            // append the new node to the end of the list
            head->appendUniList(add);
        }
    }
    else
        cout<<"Could not open the file\n";
}

void DataIO::ReadUser(User *head) {
    string column[5];
    fstream file;
    file.open("csvFiles/user.csv", ios::in);

    if(file.is_open()){
        for (int i = 0; i < 5; i++) {
            if (i == 4) {
                getline(file, *(column + i));
                if (column[4].back() == '\r')  //remove '\r' at the last of the string
                    (column[4]).erase(column[4].end() - 1);
            } else
                getline(file, column[i], ',');
        }

        head->addUserHeader(column);

        while(file.good()){

            getline(file, *(column + 0), ',');
            if ((column + 0)->empty()) break;

            for (int i = 1; i < 5; i++){
                if (i != 4) getline(file, column[i], ',');
                else
                    getline(file, column[i]);
                    if(column[i].back() == '\r')  //remove '\r' at the last of the string
                    (column[i]).erase(column[i].end() - 1);
            }
            UserNode* add = head->createUserNode(column);
            head->appendUserNode(add);
        }
    }else{
        cout<<"Could not open the file\n";
    }
    file.close();
}

void DataIO::ReadAdmin(Admin *head) {
    string column[3];
    fstream file;
    file.open("csvFiles/admin.csv", ios::in);

    if(file.is_open()){
        for (int i = 0; i < 3; i++) {
            if (i == 4) {
                getline(file, *(column + i));
                if (column[4].back() == '\r')  //remove '\r' at the last of the string
                    (column[4]).erase(column[4].end() - 1);
            } else
                getline(file, column[i], ',');
        }

        while(file.good()){

            getline(file, *(column + 0), ',');
            if ((column + 0)->empty()) break;

            for (int i = 1; i < 5; i++){
                if (i != 4) getline(file, column[i], ',');
                else
                    getline(file, column[i]);
                if(column[i].back() == '\r')  //remove '\r' at the last of the string
                    (column[i]).erase(column[i].end() - 1);
            }
            AdminNode* add = head->createAdminNode(column);
            head->appendAdminNode(add);
        }
    }else{
        cout<<"Could not open the file\n";
    }
    file.close();
}

void DataIO::ReadFeedback(Feedback *head) {

}

void DataIO::ReadFavorite(Favorite *head) {

}

void DataIO::SaveUser(UserNode* head) {
    ofstream file("csvFiles/user.csv");
    if (!file.is_open()){
        cout << "Could not open file." << endl;
        return;
    }
    UserNode *temp = head;
    file << "User ID,Username,Password,Last Login Datetime, LastLogout Datetime\n";
    while (temp != nullptr){
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


