//
// Created by Wyatt Cheang on 16/03/2023.
//

#include <iomanip>
#include <iostream>
#include "University.h"
#include "DataIO.h"
#include <chrono>


using namespace std;

University::University() {
    DataIO::ReadUniversity(this);
};

University::~University() {
}

void University::appendUniList(UniversityNode* newNode) {
    UniversityNode* current = this->universityHead;
    if (current == nullptr) {
        newNode->previousUni = nullptr;
        this->universityHead = newNode;
        this->universityTail = newNode;
        uniListSize++;
        return;
    }
    universityTail->nextUni = newNode;
    newNode->previousUni = universityTail;
    universityTail = newNode;
    uniListSize++;
}

//void University::reverseDisplay() {
//    reverseDisplay(this->universityHead);
//}
//
//void University::reverseDisplay(UniversityNode* cur){
//    if (cur == nullptr) return;
//    reverseDisplay(cur->nextUni);
//    cout << cur->rank << endl;
//}

void University::DisplayData() {
    UniversityNode* current = universityHead;

    this->PrintTableHeader();

    while (current != nullptr) {
        University::DisplayTheUniversity(current);
        current = current->nextUni;
    }
    cout << string(334, '-') << endl;
    cout << "Number of university shown: " << uniListSize << endl << endl;
}

UniversityNode* University::createNewUniversityNode(string data[]) {
    UniversityNode* newNode = new UniversityNode();
    newNode->rank = stoi(data[0]);
    newNode->institutionName = data[1];
    newNode->locationCode = data[2];
    newNode->location = data[3];
    newNode->arScore = stod(data[4]);
    newNode->arRank = (data[5]);
    newNode->erScore = stod(data[6]);
    newNode->erRank = (data[7]);
    newNode->fsrScore = stod(data[8]);
    newNode->fsrRank = (data[9]);
    newNode->cpfScore = stod(data[10]);
    newNode->cpfRank = (data[11]);
    newNode->ifrScore = stod(data[12]);
    newNode->ifrRank = (data[13]);
    newNode->isrScore = stod(data[14]);
    newNode->isrRank = (data[15]);
    newNode->irnScore = stod(data[16]);
    newNode->irnRank = (data[17]);
    newNode->gerScore = stod(data[18]);
    newNode->gerRank = (data[19]);
    newNode->scoreScaled = stod(data[20]);
    newNode->nextUni = nullptr;

    return newNode;
}

static void toUpper(std::string& str) {
    for (char& c : str) {
        c = toupper(c);
    }
}


bool University::compareNode(UniversityNode* left, UniversityNode* right) {
    string leftName, rightName, leftLocation, rightLocation, leftLocationCode, rightLocationCode;
    int nameCompare, locationCompare, locationCodeCompare, scoreCompare, rankCompare, otherRankCompare;
    double leftValue = 0, rightValue = 0;
    rankCompare = left->rank < right->rank;

    switch (this->option) {
        case uniRank:
            rankCompare = left->rank < right->rank;
            return rankCompare < 0;
            break;
        case uniName:
            leftName = left->institutionName;
            rightName = right->institutionName;
            toUpper(leftName);
            toUpper(rightName);
            nameCompare = leftName.compare(rightName);
            if (nameCompare == 0) return rankCompare < 0;
            else return nameCompare > 0;
            break;
        case uniLocation:
            leftLocation = left->location;
            rightLocation = right->location;
            toUpper(leftLocation);
            toUpper(rightLocation);
            locationCompare = leftLocation.compare(rightLocation);
            if (locationCompare == 0) return rankCompare < 0;
            else return locationCompare > 0;
            break;
        case uniLocationCode:
            leftLocationCode = left->locationCode;
            rightLocationCode = right->locationCode;
            toUpper(leftLocationCode);
            toUpper(rightLocationCode);
            locationCodeCompare = leftLocationCode.compare(rightLocationCode);
            if (locationCodeCompare == 0) return rankCompare < 0;
            else return locationCodeCompare > 0;
        case arScore:
            leftValue = left->arScore;
            rightValue = right->arScore;
            break;
        case fsrScore:
            leftValue = left->fsrScore;
            rightValue = right->fsrScore;
            break;
        case erScore:
            leftValue = left->erScore;
            rightValue = right->erScore;
            break;
        case cpfScore:
            leftValue = left->cpfScore;
            rightValue = right->cpfScore;
            break;
        case ifrScore:
            leftValue = left->ifrScore;
            rightValue = right->ifrScore;
            break;
        case isrScore:
            leftValue = left->isrScore;
            rightValue = right->isrScore;
            break;
        case irnScore:
            leftValue = left->irnScore;
            rightValue = right->irnScore;
            break;
        case gerScore:
            leftValue = left->gerScore;
            rightValue = right->gerScore;
            break;
        case scoreScaled:
            leftValue = left->scoreScaled;
            rightValue = right->scoreScaled;
            break;
        case arRank:
            leftValue = stoi(left->arRank);
            rightValue = stoi(right->arRank);
            break;
        case fsrRank:
            leftValue = stoi(left->fsrRank);
            rightValue = stoi(right->fsrRank);
            break;
        case erRank:
            leftValue = stoi(left->erRank);
            rightValue = stoi(right->erRank);
            break;
        case cpfRank:
            leftValue = stoi(left->cpfRank);
            rightValue = stoi(right->cpfRank);
            break;
        case ifrRank:
            leftValue = stoi(left->ifrRank);
            rightValue = stoi(right->ifrRank);
            break;
        case isrRank:
            leftValue = stoi(left->isrRank);
            rightValue = stoi(right->isrRank);
            break;
        case irnRank:
            leftValue = stoi(left->irnRank);
            rightValue = stoi(right->irnRank);
            break;
        case gerRank:
            leftValue = stoi(left->gerRank);
            rightValue = stoi(right->gerRank);
            break;
        default:
            break;
    }

    // scoreCompare : 0 to take left node, 1 to take right node
    if (this->option == arRank || this->option == fsrRank || this->option == erRank || this->option == cpfRank ||
        this->option == ifrRank || this->option == isrRank || this->option == irnRank || this->option == gerRank) {
        if (leftValue == 0)
            return 1;
        else if (rightValue == 0)
            return 0;
        else
            rankCompare = (leftValue > rightValue) || (leftValue == rightValue && rankCompare == 0);

        if (this->option != ::uniRank && this->option != ::uniName && rankCompare == 0)
            return 0;
        else return 1;

    }
    if (this->option == arScore || this->option == fsrScore || this->option == erScore || this->option == cpfScore ||
        this->option == ifrScore || this->option == isrScore || this->option == irnScore || this->option == gerScore ||
        this->option == scoreScaled) {
        if (leftValue == 0)
            return 1;
        else if (rightValue == 0)
            return 0;
        else
            scoreCompare = (leftValue < rightValue) || (leftValue == rightValue && rankCompare == 0);
        if (this->option != ::uniRank && this->option != ::uniName && scoreCompare == 0)
            return 0;
        else return 1;
    }
    return 0;
}

//    if ((this->option == ::uniRank && rankCompare == 1) ||
//        (this->option == ::uniName && nameCompare < 0) ||
//        (this->option != ::uniRank && this->option != ::uniName && scoreCompare == 0))
//        return 0;
//    else return 1;

// merge sort

void University::splitList(UniversityNode* list, UniversityNode** leftList, UniversityNode** rightList) {
    UniversityNode* slow = list, * fast = list->nextUni;

    // get the middle note in the list
    while (fast != nullptr) {
        fast = fast->nextUni;
        if (fast != nullptr) {
            slow = slow->nextUni;
            fast = fast->nextUni;
        }
    }
    // split the list into two parts and break the connection between them
    *leftList = list;
    *rightList = slow->nextUni;
    slow->nextUni = nullptr;
}

UniversityNode* University::mergeList(UniversityNode* leftList, UniversityNode* rightList) {
    // 'result' is the new head of merged list
    UniversityNode* result = nullptr;

    // if the list has been divided to base level (size = 1), directly return
    if (leftList == nullptr) return rightList;
    else if (rightList == nullptr) return leftList;

    // comparing first node in 'leftList' and 'rightList' to decide which node should be adopted
    if (!compareNode(leftList, rightList)) {
        result = leftList;
        result->nextUni = mergeList(leftList->nextUni, rightList);
    }
    else {
        result = rightList;
        result->nextUni = mergeList(leftList, rightList->nextUni);
    }

    return result;
}

void University::mergeSort(UniversityNode** list) {
    UniversityNode* head = *list;
    UniversityNode* leftList, * rightList;

    // nothing to be sorted if the linked list has no node or only one
    if (head == nullptr || head->nextUni == nullptr) return;

    splitList(head, &leftList, &rightList);

    mergeSort(&leftList);
    mergeSort(&rightList);

    *list = mergeList(leftList, rightList);

}

void University::callMergeSort(sortOption option) {
    this->option = option;
    // Start measuring the execution time
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(&(this->universityHead));
    // Stop measuring the execution time
    auto stop = std::chrono::high_resolution_clock::now();
    this->timeTaken = stop - start;
}

// quick sort

UniversityNode* University::getTail(UniversityNode* cur) {
    while (cur->nextUni != nullptr) cur = cur->nextUni;
    return cur;
}

UniversityNode* University::partition(UniversityNode* head, UniversityNode* end, UniversityNode** newHead, UniversityNode** newEnd) {
    // 'head' and 'end' is the original first and last node inside of this list
    // 'newHead' and 'newEnd' is the new first and last node for this list
    UniversityNode* pivot = end, * tail = pivot;
    UniversityNode* cur = head, * prev = nullptr; // prev is the last node which lies in left category

    while (cur != pivot) {
        if (!compareNode(cur, pivot)) {
            // because the order inside of a category (smaller than or larger than pivot) is not important
            // first node that suit the condition will be the 'newHead'
            if ((*newHead) == nullptr) (*newHead) = cur;
            // expanding left category
            prev = cur;
            cur = cur->nextUni;
        }
        else {
            // 'cur' will be moved to right category if it does not meet the above if case
            // if there is node(s) in left category, connect the 'prev' and the node after 'cur'
            if (prev != nullptr) prev->nextUni = cur->nextUni;
            // creating a 'temp' pointer to record the next 'cur' ('prev' might not exist)
            UniversityNode* temp = cur->nextUni;
            // setting 'cur' as the tail node
            cur->nextUni = nullptr;
            tail->nextUni = cur;
            tail = tail->nextUni;
            // go back on the track
            cur = temp;
        }
    }
    // if no 'newHead' is set (all data has been moved to right category)
    // means that the pivot is the 'newHead'
    if ((*newHead) == nullptr) (*newHead) = pivot;
    (*newEnd) = tail;

    return pivot;
}

UniversityNode* University::quickSort(UniversityNode* head, UniversityNode* end) {
    // head can be null if pivot is the last node in the previous categorized linked list
    // head can be end if there's only one node after pivot
    if (head == end || head == nullptr) return head;

    // 'newHead' and 'newEnd' is the new 'head' and 'end' of categorized linked list
    UniversityNode* newHead = nullptr, * newEnd = nullptr;
    UniversityNode* pivot = partition(head, end, &newHead, &newEnd);

    // as it is a singly linked list, better to simply skip the 
    // recursion of left category if there is no node in it
    if (newHead != pivot) {
        // break the connection between left category and pivot to recurse
        UniversityNode* tail = newHead;
        while (tail->nextUni != pivot) tail = tail->nextUni;
        tail->nextUni = nullptr;

        // sort the left category to get 'newHead' and 'newEnd' of it
        newHead = quickSort(newHead, tail);
        // rebuild the connection between left category and the pivot
        tail = getTail(newHead);
        tail->nextUni = pivot;
    }
    // sort the right category of the list
    pivot->nextUni = quickSort(pivot->nextUni, newEnd);

    return newHead;
}

void University::callQuickSort(sortOption option) {
    this->option = option;
    // Start measuring the execution time
    auto start = std::chrono::high_resolution_clock::now();
    this->universityHead = quickSort(this->universityHead, getTail(this->universityHead));
    auto stop = std::chrono::high_resolution_clock::now();
    this->timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
}

void University::addUniHeader(string data[]) {
    for (int i = 0; i < 21; i++) {
        *(this->universityHeader + i) = data[i];
    }
}

UniversityNode* University::searchUniversity(string data) {
    UniversityNode* current = this->universityHead;
    while (current != nullptr) {
        if (current->rank == stoi(data)) {
            break;
        }
        current = current->nextUni;
    }
    return current;
}

//Linear search
void University::LinearSearch(string search, sortOption option){

    // Sorting is required for fair comparison with jump sort
    callMergeSort(option);

    // Start measuring the execution time
    auto start = std::chrono::high_resolution_clock::now();

    UniversityNode* current = this->universityHead;
    int searchCounter = 0;

    // Print the table header
    PrintTableHeader();

    // Iterate the entire linked list and search for the data
    while (current != nullptr) {
        bool displayUniversity = false;
        displayUniversity = compareValues(option, search, current);

        if (displayUniversity){
            searchCounter++;
            DisplayTheUniversity(current);
        }
        current = current->nextUni;
    }


    // Stop measuring the execution time
    auto stop = std::chrono::high_resolution_clock::now();
    this->timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << string(334, '-') << endl;
    cout << "Number of university shown: " << searchCounter << endl << endl;

    if (searchCounter == 0){
        cout << "No university found in this QS ranking 2023" << endl << endl;
    }

    // Print the execution time
    cout << "Time taken by Linear Search Algorithm: ";
    cout << timeTaken.count() << " seconds." << endl;
    cout << endl;
}

//Jump search
void University::JumpSearch(string search, sortOption option) {
    // Sorting is required for Jump Search
    callMergeSort(option);

    // Start measuring the execution time
    auto startTime = std::chrono::high_resolution_clock::now();

    int jumpSize = sqrt(this->uniListSize);
    int searchCounter = 0;

    UniversityNode* current = universityHead;
    UniversityNode* prev = universityHead;

    while(current != nullptr) {
        if (option == uniName || option == uniLocation || option == uniLocationCode){
            bool check;
            switch (option){
                case uniName:
                    cout << ("search: " + search + " current->institutionName: " + current->institutionName) << endl;
                    check = compareFirstCharacter(search, current->institutionName);
                    break;
                case uniLocation:
                    check = compareFirstCharacter(search, current->location);
                    break;
                case uniLocationCode:
                    check = compareFirstCharacter(search, current->locationCode);
                    break;
            }
            if (check){
                break;
            }
        }
        if (compareValues(option, search, current)){
            break;
        }
        prev = current;
        for (int i = 0; current != nullptr && i < jumpSize; i++) {
            current = current->nextUni;
        }
    }

    // Print the table header
    PrintTableHeader();

    // Iterate the entire linked list and search for the data
    while (prev != nullptr) {
        bool displayUniversity = false;
        displayUniversity = compareValues(option, search, prev);
        if (displayUniversity){
            searchCounter++;
            DisplayTheUniversity(prev);
        }
        prev = prev->nextUni;
    }

    // Stop measuring the execution time
    auto stopTime = std::chrono::high_resolution_clock::now();
    this->timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    cout << string(334, '-') << endl;
    cout << "Number of university shown: " << searchCounter << endl << endl;

    // Print the execution time
    cout << "Time taken by Linear Search Algorithm: ";
    cout << timeTaken.count() << " seconds." << endl;
    cout << endl;
}

//int University::RemovePlusSymbol(string otherRank) {
//    // Remove the "+" sign from the ranks
////    otherRank.erase(std::remove(otherRank.begin(), otherRank.end(), '-'), otherRank.end());
//
//    // Convert the rank strings to integers
//    int convertedRank = stoi(otherRank);
//
//    // Perform the comparison
//    return convertedRank;
//}

void University::PrintTableHeader() {
    string width = { 6, 90, 12, 35, 7, 6, 7, 6, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 11 };
    cout << endl << string(334, '-') << endl;
    cout << " | ";
    for (int i = 0; i < 20; i++) {
        if (i >= 1 && i <= 3) {
            cout << left << setw(width[i]);
        }
        else {
            cout << right << setw(width[i]);
        }
        cout << *(universityHeader + i) << " | ";
    }
    cout << *(universityHeader + 20) << " | ";
    cout << endl << string(334, '-') << endl;
}

void University::DisplayTheUniversity(UniversityNode *current) {
    string width = {4, 90, 12, 35, 7, 6, 7, 6, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 8, 7, 11 };
    int checkTwoByte = 0;
    int checkThreeByte = 0;
    University::UniversityNameAlignment(current, checkTwoByte, checkThreeByte);
    cout << " | ";
    cout << right << setw(width[0]) << current->rank << " | ";
    cout << left << setw(width[1] + checkTwoByte + checkThreeByte) << current->institutionName << " | ";
    cout << left << setw(width[2]) << current->locationCode << " | ";
    cout << left << setw(width[3]) << current->location << " | ";

    if (current->arScore == 0) cout << right << setw(width[4]) << "N/A" << " | ";
    else cout << right << setw(width[4]) << current->arScore << " | ";

    if (current->arRank == "0") cout << right << setw(width[4]) << "N/A" << " | ";
    else cout << right << setw(width[5]) << current->arRank << " | ";

    if (current->erScore == 0) cout << right << setw(width[6]) << "N/A" << " | ";
    else cout << right << setw(width[6]) << current->erScore << " | ";

    if (current->erRank == "0") cout << right << setw(width[7]) << "N/A" << " | ";
    else cout << right << setw(width[7]) << current->erRank << " | ";

    if (current->fsrScore == 0) cout << right << setw(width[8]) << "N/A" << " | ";
    else cout << right << setw(width[8]) << current->fsrScore << " | ";

    if (current->fsrRank == "0") cout << right << setw(width[9]) << "N/A" << " | ";
    else cout << right << setw(width[9]) << current->fsrRank << " | ";

    if (current->cpfScore == 0) cout << right << setw(width[10]) << "N/A" << " | ";
    else cout << right << setw(width[10]) << current->cpfScore << " | ";

    if (current->cpfRank == "0") cout << right << setw(width[11]) << "N/A" << " | ";
    else cout << right << setw(width[11]) << current->cpfRank << " | ";

    if (current->ifrScore == 0) cout << right << setw(width[12]) << "N/A" << " | ";
    else cout << right << setw(width[12]) << current->ifrScore << " | ";

    if (current->ifrRank == "0") cout << right << setw(width[13]) << "N/A" << " | ";
    else cout << right << setw(width[13]) << current->ifrRank << " | ";

    if (current->isrScore == 0) cout << right << setw(width[14]) << "N/A" << " | ";
    else  cout << right << setw(width[14]) << current->isrScore << " | ";

    if (current->isrRank == "0") cout << right << setw(width[15]) << "N/A" << " | ";
    else cout << right << setw(width[15]) << current->isrRank << " | ";

    if (current->irnScore == 0) cout << right << setw(width[16]) << "N/A" << " | ";
    else cout << right << setw(width[16]) << current->irnScore << " | ";

    if (current->irnRank == "0") cout << right << setw(width[17]) << "N/A" << " | ";
    else cout << right << setw(width[17]) << current->irnRank << " | ";

    if (current->gerScore == 0) cout << right << setw(width[18]) << "N/A" << " | ";
    else cout << right << setw(width[18]) << current->gerScore << " | ";

    if (current->gerRank == "0") cout << right << setw(width[19]) << "N/A" << " | ";
    else cout << right << setw(width[19]) << current->gerRank << " | ";

    if (current->scoreScaled == -1) cout << right << setw(width[20]) << "N/A" << " |  ";
    else cout << right << setw(width[20]) << current->scoreScaled << " |  ";
    cout << endl;
}

bool University::isSubstring(const std::string& a, const std::string& b) {
    string temp1 = a;
    string temp2 = b;
    toUpper(temp1);
    toUpper(temp2);
    return (temp2.find(temp1) != std::string::npos);
}


void University::UniversityNameAlignment(UniversityNode *current, int &checkTwoByte, int &checkThreeByte) {
    for (int i = 0; i < current->institutionName.length() - 1; i++) {
        if ((unsigned int)(current->institutionName[i]) > 127 &&
            (unsigned int)(current->institutionName[i + 1]) > 127) {
            if ((unsigned int)(current->institutionName[i + 2]) > 127) {
                checkThreeByte = checkThreeByte + 2;
                i = i + 2;
            }
            else {
                checkTwoByte++;
                i = i + 1;
            }
        }
    }
}

void University::PerformSearch(int searchMethod, int searchAttributeSelection, const string &searchKeyword) {
    if (searchMethod == 1) {
        switch (searchAttributeSelection) {
            case 1:
                LinearSearch(searchKeyword, uniRank);
                break;
            case 2:
                LinearSearch(searchKeyword, uniName);
                break;
            case 3:
                LinearSearch(searchKeyword, uniLocation);
                break;
            case 4:
                LinearSearch(searchKeyword, uniLocationCode);
                break;
            case 5:
                LinearSearch(searchKeyword, arScore);
                break;
            case 6:
                LinearSearch(searchKeyword, arRank);
                break;
            case 7:
                LinearSearch(searchKeyword, erScore);
                break;
            case 8:
                LinearSearch(searchKeyword, erRank);
                break;
            case 9:
                LinearSearch(searchKeyword, fsrScore);
                break;
            case 10:
                LinearSearch(searchKeyword, fsrRank);
                break;
            case 11:
                LinearSearch(searchKeyword, cpfScore);
                break;
            case 12:
                LinearSearch(searchKeyword, cpfRank);
                break;
            case 13:
                LinearSearch(searchKeyword, ifrScore);
                break;
            case 14:
                LinearSearch(searchKeyword, ifrRank);
                break;
            case 15:
                LinearSearch(searchKeyword, isrScore);
                break;
            case 16:
                LinearSearch(searchKeyword, isrRank);
                break;
            case 17:
                LinearSearch(searchKeyword, irnScore);
                break;
            case 18:
                LinearSearch(searchKeyword, irnRank);
                break;
            case 19:
                LinearSearch(searchKeyword, gerScore);
                break;
            case 20:
                LinearSearch(searchKeyword, gerRank);
                break;
            case 21:
                LinearSearch(searchKeyword, scoreScaled);
                break;
            default:
                break;
        }
    } else if (searchMethod == 2) {
        switch (searchAttributeSelection) {
            case 1:
                JumpSearch(searchKeyword, uniRank);
                break;
            case 2:
                JumpSearch(searchKeyword, uniName);
                break;
            case 3:
                JumpSearch(searchKeyword, uniLocation);
                break;
            case 4:
                JumpSearch(searchKeyword, uniLocationCode);
                break;
            case 5:
                JumpSearch(searchKeyword, arScore);
                break;
            case 6:
                JumpSearch(searchKeyword, arRank);
                break;
            case 7:
                JumpSearch(searchKeyword, erScore);
                break;
            case 8:
                JumpSearch(searchKeyword, erRank);
                break;
            case 9:
                JumpSearch(searchKeyword, fsrScore);
                break;
            case 10:
                JumpSearch(searchKeyword, fsrRank);
                break;
            case 11:
                JumpSearch(searchKeyword, cpfScore);
                break;
            case 12:
                JumpSearch(searchKeyword, cpfRank);
                break;
            case 13:
                JumpSearch(searchKeyword, ifrScore);
                break;
            case 14:
                JumpSearch(searchKeyword, ifrRank);
                break;
            case 15:
                JumpSearch(searchKeyword, isrScore);
                break;
            case 16:
                JumpSearch(searchKeyword, isrRank);
                break;
            case 17:
                JumpSearch(searchKeyword, irnScore);
                break;
            case 18:
                JumpSearch(searchKeyword, irnRank);
                break;
            case 19:
                JumpSearch(searchKeyword, gerScore);
                break;
            case 20:
                JumpSearch(searchKeyword, gerRank);
                break;
            case 21:
                JumpSearch(searchKeyword, scoreScaled);
                break;
            default:
                break;
        }
    }
}

bool University::compareValues(sortOption attributes, const string &keyword, UniversityNode *current) {
    char a = keyword[0];
    char b;
    switch (attributes) {
        case uniRank:
            return current->rank == stoi(keyword);
        case uniName:
            return isSubstring(keyword, current->institutionName);
        case uniLocation:
            return isSubstring(keyword, current->location);
        case uniLocationCode:
            return isSubstring(keyword, current->locationCode);
        case arScore:
            return current->arScore == stod(keyword);
        case erScore:
            return current->erScore == stod(keyword);
        case fsrScore:
            return current->fsrScore == stod(keyword);
        case cpfScore:
            return current->cpfScore == stod(keyword);
        case ifrScore:
            return current->ifrScore == stod(keyword);
        case isrScore:
            return current->isrScore == stod(keyword);
        case irnScore:
            return current->irnScore == stod(keyword);
        case gerScore:
            return current->gerScore == stod(keyword);
        case scoreScaled:
            return current->scoreScaled == stod(keyword);
        case arRank:
            return stoi(current->arRank) == stoi(keyword);
        case erRank:
            return stoi(current->erRank) == stoi(keyword);
        case fsrRank:
            return stoi(current->fsrRank) == stoi(keyword);
        case cpfRank:
            return stoi(current->cpfRank) == stoi(keyword);
        case ifrRank:
            return stoi(current->ifrRank) == stoi(keyword);
        case isrRank:
            return stoi(current->isrRank) == stoi(keyword);
        case irnRank:
            return stoi(current->irnRank) == stoi(keyword);
        case gerRank:
            return stoi(current->gerRank) == stoi(keyword);
        default:
            return false;
    }
}

int University::getUniListSize() const {
    return uniListSize;
}

UniversityNode* University::searchUniversityWithName(string uniName) {
    UniversityNode *current = this->universityHead;
    while (current != nullptr) {
        if (current->institutionName == uniName) {
            return current;
        }
        current = current->nextUni;
    }
    return nullptr;
}

bool University::compareFirstCharacter(const std::string& str1, const std::string& str2) {
    // Retrieve the first character of str1
    char firstChar1 = str1[0];

    // Retrieve the first character of str2
    char firstChar2 = str2[0];

    // Compare the first characters
    return firstChar2 >= firstChar1;
}