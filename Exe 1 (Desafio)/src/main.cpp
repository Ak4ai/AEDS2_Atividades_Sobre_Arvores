#include <iostream>
#include <vector>
using namespace std;

class AVLTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    int rotationCount;

    int height(Node* n) {
        return n ? n->height : 0;
    }

    int getBalance(Node* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        cout << "Right rotation on node " << y->key << endl;
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        rotationCount++;
        return x;
    }

    Node* leftRotate(Node* x) {
        cout << "Left rotation on node " << x->key << endl;
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        rotationCount++;
        return y;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);
        if (balance < -1 && key > node->right->key)
            return leftRotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        nodeCount++;
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0) {
            cout << "Right rotation needed on node " << root->key << endl;
            return rightRotate(root);
        }
        if (balance > 1 && getBalance(root->left) < 0) {
            cout << "Left-Right rotation needed on node " << root->key << endl;
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0) {
            cout << "Left rotation needed on node " << root->key << endl;
            return leftRotate(root);
        }
        if (balance < -1 && getBalance(root->right) > 0) {
            cout << "Right-Left rotation needed on node " << root->key << endl;
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void collectKeys(Node* node, vector<int>& keys) {
        if (node != nullptr) {
            collectKeys(node->left, keys);
            keys.push_back(node->key);
            collectKeys(node->right, keys);
        }
    }

    Node* cloneTree(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->key);
        newNode->left = cloneTree(node->left);
        newNode->right = cloneTree(node->right);
        newNode->height = node->height;
        return newNode;
    }

public:

    int nodeCount = 0;

    AVLTree() : root(nullptr), rotationCount(0) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int remove(int key) {
        rotationCount = 0;
        root = deleteNode(root, key);
        return rotationCount;
    }

    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void inOrder() {
        inOrder(root);
    }

    void printTree(Node* root, string indent = "", bool last = true) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->key << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }

    void printTree() {
        printTree(root);
    }

    vector<pair<int, int>> testRemovals() {
        vector<int> keys;
        collectKeys(root, keys);
        vector<pair<int, int>> rotations;
        for (int key : keys) {
            AVLTree tempTree;
            tempTree.root = cloneTree(root);
            tempTree.rotationCount = 0; // Ensure rotation count is reset for each test
            cout << "\nBefore removing " << key << ":\n";
            tempTree.printTree();
            int rotationsCount = tempTree.remove(key);
            cout << "After removing " << key << ":\n";
            tempTree.printTree();
            rotations.push_back({key, rotationsCount});
        }
        return rotations;
    }
};

int main() {
    AVLTree tree;
    vector<int> keys = {15, 10, 20, 05, 12, 18, 25, 98, 44};
    for (int key : keys) {
        tree.insert(key);
    }

    pair<int, int> maxRotation = {0, 1}; // Inicializa com valores padrão
    vector<int> mostRotatedNodes;

    while (maxRotation.second != 0) {
        maxRotation = {-1, -1}; // Reseta o nó com mais rotações
    
        cout << "Inorder traversal of the constructed AVL tree is \n";
        tree.inOrder();
        cout << endl;

        vector<pair<int, int>> rotations = tree.testRemovals();
        cout << "\nNumber of rotations for each node removal:\n";

        for (const auto& pair : rotations) {
            cout << "Node " << pair.first << ": " << pair.second << " rotations\n";
            if (pair.second > maxRotation.second) {
                maxRotation = pair; // Atualiza se encontrar um nó com mais rotações
            }
        }

        if (maxRotation.second == 0) {
            break; // Sai do loop se o nó com mais rotações tiver 0 rotações
        }

        cout << "\nNode with the most rotations:\n";
        cout << "Node " << maxRotation.first << ": " << maxRotation.second << " rotations\n";

        cout << "\nRemoving node " << maxRotation.first << " from the AVL tree\n";
        tree.remove(maxRotation.first);
        cout << endl;
        mostRotatedNodes.push_back(maxRotation.first);
    }
    cout << "\n\n" << "Nodes with the most rotations:\n";
    for (int node : mostRotatedNodes) {
        cout << "Node " << node << " had the most rotations\n";
    }
    
    return 0;
    
}