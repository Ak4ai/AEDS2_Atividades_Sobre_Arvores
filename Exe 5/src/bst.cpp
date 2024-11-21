#include "bst.h"
#include <iostream>
#include <queue>

// Função para inserir um nó na árvore BST
Node* insertBST(Node* node, const std::string& word, const std::string& meaning) {
    if (!node) return new Node(word, meaning);

    if (word < node->word) {
        node->left = insertBST(node->left, word, meaning);
    } else if (word > node->word) {
        node->right = insertBST(node->right, word, meaning);
    }

    return node;
}

// Função para buscar uma palavra e seu significado na árvore BST
bool searchBST(Node* root, const std::string& word, std::string& meaning) {
    if (!root) return false;

    if (word < root->word) {
        return searchBST(root->left, word, meaning);
    } else if (word > root->word) {
        return searchBST(root->right, word, meaning);
    } else {
        meaning = root->meaning;
        return true;
    }
}

// Função auxiliar para autocomplete (sugestões) na árvore BST
void autocompleteHelperBST(Node* node, const std::string& prefix, std::vector<std::string>& results) {
    if (!node) return;

    if (node->word.find(prefix) == 0) {
        results.push_back(node->word);
    }

    if (prefix <= node->word) {
        autocompleteHelperBST(node->left, prefix, results);
    }

    if (prefix >= node->word) {
        autocompleteHelperBST(node->right, prefix, results);
    }
}

// Função principal de autocomplete na árvore BST
std::vector<std::string> autocompleteBST(Node* root, const std::string& prefix) {
    std::vector<std::string> results;
    autocompleteHelperBST(root, prefix, results);
    return results;
}

// Função auxiliar para encontrar a profundidade máxima da árvore
int maxDepth(Node* node) {
    if (!node) return 0;
    int leftDepth = maxDepth(node->left);
    int rightDepth = maxDepth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
}

// Função auxiliar para encontrar o nó mais profundo
void deepestNodeHelperBST(Node* node, int level, Node*& deepestNode) {
    if (!node) return;
    if (level == 1) {
        deepestNode = node;
    } else if (level > 1) {
        deepestNodeHelperBST(node->left, level - 1, deepestNode);
        deepestNodeHelperBST(node->right, level - 1, deepestNode);
    }
}

// Função para encontrar e imprimir o nó mais profundo
void printDeepestNodeBST(Node* root) {
    int depth = maxDepth(root);
    Node* deepestNode = nullptr;
    deepestNodeHelperBST(root, depth, deepestNode);
    if (deepestNode) {
        std::cout << "O nó mais profundo é: " << deepestNode->word << " com significado: " << deepestNode->meaning << std::endl;
    } else {
        std::cout << "A árvore está vazia." << std::endl;
    }
}
