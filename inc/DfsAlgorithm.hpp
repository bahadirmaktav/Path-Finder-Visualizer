#ifndef DFS_ALGORITHM_HPP_
#define DFS_ALGORITHM_HPP_

#include <iostream>
#include <deque>
#include <thread>

#include "PathFindingAlgorithmInterface.hpp"

class DfsAlgorithm : public PathFindingAlgorithmInterface {
public:
    DfsAlgorithm() 
    : matrix_(nullptr)
    , currentNode_(nullptr)
    , rowNum_(0)
    , columnNum_(0)
    {}
    ~DfsAlgorithm() {}
    Node *** GetNodeMatrix() {
        return matrix_;
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
            }
        }
    }
    void StartPathFindingSimulation(Index2D startInd, Index2D endInd) override {
        closedSet_.clear();
        openedSet_.clear();
        currentNode_ = nullptr;
        std::thread th(&FindShortestPath, this, startInd, endInd);
        th.detach();
    }
    void FindShortestPath(Index2D startInd, Index2D endInd) override {
        std::deque<Node *> openedList;
        Node * endNode = matrix_[endInd.i][endInd.j];
        Node * startNode = matrix_[startInd.i][startInd.j];
        currentNode_ = startNode;
        while(currentNode_ != endNode) {
            closedSet_.insert(currentNode_);
            for(int i = 0; i < 4; i++) {
                if(currentNode_->adjacents[i] != nullptr && currentNode_->adjacents[i]->traversable && 
                    (openedSet_.find(currentNode_->adjacents[i]) == openedSet_.end()) && (closedSet_.find(currentNode_->adjacents[i]) == closedSet_.end())) {
                    openedSet_.insert(currentNode_->adjacents[i]);
                    openedList.push_back(currentNode_->adjacents[i]);
                    currentNode_->adjacents[i]->parent = currentNode_;
                }
            }
            if(openedList.empty()) {
                std::cout << "There is no shortest way start to end cell !" << std::endl;
                return;
            }
            Node * backNode = openedList.back();
            openedSet_.erase(backNode);
            openedList.pop_back();
            currentNode_ = backNode;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        startNode->parent = nullptr;
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
private:
    Node *** matrix_;
    std::unordered_set<Node *> closedSet_;
    std::unordered_set<Node *> openedSet_;
    Node * currentNode_;
    int rowNum_;
    int columnNum_;
};

#endif // BFS_ALGORITHM_HPP_