#include <iostream>
#include <map>
#include <iostream>
#include <map>
#include <list>
#include <queue>
#include <string>

using namespace std;

class Node//класс веришин
{
public:
    int id;//айди вершины здания в графе
    string building;// названия здания
    Node(const int id, string info) : id(id), building(info) {}//конструктор
};
class Graph {// класс графа
private:
    map<int, list<int>> adjList; // Лист беттоных дорог
    map<int, Node*> nodes; // Лист зданий

public:
    void AddNode(const int id, string info) { // постройка нового здания
        Node* newNode = new Node(id, info);
        nodes[id] = newNode;
    }
    void AddEdge(const int id1, const int id2) { // укладка бетонных путей между зданиями
        adjList[id1].push_back(id2); //прокладываем дорогу в одну сторону
        adjList[id2].push_back(id1);// и в другую сторону, а зачем если есть... на самом деле это для неориентированного графа
    }
    void DFS(int startId) { // обход в глубину, но для этой здачи не нужно на самом деле
        map<int, bool> visited;//список уже посещенных зданий
        DFSmake(startId, visited);// вызываем функцию
    }
    void DFSmake(int v, map<int, bool>& visited) { // сама реализация
        visited[v] = true;//изначальную уже посетили
        cout << nodes[v]->building << v << endl;//выводим что посетили
        _List_iterator<int> i;// создаём список итератора, чтоб удобней было пробегаться по списку ребер исходящей из вершины
        for ( i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i]) {//если в этой веришне не были...
                DFSmake(*i, visited);//значит пробегаемся по ней и ей другим дорогам рекурсивно
            }
        }
    }
    void BFS(int startId) {//обход в ширину
        map<int, bool> visited;// снова делаем список посещенных зданий
        queue<int> queue; // делаем очередь из вершин каждого уровня по которым нужно будет пробежаться
        visited[startId] = true;//начальный город посетили
        queue.push(startId);//начинаем с начального очередь
        while (!queue.empty()) {//пока очередь не кочится
            int node = queue.front();//берем из очереди
            cout << "Visited " << nodes[node]->building << endl;//
            queue.pop();
            for (int i : adjList[node]) {//проходимся по вершинам этого уровня
                if (!visited[i]) {
                    queue.push(i);// если не были там, то дальше спустимся ну уровень и будем проходить по веришнам, связанными с этой
                    visited[i] = true;//отметили, что мы ее посетили
                }
            }
        }
    }
};
int main(){
    Graph g;
    g.AddNode(1, "My House");
    g.AddNode(2, "Pharmacy");
    g.AddNode(3, "Tolegenov Company");
    g.AddNode(4, "Shop");
    g.AddNode(5, "Police");
    g.AddNode(6, "Hospital");
    g.AddNode(7, "School");
    g.AddNode(8, "Lenin's Monument");
    g.AddEdge(1, 5);
    g.AddEdge(1, 7);
    g.AddEdge(1, 4);
    g.AddEdge(7, 5);
    g.AddEdge(7, 3);
    g.AddEdge(5, 6);
    g.AddEdge(5, 4);
    g.AddEdge(6, 8);
    g.AddEdge(3, 2);
    g.AddEdge(4, 2);
    cout << "DFS " << std::endl;
    g.DFS(1);
    cout << "BFS" << endl;
    g.BFS(1);
    return 0;
}