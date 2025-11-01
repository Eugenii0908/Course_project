#include "interface_lib.h"
#include "Priority_queue_lib.h"
#include <fstream>
#include <string>

// Тексты меню
const string welcome_message = "Данная программа предназначена для управления очередью на посадку в самолет.\n"
"Здесь можно реализовать вставку и извлечение из очереди, а также отображение информации о всех пассажирах.\n\n";
const string main_menu_text = "-Для перемещения по пунктам используйте стрелки вверх/вниз\n"
"-Для подтверждения выбора нажмите ENTER или стрелку вправо\n-Для выхода в главное меню нажмите ESCAPE\n-Для перехода в меню назад нажмите стрелку влево\n"
"-Для выхода из программы нажмите в главном меню на ESCAPE\n\n"
"Выберите операцию, которую хотите выполнить:\n";
string main_menu_point[] = { "1. Добавление пассажиров в очередь.", "2. Извлечение первого пассажира из очереди.",
"3. Удаление всей очереди.", "4. Отображение информации о пассажирах.", "5. Сохранение информации в файл." };
const string menu1_add_text = "Вы хотите добавить пассажиров из файла или вручную?\n";
string menu1_add_point[] = { "1. Добавить вручную.", "2. Загрузить из файла." };
const string menu1_1_add_text = "Введите данные по указанным ниже полям. Для подтверждения ввода нажмите ENTER или стрелку вправо.\n"
"Для выхода в главное меню нажмите ESCAPE, для перехода в меню назад нажмите стрелку влево.\n"
"Обращаем внимание, если вы не ввели все поля, данные последнего пассажира не сохранятся!\n"
"ФИО может состоять только из латинских и кириллических букв, пробелов и дефисов.\nНомер места должен быть введен в формате <число><буква>, например: '2F'.\n\n";
const string menu1_2_add_text = "Файл должен находиться в папке с программой. Неверно записанные пассажиры игнорируются.\n\nВыберите файл:\n";
const string menu4_search_text = "Выберите тип отображения пассажиров:\n";
string menu4_search_point[] = { "1. Поиск пассажиров по введенным данным.", "2. Поиск пассажиров с указанным приоритетом." , "3. Отображение всей очереди."};
const string menu4_1_search_text = "Введите ключевое слово или его часть для поиска по всем пассажирам:\n";
const string menu4_2_search_text = "Выберите приоритет, по которому хотите найти пассажиров:\n";
string menu4_2_search_point[] = { "1. Эконом-класс.", "2. Обладатели серебряных карт.", "3. Льготные пассажиры.",
"4. Бизнес-класс.", "5. Особый приоритет." };
const string menu4_2_1_search_text = "Выборка пассажиров по выбранному приоритету:\n\n";
const string menu4_3_search_text = "Полный список пассажиров в очереди:\n\n";
const string menu5_1_search_text = "Введите название файла, в который хотите вывести данные.\n"
"При вводе названия без расширения автоматически добавляется расширение txt.\nПри вводе названия файла и пути к нему,"
" он сохранится по указанному пути,\nиначе - в папке с программой.\n\n-Спецсимволы \\ / :*? \"<>| не разрешены, их ввод игнорируется\n\n";
const string menu5_1_1search_text = "Полный список пассажиров в очереди:\n\n";

// Функция ручного ввода данных
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int manual_add();
// Настройка меню
void setup_menu();
// Функция проверки на специальные символы в имени файла
// 0 - нет спецсимволов; 1 - есть
bool check_special_sym(char symbol);
// Функция обработки backspace (удаление последнего символа)
void backspace(string& string);
// Чтение слова с клавиатуры с обработкой специальных клавиш
// 0 - ENTER; -1 - стрелка влево; -2 - ESCAPE
int read_word(string& word);
// Функция ввода данных из файла
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int file_add();
// Функция извлечения первого в очереди пассажира
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int passanger_del();
// Функция удаления всей очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int queu_del();
// Функция поиска по совпадению
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int matching_search();
// Функция отображения сообщения в случае пустой очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int queue_is_empty();
// Фукнция поиска по приоритету
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int priority_search();
// Функция отображения всей очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int show_all();
// Функция ввода названия файла
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int write_name_file();
// Функция обработки введенных слов
// 0 - ENTER; -1 - стрелка влево; -2 - ESCAPE
int check_word(string& word, int field);
// Функция проверки, состоит ли строка только из пробелов
bool only_space(string word);
// Проверяет, является ли символ буквой (русской/английской) или разрешённым символом
bool is_alphabetic(char symbol);
// Проверяет, состоит ли строка только из букв и разрешённых символов
bool all_is_alphabetic(string word);
// Проверяет, является ли символ цифрой
bool is_digit(char symbol);
// Проверяет, состоит ли строка только из цифр
bool all_is_digit(string word);

int main() {
    setup_menu();
    cycle();
}

// Настройка меню
void setup_menu() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << welcome_message;
    system("pause");
    system("cls");
    // Создаем главное меню
    root = create_node("main_menu", main_menu_text, main_menu_point, size(main_menu_point), nullptr);
    // Создаем все подменю (потомки)
    add_node("main_menu", "1", menu1_add_text, menu1_add_point, size(menu1_add_point), nullptr);
    add_node("1", "1.1", menu1_1_add_text, nullptr, 0, manual_add);
    add_node("1", "1.2", menu1_2_add_text, nullptr, 0, file_add);
    add_node("main_menu", "2", "", nullptr, 0, passanger_del);
    add_node("main_menu", "3", "", nullptr, 0, queu_del);
    add_node("main_menu", "4", menu4_search_text, menu4_search_point, size(menu4_search_point), queue_is_empty);
    add_node("4", "4.1", menu4_1_search_text, nullptr, 0, matching_search);
    add_node("4", "4.2", menu4_2_search_text, nullptr, 0, priority_search);
    add_node("4.2", "4.2.1", menu4_2_1_search_text, nullptr, 0, nullptr);
    add_node("4", "4.3", menu4_3_search_text, nullptr, 0, show_all);
    add_node("main_menu", "5", menu5_1_search_text, nullptr, 0, write_name_file);
}

// Функция ручного ввода данных
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int manual_add() {
    system("cls");
    cout << menu1_1_add_text;   // Вывод текста меню
    string line, name, num_place, service_class;
    int priority;
    cout << "Введите ФИО через пробел:  ";
    int is_read = 0;
    int num_field = 0;
    // Пока не нажат ESCAPE или стрелка влево
    while (is_read == 0) {
        // Считываем строку
        line = "";
        is_read = check_word(line, num_field);
        // Если нажат ESCAPE или стрелка влево, выходим
        if (is_read == -1 or is_read == -2)
            break;
        // Если нажат ENTER
        if (is_read == 0) {
            // Игнорируем, если строка пустая
            if (line == "")
                continue;
            // Переход к следующему полю
            if (num_field == 0) {
                name = line;
                num_field++;
            }
            else if (num_field == 1) {
                num_place = line;
                num_field++;
            }
        }
        // Первое поле
        if (num_field == 0)
            cout << "Введите ФИО через пробел:  ";
        // Второе поле
        if (num_field == 1)
            cout << "\nВведите номер места:  ";
        // Третье поле
        if (num_field == 2) {
            // Выбор третьего поля
            int position = 0;
            string text = menu1_1_add_text + "Введите ФИО через пробел:  " + name + "\nВведите номер места:  " + num_place + "\nВыберите класс обслуживания:\n";
            dynamic_menu(position, menu4_2_search_point, size(menu4_2_search_point), text);
            priority = position;
            switch (position) {
            case 0:
                service_class = "Эконом-класс";
                break;
            case 1:
                service_class = "Обладатели серебряных карт";
                break;
            case 2:
                service_class = "Льготные пассажиры";
                break;
            case 3:
                service_class = "Бизнес-класс";
                break;
            case 4:
                service_class = "Особый приоритет";
                break;
            default:
                return position;
            };
            num_field = 0;
            // Добавление в структуру
            int result = insert_queue(priority, name, num_place, service_class);
            if (result == -1)
                cout << "\nПассажир с таким именем уже существует. Введите другого пассажира.\n\n";
            else if (result == -2)
                cout << "\nЭто место уже занято. Выберите другое.\n\n";
            else if (result == -3)
                cout << "\nПассажир с таким именем существует и введенное место уже занято.\n\n";
            else 
                cout << "\nПассажир успешно добавлен в очередь.\n\n";
            system("pause");
            system("cls");
            cout << menu1_1_add_text + "Введите ФИО через пробел:  ";
        }
    }
    return is_read;
}

// Функция ввода данных из файла
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int file_add() {
    system("cls");
    cout << menu1_2_add_text;   // Вывод текста меню
    int position = 0;
    while (position > -1) {
        bool is_added = FALSE;
        string* file_names;
        int num_files;

        // Получаем список txt-файлов в директории программы
        string program_dir = get_program_dir();
        file_names = list_files(program_dir, num_files);
        if (file_names == nullptr) {
            cout << "\nВ папке нет файлов. Добавьте нужные файлы и вернитесь в это меню.\n\n";
            system("pause");
            return -1;
        }
        // Пользователь выбирает файл
        dynamic_menu(position, file_names, num_files, menu1_2_add_text);
        if (position < 0)
            return position;

        // Формируем полный путь к файлу
        program_dir = program_dir + "\\" + file_names[position];
        ifstream fin(program_dir);

        if (!fin.is_open()) {  // Если не удалось открыть файл
            cout << "\nНе удалость открыть файл. Повторите еще раз или используйте дугой.\n\n";
            system("pause");
            continue;
        }

        // Чтение данных из файла
        while (!fin.eof()) {
            string line, name, num_place, service_class;
            int priority;
            getline(fin, name);
            // Проверка имени
            if (name == "")
                continue;
            if (!all_is_alphabetic(name))
                continue;
            if (only_space(name))
                continue;
            getline(fin, num_place);
            // Проверка номера места
            if (num_place == "")
                continue;
            if (!is_alphabetic(num_place[num_place.length() - 1]) or num_place[num_place.length() - 1] == ' ' or num_place[num_place.length() - 1] == '-')
                continue;
            string temp = num_place;
            temp.erase(temp.length() - 1);
            if (!all_is_digit(temp))
                continue;
            getline(fin, service_class);
            if (service_class == "")
                continue;
            if (service_class == "Эконом-класс")
                priority = 0;
            else if (service_class == "Обладатели серебряных карт")
                priority = 1;
            else if (service_class == "Льготные пассажиры")
                priority = 2;
            else if (service_class == "Бизнес-класс")
                priority = 3;
            else if (service_class == "Особый приоритет")
                priority = 4;
            else
                continue;
            if (insert_queue(priority, name, num_place, service_class) == 0)
                is_added = TRUE;
        }

        if (is_added == FALSE) {  // Если не было добавлено новых данных
            cout << "\nДанные в файле отсутствуют, некорректны или все пассажиры из этого файла уже были добавлены.\n\n";
            system("pause");
            continue;
        }

        // Выводим результат загрузки
        system("cls");
        cout << "Данные загружены успешно!\n\nТекущие данные:\n\n";
        pr_queue_show(cout);
        system("pause");
        return -2;
    }
}

// Функция извлечения первого в очереди пассажира
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int passanger_del() {
    string name;
    // Проверка на наличие очереди
    if (remove_first(name))
        cout << "\n\nВ очереди нет пассажиров.\n\n";
    else
        cout << "\n\nПассажир с именем: " << name << " успешно извлечен из очереди.\n\n";
    system("pause");
    // Сохраняем положение указателя
    return -3;
}

// Функция удаления всей очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int queu_del() {
    // Проверка на наличие очереди
    if (queue_empty()) {
        cout << "\n\nВ очереди нет пассажиров.\n\n";
        system("pause");
        return -3;
    }
    else {
        string warning = "Вы уверены, что хотите удалить всю очередь? Рекомендуем сохранить в файл перед удалением.\n";
        // Уточнение у пользователя об удалении
        if (no_or_yes(warning) == 1) {
            pr_queue_clear();
            cout << "\n\nВся очередь успешно удалена.\n\n";
        }
        else
            return -2;
    }
    system("pause");
    // Возвращаемся в главное меню
    return -2;
}

// Функция отображения сообщения в случае пустой очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int queue_is_empty() {
    if (queue_empty()) {
        cout << "\n\nВ очереди нет пассажиров.\n\n";
        system("pause");
        return -3;
    }
}

// Функция поиска по совпадению
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int matching_search() {
    system("cls");
    cout << menu4_1_search_text;   // Вывод текста меню
    string line;
    int is_read = 0;
    int num_field = 0;
    // Пока не нажат ESCAPE или стрелка влево
    while (is_read == 0) {
        // Считываем строку
        line = "";
        is_read = read_word(line);
        // Если нажат ESCAPE или стрелка влево, выходим
        if (is_read == -1 or is_read == -2)
            break;
        // Если нажат ENTER
        if (is_read == 0) {
            // Игнорируем, если строка пустая
            if (line == "")
                continue;
            cout << "\n\n";
            if (find_matches(line) == 0)
                cout << "Совпадений не найдено.\n\n";
        }
    }
    return is_read;
}

// Фукнция поиска по приоритету
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int priority_search() {
    int position = 0;
    while (position >= 0) {
        dynamic_menu(position, menu4_2_search_point, size(menu4_2_search_point), menu4_2_search_text);
        // Выходим по навигационным клавишам
        if (position < 0)
            return position;
        cout << "\n";
        if (!find_matches(position)) {
            cout << "Пассажиров с таким приоритетом нет.\n\n";
        }
        system("pause");
    }
}

// Функция отображения всей очереди
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int show_all() {
    system("cls");
    cout << menu4_3_search_text;
    pr_queue_show(cout);
    system("pause");
    return -1;
}

// Функция ввода названия файла
// -1 - выход на меню назад; -2 - выход в главное меню; -3 выход в главное меню с сохранением положения стрелки (для сообщений)
int write_name_file() {
    // Проверка на наличие очереди
    if (queue_empty()) {
        cout << "\n\nВ очереди нет пассажиров.\n\n";
        system("pause");
        return -3;
    }
    system("cls");
    cout << menu5_1_search_text;
    string filename;
    bool wrong_entry = false;
    while (!wrong_entry) {
        wrong_entry = true;
        int result = read_word(filename);
        if (result < 0)
            return result;
        // Проверка длины имени файла
        if (filename.length() >= 255) {
            cout << "Название слишком большое. Введите более короткое.\n";
            filename.clear();
            wrong_entry = false;
            continue;
        }
        // Проверка на пустое имя
        if (filename.length() == 0) {
            cout << "Название не может быть пустым. Введите другое.\n";
            filename.clear();
            wrong_entry = false;
            continue;
        }
        // Проверка на имя из пробелов
        if (only_space(filename)) {
            cout << "\nНазвание не может состоять только из пробелов. Введите другое.\n";
            filename.clear();
            wrong_entry = false;
            continue;
        }
        // Добавляем расширение .txt, если его нет
        if (filename.find(".txt") == filename.npos) filename += ".txt";

        // Пытаемся открыть файл
        ofstream fout(filename);
        if (!fout.is_open()) {
            cout << "Не удалость открыть или создать файл. Попробуйте еще раз.\n";
            filename.clear();
            wrong_entry = false;
            continue;
        }
        // Вывод данных
        pr_queue_show(fout);
        cout << "\nДанные были успешно сохранены в файл " + filename << "\n\n";
        system("pause");
        return -2;
    }
}

// Функция проверки на специальные символы в имени файла
// 0 - нет спецсимволов; 1 - есть
bool check_special_sym(char symbol) {
    return (symbol == '\\' or symbol == '/' or symbol == ':' or symbol == '*' or symbol == '?' or symbol == '\"' or symbol == '<' or symbol == '>' or symbol == '|');
}

// Функция обработки backspace (удаление последнего символа)
void backspace(string& string) {
    if (string == "") return; // Если строка пустая, игнорируем backspace
    printf("\b \b");  // Удаление символа из консоли
    string.erase((string.length()) - 1, 1);  // Удаление символа из строки
    return;
}

// Чтение слова с клавиатуры с обработкой специальных клавиш
// 0 - ENTER; -1 - стрелка влево; -2 - ESCAPE
int read_word(string& word) {
    char symbol = 0;
    while (symbol != ENTER) {
        symbol = _getch();

        // Обработка стрелок
        if (_kbhit()) {
            char arrow = _getch();
            if (arrow == 75)  // Стрелка влево - выход
                return -1;
            if (arrow == 77) {  // Стрелка вправо - подтверждение
                break;
            }
            else
                continue;
        }
        if (symbol == TAB) continue;  // Игнорируем Tab
        if (symbol == ENTER) break;   // Enter - завершение ввода
        if (symbol == ESCAPE) return -2;  // Escape - выход
        if (check_special_sym(symbol)) {  // Игнорируем спецсимволы
            continue;
        }
        if (symbol == BSPACE) {  // Backspace - удаление символа
            backspace(word);
            continue;
        }

        cout << symbol;
        word += symbol;  // Добавляем символ к строке
    }
    return 0;
}

// Функция обработки введенных слов
// 0 - ENTER; -1 - стрелка влево; -2 - ESCAPE
int check_word(string& word, int field) { 
    bool wrong_entry = false;
    while (!wrong_entry) {
        wrong_entry = true;
        int result = read_word(word);
        if (result < 0)
            return result;
        // Проверка для ФИО
        if (field == 0) {
            // Проверка на наличие неверных символов
            if (!all_is_alphabetic(word)) {
                cout << "\nВ ФИО должны содержаться только латинские, кириллические буквы, дефис и пробелы. Введите другие ФИО.\n\n";
                cout << "Введите ФИО через пробел:  ";
                word.clear();
                wrong_entry = false;
                continue;
            }
            // Проверка на наличие только пробелов
            if (only_space(word)) {
                cout << "\nФИО не может состоять только из пробелов. Введите другое ФИО.\n\n";
                cout << "Введите ФИО через пробел:  ";
                word.clear();
                wrong_entry = false;
                continue;
            }
        }
        // Проверка для номера места
        else if (field == 1) {
            // Проверка на наличие буквы в конце
            if (!is_alphabetic(word[word.length() - 1]) or word[word.length() - 1] == ' ' or word[word.length() - 1] == '-') {
                cout << "\nВ номере места последним символом должна быть буква. Введите номер места в правильном формате.\n\n";
                cout << "Введите номер места:  ";
                word.clear();
                wrong_entry = false;
                continue;
            }
            // Проверка на то, что только последний символ - буква, остальное - цифры
            string temp = word;
            temp.erase(temp.length() - 1);
            if (!all_is_digit(temp)) {
                cout << "\nВ номере места первым должно быть число, а последним только одна буква. Введите номер места в правильном формате.\n\n";
                cout << "Введите номер места:  ";
                word.clear();
                wrong_entry = false;
                continue;
            }
        }
        return 0;
    }
}

// Функция проверки, состоит ли строка только из пробелов
// 0 - не состоит; 1 - состоит
bool only_space(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] != ' ')
            return 0;
    }
    return 1;
}

// Проверяет, является ли символ буквой (русской/английской) или разрешённым символом
// 0 - не является; 1 - является
bool is_alphabetic(char symbol) {
    if (('А' <= symbol and symbol <= 'я') or symbol == 'ё' or symbol == 'Ё' or
        ('A' <= symbol and symbol <= 'Z') or ('a' <= symbol and symbol <= 'z') or
        symbol == ' ' or symbol == '-')
        return 1;
    else
        return 0;
}

// Проверяет, состоит ли строка только из букв и разрешённых символов
// 0 - не состоит; 1 - состоит
bool all_is_alphabetic(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!is_alphabetic(word[i]))
            return 0;
    }
    return 1;
}

// Проверяет, является ли символ цифрой
// 0 - не является; 1 - является
bool is_digit(char symbol) {
    if ('0' <= symbol and symbol <= '9')
        return 1;
    else
        return 0;
}

// Проверяет, состоит ли строка только из цифр
// 0 - не состоит; 1 - состоит
bool all_is_digit(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!is_digit(word[i]))
            return 0;
    }
    return 1;
}