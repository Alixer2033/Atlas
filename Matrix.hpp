#ifndef Matrix_hpp
#define Matrix_hpp

#include <iostream>
using std::istream;
using std::ostream;
using std::endl;

template <class T>
class Matrix {
private:
	T** Matrix_;
	int Col_;
	int Row_;
	int Size_;
public:
	Matrix(const int& Row, const int& Col) :
		Row_(Row),
		Col_(Col),
		Size_(Row_* Col_)
	{
		Matrix_ = new T * [Row_];
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
		for (int i = 0; i < obj.Row_; i++) {
			for (int j = 0; j < obj.Col_; j++) {
				out << obj.Matrix_[i][j] << " ";
			}
		out << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, Matrix<T>& obj) {
		T n;
		for (int i = 0; i < obj.Row_; i++) {
			for (int j = 0; j < obj.Col_; j++) {
				in >> n;
				obj.Matrix_[i][j] = n;
			}
		}
		return in;
	}
};

#endif