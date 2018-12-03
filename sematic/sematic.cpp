#include<iostream>
#include<fstream>
using namespace std;
char getxt[1000];
int  main()
{
	ifstream fin("F:\\shuchu.txt", ios::in);
	int i = 0;
	int count = 0;
	for (i = 0; i < 1000; i++)
	{
		getxt[i] = fin.get();
	}
	
	fin.close();
	while (getxt[count] != '\0')
	{
		cout << getxt[count] << endl;
		count++;
	}
	system("pause");
	return 0;
}
void start()
{
	int count = 0;
	int next = 0;
	char puttxt[100];
	int top = 0;
	char temp;
	while (getxt[count] != '\0')
	{
		temp = getxt[count];
		switch (temp)
		{
		case '<':
			count++;
		case '1':
		{
			next = count + 1;
			if (getxt[next] == ',')
			{
				next++;
				while()
			}
			
		}
		}
	}
}