#ifndef Matrix_hpp
#define Matrix_hpp

template <class T>
class Matrix {
private:
	T** Matrix_;
	int Col_;
	int Row_;
	int Size_;
public:
	Matrix(const int& Col, const int& Row) :
		Row_(Row),
		Col_(Col),
		Size_(Row_* Col_),
		Matrix_(new T* [Row_])
	{
		for (int i = 0; i < Row_; i++) {
			Matrix_[i] = new T[Col_];
		}
	}
	Matrix(Matrix<T>&& obj)noexcept :
		Row_(obj.Row_),
		Col_(obj.Col_),
		Size_(obj.Size_),
		Matrix_(obj.Matrix_)
	{
		obj.Matrix_ = nullptr;
	}
	~Matrix() {
		for (int i = 0; i < Row_; i++) {
			delete[] Matrix_[i];
		}
		delete[] Matrix_;
	}
	bool operator<(const Matrix<T>& obj) {
		T l, r;
		for (int i = 0; i < Row_; i++) {
			for (int j = 0; j < Col_; j++) {
				l += Matrix_[i][j];
				r += obj.Matrix_[i][j];
			}
		}
		l /= Size_;
		r /= obj.Size_;
		if (l < r) {
			return true;
		}
		else {
			return false;
		}
	}
	friend ostream& operator<<(ostream& out, const Matrix<T>& obj) {
		SimplyNode* trav = list.head_;
		while (trav) {
			out << trav->Data_ << " ";
			trav = trav->next_;
		}
		out << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Matrix<T>& obj) {
		for(int i=0;i<Size_)
		while (in) {
			T n;
			in >> n;
			if (!(obj += n)) {
				in.clear(std::ios::failbit);
				return in;
			}
		}
		return in;
	}
};

#endif