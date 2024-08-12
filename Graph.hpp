//206396863
//natalisadikov2318@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stdexcept>
#include <iostream>

namespace ariel {
    class Graph {
    private:
        std::vector<std::vector<int>> adjMatrix;
        size_t numVertices;
        int numEdges;
        bool isDirected;

    public:
        Graph() : numVertices(0), numEdges(0), isDirected(false) {}
        explicit Graph(size_t vertices);


        void loadGraph(const std::vector<std::vector<int>>& matrix);

        std::string printGraph();

        const std::vector<std::vector<int>>& getAdjMatrix() const;

        size_t getNumVertices() const;

        int getNumEdges() const;

        bool isDirectedGraph() const;
        Graph operator+() const;
        Graph operator+(const Graph& other) const;
        Graph& operator+=(const Graph& other);
        Graph& operator++();
        Graph operator++(int);
        Graph operator-() const;
        Graph operator-(const Graph& other) const;
        Graph& operator-=(const Graph& other);
        Graph& operator--();
        Graph operator--(int);
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;
        Graph& operator*=(int scalar);
        Graph operator*(int scalar) const;
        Graph operator*(const Graph& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };
}

#endif 