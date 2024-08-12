//206396863
//natalisadikov2318@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#pragma once

#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <algorithm>
#include <climits>
#include <functional>

namespace ariel {
    class Algorithms {
    public:
        static std::string isConnected(const Graph& g);
        static std::string shortestPath(const Graph& g, int start_i, int end_i);
        static std::string isContainsCycle(const Graph& g);
        static std::string isBipartite(const Graph& g);
        static std::string negativeCycle(const Graph& g);
    };
}

#endif