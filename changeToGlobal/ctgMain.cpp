#include"ctgIncludes.h"

void main()
{
	/*fstream fileToOpen;
	string fileName;
	cout<<"Enter file name (without extension .2dparse):";
	cin>>fileName;
	fileToOpen.open(fileName+".2dparse",ios::in);
	if(!fileToOpen)
	{
		cout<<"ERROR OPENING FILE.";
		_getch();
		exit(0);
	}*/
	//First testing for normal x,y
	matrixA=new Matrix(3,3);
	matrixB=new Matrix(3,3);
	matrixC=new Matrix(3,3);
	matrixD=new Matrix(3,3);
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			matrixA->setCell(i,j,((i*3)+j+1));
	matrixA->print();
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			matrixB->setCell(i,j,((i*3)+j+1));
	matrixB->print();
	matrixC->setMatrix(*(matrixA->operator+(*matrixB)));
	matrixD->setMatrix(*(matrixA->operator*(*matrixB)));
	matrixC->print();
	matrixD->print();
	_getch();
}