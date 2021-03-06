//
//  main.cpp
//  Codeforces
//
//  Created by loyinglin.
//  Copyright loyinglin. All rights reserved.

/************************** 题解 **********************
 题目链接：http://codeforces.com/contest/842/problem/C
 题目大意：
 有一颗根为1的树，共有n个点，每个点有一个权值a[i]；
 我们定义一个点的魅力值为：点到根的路径上，所有点的最大公约数（gcd）；
 同时，我们可以选择修改一个点的权值为0；（gcd(0, m) = m）
 问，每一个点的可能最大魅力值；
 
  (1 ≤ n ≤ 2e5)
  (1 ≤ a[i] ≤ 2e5)
 
 input
 3
 6 2 3
 1 2
 1 3
 output
 6 6 6
 样例解释：
 输入：首先n；
 接下来是n个数字a[i];
 然后n-1行，表示树的边；
 输出：n个点可能的最大魅力值；
 点1的最大魅力值是6（不做修改），点2的最大魅力值是6（修改点2的权值为0），点3的最大魅力值是6（修改点3的权值为0）
 
 
 
 
 题目解析：
 对于树上某个点u，其最大魅力值=点u到根上的所有数字的gcd；
 因为可以修改某个数字为0，那么先不考虑复杂度，可以枚举一遍去掉路径上某个数字后的gcd可能值；
 
 精简计算过程：
 // 每次有两种可能：1、把自己置为0
 // 2、把置为0 留给父类
 
 对每个点维护一个情况2的set，这样点u的set可以由父节点fat的set来计算，同时用于计算子节点v的set；
 
 ************************* 题解 ***********************/
#include<cstdio>
#include<cmath>
#include<stack>
#include<map>
#include<set>
#include<queue>
#include<deque>
#include<string>
#include<utility>
#include<sstream>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

typedef long long lld;
const int N = 201000, M = 3010100, inf = 0x7fffffff;
const lld llinf = 0x7fffffff7fffffffll;

vector<int> g[N];
set<int> may[N]; // 没有和父类gcd的
int a[N];
int vis[N];
int ans[N];


//最大公约数
int gcd(int m,int n){
    int t;
    if(m<n){t = n;n = m;m = t;}
    if(n == 0)
        return m;
    else
        return gcd(n,m%n);
}


void dfs(int u, int fat, int cur) {
    // 每次有两种可能：1、把自己置为0
    ans[u] = cur;
    may[u].insert(cur);

    // 2、把置为0 留给父类
    for (set<int>::iterator it = may[fat].begin(); it != may[fat].end(); ++it) {
        int tmp = gcd(*it, a[u]);
        ans[u] = max(ans[u], tmp);
        may[u].insert(tmp);
    }
    
    int gcdCur = gcd(cur, a[u]);
    for (int i = 0; i < g[u].size(); ++i) {
        int v = g[u][i];
        if (fat != v) {
            dfs(v, u, gcdCur);
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i + 1 < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    may[1].insert(0);
    ans[1] = a[1];
    for (int i = 0; i < g[1].size(); ++i) {
        int v = g[1][i];
        dfs(v, 1, a[1]);
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    
    return 0;
}

/**
 
 8
 48828 34632 22542 29094 11505 34476 46722 25545
 
 1 2
 2 3
 3 4
 4 5
 5 6
 6 7
 7 8
 
 
 8
 192 96 48 24 12 6 2 2
 
 1 2
 2 3
 3 4
 4 5
 5 6
 6 7
 7 8
 
 
 
 3
 12 11 11
 
 1 2
 2 3
 
 **/
