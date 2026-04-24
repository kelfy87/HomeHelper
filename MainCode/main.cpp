#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <cstdlib>

using namespace std;

void delay(double seconds) {
    this_thread::sleep_for(chrono::duration<double>(seconds));
}

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"

bool openSite(const string& url) {
    string command;

#ifdef _WIN32
    command = "cmd /c start \"\" \"" + url + "\"";
#elif __APPLE__
    command = "open \"" + url + "\"";
#elif __linux__
    command = "xdg-open \"" + url + "\"";
#else
    return false;
#endif

    int result = system(command.c_str());

    cout << "Команда: " << command << endl;
    cout << "Код возврата: " << result << endl;

    return result == 0;
}

void printHeader() {
    cout << CYAN << BOLD;
    cout << "=====================================\n";
    cout << "         HOME HELPER v1.0\n";
    cout << "=====================================\n";
    cout << RESET << endl;
}

void printMenu() {
    cout << BOLD << "Доступные команды:\n" << RESET;
    cout << "-------------------------------------\n";
    cout << "  [1] Обществознание\n";
    cout << "  [2] История\n";
    cout << "  [3] Английский\n";
    cout << "  [4] Химия (задачник)\n";
    cout << "-------------------------------------\n";
}

int main() {
    double wait1 = 0.3;
    
    double wait2 = 0.8;

    printHeader();
    delay(wait2);

    printMenu();
    delay(wait1);

    cout << YELLOW << "\nВведите номер команды -> " << RESET;

    int userInput;
    cin >> userInput;

    cout << endl;

    switch (userInput) {
    case 1: {
        cout << "Страница -> ";
        int userPage;
        cin >> userPage;

        string url =
            "https://gdz.ru/class-8/obshhestvoznanie/bogolyubov-gorodeckaya/"
            + to_string(userPage) + "-s/";

        cout << GREEN << "\nОткрываю...\n" << RESET;
        cout << url << endl;

        delay(wait2);

        if (!openSite(url)) {
            cout << RED << "Не удалось открыть ссылку.\n" << RESET;
        }
        break;
    }

    case 2: {
        cout << "Параграф или диапазон (например 1-2) -> ";
        string userPhp;
        cin >> userPhp;

        string url =
            "https://reshak.ru/otvet/reshebniki.php?otvet="
            + userPhp + "&predmet=medinsky_torkunov8";

        cout << GREEN << "\nОткрываю...\n" << RESET;
        cout << url << endl;

        delay(wait2);

        if (!openSite(url)) {
            cout << RED << "Не удалось открыть ссылку.\n" << RESET;
        }
        break;
    }

    case 3: {
        cout << "WB / SB -> ";
        string userBook;
        cin >> userBook;

        cout << "Страница -> ";
        int userPage;
        cin >> userPage;

        string url;

        if (userBook == "WB") {
            url = "https://gdz.ru/class-8/english/spotlight-workbook/"
                + to_string(userPage) + "-s/";
        } else if (userBook == "SB") {
            url = "https://gdz.ru/class-8/english/reshebnik-spotlight-8-angliyskiy-v-fokuse-vaulina-yu-e/"
                + to_string(userPage) + "-s/";
        } else {
            cout << RED << "Ошибка: WB или SB\n" << RESET;
            return 0;
        }

        cout << GREEN << "\nОткрываю...\n" << RESET;
        cout << url << endl;

        delay(wait2);

        if (!openSite(url)) {
            cout << RED << "Не удалось открыть ссылку.\n" << RESET;
        }
        break;
    }

    case 4: {
        cout << "Глава и номер (например 3 38) -> ";
        int userChapter, userNum;
        cin >> userChapter >> userNum;

        string url =
            "https://gdz.ru/class-8/himiya/sbornik-zadach-po-himii-8-klass-kuznecov/"
            + to_string(userChapter) + "-chapter-" + to_string(userNum) + "/";

        cout << GREEN << "\nОткрываю...\n" << RESET;
        cout << url << endl;

        delay(wait2);

        if (!openSite(url)) {
            cout << RED << "Не удалось открыть ссылку.\n" << RESET;
        }
        break;
    }

    default:
        cout << RED << "Неизвестная команда.\n" << RESET;
        break;
    }

    return 0;
}
