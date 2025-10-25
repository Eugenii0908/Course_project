#include "interface_lib.h"

const string welcome_message = "Данная программа предназначена для управления очередью на посадку в самолет.\n"
"Здесь можно реализовать вставку и извлечение из очереди, а также отображение информации о всех пассажирах.\n\n";
const string main_menu_text = "-Для перемещения по пунктам используйте стрелки вверх/вниз\n"
"-Для подтверждения выбора нажмите ENTER или стрелку вправо\n-Для выхода в главное меню нажмите ESCAPE или на стрелку влево\n\n"
"Выберите операцию, которую хотите выполнить:\n";
string main_menu_point[] = { "1. Добавить пассажиров в очередь.", "2. Извлечь пассажиров из очереди.",
"3. Отображение информации о пассажирах.", "4. Сохранение информации в файл." };
const string menu1_add_text = "Вы хотите добавить пассажиров из файла или вручную?\n";
string menu1_add_point[] = { "1. Добавить вручную.", "2. Загрузить из файла." };
const string menu1_1_add_text = "Введите данные по указанным ниже полям:\n";
const string menu1_2_add_text = "Файл должен находиться в папке с программой.\nВыберите файл:\n";
const string menu_del_text = "Выберите пассажира, которого хотите извлеч из очереди:\n";
const string menu3_search_text = "Выберите тип отображения пассажиров:\n";
string menu3_search_point[] = { "1. Поиск пассажиров по введенным данным.", "2. Поиск пассажиров с указанным приоритетам." };
const string menu3_1_search_text = "Введите ключевое слово или его часть для поиска по всем пассажирам:\n";
const string menu3_2_search_text = "Выберите приоритет, по которому хотите найти пассажиров:\n";
string menu3_2_search_point[] = { "1. Эконом-класс.", "2. Обладатели серебряных карт.", "3. Льготные пассажиры.",
"4. Бизнес-класс.", "5. Особый приоритет." };
const string menu3_2_1_search_text = "Выборка пассажиров по выбранному приоритету:\n\n";

// Пример использования
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << welcome_message;
    system("pause");
    system("cls");
    // Создаем дерево
    root = create_node("main_menu", main_menu_text, main_menu_point, size(main_menu_point), nullptr);
    add_node("main_menu", "1", menu1_add_text, menu1_add_point, size(menu1_add_point), nullptr);  // Создаем корень (родитель 0 означает создание корня)
    add_node("1", "1.1", menu1_1_add_text, nullptr, 0, nullptr);
    add_node("1", "1.2", menu1_2_add_text, nullptr, 0, nullptr);
    add_node("main_menu", "2", menu_del_text, nullptr, 0, nullptr);
    add_node("main_menu", "3", menu3_search_text, menu3_search_point, size(menu3_search_point), nullptr);  // Создаем корень (родитель 0 означает создание корня)
    add_node("3", "3.1", menu3_1_search_text, nullptr, 0, nullptr);
    add_node("3", "3.2", menu3_2_search_text, menu3_2_search_point, size(menu3_2_search_point), nullptr);
    add_node("3.2", "3.2.1", menu3_2_1_search_text, nullptr, 0, nullptr);
    cycle();
}