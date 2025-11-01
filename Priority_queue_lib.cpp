#include "Priority_queue_lib.h"

// Указатель на первого в очереди
qu_elm* head_ptr = nullptr;

// Функция вставки в очередь
// 0 - успешное добавление; -1 - это имя существует; -2 - это место занято; -3 - имя и место заняты
int insert_queue(int ins_priority, string name, string num_place, string service_class) {
	qu_elm* ins_ptr;
	qu_elm* ptr;
	qu_elm* next_ptr;

	// Проверяем на наличие повторов
	ptr = head_ptr;
	int matches = 0;
	while (ptr != nullptr) {
		// Если нашли узел с таким же именем, выходим
		if (ptr->name == name)
			matches -= 1;
		if (ptr->num_place == num_place)
			matches -= 2;
		ptr = ptr->succ_ptr;
	}
	if (matches != 0)
		return matches;
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
		return 0;
	}

	// Если приоритет первого меньше, вставляем вперед него
	if (ins_priority > head_ptr->priority) {
		ins_ptr->succ_ptr = head_ptr;
		head_ptr = ins_ptr;
		return 0;
	}

	// Проход по всем узлам
	ptr = head_ptr;
	while (ptr->succ_ptr != nullptr) {
		next_ptr = ptr->succ_ptr;
		// Если нашли узел с меньшим приоритетом, вставляем перед ним
		if (ins_priority >= next_ptr->priority) {
			ins_ptr->succ_ptr = next_ptr;
			ptr->succ_ptr = ins_ptr;
			return 0;
		}
		else
			ptr = next_ptr;
	}

	// Если не был найден узел с меньшим приоритетом, вставляем в конец
	ptr->succ_ptr = ins_ptr;
}

// Функция поиска совпадений
// 0 - совпадений нет; 1 - совпадения есть
bool find_matches(string& line) {
	qu_elm* ptr;
	ptr = head_ptr;
	bool is_find = false;
	// Проходимся по всей очереди
	while (ptr != nullptr) {
		// Если нашли узел с таким же именем, отображаем
		if (ptr->name.find(line) != string::npos) {
			pr_pass_show(cout, ptr);
			is_find = true;
		}
		// Если нашли узел с таким же местом, отображаем
		if (ptr->num_place.find(line) != string::npos) {
			pr_pass_show(cout, ptr);
			is_find = true;
		}
		ptr = ptr->succ_ptr;
	}
	return is_find;
}

// Функция поиска совпадений по приоритету
// 0 - совпадений нет; 1 - совпадения есть
bool find_matches(int priority) {
	qu_elm* ptr;
	ptr = head_ptr;
	bool is_find = false;
	// Проходимся по всей очереди
	while (ptr != nullptr) {
		// Если нашли узел с таким приоритетом, отображаем
		if (ptr->priority == priority) {
			pr_pass_show(cout, ptr);
			is_find = true;
		}
		ptr = ptr->succ_ptr;
	}
	return is_find;
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
// 0 - очередь непустая; 1 - пустая
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
		pr_pass_show(output_stream, current);
		current = current->succ_ptr;
	}
}

// Функция отображения пассажира
void pr_pass_show(ostream& output_stream, qu_elm* current) {
	// Вычисляем ширины колонок
	int name_width = max(current->name.length(), size_t(3)) + 2;
	int place_width = max(current->num_place.length(), size_t(11)) + 2;
	int class_width = max(current->service_class.length(), size_t(18)) + 2;

	string line = "+" + string(name_width, '-') + "+" + string(place_width, '-') + "+" + string(class_width, '-') + "+";

	output_stream << line << endl;
	output_stream << "| " << setw(name_width - 2) << left << "ФИО"
		<< " | " << setw(place_width - 2) << "Номер места"
		<< " | " << setw(class_width - 2) << "Класс обслуживания" << " |" << endl;
	output_stream << line << endl;
	output_stream << "| " << setw(name_width - 2) << left << current->name
		<< " | " << setw(place_width - 2) << current->num_place
		<< " | " << setw(class_width - 2) << current->service_class << " |" << endl;
	output_stream << line << endl << endl;
}