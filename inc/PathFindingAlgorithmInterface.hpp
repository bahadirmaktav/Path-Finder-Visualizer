#ifndef PATH_FINDING_ALGORITHM_INTERFACE_HPP_
#define PATH_FINDING_ALGORITHM_INTERFACE_HPP_

#include <unordered_set>

#include "Node.hpp"
#include "Index2D.hpp"

class PathFindingAlgorithmInterface {
public:
    PathFindingAlgorithmInterface() {}
    virtual ~PathFindingAlgorithmInterface() {}
    virtual Node *** GetNodeMatrix() = 0;
    virtual Node * GetCurrentNode() = 0;
    virtual std::unordered_set<Node *> & GetClosedSet() = 0;
    virtual std::unordered_set<Node *> & GetOpenedSet() = 0;
    virtual void CreateNodeMatrix(int rowNum, int coloumnNum) = 0;
    virtual void StartPathFindingSimulation(Index2D startInd, Index2D endInd) = 0;
    virtual void FindShortestPath(Index2D startInd, Index2D endInd) = 0;
    virtual void ResetNodeMatrix() = 0;
};

#endif // PATH_FINDING_ALGORITHM_INTERFACE_HPP_