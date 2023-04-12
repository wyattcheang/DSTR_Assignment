//
// Created by Wyatt Cheang on 27/03/2023.
//

#include "Guest.h"
#include <iostream>

using namespace std;


Guest::Guest(University uni) {
    int option;
    bool loop = true;
    cout << "Welcome!" << endl;
    while (loop) {
        cout << "Enter down below option to perform the coordinate execution." << endl;
        cout << "(1) Show all the universities' information." << endl;
        cout << "(2) Login/Register." << endl;
        cout << "(3) Admin Login." << endl;
        cout << "(4) Exit." << endl;
        cout << endl << "Your option: " << endl;
        cin >> option;
        if (cin.fail() && option != 1 && option != 2 && option != 3) {
            cout << "Error Input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            switch (option) {
                case 1:
                    uni.callMergeSort(uniName);
                    uni.DisplayData();
                    int option2;
                    cout << "(1) Continue\n"
                            "(2) Exit\n"
                            "Enter: ";
                    cin >> option2;
                    switch (option2) {
                        case 1:
                            cout << endl << endl;
                            continue;
                        case 2:
                            ::exit(0);
                        default:
                            ::exit(0);
                    }
                case 2:
                    loop = false;
                    break;
                case 3:
                    cout << "Thanks!";
                    break;
            }
        }
    }
}
