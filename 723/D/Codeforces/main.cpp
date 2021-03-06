//
//  main.cpp
//  Codeforces
//
//  Created by loying on 16/7/27.
//  Copyright © 2016年 loying. All rights reserved.

/************************** 题解 **********************
 题目链接：http://codeforces.com/contest/723/problem/D
 题目大意：
 给出n行m列的cell，每个cell与其上下左右联通；
 cell为*表示陆地，为.表示水，n*m的cell之外是海洋；
 被陆地围起来，并且没有和海洋连接的区域称为湖；
 
 现在要求把某些cell从.改成*，使得图只有k个湖；（给出的图，包括不小于k个湖的数量）
 
 要求给出修改的点最少；
 输出最少的修改点数，再输出修改之后n*m的cell。
  
 n, m and k (1 ≤ n, m ≤ 50, 0 ≤ k ≤ 50)
 
 
 Example
 input
 5 4 1
 ****
 *..*
 ****
 **.*
 ..**
 output
 1
 ****
 *..*
 ****
 ****
 ..**
 
 
 
 题目解析：
 要使得修改的点最少，那么应该从cell最少的湖开始修改；
 可以对全图进行一次遍历，用dfs找出所有的湖，然后排序；
 
 Tips：不要给函数定义太复杂的功能；
 这次在尝试**在dfs的返回值携带数量和当前是否为湖的信息**，导致WA了几次；
 
 
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
const int N = 51;

char str[N][N];
int vis[N][N];
vector<pair<int, int> > p;
int cnt, n, m, ok;

char dir[4][2] ={
    -1, 0,
    1, 0,
    0, -1,
    0, 1
};

int dfs(int u, int v) {
    vis[u][v] = cnt;
    int ret = 1;
    for (int i = 0; i < 4; ++i) {
        int x = u + dir[i][0], y = v + dir[i][1];
        if (str[x][y] == '.' && !vis[x][y]) {
            if (x == 0 || x == n - 1 || y == 0 || y == m - 1) { // 和海洋相连
                ok = 0;
            }
            ret += dfs(x, y);
        }
    }
    return ret;
}

int main(int argc, const char * argv[]) {
    int k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> str[i];
    }
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < m - 1; ++j) {
            if (!vis[i][j] && str[i][j] == '.') {
                ok = 1;
                ++cnt;
                int num = dfs(i, j);
                if (ok) {
                    p.push_back(make_pair(num, cnt));
                }
            }
        }
    }
    sort(p.begin(), p.end());
    int sum = 0;
    for (int z = 0; z < p.size() - k; ++z) {
        int t = p[z].second;
        sum += p[z].first;
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                if (vis[i][j] == t) {
                    str[i][j] = '*';
                }
            }
        }
    }
    cout << sum << endl;
    for (int i = 0; i < n; ++i) {
        cout << str[i] << endl;
    }
    return 0;
}

/*
 
 5 5 1
 **.**
 ..*.*
 **.**
 **.**
 *...*
 
 
 10 50 2
 *************************************************
 *...............................................*
 *.*********************************************.*
 *.*...........................................*.*
 *.*.*****************************************.*.*
 *.*.*......................................**.*.*
 *.*.***************************************.*.*.*
 *.*.*.....................................*.*.*.*
 *...*.***********************************.*.*.*.*
 *************************************************
 
 
 
 
 10 50 10
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 
 
 
 
 
 50 50 0
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 .*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*
 *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.
 
 
 50 50 50
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 ********.****.************.*******.**.***.********
 **************************************************
 *****..****************************.****.*.*******
 *******.*********.****.*.*.*.*********************
 *******.***********.*.****.**.*******..****.******
 ********.*********************.*********.*********
 **********.******.*.**********.****.****.**.*.****
 *****.******.**.***.*.********.***.*.**.**.*******
 .***.***.*****.******.********.**..**.*.**.***.***
 *****.******.**.***.*.********.***.*.**.**.*******
 
 */
