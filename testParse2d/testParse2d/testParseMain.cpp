#include"testParseIncludes.h"

void main()
{
	fstream fileToOpen;
	fstream fileToWrite;
	string fileName;
	cout<<"Enter file name (without extension):";
	cin>>fileName;
	fileToWrite.open(fileName+".2dparsefile",ios::out);
	if(!fileToWrite)
	{
		cout<<"\nERROR OPENING FILE TO WRITE";
		_getch();
		exit(-1);
	}
	fileToOpen.open(fileName+".2d",ios::in);
	if(!fileToOpen)
	{
		cout<<"\nERROR OPENING FILE TO READ";
		_getch();
		exit(-1);
	}
	char whiteSpaceChar;
	int newScanNumber;
	string scanString="Scan No: ";
	string globalX="Global X: ";
	string globalY="Global Y: ";
	string globalT="Global Theta: ";
	string scanX="X:";
	string scanY="Y:";
	string colonString=": ";
	fileToOpen.unsetf(ios::skipws);
	string searchTag;
	for(int i=0;!fileToOpen.eof();i++)
	{
		fileToOpen>>whiteSpaceChar;
		if(whiteSpaceChar=='\n')
		{
			fileToOpen>>searchTag;
			if(searchTag=="scan1Id:")
			{
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				stringstream numberString(searchTag);
				numberString>>newScanNumber;
				fileToWrite<<scanString+searchTag+"\n";
				cout<<"Scan "+searchTag+" done...\n";
			}
			if(searchTag=="robotGlobal:")	//commented lines used to store in arrays, unused as of now.
			{
				//int xpos,ypos;
				//float theta;
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<globalX+searchTag+"\n";
				//stringstream xString(searchTag);
				//xString>>xpos;
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<globalY+searchTag+"\n";
				//stringstream yString(searchTag);
				//yString>>ypos;
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<globalT+searchTag+"\n";
				//stringstream tString(searchTag);
				//tString>>theta;
				cout<<"Global done...\n";
			}
			if(searchTag=="scan1:")
			{
				for(int count=1;count<=MAX_READING_COUNT;count++)
				{
					if(count!=1)
						fileToOpen>>whiteSpaceChar;
					fileToOpen>>whiteSpaceChar;
					fileToOpen>>searchTag;
					fileToWrite<<scanX+searchTag+"\n";
					fileToOpen>>whiteSpaceChar;
					fileToOpen>>searchTag;
					fileToWrite<<scanY+searchTag+"\n";
					cout<<"Reading "<<count<<" done...\n";
					if(count==MAX_READING_COUNT)
						cout<<"Scan Set Complete...\n";
				}
			}
		}
	}
	fileToOpen.close();
	fileToWrite.close();
	cout<<"Scans copied...";
	_getch();
}

