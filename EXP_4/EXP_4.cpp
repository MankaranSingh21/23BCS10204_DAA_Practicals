#include <iostream>
using namespace std;

// -------------------- DOUBLY LINKED LIST --------------------
class DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val) : data(val), prev(NULL), next(NULL) {}
    };

    Node* head;

public:
    DoublyLinkedList() : head(NULL) {}

    // Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (head != NULL) {
            newNode->next = head;
            head->prev = newNode;
        }
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
        newNode->prev = temp;
    }

    // Delete at beginning
    void deleteAtBeginning() {
        if (head == NULL) return;
        Node* temp = head;
        head = head->next;
        if (head != NULL) head->prev = NULL;
        delete temp;
    }

    // Delete at end
    void deleteAtEnd() {
        if (head == NULL) return;
        Node* temp = head;
        while (temp->next != NULL) temp = temp->next;
        if (temp->prev != NULL) temp->prev->next = NULL;
        else head = NULL;
        delete temp;
    }

    void display() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

// -------------------- CIRCULAR LINKED LIST --------------------
class CircularLinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(NULL) {}
    };

    Node* head;

public:
    CircularLinkedList() : head(NULL) {}

    // Insert at beginning
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = newNode;
            newNode->next = head;
            return;
        }
        Node* temp = head;
        while (temp->next != head) temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
    }

    // Delete at beginning
    void deleteAtBeginning() {
        if (head == NULL) return;
        if (head->next == head) {
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        Node* last = head;
        while (last->next != head) last = last->next;
        head = head->next;
        last->next = head;
        delete temp;
    }

    // Delete at end
    void deleteAtEnd() {
        if (head == NULL) return;
        if (head->next == head) {
            delete head;
            head = NULL;
            return;
        }
        Node* temp = head;
        while (temp->next->next != head) temp = temp->next;
        Node* last = temp->next;
        temp->next = head;
        delete last;
    }

    void display() {
        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }
        Node* temp = head;
        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "(back to head)\n";
    }
};

// -------------------- MAIN --------------------
int main() {
    cout << "===== DOUBLY LINKED LIST =====\n";
    DoublyLinkedList dll;
    dll.insertAtBeginning(10);
    dll.insertAtEnd(20);
    dll.insertAtEnd(30);
    dll.display();
    dll.deleteAtBeginning();
    dll.display();
    dll.deleteAtEnd();
    dll.display();

    cout << "\n===== CIRCULAR LINKED LIST =====\n";
    CircularLinkedList cll;
    cll.insertAtBeginning(5);
    cll.insertAtEnd(15);
    cll.insertAtEnd(25);
    cll.display();
    cll.deleteAtBeginning();
    cll.display();
    cll.deleteAtEnd();
    cll.display();

    return 0;
}
