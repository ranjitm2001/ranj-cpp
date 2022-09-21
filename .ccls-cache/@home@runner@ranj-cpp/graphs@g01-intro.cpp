#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class Graph {
  private:
    bool isDirected;

  public:
    unordered_map<int, list<int>> adjList;

    Graph(bool isDirected) {
      this->isDirected = isDirected;
    } 

    void addEdge(int u, int v) {
      adjList[u].push_back(v);
      if (!isDirected) {
        adjList[v].push_back(u);
      }
    }

    void printAdjList() {
      for (auto i : adjList) {
        cout << i.first << "-> ";
        for (auto j: i.second) {
          cout << j << " ";
        }
        cout << endl;
      }
    }
};

int main() {
  Graph graph = Graph(true);
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(2, 3);
  graph.addEdge(2, 4);
  graph.printAdjList();
  return 0;
}