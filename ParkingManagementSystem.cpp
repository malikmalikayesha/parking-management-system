#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void line(char ch)
{
    for (int i = 0; i < 60; i++)
    {
        cout << ch;
    }
    cout << endl;
}

class ParkingPortal
{
protected:
    int attempts, tries;
    string input, pass;

public:
    ParkingPortal() : attempts(0), tries(3), pass("1234") {}
    ~ParkingPortal() {}

    inline void login()
    {

        system("cls");
        do
        {
            line('=');
            cout << "\t\tParking Management System\n\t\t\t Login Menu\n";
            line('=');

            cout << "\nEnter PIN to login to portal: ";
            cin >> input;
            if (input != pass)
            {
                attempts++;
                tries--;
                system("cls");

                cout << "Wrong Password!"
                     << "\t\t\tAttempts Remaining: " << tries << endl;
            }
        } while (attempts <= 3 && input != pass);

        system("cls");

        if (attempts > 3)
        {
            cout << "Login attempts exceeded\nSorry, you have been kicked from the program :/" << endl;
            exit(0);
        }

        line('*');
        getchar();

        system("cls");
    }
};

class Receipt
{
protected:
    string name;
    string license;
    int id;

public:
    Receipt() : name(" "), license(" ") {}
    ~Receipt() {}
    friend class Parking;

    void getData()
    {
        system("cls");

        cout << "\nEnter Name: ";
        cin >> name;
        cout << "Enter Reg ID: ";
        cin >> id;
        cout << "Enter Vehicle License: ";
        cin >> license;
    }

    virtual void print(){};
};

class Parking : public ParkingPortal, public Receipt
{
private:
    const int totalCapacity;
    static int parked;
    int freeSpace, cars, vans;
    int rowA[10], rowB[10], rowC[10];

public:
    Parking() : totalCapacity(30), freeSpace(30), cars(0), vans(0)
    {
        for (int i = 0; i < 10; i++)
        {
            rowA[i] = 0;
            rowB[i] = 0;
            rowC[i] = 0;
        }
    }
    ~Parking() {}

    void data();
    void currentLot();
    void park();
    void leaveLot();
    void print();
    void display();
};

int Parking::parked = 0; // static total parked

void Parking::data()
{
    cout << "Total Spaces: " << totalCapacity << "\t\t\t"
         << "Remaining Spaces: " << freeSpace << endl;
    cout << "Vehicles Parked: " << parked << "\t      Cars: " << cars << "\t\t    Vans: " << vans << endl;
}
void Parking::currentLot()
{
    line('-');
    cout << "   Row A\t\t   Row B\t\t   Row C" << endl;
    line('-');
    for (int i = 0; i < 10; i++)
    {
        string A, B, C;
        if (rowA[i] == 0)
        {
            A = "000000";
        }
        else
        {
            A = to_string(rowA[i]);
        }
        if (rowB[i] == 0)
        {
            B = "000000";
        }
        else
        {
            B = to_string(rowB[i]);
        }
        if (rowC[i] == 0)
        {
            C = "000000";
        }
        else
        {
            C = to_string(rowC[i]);
        }

        cout << "  " << A << "  |\t\t|  " << B << "  |\t\t|  " << C << endl;
    }
}
void Parking::park()
{
    int ch, pos;
    char row;

    system("cls");
    line('=');
    cout << "Current Parking Lot Stutus: " << endl;
    currentLot();
    line('=');
    cout << "Select Vehical to Park: " << endl;
    cout << "\n[1]Car" << endl;
    cout << "[2]Van" << endl;
    line('-');

    cout << "Choice: ";
    cin >> ch;

    cout << endl;

    switch (ch)
    {
    case 1:
    {
        cout << "Row B and C are reserved for Cars.\n"
             << endl;
        cout << "Enter your row: ";
        cin >> row;
        cout << "Enter your position: ";
        cin >> pos;
        cout << "\nConfirm your Reg ID: ";
        cin >> id;

        if (row == 'b' || row == 'B')
        {
            if (pos < 1 || pos > 10)
            {
                cout << "Invalid position!! :( \nPositions in Row B are from 1 - 10 only.";
                break;
            }
            else
            {
                if (rowB[pos - 1] != 0)
                {
                    cout << "Position already occupied!! :(";
                    break;
                }
                else
                {
                    rowB[pos - 1] = id;
                    system("cls");

                    cout << "Car has been parked in Row B Position " << pos << ". " << endl;
                    cout << "\nPress Enter to continue... " << endl;
                    getchar();

                    line('=');
                    cout << "Current Parking Lot Stutus: " << endl;
                    currentLot();
                    line('=');
                    cout << "\nPress Enter to continue... " << endl;
                }
            }
        }
        else if (row == 'c' || row == 'C')
        {
            if (pos < 1 || pos > 10)
            {
                cout << "Invalid position!! :( \nPositions in Row C are from 1 - 10 only.";
                break;
            }
            else
            {
                if (rowC[pos - 1] != 0)
                {
                    cout << "Position already occupied!! :(";
                    break;
                }
                else
                {
                    rowC[pos - 1] = id;
                    cout << "Car has been parked in Row C Position " << pos << ". " << endl;
                    cout << "\nPress Enter to continue... " << endl;
                    getchar();
                    line('=');
                    cout << "Current Parking Lot Stutus: " << endl;
                    currentLot();
                    line('=');
                    cout << "\nPress Enter to continue... " << endl;
                }
            }
        }
        else
        {
            cout << "Invalid row!! :( \nOnly rows B and C are reserved for Cars.";
            break;
        }

        cars++;
        parked++;
        freeSpace--;
        getchar();
    }
    break;

    case 2:
    {
        cout << "Row A is reserved for Vans." << endl;
        cout << "Enter your position: ";
        cin >> pos;
        cout << "\nConfirm your Reg ID: ";
        cin >> id;
        if (pos < 1 || pos > 10)
        {
            cout << "Invalid position!! :( \nPositions in Row A are from 1 - 10 only.";
        }
        else
        {
            if (rowA[pos - 1] != 0)
            {
                cout << "Position already occupied!! :(";
                break;
            }
            else
            {
                rowA[pos - 1] = id;
                cout << "Van has been parked in Row A Position " << pos << ". " << endl;
                cout << "\nPress Enter to continue... " << endl;
                getchar();

                getchar();
                system("cls");

                line('=');
                cout << "Current Parking Lot Stutus: " << endl;
                currentLot();
                line('=');
                cout << "\nPress Enter to continue... " << endl;
            }
        }

        vans++;
        parked++;
        freeSpace--;
        getchar();
    }
    break;

    default:
    {
        cout << "Please enter a valid option..." << endl;
        getchar();
        getchar();
        break;
    }
    }
}

void Parking::leaveLot()
{
    int choice;

    if (freeSpace == 30)
    {
        cout << "No vehicle parked, Enter a vehicle first! " << endl;
        cout << "Press enter to continue..." << endl;
        getchar();
    }
    else
    {
        system("cls");
        line('-');
        cout << "Select Vehicle to vacate from Parking lot:" << endl;
        cout << "\n[1]Vacate Car" << endl;
        cout << "[2]Vacate Van " << endl;

        line('-');

        cout << "Choice: ";
        cin >> choice;
        cout << "\nConfirm your Reg ID: ";
        cin >> id;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            if (cars == 0)
            {
                cout << "No car is parked yet" << endl;
                cout << "\nPress enter to continue..." << endl;
                getchar();
            }
            else
            {
                cars--;
                parked--;
                for (int i = 0; i < 10; i++)
                {
                    if (rowB[i] == id)
                    {

                        rowB[i] = 0;
                        cout << "Your car has been vacated from Row 'B' Position '" << i + 1 << "'" << endl;
                    }

                    if (rowC[i] == id)
                    {
                        rowC[i] = 0;
                        cout << "Your car has been vacated from Row 'C' Position '" << i + 1 << "'" << endl;
                    }
                }
                if (freeSpace < 30)
                {
                    freeSpace++;
                }
                cout << "\nPress Enter to continue... " << endl;
                getchar();
                system("cls");

                line('=');
                cout << "Current Parking Lot Stutus: " << endl;
                currentLot();
                line('=');

                cout << "\nPress enter to continue..." << endl;
                getchar();
            }
        }
        break;

        case 2:
        {
            if (vans == 0)
            {
                cout << "No van is parked yet" << endl;
                cout << "\nPress enter to continue..." << endl;
                getchar();
            }
            else
            {
                vans--;
                parked--;

                for (int i = 0; i < 10; i++)
                {
                    if (rowA[i] == id)
                    {

                        rowA[i] = 0;
                        cout << "Your van has been vacated from Row 'A' Position '" << i + 1 << "'" << endl;
                    }
                }
                if (freeSpace < 30)
                    freeSpace++;
                cout << "\nPress Enter to continue... " << endl;
                getchar();
                line('=');
                cout << "Current Parking Lot Stutus: " << endl;
                currentLot();
                line('=');

                cout << "\nPress enter to continue..." << endl;
                if (freeSpace <= 30)
                    freeSpace++;
                getchar();
            }
        }
        break;

        default:
            cout << "Invalid option";
            break;
        }
    }
}

void Parking::print()
{
    ofstream receipt("receipt.txt");
    receipt << "===============================" << endl;
    receipt << "\t  Ticket#" << parked << endl;
    receipt << "-------------------------------" << endl;
    receipt << "  Name: " << name << "  |  "
            << "Reg# " << id << endl;
    receipt << "-------------------------------" << endl;

    receipt << "  Plate Number: " << license << endl;
    receipt << "===============================" << endl;
    receipt.close();
    system("cls");
    cout << "\n\nYour Ticket has been printed!";
    cout << "\nYour ticket: \n"
         << endl;

    cout << "===============================" << endl;
    cout << "\t  Ticket#" << parked << endl;
    cout << "-------------------------------" << endl;
    cout << "  Name: " << name << "  |  "
         << "Reg# " << id << endl;
    cout << "-------------------------------" << endl;
    cout << "  Plate Number: " << license << endl;
    cout << "===============================" << endl;
    cout << "\n\nPress Enter to continue..." << endl;
    getchar();
    getchar();
}

inline void Parking::display()
{

    int ch;
    bool menu;

    system("cls");

    do
    {
        menu = false;
        system("cls");

        cout << "\t\tParking Management System\n";
        line('=');

        data();

        line('-');
        cout << "\n[1] Park Vehicle" << endl;
        cout << "[2] Exit Parking lot" << endl;
        cout << "[3] Print Receipt" << endl;
        cout << "[4] Logout" << endl;
        cout << "[5] Quit" << endl;

        line('=');

        cout << "\nChoice: ";
        cin >> ch;

        cout << endl;

        switch (ch)
        {
            int choice;

        case 1:
            park();
            menu = true;
            break;

        case 2:
            leaveLot();
            menu = true;
            break;

        case 3:
            if (parked == 0)
            {
                cout << "Park your vehicle to get your ticket" << endl;

                getchar();
                getchar();
                menu = true;
                break;
            }
            else
            {

                Receipt *rObj;
                Parking pObj;

                rObj = &pObj;

                rObj->getData();
                rObj->print();

                menu = true;
                break;
            }

        case 4:
            cout << "Are you sure you want to log out?"
                 << "\nPress enter to continue." << endl;

            getchar();

            ParkingPortal::login();
            menu = true;
            break;

        case 5:
            exit(0);

        default:
            cout << "\nEnter a valid number!\nPress Enter to try again..." << endl;
            getchar();
            getchar();
            menu = true;
            break;
        }
    } while (menu);
}

int main()
{
    Parking Main;

    Main.login();
    Main.display();

    return 0;
}