//http://codeforces.com/contest/525/problem/B
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <climits>
using namespace std;


#define inf INT_MAX/5
int a[100010];
struct ok
{
	int l,r,val,flag;
};
ok tree[500050];
void build(int l,int r,int id)
{
	tree[id].val=tree[id].flag=0;
	tree[id].l=l,tree[id].r=r;
	if(l==r) return;
	// 1 3 2 1-2 3-3
	int mid = (l+r)>>1;
	build(l,mid,id*2);
	build(mid+1,r,id*2+1);
}
void add(int l,int r,int id)
{
	//printf("now %d %d %d %d\n",tree[id].l,tree[id].r,tree[id].val,tree[id].flag);
	if(tree[id].l>=l&&tree[id].r<=r)
	{
		tree[id].flag+=1;
		tree[id].val+=1;
		return;
	}
	if(tree[id].l==tree[id].r) {tree[id].flag=0;return;}
	if(tree[id].flag)
	{
		tree[2*id].flag+=tree[id].flag;
		tree[2*id+1].flag+=tree[id].flag;
		tree[2*id].val+=tree[id].flag;
		tree[2*id+1].val+=tree[id].flag;
		tree[id].flag=0;
	}
	int mid = (tree[id].l+tree[id].r)>>1;
	if(r<=mid) add(l,r,2*id);
	else if(l>=mid+1) add(l,r,2*id+1);
	else
	{
		add(l,r,2*id);
		add(l,r,2*id+1);
	}
}
int get(int l,int id)
{
	//printf("now %d %d %d %d %d\n",l,tree[id].l,tree[id].r,tree[id].val,tree[id].flag);
	if(tree[id].l==tree[id].r&&l==tree[id].l)
		return tree[id].val;
	if(tree[id].flag)
	{
			tree[2*id].flag+=tree[id].flag;
			tree[2*id+1].flag+=tree[id].flag;
			tree[2*id].val+=tree[id].flag;
			tree[2*id+1].val+=tree[id].flag;
			tree[id].flag=0;
	}
	int mid = (tree[id].l+tree[id].r)>>1;
	if(l<=mid) return get(l,2*id);
	else return get(l,2*id+1);
}
int main(){
	int n;
	string s;
	int t;
	while(cin>>s){
		scanf("%d",&n);
		//memset(tree+1,0,sizeof(tree));
		build(1,s.size()/2,1);
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			//printf("add %d %d\n",a[i],s.size()/2);
			add(a[i],s.size()/2,1);
		}
		//puts("------");
		for(int i=0;i<s.size()/2;i++)
		{

			int cc=get(i+1,1);
			//printf("num %d %d\n",cc,i+1);
			if(cc&1) {
				//printf("swap %c %c\n",s[i],s[s.size()-i-1]);
				swap(s[i],s[s.size()-i-1]);
			}
		}
		cout<<s<<"\n";
	}


}
