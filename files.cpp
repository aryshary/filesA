#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
#include <conio.h>
#include <stack>

using namespace std;

void find(string path, string text) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!\n";
        return;
    }
    string line;
    int count = 0;
    while (getline(file, line)) {
        for (int i = 0; i <= line.length() - text.length(); i++) {
            int j = 0;
            while (j < text.length() && line[i + j] == text[j]) {
                j++;
            }
            if (j == text.length()) {
                count++;
                i += text.length() - 1;
            }
        }
    }
    cout << "Рядок " << text << "зустрічається " << count << " разів.\n";
    file.close();
}

void replace(string path, string textFind, string textReplace) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!\n";
        return;
    }
    string line, newLine;
    int replaced = 0;
    while (getline(file, line)) {
        int count = 0;
        for (int i = 0; i <= line.length() - textFind.length(); ) {
            int j = 0;
            while (j < textFind.length() && line[i + j] == textFind[j]) {
                j++;
            }
            if (j == textFind.length()) {
                line.replace(i, textFind.length(), textReplace);
                count++;
                i += textReplace.length();
            }
            else {
                i++;
            }
        }
        replaced += count;
        newLine += line + '\n';
    }
    file.close();
    ofstream outFile(path);
    outFile << newLine;
    outFile.close();
    cout << "Всього замінено: " << replaced << " разів у всьому файлі.\n";
}

void display(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << '\n';
    }
    file.close();
}

void reverse(string path) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл!\n";
        return;
    }
    stack<char> stack;
    char ch;
    while (file.get(ch)) {
        stack.push(ch);
    }
    file.close();
    ofstream outFile(path);
    while (!stack.empty()) {
        outFile << stack.top();
        stack.pop();
    }
    outFile.close();
    cout << "Вміст файлу перевернуто.\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string path;
    cout << "Введіть шлях до файлу: ";
    getline(cin, path);
    int choice;
    string textFind, textReplace;
    do {
        cout << "Оберіть опцію:\n";
        cout << "1. Пошук рядка\n";
        cout << "2. Заміна рядка\n";
        cout << "3. Виведення файлу\n";
        cout << "4. Перевертання вмісту файлу\n";
        cout << "0. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            cout << "Введіть рядок для пошуку : ";
            getline(cin, textFind);
            find(path, textFind);
            break;
        case 2:
            cout << "Введіть рядок для пошуку: ";
            getline(cin, textFind);
            cout << "Введіть рядок для заміни: ";
            getline(cin, textFind);
            replace(path, textFind, textReplace);
            break;
        case 3:
            display(path);
            break;
        case 4:
            reverse(path);
            break;
        case 0:
            cout << "Вихід з програми.\n";
            break;
        default:
            cout << "Неправильний вибір, спробуйте ще раз.\n";
            break;
        }
    } while (choice != 0);
    return 0;
}