#pragma once
#include <string>

template<typename T>
struct vector_node {
	T value;
	vector_node* next = nullptr;
};

class vector_error : public std::exception
{
public:
	vector_error(const std::string& message): message(message) {}
	const char* what() const noexcept override
	{
		return message.c_str();
	}
private:
	std::string message;
};

template<typename T>
class vector { // вектор - расширяемый массив
public:
	vector() : len(0){}
	vector(T* mas, int length) : len(0)
	{
		for (int i = 0; i < length; i++)
		{
			push_back(mas[i]);
		}
	}
	vector(const vector<T>& copy) : len(0)
	{
		int n = copy.length();
		for (int i = 0; i < n; i++)
		{
			push_back(copy[i]);
		}
	}

	~vector()
	{
		clear();
	}

	void push_back(T member)
	{
		if (!head)
		{
			vector_node<T>* newHead = new vector_node<T>;
			newHead->value = member;
			head = newHead;
			len++;
			return;
		}
		vector_node<T>* newNode = new vector_node<T>;
		newNode->value = member;
		vector_node<T>* cntr = head;
		while (cntr->next != nullptr)
		{
			cntr = cntr->next;
		}
		cntr->next = newNode;
		len++;
	}
	T pop_back()
	{
		T ret;
		if (!head)
		{
			throw vector_error("Vector is empty");
		}
		if (head->next == nullptr)
		{
			ret = head->value;
			delete head;
			head = nullptr;
			len--;
			return ret;

		}
		vector_node<T>* cntr = head;
		while (cntr->next->next != nullptr)
		{
			cntr = cntr->next;
		}
		ret = cntr->next->value;
		delete cntr->next;
		cntr->next = nullptr;
		len--;
		return ret;
	}
	T pop(int number)
	{
		T ret;
		vector_node<T>* gap;
		if (!head)
		{
			throw vector_error("Vector is empty");
		}
		if (number == 0)
		{
			ret = head->value;
			if (head->next != nullptr)
			{
				gap = head->next;
				delete head;
				head = gap;
				len--;
				return ret;
			}
			delete head;
			head = nullptr;
			len--;
			return ret;
		}
		vector_node<T>* cntr = head;
		for (int i = 0; i < number-1; i++)
		{
			if (cntr == nullptr)
			{
				break;
				throw vector_error("There are no element to pop");
			}
			cntr = cntr->next;
		}
		if (cntr->next == nullptr)
		{
			throw vector_error("There are no element to pop");
		}
		ret = cntr->next->value;
		gap = cntr->next->next;
		delete cntr->next;
		cntr->next = gap;
		len--;
		return ret;

	}
	
	T& operator[] (int number)
	{
		vector_node<T>* cntr = head;
		for (int i = 0; i < number; i++)
		{
			if (cntr == nullptr)
			{
				break;
				throw vector_error("There are no element to return");
			}
			cntr = cntr->next;
		}
		return cntr->value;
	}

	T operator[] (int number) const 
	{
		vector_node<T>* cntr = head;
		for (int i = 0; i < number; i++)
		{
			if (cntr == nullptr)
			{
				break;
				throw vector_error("There are no element to return");
			}
			cntr = cntr->next;
		}
		return cntr->value;
	}

	vector<T>& operator= (const vector<T>& copy)
	{
		clear();
		int n = copy.length();
		for (int i = 0; i < n; i++)
		{
			push_back(copy[i]);
		}
		return (*this);
	}

	void clear()
	{
		vector_node<T>* cntr, *prev;
		if (!head)
		{
			return;
		}
		cntr = head;
		while (cntr->next != nullptr)
		{
			prev = cntr;
			cntr = cntr->next;
			delete prev;
		}
		delete cntr;
		head = nullptr;
		len = 0;
	}

	int length() const
	{
		return len;
	}
private:
	vector_node<T>* head = nullptr;
	int len;
};

