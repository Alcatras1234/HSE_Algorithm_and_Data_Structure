#include <iostream>
#include <vector>
class Graph {
private:
    int numVertices;
    int numEdges;
    std::vector<std::vector<int>> incidenceMatrix;

public:
    Graph(int vertices, int edges) : numVertices(vertices), numEdges(edges) {
        // Инициализация матрицы инцидентности
        incidenceMatrix.resize(vertices, std::vector<int>(edges, 0));
    }

    void add(int start, int end, int indexEdge) {
        incidenceMatrix[start][indexEdge] = -1;
        incidenceMatrix[end][indexEdge] = 1;
    }
    void check() {

    }



};




int main() {
    Graph a (6, 10);

    a.add(0, 1, 0);
    a.add(1, 2, 1);
    a.add(2, 3, 2);
    a.add(3, 4, 3);
    a.add(4, 5, 4);
    a.add(5, 3, 5);
    a.add(3, 1, 6);
    a.add(1, 5, 7);
    a.add(5, 2, 8);
    a.add(2, 0, 9);



    return 0;
}
