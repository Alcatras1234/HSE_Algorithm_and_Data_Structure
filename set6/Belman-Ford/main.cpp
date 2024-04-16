
#include <iostream>
#include <vector>
#include <climits>

struct Edge {
    int from;
    int to;
    int weight;
};


void bellmanFord(const std::vector<Edge> &edges, int n) {
    std::vector<long> dist(n, LONG_MAX);

    dist[0] = 0;

    for (int i = 0; i < n - 1; ++i) { //n - кол-во вершин
        for (auto edge: edges) {
            if (dist[edge.from] != LONG_MAX  && (dist[edge.from] + edge.weight < dist[edge.to])) {
                dist[edge.to] = dist[edge.from] + edge.weight;
            }
        }
    }
    std::vector<int> minus_cycle(n , 0);
    for (int i = 0; i < n; ++i) {
        for (const auto& edge : edges) {
            if (minus_cycle[edge.from] == 1 || (dist[edge.from] + edge.weight < dist[edge.to])) {
                minus_cycle[edge.to] = 1;
                minus_cycle[edge.from] = 1;// Устанавливаем -inf для вершин в отрицательных циклах
            }
        }
    }


    for (int i = 1; i < n; ++i) {
         if (minus_cycle[i] == 1) {
            std::cout << "-inf" << std::endl; // Вершина находится в отрицательном цикле
        } else {
            std::cout << dist[i] << std::endl;
        }
    }
}



int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> edges[i].from >> edges[i].to >> edges[i].weight;
    }
    bellmanFord(edges, n);
    return 0;
}
