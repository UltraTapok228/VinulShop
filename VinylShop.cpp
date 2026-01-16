#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

// =======================================================
//                     СТРУКТУРЫ
// =======================================================

// Структура для хранения информации о виниловой пластинке
struct VinylRecord {
    int id;                 // Уникальный идентификатор
    char artist[50];        // Исполнитель
    char album[50];         // Название альбома
    char genre[30];         // Жанр
    int year;               // Год выпуска
    float price;            // Цена
    int quantity;           // Количество на складе
};

// Структура клиента (пока не используем, будет позже)
struct Customer {
    int id;
    char name[50];
    char phone[20];
    char email[50];
    int purchasesCount;
};

// =======================================================
//               ПРОТОТИПЫ ФУНКЦИЙ
// =======================================================

// Главное меню
void showMainMenu();

// Подменю
void addDataMenu();
void deleteDataMenu();
void searchMenu();

// Пластинки
void addRecord();
void showAllRecords();
void deleteRecordById();

// Поиск
void searchByArtist();
void searchByGenre();
void searchByPrice();

// =======================================================
//                       МЕНЮ
// =======================================================

// Главное меню программы
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

// Меню добавления данных
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

// Меню удаления данных
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

// Меню поиска
void searchMenu() {
    int choice;
    do {
        cout << "\n=== ПОИСК ПЛАСТИНОК ===\n";
        cout << "1 - По исполнителю\n";
        cout << "2 - По жанру\n";
        cout << "3 - По диапазону цены\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            searchByArtist();
            break;
        case 2:
            searchByGenre();
            break;
        case 3:
            searchByPrice();
            break;
        case 0:
            break;
        default:
            cout << "Ошибка! Неверный выбор.\n";
        }
    } while (choice != 0);
}

// =======================================================
//                  ОСНОВНЫЕ ФУНКЦИИ
// =======================================================

// Добавление новой пластинки
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

    ofstream file("records.bin", ios::binary | ios::app);
    file.write((char*)&record, sizeof(VinylRecord));
    file.close();

    cout << "Пластинка успешно добавлена!\n";
}

// Просмотр всех пластинок
void showAllRecords() {

    ifstream file("records.bin", ios::binary);
    VinylRecord record;
    bool empty = true;

    cout << "\n=== СПИСОК ПЛАСТИНОК ===\n";

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        empty = false;
        cout << record.id << " | "
            << record.artist << " | "
            << record.album << " | "
            << record.genre << " | "
            << record.year << " | "
            << record.price << " | "
            << record.quantity << "\n";
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
    int id;
    bool found = false;

    cout << "Введите ID для удаления: ";
    cin >> id;

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        if (record.id != id) {
            temp.write((char*)&record, sizeof(VinylRecord));
        }
        else {
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

// =======================================================
//                     ПОИСК
// =======================================================

// Поиск по исполнителю
void searchByArtist() {

    char artist[50];
    VinylRecord record;
    bool found = false;

    cin.ignore();
    cout << "Введите исполнителя: ";
    cin.getline(artist, 50);

    ifstream file("records.bin", ios::binary);

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        if (strcmp(record.artist, artist) == 0) {
            cout << record.id << " | " << record.album << " | " << record.price << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "Совпадений не найдено.\n";

    file.close();
}

// Поиск по жанру
void searchByGenre() {

    char genre[30];
    VinylRecord record;
    bool found = false;

    cin.ignore();
    cout << "Введите жанр: ";
    cin.getline(genre, 30);

    ifstream file("records.bin", ios::binary);

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        if (strcmp(record.genre, genre) == 0) {
            cout << record.id << " | " << record.artist << " | " << record.album << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "Совпадений не найдено.\n";

    file.close();
}

// Поиск по диапазону цены
void searchByPrice() {

    float minPrice, maxPrice;
    VinylRecord record;
    bool found = false;

    cout << "Минимальная цена: ";
    cin >> minPrice;
    cout << "Максимальная цена: ";
    cin >> maxPrice;

    ifstream file("records.bin", ios::binary);

    while (file.read((char*)&record, sizeof(VinylRecord))) {
        if (record.price >= minPrice && record.price <= maxPrice) {
            cout << record.id << " | " << record.artist << " | " << record.price << "\n";
            found = true;
        }
    }

    if (!found)
        cout << "Совпадений не найдено.\n";

    file.close();
}

// =======================================================
//                        MAIN
// =======================================================

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
        case 4:
            searchMenu();
            break;
        case 0:
            cout << "\nЗавершение работы программы...\n";
            break;
        default:
            cout << "Пункт меню не реализован.\n";
        }

    } while (choice != 0);

    return 0;
}
