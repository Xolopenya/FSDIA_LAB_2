#include "List.h"

CircularLinkedList::CircularLinkedList() : head(nullptr), last(nullptr) {}

CircularLinkedList::~CircularLinkedList() {
    freeMemory();
}

void CircularLinkedList::freeMemory() {
    if (!head) return;
    NodeList* temp = head;
    do {
        NodeList* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    } while (temp != head);
    head = nullptr;
    last = nullptr;
}

void CircularLinkedList::addElement(int value) {
    NodeList* newNode = new NodeList(value);
    if (!head) {
        head = newNode;
        last = newNode;
        head->next = head;
    }
    else {
        last->next = newNode;
        newNode->next = head;
        last = newNode;
    }
}

void CircularLinkedList::removeElement(int value) {
    if (!head) return;
    NodeList* curr = head;
    NodeList* prev = last;

    if (head->data == value) {
        if (head == last) {
            delete head;
            head = nullptr;
            last = nullptr;
        }
        else {
            head = head->next;
            last->next = head;
            delete curr;
        }
        return;
    }

    do {
        if (curr->data == value) {
            prev->next = curr->next;
            if (curr == last) {
                last = prev;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != head);
}

void CircularLinkedList::printList() const {
    if (!head) return;
    NodeList* temp = head;
    do {
        std::cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    std::cout << std::endl;
}

NodeList* CircularLinkedList::findElement(int value) {
    if (!head) return nullptr;
    NodeList* temp = head;
    do {
        if (temp->data == value) return temp;
        temp = temp->next;
    } while (temp != head);
    return nullptr;
}

bool CircularLinkedList::contains(int value) const {
    if (!head) return false;
    NodeList* temp = head;
    do {
        if (temp->data == value) return true;
        temp = temp->next;
    } while (temp != head);
    return false;
}
