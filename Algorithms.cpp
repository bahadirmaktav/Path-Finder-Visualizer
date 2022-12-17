#include <iostream>
#include <deque>
#include <unordered_set>
#include "Index2D.hpp"

struct Node {
    Index2D indPos;
    int nodeId;
    Node * adjacents[4];   // [0] = UP, [1] = RIGHT, [2] = DOWN, [3] = LEFT
    Node * parent;
    bool traversable;
    Node() 
    : nodeId(-1)
    , adjacents{nullptr, nullptr, nullptr, nullptr}
    , parent(nullptr)
    , traversable(true) 
    {}
};

Node *** CreateNodeMatrix(int rowNum, int coloumnNum) {
    Node *** matrix = new Node**[rowNum];
    for(int r = 0; r < rowNum; r++) {
        matrix[r] = new Node*[coloumnNum];
        for(int c = 0; c < coloumnNum; c++) {
            matrix[r][c] = new Node;
        }
    }
    for(int r = 0; r < rowNum; r++) {
        for(int c = 0; c < coloumnNum; c++) {
            if(r - 1 >= 0) {            // Set UP adjacent
                matrix[r][c]->adjacents[0] = matrix[r - 1][c];
            }
            if(c + 1 < coloumnNum) {    // Set RIGHT adjacent
                matrix[r][c]->adjacents[1] = matrix[r][c + 1];
            }
            if(r + 1 < rowNum) {        // Set Down adjacent
                matrix[r][c]->adjacents[2] = matrix[r + 1][c];
            }
            if(c - 1 >= 0) {            // Set LEFT adjacent
                matrix[r][c]->adjacents[3] = matrix[r][c - 1];
            }
            matrix[r][c]->nodeId = r * coloumnNum + c;
        }
    }
    return matrix;
}

void BfsPathFinder(Index2D startInd, Index2D endInd, Node *** matrix) {
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
        Node * frontNode = openedList.front();
        openedList.pop_front();
        currentNode = frontNode;
    }
    startNode->parent = nullptr;
}

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

int main() {
    int ROW_NUM = 5;
    int COLOUMN_NUM = 6;
    Node *** matrix = CreateNodeMatrix(ROW_NUM, COLOUMN_NUM);
    matrix[3][5]->traversable = false; matrix[3][4]->traversable = false;
    matrix[3][3]->traversable = false; // matrix[4][3]->traversable = false;
    Index2D startInd(0, 0); Index2D endInd(4, 5);
    // BfsPathFinder(startInd, endInd, matrix);
    DfsPathFinder(startInd, endInd, matrix);
    Node * nodeBuff = matrix[endInd.i][endInd.j];
    while(nodeBuff != nullptr) {
        std::cout << nodeBuff->nodeId << ", ";
        nodeBuff = nodeBuff->parent;
    }
    std::cout << "\n";
}