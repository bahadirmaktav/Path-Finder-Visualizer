#include <iostream>
#include <deque>
#include <unordered_set>
#include "Index2D.hpp"
#include "PathFindingAlgorithmFactory.hpp"


/* DFS Algorithm
void DfsPathFinder(Index2D startInd, Index2D endInd, Node *** matrix) {
    std::unordered_set<Node *> closedSet;
    std::unordered_set<Node *> openedSet;
    std::deque<Node *> openedList;
    Node * endNode = matrix[endInd.i][endInd.j];
    Node * startNode = matrix[startInd.i][startInd.j];
    Node * currentNode = startNode;
    while(currentNode != endNode) {
        closedSet.insert(currentNode);
        for(int i = 0; i < 4; i++) {
            if(currentNode->adjacents[i] != nullptr && currentNode->adjacents[i]->traversable && 
                (openedSet.find(currentNode->adjacents[i]) == openedSet.end()) && (closedSet.find(currentNode->adjacents[i]) == closedSet.end())) {
                openedSet.insert(currentNode->adjacents[i]);
                openedList.push_back(currentNode->adjacents[i]);
                currentNode->adjacents[i]->parent = currentNode;
            }
        }
        if(openedList.empty()) {
            std::cout << "There is no shortest way start to end cell !" << std::endl;
            return;
        }
        Node * frontNode = openedList.back();
        openedList.pop_back();
        currentNode = frontNode;
    }
    startNode->parent = nullptr;
}
*/

int main() {
    int ROW_NUM = 5;
    int COLOUMN_NUM = 6;
    PathFindingAlgorithmFactory algFac;
    PathFindingAlgorithmInterface * pfAlg = algFac.GetPathFindingAlgorithm(0);
    pfAlg->CreateNodeMatrix(ROW_NUM, COLOUMN_NUM);
    Index2D startInd(0, 0); Index2D endInd(4, 5);
    Node *** matrix = pfAlg->GetNodeMatrix();
    matrix[3][5]->traversable = false; matrix[3][4]->traversable = false;
    matrix[3][3]->traversable = false; // matrix[4][3]->traversable = false;
    // BfsPathFinder(startInd, endInd, matrix);
    pfAlg->FindShortestPath(startInd, endInd);
    Node * nodeBuff = matrix[endInd.i][endInd.j];
    while(nodeBuff != nullptr) {
        std::cout << nodeBuff->nodeId << ", ";
        nodeBuff = nodeBuff->parent;
    }
    std::cout << "\n";
    delete pfAlg;
    return 0;
}