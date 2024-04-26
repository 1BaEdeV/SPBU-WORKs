#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define NIL 0

bool bfs(vector<vector<int>>& graph, vector<int>& pair, vector<bool>& visited) {
    int n = pair.size() - 1;
    queue<int> q;
    for (int u = 0; u <= n; u++) {
        if (pair[u] == NIL) {
            visited.assign(n + 1, false);
            q.push(u);
            visited[u] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : graph[u]) {
            if (pair[v] == NIL) {
                pair[v] = u;
                return true;
            } else if (!visited[pair[v]]) {
                visited[pair[v]] = true;
                q.push(pair[v]);
            }
        }
    }

    return false;
}

int maxMatching(vector<vector<int>>& graph) {
    int n = graph.size() - 1;
    vector<int> pair(n + 1, NIL);
    int matching = 0;

    for (int u = 1; u <= n; u++) {
        vector<bool> visited(n + 1, false);
        if (bfs(graph, pair, visited)) {
            matching++;
        }
    }

    return matching;
}
int main() {
    // Пример двудольного графа
    vector<vector<int>> graph = {{2,3}, {1, 4}, {3}, {3}};

    int maxMatch = maxMatching(graph);
    cout << "Максимальный размер пароса: " << maxMatch << endl;

    return 0;
}
