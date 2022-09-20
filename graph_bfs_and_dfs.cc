#include <iostream>
#include "vector.h"
#include "list.h"
#include "queue.h"

using std::cin;
using std::cout;
using std::string;
using std::endl;

vector<list<int>> inputGraph() {
    cout << "Please input the adjacency matrix : " << endl;
    int n; cin >> n;
    vector<list<int> > adjList;
    for (int i = 0; i < n; i++) {
        list<int> l; int t;
        for (int j = 0; j < n; j++) {
            cin >> t;
            if (t) l.push_back(j);
        }
        adjList.push_back(l);
    }
    return adjList;
}

vector<int> graphBfs(vector<list<int>>& adjList) {
    vector<int> seq; 
    queue<int> q(100); 
    int book[100] = {0};
    q.push(0); seq.push_back(0); book[0] = 1;
    while (!q.empty()) {
        int number = q.front(); q.pop();
        for (auto iter = adjList[number].begin(); iter != adjList[number].end(); iter++) {
            if (!book[*iter]) {
                q.push(*iter); seq.push_back(*iter); book[*iter] = 1;
            }
        }
    }
    return seq;
}

void dfs(vector<list<int>>& adjList, vector<int>& seq, int *book, int number) {
    for (auto iter = adjList[number].begin(); iter != adjList[number].end(); iter++) {
        if (!book[*iter]) {
            seq.push_back(*iter); book[*iter] = 1;
            dfs(adjList, seq, book, *iter);
        }
    }
}

vector<int> graphDfs(vector<list<int>>& adjList) {
    vector<int> seq; int book[100] = {0};
    seq.push_back(0); book[0] = 1;
    dfs(adjList, seq, book, 0);
    return seq;
}

void ouputSeq(vector<int>& seq, string traver_type) {
    cout << traver_type << ": ";
    for (auto iter = seq.begin(); iter != seq.end(); iter++) {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(void)
{
    vector<list<int>> adjList = inputGraph();
    vector<int> seq = graphBfs(adjList);
    ouputSeq(seq, "bfs");
    seq = graphDfs(adjList);
    ouputSeq(seq, "dfs");
    return 0;
}