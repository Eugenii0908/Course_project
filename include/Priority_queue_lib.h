#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

// Структура узла очереди с приоритетами
struct qu_elm {
	int priority;
	string name;
	string num_place;
	string service_class;
	qu_elm* succ_ptr;
};

// Глобальный корень дерева
extern qu_elm* head_ptr;

// Функция вставки в очередь
// 0 - успешное добавление; -1 - это имя существует; -2 - это место занято; -3 - имя и место заняты
int insert_queue(int ins_priority, string name, string num_place, string service_class);

// Функция удаления первого из очереди
// 0 - успешное удаление; 1 - очередь пуста
bool remove_first(string & name);

// Функция проверки пустоты очереди
// 0 - очередь непустая; 1 - пустая
bool queue_empty();

// Функция очистки очереди
void pr_queue_clear();

// Функция отображения очереди
void pr_queue_show(ostream& output_stream);

// Функция отображения пассажира
void pr_pass_show(ostream& output_stream, qu_elm* current);

// Функция поиска совпадений
// 0 - совпадений нет; 1 - совпадения есть
bool find_matches(string& line);

// Функция поиска совпадений по приоритету
// 0 - совпадений нет; 1 - совпадения есть
bool find_matches(int priority);