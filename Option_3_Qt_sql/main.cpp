#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
bool connectToDatabase(QSqlDatabase& db) {
    db = QSqlDatabase::addDatabase("QSQLITE");//создание объекта
    db.setDatabaseName("C:/Users/ADMIN/OneDrive/Desktop/Lab_Qt_Db/lab8_qt_db/contacts.db");//указываю имя бд

    if (!db.open()) {
        std::cerr << "Ошибка подключения к базе данных: " << db.lastError().text().toStdString() << std::endl;
        return false;
    }
    //sql запрос
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS contacts (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            first_name TEXT NOT NULL,
            second_name TEXT NOT NULL,
            third_name TEXT,
            phone TEXT,
            email TEXT,
            address TEXT,
            birthday TEXT
        );
    )";
    //выполняю запрос на создание таблицы
    if (!query.exec(createTableQuery)) {
        std::cerr << "Ошибка создания таблицы: " << query.lastError().text().toStdString() << std::endl;
        return false;
    }

    return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db;
    if (!connectToDatabase(db)) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось подключиться к базе данных.");
        return -1;
    }
    MainWindow w;
    w.show();
    return a.exec();
}
