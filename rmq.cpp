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

int f[1000][12]; //动规数组
int N, M; //N:区间大小，M:数据个数
inline void build(); //预处理ST算法数组
inline int get(int b, int e); //取得最大值
inline void set(int x, int y); //将y放置在x处并更新
int main() {
    int i, b, e, p;
    cin >> N;
    for (i = 1; i <= N; i++)
        cin >> f[i][0];
    build();

    cin >> M;
    int c;
    for (i = 1; i <= M; i++) {
        cin >> c;
        if (c == 1) { //修改
            cin >> b >> p;
            set(b, p);
        } else { //查询
            cin >> b >> e;
            cout << get(b, e) << endl;
        }
    }
    system("pause");
}
void build() {
    /*l=(int)log2(N)*/;
    for (int j = 1; (1 << j) <= N; j++)
    {
        for (int i = 1; i + (1 << j) - 1 <= N; i++)
        {
            f[i][j] = max(f[i][j - 1] , f[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int get(int b, int e) {
    int j = (int) log2(e - b + 1); //区域长度的j,使得(2^j)大于等于请求区间的一半即可
    return max(f[b][j] , f[e - (1 << j) + 1][j]); //f[e-(1<<j)+1][j] 表示以e为中点长为2^j的区间
}
void set(int x, int y) { //将y放置在x处并更新
    f[x][0] = y;
    for (int j = 1; (1 << j) <= N; j++)
    {
        for (int i = max(x - (1 << j) + 1, 1); i <= x && i + (1 << j) - 1 <= N; i++)
        {
            //应从最早包含x位的一位开始循环，即x-(1<<j)+1，但有可能为负数
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }
}
