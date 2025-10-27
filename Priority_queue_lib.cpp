#include "Priority_queue_lib.h"

// Указатель на первого в очереди
qu_elm* head_ptr = nullptr;

// Функция вставки в очередь
void insert_queue(int ins_priority, string name, string num_place, string service_class) {
	qu_elm* ins_ptr;
	qu_elm* ptr;
	qu_elm* next_ptr;

	// Создаем новый узел очереди
	ins_ptr = new qu_elm;
	ins_ptr->priority = ins_priority;
	ins_ptr->name = name;
	ins_ptr->num_place = num_place;
	ins_ptr->service_class = service_class;
	ins_ptr->succ_ptr = nullptr;

	// Если очередь пуста, вставляем в начало
	if (head_ptr == nullptr) {
		head_ptr = ins_ptr;
		return;
	}

	// Если приоритет первого меньше, вставляем вперед него
	if (ins_priority > head_ptr->priority) {
		ins_ptr->succ_ptr = head_ptr;
		head_ptr = ins_ptr;
		return;
	}

	// Проход по всем узлам
	ptr = head_ptr;
	while (ptr->succ_ptr != nullptr) {
		next_ptr = ptr->succ_ptr;
		// Если нашли узел с меньшим приоритетом, вставляем перед ним
		if (ins_priority >= next_ptr->priority) {
			ins_ptr->succ_ptr = next_ptr;
			ptr->succ_ptr = ins_ptr;
			return;
		}
		else
			ptr = next_ptr;
	}

	// Если не был найден узел с меньшим приоритетом, вставляем в конец
	ptr->succ_ptr = ins_ptr;
}

// Функция удаления первого из очереди
// 0 - успешное удаление; 1 - очередь пуста
bool remove_first(string& name) {
	qu_elm* ptr;
	// Если очередь непустая
	if (head_ptr != nullptr) {
		// Возвращаем данные
		name = head_ptr->name;
		ptr = head_ptr;
		head_ptr = head_ptr->succ_ptr;
		// Удаляем первого
		delete ptr;
		return 0;
	}
	else
		return 1;
}

// Функция проверки пустоты очереди
bool queue_empty() {
	return (head_ptr == nullptr);
}

// Функция очистки очереди
void pr_queue_clear() {
	string temp_string;
	// Удаляем первого в очереди, пока не достигнем конца
	while (!remove_first(temp_string));
}

// Функция отображения очереди
void pr_queue_show(ostream& output_stream) {

	qu_elm* current = head_ptr;
	// Отображаем данные обо всех в очереди
	while (current != nullptr) {
		output_stream << "+--------------------+--------------+---------------------+" << endl;
		output_stream << "| ФИО                | Номер места  | Класс обслуживания  |" << endl;
		output_stream << "+--------------------+--------------+---------------------+" << endl;
		output_stream << "| " << setw(18) << left << current->name
			<< " | " << setw(12) << current->num_place
			<< " | " << setw(19) << current->service_class << " |" << endl;
		output_stream << "+--------------------+--------------+---------------------+" << endl << endl;
		current = current->succ_ptr;
	}
}