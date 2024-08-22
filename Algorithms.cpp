//206396863
//natalisadikov2318@gmail.com

#include "Algorithms.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <sstream>
#include <vector>
#include <utility>
#include <functional>

namespace ariel {

    std::string Algorithms::isConnected(const Graph& g) {
        size_t numVertices = g.getNumVertices();
        if (numVertices == 0)
            return "0";

        std::vector<int> dist(numVertices, INT_MAX);
        std::vector<int> prev(numVertices, -1);

        // BFS 
        std::queue<size_t> q;
        dist[0] = 0;
        q.push(0);

        while (!q.empty()) {
            size_t v = q.front();
            q.pop();

            for (size_t i = 0; i < numVertices; ++i) {
                if (g.getAdjMatrix()[v][i] > 0 && dist[i] == INT_MAX) {
                    dist[i] = dist[v] + 1;
                    prev[i] = v;
                    q.push(i);
                }
            }
        }

        // Check if all vertices connected
        for (size_t i = 0; i < numVertices; ++i) {
            if (dist[i] == INT_MAX)
                return "false";
        }
        return "true";
    }

    std::string Algorithms::shortestPath(const Graph& g, int start_i, int end_i) {
        size_t start = static_cast<size_t>(start_i);
        size_t end = static_cast<size_t>(end_i);
        size_t numVertices = g.getNumVertices();

        if (start >= numVertices || end >= numVertices) {
            throw std::out_of_range("Invalid start or end vertex");
        }

        std::vector<int> dist(numVertices, std::numeric_limits<int>::max());
        std::vector<int> prev(numVertices, -1);
        std::vector<bool> visited(numVertices, false);

        // Priority queue to store vertices that are being preprocessed
        std::priority_queue<std::pair<int, size_t>, std::vector<std::pair<int, size_t>>, std::greater<std::pair<int, size_t>>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            size_t u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            if (u == end) break;  // Found the shortest path to the end vertex

            for (size_t v = 0; v < numVertices; ++v) {
                int weight = g.getAdjMatrix()[u][v];
                if (weight > 0 && !visited[v]) {
                    int newDist = dist[u] + weight;
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        prev[v] = static_cast<int>(u);
                        pq.push({newDist, v});
                    }
                }
            }
        }

        if (dist[end] == std::numeric_limits<int>::max()) {
            return "-1";  // No path exists
        }

        // Reconstruct the path
        std::vector<int> path;
        for (int at = static_cast<int>(end); at != -1; at = prev[static_cast<size_t>(at)]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        // Format the path as a string
        std::ostringstream oss;
        for (size_t i = 0; i < path.size(); ++i) {
            oss << path[i];
            if (i < path.size() - 1) {
                oss << "->";
            }
        }
        return oss.str();
    }

    std::string Algorithms::isContainsCycle(const Graph& g) {
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        size_t n = adjMatrix.size();
        std::vector<bool> visited(n, false);
        std::vector<bool> inStack(n, false);

        //  DFS 
        std::function<bool(size_t)> dfs = [&](size_t u) -> bool {
            visited[u] = true;
            inStack[u] = true;

            for (size_t v = 0; v < n; v++) {
                if (adjMatrix[u][v] != 0) {
                    if (!visited[v]) {
                        if (dfs(v)) {
                            return true;
                        }
                    } else if (inStack[v]) {
                        return true; 
                    }
                }
            }
            inStack[u] = false; 
            return false;
        };

        for (size_t u = 0; u < n; u++) {
            if (!visited[u]) {
                if (dfs(u)) {
                    return "true";
                }
            }
        }

        return "false";
    }

    std::string Algorithms::isBipartite(const Graph& g) {
    size_t numVertices = g.getNumVertices();
    if (numVertices == 0) {
        return "The graph is bipartite: A={}, B={}";
    }
    if (numVertices == 1) {
        return "The graph is bipartite: A={0}, B={}";
    }

    std::vector<int> color(numVertices, -1);
    std::vector<int> setA, setB;

    auto bfsBipartite = [&](size_t start) -> bool {
        std::queue<size_t> queue;
        queue.push(start);
        color[start] = 0;
        setA.push_back(start);

        while (!queue.empty()) {
            size_t curr = queue.front();
            queue.pop();

            for (size_t neighbor = 0; neighbor < numVertices; neighbor++) {
                if (g.getAdjMatrix()[curr][neighbor] != 0) {  
                    if (color[neighbor] == -1) {
                        color[neighbor] = 1 - color[curr];
                        queue.push(neighbor);
                        (color[neighbor] == 0 ? setA : setB).push_back(neighbor);
                    } else if (color[neighbor] == color[curr]) {
                        return false; 
                    }
                }
            }
        }
        return true;
    };

    for (size_t node = 0; node < numVertices; node++) {
        if (color[node] == -1) {
            if (!bfsBipartite(node)) {
                return "0"; 
            }
        }
    }

    std::sort(setA.begin(), setA.end());
    std::sort(setB.begin(), setB.end());

    std::ostringstream oss;
    oss << "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        oss << setA[i] << (i != setA.size() - 1 ? ", " : "");
    }
    oss << "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        oss << setB[i] << (i != setB.size() - 1 ? ", " : "");
    }
    oss << "}";
    return oss.str();
}

    std::string Algorithms::negativeCycle(const Graph& g) {
        size_t numVertices = g.getNumVertices();
        const std::vector<std::vector<int>>& adjMatrix = g.getAdjMatrix();
        std::vector<int> dist(numVertices, INT_MAX);

        //  Bellman Ford
        dist[0] = 0;

        for (size_t k = 0; k < numVertices - 1; ++k) {
            for (size_t u = 0; u < numVertices; ++u) {
                for (size_t v = 0; v < numVertices; ++v) {
                    if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX &&
                        dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                    }
                }
            }
        }

        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX &&
                    dist[u] + adjMatrix[u][v] < dist[v]) {
                    return "true"; 
                }
            }
        }

        return "false"; 
    }
}
