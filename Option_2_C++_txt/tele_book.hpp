#include <iostream>
#include <string>

using namespace std;

struct Person {
    string first_name;
    string second_name;
    string number;
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