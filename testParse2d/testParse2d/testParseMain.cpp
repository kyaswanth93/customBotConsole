#include"testParseIncludes.h"

void main()
{
	fstream fileToOpen;
	fstream fileToWrite;
	string fileName;
	cout<<"Enter file name (without extension):";
	cin>>fileName;
	fileToWrite.open(fileName+".2dparse",ios::out);
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
				fileToWrite<<searchTag+"\n";
				cout<<"Scan "+searchTag+" done...\n";
			}
			if(searchTag=="robotGlobal:")
			{
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<searchTag+"\n";
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<searchTag+"\n";
				fileToOpen>>whiteSpaceChar;
				fileToOpen>>searchTag;
				fileToWrite<<searchTag+"\n";
			}
			if(searchTag=="scan1:")
			{
				for(int count=1;count<=MAX_READING_COUNT;count++)
				{
					if(count!=1)
						fileToOpen>>whiteSpaceChar;
					fileToOpen>>whiteSpaceChar;
					fileToOpen>>searchTag;
					fileToWrite<<searchTag+"\n";
					fileToOpen>>whiteSpaceChar;
					fileToOpen>>searchTag;
					fileToWrite<<searchTag+"\n";	
				}
			}
		}
	}
	fileToOpen.close();
	fileToWrite.close();
	cout<<"Scans copied...";
	_getch();
}