//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_FAVOURITE_H
#define ASSIGNMENT_FAVOURITE_H
#include "University.h"
#include "User.h"

struct FavouriteNode {
    UniversityNode* favUniversity;
    UserNode* favUser;
    FavouriteNode* nextFav;
};

struct SumFavouriteNode{
    UniversityNode* sumFavUniversity;
    int sumFavCount;
    SumFavouriteNode* nextSumFav;
};

class Favourite {
private:
    FavouriteNode* favouriteHead = nullptr;
    FavouriteNode* favouriteTail = nullptr;
    SumFavouriteNode* sumFavHead = nullptr;
    University* uniClass = nullptr;
    User* userClass = nullptr;
    int favSize = 0;
public:
    //Required Functions
    Favourite(University* uniClass, User* userClass);
    ~Favourite();
    FavouriteNode* createFavouriteNode(UniversityNode* uniNode, UserNode* userNode);
    void appendFavouriteNode(FavouriteNode* newNode);
    void addFavourite(UniversityNode* favUniversity);
    bool checkDuplicatedFavourite(UniversityNode* favUniversity);
    void printUserFavourite();
    void calculateSumFavourite();
    void sortSumFavouriteList();
    void printSumFavourite();
};

#endif //ASSIGNMENT_FAVOURITE_H