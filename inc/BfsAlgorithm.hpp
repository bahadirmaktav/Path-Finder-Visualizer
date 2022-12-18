#ifndef BFS_ALGORITHM_HPP_
#define BFS_ALGORITHM_HPP_

#include "PathFindingAlgorithmInterface.hpp"

class BfsAlgorithm : public PathFindingAlgorithmInterface {
public:
    BfsAlgorithm() 
    : matrix_(nullptr)
    , currentNode_(nullptr)
    , rowNum_(0)
    , coloumnNum_(0)
    {}
    ~BfsAlgorithm() {}
    Node *** GetNodeMatrix() {
        return matrix_;
    }
    std::unordered_set<Node *> & GetClosedSet() override {
        return closedSet_;
    }
    std::unordered_set<Node *> & GetOpenedSet() override {
        return openedSet_;
    }
    void CreateNodeMatrix(int rowNum, int coloumnNum) override {
        if(matrix_ != nullptr) {
            ClearMatrix(rowNum_, coloumnNum_);
        }
        rowNum_ = rowNum; 
        coloumnNum_ = coloumnNum;
        matrix_ = new Node**[rowNum];
        for(int r = 0; r < rowNum; r++) {
            matrix_[r] = new Node*[coloumnNum];
            for(int c = 0; c < coloumnNum; c++) {
                matrix_[r][c] = new Node;
            }
        }
        for(int r = 0; r < rowNum; r++) {
            for(int c = 0; c < coloumnNum; c++) {
                if(r - 1 >= 0) {            // Set UP adjacent
                    matrix_[r][c]->adjacents[0] = matrix_[r - 1][c];
                }
                if(c + 1 < coloumnNum) {    // Set RIGHT adjacent
                    matrix_[r][c]->adjacents[1] = matrix_[r][c + 1];
                }
                if(r + 1 < rowNum) {        // Set Down adjacent
                    matrix_[r][c]->adjacents[2] = matrix_[r + 1][c];
                }
                if(c - 1 >= 0) {            // Set LEFT adjacent
                    matrix_[r][c]->adjacents[3] = matrix_[r][c - 1];
                }
                matrix_[r][c]->nodeId = r * coloumnNum + c;
            }
        }
    }
    void StartPathFindingSimulation(Index2D startInd, Index2D endInd) override {
        closedSet_.clear();
        openedSet_.clear();
        currentNode_ = nullptr;
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
            Node * frontNode = openedList.front();
            openedList.pop_front();
            currentNode_ = frontNode;
        }
        startNode->parent = nullptr;
    }
private:
    void ClearMatrix(int rowNum, int coloumnNum) {
        for(int i = 0; i < rowNum; i++) {
            for(int j = 0; j < coloumnNum; j++) {
                delete matrix_[i][j];
            }
            delete[] *matrix_[i];
        }
        delete[] **matrix_;
        matrix_ = nullptr;
    }
private:
    Node *** matrix_;
    std::unordered_set<Node *> closedSet_;
    std::unordered_set<Node *> openedSet_;
    Node * currentNode_;
    int rowNum_;
    int coloumnNum_;
};

#endif // BFS_ALGORITHM_HPP_