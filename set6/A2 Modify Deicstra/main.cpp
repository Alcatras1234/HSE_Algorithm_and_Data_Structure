#include <iostream>
#include <vector>
#include <queue>

std::vector<int> DijkstraMULT(std::vector<std::vector<std::pair<int, int>>> &adjList, int start) {
    int n = adjList.size();
    std::vector<int> dist(n, INT_MAX); // Массив расстояний
    std::vector<bool> visited(n, false); // Массив для отслеживания посещенных вершин
    dist[start] = 0; // Расстояние до начальной вершины равно 0

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start)); // Добавляем начальную вершину в очередь с приоритетом

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Проходим по всем смежным вершинам
        for (auto &edge: adjList[u]) {
            int v = edge.first; // Индекс смежной вершины
            int weight_uv = edge.second; // Вес ребра (расстояние от u до v)

            // Если найден более короткий путь к вершине v через u, обновляем расстояние
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight_uv < dist[v]) {
                dist[v] = dist[u] + weight_uv;
                visited[v] = true;
                pq.push(std::make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

    int main() {
    int n, m;
    std::cin>>n>>m;
    std::vector<std::vector<std::pair<int, int>>> adjList(n);
    //ввод ребер
    for (int i = 0; i < m; ++i) {
        int start, end, weight;
        std::cin>>start>>end>>weight;
        adjList[start].push_back({end, weight});
    }

    int start;
    std::cin>>start;

    std::vector<int> shortest_paths = DijkstraMULT(adjList, start);

    for (int i = 0; i < shortest_paths.size(); ++i) {
        std::cout << "Vertex " << i << ": " << shortest_paths[i] << "\n";
    }


    return 0;
}
