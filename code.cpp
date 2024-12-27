#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>  

using namespace std;

// Some definition due to language limitations of 2D arrays
const int MAX_ROWS = 100;  
const int MAX_COLUMNS = 100;

// Vehicle structure
struct Vehicle {
    string number_plate;
    string make;  // Make is the company 
    string model; 
    string color;
    float charges;
};

Vehicle arr[MAX_ROWS][MAX_COLUMNS];

// Pre - defined charges, 3$ for LTV,  5$ for HTV and 1.5 $ for smaller vehicles
float charges[3] = {3, 5, 1.5};

// Pre - defined attributes for the code to be used later in most functions
int rows = 0, columns = 0, total = 0, occupied = 0;

// Function pre-definitions
void display_menu();
void add_vehicle(int row, int column);
void remove_vehicle(int row, int column);
void display_parking();
void show_status();
void show_vehicle_details(int row, int column);
void reset_parking_lot();
void add_history(string data);
void write_log(string data);

int main()
{
    cout << "Enter rows of the parking: ";
    cin >> rows;
    cout << "Enter columns of the parking: ";
    cin >> columns;
    total = rows * columns;

    display_parking();

    display_menu();

    return 0;
}

void display_parking()
{
    // Function to display the parking
    cout << "    ";
    for (int j = 0; j < columns; j++)
    {
        cout << "C" << j + 1 << "  ";  
    }
    cout << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "R" << i + 1 << " ";  

        for (int j = 0; j < columns; j++)
        {
            if (arr[i][j].number_plate == "")
            {
                cout << "🟩  "; // represents unoccupied space
            }
            else
            {
                cout << " 🚗  ";  // represents occupied space
            }
        }
        cout << endl;
    }
}

void display_menu()
{
    int option, row, column;
    while (true)
    {
        // Differente possible functions 

        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Add a vehicle." << endl;
        cout << "2. Remove a vehicle." << endl;
        cout << "3. Show parking lot status." << endl;
        cout << "4. Show status of a specific vehicle." << endl;
        cout << "5. Reset parking lot." << endl;
        cout << "6. Exit program." << endl;

        cout << "Enter your choice (1-6): ";
        cin >> option;

        if (option == 6)
        {
            cout << "Exiting program..." << endl;
            exit(0);
        }

        else if (option == 3)
        {
            show_status();
            cout << "Press any key to continue..." << endl;
            getch();
            display_menu();
        }
        else if (option == 5)
        {
            reset_parking_lot();
            display_parking();
            cout << "Press any key to continue..." << endl;
            getch(); 
            continue;
        }

        cout << "Enter the row (1 to " << rows << "): ";
        cin >> row;
        cout << "Enter the column (1 to " << columns << "): ";
        cin >> column;

        row -= 1;
        column -= 1;

        if (row < 0 || row >= rows || column < 0 || column >= columns)
        {
            cout << "Invalid row or column. Please try again." << endl;
            continue;
        }

        switch (option)
        {
        case 1:
            add_vehicle(row, column);
            break;
        
        case 2:
            remove_vehicle(row, column);
            break;
        
        case 4:
            show_vehicle_details(row, column);
            break;

        default:
            cout << "Invalid Input. Please choose between 1 and 6." << endl;
        }

        display_parking(); 
        cout << "Press any key to continue..." << endl;
        getch(); 
    }
}

void add_vehicle(int row, int column)
{
    if (arr[row][column].number_plate == "")
    {
        int type, days;
        cout << "Enter vehicle details:" << endl;
        cout << "Number plate: ";
        cin >> arr[row][column].number_plate;
        cout << "Make: ";
        cin >> arr[row][column].make;
        cout << "Model: ";
        cin >> arr[row][column].model;
        cout << "Color: ";
        cin >> arr[row][column].color;
        cout << "Enter vehicle type (1-3) (1- LTV | 2- HTV | 3- Others): ";
        cin >> type;
        cout << "Enter days of durtaion: ";
        cin >> days;
        while(days < 0){
            cout << "Days must be more than 1!";
            cin >> days;
        }

        arr[row][column].charges = charges[type-1]*days; 
        cout << "Vehicle added to spot R" << row + 1 << "C" << column + 1 << "." << endl;
        occupied += 1;
        add_history(("Vehicle: " + arr[row][column].number_plate + " Make & Model: " + arr[row][column].make + " " + arr[row][column].model + " Color: " + arr[row][column].color + "\n"));
        write_log(("Vehicle " + arr[row][column].number_plate + " has entered the parking!"));

    }
    else
    {
        cout << "This spot is already occupied!" << endl;
    }
}

void remove_vehicle(int row, int column)
{
    if (arr[row][column].number_plate != "")
    {
        cout << "Vehicle removed from spot R" << row + 1 << "C" << column + 1 << "." << endl;
        arr[row][column] = Vehicle(); 
        occupied -= 1;
        string vehicle_number = arr[row][column].number_plate;

        write_log(("Vehicle " + vehicle_number + " has left the parking!"));
    }
    else
    {
        cout << "This spot is already empty!" << endl;
    }
}

void show_status()
{
    cout << "Total Capacity: " << total << endl;
    cout << "Occupied Spaces: " << occupied << endl;
    cout << "Available Spaces: " << total - occupied << endl << endl;
}

void show_vehicle_details(int row, int column)
{
    if (arr[row][column].number_plate != "")
    {
        cout << "--------------------------------------------" << endl;
        cout << "Vehicle details at R" << row + 1 << "C" << column + 1 << ":" << endl;
        cout << "Number plate: " << arr[row][column].number_plate << endl;
        cout << "Make: " << arr[row][column].make << endl;
        cout << "Model: " << arr[row][column].model << endl;
        cout << "Color: " << arr[row][column].color << endl;
        cout << "Charges: $" << arr[row][column].charges << endl;
        cout << "--------------------------------------------" << endl;
    }
    else
    {
        cout << "--------------------------------------------" << endl;
        cout << "No vehicle is parked at R" << row + 1 << "C" << column + 1 << endl;
        cout << "--------------------------------------------" << endl;
    }
    write_log(("Details of vehicle " + arr[row][column].number_plate + " have been accessed!"));
}

void reset_parking_lot()
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            arr[i][j] = Vehicle(); 
        }
    }
    occupied = 0; 
    cout << "Parking lot has been reset." << endl;
    write_log(("Parking lot has been reset."));

}


void write_log(string data)
{
    fstream LogFile("logs.txt", ios::app);
    LogFile << data << endl;
    LogFile.close();

}

void add_history(string data)
{
    fstream LogFile("history.txt", ios::app);
    LogFile << data << endl;
    LogFile.close();

}
