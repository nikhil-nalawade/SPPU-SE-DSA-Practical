// Represent a given graph using adjacency matrix/list to perform DFS and using adjacency 
// list  to  perform  BFS.  Use  the  map  of  the  area  around  the  college  as  the  graph.  Identify 
// the prominent land marks as nodes and perform DFS and BFS on that.

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Graph {
public:
    int numNodes;           // Number of nodes
    int **adjMatrix;        // Adjacency matrix
    int **adjList;          // Adjacency list
    bool *visited;          // Array to track visited nodes

    Graph() {
        numNodes = 0;
        adjMatrix = nullptr;
        adjList = nullptr;
        visited = nullptr;
    }

    // Create graph using adjacency matrix
    void createMatrix() {
        cout << "Enter the number of nodes: ";
        cin >> numNodes;

        adjMatrix = new int*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            adjMatrix[i] = new int[numNodes];
        }

        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                cout << "Enter 1 if there is an edge from node " << i << " to node " << j << ", else 0: ";
                cin >> adjMatrix[i][j];
            }
        }
    }

    // Create graph using adjacency list
    void createList() {
        cout << "Enter the number of nodes: ";
        cin >> numNodes;

        adjList = new int*[numNodes];
        for (int i = 0; i < numNodes; i++) {
            adjList[i] = new int[numNodes](); // Initialize with zeros
        }

        for (int i = 0; i < numNodes; i++) {
            int edges;
            cout << "Enter the number of nodes connected to node " << i << ": ";
            cin >> edges;

            cout << "Enter the nodes connected to node " << i << ": ";
            for (int j = 0; j < edges; j++) {
                int connectedNode;
                cin >> connectedNode;
                adjList[i][connectedNode] = 1;
            }
        }
    }

    // Display the adjacency matrix
    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n";
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Display the adjacency list
    void displayList() {
        cout << "\nAdjacency List:\n";
        for (int i = 0; i < numNodes; i++) {
            cout << "Node " << i << " is connected to: ";
            for (int j = 0; j < numNodes; j++) {
                if (adjList[i][j] == 1) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

    // Depth First Search (DFS) using adjacency matrix
    void dfsMatrix(int startNode) {
        visited = new bool[numNodes]();
        stack<int> s;
        s.push(startNode);

        cout << "DFS traversal starting from node " << startNode << ": ";

        while (!s.empty()) {
            int node = s.top();
            s.pop();

            if (!visited[node]) {
                cout << node << " ";
                visited[node] = true;
            }

            for (int i = numNodes - 1; i >= 0; i--) {
                if (adjMatrix[node][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
        cout << endl;

        delete[] visited;
    }

    // Breadth First Search (BFS) using adjacency list
    void bfsList(int startNode) {
        visited = new bool[numNodes]();
        queue<int> q;
        q.push(startNode);
        visited[startNode] = true;

        cout << "BFS traversal starting from node " << startNode << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << node << " ";

            for (int i = 0; i < numNodes; i++) {
                if (adjList[node][i] == 1 && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;

        delete[] visited;
    }
};

int main() {
    Graph graph;
    int choice;
    bool flag = true;

    while (flag) {
        cout << "\nMenu:";
        cout << "\n1. Create Graph (Matrix)";
        cout << "\n2. Display Graph (Matrix)";
        cout << "\n3. Perform DFS (Matrix)";
        cout << "\n4. Create Graph (List)";
        cout << "\n5. Display Graph (List)";
        cout << "\n6. Perform BFS (List)";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                graph.createMatrix();
                break;
            case 2:
                graph.displayMatrix();
                break;
            case 3: {
                int startNode;
                cout << "Enter the starting node for DFS: ";
                cin >> startNode;
                graph.dfsMatrix(startNode);
                break;
            }
            case 4:
                graph.createList();
                break;
            case 5:
                graph.displayList();
                break;
            case 6: {
                int startNode;
                cout << "Enter the starting node for BFS: ";
                cin >> startNode;
                graph.bfsList(startNode);
                break;
            }
            case 7:
                flag = false;
                cout << "Exiting program!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}