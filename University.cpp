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
            cout << ("testing");
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
            rightValue = stoi(left->arRank);
            leftValue = stoi(right->arRank);
            break;
        case fsrRank:
            rightValue = stoi(left->fsrRank);
            leftValue = stoi(right->fsrRank);
            break;
        case erRank:
            rightValue = stoi(left->erRank);
            leftValue = stoi(right->erRank);
            break;
        case cpfRank:
            rightValue = stoi(left->cpfRank);
            leftValue = stoi(right->cpfRank);
            break;
        case ifrRank:
            rightValue = stoi(left->ifrRank);
            leftValue = stoi(right->ifrRank);
            break;
        case isrRank:
            rightValue = stoi(left->isrRank);
            leftValue = stoi(right->isrRank);
            break;
        case irnRank:
            rightValue = RemovePlusSymbol(left->irnRank);
            leftValue = RemovePlusSymbol(right->irnRank);
            break;
        case gerRank:
            rightValue = RemovePlusSymbol(left->gerRank);
            leftValue = RemovePlusSymbol(right->gerRank);
            break;
        default:
            break;
    }

    // scoreCompare : 0 to take left node, 1 to take right node
    scoreCompare = (leftValue < rightValue) || (leftValue == rightValue && rankCompare == 0);

    if ((this->option == ::uniRank && rankCompare == 1) ||
        (this->option == ::uniName && nameCompare < 0) ||
        (this->option != ::uniRank && this->option != ::uniName && scoreCompare == 0))
        return 0;
    else return 1;
}

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
void University::LinearSearch(string search, sortOption option)
{
    UniversityNode* current = this->universityHead;
    int searchCounter = 0;

    PrintTableHeader();
    callMergeSort(option);

    // Start measuring the execution time
    auto start = std::chrono::high_resolution_clock::now();

    // Iterate the entire linked list and search for the data
    while (current != nullptr) {
        bool displayUniversity = false;

        switch (option) {
            case uniRank:
                displayUniversity = (current->rank == stoi(search));
                break;
            case uniName:
                displayUniversity = isSubstring(search, current->institutionName);
                break;
            case uniLocation:
                displayUniversity = isSubstring(search, current->location);
                break;
            case uniLocationCode:
                displayUniversity = isSubstring(search, current->locationCode);
                break;
            case arScore:
                displayUniversity = (current->arScore == stod(search));
                break;
            case erScore:
                displayUniversity = (current->erScore == stod(search));
                break;
            case fsrScore:
                displayUniversity = (current->fsrScore == stod(search));
                break;
            case cpfScore:
                displayUniversity = (current->cpfScore == stod(search));
                break;
            case ifrScore:
                displayUniversity = (current->ifrScore == stod(search));
                break;
            case isrScore:
                displayUniversity = (current->isrScore == stod(search));
                break;
            case irnScore:
                displayUniversity = (current->irnScore == stod(search));
                break;
            case gerScore:
                displayUniversity = (current->gerScore == stod(search));
                break;
            default:
                break;
        }
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
    // Sort the linked list by institution name
    callMergeSort(option);

    // Start measuring the execution time
    auto startTime = std::chrono::high_resolution_clock::now();

    int lengthOfLinkedList = 0;
    UniversityNode* current = universityHead;

    while (current != nullptr) {
        lengthOfLinkedList++;
        current = current->nextUni;
    }

    int jump = sqrt(lengthOfLinkedList);

    UniversityNode* start = universityHead;
    UniversityNode* end = universityHead;

    if (option == uniName) {
        while (end != nullptr && end->institutionName < search) {
            start = end;
            for (int i = 0; i < jump && end->nextUni != nullptr; i++) {
                end = end->nextUni;
            }
        }
    }
    else if (option == arScore) {
        while (end != nullptr && end->arScore < stod(search)) {
            start = end;
            for (int i = 0; i < jump && end->nextUni != nullptr; i++) {
                end = end->nextUni;
            }
        }
    }

    UniversityNode* match = nullptr;
    if (option == uniName) {
        while (start != nullptr && start != end->nextUni) {
            if (start->institutionName == search) {
                match = start;
                break;
            }
            start = start->nextUni;
        }
    }
    else if (option == arScore) {
        while (start != nullptr && start != end->nextUni) {
            if (start->arScore == stod(search)) {
                match = start;
                break;
            }
            start = start->nextUni;
        }
    }

    if (match == nullptr) 
        cout << "No university found in this QS ranking 2023" << endl << endl;
    else {
        // Traverse the linked list and display all the matching nodes
        UniversityNode* temp = match;
        if (option == uniName) {
            while (temp != nullptr && temp != match->nextUni) {
                if (temp->institutionName == search) {
//                    DisplaySearchResult(temp, search); // Updated parameter
                }
                temp = temp->nextUni;
            }
        }
        else if (option == arScore) {
            while (temp != nullptr && temp != match->nextUni) {
                if (temp->arScore == stod(search)) {
//                    DisplaySearchResult1(temp, search); // Updated parameter
                }
                temp = temp->nextUni;
            }
        }
    }

    // Stop measuring the execution time
    auto stopTime = std::chrono::high_resolution_clock::now();
    this->timeTaken = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

//    cout << string(334, '-') << endl;
//    cout << "Number of university shown: " << searchCounter << endl << endl;
//
//    if (searchCounter == 0){
//        cout << "No university found in this QS ranking 2023" << endl << endl;
//    }

    // Print the execution time
    cout << "Time taken by Linear Search Algorithm: ";
    cout << timeTaken.count() << " seconds." << endl;
    cout << endl;
}

int University::RemovePlusSymbol(string otherRank) {
    // Remove the "+" sign from the ranks
//    otherRank.erase(std::remove(otherRank.begin(), otherRank.end(), '-'), otherRank.end());

    // Convert the rank strings to integers
    int convertedRank = stoi(otherRank);

    // Perform the comparison
    return convertedRank;
}

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
    int checkTwoByte = 0;
    int checkThreeByte = 0;
    University::UniversityNameAlignment(current, checkTwoByte, checkThreeByte);
    cout << " | ";
    cout << right << setw(4) << current->rank << " | ";
    cout << left << setw(90 + checkTwoByte + checkThreeByte) << current->institutionName << " | ";
    cout << left << setw(12) << current->locationCode << " | ";
    cout << left << setw(35) << current->location << " | ";
    cout << right << setw(7) << current->arScore << " | ";
    cout << right << setw(6) << current->arRank << " | ";
    cout << right << setw(7) << current->erScore << " | ";
    cout << right << setw(6) << current->erRank << " | ";
    cout << right << setw(8) << current->fsrScore << " | ";
    cout << right << setw(7) << current->fsrRank << " | ";
    cout << right << setw(8) << current->cpfScore << " | ";
    cout << right << setw(7) << current->cpfRank << " | ";
    cout << right << setw(8) << current->ifrScore << " | ";
    cout << right << setw(7) << current->ifrRank << " | ";
    cout << right << setw(8) << current->isrScore << " | ";
    cout << right << setw(7) << current->isrRank << " | ";
    cout << right << setw(8) << current->irnScore << " | ";
    cout << right << setw(7) << current->irnRank << " | ";
    cout << right << setw(8) << current->gerScore << " | ";
    cout << right << setw(7) << current->gerRank << " | ";
    cout << right << setw(11) << current->scoreScaled << " |  ";
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