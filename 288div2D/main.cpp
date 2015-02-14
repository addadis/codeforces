//euler path
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <stdlib.h>
using namespace std;
int n, indegree[500005], outdegree[500005], vis[500005], f[500005], numNode, cnt;
string strings[200005];
map<string, int> hashmp;
vector<int> graph[500005];
stack<int> path;

int getHashCode(string s) {
    if (hashmp.count(s)) {
        return hashmp[s];
    }
    hashmp[s] = numNode;
    strings[numNode] = s;
    return numNode++;
}

int findSet(int x) {
    return f[x] == x? x : f[x] = findSet(f[x]);
}


void unionSet(int x, int y) {
    f[findSet(x)] = findSet(y);
}

//check the convectivity of graph
void checkConnectivity() {
    for (int i = 0; i < numNode; i++) {
        if (findSet(i) != findSet(0)) {
            cout << "NO" << endl;
            exit(0);
        }
    }
}

//the number of nodes with abs(indegree - outdegree)
//cannot exceed 2
void checkDegrees() {
    cnt = 0;
    for (int i = 0; i < numNode; i++) {
        //cout << indegree[i] << " " << outdegree[i] << endl;
        cnt += abs(indegree[i] - outdegree[i]);
    }
    if (cnt > 2) {
        cout << "NO" << endl;
        exit(0);
    }
}

void checkValid() {
    checkConnectivity();
    checkDegrees();
}

void dfsEuler(int u) {
    while (vis[u] < graph[u].size()) {
        dfsEuler(graph[u][vis[u]++]);
    }
    path.push(u);
}


void findEulerPath() {

    if (cnt == 2) {
        //we must start dfs with the node i such that outdegree[i]
        //- indegree[i] == 1
        for (int i = 0; i < numNode; i++) {
            if (outdegree[i] - indegree[i] == 1) {
                dfsEuler(i);
                break;
            }
        }
    } else {
        //otherwise we start dfs from any node;
        dfsEuler(0);
    }
}

int main()
{
    cin >> n;
    string s;
    for (int i = 0; i < 2 * n; i++) {
        f[i] = i;
    }
    for (int i = 0; i < n; i++) {
        cin >> s;
        //hash the string into numbers
        string s1 = s.substr(0, 2);
        string s2 = s.substr(1, 2);
        int c1 = getHashCode(s1);
        int c2 = getHashCode(s2);
        graph[c1].push_back(c2);
        indegree[c2]++;
        outdegree[c1]++;
        //union the two nodes in order to check connectivity of graph
        unionSet(c1, c2);
    }


    checkValid();

    findEulerPath();

    cout << "YES" << endl;

    cout << strings[path.top()];
    path.pop();
    while(!path.empty()) {
        cout << strings[path.top()][1];
        path.pop();
    }

    return 0;
}

