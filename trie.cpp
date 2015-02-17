//find the prefix str in the dict
#include <iostream>
#include <string>
using namespace std;
struct ok
{
    int next[26];
};
ok a[3999895];
int id=1;
void ins(string s)
{ 
	int cur =0;
	for(int i =0;i<s.size();i++)
	{
		if(a[cur].next[s[i]-'a'])
		{
			cur =a[cur].next[s[i]-'a'];
		}
		else
		{
			a[cur].next[s[i]-'a'] =++id;
			cur =id;
		}
	}
}
bool find(string s)
{
	int cur=0;
	for(int i=0;i<s.size();i++)
	{
		if(a[cur].next[s[i]-'a'])
		{
			cur=a[cur].next[s[i]-'a'];
		}
		else
			return false;
		}
	return true;
}
int main()
{
    string hold;
    id=0;
    int i,j;
    //insert word in dict
    while(cin>>hold)  ins(hold);
    //given a word find whether exits a prefix string in dict
    while(cin>>hold) 
    {
        printf("%d\n", find(hold));
    }
    return 0;
}