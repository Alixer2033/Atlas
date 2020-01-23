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


};

#endif