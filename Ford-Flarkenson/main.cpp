#include <iostream>
#include <vector>

using namespace std;


bool dfs(vector<vector<int>>& expengraph, int u, int end, vector<int>& path, int& V) {

    vector<bool> visited(V, false);
    visited[u] = true;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && expengraph[u][v] > 0) {
            path[v] = u;
            if (v == end) {;
                return true;

            }
            if (dfs(expengraph, v, end,  path, V)) {
                return true;
            }
        }
    }
    return false;
}

int Ford_Falkerson(vector<vector<int>>& graph, int & start, int & end) {

    int V = 5; // кол-во вершин в графе

    vector<vector<int>> expengraph = graph;//копия графа, в котором будем изменять веса
    vector<int> path(V, -1);//путь между начало и концом
    int maxFlow = 0;


    while (dfs(expengraph, start, end, path, V)) {//пока существует хоть какой-то путь из первой в конечную вершину
        int mincapacity = 9999999999999;
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
    k_potok_FF(6, graph, start, finish);
    cout << "Максимальный поток в сети: " << maxFlow << endl;

    return 0;
}
