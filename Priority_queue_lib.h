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
void insert_queue(int ins_priority, string name, string num_place, string service_class);

// Функция удаления первого из очереди
// 0 - успешное удаление; 1 - очередь пуста
bool remove_first(string & name);

// Функция проверки пустоты очереди
bool queue_empty();

// Функция очистки очереди
void pr_queue_clear();

// Функция отображения очереди
void pr_queue_show(ostream& output_stream);