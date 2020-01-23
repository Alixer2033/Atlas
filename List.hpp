#ifndef List_hpp
#define List_hpp
#include <string>
using std::string;

struct Node {
	int Data_;
	Node* next_;
	Node() :next_(nullptr) {}
	Node(const int& Data) :Data_(Data), next_(nullptr) {}
};

class List {
private:
	string Name_;
	Node* head_;
	Node* tail_;
public:
	List() :head_(nullptr), tail_(nullptr) {}
	List(List&& list) noexcept:Name_(list.Name_), head_(list.head_), tail_(list.tail_) {
		list.Name_ = "";
		list.head_ = list.tail_ = nullptr;
	}
	~List() {
		while (head_) {
			tail_ = head_->next_;
			delete head_;
			head_ = tail_;
		}
	}
	bool operator+=(const int& Data) {
		Node* trav = head_;
		while (trav) {
			if (trav->Data_ == Data) {
				return false;
			}
			else if (trav->Data_ > Data) {
				Node* node = new Node(Data);
				node->next_ = head_;
				head_ = node;
				return true;
			}
			else if (trav->Data_ < Data && !trav->next_) {
				tail_->next_ = new Node(Data);
				tail_ = tail_->next_;
				return true;
			}
			else if (trav->Data_ < Data && trav->next_->Data_ > Data) {
				Node* node = new Node(Data);
				node->next_ = trav->next_;
				trav->next_ = node;
				return true;
			}
			trav = trav->next_;
		}
		head_ = tail_ = new Node(Data);
		return true;
	}
	bool operator==(const List& list) {
		Node* trav = head_;
		Node* trav2 = list.head_;
		while (trav) {
			if (!trav2) {
				return false;
			}
			else if (trav->Data_ != trav2->Data_) {
				return false;
			}
			trav = trav->next_;
			trav2 = trav2->next_;
		}
		if (trav2) {
			return false;
		}
		else {
			return true;
		}
	}
};

#endif



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  cpp: 
#include <iostream>
#include <fstream>
#include <string>
#include<conio.h>
#include "List.hpp"
using namespace std;
int main() {
    List list;
    ifstream in;
    in.open("in.txt");
    in >> list;
    list += 13;
    list += 11;
    list += 16;
    list += 12;
    cout << list;
    _getch();
	return 0;
}