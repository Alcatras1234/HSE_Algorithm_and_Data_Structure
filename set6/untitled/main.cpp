#include <iostream>
#include <vector>
#include <queue>
#include <climits>



struct Edge {
    long dest, capacity, curFlow;

    Edge(long dest, long capacity, long flow)
            : dest(dest), capacity(capacity), curFlow(flow) {}
};

std::vector<std::vector<long>> adjList; // Список смежности для индексов ребер.
std::vector<Edge> edge; // Вектор ребер.
std::vector<long> depth; // Глубина для каждой вершины
std::vector<long> searchPointer; // указатели для DFS

// Добавляет ребро в граф
void AddEdge(long from, long to, long capacity) {
    adjList[from].push_back(edge.size());
    edge.emplace_back(to, capacity, 0);
    adjList[to].push_back(edge.size());
    edge.emplace_back(from, 0, 0); // Обратное ребро для алгоритма отмены
}

// Обновляет уровни вершин, выполняя BFS
bool BFS(long source, long sink) {
    fill(depth.begin(), depth.end(), -1);
    std::queue<long> visited;
    visited.push(source);
    depth[source] = 0;
    size_t i = 0;

    while (!visited.empty() && depth[sink] == -1) {
        long currentNode = visited.front();
        visited.pop();
        for (long edgeIndex: adjList[currentNode]) {
            long nextNode = edge[edgeIndex].dest;
            if (depth[nextNode] == -1 && edge[edgeIndex].curFlow < edge[edgeIndex].capacity) {
                visited.push(nextNode);
                depth[nextNode] = depth[currentNode] + 1;
            }
        }
    }
    return depth[sink] != -1;
}


long DFS(long node, long sink, long toPush) {
    if (toPush == 0)
        return 0;
    if (toPush != 0 )
        if (node == sink)
            return toPush;

    for(long &edgeIndex = searchPointer[node]; edgeIndex < adjList[node].size(); ++edgeIndex) {
        long curEdgeIndex = adjList[node][edgeIndex];
        long nextNode = edge[curEdgeIndex].dest;
        if (depth[node] + 1 != depth[nextNode] ||
            edge[curEdgeIndex].curFlow == edge[curEdgeIndex].capacity)
            continue;

        long flow = DFS(nextNode, sink,
                        std::min(toPush, edge[curEdgeIndex].capacity - edge[curEdgeIndex].curFlow));
        if (flow > 0) {
            edge[curEdgeIndex].curFlow += flow;
            edge[curEdgeIndex ^ 1].curFlow -= flow;
            return flow;
        }
    }
    return 0;
}


long DinicAl(long source, long sink) {
    long flow = 0;
    long totalFlow = 0;
    while (true) {
        if (!BFS(source, sink))
            break;
        fill(searchPointer.begin(), searchPointer.end(), 0);
        while (long flow1 = DFS(source, sink, LONG_MAX)) {
            totalFlow += flow1;
        }
    }
    return totalFlow;
}

int main() {
    long n, m;
    std::cin>>n>>m;
    adjList.resize(n + 1);
    depth.resize(n + 1);
    searchPointer.resize(n + 1);

    for (long i = 0; i < m; ++i) {
        long from, to, capacity;
        std::cin>>from>>to>> capacity;
        AddEdge(from, to, capacity);
    }

    std::cout << DinicAl(1, n) << std::endl;

    return 0;
}

