#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

//ребро графа
struct Edge{
    int target;
    int weight;
};
// куча несбалансированная поэтому без хипифай
class BinaryHeap{
private:
    vector<pair<int,int>> heap; // пары: (расстояние, вершина)

public:
    void push(int distance, int vertex) { //добавление  для кучи для дикстры
        heap.push_back(make_pair(distance, vertex));
    }
    pair<int, int> pop() { // достаем элемент
        pair<int, int> minPair=make_pair(INF, -1);
        for (const auto& node:heap) {
            if (node.first<minPair.first) {
                minPair=node;
            }
        }
        for(auto it=heap.begin();it!=heap.end();++it) {
            if (*it==minPair) {
                heap.erase(it);
                break;
            }
        }
        return minPair;
    }

    bool isEmpty() {//проверка на пустоту кучи
        return heap.empty();
    }

    void removeShortestPath(vector<vector<Edge>>& graph,int start,int target) //удаляем путь снизу вверх
        int current=target;
        while (current!=start) {
            int parent=-1;
            for (int i=0;i<graph[current].size();i++) {
                if (graph[current][i].target==current) {
                    parent=i;
                    break;
                }
            }
            if (parent != -1) {
                graph[current].erase(graph[current].begin()+parent);
                current=graph[current][parent].target;
            }else{
                break;
            }
        }
    }
};

void dijkstrabinheap(vector<vector<Edge>>& graph, int start, int target) {//алгоритм дийсктры собственной персоны
    int n = graph.size();//для начало само с собой
    vector<int> distance(n, 9999999999);//вектор расстояний максимальных
    vector<int> parent(n, -1);//вектор родительских вершин
    BinaryHeap heap;//решил функцию не делать методом чтоб потом в простом графе просто реализовать можно было

    distance[start] = 0;//начальное расстояние понятное дело 0
    heap.push(0, start);//первая вершина

    while (!heap.isEmpty()) {//пока полностью
        int u = heap.pop().second;// достаём номер вершины

        for (const Edge& edge : graph[u]) {//достаем веса соседних ребер
            int v=edge.target;
            int w=edge.weight;

            if (distance[v]>distance[u]+w) {//проверяем на наименьшее расстояние и заменяем дистанцию
                distance[v]=distance[u]+w;
                parent[v]=u;

                heap.push(distance[v],v);
            }
        }
    }
    for(int i=0;i<distance.size();i++){
        cout<<"Кратчайшее расстояние от вершины"<<start<<"до"<<i<<": "<< distance[i]<<endl;
    }
    // Удаление кратчайшего пути между start и target
    heap.removeShortestPath(graph, start, target);//а потом удалаяем кратчайший путь до вершин

    cout<<"Кратчайший путь между вершинами"<<start<<"и"<<target<<"удален"<<endl;
}
// функцию удаления я как ни старался, не удаляется, посмотрите, пожалуйста, как лучше поступить
int main() {
    int n = 6; // кол-во вершин в куче
    vector<vector<Edge>> graph(n);

    // пример  ребер
    graph[0].push_back({1, 2});
    graph[0].push_back({2, 5});
    graph[1].push_back({2, 2});
    graph[1].push_back({3, 1});
    graph[2].push_back({3, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({4, 2});
    graph[4].push_back({5, 3});

    int start=0; // старт и до которого ищем кратчайщий путь
    int target=5; // Вершина, до которой ищем кратчайший путь

    dijkstrabinheap(graph,start,target);

    return 0;
}
//