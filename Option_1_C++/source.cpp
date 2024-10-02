#include "Telephone_book.hpp"
#include <conio.h>

int main() {
    Telephone_book tel_book;
    system("cls");
    cout << "Welcome to the phone book!" << endl;
    string option;
    while(true) {
        Window();
        cin >> option;
        if (option == "1") {
            cout << "Enter contact name:" << endl;
            string first_name;      cin >> first_name;
            cout << "Enter contact's last name:" << endl;
            string second_name;     cin >> second_name;
            cout << "Enter phone number:" << endl;
            string number;          cin >> number;
            cout << "Enter contact's job:" << endl;
            string job;             cin >> job;
            cout << "Add contact to phone book? Yes/No" << endl;
            string ans;             cin >> ans;
            if(ans == "Yes" || ans == "yes") {
                tel_book.Insert(first_name, second_name, number, job);
                cout << "Add to phone book successfully!" << endl;
            }
        }
        else if (option == "2") {
            cout << "Enter the phone number to remove: " << endl;
            string number;              cin >> number;
            tel_book.Erase(number);
            cout << "Deleted successfully!" << endl;
        }
        else if (option == "3") {
            cout << "Enter contact's last name: " << endl;
            string second_name;
            cin >> second_name;
            tel_book.Find(second_name);
        }
        else if (option == "4") {
            tel_book.Print_all();
        }
        else if (option == "5") {
            cout << "The last name to change: " << endl;
            string second_name;         cin >> second_name;
            cout << "Enter a new contact name: " << endl;
            string first_name;          cin >> first_name;
            cout << "Enter the contact's new phone number: " << endl;
            string number;              cin >> number;
            cout << "Enter the contact's new job: " << endl;
            string job;                 cin >> job;
            tel_book.Update(second_name, first_name, number, job); 
            cout << "Update successfully!" << endl;
        }
        else if (option == "6") {
            cout << "Clear your phone book? Yes/No" << endl;
            string ans;                 cin >> ans;
            if(ans == "Yes" || ans == "yes"){
                tel_book.Clear();
                cout << "Clear successfully!" << endl;
            }
        }
        else if (option == "7") {
            cout << "Closed phone book successfully!" << endl;
            break;
        }
        else {
            cout << "Your input invalid!" << endl;
        }        
        cout << "\nPress any key to the continue...";
        _getch();
        //system("cls");
    }
}