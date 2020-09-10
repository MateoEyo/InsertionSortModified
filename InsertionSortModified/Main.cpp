/*
Insertion Sort modified to use binary search instead of linear search when inserting elements
*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
using namespace std;

int getTotal();
vector<int> insertionSort(vector<int> toSort);
vector<int> binarySearch(vector<int> toSort);

// Begin the program
int main() {

    bool keepGoing = false;
    int total = 0;
    vector<int> preSortArray;
    vector<int> sortedInsertion;
    vector<int> sortedBinary;

    cout << "*** Welcome to Insertion Sort! This insertion sort will look at integers between 1 and 1,000. ***" << endl;

    // Run until the user wants to stop
    do {
        total = getTotal();
        if (total == -1) {
            exit(EXIT_FAILURE);
        }
        else {
            preSortArray.resize(total);
            sortedInsertion.resize(total);
            for (int i = 0; i < total; i++) {
                srand(total);
                preSortArray[i] = (rand() % 1000) + 1;
            }
        }
        
        sortedInsertion = insertionSort(preSortArray);
        sortedBinary = binarySearch(preSortArray);
        for (int i = 0; i < preSortArray.size(); i++) {
            cout << preSortArray[i] << endl;
        }
        for (int i = 0; i < sortedBinary.size(); i++) {
            cout << sortedBinary[i] << endl;
        }

        sortedInsertion.clear();
        preSortArray.clear();

        cout << "Type 1 to continue sorting with a new array or 0 to stop. ";
        cin >> keepGoing;
    } while (keepGoing);

    // End of program
    return 0;
}

// Gets and validates input from user for total number of preSortArray
int getTotal() {

    string input;
    int total;
    bool checkInput;

    // Ask the user how many values they wish to sort
    cout << "\nHow many integers do you want to sort? ";
    cin >> input;

    checkInput = input.find_first_not_of("0123456789") == string::npos;

    if (checkInput) {
        total = stoi(input);
        total = abs(total);
        return total;
    }
    else {
        cout << "You've typed something other than an integer, the program will end now. Goodbye!";
        return -1;
    }
}

// Utilize insertion sort to sort given array
vector<int> insertionSort(vector<int> toSort) {

    int temp;
    int check;

    for (size_t i = 1; i < toSort.size(); i++) {
        temp = toSort[i];
        check = i - 1;

        while ((check >= 0) && toSort[check] > temp) {
            toSort[check + 1] = toSort[check];
            check = check - 1;
        }
        toSort[check + 1] = temp;
    }

    return toSort;
}

// Insertion sort using binary search instead of a linear search
vector<int> binarySearch(vector<int> toSort) {

    int temp;

    for (size_t i = 1; i < toSort.size(); i++) {

        int lower = 0;
        int upper = i - 1; 
        int midpoint = 0;

        while (lower < i) {

            midpoint = floor(lower + (upper - lower) / 2);

            if (toSort[midpoint] < toSort[i]) { lower = midpoint + 1; }
            if (toSort[midpoint] > toSort[i]) { upper = midpoint + 1; }
            if (toSort[midpoint] == toSort[i]) { break; }
        }

        temp = toSort[lower];
        toSort[lower] = toSort[i];
        toSort[i] = temp;
    }

    return toSort;
}