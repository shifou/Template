#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int next[100], pattern_len, str_len;
char * pattern, * str;
void getNext()
{
	int i = 0,j; 
	next[0] = j = -1;
	while (i < pattern_len - 1)
	{
		if (j == -1 || pattern[i] == pattern[j])
		{
			++i;
			++j;
			if (pattern[i] != pattern[j]) 
				next[i] = j;
			else 
				next[i] = next[j];
		}
		else
			j = next[j];
	}
}
int kmp()
{
	int i = 0, j = 0;
	str_len = strlen(str);
	getNext(); 
	while (i < str_len && j < pattern_len)
	{
		if (j == -1 || str[i] == pattern[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j == pattern_len)
		return i - j;
	else
		return -1;
}
void printNext() 
{
	for (int i = 0; i < pattern_len; i++)
		cout << next[i] << " ";
	cout << endl;
}
int main()
{
	// get the starting index that match the pattern in str 
	str = "BBC ABCDAB ABCDABCDABDE";
	pattern = "ABCDABD";
	pattern_len = strlen(pattern);
	int res = kmp();
	cout << res << endl;
	printNext();

}