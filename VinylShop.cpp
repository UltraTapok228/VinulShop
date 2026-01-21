#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <iomanip>

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
void showCustomers();

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
    cout << "=============================================\n";
    cout << "        МАГАЗИН ВИНИЛОВЫХ ПЛАСТИНОК           \n";
    cout << "=============================================\n";
    cout << "1 - Добавить данные\n";
    cout << "2 - Просмотреть данные\n";
    cout << "3 - Удалить данные\n";
    cout << "4 - Поиск / фильтрация\n";
    cout << "5 - Сводная информация\n";
    cout << "6 - Сортировка\n";
    cout << "0 - Выход\n";
    cout << "---------------------------------------------\n";
    cout << "Ваш выбор: ";
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

        if (choice == 1)
            deleteRecordById();

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

        if (choice == 1) searchByArtist();
        if (choice == 2) searchByGenre();
        if (choice == 3) filterByPrice();

        if (choice != 0) system("pause");

    } while (choice != 0);
}

void sortMenu() {
    int choice;
    do {
        system("cls");
        cout << "=== СОРТИРОВКА ===\n";
        cout << "1 - По цене\n";
        cout << "2 - По году выпуска\n";
        cout << "0 - Назад\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) sortByPrice();
        if (choice == 2) sortByYear();

        if (choice != 0) system("pause");

    } while (choice != 0);
}

// ==================================================
//              РАБОТА С ПЛАСТИНКАМИ
// ==================================================

void addRecord() {
    VinylRecord r;

    cout << "\nID: ";
    cin >> r.id;
    cin.ignore();

    cout << "Исполнитель: ";
    cin.getline(r.artist, 50);

    cout << "Альбом: ";
    cin.getline(r.album, 50);

    cout << "Жанр: ";
    cin.getline(r.genre, 30);

    cout << "Год: ";
    cin >> r.year;

    cout << "Цена: ";
    cin >> r.price;

    cout << "Количество: ";
    cin >> r.quantity;

    ofstream file("records.bin", ios::binary | ios::app);
    file.write((char*)&r, sizeof(r));
    file.close();

    cout << "Пластинка добавлена.\n";
    system("pause");
}

void showAllRecords() {
    system("cls");
    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    cout << left
         << setw(5)  << "ID"
         << setw(20) << "Исполнитель"
         << setw(25) << "Альбом"
         << setw(15) << "Жанр"
         << setw(8)  << "Год"
         << setw(10) << "Цена"
         << setw(10) << "Кол-во"
         << endl;

    cout << string(93, '-') << endl;

    while (file.read((char*)&r, sizeof(r))) {
        cout << left
             << setw(5)  << r.id
             << setw(20) << r.artist
             << setw(25) << r.album
             << setw(15) << r.genre
             << setw(8)  << r.year
             << setw(10) << fixed << setprecision(2) << r.price
             << setw(10) << r.quantity
             << endl;
    }

    file.close();
    system("pause");
}

void deleteRecordById() {
    // очистка экрана
    system("cls");

    // Показываем таблицу перед удалением
    showAllRecords();

    int id;
    cout << "\nВведите ID для удаления: ";
    cin >> id;

    ifstream file("records.bin", ios::binary);
    ofstream temp("temp.bin", ios::binary);

    VinylRecord r;
    bool found = false;

    while (file.read((char*)&r, sizeof(r))) {
        if (r.id != id)
            temp.write((char*)&r, sizeof(r));
        else
            found = true;
    }
    

    file.close();
    temp.close();

    remove("records.bin");
    rename("temp.bin", "records.bin");

    cout << (found ? "Запись удалена.\n" : "ID не найден.\n");
    system("pause");
}

// ==================================================
//                    КЛИЕНТЫ
// ==================================================

void addCustomer() {
    Customer c;

    cout << "\nID клиента: ";
    cin >> c.id;
    cin.ignore();

    cout << "ФИО: ";
    cin.getline(c.name, 50);

    cout << "Телефон: ";
    cin.getline(c.phone, 20);

    cout << "Email: ";
    cin.getline(c.email, 50);

    cout << "Кол-во покупок: ";
    cin >> c.purchasesCount;

    cout << "Сумма покупок: ";
    cin >> c.totalSpent;

    ofstream file("customers.bin", ios::binary | ios::app);
    file.write((char*)&c, sizeof(c));
    file.close();

    cout << "Клиент добавлен.\n";
    system("pause");
}

void showCustomers() {
    ifstream file("customers.bin", ios::binary);
    Customer c;

    cout << left
         << setw(5)  << "ID"
         << setw(25) << "ФИО"
         << setw(10) << "Покупки"
         << setw(15) << "Сумма"
         << endl;

    cout << string(55, '-') << endl;

    while (file.read((char*)&c, sizeof(c))) {
        cout << left
             << setw(5)  << c.id
             << setw(25) << c.name
             << setw(10) << c.purchasesCount
             << setw(15) << fixed << setprecision(2) << c.totalSpent
             << endl;
    }

    file.close();
}

// ==================================================
//                СВОДНАЯ ИНФОРМАЦИЯ
// ==================================================

void showSummary() {
    system("cls");

    cout << "=== КЛИЕНТЫ ===\n";
    showCustomers();

    system("pause");
}

// ==================================================
//              ПОИСК / ФИЛЬТРАЦИЯ
// ==================================================

void searchByArtist() {
    char artist[50];
    cin.ignore();
    cout << "Введите исполнителя: ";
    cin.getline(artist, 50);

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(r))) {
        if (strcmp(r.artist, artist) == 0)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;
    }

    file.close();
}

void searchByGenre() {
    char genre[30];
    cin.ignore();
    cout << "Введите жанр: ";
    cin.getline(genre, 30);

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(r))) {
        if (strcmp(r.genre, genre) == 0)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;
    }

    file.close();
}

void filterByPrice() {
    float minP, maxP;
    cout << "Мин. цена: ";
    cin >> minP;
    cout << "Макс. цена: ";
    cin >> maxP;

    ifstream file("records.bin", ios::binary);
    VinylRecord r;

    while (file.read((char*)&r, sizeof(r))) {
        if (r.price >= minP && r.price <= maxP)
            cout << r.artist << " | " << r.album << " | " << r.price << endl;
    }

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
//                      MAIN
// ==================================================

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;
    do {
        showMainMenu();
        cin >> choice;

        if (choice == 1) addDataMenu();
        if (choice == 2) showAllRecords();
        if (choice == 3) deleteDataMenu();
        if (choice == 4) searchMenu();
        if (choice == 5) showSummary();
        if (choice == 6) sortMenu();

    } while (choice != 0);

    return 0;
}
