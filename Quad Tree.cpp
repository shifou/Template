//http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=1788
#include<iostream>
#include<queue>
#include<cstdio>
#include<cstring>
using namespace std;

#define maxn 520
char mp[maxn][maxn];
int n;

struct node
{
	string data;
	node * next[4];
	node()
	{
		data.clear();
		memset(next, NULL, sizeof(next));
	}
}*root;

queue<node *> q;

int cal(int x, int y, int size)
{
	int re1 = 0, re2 = 0;
	for(int i = x; i < x+size; i++)
	{
		for(int j = y; j < y+size; j++)
		{
			if(mp[i][j] == '1')
				re1++;
			else re2++;
		}
	}
	if(re1 == 0)return 0;
	if(re2 == 0)return 1;
	return -1;
}

node* dfs(int x, int y, int size)
{
	node *p;
	if(size == 1)
	{
		p = new node();
		p->data = "0";
		p->data += mp[x][y];
		for(int i = 0; i < 4; i++)
			p->next[i] = NULL;
		return p;
	}
	int re = cal(x, y, size);
	if(re == 0)
	{
		p = new node();
		p->data = "00";
		for(int i = 0; i < 4; i++)
			p->next[i] = NULL;
		return p;
	}
	else if(re == 1)
	{
		p = new node();
		p->data = "01";
		for(int i = 0; i < 4; i++)
			p->next[i] = NULL;
		return p;
	}
	else
	{
		p = new node();
		int len = size >> 1;
		p->data = "1";
		p->next[0] = dfs(x, y, size>>1);
		p->next[1] = dfs(x, y+len, size>>1);
		p->next[2] = dfs(x+len, y, size>>1);
		p->next[3] = dfs(x+len, y+len, size>>1);
		return p;
	}
}

void show(int x)
{
	if(x <= 9)
		printf("%c", x+48);
	else if(x == 10)
		printf("A");
	else if(x==11)
           putchar('B');
    else if(x==12)
       putchar('C');
    else if(x==13)
       putchar('D');
    else if(x==14)
       putchar('E');
    else
       putchar('F');
}

void change(string s)
{
	int len = s.size();
	int part = len % 4;
	int u = 1, num = 0;
	if(part > 0)
	{
		for(int i = part-1; i >= 0; i--)
		{
			num += u*(s[i] - 48);
			u <<= 1;
		}
		show(num);
	}
	for(int i = part; i < len; i += 4)
	{
		num = 0, u = 1;
		for(int j = i+3; j >= i; j--)
		{
			num += u*(s[j]-48);
			u <<= 1;
		}
		show(num);
	}
}

void bfs(node * root)
{
	while(!q.empty())
		q.pop();
	q.push(root);
	node * temp;
	string s = "";
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		s += temp->data;
		for(int i = 0; i < 4; i++)
		{
			if(temp->next[i] != NULL)
			{
				q.push(temp->next[i]);
			}
		}
	}
	change(s);
}

int main()
{
	int tot;
	scanf("%d", &tot);
	while(tot--)
	{
		scanf("%d", &n);
		getchar();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				scanf("%c", &mp[i][j]);
				getchar();
			}
		}
		root = dfs(0, 0, n);
		bfs(root);
		putchar(10);
	}
	return 0;
}