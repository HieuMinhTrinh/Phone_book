#pragma once
#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Human{
    string first_name;
    string second_name;
    string number;
    string job;
    
    Human(string first_name = "", string second_name = "", string number = "", string job = "");
};

class Telephone_book{
public:
    void Insert(string first_name, string second_name, string number, string job);
    void Erase(string number);
    void Print_all();
    void Find(string second_name);
    void Update(string second_name, string first_name, string number, string job);
    void Clear();
private:
    map<string, Human> tb;
    
};

void Window();

ostream& operator <<(ostream& os, Human& human);