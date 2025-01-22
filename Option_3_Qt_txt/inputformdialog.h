#ifndef INPUTFORMDIALOG_H
#define INPUTFORMDIALOG_H


#include <QDialog>
#include <QBoxLayout>
#include <QLineEdit>
#include <QDateEdit>

#include "addbookrecord.h"

class InputFormDialog: public QDialog
{
    Q_OBJECT

public:
    InputFormDialog(QList<AddressBookRecord> *records, QString *title, QWidget *parent = 0);
    ~InputFormDialog();

    AddressBookRecord getInput() const;
    void setInitialRecords(AddressBookRecord& record);

private:
    QList<AddressBookRecord> *records_num;

    QLineEdit *name;
    QLineEdit *surname;
    QLineEdit *patronymic;
    QLineEdit *address;
    QDateEdit *birthDate;
    QLineEdit *email;
    QLineEdit *phoneNumber;

    bool correctName = false;
    bool correctSurname = false;
    bool correctPatronymic = false;
    bool correctBirthDate = true;
    bool correctEmail = false;
    bool correctPhoneNumber = false;

private:
    bool validateNameLike(QString string);
    QHBoxLayout *addEditTextWithLabel(QString label, QWidget *widget);
    bool balanced(QString str);
signals:
    void allOk();

private slots:
    void setDateVisible();
    void validateAll();
    void validateName();
    void validateSurname();
    void validatePatronymic();
    void validateBirthDate();
    void validateEmail();
    void validatePhoneNumber();
};

#endif
