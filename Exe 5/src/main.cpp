#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include "avl.h"
#include "bst.h"
#include "suggestion.h"

using namespace std;
using namespace std::chrono;

void printMenu() {
    cout << "Escolha a operação:\n";
    cout << "1. Inserir palavras na AVL\n";
    cout << "2. Inserir palavras na BST\n";
    cout << "3. Imprimir AVL\n";
    cout << "4. Imprimir BST\n";
    cout << "Escolha: ";
}

int main() {
    AVLNode* avlRoot = nullptr;
    Node* bstRoot = nullptr;

    int choice;
    printMenu();
    cin >> choice;
    cin.ignore(); // Limpa o buffer do cin

    if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
        ifstream file("dicionario.txt");
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                size_t delimiterPos = line.find(':');
                if (delimiterPos != string::npos) {
                    string word = line.substr(0, delimiterPos);
                    string meaning = line.substr(delimiterPos + 1);

                    if (choice == 1 || choice == 3) {
                        avlRoot = insert(avlRoot, word, meaning);
                    } else if (choice == 2 || choice == 4) {
                        bstRoot = insertBST(bstRoot, word, meaning);
                    }}
                }
            }
            file.close();
        }

        if (choice == 3) {
            printDeepestNode(avlRoot);
            return 0;
        } else if (choice == 4) {
            printDeepestNodeBST(bstRoot);
            return 0;
        } else {
            cout << "Opção inválida!" << endl;
        }

    string prefix;
    printSuggestions({}, prefix);

    setTerminalMode(true);

    vector<string> suggestions;

    while (true) {
        char ch;
        read(STDIN_FILENO, &ch, 1); // Lê um caractere sem Enter
        if (ch == 27) { // Tecla ESC para sair
            break;
        } else if (ch == 127) { // Backspace
            if (!prefix.empty()) prefix.pop_back();
        } else if (ch == 10) { // Enter
            setTerminalMode(false);
            cout << "\n\n" << prefix << endl;

            string meaning;
            bool found;

            // Medir o tempo apenas durante a busca
            auto start = high_resolution_clock::now();
            if (choice == 1) {
                found = search(avlRoot, prefix, meaning);
            } else {
                found = searchBST(bstRoot, prefix, meaning);
            }
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start).count();

            if (found) {
                cout << "Palavra encontrada." << endl;
                cout << "Significado: " << meaning << endl;
            } else {
                cout << "Palavra não encontrada." << endl;
            }
            cout << "Tempo de busca: " << duration << " microsegundos" << endl;

            break;
        } else if (ch == 9) { // Tecla TAB
            // Se houver sugestões, complete a palavra com a primeira sugestão
            if (!suggestions.empty()) {
                prefix = suggestions[0];
            }
        } else if (isprint(ch)) {
            prefix += ch;
        }

        // Obtenha as sugestões de autocompletar
        if (choice == 1) {
            suggestions = autocomplete(avlRoot, prefix);
        } else {
            suggestions = autocompleteBST(bstRoot, prefix);
        }

        printSuggestions(suggestions, prefix);
    }

    setTerminalMode(false);

    return 0;
}
