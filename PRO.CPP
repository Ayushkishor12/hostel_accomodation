#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Hostel {
private:
    string name;
    int rent, bed;

public:
    // Constructor
    Hostel(string name, int rent, int bed) {
        this->name = name;
        this->rent = rent;
        this->bed = bed;
    }

    // Getter methods
    string getName() { return name; }
    int getRent() { return rent; }
    int getBed() { return bed; }

    // Reserve bed and update the file
    void reserve() {
        ifstream in("C:\\Users\\KIIT\\Desktop\\c++\\project\\hostel.txt");
        ofstream out("C:\\Users\\KIIT\\Desktop\\c++\\project\\temp.txt");

        string line;
        while (getline(in, line)) {
            int pos = line.find("3star");
            if (pos != string::npos) {  // Fixed string::npos check
                // Update bed count
                bed--;  // Reduce bed count
                stringstream ss;
                ss << bed;  // Convert int to string
                string strBed = ss.str();

                // Find position and replace
                int bedPos = line.find_last_of(':');
                line.replace(bedPos + 1, string::npos, strBed);
            }
            out << line << endl;  // Write updated line
        }
        in.close();
        out.close();

        // Replace old file with updated file
        remove("C:\\Users\\KIIT\\Desktop\\c++\\project\\hostel.txt");
        rename("C:\\Users\\KIIT\\Desktop\\c++\\project\\temp.txt", 
               "C:\\Users\\KIIT\\Desktop\\c++\\project\\hostel.txt");

        cout << "\n\tBed reserved successfully!" << endl;
    }
};

class Student {
private:
    string Name, Rollno, Address;

public:
    Student() : Name(""), Rollno(""), Address("") {}

    // Setter methods
    void setName(string name) { Name = name; }
    void setRollno(string rollno) { Rollno = rollno; }
    void setAddress(string address) { Address = address; }

    // Getter methods
    string getName() { return Name; }
    string getRollno() { return Rollno; }
    string getAddress() { return Address; }
};

int main() {
    Hostel h("3star", 5000, 2);  // Initialize hostel with 2 beds

    // Save hostel data to file
    ofstream out("C:\\Users\\KIIT\\Desktop\\c++\\project\\hostel.txt");
    out << h.getName() << " : " << h.getRent() << " : " << h.getBed() << endl;
    out.close();

    cout << "Hostel data saved!" << endl;

    Student s;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome to Hostel Accommodation System" << endl;
        cout << "\t**********************************" << endl;
        cout << "\t1. Reserve a bed." << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");

            if (h.getBed() == 0) {  // No beds available
                cout << "\nNo beds available. Please try later.\n";
                system("pause");
                continue;
            }

            // Input student details
            string name, rollno, address;
            cout << "\tEnter Name of Student: ";
            cin.ignore();
            getline(cin, name);
            s.setName(name);

            cout << "\tEnter Roll No of Student: ";
            getline(cin, rollno);
            s.setRollno(rollno);

            cout << "\tEnter Address of Student: ";
            getline(cin, address);
            s.setAddress(address);

            // Reserve a bed
            h.reserve();

            // Save student details to file
            ofstream outFile("C:\\Users\\KIIT\\Desktop\\c++\\project\\student.txt", ios::app);
            outFile << s.getName() << " : " << s.getRollno() << " : " << s.getAddress() << endl;
            outFile.close();

            cout << "\nStudent details saved successfully!\n";
            system("pause");
        } else if (val == 2) {
            exit = true;
            cout << "\nExiting the system. Goodbye!" << endl;
            Sleep(3000);
        } else {
            cout << "\nInvalid choice! Try again." << endl;
            system("pause");
        }
    }

    return 0;
}
