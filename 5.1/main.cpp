#include <iostream>

using namespace std;

//Дан линейный однонаправленный список L
//1) Разработать функцию, которая создает из значений узлов списка L два новых списка: L1 – из положительных элементов L; L2 – из остальных элементов L.
//2) Разработать функцию, которая удаляет из списка L2 все отрицательные элементы.
//3) Разработать функцию, которая в списке L1 узел с максимальным значением размещает перед первым узлом.


struct Node // узел списка
{
	int element; // данные узла
	Node* next; // указатель на следующий узел
	Node(int _element) : element(_element), next(nullptr){};
};

struct List // однонаправленный список
{
	Node* first; // указатель на первый узел списка
	Node* last; // указатель на последний узел списка
	List() : first(nullptr), last(nullptr) {};
	void addNode(int element) // добавление узла в список
	{
		Node* p = new Node(element); 
		if (first == nullptr)
		{
			first = p;
			last = p;
		}
		else
		{
			Node* temp = first;
			first = p;
			first->next = temp;
		}
	}
	void delNode(int element) // удаление узла по элементу
	{
		if (first->element == element)
		{
			Node* temp = first;
			first = first->next;
			delete temp;
			return;
		}
		else if (last->element == element)
		{
			Node* p = first;
			while(p->next != last)
			{
				p = p->next;
			}
			delete last;
			p->next = nullptr;
			last = p;
		}
		else
		{
			Node* p = first;
			Node* nxt = p->next;
			while (nxt->element != element)
			{
				p = p->next;
				nxt = p->next;
			}
			p->next = nxt->next;
			delete nxt;
		}
	}
	void moveToStart(int element)
	{
		Node* p = first;
		Node* search = first;
		while (search != nullptr)
		{
			if (search->element == element) break;
			search = search->next;
		}
		if (search == first) return;
		else if (search == last)
		{
			while (p->next != nullptr)
			{
				if (p->next == last)
				{
					last = p;
					p->next = nullptr;
					search->next = first;
					first = search;
					break;
				}
				p = p->next;
			}
		}
		else
		{
			while (p->next != nullptr)
			{
				if (p->next == search)
				{
					p->next = search->next;
					search->next = first;
					first = search;
					break;
				}
				p = p->next;
			}
		}
	}
	void outputList() // вывод списка
	{
		Node* p = first;
		while (p != nullptr)
		{
			cout << p->element << " ";
			p = p->next;
		}
	}
};

void createLists(List L, List& L1, List& L2) // заполнение списков L1 и L2
{
	Node* p = L.first;
	while (p != nullptr)
	{
		if (p->element > 0) L1.addNode(p->element);
		else L2.addNode(p->element);
		p = p->next;
	}
}

void delNegL2(List& L2) // удаление всех отрицательных элементов из списка L2
{
	Node* p = L2.first;
	int k = 0;
	while (p != nullptr)
	{
		k += 1;
		p = p->next;
	}
	p = L2.first;
	for (int i = 0; i < k; i++) 
	{
		int el = p->element;
		if (el < 0)
		{
			p = p->next;
			L2.delNode(el);
		}
		else p = p->next;
	}
}

void maxElL1(List& L1) // перемещение узла с максимальным значением в начало списка
{
	Node* p = L1.first;
	int max_el = 0;
	while (p != nullptr)
	{
		if (p->element > max_el)
		{
			max_el = p->element;
		}
		p = p->next;
	}
	if (max_el == 0) return;
	L1.moveToStart(max_el);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	List L, L1, L2;
	cout << "Введите количество элементов в списке: ";
	int n;
	cin >> n;
	cout << "Введенные вами элементы: ";
	if (n == 0) cout << endl;
	else 
	{
		for (int i = 0; i < n; i++)
		{
			int el;
			cin >> el;
			L.addNode(el);
		}
	}
	cout << "Элементы списка L: ";
	L.outputList();
	cout << endl;
	createLists(L, L1, L2);
	cout << "Элементы списка L1: ";
	L1.outputList();
	cout << endl;
	cout << "Элементы списка L2: ";
	L2.outputList();
	cout << endl;
	delNegL2(L2);
	cout << "Список L2 после удаления отрицательных элементов: ";
	L2.outputList();
	cout << endl;
	maxElL1(L1);
	cout << "Список L1 после перемещения узла с максимальным значением в начало: ";
	L1.outputList();
	return(0);
}
