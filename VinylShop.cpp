#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

// ==================================================
//                    СТРУКТУРЫ
// ==================================================

struct VinylRecord {
    int id;
    char artist[50];
    char album[50];
    char genre[30];
    int year;
    float price;
    int quantity;
};

struct Customer {
    int id;
    char name[50];
    char phone[20];
    char email[50];
    int purchasesCount;
    float totalSpent;
};

// ==================================================
//              ПРОТОТИПЫ ФУНКЦИЙ
// ==================================================

void showMainMenu();
void addDataMenu();
void deleteDataMenu();
void searchMenu();
void sortMenu();

// Пластинки
void addRecord();
void showAllRecords();
void deleteRecordById();
void showSummary();

// Клиенты
void addCustomer();
void showAllCustomers();

// Поиск / фильтрация
void searchByArtist();
void searchByGenre();
void filterByPrice();

// Сортировка
void sortByPrice();
void sortByYear();

// ==================================================
//                      МЕНЮ
// ==================================================

void showMainMenu() {
    system("cls");
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
        system("cls");
        cout << "=== ДОБАВЛЕНИЕ ДАННЫХ ===\n";
        cout << "1 - Добавить пластинку\n";
        cout << "2 - Добавить клиента\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) addRecord();
        if (choice == 2) addCustomer();

    } while (choice != 0);
}

void deleteDataMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== УДАЛЕНИЕ ДАННЫХ ===\n";
        cout << "1 - Удалить пластинку по ID\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) deleteRecordById();

    } while (choice != 0);
}

void searchMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== ПОИСК / ФИЛЬТРАЦИЯ ===\n";
        cout << "1 - Поиск по исполнителю\n";
        cout << "2 - Поиск по жанру\n";
        cout << "3 - Фильтр по цене\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: searchByArtist(); break;
        case 2: searchByGenre(); break;
        case 3: filterByPrice(); break;
        }

        if (choice != 0) system("pause");

    } while (choice != 0);
}

void sortMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== СОРТИРОВКА ===\n";
        cout << "1 - По цене (возрастание)\n";
        cout << "2 - По году выпуска (убывание)\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) sortByPrice();
        if (choice == 2) sortByYear();

        if (choice != 0) system("pause");

    } while (choice != 0);
}

// ==================================================
//                ПЛАСТИНКИ
// ==================================================

void addRecord() {
    VinylRecord r;

    cout << "\n--- Добавление пластинки ---\n";
    cout << "ID: ";
    cin >> r.id;
    cin.ignore();

    cout << "Исполнитель: ";
    cin.getline(r.artist, 50);

    cout << "Альбом: ";
    cin.getline(r.album, 50);

    cout << "Жанр: ";
    cin.getline(r.genre, 30);

    cout << "Год выпуска: ";
    cin >> r.year;

    cout << "Цена: ";
    cin >> r.price;

    cout << "Количество: ";
    cin >> r.quantity;

    ofstream file("records.bin", ios::binary | ios::app);
    file.write((char*)&r, sizeof(VinylRecord));
    file.close();

    cout << "Пластинка добавлена!\n";
    system("pause");
}

void showAllRecords() {
    system("cls");
    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    cout << "=== СПИСОК ПЛАСТИНОК ===\n";

    while (file.read((char*)&r, sizeof(VinylRecord))) {
        cout << r.id << " | " << r.artist << " | " << r.album
             << " | " << r.genre << " | " << r.year
             << " | " << r.price << " | " << r.quantity << endl;
    }

    file.close();
    system("pause");
}

void deleteRecordById() {
    int id;
    cout << "Введите ID: ";
    cin >> id;

    ifstream file("records.bin", ios::binary);
    ofstream temp("temp.bin", ios::binary);

    VinylRecord r;
    bool found = false;

    while (file.read((char*)&r, sizeof(VinylRecord))) {
        if (r.id != id)
            temp.write((char*)&r, sizeof(VinylRecord));
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("records.bin");
    rename("temp.bin", "records.bin");

    cout << (found ? "Удалено.\n" : "Не найдено.\n");
    system("pause");
}

// ==================================================
//                КЛИЕНТЫ
// ==================================================

void addCustomer() {
    Customer c;

    cout << "\n--- Добавление клиента ---\n";
    cout << "ID: ";
    cin >> c.id;
    cin.ignore();

    cout << "ФИО: ";
    cin.getline(c.name, 50);

    cout << "Телефон: ";
    cin.getline(c.phone, 20);

    cout << "Email: ";
    cin.getline(c.email, 50);

    cout << "Количество покупок: ";
    cin >> c.purchasesCount;

    cout << "Сумма покупок: ";
    cin >> c.totalSpent;

    ofstream file("customers.bin", ios::binary | ios::app);
    file.write((char*)&c, sizeof(Customer));
    file.close();

    cout << "Клиент добавлен!\n";
    system("pause");
}

void showAllCustomers() {
    system("cls");
    ifstream file("customers.bin", ios::binary);
    Customer c;

    cout << "=== КЛИЕНТЫ ===\n";
    while (file.read((char*)&c, sizeof(Customer))) {
        cout << c.id << " | " << c.name << " | "
             << c.phone << " | " << c.email
             << " | " << c.purchasesCount
             << " | " << c.totalSpent << " руб.\n";
    }

    file.close();
    system("pause");
}

// ==================================================
//            ПОИСК / ФИЛЬТРАЦИЯ
// ==================================================

void searchByArtist() {
    char artist[50];
    cin.ignore();
    cout << "Исполнитель: ";
    cin.getline(artist, 50);

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(VinylRecord)))
        if (strcmp(r.artist, artist) == 0)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;

    file.close();
}

void searchByGenre() {
    char genre[30];
    cin.ignore();
    cout << "Жанр: ";
    cin.getline(genre, 30);

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(VinylRecord)))
        if (strcmp(r.genre, genre) == 0)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;

    file.close();
}

void filterByPrice() {
    float minP, maxP;
    cout << "Мин цена: ";
    cin >> minP;
    cout << "Макс цена: ";
    cin >> maxP;

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(VinylRecord)))
        if (r.price >= minP && r.price <= maxP)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;

    file.close();
}

// ==================================================
//                  СОРТИРОВКА
// ==================================================

void sortByPrice() {
    VinylRecord arr[100];
    int n = 0;

    ifstream file("records.bin", ios::binary);
    while (file.read((char*)&arr[n], sizeof(VinylRecord))) n++;
    file.close();

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].price > arr[j + 1].price)
                swap(arr[j], arr[j + 1]);

    for (int i = 0; i < n; i++)
        cout << arr[i].artist << " | " << arr[i].album << " | " << arr[i].price << endl;
}

void sortByYear() {
    VinylRecord arr[100];
    int n = 0;

    ifstream file("records.bin", ios::binary);
    while (file.read((char*)&arr[n], sizeof(VinylRecord))) n++;
    file.close();

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].year < arr[j + 1].year)
                swap(arr[j], arr[j + 1]);

    for (int i = 0; i < n; i++)
        cout << arr[i].artist << " | " << arr[i].album << " | " << arr[i].year << endl;
}

// ==================================================
//              СВОДНАЯ ИНФОРМАЦИЯ
// ==================================================

void showSummary() {
    system("cls");

    VinylRecord r;
    int totalQty = 0;
    float totalCost = 0;

    ifstream file("records.bin", ios::binary);
    while (file.read((char*)&r, sizeof(VinylRecord))) {
        totalQty += r.quantity;
        totalCost += r.price * r.quantity;
    }
    file.close();

    cout << "=== СКЛАД ===\n";
    cout << "Всего пластинок: " << totalQty << endl;
    cout << "Стоимость склада: " << totalCost << " руб.\n\n";

    Customer c;
    ifstream cfile("customers.bin", ios::binary);

    cout << "=== КЛИЕНТЫ ===\n";
    while (cfile.read((char*)&c, sizeof(Customer))) {
        cout << c.name << " купил "
             << c.purchasesCount
             << " пластинок на сумму "
             << c.totalSpent << " руб.\n";
    }
    cfile.close();

    system("pause");
}

// ==================================================
//                      MAIN
// ==================================================

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1: addDataMenu(); break;
        case 2: showAllRecords(); break;
        case 3: deleteDataMenu(); break;
        case 4: searchMenu(); break;
        case 5: showSummary(); break;
        case 6: sortMenu(); break;
        case 0: cout << "Выход...\n"; break;
        default: cout << "Неверный пункт!\n"; system("pause");
        }

    } while (choice != 0);

    return 0;
}
