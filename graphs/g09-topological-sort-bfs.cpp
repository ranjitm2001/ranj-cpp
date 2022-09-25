#include <iostream>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

class Graph {
private:
  bool isDirected;
  unordered_map<int, int> inDegree;

  void topologicalSortBFSHelper(int node, unordered_map<int, bool> &visited,
                                unordered_map<int, int> &currInDegree,
                                queue<int> &component) {
    visited[node] = true;
    component.push(node);
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
      int front = q.front();
      q.pop();
      for (auto i : AdjList[front]) {
        if (!visited[i]) {
          visited[i] = true;
          currInDegree[i]--;
          if (currInDegree[i] == 0) {
            component.push(i);
          }
          q.push(i);
        }
      }
    }
  }

public:
  unordered_map<int, list<int>> AdjList;

  Graph(bool isDirected) : isDirected(isDirected) {}

  void AddEdge(int u, int v) {
    AdjList[u].push_back(v);
    inDegree[v]++;
    if (!isDirected) {
      AdjList[v].push_back(u);
    }
  }

  void Print() {
    for (pair<int, list<int>> i : AdjList) {
      cout << i.first << " --> ";
      for (int j : i.second) {
        cout << j << " ";
      }
      cout << endl;
    }
  }

  vector<queue<int>> TopologicalSortBFS() {
    unordered_map<int, bool> visited;
    vector<queue<int>> ans;
    for (int i = 0; i < AdjList.size(); i++) {
      if (!visited[i]) {
        unordered_map<int, int> currInDegree = inDegree;
        queue<int> component;
        topologicalSortBFSHelper(i, visited, currInDegree, component);
        ans.push_back(component);
      }
    }
    return ans;
  }
};

void PrintVQI(vector<queue<int>> input) {
  for (int i = 0; i < input.size(); i++) {
    while (!input[i].empty()) {
      int front = input[i].front();
      input[i].pop();
      cout << front << " ";
    }
    cout << endl;
  }
}

int main() {
  Graph graph = Graph(true);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 3);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 4);
  graph.AddEdge(4, 5);
  graph.AddEdge(5, 2);
  graph.Print();

  vector<queue<int>> ans = graph.TopologicalSortBFS();
  PrintVQI(ans);

  // If length of the TS list, is not equal to the number of the vertices
  // then, it is acyclic.
  
  return 0;
}