#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));
    list<Goat> trip;
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    //while loop that continuously loops as long as the user does not input the sentinel value 4, which breaks the loop
    while(true){
        //calls the main_menu() function, which returns the user's choice of action based on the displayed menu
        int choice = main_menu();

        //if the choice does not fall within our desired bounds, then we will return this message
        if (choice < 1 || choice > 4)
        cout << "Invalid input";

        //if choice is equal to 1, we will add a goat to the trip, with a randomized name and color
        if(choice == 1)
            add_goat(trip, names, colors);
        //if choice is equal to 2, allows the user to select a goat to remove from the trip
        if(choice == 2)
            delete_goat(trip);
        //if choice is equal to 3, displays the current list of goats on the trip
        if(choice == 3)
            display_trip(trip);
        //if choice is equal to 4, breaks the loop and ends the user selection
        if(choice == 4)
            break;

            cout << endl;
    }

    return 0;
}

//int function that displays the menu of options to the user and receives a user input for the desired action
int main_menu() {
    int c;
    
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "Choice -->";
    cin >> c;
        
    return c;
}

//int function that accepts and inputted user argument to decide the designated goat on the trip
int select_goat(list<Goat> trip) {
    int c;
    cout << "Enter the number of the goat you wish to choose: ";
    cin >> c;

    return c;
}

//function that displays the goats on the current trip
void display_trip(list<Goat> trip){
    cout << endl;
    //if there are no goats on the trip, then the program will display this message 
    if (trip.empty()) {
        cout << "No goats on this trip.\n";
        return;
    }
    //if there are goats on the trip, the program will continuously display the values stored within the goat class object until we have traversed the entire list
    cout << "Goats On Current Trip:\n";
    int i = 1;
    for (auto &goat : trip){
        cout << "[" << i++ << "] ";
        cout << goat.get_name() << " (" << goat.get_age() << ", " << goat.get_color() << ")";
        cout << endl;
    }
}

//function that adds a goat with a randomized name and color from our external text files to the trip and adds it to the list
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % MAX_AGE + 1;
    trip.push_back(Goat(name, age, color));
}

//function that allows the user to choose a goat from the current trip to remove
void delete_goat(list<Goat> &trip) {
    //if the trip is currently empty, then we will display this message
    if (trip.empty()) {
        cout << "No goats on this trip.\n";
        return;
    }

    //displays the current trip and calls the select_goat function so that the user can select the position of the goat
    display_trip(trip);
    int c = select_goat(trip);

    //if the selection does not exist within our bounds, display this message
    if (c < 1 || c > trip.size()) {
        cout << "Invalid goat selection.\n";
        return;
    }
    //traverses the list until the desired location is met and then deletes the Goat object at that location
    else if (c >= 1 && c <= trip.size()){
        auto it = trip.begin();
        advance(it, c-1);
        trip.erase(it);
    }
}

