#ifndef BST_H
#define BST_H

#include <string>
#include <vector>

// Estrutura de nó para a árvore BST
struct Node {
    std::string word;       // Palavra
    std::string meaning;    // Significado da palavra
    Node* left;             // Ponteiro para o nó à esquerda
    Node* right;            // Ponteiro para o nó à direita

    // Construtor
    Node(const std::string& w, const std::string& m) 
        : word(w), meaning(m), left(nullptr), right(nullptr) {}
};

// Funções para manipulação da árvore BST
Node* insertBST(Node* node, const std::string& word, const std::string& meaning);

// Função para buscar uma palavra e seu significado
bool searchBST(Node* root, const std::string& word, std::string& meaning);

// Funções para autocomplete (sugestões de palavras)
void autocompleteHelperBST(Node* node, const std::string& prefix, std::vector<std::string>& results);
std::vector<std::string> autocompleteBST(Node* root, const std::string& prefix);


// Função auxiliar para encontrar a profundidade máxima da árvore
int maxDepth(Node* node);
// Função auxiliar para encontrar o nó mais profundo
void deepestNodeHelperBST(Node* node, int level, Node*& deepestNode);
// Função para encontrar e imprimir o nó mais profundo
void printDeepestNodeBST(Node* root);

#endif // BST_H
