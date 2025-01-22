#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <iostream>
#include "addbookrecord.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_editButton_clicked();
    void on_findButton_clicked();
    void on_clearFindButton_clicked();
    void clearFind();

private:
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *findButton;
    QPushButton *clearFindButton;
    QPushButton *deleteButton;

    QTableWidget *table;

    QList<AddressBookRecord> records;
    QSqlDatabase db; // объект базы данных

private:
    void TableWidgetDisplay(const QList<AddressBookRecord>& records);
    int getSelectedRowIndex() const;
    int getIndexByPhoneNumber(const QString& phoneNumber) const;
    void insertRecord(AddressBookRecord record);

    QList<AddressBookRecord> *findRecords(AddressBookRecord record);
    QList<AddressBookRecord> *readRecordsFromDb();
    void writeRecordsToFile(QList<AddressBookRecord> *data);
    void Add(const std::string& first_name, const std::string& second_name, const std::string& third_name,
             const std::string& number, const std::string& address, const std::string& birthday,
             const std::string& email);
    void clear();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
#endif // MAINWINDOW_H
