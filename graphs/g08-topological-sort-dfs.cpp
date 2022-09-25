#include <iostream>
#include <list>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
private:
  bool isDirected;

  void topologicalSortDFSHelper(int node, unordered_map<int, bool> &visited,
                                stack<int> &component) {
    visited[node] = true;
    for (auto i : AdjList[node]) {
      if (!visited[i]) {
        topologicalSortDFSHelper(i, visited, component);
      }
    }
    component.push(node);
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

  vector<stack<int>> TopologicalSortDFS() {
    unordered_map<int, bool> visited;
    vector<stack<int>> ans;
    for (int i = 0; i < AdjList.size(); i++) {
      if (!visited[i]) {
        stack<int> component;
        topologicalSortDFSHelper(i, visited, component);
        ans.push_back(component);
      }
    }
    return ans;
  }
};

void PrintVSI(vector<stack<int>> input) {
  for (int i = 0; i < input.size(); i++) {
    while (!input[i].empty()) {
      int top = input[i].top();
      input[i].pop();
      cout << top << " ";
    }
    cout << endl;
  }
}

int main() {
  Graph *graph = new Graph(true);
  graph->AddEdge(0, 1);
  graph->AddEdge(1, 2);
  graph->AddEdge(1, 3);
  graph->AddEdge(2, 3);
  graph->AddEdge(2, 4);
  graph->AddEdge(2, 5);

  graph->Print();
  PrintVSI(graph->TopologicalSortDFS());
  return 0;
}