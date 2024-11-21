#include "avl.h"
#include <algorithm>
#include <iostream>

// Funções auxiliares para manipulação da altura
int height(AVLNode* node) {
    return node ? node->height : 0;
}

void updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

int balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Funções de rotação
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// Balanceamento da árvore
AVLNode* balance(AVLNode* node) {
    updateHeight(node);

    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// Inserção na árvore AVL
AVLNode* insert(AVLNode* node, const std::string& word, const std::string& meaning) {
    if (!node) return new AVLNode(word, meaning);

    if (word < node->word) {
        node->left = insert(node->left, word, meaning);
    } else if (word > node->word) {
        node->right = insert(node->right, word, meaning);
    } else {
        // Palavra já existe, não faz nada
        return node;
    }

    return balance(node);
}

// Busca de uma palavra e seu significado na árvore AVL
bool search(AVLNode* root, const std::string& word, std::string& meaning) {
    if (!root) return false;

    if (word < root->word) {
        return search(root->left, word, meaning);
    } else if (word > root->word) {
        return search(root->right, word, meaning);
    } else {
        meaning = root->meaning;
        return true;
    }
}

// Autocomplete para árvore AVL
void autocompleteHelper(AVLNode* node, const std::string& prefix, std::vector<std::string>& results) {
    if (!node) return;

    if (node->word.find(prefix) == 0) {
        results.push_back(node->word);
    }

    if (prefix <= node->word) {
        autocompleteHelper(node->left, prefix, results);
    }
    if (prefix >= node->word) {
        autocompleteHelper(node->right, prefix, results);
    }
}

std::vector<std::string> autocomplete(AVLNode* root, const std::string& prefix) {
    std::vector<std::string> results;
    autocompleteHelper(root, prefix, results);
    return results;
}

// Função auxiliar para encontrar o nó mais profundo
void findDeepestNodeHelper(AVLNode* node, int depth, int& maxDepth, AVLNode*& deepestNode) {
    if (node == nullptr) return;

    // Se a profundidade atual for maior que a profundidade máxima, atualize o nó mais profundo
    if (depth > maxDepth) {
        maxDepth = depth;
        deepestNode = node;
    }

    // Percorre a subárvore esquerda
    findDeepestNodeHelper(node->left, depth + 1, maxDepth, deepestNode);

    // Percorre a subárvore direita
    findDeepestNodeHelper(node->right, depth + 1, maxDepth, deepestNode);
}

// Função para encontrar o nó mais profundo da árvore AVL
AVLNode* findDeepestNode(AVLNode* root) {
    int maxDepth = -1;
    AVLNode* deepestNode = nullptr;
    findDeepestNodeHelper(root, 0, maxDepth, deepestNode);
    return deepestNode;
}

// Função para imprimir o nó mais profundo
void printDeepestNode(AVLNode* root) {
    AVLNode* deepestNode = findDeepestNode(root);
    if (deepestNode) {
        std::cout << "O nó mais profundo é: " << deepestNode->word << " com significado: " << deepestNode->meaning << std::endl;
    } else {
        std::cout << "A árvore está vazia." << std::endl;
    }
}
