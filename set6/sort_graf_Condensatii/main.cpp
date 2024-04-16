
#include <iostream>
#include <vector>
#include <stack>



void DFS(int vertex, std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::stack<int>& readyStack) { //вершина
    visited[vertex] = true; // говорим, что вершина была посещена
    for(int neighbours : graph[vertex]) { // берем эл из вектора стоящем на определенном индексе vertex
        if (!visited[neighbours])
            DFS(neighbours, graph, visited, readyStack);
    }
    readyStack.push(vertex);
}

void stDFS(int vertex, std::vector<std::vector<int>>& transport_graph, std::vector<bool>& visited, int& countSCC, std::vector<int>& com) {
    visited[vertex] = true;
    com[vertex] = countSCC;
    for (int neighbours : transport_graph[vertex]) {
        if (!visited[neighbours])
            stDFS(neighbours, transport_graph, visited, countSCC , com);
    }

}

int main() {
    int n, m = 0; // n - кол-во вершин, m - кол-во рёбер
    std::cin>>n>>m;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<std::vector<int>> trasport_graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int from, to;
        std:: cin >> from >> to;
        // Добавляем ребро в граф
        graph[from].push_back(to);
        trasport_graph[to].push_back(from);
    }
    std::vector<bool> visited(n+1, false);
    std::stack<int> readyStack;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i])
            DFS(i, graph, visited, readyStack);//обход в глубину
    }
    fill(visited.begin(), visited.end(), false); // опустошаем список с посещенными вершинами
    int count_componentSCC = 1;
    std::vector<int> components (n + 1, 0);
    while(!readyStack.empty()) {
        int cur = readyStack.top();
        readyStack.pop();
        if (!visited[cur]) {
            stDFS(cur, trasport_graph, visited, count_componentSCC, components);
            count_componentSCC++;
        }
    }

    std::cout<<count_componentSCC - 1<<std::endl;
    for (int i = 1; i <= n; ++i) {
        std::cout<<components[i]<<" ";
    }
    return 0;
}
