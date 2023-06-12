//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Favourite.h"
#include "User.h"
#include "DataIO.h"
#include <iostream>
#include <utility>
using namespace std;

const string filePath = "C:\\Users\\jamie\\Source\\Repos\\DSTR_Assignment\\csvFiles\\";

Favourite::Favourite(University* uniClass, User* userClass) {
    this->uniClass = uniClass;
    this->userClass = userClass;
    DataIO::ReadFavourite(this, uniClass, userClass);
}

Favourite::~Favourite() {
    DataIO::SaveFavourite(this->favouriteHead);
}

FavouriteNode* Favourite::createFavouriteNode(UniversityNode* uniNode, UserNode* userNode) {
    FavouriteNode* newFavouriteNode = new FavouriteNode;
    newFavouriteNode->favUniversity = uniNode;
    newFavouriteNode->favUser = userNode;
    newFavouriteNode->nextFav = nullptr;
    return newFavouriteNode;
}

void Favourite::appendFavouriteNode(FavouriteNode* newNode) {
    if (this->favouriteHead == nullptr) {
        this->favouriteHead = this->favouriteTail = newNode;
        favSize++;
        return;
    }
    this->favouriteTail->nextFav = newNode;
    this->favouriteTail = newNode;
    favSize++;
}

void Favourite::addFavourite(UniversityNode* favUniversity)
{
    UniversityNode* uniNode = favUniversity;
    UserNode* userNode = userClass->getLoginUser();
    FavouriteNode* newFavouriteNode = createFavouriteNode(uniNode, userNode);
    appendFavouriteNode(newFavouriteNode);
}

void Favourite::printUserFavourite() {
    int count = 0;
    FavouriteNode* current = this->favouriteHead;

    if (current == nullptr) {
        cout << "No Favourite University" << endl;
        return;
    }
    uniClass->PrintTableHeader();

    while (current != nullptr){
        if (current->favUser == userClass->getLoginUser()){
            uniClass->DisplayTheUniversity(current->favUniversity);
            count++;
        }
        current = current->nextFav;
    }
    cout << string (334, '-') << endl;
    cout << "Total Favourite: " << count << endl;
    cout << endl;
}

bool Favourite::checkDuplicatedFavourite(UniversityNode* favUniversity) {
    FavouriteNode *current = this->favouriteHead;
    while (current != nullptr) {
        if (current->favUniversity == favUniversity && current->favUser == userClass->getLoginUser()) {
            return true;
        }
        current = current->nextFav;
    }
    return false;
}

void Favourite::calculateSumFavourite() {
    FavouriteNode* currentFav = this->favouriteHead;
    sumFavHead = nullptr;
    while (currentFav != nullptr) {
        // Get the favorite university from the current FavouriteNode
        UniversityNode* currentUniversity = currentFav->favUniversity;

        // Check if the university is already present in the SumFavouriteNode list
        SumFavouriteNode* currentSum = sumFavHead;
        while (currentSum != nullptr) {
            // If the university is found, increment the favorite count
            if (currentSum->sumFavUniversity == currentUniversity) {
                currentSum->sumFavCount++;
                break;
            }
            currentSum = currentSum->nextSumFav;
        }

        // If the university is not found, create a new SumFavouriteNode and add it to the list
        if (currentSum == nullptr) {
            SumFavouriteNode* newSumNode = new SumFavouriteNode;
            newSumNode->sumFavUniversity = currentUniversity;
            newSumNode->sumFavCount = 1;
            newSumNode->nextSumFav = sumFavHead;
            sumFavHead = newSumNode;
        }

        // Move to the next FavouriteNode
        currentFav = currentFav->nextFav;
    }
}

void Favourite::sortSumFavouriteList() {
    if (sumFavHead == nullptr || sumFavHead->nextSumFav == nullptr) {
        // Empty list or single node, no need to sort
        return;
    }
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        SumFavouriteNode* current = sumFavHead;
        SumFavouriteNode* nextNode = sumFavHead->nextSumFav;

        while (nextNode != nullptr) {
            // Compare the favorite counts
            if (current->sumFavCount < nextNode->sumFavCount) {
                // Swap the nodes
                UniversityNode* tempUniversity = current->sumFavUniversity;
                int tempCount = current->sumFavCount;

                current->sumFavUniversity = nextNode->sumFavUniversity;
                current->sumFavCount = nextNode->sumFavCount;

                nextNode->sumFavUniversity = tempUniversity;
                nextNode->sumFavCount = tempCount;

                sorted = false;
            }
            // Move to the next nodes
            current = nextNode;
            nextNode = nextNode->nextSumFav;
        }
    }
}

void Favourite::printSumFavourite() {
    int total = 0;
    cout << "Sum of Favourite" << endl;
    cout << string(100, '=') << endl;
    cout << " | ";
    cout << left << setfill(' ') << setw(86) << "University Name";
    cout << " | ";
    cout << right << setfill(' ') << setw(5) << "Count";
    cout << " | " << endl;
    cout << string(100, '=') << endl;

    while (sumFavHead != nullptr) {
        int checkTwoByte = 0;
        int checkThreeByte = 0;
        University::UniversityNameAlignment(sumFavHead->sumFavUniversity, checkTwoByte, checkThreeByte);
        cout << " | ";
        cout << left << setw(86 + checkTwoByte + checkThreeByte) << sumFavHead->sumFavUniversity->institutionName << " | ";
        cout << right << setw(5) << sumFavHead->sumFavCount << " | " << endl;
        sumFavHead = sumFavHead->nextSumFav;
        total++;
        if (total == 10) {
            break;
        }
    }
    cout << string(100, '-') << endl;
}
