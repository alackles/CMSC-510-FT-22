#pragma once
#include <exception>

// Note: the code below contains error checking code for use
// in debugging. To turn on error checking, uncomment
// the line below:
#define mDebug
// To turn off error checking comment the line back out.

class BadArrayAccess : public std::exception {
public:
	BadArrayAccess(int r, int c) noexcept
		: row(r), col(c) {}
	virtual const char* what() const noexcept
	{
		return "Bad array access";
	}

	int getRow() { return row; }
	int getCol() { return col; }
private:
	int row, col;
};

template <typename T>
class Matrix {
public:
	Matrix(int r, int c) : rows(r), cols(c) {
		data = new T[r*c];
	}
	~Matrix() { delete[] data; }

	T& operator()(int row, int col) {
#ifdef mDebug
		if (row < 0 || row >= rows || col < 0 || col >= cols)
			throw BadArrayAccess(row, col);
#endif
		return data[row*cols + col];
	}

private:
	int rows, cols;
	T* data;

	// We declare the copy constructor and operator= to be private
	// to prevent their use in code. If you wish to use these, move
	// them to the public section of this class.
	// I strongly suggest that you avoid using these, since copies are
	// inefficient. In particular, when passing Matrix objects as
	// parameters to functions you should always try to pass them
	// using reference parameters
	Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols) {
		data = new T[rows*cols];
		for (int i = 0; i < rows*cols; i++)
			data[i] = other.data[i];
	}

	Matrix<T>& operator=(const Matrix<T>& other) {
		if (data)
			delete[] data;
		rows = other.rows;
		cols = other.cols;
		data = new T[rows*cols];
		for (int i = 0; i < rows*cols; i++)
			data[i] = other.data[i];
		return *this;
	}
};
