// Beginning  with  an  empty  binary  search  tree,  Construct  binary  search  tree  by  inserting 
// the values in the order given. After constructing a binary tree -  
// i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data 
// value found in the tree, iv. Change a tree so that the roles of the left and right pointers 
// are swapped at every node, v. Search a value
#include <iostream>
using namespace std;

// Node structure for the Binary Search Tree
struct Bstnode {
    int data;
    Bstnode* left = NULL;
    Bstnode* right = NULL;
};

// Binary Tree class
class Btree {
public:
    Bstnode* root;

    Btree() {
        root = NULL;
    }

    // Function to create a new node
    Bstnode* GetNewNode(int in_data) {
        Bstnode* ptr = new Bstnode();
        ptr->data = in_data;
        return ptr;
    }

    // Insert a node into the tree
    Bstnode* insert(Bstnode* temp, int in_data) {
        if (temp == NULL) {
            return GetNewNode(in_data);
        }
        if (in_data < temp->data) {
            temp->left = insert(temp->left, in_data);
        } else {
            temp->right = insert(temp->right, in_data);
        }
        return temp;
    }

    // Wrapper to add a node
    void addNode() {
        int value;
        cout << "Enter value to insert into the tree: ";
        cin >> value;
        root = insert(root, value);
        cout << "Node " << value << " inserted successfully!" << endl;
    }

    // Find the depth of the tree (longest path from root)
    int findDepth(Bstnode* temp) {
        if (temp == NULL)
            return 0;
        return max(findDepth(temp->left), findDepth(temp->right)) + 1;
    }

    // Wrapper to find the depth
    void displayDepth() {
        if (root == NULL) {
            cout << "The tree is empty!" << endl;
        } else {
            cout << "Number of nodes in the longest path (depth): " << findDepth(root) << endl;
        }
    }

    // Find the minimum value in the tree
    void findMinValue() {
        if (root == NULL) {
            cout << "The tree is empty!" << endl;
            return;
        }
        Bstnode* temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        cout << "Minimum value in the tree: " << temp->data << endl;
    }

    // Mirror the tree (swap left and right pointers)
    void mirrorTree(Bstnode* temp) {
        if (temp == NULL)
            return;
        swap(temp->left, temp->right);
        mirrorTree(temp->left);
        mirrorTree(temp->right);
    }

    // Wrapper to mirror the tree
    void mirror() {
        if (root == NULL) {
            cout << "The tree is empty!" << endl;
            return;
        }
        mirrorTree(root);
        cout << "Tree mirrored successfully!" << endl;
    }

    // Search for a value in the tree
    bool search(Bstnode* temp, int in_data) {
        if (temp == NULL)
            return false;
        if (temp->data == in_data)
            return true;
        if (in_data < temp->data)
            return search(temp->left, in_data);
        return search(temp->right, in_data);
    }

    // Wrapper to search for a value
    void searchValue() {
        int value;
        cout << "Enter value to search: ";
        cin >> value;
        if (search(root, value)) {
            cout << "Value " << value << " found in the tree." << endl;
        } else {
            cout << "Value " << value << " not found in the tree." << endl;
        }
    }

    // Inorder traversal
    void inorder(Bstnode* temp) {
        if (temp == NULL)
            return;
        inorder(temp->left);
        cout << temp->data << " ";
        inorder(temp->right);
    }

    // Wrapper to display the tree
    void display() {
        if (root == NULL) {
            cout << "The tree is empty!" << endl;
            return;
        }
        cout << "Inorder traversal of the tree: ";
        inorder(root);
        cout << endl;
    }
};

// Main function
int main() {
    Btree tree;
    int choice;

    while (true) {
        cout << "\nMenu:\n"
             << "1. Insert new node\n"
             << "2. Find number of nodes in the longest path (depth)\n"
             << "3. Find minimum data value in the tree\n"
             << "4. Mirror the tree\n"
             << "5. Search for a value\n"
             << "6. Display tree\n"
             << "7. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tree.addNode();
                break;
            case 2:
                tree.displayDepth();
                break;
            case 3:
                tree.findMinValue();
                break;
            case 4:
                tree.mirror();
                break;
            case 5:
                tree.searchValue();
                break;
            case 6:
                tree.display();
                break;
            case 7:
                cout << "Exiting program!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }

    return 0;
}