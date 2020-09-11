/*
Insertion Sort modified to use binary search instead of linear search when inserting elements
*/

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>
using namespace std;

int getTotal();
vector<int> insertionSort(vector<int> toSort);
vector<int> insertionSortBinary(vector<int> toSort);
int binarySearch(vector<int> toSort, int value, int lower, int higher);

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
            srand(total);
            preSortArray.resize(total);
            sortedInsertion.resize(total);
            for (int i = 0; i < total; i++) {
                preSortArray[i] = (rand() % 1000) + 1;
            }
        }
        
        // Run insertion sort and calculate time
        auto beginInsertion = chrono::high_resolution_clock::now();
        sortedInsertion = insertionSort(preSortArray);
        auto endInsertion = chrono::high_resolution_clock::now();
        auto insertionElapsed = chrono::duration_cast<chrono::nanoseconds>(endInsertion - beginInsertion);

        // Run insertion sort with binary and calculate time
        auto beginBinary = chrono::high_resolution_clock::now();
        sortedBinary = insertionSortBinary(preSortArray);
        auto endBinary = chrono::high_resolution_clock::now();
        auto binaryElapsed = chrono::duration_cast<chrono::nanoseconds>(endBinary - beginBinary);

        // Print out arrays to text files for manual validation
        ofstream preSortFile;
        preSortFile.open(to_string(total) + "_preSort_total.txt");
        for (int i = 0; i < total; i++) {
            preSortFile << preSortArray[i] << endl;
        }
        preSortFile.close();

        ofstream insertionFile;
        insertionFile.open(to_string(total) + "_insertion_total.txt");
        for (int i = 0; i < total; i++) {
            insertionFile << sortedInsertion[i] << endl;
        }
        insertionFile.close();

        ofstream binaryFile;
        binaryFile.open(to_string(total) + "_binary_total.txt");
        for (int i = 0; i < total; i++) {
            binaryFile << sortedBinary[i] << endl;
        }
        binaryFile.close();

        // Print out execution time for both sorts
        cout << "Execution time for insertion sort is " + to_string(insertionElapsed.count()) << endl;
        cout << "Execution time for insertion sort with binary is " + to_string(binaryElapsed.count()) << endl;

        // Clear out vectors to avoid possible memory issues
        sortedInsertion.clear();
        sortedBinary.clear();
        preSortArray.clear();

        cout << "\nType 1 to continue sorting with a new array or 0 to stop. ";
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

    int value;
    int check;

    for (size_t i = 1; i < toSort.size(); i++) {
        value = toSort[i];
        check = i - 1;

        while ((check >= 0) && toSort[check] > value) {
            toSort[check + 1] = toSort[check];
            check--;
        }
        toSort[check + 1] = value;
    }

    return toSort;
}

// Insertion sort using binary search instead of a linear search
vector<int> insertionSortBinary(vector<int> toSort) {

    int value;
    int check;
    int location;

    for (size_t i = 1; i < toSort.size(); i++) {
        value = toSort[i];
        check = i - 1;
        
        // Call a binary search that will run recursively to find the location to insert 'value'
        location = binarySearch(toSort, value, 0, check);

        // Shift all elements after the location found in binary search to allow the value to be placed
        while (check >= location) {
            toSort[check + 1] = toSort[check];
            check--;
        }
        toSort[check + 1] = value;
    }

    return toSort;
}

// Binary search function that finds the position where the 'value' should be inserted recursively
int binarySearch(vector<int> toSort, int value, int lower, int higher) {

    int midpoint = 0;

    while (lower <= higher) {
        if (higher <= lower) {
            // Working on this project helped me find out about the "ternary operator" that is in use below
            return (value > toSort[lower]) ? (lower + 1) : lower;
        }

        midpoint = ceil((lower + higher) / 2);

        if (value > toSort[midpoint]) {
            lower = midpoint + 1;
        }
        else {
            higher = midpoint - 1;
        }
    }
}