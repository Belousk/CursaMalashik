#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <ctime>

class Graph {
private:
    size_t vertices; // Количество вершин
    std::vector<std::vector<int>> adjacencyMatrix; // Матрица смежности

public:
    // Конструктор
    Graph(size_t numVertices=0) : vertices(numVertices), 
    adjacencyMatrix(numVertices, std::vector<int>(numVertices, 0)) {}

    // Добавить ребро с весом
    void addEdge(size_t u, size_t v, int weight) {
        if (u >= vertices || v >= vertices) {
            std::cerr << "Invalid vertex index.\n";
            return;
        }
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight; // Граф неориентированный
    }

    // Обход в глубину (DFS)
    void dfs(size_t startVertex, std::ofstream& outFile) const {
        if (startVertex >= vertices) {
            std::cerr << "Invalid start vertex.\n";
            return;
        }

        std::vector<bool> visited(vertices, false);
        std::stack<size_t> stack;
        stack.push(startVertex);

        outFile << "DFS starting from vertex " << startVertex << ": ";

        while (!stack.empty()) {
            size_t current = stack.top();
            stack.pop();

            if (!visited[current]) {
                outFile << current << " ";
                visited[current] = true;

                // Добавляем всех соседей текущей вершины в стек
                for (size_t i = 0; i < vertices; ++i) {
                    if (adjacencyMatrix[current][i] != 0 && !visited[i]) {
                        stack.push(i);
                    }
                }
            }
        }
        outFile << "\n";
    }

    // Генерация случайного графа
    void generateRandomGraph(size_t edges, int minWeight = 1, int maxWeight = 10) {
        if (edges < vertices - 1) {
            std::cerr << "Not enough edges to ensure connectivity.\n";
            return;
        }

        // Гарантируем связность графа, соединяя все вершины хотя бы одним ребром
        for (size_t i = 0; i < vertices - 1; ++i) {
            int weight = minWeight + rand() % (maxWeight - minWeight + 1);
            addEdge(i, i + 1, weight);
        }

        size_t currentEdges = vertices - 1;

        // Добавляем оставшиеся ребра
        while (currentEdges < edges) {
            size_t u = rand() % vertices;
            size_t v = rand() % vertices;
            if (u != v && adjacencyMatrix[u][v] == 0) {
                int weight = minWeight + rand() % (maxWeight - minWeight + 1);
                addEdge(u, v, weight);
                ++currentEdges;
            }
        }
    }

    // Сохранить граф в файл
    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }

        outFile << vertices << "\n";
        for (const auto& row : adjacencyMatrix) {
            for (int weight : row) {
                outFile << weight << " ";
            }
            outFile << "\n";
        }
        outFile.close();
    }

    // Загрузить граф из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file for reading.\n";
            return;
        }

        inFile >> vertices;
        adjacencyMatrix.assign(vertices, std::vector<int>(vertices, 0));
        for (size_t i = 0; i < vertices; ++i) {
            for (size_t j = 0; j < vertices; ++j) {
                inFile >> adjacencyMatrix[i][j];
            }
        }
        inFile.close();
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    size_t numVertices = 100; // Количество вершин
    size_t numEdges = 1000; // Количество ребер

    Graph graph(numVertices);

    // Генерация графа
    graph.generateRandomGraph(numEdges);

    // Сохранение графа в файл
    graph.saveToFile("graph.txt");

    // Загрузка графа из файла
    Graph loadedGraph;
    loadedGraph.loadFromFile("graph.txt");

    // Выполнение DFS и вывод результата в файл
    std::ofstream outFile("dfs_result.txt");
    if (!outFile) {
        std::cerr << "Error opening DFS result file for writing.\n";
        return 1;
    }

    loadedGraph.dfs(0, outFile); // Стартуем с вершины 0
    outFile.close();

    std::cout << "Graph saved to 'graph.txt' and DFS results saved to 'dfs_result.txt'.\n";

    return 0;
}
