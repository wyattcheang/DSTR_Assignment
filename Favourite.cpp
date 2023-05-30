//
// Created by Wyatt Cheang on 23/03/2023.
//

#include "Favourite.h"
#include "User.h"
#include "DataIO.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <utility>
#include <sstream>
#include <regex>
#include <fstream>
using namespace std;

const string filePath = "C:\\Users\\jamie\\Source\\Repos\\DSTR_Assignment\\csvFiles\\";

Favourite::Favourite() {
    DataIO::ReadFavourite(this);
}

Favourite::~Favourite() {
    DataIO::SaveFavourite(this->favouriteHead);
}

FavouriteNode* Favourite::createFavouriteNode(string data[]) {
    FavouriteNode* newFavouriteNode = new FavouriteNode;
    newFavouriteNode->favUniversity = data[0];
    newFavouriteNode->favUser = data[1];
    newFavouriteNode->nextFav = nullptr;
    return newFavouriteNode;
}

void Favourite::appendFavouriteNode(FavouriteNode* newNode) {
    if (this->favouriteTail == nullptr) {
        this->favouriteHead = this->favouriteTail = newNode;
        favSize++;
        return;
    }
    this->favouriteTail->nextFav = newNode;
    this->favouriteTail = newNode;
    favSize++;
}

void Favourite::addFavourite(string uniName, string username)
{
    if (!uniName.empty() && !username.empty()) {
        string data[2] = { uniName, username };
        FavouriteNode* newFavouriteNode = createFavouriteNode(data);
        appendFavouriteNode(newFavouriteNode);

        DataIO::SaveFavourite(favouriteHead);
    }
}