#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;


//На сколько я понял, алгоритм Диница сводиться к нахождению крачтчайшего пути,
// его блокировки этого пути, чтобы не рассматривать его снова в поиске новых
// путей. Повторяем этот процесс, увеличивая тем самым поток. Для кратчайшего пути
// лучше использовать BFS.

bool bfs(vector<vector<int>>& expengraph, int start, int end, vector<int>& path, int& V) {
    vector<bool> visited(V, false);
    queue<int> ochered;
    visited[start] = true;
    ochered.push(start);
    path[start] = -1;
    while (!ochered.empty()) {
        int u = ochered.front();
        ochered.pop();
        for(int v=0; v<V;v++) {
            if (!visited[v] && expengraph[u][v] > 0) {
                path[v]=u;
                ochered.push(v);
                visited[v]=true;
                }
            }
        }
    return visited[end];

}

int Ford_Falkerson(vector<vector<int>>& graph, int & start, int & end) {

    int V = graph.size(); // кол-во вершин в графе

    vector<vector<int>> expengraph = graph;//копия графа, в котором будем изменять веса
    vector<int> path(V);//путь между начало и концом
    int maxFlow = 0;

    while (bfs(expengraph, start, end, path, V)) {//пока существует хоть какой-то путь из первой в конечную вершину
        int mincapacity = INT_MAX;
        int v = end;
        while (v != start) {//в этом цикле находим ребро с наименьшей пропускной способностью
            int u = path[v];
            mincapacity = min(mincapacity, expengraph[u][v]);
            v = u;
        }
        v = end;
        while (v != start) {//из каждого ребра в пути вычитаем наименьшую пропускную способность
            int u = path[v];
            expengraph[u][v]-=mincapacity;
            v = u;
        }
        maxFlow += mincapacity;//увеличиваем макс поток
        vector<int> path(V, -1);//обновляем путь
    }
    return maxFlow;
}

void k_potok_FF(int k, vector<vector<int>>& graph, int & start, int & end ){
    int m = Ford_Falkerson(graph, start, end);
    if (m>=k){
        cout<<"Поток размера "<<k<<" МОЖНО пустить по трубам между вершинами "<<start<<" и "<<end<<endl;
    }
    else{
        cout<<"Поток размера "<<k<<" НЕЛЬЗЯ пустить по трубам между вершинами "<<start<<" и "<<end<<endl;
    };
}

int main() {
    vector<vector<int>> graph = {
            {0, 2, 12, 4, 0},
            {0, 0, 0, 0, 7},
            {0, 7, 0, 5, 0},
            {0, 0, 0, 0, 8},
            {0, 0, 0, 0, 0},
    };
    int start = 0;
    int finish = 4;
    int maxFlow = Ford_Falkerson(graph, start, finish);
    cout << "Максимальный поток в сети: " << maxFlow << endl;

    return 0;
}