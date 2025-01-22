#include "addbookrecord.h"

AddressBookRecord::AddressBookRecord()
{
    name = QString("");
    surname = QString("");
    patronymic = QString("");
    birthDate = QString("");
    phoneNumber = QString("");
}

AddressBookRecord::AddressBookRecord(QString name,
                                     QString surname,
                                     QString patronymic,
                                     QString address,
                                     QString birthDate,
                                     QString email,
                                     QString phoneNumber)
{
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->address = address;
    this->birthDate = birthDate;
    this->email = email;
    this->phoneNumber = phoneNumber;
}

bool AddressBookRecord::operator==(const AddressBookRecord& person) const
{
    return (this->name == person.name && this->surname == person.surname &&
            this->patronymic == person.patronymic && this->address == person.address
            && this->birthDate == person.birthDate && this->email == person.email
            && this->phoneNumber == person.phoneNumber);
}


QString AddressBookRecord::getName() const
{
    return name;
}

QString AddressBookRecord::getSurname() const
{
    return surname;
}

QString AddressBookRecord::getPatronymic() const
{
    return patronymic;
}

QString AddressBookRecord::getAddress() const
{
    return address;
}

QString AddressBookRecord::getBirthDate() const
{
    return birthDate;
}

QString AddressBookRecord::getEmail() const
{
    return email;
}

QString AddressBookRecord::getPhoneNumber() const
{
    return phoneNumber;
}

void AddressBookRecord::setName(QString& value)
{
    name = value;
}

void AddressBookRecord::setSurname(QString& value)
{
    surname = value;
}

void AddressBookRecord::setPatronymic(QString& value)
{
    patronymic = value;
}

void AddressBookRecord::setAddress(QString& value)
{
    address = value;
}

void AddressBookRecord::setBirthDate(QString& value)
{
    birthDate = value;
}

void AddressBookRecord::setEmail(QString& value)
{
    email = value;
}

void AddressBookRecord::setPhoneNumber(QString& value)
{
    phoneNumber = value;
}
