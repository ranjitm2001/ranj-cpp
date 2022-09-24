#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <queue>

using namespace std;

class Graph {
  private:
    bool isDirected;
    int numEdges;

    void bfs(int vertex, unordered_map<int, bool> &visited, vector<int> &component) {
      queue<int> q;
      q.push(vertex);
      while (!q.empty()) {
        int front = q.front();
        visited[front] = true;
        component.push_back(front);
        q.pop();
        for (auto i : this->AdjList[front]) {
          if (!visited[i]) {
            visited[i] = true;
            q.push(i);
          }
        }
      }
    }

    void dfs(int vertex, unordered_map<int, bool> &visited, vector<int> &component) {
      visited[vertex] = true;
      component.push_back(vertex);
      for (auto i : this->AdjList[vertex]) {
        if (!visited[i]) {
          dfs(i, visited, component);
        }
      }
    }

  public:
    unordered_map<int, list<int>> AdjList;

    Graph(bool isDirected) {
      this->isDirected = isDirected;
      this->numEdges = 0;
    }

    void AddEdge(int u, int v) {
      AdjList[u].push_back(v);
      numEdges++;
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

    int NumVertices() {
      return this->AdjList.size();
    }

    int NumEdges() {
      return this->numEdges;
    }

    vector<vector<int>> BFS() {
      unordered_map<int, bool> visited(this->NumVertices());
      for (int i = 0; i < this->NumVertices(); i++) {
        visited[i] = false;
      }
      vector<vector<int>> ans;
      for (int i = 0; i < this->NumVertices(); i++) {
        if (!visited[i]) {
          vector<int> component;
          bfs(i, visited, component);
          ans.push_back(component);
        }
      }
      return ans;
    }

    vector<vector<int>> DFS() {
      unordered_map<int, bool> visited(this->NumVertices());
      for (int i = 0; i < this->NumVertices(); i++) {
        visited[i] = false;
      }
      vector<vector<int>> ans;
      for (int i = 0; i < this->NumVertices(); i++) {
        if (!visited[i]) {
          vector<int> component;
          dfs(i, visited, component);
          ans.push_back(component);
        }
      }
      return ans;
    }
};

void PrintVVI(vector<vector<int>> input) {
  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      cout << input[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  Graph graph = Graph(false);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(1, 4);
  graph.AddEdge(3, 4);
  graph.AddEdge(5, 6);
  graph.AddEdge(5, 8);
  graph.AddEdge(6, 7);
  graph.Print();
  vector<vector<int>> bfs = graph.BFS();
  vector<vector<int>> dfs = graph.DFS();
  PrintVVI(bfs);
  PrintVVI(dfs);
  return 0;
}