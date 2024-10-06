#include <fstream>
#include <filesystem>
#include "tele_book.hpp"
#include "table.hpp"

const string file_name = "phone_list.txt";

void TelephoneList::init(int& member) {
    std:: ifstream data(file_name);
    string line;
    /* If phone_list isn't empty*/
    if (!filesystem::is_empty(file_name)) {
        while(getline(data, line)) {
            int count = 0;
            string infoPerson[3];
            int i = line.find(";");
            while ( i != string:: npos) {
                infoPerson[count] = line.substr(0,i);
                count ++;
                line = line.substr(i+1);
                i = line.find(";");
            }
            infoPerson[3] = line;
            Person* person = new Person;
            person->first_name = infoPerson[0];
            person->second_name = infoPerson[1];
            person->number = infoPerson[2];
            person->job = infoPerson[3];
            append(person);
            member++;
        }
    }
    else {
        cout << "Phone list is empty.Please add to list" << endl;
        addPerson();
        string ans;
        cout << "Do you want to save to file? Yes/No" << endl;
        cin >> ans;
        if (ans == "Yes" or "yes") {
            pastIntoFile();
            cout << "Successfully save to file!" << endl;
        }
        else {
            cout << "Data not saved!" << endl;
        }
    }
    data.close();
}

void TelephoneList::append(Person* person_append) {
    if (head == NULL) {
        head = person_append;
        return;
    }
    Person *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = person_append;
}

void TelephoneList::addPerson(){
    string fName, sName, numPhone, job;
    cout << "Add member to phone list:" << endl;
    cout << "\tEnter your contact name: "; cin >> fName;
    cout << "\tEnter your last name: "; cin >> sName;
    cout << "\tEnter phone number: "; cin >> numPhone;
    cout << "\tEnter contact's job: "; cin >> job;
    cout << "Added successfully: " << fName << "-" << sName << "-" << numPhone << "-" << job << endl;
    Person* newPerson = new Person;
    newPerson->first_name = fName;
    newPerson->second_name = sName;
    newPerson->number = numPhone;
    newPerson->job = job;
    append(newPerson);
}
void TelephoneList::pastIntoFile() {
    std:: ofstream outPut("phone_list.txt");
    for (Person* p = head; p != NULL; p = p->next) {
        outPut << p->first_name << ";" << p->second_name << ";" << p->number << ";" << p->job << endl;
    }
    cout << "Successfully saved file!" << endl;
}
void TelephoneList::printAll() {
    print_row();
    cout << endl;
    print_row ("No", "Contact name", "Last name", "Phone number", "Job");
    print_row();
    cout << endl;
    int count = 1;
    for (Person* p = head; p != NULL; p = p->next ) {
        print_row(count, p->first_name, p->second_name, p->number, p->job);
        count++;
    }
    print_row();
}
void TelephoneList::updatePerson(int update_index, Person* person_head) {
    int choose;
    int cnt = 1;
    string update_fname, update_sname, update_number, update_job;
    Person* p = person_head;
    for (; p != NULL; p = p->next) {
        if (cnt == update_index) {
            break;
        }
        cnt ++;
    }
    cout << "\t\t (!)What do you want to update: " << endl << "\t\t 1- Contact name: " << endl << "\t\t 2- Last name: " << endl << "\t\t 3- Phone number: " << endl << "\t\t 4- Job "  << "\t (?) Option: "; cin >> choose;
    cin.ignore();
    if (choose == 1) {
        cout << "\t\t Enter contact name: "; cin >> update_fname;
        p->first_name = update_fname;
    }
    else if (choose == 2 ) {
        cout << "\t\t Enter last name: "; cin >> update_sname;
        p->second_name = update_sname;
    }
    else if (choose == 3) {
        cout << "\t\t Enter phone number: "; cin >> update_number;
        p->number = update_number;
    }
    else if (choose == 4) {
        cout << "\t\t Enter job: "; cin >> update_job;
        p->job = update_job;
    }
}
void TelephoneList::findPerson() {
    string find_char;
    Person temp_person[100];
    int count_find = 0;

    cout << "\t\t (?)Enter the character (string) you want to find: "; cin >> find_char;
    for (Person* p = head; p != NULL; p = p->next) {
        if ((p->second_name).find(find_char) != string:: npos) {
            temp_person[count_find].first_name = p->first_name;
            temp_person[count_find].second_name = p->second_name;
            temp_person[count_find].number = p->number;
            temp_person[count_find].job = p->job;
            count_find++;
        }
    }
    print_row();
    cout << endl;
    print_row ("No", "Contact name", "Last name", "Phone number", "Job");
    print_row();
    cout << endl;
    int count = 1;
    for (int i = 0; i < count_find; i++) {
        print_row(count, temp_person[i].first_name, temp_person[i].second_name, temp_person[i].number, temp_person[i].job);
        count++;
    }
    print_row();
}
void TelephoneList::removePerson(int remove_index, Person** remove_head){
    int count = 1;
    if (remove_index == 0) {
        *remove_head = head->next;
        head = *remove_head;
        return;
    }
    Person* p2_back = head;
    Person* p2 = head->next;
    while (p2 != NULL ) {
        if (count == remove_index) {
            p2_back->next = p2->next;
            delete(p2);
        }
        count++;
        p2_back = p2;
        p2 = p2->next;
    }
    cout << "Successfully deleted!" << endl;
}
void Option() {
    cout << "\nSelect option:" << endl;
    cout << "1- Add a contact to your phone book." << endl;
    cout << "2- Delete a contact from your phone book." << endl;
    cout << "3- Find a contact in the phone book." << endl;
    cout << "4- Print all contact in phone book." << endl;
    cout << "5- Update contact information in your phone book." << endl;
    cout << "6- Save information in to file." << endl;
    cout << "7- Close the phone book." << endl;
}


