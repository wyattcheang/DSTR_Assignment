//
// Created by Wyatt Cheang on 16/03/2023.


#include <iostream>
using namespace std;

#ifndef ASSIGNMENT_UNIVERSITY_H
#define ASSIGNMENT_UNIVERSITY_H

enum sortOption {uniRank, uniName, uniLocation, uniLocationCode,
        arScore, arRank, erScore, erRank, fsrScore, fsrRank, cpfScore, cpfRank,
        ifrScore, ifrRank, isrScore, isrRank, irnScore, irnRank, gerScore, gerRank, scoreScaled};

struct UniversityNode {
    UniversityNode* previousUni;
    int rank;
    string institutionName;
    string locationCode;
    string location;
    double arScore;
    string arRank;
    double erScore;
    string erRank;
    double fsrScore;
    string fsrRank;
    double cpfScore;
    string cpfRank;
    double ifrScore;
    string ifrRank;
    double isrScore;
    string isrRank;
    double irnScore;
    string irnRank;
    double gerScore;
    string gerRank;
    double scoreScaled;
    UniversityNode* nextUni;
};

class University {
private:
    UniversityNode* universityHead = nullptr;
    UniversityNode* universityTail = nullptr;
    string* universityHeader = new string[21];
    sortOption option;
    int uniListSize = 0;
public:
    chrono::duration<double> timeTaken;
    University();
    ~University();
    void addUniHeader(string data[]);
    UniversityNode* createNewUniversityNode(string data[]);
    void appendUniList(UniversityNode* newNode);
    void DisplayData();

    // for feedback
    UniversityNode* searchUniversity(string rank);
    UniversityNode* searchUniversityWithName(string uniName);

    // functions of merge sort
    void splitList(UniversityNode* list, UniversityNode** leftList, UniversityNode** rightList);
    UniversityNode* mergeList(UniversityNode* left, UniversityNode* right);
    void mergeSort(UniversityNode** list);

    // functions of quick sort
    UniversityNode* partition(UniversityNode* head, UniversityNode* end, UniversityNode** newHead, UniversityNode** newEnd);
    UniversityNode* quickSort(UniversityNode* head, UniversityNode* end);

    bool compareNode(UniversityNode* left, UniversityNode* right);
    UniversityNode* getTail(UniversityNode* cur);

    void callMergeSort(sortOption option);
    void callQuickSort(sortOption option);

    void LinearSearch(string search, sortOption option);
    void JumpSearch(string search, sortOption option);
    void PerformSearch(int searchMethod, int searchAttributeSelection, const string& searchKeyword);
    bool compareValues(sortOption attributes, const string& keyword, UniversityNode* current);

    static int RemovePlusSymbol(string otherRank);
    static bool isSubstring(const std::string& a, const std::string& b);
    void PrintTableHeader();
    void DisplayTheUniversity(UniversityNode* current);
    static void UniversityNameAlignment(UniversityNode *current, int &checkTwoByte, int &checkThreeByte);

    int getUniListSize() const;
};

#endif //ASSIGNMENT_UNIVERSITY_H