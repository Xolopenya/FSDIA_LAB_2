#include <iostream>
#include <fstream>
#include <string>
#include "RBT.h"

int main() {
    RedBlackTree tree;

    // Чтение данных из файла и добавление в дерево
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file!" << std::endl;
        return 1;
    }

    std::string series, number;
    int lineNumber = 0;

    while (inputFile >> series >> number) {
        lineNumber++;
        tree.insert(series, number, lineNumber); // Добавляем номер строки
    }

    inputFile.close();

    // Сохранение дерева в файл после начальной вставки
    tree.saveToFile("output_with_lines.txt");

    std::cout << "Tree after insertion from file:\n";
    tree.showTree();

    // Интерактивное меню
    char choice;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "a - Add a new element\n";
        std::cout << "d - Delete an element\n";
        std::cout << "f - Find an element\n";
        std::cout << "s - Show the tree\n";
        std::cout << "q - Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 'a') {
            std::cout << "Enter series (4 digits): ";
            std::cin >> series;
            std::cout << "Enter number (6 digits): ";
            std::cin >> number;
            lineNumber++; // Увеличиваем номер строки для добавляемого элемента
            tree.insert(series, number, lineNumber);
            std::cout << "Element added successfully!\n";
        }
        else if (choice == 'd') {
            std::cout << "Enter series (4 digits) of the element to delete: ";
            std::cin >> series;
            std::cout << "Enter number (6 digits) of the element to delete: ";
            std::cin >> number;
            tree.remove(series, number);
            std::cout << "Element deleted successfully!\n";
        }
        else if (choice == 'f') {
            std::cout << "Enter series (4 digits) of the element to find: ";
            std::cin >> series;
            std::cout << "Enter number (6 digits) of the element to find: ";
            std::cin >> number;
            tree.findAndDisplay(series, number);
        }
        else if (choice == 's') {
            tree.showTree();
        }
        else if (choice != 'q') {
            std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 'q');

    // Сохранение дерева в файл после завершения работы
    tree.saveToFile("output_inOrder.txt");
    std::cout << "Tree saved to output_inOrder.txt. Goodbye!\n";

    return 0;
}
