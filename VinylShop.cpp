#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

// ================== СТРУКТУРЫ ==================

// Структура "Пластинка"
struct VinylRecord {
    int id;                 // ID пластинки
    char artist[50];        // Исполнитель
    char album[50];         // Название альбома
    char genre[30];         // Жанр
    int year;               // Год выпуска
    float price;            // Цена
    int quantity;           // Количество на складе
};

// Структура "Клиент" (пока не используется, но нужна по заданию)
struct Customer {
    int id;
    char name[50];
    char phone[20];
    char email[50];
    int purchasesCount;
};

// ================== ПРОТОТИПЫ ФУНКЦИЙ ==================

void showMainMenu();
void addDataMenu();
void deleteDataMenu();

// Работа с пластинками
void addRecord();
void showAllRecords();
void deleteRecordById();
void showSummary();   // <<< СВОДНАЯ ИНФОРМАЦИЯ

// ================== МЕНЮ ==================

void showMainMenu() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=========================================\n";
    cout << "   МАГАЗИН ВИНИЛОВЫХ ПЛАСТИНОК\n";
    cout << "=========================================\n";
    cout << "1 - Добавить данные\n";
    cout << "2 - Просмотреть данные\n";
    cout << "3 - Удалить данные\n";
    cout << "4 - Поиск / фильтрация\n";
    cout << "5 - Сводная информация\n";
    cout << "6 - Сортировка\n";
    cout << "0 - Выход\n";
    cout << "-----------------------------------------\n";
    cout << "Введите номер пункта: ";
}

void addDataMenu() {
    int choice;
    do {
        cout << "\n=== ДОБАВЛЕНИЕ ДАННЫХ ===\n";
        cout << "1 - Добавить пластинку\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 0:
            break;
        default:
            cout << "Ошибка! Неверный выбор.\n";
        }
    } while (choice != 0);
}

void deleteDataMenu() {
    int choice;
    do {
        cout << "\n=== УДАЛЕНИЕ ДАННЫХ ===\n";
        cout << "1 - Удалить пластинку по ID\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            deleteRecordById();
            break;
        case 0:
            break;
        default:
            cout << "Ошибка! Неверный выбор.\n";
        }
    } while (choice != 0);
}

// ================== ФУНКЦИИ ==================

// Добавление пластинки
void addRecord() {

    VinylRecord record;

    cout << "\n--- Добавление пластинки ---\n";
    cout << "ID: ";
    cin >> record.id;
    cin.ignore();

    cout << "Исполнитель: ";
    cin.getline(record.artist, 50);

    cout << "Название альбома: ";
    cin.getline(record.album, 50);

    cout << "Жанр: ";
    cin.getline(record.genre, 30);

    cout << "Год выпуска: ";
    cin >> record.year;

    cout << "Цена: ";
    cin >> record.price;

    cout << "Количество на складе: ";
    cin >> record.quantity;

    // Запись в бинарный файл
    ofstream file("records.bin", ios::binary | ios::app);
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    file.write((char*)&record, sizeof(VinylRecord));
    file.close();

    cout << "Пластинка успешно добавлена!\n";
}

// Просмотр всех пластинок
void showAllRecords() {

    ifstream file("records.bin", ios::binary);
    if (!file) {
        cout << "Файл с пластинками не найден.\n";
        return;
    }

    VinylRecord record;
    bool empty = true;

    cout << "\n=== СПИСОК ПЛАСТИНОК ===\n";

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        empty = false;
        cout << "ID: " << record.id
             << " | Исполнитель: " << record.artist
             << " | Альбом: " << record.album
             << " | Цена: " << record.price
             << " | Кол-во: " << record.quantity << "\n";
    }

    if (empty) {
        cout << "Список пуст.\n";
    }

    file.close();
}

// Удаление пластинки по ID
void deleteRecordById() {

    ifstream file("records.bin", ios::binary);
    ofstream temp("temp.bin", ios::binary);

    VinylRecord record;
    int deleteId;
    bool found = false;

    cout << "Введите ID пластинки для удаления: ";
    cin >> deleteId;

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        if (record.id != deleteId) {
            temp.write((char*)&record, sizeof(VinylRecord));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("records.bin");
    rename("temp.bin", "records.bin");

    if (found)
        cout << "Пластинка удалена.\n";
    else
        cout << "Пластинка не найдена.\n";
}

// ================== СВОДНАЯ ИНФОРМАЦИЯ ==================

void showSummary() {

    ifstream file("records.bin", ios::binary);
    if (!file) {
        cout << "Файл с данными не найден.\n";
        return;
    }

    VinylRecord record;

    int recordsCount = 0;        // Количество записей
    int totalQuantity = 0;       // Общее количество экземпляров
    float totalCost = 0;         // Общая стоимость
    float minPrice = 0, maxPrice = 0;
    bool first = true;

    // Чтение всех записей
    while (file.read((char*)&record, sizeof(VinylRecord))) {

        recordsCount++;
        totalQuantity += record.quantity;
        totalCost += record.price * record.quantity;

        // Поиск минимальной и максимальной цены
        if (first) {
            minPrice = maxPrice = record.price;
            first = false;
        } else {
            if (record.price < minPrice) minPrice = record.price;
            if (record.price > maxPrice) maxPrice = record.price;
        }
    }

    file.close();

    if (recordsCount == 0) {
        cout << "Данных для анализа нет.\n";
        return;
    }

    cout << "\n=== СВОДНАЯ ИНФОРМАЦИЯ ===\n";
    cout << "Количество пластинок: " << recordsCount << "\n";
    cout << "Общее количество экземпляров: " << totalQuantity << "\n";
    cout << "Общая стоимость: " << totalCost << " руб.\n";
    cout << "Средняя цена: " << totalCost / totalQuantity << " руб.\n";
    cout << "Самая дешевая пластинка: " << minPrice << " руб.\n";
    cout << "Самая дорогая пластинка: " << maxPrice << " руб.\n";
}

// ================== MAIN ==================

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addDataMenu();
            break;
        case 2:
            showAllRecords();
            break;
        case 3:
            deleteDataMenu();
            break;
        case 5:
            showSummary();
            break;
        case 0:
            cout << "Завершение работы программы...\n";
            break;
        default:
            cout << "Пункт пока не реализован.\n";
        }

    } while (choice != 0);

    return 0;
}
