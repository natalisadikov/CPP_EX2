//206396863
//natalisadikov2318@gmail.com
#include "Graph.hpp"
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace ariel {
    Graph::Graph(size_t vertices) : numVertices(vertices), numEdges(0), isDirected(false) {
    adjMatrix = std::vector<std::vector<int>>(vertices, std::vector<int>(vertices, 0));
    }

    void Graph::loadGraph(const std::vector<std::vector<int>>& matrix) {
        if (matrix.empty() || matrix.size() != matrix[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        adjMatrix = matrix;
        numVertices = matrix.size();
        numEdges = 0;
        isDirected = false;

        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                if (adjMatrix[i][j] != 0) {
                    numEdges++;
                    if (adjMatrix[i][j] != adjMatrix[j][i]) {
                        isDirected = true;
                    }
                }
            }
        }

        if (!isDirected) {
            numEdges /= 2;
        }
    }

    std::string Graph::printGraph() {
    std::ostringstream oss;
    for (size_t row = 0; row < adjMatrix.size(); ++row) {
        oss << "[";
        for (size_t col = 0; col < adjMatrix[row].size(); ++col) {
            oss << adjMatrix[row][col];
            if (col < adjMatrix[row].size() - 1) {
                oss << ", ";
            }
        }
        oss << "]";
        if (row < adjMatrix.size() - 1) {
            oss << "\n";
        }
    }
        return oss.str();
    }

    const std::vector<std::vector<int>>& Graph::getAdjMatrix() const {
        return adjMatrix;
    }

    size_t Graph::getNumVertices() const {
        return numVertices;
    }

    int Graph::getNumEdges() const {
        return numEdges;
    }

    bool Graph::isDirectedGraph() const {
        return isDirected;
    }

    Graph Graph::operator+(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices");
        }
        Graph result(numVertices);
            for (size_t i = 0; i < numVertices; ++i) {
                for (size_t j = 0; j < numVertices; ++j) {
                    result.adjMatrix[i][j] = adjMatrix[i][j] + other.adjMatrix[i][j];
                }
            }
            return result;
        }

    Graph& Graph::operator+=(const Graph& other) {
        *this = *this + other;
        return *this;
    }

    Graph Graph::operator+() const {
        return *this;
    }

    Graph Graph::operator-(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices");
        }
        Graph result(numVertices);
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                result.adjMatrix[i][j] = adjMatrix[i][j] - other.adjMatrix[i][j];
            }
        }
        return result;
    }

    Graph& Graph::operator-=(const Graph& other) {
        *this = *this - other;
        return *this;
    }

    Graph Graph::operator-() const {
        Graph result(numVertices);
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                result.adjMatrix[i][j] = -adjMatrix[i][j];
            }
        }
        return result;
    }

    bool Graph::operator>(const Graph& other) const {
        if (numVertices != other.numVertices) {
            return numVertices > other.numVertices;
        }
        return numEdges > other.numEdges;
    }

    bool Graph::operator>=(const Graph& other) const {
        return (*this > other) || (*this == other);
    }

    bool Graph::operator<(const Graph& other) const {
        return !(*this >= other);
    }

    bool Graph::operator<=(const Graph& other) const {
        return !(*this > other);
    }

    bool Graph::operator==(const Graph& other) const {
        return adjMatrix == other.adjMatrix;
    }

    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }

    Graph& Graph::operator++() {
        for (auto& row : adjMatrix) {
            for (auto& element : row) {
                ++element;
            }
        }
        return *this;
    }

    Graph Graph::operator++(int) {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph& Graph::operator--() {
        for (auto& row : adjMatrix) {
            for (auto& element : row) {
                --element;
            }
        }
        return *this;
    }

    Graph Graph::operator--(int) {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    Graph Graph::operator*(int scalar) const {
        Graph result = *this;
        for (auto& row : result.adjMatrix) {
            for (auto& element : row) {
                element *= scalar;
            }
        }
        return result;
    }

    Graph Graph::operator*(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Graphs must have the same number of vertices for multiplication");
        }
        Graph result(numVertices);
        for (size_t i = 0; i < numVertices; ++i) {
            for (size_t j = 0; j < numVertices; ++j) {
                result.adjMatrix[i][j] = 0;
                for (size_t k = 0; k < numVertices; ++k) {
                    result.adjMatrix[i][j] += adjMatrix[i][k] * other.adjMatrix[k][j];
                }
            }
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        for (const auto& row : graph.adjMatrix) {
            for (int element : row) {
                os << element << " ";
            }
            os << std::endl;
        }
        return os;
    }


}