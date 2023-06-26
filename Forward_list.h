#pragma once

template<typename T>
class Forward_list
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

	Node* head;

	unsigned int _size;

	void swap_for_sort(int first, int second);

public:
	Forward_list();

	Forward_list(const Forward_list& other);
	Forward_list(Forward_list&& other) noexcept;

	Forward_list(std::initializer_list<T> list);

	Forward_list(const int size);

	Forward_list(const int size, const T& value);

	~Forward_list();

	void push_back(const T& value);
	void push_back(std::initializer_list<T> list);

	void insert(int index, const T& value);
	void insert(int index, std::initializer_list<T> list);

	void pop_back();

	void erase(const int index);
	void erase(const int first_index, const int second_index);

	void assign(const int size);
	void assign(const int size, const T& value);
	void assign(std::initializer_list<T> list);

	bool search(const T& element);
	bool bin_search(const T& element);

	int get_index(const T& element);
	int get_index(const T& element, const int start_index);

	void sort();
	void sort(const int first, const int last);

	void clear();

	bool is_empty() const;

	T& operator[](int index);
	const T& operator[](int index) const;

	void operator=(const Forward_list& other);
	void operator=(Forward_list&& other) noexcept;
	void operator=(std::initializer_list<T> list);

	bool operator==(const Forward_list& other) const;

	unsigned int size() const;
};

template<typename T>
inline Forward_list<T>::Forward_list()
	: head(nullptr), _size(0)
{ }

template<typename T>
inline Forward_list<T>::Forward_list(const Forward_list& other)
	: head(nullptr), _size(other.size())
{
	if (_size > 0)
		head = new Node{ other[0], nullptr};

	Node* current = head;

	for (int i = 1; i < _size; i++)
	{
		current->next = new Node{ other[i], nullptr };

		current = current->next;
	}
}

template<typename T>
inline Forward_list<T>::Forward_list(Forward_list&& other) noexcept
	: head(other.head), _size(other.size())
{
	other.head = nullptr;
	other._size = 0;
}

template<typename T>
inline Forward_list<T>::Forward_list(std::initializer_list<T> list)
{
	assign(list);
}

template<typename T>
inline Forward_list<T>::Forward_list(const int size)
{
	assign(size);
}

template<typename T>
inline Forward_list<T>::Forward_list(const int size, const T& value)
{
	assign(size, value);
}

template<typename T>
inline Forward_list<T>::~Forward_list()
{
	clear();
}

template<typename T>
inline void Forward_list<T>::push_back(const T& value)
{
	if (head == nullptr)
	{
		head = new Node{ value, nullptr };

		_size++;

		return;
	}

	Node* current = head;

	while(current->next != nullptr)
		current = current->next;

	current->next = new Node{ value, nullptr };

	_size++;
}

template<typename T>
inline void Forward_list<T>::push_back(std::initializer_list<T> list)
{
	if (list.size() == 0)
		return;

	if (head == nullptr)
	{
		head = new Node{ *list.begin(), nullptr };

		Node* current = head;

		for (int i = 1; i < list.size(); i++)
		{
			current->next = new Node{ *(list.begin() + i), nullptr };

			current = current->next;
		}

		_size += list.size();

		return;
	}

	Node* current = head;

	while (current->next != nullptr)
		current = current->next;

	for (int i = 0; i < list.size(); i++)
	{
		current->next = new Node{ *(list.begin() + i), nullptr };

		current = current->next;
	}

	_size += list.size();
}

template<typename T>
inline void Forward_list<T>::insert(int index, const T& value)
{
	if (index > _size || index < 0)
		throw std::out_of_range("Out of Range");

	if (index == 0)
	{
		Node* temp = head;

		head = new Node{ value, nullptr };

		head->next = temp;

		_size++;

		return;
	}

	Node* current = head;

	for (int i = 0; i < index - 1; i++)
		current = current->next;

	Node* temp = current->next;

	current->next = new Node{ value, nullptr };

	current->next->next = temp;

	_size++;
}

template<typename T>
inline void Forward_list<T>::insert(int index, std::initializer_list<T> list)
{
	if (index > _size || index < 0)
		throw std::out_of_range("Out of Range");

	if (index == 0)
	{		
		Node* temp = head;

		head = new Node{ *list.begin(), nullptr };

		Node* current = head;

		for (int i = 1; i < list.size(); i++)
		{
			current->next = new Node{ *(list.begin() + i), nullptr };

			current = current->next;
		}

		current->next = temp;

		_size += list.size();

		return;
	}

	Node* current = head;

	for (int i = 0; i < index - 1; i++)
		current = current->next;

	Node* temp = current->next;

	for (int i = 0; i < list.size(); i++)
	{
		current->next = new Node{ *(list.begin() + i), nullptr };

		current = current->next;
	}

	current->next = temp;

	_size += list.size();
}

template<typename T>
inline void Forward_list<T>::pop_back()
{
	if (head == nullptr)
		return;

	Node* current = head;

	while (current->next != nullptr)
		current = current->next;

	delete current;
	current = nullptr;

	_size--;
}

template<typename T>
inline void Forward_list<T>::erase(const int index)
{
	if (index >= _size || index < 0)
		throw std::out_of_range("Out of Range");

	if (index == 0)
	{
		Node* temp = head->next;

		delete head;

		head = temp;

		_size--;

		return;
	}

	Node* current = head;

	for (int i = 0; i < index - 1; i++)
		current = current->next;

	Node* temp = current->next->next;

	delete current->next;
	current->next = nullptr;

	current->next = temp;

	_size--;
}

template<typename T>
inline void Forward_list<T>::erase(const int first_index, const int second_index)
{
	if (first_index > _size || first_index < 0 || second_index > _size || second_index < 0)
		throw std::out_of_range("out of range");

	if (second_index < first_index)
		throw std::exception("first index is bigger than second index");

	if (second_index == first_index)
		return;

	Node* current = head;

	for (int i = 0; i < first_index - 1; i++)
		current = current->next;

	Node* previous;
	Node* temp = nullptr;

	if (first_index > 0)
	{
		temp = current;

		current = current->next;
	}

	for (int i = 0; i < second_index - first_index; i++)
	{
		previous = current;

		current = current->next;

		delete previous;
		previous = nullptr;
	}

	if (first_index > 0)
		temp->next = current;
	else
		head = current;

	_size -= (second_index - first_index);
}

template<typename T>
inline void Forward_list<T>::assign(const int size)
{
	clear();

	_size = size;

	if (_size > 0)
		head = new Node{ 0, nullptr };

	Node* current = head;

	for (int i = 1; i < _size; i++)
	{
		current->next = new Node{ 0, nullptr };

		current = current->next;
	}
}

template<typename T>
inline void Forward_list<T>::assign(const int size, const T& value)
{
	clear();

	_size = size;

	if (_size > 0)
		head = new Node{ value, nullptr };

	Node* current = head;

	for (int i = 1; i < _size; i++)
	{
		current->next = new Node{ value, nullptr };

		current = current->next;
	}
}

template<typename T>
inline void Forward_list<T>::assign(std::initializer_list<T> list)
{
	clear();

	_size = list.size();

	if (_size > 0)
		head = new Node{ *list.begin(), nullptr };

	Node* current = head;

	for (int i = 1; i < _size; i++)
	{
		current->next = new Node{ *(list.begin() + i), nullptr};

		current = current->next;
	}
}

template<typename T>
inline bool Forward_list<T>::search(const T& element)
{
	Node* current = head;

	for (int i = 0; i < _size; i++)
	{
		if (operator[](i) == element)
			return true;
	}

	return false;
}

template<typename T>
inline bool Forward_list<T>::bin_search(const T& element)
{
	int left = 0;
	int right = _size - 1;

	int middle = 0;

	do
	{
		middle = (left + right) / 2;

		T& middle_elem = operator[](middle);

		if (middle_elem == element)
			return true;
		else if (middle_elem < element)
			left = middle + 1;
		else if (element < middle_elem)
			right = middle - 1;
	} 
	while (left <= right);

	return false;
}

template<typename T>
inline int Forward_list<T>::get_index(const T& element)
{
	Node* current = head;

	for (int i = 0; i < _size; i++)
	{
		if (operator[](i) == element)
			return i;
	}

	return -1;
}

template<typename T>
inline int Forward_list<T>::get_index(const T& element, const int start_index)
{
	Node* current = head;

	for (int i = start_index; i < _size; i++)
	{
		if (operator[](i) == element)
			return i;
	}

	return -1;
}

template<typename T>
inline void Forward_list<T>::sort()
{
	sort(0, _size - 1);
}

template<typename T>
inline void Forward_list<T>::swap_for_sort(int first, int second)
{
	T temp = operator[](first);

	operator[](first) = operator[](second);
	operator[](second) = temp;
}

template<typename T>
inline void Forward_list<T>::sort(const int first, const int last)
{
	T middle = operator[]((first + last) / 2);

	int i = first;
	int j = last;

	do
	{
		while (operator[](i) < middle)
			i++;
		while (middle < operator[](j))
			j--;

		if (i <= j)
		{
			swap_for_sort(i, j);

			i++;
			j--;
		}
	} 
	while (i <= j);

	if (i < last)
		sort(i, last);
	if (j > first)
		sort(first, j);
}

template<typename T>
inline void Forward_list<T>::clear()
{
	if (head == nullptr)
		return;

	Node* current = head;
	Node* previous;

	for (int i = 0; i < _size; i++)
	{
		previous = current;
		current = current->next;

		delete previous;
	}

	head = nullptr;
}

template<typename T>
inline bool Forward_list<T>::is_empty() const
{
	return head == nullptr ? true : false;
}

template<typename T>
inline T& Forward_list<T>::operator[](int index)
{
	if(index >= _size || index < 0)
		throw std::out_of_range("out of range");

	Node* current = head;

	for (int i = 0; i < index; i++)
		current = current->next;

	return current->data;
}

template<typename T>
inline const T& Forward_list<T>::operator[](int index) const
{
	if (index >= _size || index < 0)
		throw std::out_of_range("out of range");

	Node* current = head;

	for (int i = 0; i < index; i++)
		current = current->next;

	return current->data;
}

template<typename T>
inline void Forward_list<T>::operator=(const Forward_list& other)
{
	clear();

	_size = other.size();

	if (_size > 0)
		head = new Node{ other[0], nullptr };

	Node* current = head;

	for (int i = 1; i < _size; i++)
	{
		current->next = new Node{ other[i], nullptr };

		current = current->next;
	}
}

template<typename T>
inline void Forward_list<T>::operator=(Forward_list&& other) noexcept
{
	head = other.head;
	_size = other.size();

	other.head = nullptr;
	other._size = 0;
}

template<typename T>
inline void Forward_list<T>::operator=(std::initializer_list<T> list)
{
	assign(list);
}

template<typename T>
inline bool Forward_list<T>::operator==(const Forward_list& other) const
{
	if (_size != other.size())
		return false;

	for (int i = 0; i < _size; i++)
	{
		if (operator[](i) != other[i])
			return false;
	}

	return true;
}

template<typename T>
inline unsigned int Forward_list<T>::size() const { return _size; }