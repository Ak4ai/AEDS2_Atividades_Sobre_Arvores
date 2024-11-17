#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Estrutura de no da arvore binaria
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Funcao para inserir um novo no na arvore
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Funcao para encontrar o valor minimo em uma arvore (usada na remocao)
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Funcao para remover um no da arvore
Node* remove(Node* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = remove(root->left, value);
    } else if (value > root->data) {
        root->right = remove(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data);
    }
    return root;
}

// Funcao para calcular o nivel maximo (altura) da arvore
int calcNivelMaximo(Node* root) {
    if (root == nullptr) return -1; // arvore vazia tem altura -1
    int leftHeight = calcNivelMaximo(root->left);
    int rightHeight = calcNivelMaximo(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Funcao para encontrar o caminho mais longo da raiz ate a folha mais distante
void encontrarCaminhoMaisLongo(Node* root, vector<int>& caminhoAtual, vector<int>& caminhoMaisLongo) {
    if (root == nullptr) return;

    caminhoAtual.push_back(root->data);
    if (root->left == nullptr && root->right == nullptr) { // No folha
        if (caminhoAtual.size() > caminhoMaisLongo.size()) {
            caminhoMaisLongo = caminhoAtual;
        }
    }
    encontrarCaminhoMaisLongo(root->left, caminhoAtual, caminhoMaisLongo);
    encontrarCaminhoMaisLongo(root->right, caminhoAtual, caminhoMaisLongo);
    caminhoAtual.pop_back(); // Retirar o no atual ao retornar
}

// Funcao para exibir o caminho mais longo
void mostrarCaminhoMaisLongo(Node* root) {
    vector<int> caminhoAtual, caminhoMaisLongo;
    encontrarCaminhoMaisLongo(root, caminhoAtual, caminhoMaisLongo);

    cout << "Caminho mais longo da raiz ate a folha mais distante: ";
    for (int valor : caminhoMaisLongo) {
        cout << valor << " ";
    }
    cout << endl;
}

// Funcao auxiliar para exibir o nivel maximo (altura) e o caminho mais longo
void exibirInfoArvore(Node* root) {
    int nivelMaximo = calcNivelMaximo(root);
    cout << "Nivel maximo (altura) da arvore: " << nivelMaximo << endl;
    mostrarCaminhoMaisLongo(root);
}

// Funcao para printar a arvore com seus galhos usando / e \ para os filhos
void printArvore(Node* root, string prefixo = "", bool isLeft = true) {
    if (root != nullptr) {
        cout << prefixo;

        if (isLeft) {
            cout << "L-- ";
            prefixo += "|   ";
        } else {
            cout << "R-- ";
            prefixo += "    ";
        }

        // Printar o valor do no atual
        cout << root->data << endl;

        // Chamar recursivamente para os filhos esquerdo e direito
        printArvore(root->left, prefixo, true);
        printArvore(root->right, prefixo, false);
    }
}

// Funcao para comparar o crescimento de duas arvores e calcular a depreciacao
void compararCrescimentoArvores(const vector<int>& insercoesDesbalanceada, const vector<int>& insercoesEquilibrada) {
    Node* rootDesbalanceada = nullptr;
    Node* rootEquilibrada = nullptr;
    cout << "\n\n";
    cout << "-------------------------------------------------------------------\n";
    cout << "Comparacao do crescimento das arvores:\n";
    cout << "Insercao\tNivel Max Desbal\tNivel Max Equil\tDepreciacao (%)\n";
    cout << "-------------------------------------------------------------------\n";

    for (size_t i = 0; i < insercoesDesbalanceada.size(); i++) {
        // Inserir na arvore desbalanceada e calcular o nivel maximo
        rootDesbalanceada = insert(rootDesbalanceada, insercoesDesbalanceada[i]);
        int nivelMaximoDesbalanceada = calcNivelMaximo(rootDesbalanceada);

        // Inserir na arvore equilibrada e calcular o nivel maximo
        rootEquilibrada = insert(rootEquilibrada, insercoesEquilibrada[i]);
        int nivelMaximoEquilibrada = calcNivelMaximo(rootEquilibrada);

        // Calcular a diferenca percentual entre os niveis maximos das arvores
        double depreciacaoPercentual = 0;
        if (nivelMaximoEquilibrada > 0) {
            depreciacaoPercentual = ((double)(nivelMaximoDesbalanceada - nivelMaximoEquilibrada) / nivelMaximoEquilibrada) * 100;
        }

        // Exibir resultados para a insercao atual
        cout << insercoesDesbalanceada[i] << "\t\t"
             << nivelMaximoDesbalanceada << "\t\t\t"
             << nivelMaximoEquilibrada << "\t\t"
             << depreciacaoPercentual << "%\n";
    }

    // Exibir informacões finais
    cout << "\nNivel maximo final - arvore desbalanceada: " << calcNivelMaximo(rootDesbalanceada) << endl;
    cout << "Nivel maximo final - arvore equilibrada: " << calcNivelMaximo(rootEquilibrada) << endl;
    
    cout << "-------------------------------------------------------------------\n";
}

void modificarArvore(Node*& root) {
    char escolha;
    int valor;

    cout << "Estrutura da árvore atualizada:" << endl;
    printArvore(root);
    while (true) {
        cout << "\nDeseja inserir (I) ou remover (R) um no? (ou Q para sair): ";
        cin >> escolha;

        if (escolha == 'Q' || escolha == 'q') {
            break; // Sair do loop
        }

        cout << "Digite o valor do no: ";
        cin >> valor;

        if (escolha == 'I' || escolha == 'i') {
            root = insert(root, valor);
            cout << "No " << valor << " inserido com sucesso." << endl;
        } else if (escolha == 'R' || escolha == 'r') {
            root = remove(root, valor);
            cout << "No " << valor << " removido com sucesso." << endl;
        } else {
            cout << "Escolha inválida. Tente novamente." << endl;
            continue; // Solicitar novamente
        }

        // Exibir informações da árvore apos a modificaçao
        exibirInfoArvore(root);
        cout << "Estrutura da árvore atualizada:" << endl;
        printArvore(root);
    }
}

int main() {
    Node* rootDesbalanceada = nullptr;
    Node* rootEquilibrada = nullptr;

    // Insercões para uma arvore desbalanceada (ordem crescente)
    vector<int> insercoesDesbalanceada = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    // Insercões para uma arvore mais equilibrada
    vector<int> insercoesEquilibrada = {50, 30, 70, 20, 40, 60, 80, 10, 90, 100};

    cout << "Crescimento da arvore desbalanceada:\n";
    for (int valor : insercoesDesbalanceada) {
        rootDesbalanceada = insert(rootDesbalanceada, valor);
        int nivelMaximo = calcNivelMaximo(rootDesbalanceada);
        cout << "Apos inserir " << valor << ", nivel maximo: " << nivelMaximo << endl;
    }

    cout << "\nCrescimento da arvore equilibrada:\n";
    for (int valor : insercoesEquilibrada) {
        rootEquilibrada = insert(rootEquilibrada, valor);
        int nivelMaximo = calcNivelMaximo(rootEquilibrada);
        cout << "Apos inserir " << valor << ", nivel maximo: " << nivelMaximo << endl;
    }

    // Exibir informacões finais das duas arvores
    cout << "\n\n-------------------------------------------------------------------\n";
    cout << "arvore desbalanceada final:\n";
    exibirInfoArvore(rootDesbalanceada);
    cout << "Estrutura da arvore desbalanceada:\n";
    printArvore(rootDesbalanceada);
    cout << "-------------------------------------------------------------------\n";

    cout << "-------------------------------------------------------------------\n";
    cout << "arvore equilibrada final:\n";
    exibirInfoArvore(rootEquilibrada);
    cout << "Estrutura da arvore equilibrada:\n";
    printArvore(rootEquilibrada);
    cout << "-------------------------------------------------------------------\n";

    compararCrescimentoArvores(insercoesDesbalanceada, insercoesEquilibrada);

    // Criar uma árvore a partir das inserções equilibradas para a modificaçao
    Node* root = nullptr;
    for (int valor : insercoesEquilibrada) {
        root = insert(root, valor);
    }

    // Permitir ao usuário modificar a árvore
    modificarArvore(root);

    return 0;
}

