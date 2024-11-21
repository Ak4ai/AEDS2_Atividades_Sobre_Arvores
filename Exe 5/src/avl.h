#ifndef AVL_H
#define AVL_H

#include <string>
#include <vector>

// Estrutura de nó para a árvore AVL
struct AVLNode {
    std::string word;       // Palavra
    std::string meaning;    // Significado da palavra
    AVLNode* left;          // Ponteiro para o nó à esquerda
    AVLNode* right;         // Ponteiro para o nó à direita
    int height;             // Altura do nó

    // Construtor
    AVLNode(const std::string& w, const std::string& m) 
        : word(w), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

// Funções auxiliares para manipulação da árvore AVL
int height(AVLNode* node);
void updateHeight(AVLNode* node);
int balanceFactor(AVLNode* node);

// Funções de rotação
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);

// Função para balancear a árvore
AVLNode* balance(AVLNode* node);

// Inserção de um novo nó na árvore AVL
AVLNode* insert(AVLNode* node, const std::string& word, const std::string& meaning);

// Busca de uma palavra e seu significado na árvore AVL
bool search(AVLNode* root, const std::string& word, std::string& meaning);

// Funções para autocomplete (sugestões de palavras)
void autocompleteHelper(AVLNode* node, const std::string& prefix, std::vector<std::string>& results);
std::vector<std::string> autocomplete(AVLNode* root, const std::string& prefix);

// Função auxiliar para encontrar o nó mais profundo
void findDeepestNodeHelper(AVLNode* node, int depth, int& maxDepth, AVLNode*& deepestNode);

// Função para encontrar o nó mais profundo da árvore AVL
AVLNode* findDeepestNode(AVLNode* root);

// Função para imprimir o nó mais profundo da árvore AVL
void printDeepestNode(AVLNode* root);

#endif // AVL_H
