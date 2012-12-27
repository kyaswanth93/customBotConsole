#include"testParseIncludes.h"

void main()
{
	int countLines=0,countSpaces=1;
	fstream fileToOpen;
	fileToOpen.open("mctlab.2d",ios::in);
	if(!fileToOpen)
	{
		cout<<"\nERROR OPENING FILE";
		_getch();
		exit(-1);
	}
	fileToOpen.unsetf(ios::skipws);
	char chars[2];
	for(int i=0;!fileToOpen.eof();i++)
	{
		chars[1]='0';
		fileToOpen>>chars[0];
		if(chars[0]=='\n')
			countLines++;
		if((countLines==12)&&(chars[0]==' '))
		{
			fileToOpen>>chars[1];
			if(chars[1]==' ')
				countSpaces++;
		}
	}
	cout<<"Total number of elements:"<<countSpaces;
	_getch();
}

