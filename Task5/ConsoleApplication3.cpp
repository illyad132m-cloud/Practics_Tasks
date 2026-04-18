#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

struct Site {
    string name;
    string specialization;
    int year;
    int visitors;
    string owner;
};
const string FILENAME = "sites_data.txt";
void addSite() {
    Site newSite;
    cout << "\n--- ДОДАВАННЯ НОВОГО САЙТУ ---" << endl;
    cout << "Введіть назву сайту: ";
    getline(cin, newSite.name);
    cout << "Введіть спеціалізацію: ";
    getline(cin, newSite.specialization);
    cout << "Введіть рік заснування: ";
    cin >> newSite.year;
    cout << "Введіть середню кількість відвідувачів: ";
    cin >> newSite.visitors;
    cin.ignore();
    cout << "Введіть ім'я власника: ";
    getline(cin, newSite.owner);
    ofstream outFile(FILENAME, ios::app);
    if (outFile.is_open()) {
        outFile << newSite.name << endl;
        outFile << newSite.specialization << endl;
        outFile << newSite.year << endl;
        outFile << newSite.visitors << endl;
        outFile << newSite.owner << endl;
        outFile.close();
        cout << "Сайт успішно збережено у файл!" << endl;
    }
    else {
        cout << "Помилка відкриття файлу для запису!" << endl;
    }
}
void viewAllSites() {
    ifstream inFile(FILENAME);
    if (!inFile.is_open()) {
        cout << "\nФайл ще порожній або не існує. Додайте спочатку сайт." << endl;
        return;
    }
    cout << "\n--- СПИСОК УСІХ САЙТІВ ---" << endl;
    Site temp;
    int count = 1;
    while (getline(inFile, temp.name)) {
        getline(inFile, temp.specialization);
        inFile >> temp.year;
        inFile >> temp.visitors;
        inFile.ignore();
        getline(inFile, temp.owner);

        cout << count << ". Назва: " << temp.name << " | Спец: " << temp.specialization
            << " | Рік: " << temp.year << " | Відвідувачі: " << temp.visitors
            << " | Власник: " << temp.owner << endl;
        count++;
    }

    inFile.close();
}
void showTop3LowestVisitors() {
    ifstream inFile(FILENAME);

    if (!inFile.is_open()) {
        cout << "\nФайл порожній. Немає що аналізувати." << endl;
        return;
    }
    vector<Site> allSites;
    Site temp;
    while (getline(inFile, temp.name)) {
        getline(inFile, temp.specialization);
        inFile >> temp.year;
        inFile >> temp.visitors;
        inFile.ignore();
        getline(inFile, temp.owner);

        allSites.push_back(temp);
    }
    inFile.close();

    int n = allSites.size();
    if (n == 0) {
        cout << "Немає записів." << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (allSites[j].visitors > allSites[j + 1].visitors) {
                swap(allSites[j], allSites[j + 1]);
            }
        }
    }
    cout << "\n--- ТОП-3 САЙТИ З НАЙМЕНШОЮ ВІДВІДУВАНІСТЮ ---" << endl;
    int limit = 3;
    if (n < 3) {
        limit = n;
    }

    for (int i = 0; i < limit; i++) {
        cout << i + 1 << ". " << allSites[i].name
            << " (Відвідувачів: " << allSites[i].visitors << ")" << endl;
    }
}
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice = 0;
    while (choice != 4) {
        cout << "\n===============================" << endl;
        cout << "        ГОЛОВНЕ МЕНЮ" << endl;
        cout << "===============================" << endl;
        cout << "1. Додати новий сайт" << endl;
        cout << "2. Переглянути всі сайти" << endl;
        cout << "3. Знайти 3 найменш популярні сайти" << endl;
        cout << "4. Вийти з програми" << endl;
        cout << "Оберіть дію (1-4): ";

        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            addSite();
        }
        else if (choice == 2) {
            viewAllSites();
        }
        else if (choice == 3) {
            showTop3LowestVisitors();
        }
        else if (choice == 4) {
            cout << "Програма завершена. До побачення!" << endl;
        }
        else {
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    }

    return 0;
}