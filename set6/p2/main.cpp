#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int start, end, weight;
};

bool CompareEdge(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int find(int x, vector<int>& parent) {
    if (x == parent[x]) {
        return x;
    } else {
        return parent[x] = find(parent[x], parent);
    }
}

void unionSet(int x, int y, vector<int>& parent, vector<int>& rank) {
    x = find(x, parent);
    y = find(y, parent);

    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else {
        parent[y] = x;
        if (rank[x] == rank[y]){
            ++rank[y];
        }
    }
}

void isConnected(int start, int to){}

vector<Edge> kruskala(vector<Edge>& edges, int N) {
    sort(edges.begin(), edges.end(), CompareEdge);
    vector<int> parent(N + 1);
    vector<int> rank(N + 1, 0);
    vector<Edge> mst;
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
    }
    for (auto& edge : edges) {
        if (find(edge.start, parent) != find(edge.end, parent)) {
            unionSet(edge.start, edge.end, parent, rank);
            mst.push_back(edge);
        }
    }
    return mst;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<Edge> edges(M);

    for (int i = 0; i < M; ++i) {
        cin >> edges[i].start >> edges[i].end >> edges[i].weight;
    }

    vector<Edge> mst = kruskala(edges, N);

    int S1 = 0;
    for (auto edge : mst) {
        S1 += edge.weight;
    }

    int S2 = INT_MAX;
    for (int i = 0; i < mst.size(); ++i) {
        vector<int> parent(N + 1);
        vector<int> rank(N + 1, 0);
        for (int j = 1; j <= N; ++j)
            parent[j] = j;

        int currentWeight = 0, edgesUsed = 0;
        for (auto& edge : edges) {
            if (edge.weight == mst[i].weight && edge.start == mst[i].start && edge.end == mst[i].end) {
                continue;
            }
            if (find(edge.start, parent) != find(edge.end, parent)) {
                unionSet(edge.start, edge.end, parent, rank);
                currentWeight += edge.weight;
                edgesUsed++;
            }
        }

        if (edgesUsed == N - 1) {
            S2 = min(S2, currentWeight);
        }
    }

    cout << S1 << " " << S2 << endl;

    return 0;
}
