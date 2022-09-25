#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

class Graph {
  private:
    bool isDirected;

    void isCyclicBFSHelper(int vertex, unordered_map<int, bool> &visited, unordered_map<int, int> &parent, bool &isCyclic) {
      queue<int> q;
      q.push(vertex);
      visited[vertex] = true;
      while (!q.empty()) {
        int front = q.front();
        q.pop();
        for (auto i : this->AdjList[front]) {
          // 5 (front) | 2, 3 (neighbor)
          // If any neighbor is already visited, then he should be his parent, else cyclic.
          if (visited[i] && i != parent[front]) {
            isCyclic = true;
            return;
          }
          if (!visited[i]) {
            parent[i] = front;
            visited[i] = true;
            q.push(i);
          }
        }
      }
    }
    
  public:
    unordered_map<int, list<int>> AdjList;

    Graph(bool isDirected) {
      this->isDirected = isDirected;
    } 

    void AddEdge(int u, int v) {
      this->AdjList[u].push_back(v);
      if (!this->isDirected) {
        this->AdjList[v].push_back(u);
      }
    }

    void Print() {
      for (auto i : this->AdjList) {
        cout << i.first << " -> ";
        for (auto j : i.second) {
          cout << j << " ";
        }
        cout << endl;
      }
    }

    bool IsCyclicBFS() {
      unordered_map<int, bool> visited(this->AdjList.size());
      for (int i = 0; i < this->AdjList.size(); i++) {
        visited[i] = false;
      }
      bool isCyclic = false;
      unordered_map<int, int> parent;
      for (int i = 0; i < this->AdjList.size(); i++) {
        parent[i] = -1;
        if (!visited[i]) {
          isCyclicBFSHelper(i, visited, parent, isCyclic);    
        }
      }
      return isCyclic;
    }
};

int main() {
  Graph graph = Graph(false);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 4);
  graph.AddEdge(2, 5);
  graph.AddEdge(3, 5);
  graph.Print();
  cout << graph.IsCyclicBFS() << endl;
  return 0;
}