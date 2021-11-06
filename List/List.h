//
//  List.h
//  Prt
//
//  Created by Михаил Фокин on 05.11.2021.
//

#ifndef List_h
#define List_h

#include <vector>

template <class T>
class Node {
	size_t index;
	T data;
	std::shared_ptr<Node> next;
	std::weak_ptr<Node> prev;
public:
	
	Node(T data):index(0), data(data), next(nullptr) {}
	
	void setNextNode(std::shared_ptr<Node> &node) { next = node; }
	
	void setPrevNode(std::shared_ptr<Node> &node) { prev = node; }
	
	std::shared_ptr<Node> &getNextNode() { return next; }
	
	T getData() const { return data; }
	
	size_t getIndex() const { return index; }
	
	void setIndex(size_t newIndex) { index = newIndex; }
};

template <class T>
std::ostream& operator<< (std::ostream &out, Node<T> &node)
{
	out << "Node(" << node.getData() << ")";
	return out;
}


template <class T>
class List {
	size_t size;
	std::shared_ptr<Node<T>> head;
	std::shared_ptr<Node<T>> tail;
	
	// Устанавливаем в случайное место слабую ссылку
	void setRandomWearPtr() {
		srand(static_cast<unsigned int>(time(0)));
		
		size_t i = rand() % size;
		
		std::shared_ptr<Node<int>> temp = head;
		size_t j = 0;
		while (temp != nullptr) {
			if (i == j) {
				head.get()->setPrevNode(temp);
				std::cout << "weak " << *temp << std::endl;
			}
			temp = temp.get()->getNextNode();
			j++;
		}
	}
	
	std::vector<size_t> indexVector() {
		std::vector<size_t> indexes;
		std::shared_ptr<Node<int>> temp = head;
		size_t i = 0;
		while (temp != nullptr) {
			indexes.push_back(i);
			temp = temp.get()->getNextNode();
		}
		return indexes;
	}
	
public:

	List():size(0), head(nullptr), tail(nullptr) {};
	
	~List() {
		std::cout << "List destructor" << std::endl;
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	
	// Добавление нового узла в начало списка.
	void addNode(T data) {
		if (head.get() == nullptr) {
			head = std::shared_ptr<Node<T>>(new Node<T>(data));
			head.get()->setIndex(size);
			tail = head;
			size++;
			return ;
		}
		std::shared_ptr<Node<T>> newNode(new Node<T>(data));
		newNode.get()->setNextNode(head);
		head = newNode;
		size++;
		setRandomWearPtr();
	}

	size_t getSize() const {
		return size;
	}
	
	void printNodes() const {
		std::shared_ptr<Node<int>> temp = head;
		while (temp != nullptr) {
			std::cout << *temp << std::endl;
			temp = temp.get()->getNextNode();
		}
	}
	
	// Установка для определенного узла срабую ссылку по индексу.
	void setWeakPrt(std::shared_ptr<Node<T>> &node, size_t index) {
		std::shared_ptr<Node<int>> temp = head;
		size_t i = 0;
		while (temp != nullptr) {
			if (i == index)
				node->setPrevNode(temp);
			temp = temp.get()->getNextNode();
			i++;
		}
	}
	
	// Установка слабых ссылок на основе вектора индексов.
	void setWeakPrtFormVector(std::vector<size_t> &indexes) {
		std::shared_ptr<Node<int>> temp = head;
		while (temp != nullptr) {
			size_t index = temp.get()->getIndex();
			setWeakPrt(temp, index);
			temp = temp.get()->getNextNode();
		}
	}
	
	List getCopy() {
		std::vector<size_t> indexes = indexVector();
		List<T> newList;
		std::shared_ptr<Node<int>> temp = head;
		while (temp != nullptr) {
			newList.addNode(temp.get()->getData());
			temp = temp.get()->getNextNode();
		}
		newList.setWeakPrtFormVector(indexes);
		return newList;
	}
};

#endif /* List_h */
