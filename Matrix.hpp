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
};

#endif