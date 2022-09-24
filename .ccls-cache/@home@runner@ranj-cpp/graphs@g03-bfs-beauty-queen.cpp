#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>

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

    void AddEdgePairs(vector<pair<int, int>> edges) {
      for (auto i : edges) {
        AdjList[i.first].push_back(i.second);
        if (!this->isDirected) {
          AdjList[i.second].push_back(i.first);
        }
      }
    }

    void Print() {
      for (int i = 0; i < AdjList.size(); i++) {
        cout << i << " -> "; 
        list<int>::iterator it;
        for (it = AdjList[i].begin(); it != AdjList[i].end(); it++) {
          cout << *it << " ";
        }
        cout << endl;
      }
    }

    int NumNodes() {
      int count = 0;
      for (auto i : AdjList) {
        count++;
      }
      return count;
    }
};

void bfsHelper(unordered_map<int, list<int>> adjList, unordered_map<int, bool> &visited, vector<int> &ans, int startNode) {
  queue<int> nodeQ;
  nodeQ.push(startNode);
  visited[startNode] = true;

  while (!nodeQ.empty()) {
    int frontNode = nodeQ.front();
    nodeQ.pop();

    ans.push_back(frontNode);
    for (auto i : adjList[frontNode]) {
      if (!visited[i]) {
        nodeQ.push(i);
        visited[i] = true;
      }
    }
  }

}

vector<int> BFS(int vertex, vector<pair<int, int>> edges) {
  vector<int> ans;
  Graph graph = Graph(false);
  graph.AddEdgePairs(edges);

  unordered_map<int, bool> visited;
  for (int i = 0; i < vertex; i++) {
    visited[i] = false;
  }
  for (int i = 0; i < vertex; i++) {
    if (!visited[i]) {
      bfsHelper(graph.AdjList, visited, ans, i);
    }
  }
  return ans;
}

int main() {
  vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {1, 3}, {2, 4}, {0, 4}};
  vector<int> ans = BFS(5, edges);
  for (auto i : ans) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}