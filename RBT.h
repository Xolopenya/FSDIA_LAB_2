// RedBlackTree.h
#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <fstream>
#include <string>
#include "List.h"

enum Color { RED, BLACK };

class Node {
public:
    std::string series;
    std::string number;
    int color;
    Node* left;
    Node* right;
    Node* parent;

    CircularLinkedList lineNumbers; // Используем ваш класс для хранения номеров строк

    Node(const std::string& series, const std::string& number)
        : series(series), number(number), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};



class RedBlackTree {
private:
    Node* root;
    Node* TNULL;

    void initializeNullNode(Node* node, Node* parent);
    void inOrderTraversal(Node* node, std::ofstream& outFile);
    void showTreeHelper(Node* root, int level);
    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void fixInsert(Node* k);
    void fixDelete(Node* x);
    void freeMemory(Node* node);
    void transplant(Node* u, Node* v);
    Node* deleteNode(Node* node, const std::string& series, const std::string& number);
    Node* findMin(Node* node);
    Node* search(Node* node, const std::string& series, const std::string& number);

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(const std::string& series, const std::string& number, int lineNumber);
    void remove(const std::string& series, const std::string& number);


    void saveToFile(const std::string& filename);
    void showTree();
    void findAndDisplay(const std::string& series, const std::string& number);
};

#endif // RED_BLACK_TREE_H
