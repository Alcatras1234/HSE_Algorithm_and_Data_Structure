#include <iostream>
#include <vector>
#include <climits>

void floydWarshall(std::vector<std::vector<long long>> vector1, int n) {
    std::vector<std::vector<long long>> dist(n, std::vector<long long>(n, LLONG_MAX));
    dist[0][0] = 0;
    //Инициализация расстояний
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                dist[i][j] = 0;
            } else {
                dist[i][j] = vector1[i][j];
            }
        }
    }

    for (int k = 0; k <= n - 1; ++k) {
        for (int i = 0; i <= n - 1; ++i) {
            for (int j = 0; j <= n - 1; ++j) {
                if (dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];

                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j)
                continue;
            else if (dist[i][j] == LLONG_MAX) {
                std::cout << i << " " << j << " -1" << std::endl;
            } else {
                std::cout << i << " " << j << " " << dist[i][j] << std::endl;
            }
        }
    }
}


int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<long long>> graph(n, std::vector<long long>(n, LLONG_MAX));
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;
        graph[u][v] = w;
    }
    floydWarshall(graph, n);
    return 0;
}

