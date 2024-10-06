#include "tele_book.hpp"
#include <conio.h>

int main() {
    int members = 0;
    string option;
    int update_index = 0;
    int remove_index = 0;

    TelephoneList list;
    Person *head;
    list.init(members);
    head = list.head;

    while(true) {
        Option(); cin >> option;
        if (option == "1") {
            list.addPerson();
            members++;
        }
        else if (option == "2") {
            cout << "\n\t\t (?)Enter the index you want to delete: "; cin >> remove_index;
            while (remove_index < 0 || remove_index > members) {
                cout << "\t\tValue is invalid... ";
                cout << "\n\t\t (?)Enter the index to delete: ";
                cin >> remove_index;
            }
            list.removePerson(remove_index-1, &head);
            members--;
        }
        else if (option == "3") {
            list.findPerson();
        }
        else if (option == "4") {
            list.printAll();
        }
        else if (option == "5") {
            cout << "\n\t\t (?)Enter the index you want to update: "; cin >> update_index;
            while (update_index < 0 || update_index > members) {
                cout << "\t\tValue is invalid... ";
                cout << "\n\t\t (?)Enter the index to update: ";
                cin >> update_index;
            }
            list.updatePerson(update_index, head);
        }
        else if (option == "6") {
            list.pastIntoFile();
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
    }
}