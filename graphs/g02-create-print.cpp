#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> printAdjacency(int numNode, int numEdge, vector<vector<int>> &edges) {
  vector<int> neighboursList[numNode];
  for (int i = 0; i < numEdge; i++) {
    int u = edges[i][0];
    int v = edges[i][1];

    // Undirected graph -- so, 2 ways
    neighboursList[u].push_back(v);
    neighboursList[v].push_back(u);
  }

  // Create list with the known size, already
  vector<vector<int>> customList(numNode);
  for (int i = 0; i < numNode; i++) {
    customList[i].push_back(i);
    for (int j = 0; j < neighboursList[i].size(); j++) {
      customList[i].push_back(neighboursList[i][j]);
    }
  }
  return customList;
}

void printList(vector<vector<int>> list) {
  for (int i = 0; i < list.size(); i++) {
    for (int j = 0; j < list[i].size(); j++) {
      cout << list[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  /*
    Input:
    0---1---2
        |___3
    Output:
    0 1`
    1 0 2 3
    2 1
    3 1
  */
  vector<vector<int>> edges = {{0, 1}, {1, 2}, {1, 3}};
  vector<vector<int>> customList = printAdjacency(4, 3, edges);
  printList(customList);
  return 0;
}