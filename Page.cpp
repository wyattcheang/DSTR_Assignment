//
// Created by Wyatt Cheang on 27/03/2023.
//

#include "Page.h"
#include "Admin.h"
#include "User.h"
#include "University.h"
#include "Feedback.h"
#include "Favourite.h"
#include "DataIO.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <limits> // Added for numeric_limits

using namespace std;

BasePage::BasePage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : university(university), user(user), admin(admin), feedback(feedback), favourite(favourite) {
}



StartPage::StartPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : BasePage(university, user, admin, feedback, favourite) {
}

UserPage::UserPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : BasePage(university, user, admin, feedback, favourite) {
}

AdminPage::AdminPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : BasePage(university, user, admin, feedback, favourite) {
}

FeedbackPage::FeedbackPage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : BasePage(university, user, admin, feedback, favourite) {
}

FavouritePage::FavouritePage(University* university, User* user, Admin* admin, Feedback* feedback, Favourite* favourite)
        : BasePage(university, user, admin, feedback, favourite) {
}


void StartPage::DisplayStartPage(UserPage* userPage, AdminPage* adminPage, FeedbackPage* feedbackPage, FavouritePage* favouritePage) {
    int startMenuOption, sortSelection, searchSelection;
    string searchKeyword;
    bool loop = true;
    cout << string(100, '*') << endl;
    DataIO::printStringCentered("Welcome to University Finder!");
    cout << string(100, '*') << endl;
    while (loop) {
        cout << string(100, '=') << endl;
        DataIO::printStringCentered("Guest Page (Login/Register for membership to unlock more features!)");
        cout << string(100, '=') << endl;
        cout << "Enter down below option to perform the coordinate execution." << endl;
        cout << "(1) Show all the universities' information." << endl;
        cout << "(2) Sort university information in ascending order by university name." << endl;
        cout << "(3) Search individual university details." << endl;
        cout << "(4) Register as Customer." << endl;
        cout << "(5) Customer Login." << endl;
        cout << "(6) Admin Login." << endl;
        cout << "(7) Exit." << endl;
        cout << endl << "Your option: ";
        cin >> startMenuOption;
        if (cin.fail() || startMenuOption < 1 || startMenuOption > 7) {
            cout << "Error Input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            switch (startMenuOption) {
                case 1:
                    university->DisplayData();
                    break;
                case 2:
                    while (true) {
                        DataIO::selectSortMethodMenu();
                        cin >> sortSelection;
                        if (cin.fail() || sortSelection < 1 || sortSelection > 2) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                    switch (sortSelection) {
                        case 1:
                            university->callMergeSort(uniName);
                            break;
                        case 2:
                            university->callQuickSort(uniName);
                            break;
                        default:
                            break;
                    }
                    university->DisplayData();
                    if (sortSelection == 1) {
                        cout << "Time taken by Merge Sort Algorithm: ";
                    } else if (sortSelection == 2) {
                        cout << "Time taken by Quick Sort Algorithm: ";
                    }
                    cout << university->timeTaken.count() << " seconds." << endl;
                    cout << endl;
                    break;
                case 3:
                    while (true) {
                        cout << "Enter the keyword to search: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        getline(cin, searchKeyword);
                        if (cin.fail()) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                    while (true) {
                        DataIO::selectSearchMethodMenu();
                        cin >> searchSelection;
                        if (cin.fail() || searchSelection < 1 || searchSelection > 2) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                    university->PerformSearch(searchSelection, 2, searchKeyword);
                    break;
                case 4:
                    user->userRegister();
                    break;
                case 5:
                    user->userLogin();
                    userPage->DisplayUserPage(feedbackPage, favouritePage);
                    break;
                case 6:
                    admin->adminLogin();
                    adminPage->DisplayAdminPage(feedbackPage, favouritePage);
                    break;
                case 7:
                    cout << "Thank you for using our system!" << endl;
                    loop = false;
                    break;
                default:
                    break;
            }
        }
    }
}

void UserPage::DisplayUserPage(FeedbackPage* feedbackPage, FavouritePage* favouritePage) {
    bool userPageLoop = true;
    int searchAttributeSelection, searchSelection;
    string searchKeyword;
    while (userPageLoop) {
        cout << string(100, '=') << endl;
        DataIO::printStringCentered("User Page | Welcome back, " + user->getLoginUser()->username);
        cout << string(100, '=') << endl;
        int option;
        University uni;
        Favourite fav;
        cout << "Enter down below option to perform the coordinate execution." << endl;
        cout << "(1) Sort University." << endl;
        cout << "(2) Search University." << endl;
        cout << "(3) Show all favourite university." << endl;
        cout << "(4) Send feedback to MoHE for further information about the University." << endl;
        cout << "(5) Read feedback reply from MoHE Based on latest date." << endl;
        cout << "(6) Logout" << endl;
        cout << endl << "Your option: ";
        cin >> option;
        if (cin.fail() || option < 1 || option > 7) {
            cout << "Error Input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            switch (option) {
                case 1: {
                    int sortAttributeSelection, sortSelection;
                    while (true) {
                        cout << "Sort university based on: " << endl;
                        DataIO::printSelectUniversityAttributeMenu();
                        cin >> sortAttributeSelection;
                        if (cin.fail() || sortAttributeSelection < 1 || sortAttributeSelection > 21) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                    while (true) {
                        DataIO::selectSortMethodMenu();
                        cin >> sortSelection;
                        if (cin.fail() || sortSelection < 1 || sortSelection > 2) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }
                    switch (sortAttributeSelection) {
                        case 1:
                            if (sortSelection == 1) uni.callMergeSort(uniRank);
                            else if (sortSelection == 2) uni.callQuickSort(uniRank);
                            break;
                        case 2:
                            if (sortSelection == 1) uni.callMergeSort(uniName);
                            else if (sortSelection == 2) uni.callQuickSort(uniName);
                            break;
                        case 3:
                            if (sortSelection == 1) uni.callMergeSort(uniLocation);
                            else if (sortSelection == 2) uni.callQuickSort(uniLocation);
                            break;
                        case 4:
                            if (sortSelection == 1) uni.callMergeSort(uniLocationCode);
                            else if (sortSelection == 2) uni.callQuickSort(uniLocationCode);
                            break;
                        case 5:
                            if (sortSelection == 1) uni.callMergeSort(arScore);
                            else if (sortSelection == 2) uni.callQuickSort(arScore);
                            break;
                        case 6:
                            if (sortSelection == 1) uni.callMergeSort(arRank);
                            else if (sortSelection == 2) uni.callQuickSort(arRank);
                            break;
                        case 7:
                            if (sortSelection == 1) uni.callMergeSort(erScore);
                            else if (sortSelection == 2) uni.callQuickSort(erScore);
                            break;
                        case 8:
                            if (sortSelection == 1) uni.callMergeSort(erRank);
                            else if (sortSelection == 2) uni.callQuickSort(erRank);
                            break;
                        case 9:
                            if (sortSelection == 1) uni.callMergeSort(fsrScore);
                            else if (sortSelection == 2) uni.callQuickSort(fsrScore);
                            break;
                        case 10:
                            if (sortSelection == 1) uni.callMergeSort(fsrRank);
                            else if (sortSelection == 2) uni.callQuickSort(fsrRank);
                            break;
                        case 11:
                            if (sortSelection == 1) uni.callMergeSort(cpfScore);
                            else if (sortSelection == 2) uni.callQuickSort(cpfScore);
                            break;
                        case 12:
                            if (sortSelection == 1) uni.callMergeSort(cpfRank);
                            else if (sortSelection == 2) uni.callQuickSort(cpfRank);
                            break;
                        case 13:
                            if (sortSelection == 1) uni.callMergeSort(ifrScore);
                            else if (sortSelection == 2) uni.callQuickSort(ifrScore);
                            break;
                        case 14:
                            if (sortSelection == 1) uni.callMergeSort(ifrRank);
                            else if (sortSelection == 2) uni.callQuickSort(ifrRank);
                            break;
                        case 15:
                            if (sortSelection == 1) uni.callMergeSort(isrScore);
                            else if (sortSelection == 2) uni.callQuickSort(isrScore);
                            break;
                        case 16:
                            if (sortSelection == 1) uni.callMergeSort(isrRank);
                            else if (sortSelection == 2) uni.callQuickSort(isrRank);
                            break;
                        case 17:
                            if (sortSelection == 1) uni.callMergeSort(irnScore);
                            else if (sortSelection == 2) uni.callQuickSort(irnScore);
                            break;
                        case 18:
                            if (sortSelection == 1) uni.callMergeSort(irnRank);
                            else if (sortSelection == 2) uni.callQuickSort(irnRank);
                            break;
                        case 19:
                            if (sortSelection == 1) uni.callMergeSort(gerScore);
                            else if (sortSelection == 2) uni.callQuickSort(gerScore);
                            break;
                        case 20:
                            if (sortSelection == 1) uni.callMergeSort(gerRank);
                            else if (sortSelection == 2) uni.callQuickSort(gerRank);
                            break;
                        case 21:
                            if (sortSelection == 1) uni.callMergeSort(scoreScaled);
                            else if (sortSelection == 2) uni.callQuickSort(scoreScaled);
                            break;
                        default:
                            break;
                    }
                    uni.DisplayData();
                    // Print the execution time
                    if (sortSelection == 1) {
                        cout << "Time taken by Merge Sort Algorithm: ";
                    } else if (sortSelection == 2) {
                        cout << "Time taken by Quick Sort Algorithm: ";
                    }
                    cout << uni.timeTaken.count() << " microseconds." << endl;
                    cout << endl;
                    break;
                }
                case 2:
                    while (true) {
                        DataIO::printSelectUniversityAttributeMenu();
                        cin >> searchAttributeSelection;
                        if (cin.fail() || searchAttributeSelection < 1 || searchAttributeSelection > 21) {
                            cout << "Error Input!" << endl << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        } else {
                            break;
                        }
                    }
                    while (true) {
                        cout << "Enter the keyword to search: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        getline(cin, searchKeyword);
                        if (cin.fail()) {
                            cout << "Error Input!" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        } else {
                            break;
                        }
                    }

                    if (searchAttributeSelection == 1) {
                        try {
                            int a = stoi(searchKeyword);
                        } catch (std::invalid_argument const &e) {
                            cout << "Error Input!" << endl << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                    } else if (searchAttributeSelection == 5 || searchAttributeSelection == 6 || searchAttributeSelection == 7 ||
                               searchAttributeSelection == 8 || searchAttributeSelection == 9 || searchAttributeSelection == 10 ||
                               searchAttributeSelection == 11 || searchAttributeSelection == 12 || searchAttributeSelection == 13 ||
                               searchAttributeSelection == 14 || searchAttributeSelection == 15 || searchAttributeSelection == 16 ||
                               searchAttributeSelection == 17 || searchAttributeSelection == 18 || searchAttributeSelection == 19 ||
                               searchAttributeSelection == 20 || searchAttributeSelection == 21) {
                        try {
                            double a = stod(searchKeyword);
                        } catch (std::invalid_argument const &e) {
                            cout << "Error Input!" << endl << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                    }
                    while (true) {
                        DataIO::selectSearchMethodMenu();
                        cin >> searchSelection;
                        if (cin.fail() || searchSelection < 1 || searchSelection > 2) {
                            cout << "Error Input!" << endl << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        } else {
                            break;
                        }
                    }
                    university->PerformSearch(searchSelection, searchAttributeSelection, searchKeyword);
                    break;
                case 3:
                    cout << "Save" << endl;
                    break;
                case 4:
                    feedbackPage->UserAddFeedbackPage();
                    break;
                case 5:
                    feedbackPage->UserReviewFeedbackPage();
                    break;
                case 6:
                    user->userLogout();
                    userPageLoop = false;
                    break;
                default:
                    break;
            }
        }
    }
}

void AdminPage::DisplayAdminPage(FeedbackPage *feedbackPage, FavouritePage *favouritePage) {
    bool adminPageLoop = true;
    while (adminPageLoop) {
        cout << string(100, '=') << endl;
        DataIO::printStringCentered("Admin Page | Welcome back, " + admin->getLoginAdmin()->username);
        cout << string(100, '=') << endl;
        int option;
        University uni;
        cout << "Enter down below option to perform the coordinate execution." << endl;
        cout << "(1) Display all registered users' details." << endl;
        cout << "(2) Modify user's details." << endl;
        cout << "(3) Delete user's account based on inactivity status." << endl;
        cout << "(4) Display registered users' feedback according to latest date." << endl;
        cout << "(5) Reply to user's feedback." << endl;
        cout << "(6) Display top 10 universities most preferred by parents in Malaysia." << endl;
        cout << "(7) Logout." << endl;
        cout << endl << "Your option: ";
        cin >> option;
        if (cin.fail() || option < 1 || option > 7) {
            cout << "Error Input!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            switch (option) {
                case 1: {
                    user->displayUser();
                    break;
                }
                case 2: {
                    int modifyOption;
                    while (true) {
                        cout << "Choose one to modify: " << endl;
                        cout << "(1) Username" << endl;
                        cout << "(2) Password" << endl;
                        cin >> modifyOption;
                        if (cin.fail() || modifyOption < 1 || modifyOption > 2) {
                            cout << "Error Input!" << endl << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        } else {
                            break;
                        }
                    }
                    switch (modifyOption) {
                        case 1: {
                            admin->modifyUsername();
                            break;
                        }
                        case 2: {
                            admin->modifyUserPassword();
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                }
                break;
                case 3: {
                    cout << "Delete" << endl;
                    user->deleteInactiveUsers();
                    break;
                }
                case 4: {
                    cout << "HI" << endl;
                    break;
                }
                case 5: {
                    cout << "HI" << endl;
                    break;
                }
                case 6: {
                    cout << "HI" << endl;
                    break;
                }
                case 7: {
                    admin->adminLogout();
                    adminPageLoop = false;
                    cout << "Successfully Logout" << endl;
                }
                default: {
                    break;
                }
            }
        }
    }
}

void FeedbackPage::UserAddFeedbackPage() {
    int selectUniversity;
    cout << string(100, '-') << endl;
    DataIO::printStringCentered("User Feedback Page");
    cout << string(100, '-') << endl;
    while (true) {
        while (true) {
            cout << "Enter the university rank: ";
            cin >> selectUniversity;
            if (cin.fail() || selectUniversity < 1 || selectUniversity > university->getUniListSize()) {
                cout << "Error Input!" << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
                break;
            }
        }
        string feedback;
        int confirmSelection;
        UniversityNode *selectedUniversity = university->searchUniversity(to_string(selectUniversity));
        cout << setw(50) << setfill('=') << "" << endl;
        cout << "University Rank: " << selectedUniversity->rank << endl;
        cout << "University Name: " << selectedUniversity->institutionName << endl;
        cout << setw(50) << setfill('=') << "" << endl;
        cout << "Feedbacks: " << endl;
        cin.ignore();
        getline(cin, feedback);
        while (true) {
            cout << "Do you confirm to add this feedback?" << endl;
            cout << "(1) Yes" << endl;
            cout << "(2) No" << endl;
            cout << "Enter your option:";
            cin >> confirmSelection;
            if (cin.fail() || confirmSelection < 1 || confirmSelection > 2) {
                cout << "Error Input!" << endl << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else {
                break;
            }
        }
        if (confirmSelection == 1) {
            this->feedback->appendFeedbackNode(feedback, user->getLoginUser(), selectedUniversity);
            cout << "Successfully added feedback!" << endl;
            break;
        } else {
            cout << "Execution was cancelled!" << endl;
            break;
        }
    }
}

void FeedbackPage::UserReviewFeedbackPage() {
    FeedbackNode* currentFeedback =feedback->getUserNextFeedback(user->getLoginUser(), nullptr);
    if (currentFeedback != nullptr){
        feedback->printFeedback(currentFeedback);
    }
}


