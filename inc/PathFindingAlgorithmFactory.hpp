#ifndef PATH_FIDNING_ALGORITHM_FACTORY_HPP_
#define PATH_FIDNING_ALGORITHM_FACTORY_HPP_

#include "PathFindingAlgorithmInterface.hpp"
#include "BfsAlgorithm.hpp"

class PathFindingAlgorithmFactory {
public:
    PathFindingAlgorithmFactory() {}
    ~PathFindingAlgorithmFactory() {}
    PathFindingAlgorithmInterface * GetPathFindingAlgorithm(int selectedAlgorithmType) {
        PathFindingAlgorithmInterface * pathFinder;
        if(selectedAlgorithmType == 0) {            // BFS
            pathFinder = new BfsAlgorithm();
        } else if(selectedAlgorithmType == 1) {     // DFS

        } else if(selectedAlgorithmType == 2) {     // Dijkstra

        } else if(selectedAlgorithmType == 3) {     // A Star

        }
        return pathFinder;
    }
};

#endif // PATH_FIDNING_ALGORITHM_FACTORY_HPP_