#include"ctgIncludes.h"

void main()
{
	fstream fileToOpen;
	string fileName;
	double globalX[1];
	double globalY[1];
	double globalT[1];
	Matrix *matrixStack[1][541];
	double tempX,tempY;
	cout<<"Enter file name (without extension .2dparse):";
	cin>>fileName;
	fileToOpen.open(fileName+".2dparse",ios::in);
	if(!fileToOpen)
	{
		cout<<"ERROR OPENING FILE.";
		_getch();
		exit(0);
	}
	string stringArray[1086];
	for(int i=0,j=0;((!fileToOpen.eof())&&(j!=1000));i++)
	{
		if(i==0)
			fileToOpen>>stringArray[i];
		else if(i==1)
		{
			stringstream globX(stringArray[i]);
			globX>>globalX[j];
			fileToOpen>>stringArray[++i];
			stringstream globY(stringArray[i]);
			globY>>globalY[j];
			fileToOpen>>stringArray[++i];
			stringstream globT(stringArray[i]);
			globT>>globalT[j];
		}
		else if(i>3)
		{
			fileToOpen>>stringArray[i];
			stringstream relX(stringArray[i]);
			relX>>tempX;
			matrixStack[j][int((i-4)/2)]->setCell(0,0,tempX);
			fileToOpen>>stringArray[++i];
			stringstream relY(stringArray[i]);
			relY>>tempY;
			matrixStack[j][int((i-4)/2)]->setCell(1,0,tempY);
		}
		if(i==1085)
		{
			break;
		}
	}
	for(int i=0;i<541;i++)
		matrixStack[0][i]->print();
	_getch();
}