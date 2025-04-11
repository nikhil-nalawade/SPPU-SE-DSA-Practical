// Consider a scenario for Hospital to cater services to different kinds of patients as Serious 
// (top  priority),  b)  non-serious  (medium  priority),  c)  General  Checkup  (Least  priority). 
// Implement the priority queue to cater services to the patients
#include <iostream>
using namespace std;

class Node {
public:
    string data;
    int priority;
    Node* next;

    Node(string d, int prior) {
        data = d;
        priority = prior;
        next = NULL;
    }
};

class PriorityQueue {
public:
    Node* front = NULL;

    // Insert patient in priority order
    void insert(string d, int prior) {
        Node* temp = new Node(d, prior);

        // If queue is empty OR new node has higher priority than front
        if (front == NULL || front->priority < prior) {
            temp->next = front;
            front = temp;
        } else {
            Node* rear = front;
            while (rear->next != NULL && rear->next->priority >= prior) {
                rear = rear->next;
            }
            temp->next = rear->next;
            rear->next = temp;
        }
        cout << "Patient " << d << " added with priority " << prior << ".\n";
    }

    // Peek first patient
    void peek() {
        if (front == NULL) {
            cout << "Queue is empty!\n";
            return;
        }
        cout << "First patient is: " << front->data << " with priority " << front->priority << ".\n";
    }

    // Remove the highest priority patient
    void pop() {
        if (front == NULL) {
            cout << "No patients to remove!\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        cout << "Patient " << temp->data << " removed.\n";
        delete temp; // Prevent memory leak
    }

    // Display all patients
    void display() {
        if (front == NULL) {
            cout << "No patients in queue.\n";
            return;
        }
        cout << "\nPatient List:\n";
        Node* curr = front;
        while (curr != NULL) {
            string currPrior;
            if (curr->priority == 3)
                currPrior = "Serious";
            else if (curr->priority == 2)
                currPrior = "Non-serious";
            else
                currPrior = "General checkup";

            cout << curr->data << " with priority: " << currPrior << "\n";
            curr = curr->next;
        }
    }
};

int main() {
    string name;
    int priority, choice;
    PriorityQueue q;

    do {
        cout << "\n--- MAIN MENU ---";
        cout << "\n1 -> Add patient";
        cout << "\n2 -> Remove patient";
        cout << "\n3 -> Display all patients";
        cout << "\n4 -> Peek first patient";
        cout << "\n0 -> Exit";
        cout << "\nChoose an option (0-4): ";
        cin >> choice;
        cin.ignore(); // Ensures getline works correctly after numeric input

        switch (choice) {
            case 1:
                cout << "Patient name: ";
                getline(cin, name);
                cout << "Enter priority (3-High, 2-Medium, 1-General): ";
                cin >> priority;
                if (priority < 1 || priority > 3) {
                    cout << "Invalid priority! Enter between 1-3.\n";
                    break;
                }
                q.insert(name, priority);
                break;
            case 2:
                q.pop();
                break;
            case 3:
                q.display();
                break;
            case 4:
                q.peek();
                break;
            case 0:
                cout << "\nExiting program. Thank you!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
