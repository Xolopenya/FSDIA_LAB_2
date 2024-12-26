#pragma once
#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

#include <iostream>

class NodeList {
public:
    int data;
    NodeList* next;
    NodeList(int value) : data(value), next(nullptr) {}
};

class CircularLinkedList {
private:
    NodeList* last;
public:
    NodeList* head;
    CircularLinkedList();
    ~CircularLinkedList();

    void addElement(int value);
    void removeElement(int value);
    void printList() const;
    NodeList* findElement(int value);
    bool contains(int value) const;
    void freeMemory();
};

#endif // CIRCULAR_LINKED_LIST_H
