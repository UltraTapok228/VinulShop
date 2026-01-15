#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

// СТРУКТУРЫ

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
};

// типа функции(пока что)

void showMainMenu();
void addDataMenu();

// Пластинки
void addRecord();

// менюшка

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

// ================== ФУНКЦИИ ==================

void addRecord() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    VinylRecord record;

    cout << "\n--- Добавление пластинки ---\n";
    cout << "ID: ";
    cin >> record.id;

    cin.ignore(); // очистка буфера

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

    ofstream file("records.dat", ios::binary | ios::app);
    if (!file) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    file.write((char*)&record, sizeof(VinylRecord));
    file.close();

    cout << "Пластинка успешно добавлена!\n";
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
        case 0:
            cout << "\nЗавершение работы программы...\n";
            break;
        default:
            cout << "\nДанный пункт пока не реализован.\n";
        }

    } while (choice != 0);

    return 0;
}
