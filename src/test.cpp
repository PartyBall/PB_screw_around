#include <iostream>
#include <stdio.h>

using namespace std;

int main ()
{
	//setvbuf (stdout, NULL, _IONBF, 0);
	for(int index_0 = 0; index_0 < 10000000; ++index_0)
	{
		printf("test\n");
	}
	cin.ignore();
	return 0;
}