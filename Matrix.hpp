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
		Col_(Col),
		Row_(Row),
		Size_(Col_* Row_),
		Matrix_(new T* [Row_])
	{
		for (int i = 0; i < Col_; i++) {
			Matrix_[i] = new T[Row_];
		}
	}
	Matrix(Matrix<T>&& obj)noexcept :
		Col_(obj.Col_),
		Row_(obj.Row_),
		Size_(obj.Size_),
		Matrix_(obj.Matrix_)
	{
		obj.Matrix_ = nullptr;
	}
	~Matrix() {
		for (int i = 0; i < Col_; i++) {
			delete[] Matrix_[i];
		}
		delete[] Matrix_;
	}
};

#endif