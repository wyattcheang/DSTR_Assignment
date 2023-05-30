//
// Created by Wyatt Cheang on 23/03/2023.
//

#ifndef ASSIGNMENT_FAVOURITE_H
#define ASSIGNMENT_FAVOURITE_H
#include "University.h"
#include "User.h"

struct FavouriteNode {
    string favUniversity;
    string favUser;
    FavouriteNode* nextFav;
};

class Favourite {
private:
    FavouriteNode* favouriteHead = nullptr;
    FavouriteNode* favouriteTail = nullptr;
    int favSize = 0;
public:
    //Required Functions
    Favourite();
    ~Favourite();
    FavouriteNode* createFavouriteNode(string data[]);
    void appendFavouriteNode(FavouriteNode* newNode);
    void addFavourite(string uniName, string username);
};


#endif //ASSIGNMENT_FAVOURITE_H