#ifndef CTG_MATRIX_H
#define CTG_MATRIX_H

class Matrix
{
	double* cell[9];
	int rows,cols;
public:
	Matrix();
	Matrix(int i, int j);
	void setCell(int i, int j, double value);
	double getCell(int i, int j);
	Matrix* operator+(Matrix& newMatrix);
	Matrix* operator*(Matrix& newMatrix);
	void print();
	void setMatrix(Matrix &newMatrix);
};

#endif