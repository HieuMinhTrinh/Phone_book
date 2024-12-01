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
            string infoPerson[7];
            int i = line.find(";");
            while ( i != string:: npos) {
                infoPerson[count] = line.substr(0,i);
                count ++;
                line = line.substr(i+1);
                i = line.find(";");
            }
            infoPerson[7] = line;
            Person* person = new Person;
            person->first_name = infoPerson[0];
            person->last_name = infoPerson[1];
            person->middle_name = infoPerson[2];
            person->address = infoPerson[3];
            person->date_of_birth = infoPerson[4];
            person->email = infoPerson[5];
            person->phone_number = infoPerson[6];
            person->job = infoPerson[7];
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
    int idx_1, idx_2;
    string fullName, fName, lName, mName, address, dateBirth, email, numPhone, job;
    cout << "Add member to phone list:" << endl;

    do {
        cin.ignore();
        cout << "\tEnter your full name: "; getline(cin, fullName);
    } while(validateName(fullName) == false);
    fName = f_name(fullName, &idx_1);
    lName = l_name(fullName, &idx_2);
    mName = std::regex_replace(fullName.substr(idx_1,idx_2 - idx_1), std::regex("\\s+"), "");

    cout << "\tEnter your address: "; cin >> address;

    do {
        cout << "\tEnter your date of birth (YYYY-MM-DD): "; cin >> dateBirth;
    } while(validateDateOfBirth(dateBirth) == false);

    do {
        cout << "\tEnter your email: "; cin >> email;
    } while(validateEmail(email) == false);

    do {
        cout << "\tEnter your number phone: "; cin >> numPhone;
    } while(validatePhoneNumber(numPhone) == false);
    cout << "\tEnter contact's job: "; cin >> job;
    cout << "Added successfully: " << fName << "~" << lName << "~" << mName << "~" 
                                   << address << "~" << dateBirth  << "~" << email << "~" 
                                   << numPhone << "~" << job << endl;
    Person* newPerson = new Person;
    newPerson->first_name = fName;
    newPerson->last_name = lName;
    newPerson->middle_name = mName;
    newPerson->address = address;
    newPerson->date_of_birth = dateBirth;
    newPerson->email = email;
    newPerson->phone_number = numPhone;
    newPerson->job = job;
    append(newPerson);
}
void TelephoneList::pastIntoFile() {
    std:: ofstream outPut("phone_list.txt");
    for (Person* p = head; p != NULL; p = p->next) {
        outPut << p->first_name << ";" << p->last_name << ";" << p->middle_name << ";" 
               << p->address << ";" << p->date_of_birth << ";" << p->email << ";"
               << p->phone_number << ";" << p->job << endl;
    }
    cout << "Successfully saved file!" << endl;
}
void TelephoneList::printAll() {
    print_row();
    cout << endl;
    print_row ("No", "First name", "Last name", "Middle name", "Address", "Date of birth", "Email", "Phone number", "Job");
    print_row();
    cout << endl;
    int count = 1;
    for (Person* p = head; p != NULL; p = p->next ) {
        print_row(count, p->first_name, p->last_name, p->middle_name, p->address, p->date_of_birth, p->email, p->phone_number, p->job);
        count++;
    }
    print_row();
}
void TelephoneList::updatePerson(int update_index, Person* person_head) {
    int choose;
    int cnt = 1;
    string update_fname, update_lname, update_mname, update_address, update_birth, update_email, update_number, update_job;
    Person* p = person_head;
    for (; p != NULL; p = p->next) {
        if (cnt == update_index) {
            break;
        }
        cnt ++;
    }
    cout << "\t\t (!)What do you want to update: " << endl << "\t\t 1- First name: " << endl << "\t\t 2- Last name: " << endl
                                                           << "\t\t 3- Middle name: " << endl << "\t\t 4- Address: " << endl
                                                           << "\t\t 5- Date of birth: " << endl << "\t\t 6- Email: " << endl
                                                           << "\t\t 7- Phone number: " << endl << "\t\t 8- Job "  << "\t (?) Option: "; cin >> choose;
    cin.ignore();
    if (choose == 1) {
        cout << "\t\t Enter first name: "; cin >> update_fname;
        p->first_name = update_fname;
    }
    else if (choose == 2) {
        cout << "\t\t Enter last name: "; cin >> update_lname;
        p->last_name = update_lname;
    }
    else if (choose == 3) {
        cout << "\t\t Enter middle name: "; cin >> update_mname;
        p->middle_name = update_mname;
    }
    else if (choose == 4) {
        cout << "\t\t Enter address: "; cin >> update_address;
        p->address = update_address;
    }
    else if (choose == 5) {
        cout << "\t\t Enter date of birth: "; cin >> update_birth;
        p->date_of_birth = update_birth;
    }
    else if (choose == 6) {
        cout << "\t\t Enter email: "; cin >> update_email;
        p->email = update_email;
    }
    else if (choose == 7) {
        cout << "\t\t Enter phone number: "; cin >> update_number;
        p->phone_number = update_number;
    }
    else if (choose == 8) {
        cout << "\t\t Enter job: "; cin >> update_job;
        p->job = update_job;
    }
}
void TelephoneList::findPerson() {
    string find_char;
    Person temp_person[100];
    int count_find = 0;

    cout << "\t\t (?)Enter the character(string) you want to find (last name): "; cin >> find_char;
    for (Person* p = head; p != NULL; p = p->next) {
        if ((p->last_name).find(find_char) != string:: npos) {
            temp_person[count_find].first_name = p->first_name;
            temp_person[count_find].last_name = p->last_name;
            temp_person[count_find].middle_name = p->middle_name;
            temp_person[count_find].address = p->address;
            temp_person[count_find].date_of_birth = p->date_of_birth;
            temp_person[count_find].email = p->email;
            temp_person[count_find].phone_number = p->phone_number;
            temp_person[count_find].job = p->job;
            count_find++;
        }
    }
    print_row();
    cout << endl;
    print_row ("No", "First name", "Last name", "Middle name", "Address", "Date of birth", "Email", "Phone number", "Job");
    print_row();
    cout << endl;
    int count = 1;
    for (int i = 0; i < count_find; i++) {
        print_row(count, temp_person[i].first_name, temp_person[i].last_name, temp_person[i].middle_name, temp_person[i].address, temp_person[i].date_of_birth, temp_person[i].email, temp_person[i].phone_number, temp_person[i].job);
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

/*
^[A-Za-z]:
    The name must start with an English letter (case-insensitive).
[A-Za-z0-9 -]*:
    Allows letters, digits, hyphens, and spaces in the middle.
[A-Za-z0-9]$:
    Ensures the name ends with a letter or digit (not a space or hyphen).
*/
bool validateName(const std::string& name) {
    std::regex namePattern(R"(^[A-Za-z][A-Za-z0-9 -]*[A-Za-z0-9]$)", std::regex_constants::icase);
    return std::regex_match(name, namePattern);
}

/*
This regex checks if the input date matches the format YYYY-MM-DD, where:
    \d{4}: Four digits for the year.
    \d{2}: Two digits for the month.
    \d{2}: Two digits for the day.

*/
// Check if a year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Validate Date of Birth (Format: YYYY-MM-DD, and must be less than the current date)
bool validateDateOfBirth(const std::string& dob) {
    // Define the regex pattern for the date format YYYY-MM-DD
    std::regex datePattern(R"(\d{4}-\d{2}-\d{2})");

    // Check if the date matches the pattern
    if (!std::regex_match(dob, datePattern)) {
        return false;
    }

    // Parse year, month, and day
    int year, month, day;
    sscanf(dob.c_str(), "%d-%d-%d", &year, &month, &day);

    // Validate the month range (1 to 12)
    if (month < 1 || month > 12) {
        return false;
    }

    // Check days per month
    int daysPerMonth[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    // Validate the day range (1 to daysInMonth)
    if (day > daysPerMonth[month - 1]) {
        return false;
    }

    // Check if date is less than the current date
    time_t now = time(nullptr);
    tm* current = localtime(&now);

    if (year > current->tm_year + 1900 ||
        (year == current->tm_year + 1900 && month > current->tm_mon + 1) ||
        (year == current->tm_year + 1900 && month == current->tm_mon + 1 && day > current->tm_mday)) {
        return false;
    }
    return true;
}

bool validateEmail(const std::string& email) {
    // Regular expression pattern for validating the email
    std::regex emailPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    // Perform the validation after removing spaces
    return std::regex_match(email, emailPattern);
}

bool validatePhoneNumber(const std::string& phone) {
    // Updated regex with stricter area code validation for +7
    // Now we assume that only valid area codes for Russia (e.g., starting with 812, 495, etc.) are allowed.
    std::regex phonePattern(R"(^(\+7|8)(\((495|812)\)|\d{3})\d{3}[-]?\d{2}[-]?\d{2}$)");

    return std::regex_match(phone, phonePattern);
}

string f_name (string s, int *idx) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == SPACE || s[i] == HYPHEN || s[i] == UNDERLINE)  {
            *idx = i;
            return s.substr(0, i);
        }
    }
    return NULL;
}

string l_name (string s, int *idx) {
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == SPACE || s[i] == HYPHEN || s[i] == UNDERLINE)  {
            *idx = i;
            return s.substr(i+1);
        }
    }
    return NULL;
}