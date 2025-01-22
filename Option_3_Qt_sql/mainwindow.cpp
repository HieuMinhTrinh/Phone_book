#include "mainwindow.h"

#include <QHBoxLayout>
#include <QFile>
#include <QHeaderView>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>

#include "inputformdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    records = *readRecordsFromDb();

    QVBoxLayout *layout = new QVBoxLayout;
    table = new QTableWidget();
    table->viewport()->installEventFilter(this);
    TableWidgetDisplay(records);
    layout->addWidget(table);

    QHBoxLayout* layoutForButtons = new QHBoxLayout;

    addButton = new QPushButton("Добавить");
    addButton->setStyleSheet("background-color: lightBlue");
    connect(addButton, SIGNAL(clicked()), SLOT(on_addButton_clicked()));
    layoutForButtons->addWidget(addButton);

    editButton = new QPushButton("Изменить");
    editButton->setStyleSheet("background-color: lightBlue");
    connect(editButton, SIGNAL(clicked()), SLOT(on_editButton_clicked()));
    layoutForButtons->addWidget(editButton);

    findButton = new QPushButton("Найти");
    findButton->setStyleSheet("background-color: lightBlue");
    connect(findButton, SIGNAL(clicked()), SLOT(on_findButton_clicked()));
    layoutForButtons->addWidget(findButton);

    clearFindButton = new QPushButton("Главный");
    clearFindButton->setStyleSheet("background-color: lightBlue");
    connect(clearFindButton, SIGNAL(clicked()), SLOT(on_clearFindButton_clicked()));
    layoutForButtons->addWidget(clearFindButton);

    deleteButton = new QPushButton("Удалить");
    deleteButton->setStyleSheet("background-color: lightBlue");
    connect(deleteButton, SIGNAL(clicked()), SLOT(on_deleteButton_clicked()));
    layoutForButtons->addWidget(deleteButton);

    layout->addLayout(layoutForButtons);
    setLayout(layout);
    setWindowTitle(tr("Телефонный справочник"));
    resize(550, 370);
}

void MainWindow::TableWidgetDisplay(const QList<AddressBookRecord>& records)
{
    table->clear();
    table->setColumnCount(7);
    table->setRowCount(records.count());

    QStringList hLabels;
    hLabels << "Имя" << "Фамилия" << "Отчество" << "Адрес" << "Дата рождения" << "Email" << "Номер телефона";
    table->setHorizontalHeaderLabels(hLabels);

    for (int i = 0; i < table->rowCount(); i++) {
        QTableWidgetItem *item;
        for (int j = 0; j<table->columnCount(); j++) {
            item = new QTableWidgetItem();
            switch (j) {
            case 0: item->setText(records[i].getName()); break;
            case 1: item->setText(records[i].getSurname()); break;
            case 2: item->setText(records[i].getPatronymic()); break;
            case 3: item->setText(records[i].getAddress()); break;
            case 4: {
                QDate date = QDate::fromString(records[i].getBirthDate(), "dd.MM.yyyy");
                item->setData(Qt::DisplayRole, date);
                break;
            }
            case 5: item->setText(records[i].getEmail()); break;
            case 6: item->setText(records[i].getPhoneNumber()); break;
            }

            table->setItem(i, j, item);
        }
    }

    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers((QAbstractItemView::EditTrigger) 0);

    table->setShowGrid(true);
    table->setGridStyle(Qt::SolidLine);
    table->setSortingEnabled(true);

    table->horizontalHeader()->setVisible(true);
    table->horizontalHeader()->setDefaultSectionSize(150);

    QHeaderView *hw = table->horizontalHeader();
    emit hw->sectionClicked(1);
}


MainWindow::~MainWindow()
{
    clear();
    writeRecordsToFile(&records);
}

void MainWindow::on_addButton_clicked()
{
    InputFormDialog dlg(&records, new QString("Добавить"), this);
    switch (dlg.exec()) {
    case QDialog::Accepted: {
        insertRecord(dlg.getInput()); break;
    }
    case QDialog::Rejected: {
        qDebug() << "Record rejected";
        break;
    }
    default:
        qDebug() << "Record unexpected";
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int selectedRowIndex = getSelectedRowIndex();
    if (selectedRowIndex > -1){
        QString phoneNumber = table->item(selectedRowIndex, table->columnCount()-1)->text();
        int indexByPhone = getIndexByPhoneNumber(phoneNumber);

        if (indexByPhone > -1)
            records.erase(records.begin() + getIndexByPhoneNumber(phoneNumber));

        table->removeRow(selectedRowIndex);
        table->clearSelection();
    } else {
        auto mb = new QMessageBox();
        mb->setText(tr("выберите запись пожалуйста!!!"));
        mb->open();
    }
}

void MainWindow::on_editButton_clicked()
{
    int selectedRowIndex = getSelectedRowIndex();
    if (selectedRowIndex > -1) {
        QString name = table->item(selectedRowIndex, 0)->text();
        QString surname = table->item(selectedRowIndex, 1)->text();
        QString patronymic = table->item(selectedRowIndex, 2)->text();
        QString address = table->item(selectedRowIndex, 3)->text();
        QDate birthDate = table->item(selectedRowIndex, 4)->data(Qt::DisplayRole).toDate();
        QString birthDateString = birthDate.toString("dd.MM.yyyy");
        QString email = table->item(selectedRowIndex, 5)->text();
        QString phoneNumber = table->item(selectedRowIndex, 6)->text();
        AddressBookRecord record(name, surname, patronymic, address,
                                 birthDateString, email, phoneNumber);

        QList<AddressBookRecord> records_without_number;
        records_without_number.append(records);
        records_without_number.removeOne(records[getIndexByPhoneNumber(phoneNumber)]);
        InputFormDialog dlg(&records_without_number, new QString("Изменить"), this);
        dlg.setInitialRecords(record);
        switch (dlg.exec()) {
        case QDialog::Accepted:
            table->setSortingEnabled(false);
            on_deleteButton_clicked();
            insertRecord(dlg.getInput());
            table->setSortingEnabled(true);
            break;
        case QDialog::Rejected:
            qDebug() << "Rejected";
            break;
        default:
            qDebug() << "Unexpected";
        }
    }else {
        auto mb = new QMessageBox();
        mb->setText(tr("выберите запись пожалуйста!!!"));
        mb->open();
    }
}

void MainWindow::on_findButton_clicked()
{
    clearFind();
    InputFormDialog dlg(&records, new QString("Найти"), this);
    AddressBookRecord record("", "", "", "",
                             "", "", "");
    dlg.setInitialRecords(record);
    switch (dlg.exec()) {
    case QDialog::Accepted: {
        AddressBookRecord record = dlg.getInput();
        QList<AddressBookRecord> *found_records = findRecords(record);
        TableWidgetDisplay(*found_records);
        connect(addButton, &QPushButton::clicked, this, &MainWindow::clearFind);
        connect(editButton, &QPushButton::clicked, this, &MainWindow::clearFind);
        connect(findButton, &QPushButton::clicked, this, &MainWindow::clearFind);
        connect(deleteButton, &QPushButton::clicked, this, &MainWindow::clearFind);
        break;
    }
    case QDialog::Rejected: {
        qDebug() << "Rejected";
        break;
    }
    default:
        qDebug() << "Unexpected";
    }
}

void MainWindow::on_clearFindButton_clicked()
{
    clearFind();
}

void MainWindow::clearFind()
{
    disconnect(addButton, &QPushButton::clicked, this, &MainWindow::clearFind);
    disconnect(editButton, &QPushButton::clicked, this, &MainWindow::clearFind);
    disconnect(findButton, &QPushButton::clicked, this, &MainWindow::clearFind);
    disconnect(deleteButton, &QPushButton::clicked, this, &MainWindow::clearFind);
    table->setSortingEnabled(false);
    TableWidgetDisplay(records);
}

QList<AddressBookRecord>* MainWindow::findRecords(AddressBookRecord record){
    QList<AddressBookRecord>* find_records = new QList<AddressBookRecord>();
    QList<AddressBookRecord>::iterator iterator_points= records.begin();

    while (iterator_points != records.end()) {
        iterator_points = std::find_if(iterator_points, records.end(), [&](AddressBookRecord record_inner){
            if(!record.getName().isEmpty() && !record_inner.getName().startsWith(record.getName())) return false;
            if(!record.getSurname().isEmpty() && !record_inner.getSurname().startsWith(record.getSurname())) return false;
            if(!record.getPatronymic().isEmpty() && !record_inner.getPatronymic().startsWith(record.getPatronymic())) return false;
            if(!record.getAddress().isEmpty() &&!record_inner.getAddress().startsWith(record.getAddress())) return false;
            if(!(record.getBirthDate() == " ") &&!record_inner.getBirthDate().startsWith(record.getBirthDate())) return false;
            if(!record.getEmail().isEmpty() &&!record_inner.getEmail().startsWith(record.getEmail())) return false;
            if(!record.getPhoneNumber().isEmpty() &&!record_inner.getPhoneNumber().startsWith(record.getPhoneNumber())) return false;
            return true;
        });
        if (iterator_points == records.end()) {
            break;
        }
        find_records->append(*iterator_points);
        iterator_points++;
    }
    return find_records;
}

int MainWindow::getSelectedRowIndex() const
{
    // поиск индекса выделенной строки
    QList<QTableWidgetSelectionRange> rangesList = table->selectedRanges();
    foreach (QTableWidgetSelectionRange range, rangesList)
    {
        return range.topRow();
    }
    return -1;
}

int MainWindow::getIndexByPhoneNumber(const QString& phoneNumber) const
{
    int index = 0;
    for(const AddressBookRecord& element: records){
        if(element.getPhoneNumber() == phoneNumber){
            return index;
        }
        index++;
    }
    return -1;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == table->viewport() && event->type() == QEvent::MouseButtonRelease) {
        // снятие выделения строки при нажатии на "свободную" поверхность
        QMouseEvent *me = static_cast<QMouseEvent*> (event);

        QModelIndex index = table->indexAt(me->pos());

        if (!index.isValid()) {
            table->clearSelection();
        }

        return true;
    }

    return QWidget::eventFilter(watched, event);
}

void MainWindow::insertRecord(AddressBookRecord record)
{
    records.append(record);
    table->setSortingEnabled(false);
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1, 0, new QTableWidgetItem(record.getName()));
    table->setItem(table->rowCount()-1, 1, new QTableWidgetItem(record.getSurname()));
    table->setItem(table->rowCount()-1, 2, new QTableWidgetItem(record.getPatronymic()));
    table->setItem(table->rowCount()-1, 3, new QTableWidgetItem(record.getAddress()));
    auto date = QDate::fromString(record.getBirthDate(), "dd.MM.yyyy");
    auto item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, date);
    table->setItem(table->rowCount()-1, 4, item);
    table->setItem(table->rowCount()-1, 5, new QTableWidgetItem(record.getEmail()));
    table->setItem(table->rowCount()-1, 6, new QTableWidgetItem(record.getPhoneNumber()));
    table->setSortingEnabled(true);
}
void MainWindow::Add(const std::string& first_name, const std::string& second_name, const std::string& third_name,
                     const std::string& number, const std::string& address, const std::string& birthday,
                     const std::string& email) {
    QSqlQuery query;
    //подготовка для добавления данных в таблицу
    query.prepare("INSERT INTO contacts (first_name, second_name, third_name, phone, email, address, birthday) "
                  "VALUES (:first_name, :second_name, :third_name, :phone, :email, :address, :birthday)");
    //привязка значений
    query.bindValue(":first_name", QString::fromStdString(first_name));
    query.bindValue(":second_name", QString::fromStdString(second_name));
    query.bindValue(":third_name", QString::fromStdString(third_name));
    query.bindValue(":phone", QString::fromStdString(number));
    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":address", QString::fromStdString(address));
    query.bindValue(":birthday", QString::fromStdString(birthday));
    //выполнение sql запроса
    if (!query.exec()) {
        qDebug() << "Ошибка добавления контакта:" << query.lastError().text();
    }
}
void MainWindow::clear()
{
    QSqlQuery query;
    if (!query.exec("DELETE FROM contacts")) {
        qDebug() << "Ошибка очистки базы данных:" << query.lastError().text();
    }
}
QList<AddressBookRecord> *MainWindow::readRecordsFromDb()
{
    QFile file("C:\\Users\\ADMIN\\OneDrive\\Desktop\\Phone_book\\Option_2_C++_txt\\phone_list_1.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Could not open the file for reading: C:\\Users\\ADMIN\\OneDrive\\Desktop\\Phone_book\\Option_2_C++_txt\\phone_list_1.txt";
        return nullptr;
    }

    QTextStream in(&file);
    QList<AddressBookRecord> *list = new QList<AddressBookRecord>();
    while (!in.atEnd()) {
        AddressBookRecord record;
        in >> record;
        list->append(record);
    }

    file.close();
    return list;
}
void MainWindow::writeRecordsToFile(QList<AddressBookRecord> *data)
{
    QFile file("C:/Users/ADMIN/OneDrive/Desktop/Lab_Qt_Db/lab8_qt_db/result.txt");
    if (!file.open(QFile::WriteOnly |
                   QFile::Text)) {
        qDebug() << "C:/Users/ADMIN/OneDrive/Desktop/Lab_Qt_Db/lab8_qt_db/result.txt";
        return;
    }
    QTextStream out(&file);
    for (auto iter = data->begin(); iter != data->end(); iter++) {
        out << *iter;
        if (iter != data->end()-1) {
            out << "\n";
        }
    }
    file.close();
    QFile file_2("C:/Users/ADMIN/OneDrive/Desktop/Lab_Qt_Db/lab8_qt_db/result.txt");

    if (!file_2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла для чтения:" << file_2.errorString();
        return;
    }

    QTextStream in(&file_2);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() != 7) {
            qDebug() << "Ошибка в формате строки:" << line;
            continue;
        }

        Add(fields[0].toStdString(), fields[1].toStdString(), fields[2].toStdString(),
            fields[3].toStdString(), fields[4].toStdString(), fields[5].toStdString(), fields[6].toStdString());
    }

    file_2.close();
}
