#ifndef ADDBOOKRECORD_H
#define ADDBOOKRECORD_H

#include <QString>
#include <QTextStream>

class AddressBookRecord
{
public:
    AddressBookRecord();
    AddressBookRecord(QString name, QString surname, QString patronymic,
                      QString address, QString birthDate, QString email,
                      QString phoneNumber);

public:
    QString getName() const;
    QString getSurname() const;
    QString getPatronymic() const;
    QString getAddress() const;
    QString getBirthDate() const;
    QString getEmail() const;
    QString getPhoneNumber() const;

public:
    void setName(QString& value);
    void setSurname(QString& value);
    void setPatronymic(QString& value) ;
    void setAddress(QString& value);
    void setBirthDate(QString& value);
    void setEmail(QString& value);
    void setPhoneNumber(QString& value);

public:
    bool operator == (const AddressBookRecord& person) const;
    friend QTextStream& operator>>(QTextStream& in, AddressBookRecord& person);
    friend QTextStream& operator<<(QTextStream& in, const AddressBookRecord& person);

private:
    QString name;
    QString surname;
    QString patronymic;
    QString address;
    QString birthDate;
    QString email;
    QString phoneNumber;
};

inline QTextStream& operator>>(QTextStream& in, AddressBookRecord& person)
{
    in >> person.name;
    in >> person.surname;
    in >> person.patronymic;
    in >> person.address;
    in >> person.birthDate;
    in >> person.email;
    in >> person.phoneNumber;

    person.address = person.address.replace("_", " ");
    person.phoneNumber = person.phoneNumber.replace("_", " ");

    return in;
}

inline QTextStream& operator<<(QTextStream& out, const AddressBookRecord& person)
{
    QString adress = person.address.simplified();
    if (adress.trimmed().isEmpty())
        adress = "Отсутствуют данные";

    out << person.name;
    out << " " << person.surname;
    out << " " << person.patronymic;
    out << " " << adress.replace(" ", "_");
    out << " " << person.birthDate;
    out << " " << person.email;
    out << " " << person.phoneNumber;

    return out;
}

#endif

