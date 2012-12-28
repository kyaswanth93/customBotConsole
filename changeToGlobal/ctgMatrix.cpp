#include"ctgExternIncludes.h"

Matrix::Matrix()
{

}
Matrix::Matrix(int i,int j)
{
	for(int k=0;k<i;k++)
		for(int l=0;l<j;l++)
			cell[(k*l)+l]=new double();
	rows=i;
	cols=j;
}
void Matrix::setCell(int i,int j, double value)
{
	cell[i][j]=value;
}
double Matrix::getCell(int i, int j)
{
	return cell[i][j];
}
Matrix* Matrix::operator+(Matrix& newMatrix)
{
	Matrix* returnMatrix=new Matrix(rows,cols);
	if((newMatrix.rows==rows)&&(newMatrix.cols==cols))
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				returnMatrix->setCell(i,j,(getCell(i,j)+newMatrix.getCell(i,j)));
	return returnMatrix;
}
Matrix* Matrix::operator*(Matrix& newMatrix)
{
	Matrix* returnMatrix=new Matrix(rows,cols);
	if((newMatrix.rows==rows)&&(newMatrix.cols==cols)&&(rows==cols))
	{
		for(int i=0;i<rows;i++)
			for(int j=0;j<cols;j++)
				returnMatrix->setCell(i,j,0);
		for(int i=0;i<rows;i++)
			for(int j=0;j<rows;j++)
				for(int k=0;k<rows;k++)
					returnMatrix->setCell(i,j,(returnMatrix->getCell(i,j)+(getCell(i,k)*newMatrix.getCell(k,j))));
	}
	return returnMatrix;
}
void Matrix::print()
{
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<cols;j++)
			cout<<getCell(i,j)<<"\t";
		cout<<"\n";
	}
}
void Matrix::setMatrix(Matrix& newMatrix)
{
	for(int i=0;i<rows;i++)
		for(int j=0;j<cols;j++)
			setCell(i,j,newMatrix.getCell(i,j));
}