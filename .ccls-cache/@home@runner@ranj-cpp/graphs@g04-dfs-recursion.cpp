#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

using namespace std;

class Graph {
  private:
    bool isDirected;

  public:
    unordered_map<int, list<int>> AdjList;

    Graph(bool isDirected) {
      this->isDirected = isDirected;
    }

    void AddEdge(int u, int v) {
      AdjList[u].push_back(v);
      if (!this->isDirected) {
        AdjList[v].push_back(u);
      }
    }

    void Print() {
      for (auto i : AdjList) {
        cout << i.first << " -> ";
        for (auto j : i.second) {
          cout << j << " ";
        }
        cout << endl;
      }
    }
};

void dfsHelper(int node, unordered_map<int, list<int>> adjList, unordered_map<int, bool> &visited, vector<int> &output) {
  visited[node] = true;
  output.push_back(node);
  for (auto i : adjList[node]) {
    if (!visited[i]) {
      dfsHelper(i, adjList, visited, output);
    }
  }
}

vector<vector<int>> depthFirstSearch(int V, int E, vector<vector<int>> &edges) {
  // Prepare adjList -- unordered_map<int, list<int>>
  Graph graph = Graph(false); // Undirected
  for (int i = 0; i < E; i++) {
    graph.AddEdge(edges[i][0], edges[i][1]);
  }
  // Prepare visitedMap -- unordered_map<int, bool>
  unordered_map<int, bool> visited(V);
  for (int i = 0; i < V; i++) {
    visited[i] = false;
  }
  
  vector<vector<int>> ans;
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {    
      vector<int> output;
      dfsHelper(i, graph.AdjList, visited, output);
      ans.push_back(output);
    }
  }
  return ans;
}

int main() {
  vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 5}, {4, 5}};
  vector<vector<int>> ans = depthFirstSearch(6, 7, edges);
  for (int i = 0; i < ans.size(); i++) {
    for (int j = 0; j < ans[i].size(); j++) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}