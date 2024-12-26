// RedBlackTree.cpp
#include "RBT.h"


RedBlackTree::RedBlackTree() {
    TNULL = new Node("", "");
    initializeNullNode(TNULL, nullptr);
    root = TNULL; // Инициализация корня
}


RedBlackTree::~RedBlackTree() {
    freeMemory(root);
    delete TNULL;
}

void RedBlackTree::initializeNullNode(Node* node, Node* parent) {
    node->series = "";
    node->number = "";
    node->color = BLACK;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;
}

void RedBlackTree::inOrderTraversal(Node* node, std::ofstream& outFile) {
    if (node == TNULL) return;
    inOrderTraversal(node->left, outFile);

    outFile << node->series << " " << node->number;


    if (node->lineNumbers.contains(0) || !node->lineNumbers.contains(1)) {
        outFile << " [Lines: ";
        NodeList* current = node->lineNumbers.head;
        if (current) {
            do {
                outFile << current->data;
                current = current->next;
                if (current != node->lineNumbers.head) {
                    outFile << ", ";
                }
            } while (current != node->lineNumbers.head);
        }
        outFile << "]";
    }
    outFile << std::endl;

    inOrderTraversal(node->right, outFile);
}


void RedBlackTree::showTreeHelper(Node* root, int level) {
    if (root == TNULL || root == nullptr) {
        return;
    }

    showTreeHelper(root->right, level + 1);

    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }

    std::string color = (root->color == RED) ? "RED" : "BLACK";
    std::cout << root->series << " " << root->number << " (" << color << ")";

    // Безусловная печать для диагностики
    if (root->lineNumbers.head) {
        std::cout << " [Lines: ";
        NodeList* current = root->lineNumbers.head;
        do {
            std::cout << current->data;
            current = current->next;
            if (current != root->lineNumbers.head) {
                std::cout << ", ";
            }
        } while (current != root->lineNumbers.head);
        std::cout << "]";
    }
    else {
        std::cout << " [No Lines]";
    }

    std::cout << std::endl;

    showTreeHelper(root->left, level + 1);
}



void RedBlackTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node* k) {
    while (k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            Node* u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rotateRight(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateLeft(k->parent->parent);
            }
        }
        else {
            Node* u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            }
            else {
                if (k == k->parent->right) {
                    k = k->parent;
                    rotateLeft(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rotateRight(k->parent->parent);
            }
        }
        if (k == root) break;
    }
    root->color = BLACK;
}

Node* RedBlackTree::search(Node* node, const std::string& series, const std::string& number) {
    if (node == TNULL || (node->series == series && node->number == number)) {
        return node;
    }
    if (series < node->series || (series == node->series && number < node->number)) {
        return search(node->left, series, number);
    }
    return search(node->right, series, number);
}

void RedBlackTree::freeMemory(Node* node) {
    if (node == TNULL) return;
    freeMemory(node->left);
    freeMemory(node->right);
    delete node;
}

void RedBlackTree::fixDelete(Node* x) {
    Node* s;
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                s = x->parent->right;
            }
            if (s->left->color == BLACK && s->right->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rotateRight(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        }
        else {
            s = x->parent->left;
            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                s = x->parent->left;
            }
            if (s->right->color == BLACK && s->left->color == BLACK) {
                s->color = RED;
                x = x->parent;
            }
            else {
                if (s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    rotateLeft(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                s->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::transplant(Node* u, Node* v) {
    if (u->parent == nullptr) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


Node* RedBlackTree::deleteNode(Node* node, const std::string& series, const std::string& number) {
    Node* z = TNULL;
    Node* x, * y;
    while (node != TNULL) {
        if (node->series == series && node->number == number) {
            z = node;
        }
        if (node->series <= series) {
            node = node->right;
        }
        else {
            node = node->left;
        }
    }
    if (z == TNULL) return node;
    y = z;
    int yOriginalColor = y->color;
    if (z->left == TNULL) {
        x = z->right;
        transplant(z, z->right);
    }
    else if (z->right == TNULL) {
        x = z->left;
        transplant(z, z->left);
    }
    else {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) {
        fixDelete(x);
    }
    return root;
}

void RedBlackTree::remove(const std::string& series, const std::string& number) {
    if (root != nullptr) { // Проверка, что дерево инициализировано
        root = deleteNode(root, series, number);
    }
    else {
        std::cerr << "Error: Tree is empty. Cannot remove element.\n";
    }
}

Node* RedBlackTree::findMin(Node* node) {
    while (node->left != TNULL) node = node->left;
    return node;
}

void RedBlackTree::insert(const std::string& series, const std::string& number, int lineNumber) {
    if (series.length() != 4 || series.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Error: Series must be exactly 4 digits.\n";
        return;
    }
    if (number.length() != 6 || number.find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Error: Number must be exactly 6 digits.\n";
        return;
    }

    Node* node = new Node(series, number);
    node->lineNumbers.addElement(lineNumber); // Добавляем номер строки

    node->parent = nullptr;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;

    Node* y = nullptr;
    Node* x = root;

    while (x != TNULL) {
        y = x;
        if (node->series == x->series && node->number == x->number) {
            x->lineNumbers.addElement(lineNumber); // Обновляем номера строк
            delete node; // Удаляем временный узел
            return;
        }

        if (node->series < x->series || (node->series == x->series && node->number < x->number)) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }

    node->parent = y;
    if (y == nullptr) {
        root = node;
    }
    else if (node->series < y->series || (node->series == y->series && node->number < y->number)) {
        y->left = node;
    }
    else {
        y->right = node;
    }

    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }

    if (node->parent->parent == nullptr) {
        return;
    }

    fixInsert(node);
}


void RedBlackTree::showTree() {
    std::cout << "Red-Black Tree Visualization:" << std::endl;
    showTreeHelper(root, 0);
}

void RedBlackTree::saveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return;
    }
    inOrderTraversal(root, outFile);
    outFile.close();
}

void RedBlackTree::findAndDisplay(const std::string& series, const std::string& number) {
    Node* result = search(root, series, number);
    if (result != TNULL) {
        std::cout << "Found element: " << result->series << " " << result->number << "\n";
    }
    else {
        std::cout << "Element not found.\n";
    }
}


