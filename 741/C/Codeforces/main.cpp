//
//  main.cpp
//  Codeforces
//
//  Created by loying on 16/7/27.
//  Copyright © 2016年 loying. All rights reserved.

/************************** 题解 **********************
 题目链接：http://codeforces.com/contest/741/problem/C
 题目大意：n对情侣坐成一圈（座位编号1和2n相邻），现在有两种食物（1和2），要求：
 1、情侣不吃相同的食物；
 2、连续的3个人必须包括2种食物；
 输出一种可行的方案。
 (1  ≤  n  ≤  105)
 
 Example
 input
 3
 1 4
 2 5
 3 6
 output
 1 2
 2 1
 1 2
 
 样例解释：
 3表示3对情侣；
 接下来是3行，分别表示情侣的两个座位；
 
 输出：
 n行，每行表示情侣的食物；
 如果无解，输出-1；
 
 
 题目解析：
 先看是否存在无解的情况。
 假定我们制定一个规则，先满足情侣不同的条件，当填入情侣中一人时，必然在另外一个位置填入相反的食物；
 
 于是我们采用这样的一种构造方式：
 座位从小到大分配食物，优先满足情侣的要求；
 其次，相邻的位置填入相反的食物；（贪心）
 最后如果出现111的情况，就选择中间的位置对调。（事实没有出现的111的情况，这里如果有人愿意证明下，非常感谢）

 
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
const int N = 201010;
int f[N], ans[N];
pair<int, int> p[N];

void dfs(int k, int cur) {
    ans[k] = cur;
    if (!ans[f[k]]) {
        dfs(f[k], 3 - cur);
    }
    if (!ans[k^1]) {
        dfs(k^1, 3 - cur);
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        p[i].first = u;
        p[i].second = v;
        f[u] = v;
        f[v] = u;
    }
    for (int i = 0; i < n; ++i) {
        if (!ans[2 * i]) {
            dfs(2 * i, 1);
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[p[i].first] << " " << ans[p[i].second] << endl;
    }
    
    return 0;
}
