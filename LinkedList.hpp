#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

struct SimplyNode {
	int Data_;
	SimplyNode* next_;
	SimplyNode() :Data_(0), next_(nullptr) {}
	SimplyNode(const int& Data) :Data_(Data), next_(nullptr) {}
};

class SimplyLinkedList {
private:
	SimplyNode* head_;
	SimplyNode* tail_;
public:
	SimplyLinkedList() :head_(nullptr), tail_(nullptr) {}
	SimplyLinkedList(SimplyLinkedList&& list) noexcept :head_(list.head_), tail_(list.tail_) {
		list.head_ = list.tail_ = nullptr;
	}
	SimplyLinkedList(const SimplyLinkedList& list) :head_(nullptr), tail_(nullptr) {
		if (list.head_) {
			head_ = new SimplyNode(list.head_->Data_);
			SimplyNode* trav = list.head_->next_;
			tail_ = head_;
			while (trav) {
				tail_->next_ = new SimplyNode(trav->Data_);
				tail_ = tail_->next_;
				trav = trav->next_;
			}
		}
	}
	~SimplyLinkedList() {
		while (head_) {
			tail_ = head_->next_;
			delete head_;
			head_ = tail_;
		}
	}
	const SimplyLinkedList& operator=(SimplyLinkedList&& list)noexcept {
		while (head_) {
			tail_ = head_->next_;
			delete head_;
			head_ = tail_;
		}
		head_ = list.head_;
		tail_ = list.tail_;
		list.head_ = list.tail_ = nullptr;
		return *this;
	}
	bool operator+=(const int& Data) {
		SimplyNode* trav = head_;
		while (trav) {
			if (trav->Data_ == Data) {
				return false;
			}
			else if (trav->Data_ > Data) {
				SimplyNode* node = new SimplyNode(Data);
				node->next_ = head_;
				head_ = node;
				return true;
			}
			else if (trav->Data_ < Data && !trav->next_) {
				tail_->next_ = new SimplyNode(Data);
				tail_ = tail_->next_;
				return true;
			}
			else if (trav->Data_ < Data && trav->next_->Data_ > Data) {
				SimplyNode* node = new SimplyNode(Data);
				node->next_ = trav->next_;
				trav->next_ = node;
				return true;
			}
			trav = trav->next_;
		}
		head_ = tail_ = new SimplyNode(Data);
		return true;
	}
	bool operator==(const SimplyLinkedList& list) {
		SimplyNode* trav = head_;
		SimplyNode* trav2 = list.head_;
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
	friend ostream& operator<<(ostream& out, const SimplyLinkedList& list) {
		SimplyNode* trav = list.head_;
		while (trav) {
			out << trav->Data_ << " ";
			trav = trav->next_;
		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, SimplyLinkedList& list) {
		while (in) {
			int n;
			in >> n;
			if (!(list += n)) {
				in.clear(std::ios::failbit);
				return in;
			}
		}
		return in;
	}
	friend SimplyLinkedList operator&(SimplyLinkedList& l, SimplyLinkedList r) {
		SimplyLinkedList list;
		SimplyNode* trav1 = l.head_;
		SimplyNode* trav2 = r.head_;
		while (trav1 && trav2) {
			if (trav1->Data_ == trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ > trav2->Data_) {
				list += trav2->Data_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ < trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
			}
		}
		while (trav1) {
			list += trav1->Data_;
			trav1 = trav1->next_;
		}
		while (trav2) {
			list += trav2->Data_;
			trav2 = trav2->next_;
		}
		return list;
	}
	friend SimplyLinkedList operator|(SimplyLinkedList& l, SimplyLinkedList r) {
		SimplyLinkedList list;
		SimplyNode* trav1 = l.head_;
		SimplyNode* trav2 = r.head_;
		while (trav1 && trav2) {
			if (trav1->Data_ == trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ > trav2->Data_) {
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ < trav2->Data_) {
				trav1 = trav1->next_;
			}
		}
		return list;
	}
	void merge(SimplyLinkedList& list) {
		SimplyNode* trav = list.head_;
		while (trav) {
			*this += trav->Data_;
			trav = trav->next_;
		}
		while (list.head_) {
			list.tail_ = list.head_->next_;
			delete list.head_;
			list.head_ = list.tail_;
		}
	}
};

struct DoublyNode {
	int Data_;
	DoublyNode* next_;
	DoublyNode* prev_;
	DoublyNode() :Data_(0), next_(nullptr), prev_(nullptr) {}
	DoublyNode(const int& Data) :Data_(Data), next_(nullptr), prev_(nullptr) {}
};

class DoublyLinkedList {
private:
	DoublyNode* head_;
	DoublyNode* tail_;
public:
	DoublyLinkedList() :head_(nullptr), tail_(nullptr) {}
	DoublyLinkedList(DoublyLinkedList&& list) noexcept :head_(list.head_), tail_(list.tail_) {
		list.head_ = list.tail_ = nullptr;
	}
	DoublyLinkedList(const DoublyLinkedList& list) :head_(nullptr), tail_(nullptr) {
		if (list.head_) {
			head_ = new DoublyNode(list.head_->Data_);
			DoublyNode* trav = list.head_->next_;
			tail_ = head_;
			while (trav) {
				tail_->next_ = new DoublyNode(trav->Data_);
				tail_->next_->prev_ = tail_;
				tail_ = tail_->next_;
				trav = trav->next_;
			}
		}
	}
	~DoublyLinkedList() {
		while (head_) {
			tail_ = head_->next_;
			delete head_;
			head_ = tail_;
		}
	}
	const DoublyLinkedList& operator=(DoublyLinkedList&& list)noexcept {
		while (head_) {
			tail_ = head_->next_;
			delete head_;
			head_ = tail_;
		}
		head_ = list.head_;
		tail_ = list.tail_;
		list.head_ = list.tail_ = nullptr;
		return *this;
	}
	bool operator+=(const int& Data) {
		DoublyNode* trav = head_;
		while (trav) {
			if (trav->Data_ == Data) {
				return false;
			}
			else if (trav->Data_ > Data) {
				DoublyNode* node = new DoublyNode(Data);
				node->next_ = head_;
				head_->prev_ = node;
				head_ = node;
				return true;
			}
			else if (trav->Data_ < Data && !trav->next_) {
				tail_->next_ = new DoublyNode(Data);
				tail_->next_->prev_ = tail_;
				tail_ = tail_->next_;
				return true;
			}
			else if (trav->Data_ < Data && trav->next_->Data_ > Data) {
				DoublyNode* node = new DoublyNode(Data);
				node->next_ = trav->next_;
				node->next_->prev_ = node;
				trav->next_ = node;
				node->prev_ = trav;
				return true;
			}
			trav = trav->next_;
		}
		head_ = tail_ = new DoublyNode(Data);
		return true;
	}
	bool operator==(const DoublyLinkedList& list) {
		DoublyNode* trav = head_;
		DoublyNode* trav2 = list.head_;
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
	friend ostream& operator<<(ostream& out, const DoublyLinkedList& list) {
		DoublyNode* trav = list.head_;
		while (trav) {
			out << trav->Data_ << " ";
			trav = trav->next_;
		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, DoublyLinkedList& list) {
		while (in) {
			int n;
			in >> n;
			if (!(list += n)) {
				in.clear(std::ios::failbit);
				return in;
			}
		}
		return in;
	}
	friend DoublyLinkedList operator&(DoublyLinkedList& l, DoublyLinkedList r) {
		DoublyLinkedList list;
		DoublyNode* trav1 = l.head_;
		DoublyNode* trav2 = r.head_;
		while (trav1 && trav2) {
			if (trav1->Data_ == trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ > trav2->Data_) {
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ < trav2->Data_) {
				trav1 = trav1->next_;
			}
		}
		return list;
	}
	friend DoublyLinkedList operator|(DoublyLinkedList& l, DoublyLinkedList r) {
		DoublyLinkedList list;
		DoublyNode* trav1 = l.head_;
		DoublyNode* trav2 = r.head_;
		while (trav1 && trav2) {
			if (trav1->Data_ == trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ > trav2->Data_) {
				list += trav2->Data_;
				trav2 = trav2->next_;
			}
			else if (trav1->Data_ < trav2->Data_) {
				list += trav1->Data_;
				trav1 = trav1->next_;
			}
		}
		while (trav1) {
			list += trav1->Data_;
			trav1 = trav1->next_;
		}
		while (trav2) {
			list += trav2->Data_;
			trav2 = trav2->next_;
		}
		return list;
	}
	void merge(DoublyLinkedList& list) {
		DoublyNode* trav = list.head_;
		while (trav) {
			*this += trav->Data_;
			trav = trav->next_;
		}
		while (list.head_) {
			list.tail_ = list.head_->next_;
			delete list.head_;
			list.head_ = list.tail_;
		}
	}
};

#endif