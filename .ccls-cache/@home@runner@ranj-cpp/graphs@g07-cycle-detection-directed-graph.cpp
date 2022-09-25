#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class Graph {
private:
  bool isDirected;

  void isCyclicDirectedDFSHelper(int node, unordered_map<int, bool> &visited,
                                 unordered_map<int, bool> &dfsVisited,
                                 bool &isCyclic) {
    visited[node] = true;
    dfsVisited[node] = true;
    for (auto i : AdjList[node]) {
      if (!visited[i]) {
        isCyclicDirectedDFSHelper(i, visited, dfsVisited, isCyclic);
      }
      if (dfsVisited[i]) {
        isCyclic = true;
        return;
      }
    }
    dfsVisited[node] = false;
  }

public:
  unordered_map<int, list<int>> AdjList;

  Graph(bool isDirected) : isDirected(isDirected) {}

  void AddEdge(int u, int v) {
    AdjList[u].push_back(v);
    if (!isDirected) {
      AdjList[v].push_back(u);
    }
  }

  void Print() {
    for (auto i : AdjList) {
      cout << i.first << " --> ";
      for (auto j : i.second) {
        cout << j << " ";
      }
      cout << endl;
    }
  }

  bool IsCyclicDirectedDFS() {
    // visited and dfsVisited
    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;
    bool isCyclic = false;
    for (int i = 0; i < AdjList.size(); i++) {
      if (!visited[i]) {
        isCyclicDirectedDFSHelper(i, visited, dfsVisited, isCyclic);
      }
    }
    return isCyclic;
  }
};

int main() {
  Graph graph = Graph(true);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(3, 2);
  graph.AddEdge(2, 4);
  graph.AddEdge(4, 5);
  graph.AddEdge(5, 6);
  graph.AddEdge(6, 4);
  graph.Print();
  cout << graph.IsCyclicDirectedDFS() << endl;
  return 0;
}