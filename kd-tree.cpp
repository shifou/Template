// http://acm.hdu.edu.cn/showproblem.php?pid=4347
// kd-tree
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define N 50004
#define K 10
const int INF = 1 << 30;
int d;
int level[N];
struct mlx {
    int x[K];
    bool operator <(const mlx &u) const {
        return x[d] < u.x[d];
    }
};
struct ok {
    int id;
    int val;
};
ok ans[20];
bool operator<(const ok& a, const ok& b) {
    return a.val < b.val;
}

priority_queue<ok> q;
int k,m;
mlx a[N];
mlx fk;
int dist(mlx &a, mlx& b) {
    int res = 0;
    for (int i = 0; i < k; i++)
        res += (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return res;
}
void build(int l, int r) {
    if (l >= r)
        return;
    int mid = (l + r) >> 1;
    int hold=-1,pos;
    for (int i = 0; i < k; i++) {
        d = i;
        int mini = min_element(a + l, a + r + 1)->x[d];
        int maxx = max_element(a + l, a + r + 1)->x[d];
        if(maxx - mini > hold)
        {
            hold=maxx-mini;
            pos=i;
        }
    }
    level[mid] = d = pos;
    nth_element(a + l, a + mid, a + r + 1);
    build(l, mid - 1);
    build(mid + 1, r);
}
void update(ok a) {
    if(q.size()<m)
        q.push(a);
    else if(q.size()==m)
    {
        if(q.top().val>a.val)
        {
            q.pop();
            q.push(a);
        }
    }
}
void ask(int l, int r) {
    if (l > r)
        return;
    if (l == r) {

        int dis= dist(a[l], fk);
        ok b;
        b.id=l,b.val=dis;
        update(b);
        return;
    }
    int mid = (l + r) >> 1;
    int dis = (fk.x[level[mid]]) - (a[mid].x[level[mid]]);
    int tempdist = dist(a[mid], fk);
    ok b;
    b.id=mid,b.val=tempdist;
    update(b);
    //printf("level %d %d\n",level[mid],dis);
    int l1 = l, r1 = mid - 1, l2 = mid + 1, r2 = r;
    if (dis > 0)
        swap(l1, l2), swap(r1, r2);
    ask(l1, r1);
    if (dis * dis < q.top().val || q.size()<m)
        ask(l2, r2);

}
int main() {
    int t;
    int n;

    while (scanf("%d%d", &n, &k) != EOF) {

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < k; j++) {
                scanf("%d", &a[i].x[j]);
            }
        }
        build(0, n - 1);
        scanf("%d", &t);
        while (t--) {
            for (int i = 0; i < k; i++)
                scanf("%d", &fk.x[i]);
            scanf("%d", &m);
            printf("the closest %d points are:\n", m);
            ask(0,n-1);
            for(int i=0;!q.empty();i++) {ans[i]=q.top();q.pop();}
            for(int j=m-1;j>=0;j--)
            {
                for(int i=0;i<k;i++)
                    printf("%d%c",a[ans[j].id].x[i],i==k-1?'\n':' ');
            }
        }
    }
    return 0;
}