#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <regex>
#include <chrono>

// Функция чтения аркана по номеру
void readArcanaInfo(const std::wstring& filename, int arcanaNumber) {
    std::wifstream file(filename);
    file.imbue(std::locale("ru_RU.UTF-8"));

    if (!file) {
        std::wcerr << L"Не могу открыть файл " << filename << std::endl;
        return;
    }

    std::wstring line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        lineNum++;
        if (lineNum == arcanaNumber) {
            std::wcout << L"Аркан " << arcanaNumber << L": " << line << std::endl;
            return;
        }
    }

    std::wcerr << L"Аркан с номером " << arcanaNumber << L" не найден." << std::endl;
}

// Логируем дату в файл
void logDate(const std::wstring& filename, const std::wstring& date) {
    std::wofstream file(filename, std::ios::app);
    file.imbue(std::locale("ru_RU.UTF-8"));

    if (!file) {
        std::wcerr << L"Не могу открыть файл " << filename << std::endl;
        return;
    }

    file << date << std::endl;
    std::wcout << L"Записана дата: " << date << std::endl;
}

// Показать содержимое лога
void displayLog(const std::wstring& filename) {
    std::wifstream file(filename);
    file.imbue(std::locale("ru_RU.UTF-8"));

    if (!file) {
        std::wcerr << L"Не могу открыть файл " << filename << std::endl;
        return;
    }

    std::wstring line;
    while (std::getline(file, line)) {
        std::wcout << line << std::endl;
    }
}

// Проверка даты
bool isValidDate(const std::wstring& date) {
    std::wregex datePattern(LR"((\d{4})\.(\d{2})\.(\d{2}))");
    std::wsmatch result;

    if (!std::regex_match(date, result, datePattern)) {
        std::wcerr << L"Формат даты неверный." << std::endl;
        return false;
    }

    int year = std::stoi(result[1].str());
    int month = std::stoi(result[2].str());
    int day = std::stoi(result[3].str());

    if (month < 1 || month > 12) {
        std::wcerr << L"Месяц неверный." << std::endl;
        return false;
    }

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[1] = 29;
    }

    if (day < 1 || day > daysInMonth[month - 1]) {
        std::wcerr << L"День неверный." << std::endl;
        return false;
    }

    return true;
}

// Главное меню
void showMenu(const std::wstring& infoFile, const std::wstring& logFile) {
    while (true) {
        std::wcout << L"\nМеню:\n";
        std::wcout << L"1. Показать аркан\n";
        std::wcout << L"2. Записать дату\n";
        std::wcout << L"3. Показать лог\n";
        std::wcout << L"4. Выход\n";
        std::wcout << L"Введите номер: ";

        int choice;
        std::wcin >> choice;

        if (choice == 1) {
            int arcanaNumber;
            std::wcout << L"Номер аркана: ";
            std::wcin >> arcanaNumber;

            readArcanaInfo(infoFile, arcanaNumber);

        }
        else if (choice == 2) {
            std::wstring date;
            std::wcout << L"Введите дату (ГГГГ.ММ.ДД): ";
            std::wcin >> date;

            if (!isValidDate(date)) {
                continue;
            }

            logDate(logFile, date);

        }
        else if (choice == 3) {
            displayLog(logFile);

        }
        else if (choice == 4) {
            std::wcout << L"Выход из программы." << std::endl;
            break;

        }
        else {
            std::wcout << L"Неверный ввод. Попробуйте ещё." << std::endl;
        }
    }
}

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::wcin.imbue(std::locale("ru_RU.UTF-8"));
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    const std::wstring infoFile = L"info.txt";
    const std::wstring logFile = L"log.txt";

    showMenu(infoFile, logFile);

    return 0;
}
