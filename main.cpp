#include <iostream>
#include "University.h"
#include "DataIO.h"
#include "Guest.h"
#include "User.h"

using namespace std;



int main() {
    User user;
    University uniClass;
    Admin admin;

    Guest guest(uniClass);
    uniClass.DisplayData();
    user.userLogin();













//    auto start = chrono::high_resolution_clock::now();
//    University uniClass;
//    auto end = chrono::high_resolution_clock ::now();
//    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
//    cout << "Time used for read file\t\t\t: " << duration.count() << endl;
//
//
//    start = chrono::high_resolution_clock::now();
//    uniClass.callMergeSort(uniName);
//    end = chrono::high_resolution_clock ::now();
//    duration = chrono::duration_cast<chrono::microseconds>(end - start);
//    cout << "Time used for merge sort file\t: " << duration.count() << endl;

}
