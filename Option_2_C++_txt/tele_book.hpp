#include <iostream>
#include <regex>
#include <string>
#include <ctime>

#define SPACE 32
#define HYPHEN 45
#define UNDERLINE 95

using namespace std;

struct Person {
    string first_name;
    string last_name;
    string middle_name;
    string address;
    string date_of_birth;
    string email;
    string phone_number;
    string job;
    Person* next = NULL;
};

class TelephoneList {
    public:
        Person* head = NULL;
    public:
        void init(int& member);
        void append(Person* person_append);
        void addPerson();
        void updatePerson(int fix_index, Person* person_head);
        void removePerson(int remove_index, Person** remove_head);
        void findPerson();
        void pastIntoFile();
        void printAll();

};

void Option();
bool validateName(const std::string& name);
bool isLeapYear(int year);
bool validateDateOfBirth(const std::string& dob);
bool validateEmail(const std::string& email);
bool validatePhoneNumber(const std::string& phone);
string f_name(string s, int *idx);
string l_name(string s, int *idx);
