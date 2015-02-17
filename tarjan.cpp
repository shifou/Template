// http://poj.org/problem?id=1330
// Lowest Common Ancestor problem
// Tarjan offline algorithm
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;
#define N 200000
int par[N];
int ans[N];
int ind[N];
int head[N];
int qhead[N];
int dis[N];
int vis[N];
int id;
int qid;
struct edge{
	int to,next,cost;
};
struct query{
	int to,next,id;
};
edge ee[N*2];
query qq[N];
void addedge(int u,int v,int w)
{
	ee[id].to=v;
	ee[id].cost=w;
	ee[id].next=head[u];
	head[u]=id++;
}
void addquery(int u,int v,int i)
{
	qq[qid].to=v;
	qq[qid].id=i;
	qq[qid].next=qhead[u];
	qhead[u]=qid++;

	qq[qid].to=u;
	qq[qid].id=i;
	qq[qid].next=qhead[v];
	qhead[v]=qid++;
}
int find (int x)
{
    int j=x,hold;
    while(j!=par[j])  j=par[j];
    while(x!=par[x])
    {
    	hold=par[x];
    	par[x]=j;
    	x=hold;
    }
    return x;
}
void tarjan(int root)
{
	for(int i=head[root];i!=-1;i=ee[i].next)
	{
		dis[ee[i].to]=dis[root]+ee[i].cost;
		tarjan(ee[i].to);
		par[ee[i].to]=root;
		find(ee[i].to);
	}
	vis[root]=1;
	for(int i=qhead[root];i!=-1;i=qq[i].next)
	{
		if(vis[qq[i].to])
		{
			int lca= find(qq[i].to);
			ans[qq[i].id]=lca;
		}
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
    	int n, m;
        scanf("%d", &n);
        memset(head,-1,sizeof(int)*(n+1));
        memset(qhead,-1,sizeof(int)*(n+1));
        memset(ind,0,sizeof(int)*(n+1));
        memset(vis,0,sizeof(int)*(n+1));
        memset(dis,0,sizeof(int)*(n+1));
        qid=id=0;

        for (int i = 0; i < n-1; i ++){
            int u, v, w;
            scanf("%d%d", &u, &v);
            addedge(u, v, 0);
            ind[v]++;
        }

        int q=1;
        for (int i = 0; i < q; i ++){
            int u, v;
            scanf("%d%d", &u, &v);
            addquery(u, v,i);
        }

     
        vector<int> root;
        for(int i=1;i<=n;i++)
        {
        	if(ind[i]==0) root.push_back(i);
        	par[i]=i;
        }
        for(int i=0;i<root.size();i++)
           tarjan(root[i]);
        for (int i =0; i < q; i ++){
            printf("%d\n", ans[i]);
        }
	}
	return 0;
}