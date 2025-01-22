#include "inputformdialog.h"
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <bits/stdc++.h>

InputFormDialog::InputFormDialog(QList<AddressBookRecord> *records, QString *title, QWidget *parent)
    : QDialog(parent)
{
    records_num = records;
    QBoxLayout* layout = new QVBoxLayout;

    name = new QLineEdit;
    surname = new QLineEdit;
    patronymic = new QLineEdit;
    address = new QLineEdit;

    connect(name,       &QLineEdit::textEdited, this, &InputFormDialog::validateName);
    connect(surname,    &QLineEdit::textEdited, this, &InputFormDialog::validateSurname);
    connect(patronymic, &QLineEdit::textEdited, this, &InputFormDialog::validatePatronymic);

    layout->addLayout(addEditTextWithLabel("Имя ",      name));
    layout->addLayout(addEditTextWithLabel("Фамилия ",  surname));
    layout->addLayout(addEditTextWithLabel("Отчество ", patronymic));
    layout->addLayout(addEditTextWithLabel("Адрес ",    address));

    birthDate = new QDateEdit(QDate::currentDate());
    // birthDate->setCalendarPopup(true);
    birthDate->setDisplayFormat("dd.MM.yyyy");

    connect(birthDate, &QDateEdit::userDateChanged, this, &InputFormDialog::validateBirthDate);
    layout->addLayout(addEditTextWithLabel("Дата рождения: ", birthDate));

    email = new QLineEdit;
    connect(email, &QLineEdit::textEdited, this, &InputFormDialog::validateEmail);
    layout->addLayout(addEditTextWithLabel("Email: ", email));
    phoneNumber = new QLineEdit;
    connect(phoneNumber, &QLineEdit::textEdited, this, &InputFormDialog::validatePhoneNumber);
    layout->addLayout(addEditTextWithLabel("Номер телефона: ", phoneNumber));

    QBoxLayout *layoutH = new QHBoxLayout;

    QPushButton *okButton = new QPushButton("OK");
    connect(okButton, SIGNAL(clicked()), SLOT( validateAll()));
    connect(this, &InputFormDialog::allOk, &QDialog::accept);
    layoutH->addWidget(okButton);

    QPushButton *cancelButton = new QPushButton( "Cancel" );
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
    layoutH->addWidget(cancelButton);

    layout->addLayout(layoutH);
    setWindowTitle(*title);
    setLayout( layout );
}

void InputFormDialog::setDateVisible()
{
    birthDate->setStyleSheet("color: rgb(0,0,0)");
    disconnect(birthDate, &QDateEdit::userDateChanged, this, &InputFormDialog::setDateVisible);
    validateBirthDate();
}

QHBoxLayout *InputFormDialog::addEditTextWithLabel(QString label, QWidget *widget)
{
    QHBoxLayout *layoutSurname = new QHBoxLayout;
    QLabel *surnameLabel = new QLabel(label);
    layoutSurname->addWidget(surnameLabel);
    layoutSurname->addWidget(widget);
    return layoutSurname;
}

InputFormDialog::~InputFormDialog()
{
}

AddressBookRecord InputFormDialog::getInput() const
{
    QString place = address->text().simplified();
    return AddressBookRecord(name->text().replace(" ", ""), surname->text().replace(" ", ""), patronymic->text().replace(" ", ""),
                             place, birthDate->text(), email->text(),
                             phoneNumber->text().replace(" ", "").replace("+", "").replace("-", "").replace("(", "").replace(")", ""));
}

void InputFormDialog::setInitialRecords(AddressBookRecord& record)
{
    correctName = true;
    correctSurname = true;
    correctPatronymic = true;
    correctBirthDate = true;
    correctEmail = true;
    correctPhoneNumber = true;
    name->setText(record.getName());
    surname->setText(record.getSurname());
    patronymic->setText(record.getPatronymic());
    address->setText(record.getAddress());
    if(record.getBirthDate().isEmpty()){
        birthDate->setSpecialValueText(" ");
        birthDate->setDate(QDate::fromString("01.01.0001", "dd.MM.yyyy"));
        connect(birthDate, &QDateEdit::userDateChanged, this, &InputFormDialog::setDateVisible);
    } else {
        QDate date = QDate::fromString(record.getBirthDate(), "dd.MM.yyyy");
        birthDate->setDate(date);
    }
    email->setText(record.getEmail());
    phoneNumber->setText(record.getPhoneNumber());
}

void InputFormDialog::validateAll()
{
    if (correctName && correctSurname && correctPatronymic &&
        correctBirthDate && correctEmail && correctPhoneNumber) {
        emit allOk();
    } else {
        QMessageBox about;
        about.addButton(QString::fromUtf8("Ок"), QMessageBox::YesRole);
        about.setWindowTitle(QString::fromUtf8("Ошибка"));
        about.setText("Не все поля заполнены корректно");
        about.setIcon(QMessageBox::Information);
        about.resize(100, 100);
        about.exec();
    }
}

bool InputFormDialog::validateNameLike(QString string)
{
    QRegularExpression r(R"([А-ЯЁA-Z][А-ЯЁа-яёA-Za-z1-9]*)");
    QString str = string;
    QStringList pieces = str.split("-");
    for (QString& piece: pieces){
        if (!r.match(piece).hasMatch())
            return false;
    } return true;
}

void InputFormDialog::validateName()
{
    if (validateNameLike(name->text())) {
        name->setStyleSheet("color: rgb(0, 0, 0)");
        correctName = true;
    } else {
        name->setStyleSheet("color: rgb(255, 0, 0)");
        correctName = false;
    }
}

void InputFormDialog::validateSurname()
{
    if (validateNameLike(surname->text())) {
        surname->setStyleSheet("color: rgb(0, 0, 0)");
        correctSurname = true;
    } else {
        surname->setStyleSheet("color: rgb(255, 0, 0)");
        correctSurname = false;
    }
}

void InputFormDialog::validatePatronymic()
{
    if (validateNameLike(patronymic->text())) {
        patronymic->setStyleSheet("color: rgb(0, 0, 0)");
        correctPatronymic = true;
    } else {
        patronymic->setStyleSheet("color: rgb(255, 0, 0)");
        correctPatronymic = false;
    }
}

void InputFormDialog::validateBirthDate()
{
    if (birthDate->date() < QDate::currentDate()) {
        birthDate->setStyleSheet("color: rgb(0, 0, 0)");
        correctBirthDate = true;
    } else {
        birthDate->setStyleSheet("color: rgb(255, 0, 0)");
        correctBirthDate = false;
    }
}

void InputFormDialog::validateEmail()
{
    QRegularExpression r(R"([a-zA-Z1-9\-\._]+@[a-z1-9]+(\.[a-z1-9]+){1,})");
    if (r.match(email->text()).hasMatch()) {
        email->setStyleSheet("color: rgb(0, 0, 0)");
        correctEmail = true;
    } else {
        email->setStyleSheet("color: rgb(255, 0, 0)");
        correctEmail = false;
    }
}

void InputFormDialog::validatePhoneNumber()
{
    QString numbers = phoneNumber->text().replace(" ", "").replace("+", "").replace("-", "").replace("(", "").replace(")", "");

    QRegularExpression validPhoneRegex(R"(\d{10,12})");
    if (!validPhoneRegex.match(numbers).hasMatch()) {
        phoneNumber->setStyleSheet("color: rgb(255, 0, 0)");
        correctPhoneNumber = false;
        return;
    }

    QRegularExpression r(R"(\+?\d{1,3}([\(\s\-]?\d+[\)\s\-]?[\d\s\-]{6,12})?)");
    QRegularExpression r2(R"([1-9\+\(\)\s]+)");
    QRegularExpression r3(R"(\d)");
    int digits = 0;
    for (QChar element: phoneNumber->text()) {
        if(r3.match(element).hasMatch())
            digits += 1;
    }

    QStringList pieces = phoneNumber->text().split("-");
    for(QString& piece: pieces) {
        if(!r2.match(piece).hasMatch()) {
            phoneNumber->setStyleSheet("color: rgb(255, 0, 0)");
            correctPhoneNumber = false;
            return;
        }
    }
    if (!balanced(phoneNumber->text())) {
        phoneNumber->setStyleSheet("color: rgb(255, 0, 0)");
        correctPhoneNumber = false;
        return;
    }
    if (r.match(phoneNumber->text()).hasMatch() && digits <= 12) {
        phoneNumber->setStyleSheet("color: rgb(0, 0, 0)");
        correctPhoneNumber = true;
    } else {
        phoneNumber->setStyleSheet("color: rgb(255, 0, 0)");
        correctPhoneNumber = false;
    }
}

// проверка на правильность расстановки скобок
bool InputFormDialog::balanced(QString str)
{
    std::stack<QChar> stack;
    for(QChar c:str){
        if (c == '(')
            stack.push(')');
        if (c == ')') {
            if (stack.empty() || stack.top() != c)
                return false;
            stack.pop();
        }
    } return stack.empty();
}
