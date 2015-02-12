#include <iostream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <stdio.h>
using namespace std;

int n, m, component[100005], compSize[100005], vis[100005];

//the graph with an edge between each two cities that requires teleportation
vector<int> graph[100005];
//the graph with reversed edges in graph;
vector<int> reverseGraph[100005];
vector<int> dfsVec;

void addEdge(int from, int to) {
    graph[from].push_back(to);
    reverseGraph[to].push_back(from);
}

//dfs to determine the finishing time of each node
void sccDFS(int u) {
    vis[u] = 1;
    for (int i = 0; i < graph[u].size(); i++) {
        if (!vis[graph[u][i]]) {
            sccDFS(graph[u][i]);
        }
    }
    dfsVec.push_back(u);
}

//find scc by dfs with decreasing finishing time
void findSCC(int u, int cmpNumber) {
    vis[u] = 1;
    component[u] = cmpNumber;
    for (int i = 0; i < reverseGraph[u].size(); i++) {
        if (!vis[reverseGraph[u][i]]) {
            findSCC(reverseGraph[u][i], cmpNumber);
        }
    }
}

void decomposeToSCC() {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            sccDFS(i);
        }
    }
    int cmpNumber = 0;
    memset(vis, 0, sizeof vis);
    for (int i = dfsVec.size() - 1; i >= 0; i--) {
        if (!vis[dfsVec[i]]) {
            findSCC(dfsVec[i], cmpNumber++);
        }
    }
}

int checkReduce(int u) {
    int res = compSize[component[u]] == 1;
    vis[u] = 1;
    for (int i = 0; i < graph[u].size(); i++) {
        if (!vis[graph[u][i]]) {
            res &= checkReduce(graph[u][i]);
        }
    }

    for (int i = 0; i < reverseGraph[u].size(); i++) {
        if (!vis[reverseGraph[u][i]]) {
            res &= checkReduce(reverseGraph[u][i]);
        }
    }
    return res;

}

int solve() {
    //decompose the graph to strongly connected components
    decomposeToSCC();

    int ans = n;
    //check number of nodes in each component
    for (int i = 1; i <= n; i++) {
        compSize[component[i]]++;
    }
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            ans -= checkReduce(i);
        }
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int from, to;
        cin >> from >> to;
        addEdge(from, to);
    }

    cout << solve() << endl;

    return 0;
}

