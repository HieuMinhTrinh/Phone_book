
#ifndef __PRINTUTILS_HPP__
#define __PRINTUTILS_HPP__

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

//Display config

const int order_columm_width = 3;
const int fname_columm_width = 12;
const int lname_columm_width = 12;
const int mname_columm_width = 12;
const int add_columm_width = 10;
const int birth_columm_width = 15;
const int email_columm_width = 25;
const int number_columm_width = 15;
const int job_columm_width = 10;

const string corner_char = "+";
const string vertical_border_char = "|";
const string horizontal_border_char = "-";

void print_row ( string order, string fname, string lname, string mname, string add, string birth, string email, string number, string job) {
    cout << "\t" << std :: left 
        << vertical_border_char << setw(order_columm_width) << " " + order 
        << vertical_border_char << setw(fname_columm_width) << " " + fname
        << vertical_border_char << setw(lname_columm_width) << " " + lname
        << vertical_border_char << setw(mname_columm_width) << " " + mname
        << vertical_border_char << setw(add_columm_width) << " " + add
        << vertical_border_char << setw(birth_columm_width) << " " + birth
        << vertical_border_char << setw(email_columm_width) << " " + email
        << vertical_border_char << setw(number_columm_width) << " " + number
        << vertical_border_char << setw(job_columm_width) << " " + job
        << "|\n";
}

void print_row ( int order, string fname, string lname, string mname, string add, string birth, string email, string number, string job) {
    print_row(to_string(order), fname, lname, mname, add, birth, email, number, job);
}

std:: string line (int border_width, string c ) {
    string s;
    for ( int i = 0; i < border_width; i++) {
        s += c;
    }
    return s;
}

//Cơ chế Function Overloading : Cùng tên nhưng mà khác tham số nên đây được coi là 2 hàm khác nhau
void print_row () {
    cout << "\t" 
        << corner_char << line (order_columm_width, horizontal_border_char)
        << corner_char << line (fname_columm_width , horizontal_border_char)
        << corner_char << line (lname_columm_width , horizontal_border_char)
        << corner_char << line (mname_columm_width , horizontal_border_char)
        << corner_char << line (add_columm_width , horizontal_border_char)
        << corner_char << line (birth_columm_width , horizontal_border_char)
        << corner_char << line (email_columm_width , horizontal_border_char)
        << corner_char << line (number_columm_width , horizontal_border_char)
        << corner_char << line (job_columm_width , horizontal_border_char)
        << corner_char;
}
#endif