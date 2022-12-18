#ifndef PATH_FIDNING_ALGORITHM_FACTORY_HPP_
#define PATH_FIDNING_ALGORITHM_FACTORY_HPP_

#include "PathFindingAlgorithmInterface.hpp"
#include "BfsAlgorithm.hpp"
#include "DfsAlgorithm.hpp"
#include "AStarAlgorithm.hpp"
#include "DijkstraAlgorithm.hpp"

class PathFindingAlgorithmFactory {
public:
    enum Algorithm {
        TYPE__BFS = 0,
        TYPE__DFS,
        TPYE__DIJKSTRA,
        TYPE__A_STAR
    };
    PathFindingAlgorithmFactory() {}
    ~PathFindingAlgorithmFactory() {}
    static PathFindingAlgorithmInterface * GetPathFindingAlgorithm(int selectedAlgorithmType) {
        PathFindingAlgorithmInterface * pathFinder;
        if(selectedAlgorithmType == Algorithm::TYPE__BFS) {
            pathFinder = new BfsAlgorithm();
        } else if(selectedAlgorithmType == Algorithm::TYPE__DFS) {
            pathFinder = new DfsAlgorithm();
        } else if(selectedAlgorithmType == Algorithm::TPYE__DIJKSTRA) {
            pathFinder = new DijkstraAlgorithm();
        } else if(selectedAlgorithmType == Algorithm::TYPE__A_STAR) {
            pathFinder = new AStarAlgorithm();
        }
        return pathFinder;
    }
};

#endif // PATH_FIDNING_ALGORITHM_FACTORY_HPP_