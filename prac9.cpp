// A Dictionary stores keywords and its meanings. Provide facility for adding new 
// keywords,  deleting  keywords,  updating  values  of  any  entry.  Provide  facility  to  display 
// whole  data  sorted  in  ascending/  Descending  order.  Also  find  how  many  maximum 
// comparisons may require for finding any keyword. Use Height balance tree and find the 
// complexity for finding a keyword 

#include <iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node *left, *right;

    Node(string k, string m) {
        key = k;
        meaning = m;
        left = right = NULL;
    }
};

class AVL {
    Node* root;

public:
    AVL() { root = NULL; }

    void create();
    Node* insert(Node* cur, Node* temp);
    Node* balance(Node* temp);
    int getBalanceFactor(Node* temp);
    int height(Node* temp);
    Node* rotateLL(Node* par);
    Node* rotateRR(Node* par);
    Node* rotateLR(Node* par);
    Node* rotateRL(Node* par);
    void ascending(Node* temp);
    void descending(Node* temp);
    void display();
    bool search(Node* cur, string key1);
    void search_value();
    Node* deleteNode(Node* cur, string key1);
    void deleten();
    Node* findMin(Node* t);
};

// Function to create AVL dictionary
void AVL::create() {
    char answer;
    do {
        string key, meaning;
        cout << "\nEnter keyword:\t";
        cin >> key;
        cout << "Enter meaning:\t";
        cin >> meaning;
        Node* temp = new Node(key, meaning);
        root = insert(root, temp);
        cout << "\nAdd another word? (y/n):\t";
        cin >> answer;
    } while (answer == 'y' || answer == 'Y');
}

// Function to insert a node into AVL tree
Node* AVL::insert(Node* cur, Node* temp) {
    if (cur == NULL) return temp;

    if (temp->key < cur->key) {
        cur->left = insert(cur->left, temp);
    } else if (temp->key > cur->key) {
        cur->right = insert(cur->right, temp);
    } else {
        cout << "Duplicate keyword not allowed!";
        return cur;
    }

    return balance(cur);
}

// Function to balance AVL tree
Node* AVL::balance(Node* temp) {
    int balanceFactor = getBalanceFactor(temp);

    if (balanceFactor > 1) {
        if (getBalanceFactor(temp->left) < 0)
            temp = rotateLR(temp);
        else
            temp = rotateLL(temp);
    } else if (balanceFactor < -1) {
        if (getBalanceFactor(temp->right) > 0)
            temp = rotateRL(temp);
        else
            temp = rotateRR(temp);
    }

    return temp;
}

// Function to get height difference
int AVL::getBalanceFactor(Node* temp) {
    return (temp == NULL) ? 0 : height(temp->left) - height(temp->right);
}

// Function to get height of tree
int AVL::height(Node* temp) {
    if (temp == NULL) return 0;
    return max(height(temp->left), height(temp->right)) + 1;
}

// Rotation Functions
Node* AVL::rotateLL(Node* par) {
    Node* temp = par->left;
    par->left = temp->right;
    temp->right = par;
    return temp;
}

Node* AVL::rotateRR(Node* par) {
    Node* temp = par->right;
    par->right = temp->left;
    temp->left = par;
    return temp;
}

Node* AVL::rotateLR(Node* par) {
    par->left = rotateRR(par->left);
    return rotateLL(par);
}

Node* AVL::rotateRL(Node* par) {
    par->right = rotateLL(par->right);
    return rotateRR(par);
}

// Inorder traversal (ascending order)
void AVL::ascending(Node* temp) {
    if (temp != NULL) {
        ascending(temp->left);
        cout << "\n\t" << temp->key << " : " << temp->meaning;
        ascending(temp->right);
    }
}

// Reverse inorder traversal (descending order)
void AVL::descending(Node* temp) {
    if (temp != NULL) {
        descending(temp->right);
        cout << "\n\t" << temp->key << " : " << temp->meaning;
        descending(temp->left);
    }
}

// Function to display dictionary in order
void AVL::display() {
    cout << "\nKeywords in ascending order:\t";
    ascending(root);
    cout << "\nKeywords in descending order:\t";
    descending(root);
}

// Function to search for a key in AVL tree
bool AVL::search(Node* cur, string key1) {
    if (cur == NULL) return false;
    if (cur->key == key1) return true;
    return (cur->key > key1) ? search(cur->left, key1) : search(cur->right, key1);
}

void AVL::search_value() {
    string key2;
    cout << "\nKeyword to search:\t";
    cin >> key2;
    if (search(root, key2))
        cout << "\nKeyword exists in AVL tree.";
    else
        cout << "\nKeyword does not exist in AVL tree.";
}

// Function to delete a node from AVL tree
Node* AVL::deleteNode(Node* cur, string key1) {
    if (!cur) return NULL;
    if (key1 < cur->key)
        cur->left = deleteNode(cur->left, key1);
    else if (key1 > cur->key)
        cur->right = deleteNode(cur->right, key1);
    else {
        if (!cur->left) {
            Node* temp = cur->right;
            delete cur;
            return temp;
        } else if (!cur->right) {
            Node* temp = cur->left;
            delete cur;
            return temp;
        }

        Node* minNode = findMin(cur->right);
        cur->key = minNode->key;
        cur->meaning = minNode->meaning;
        cur->right = deleteNode(cur->right, minNode->key);
    }

    return balance(cur);
}

// Function to find minimum node in AVL tree
Node* AVL::findMin(Node* t) {
    while (t->left) t = t->left;
    return t;
}

void AVL::deleten() {
    string key;
    cout << "\nKeyword to delete:\t";
    cin >> key;
    root = deleteNode(root, key);
}

// **Main Function**
int main() {
    char c;
    int ch;
    AVL a;

    do {
        cout << "\n--- MAIN MENU ---";
        cout << "\n1 -> Insert keyword";
        cout << "\n2 -> Display AVL tree";
        cout << "\n3 -> Search a keyword";
        cout << "\n4 -> Delete a keyword";
        cout << "\nChoose an option (1-4):\t";
        cin >> ch;

        switch (ch) {
            case 1: a.create(); break;
            case 2: a.display(); break;
            case 3: a.search_value(); break;
            case 4: a.deleten(); break;
            default: cout << "\nPlease choose a valid option (1-4).";
        }

        cout << "\nWould you like to continue? (y/n):\t";
        cin >> c;
    } while (c == 'y' || c == 'Y');

    cout << "\n\n// END OF CODE\n\n";
    return 0;
}