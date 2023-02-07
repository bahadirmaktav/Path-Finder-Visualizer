#ifndef A_STAR_ALGORITHM_HPP_
#define A_STAR_ALGORITHM_HPP_

#include <math.h>

#include <iostream>
#include <deque>
#include <thread>

#include "PathFindingAlgorithmInterface.hpp"

class AStarAlgorithm : public PathFindingAlgorithmInterface {
public:
    AStarAlgorithm() 
    : matrix_(nullptr)
    , currentNode_(nullptr)
    , rowNum_(0)
    , columnNum_(0)
    , isSimulationStarted_(false)
    , algorithmSpeed_(1)
    {}
    ~AStarAlgorithm() {}
    Node *** GetNodeMatrix() {
        return matrix_;
    }
    void SetNodeMatrix(Node *** matrix) {
        matrix_ = matrix;
    }
    Node * GetCurrentNode() {
        return currentNode_;
    }
    std::unordered_set<Node *> & GetClosedSet() override {
        return closedSet_;
    }
    std::unordered_set<Node *> & GetOpenedSet() override {
        return openedSet_;
    }
    void CreateNodeMatrix(int rowNum, int columnNum) override {
        if(matrix_ != nullptr) {
            ClearNodeMatrix(rowNum_, columnNum_);
        }
        rowNum_ = rowNum; 
        columnNum_ = columnNum;
        matrix_ = new Node**[rowNum];
        for(int r = 0; r < rowNum; r++) {
            matrix_[r] = new Node*[columnNum];
            for(int c = 0; c < columnNum; c++) {
                matrix_[r][c] = new Node;
            }
        }
        for(int r = 0; r < rowNum; r++) {
            for(int c = 0; c < columnNum; c++) {
                if(r - 1 >= 0) {            // Set UP adjacent
                    matrix_[r][c]->adjacents[0] = matrix_[r - 1][c];
                }
                if(c + 1 < columnNum) {    // Set RIGHT adjacent
                    matrix_[r][c]->adjacents[1] = matrix_[r][c + 1];
                }
                if(r + 1 < rowNum) {        // Set Down adjacent
                    matrix_[r][c]->adjacents[2] = matrix_[r + 1][c];
                }
                if(c - 1 >= 0) {            // Set LEFT adjacent
                    matrix_[r][c]->adjacents[3] = matrix_[r][c - 1];
                }
                matrix_[r][c]->indId = r * columnNum + c;
                matrix_[r][c]->cost = 0;
            }
        }
    }
    void StartPathFindingSimulation(Index2D startInd, Index2D endInd) override {
        closedSet_.clear();
        openedSet_.clear();
        currentNode_ = nullptr;
        isSimulationStarted_ = true;
        std::thread th(&AStarAlgorithm::FindShortestPath, this, startInd, endInd);
        th.detach();
    }
    void StopPathFindingSimulation() {
        isSimulationStarted_ = false;
    }
    bool IsSimulationStarted() {
        return isSimulationStarted_;
    }
    void FindShortestPath(Index2D startInd, Index2D endInd) override {
        openedSet_.insert(matrix_[startInd.i][startInd.j]);
        while(isSimulationStarted_) {
            currentNode_ = GetLowestCostNode();
            openedSet_.erase(currentNode_);
            closedSet_.insert(currentNode_);
            if(currentNode_ == matrix_[endInd.i][endInd.j]) {
                break;
            }
            int current_PathLong = 0;
            Node * current_PathNode = currentNode_->parent;
            while(current_PathNode != nullptr) {
                current_PathLong += 10;
                current_PathNode = current_PathNode->parent;
            }
            for(Node * neighbour : currentNode_->adjacents) {
                if(neighbour == nullptr || !neighbour->traversable || closedSet_.find(neighbour) != closedSet_.end()) {
                    continue;
                }
                int oldPathLong = 0;
                Node * oldPathNode = neighbour->parent;
                while(oldPathNode != nullptr) {
                    oldPathLong += 10;
                    oldPathNode = oldPathNode->parent;
                }
                if(current_PathLong < oldPathLong || openedSet_.find(neighbour) == openedSet_.end()) {
                    int gCostBuff = current_PathLong + 10;
                    int hCostBuff = sqrt(pow(abs(endInd.i - neighbour->indPos.i), 2) + pow(abs(endInd.j - neighbour->indPos.j), 2)) * 10;
                    neighbour->cost = gCostBuff + hCostBuff;
                    neighbour->parent = currentNode_;
                    if(openedSet_.find(neighbour) == openedSet_.end()) {
                        openedSet_.insert(neighbour);
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(int(100 / algorithmSpeed_)));
        }
    }
    void ResetNodeMatrix() {
        closedSet_.clear();
        openedSet_.clear();
        currentNode_ = nullptr;
        for(int i = 0; i < rowNum_; i++) {
            for(int j = 0; j < columnNum_; j++) {
                matrix_[i][j]->parent = nullptr;
                matrix_[i][j]->traversable = true;
                matrix_[i][j]->cost = 0;
            }
        }
    }
    void SetAlgorithmSpeed(float algorithmSpeed) {
        algorithmSpeed_ = algorithmSpeed;
    }
private:
    void ClearNodeMatrix(int rowNum, int columnNum) {
        for(int i = 0; i < rowNum; i++) {
            for(int j = 0; j < columnNum; j++) {
                delete matrix_[i][j];
            }
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
    }
    Node * GetLowestCostNode() {
        Node * lowestCostNode = *openedSet_.begin();
        for(auto itr = openedSet_.begin(); itr != openedSet_.end(); ++itr) {
            Node * n = *itr;
            if(n->cost < lowestCostNode->cost)
                lowestCostNode = n;
        }
        return lowestCostNode;
    }
private:
    Node *** matrix_;
    std::unordered_set<Node *> closedSet_;
    std::unordered_set<Node *> openedSet_;
    Node * currentNode_;
    int rowNum_;
    int columnNum_;
    bool isSimulationStarted_;
    float algorithmSpeed_;
};

#endif // A_STAR_ALGORITHM_HPP_