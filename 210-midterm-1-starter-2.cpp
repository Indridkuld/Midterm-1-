#include <iostream> // iostream is a library that brings in functionality for input and output like cout and cin
using namespace std; // allows standard library features without std:: 

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // all of these are constant integer values

class DoublyLinkedList { // this is the start of the DoublyLinkedList class definition which is an abstract data type
private: // this identifier indicates that everything under it is private to the class, and cannot be accessed outside of it
//classes are baseline private in c++ while structs are baseline public
    struct Node { // this is the definition of the Node struct as the first data type of the DoublyLinkedList class
        int data; // integer data member of the Node struct, contains the main data that the node is actually storing in the linked list
        Node* prev; // this is a node object pointer, will be used to point to the previous node in the list
        Node* next; // this is another node object pointer, will be used to point to the next node in the list
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // constructor of the Node struct, it takes an integer value and optionally two node pointers
            data = val; // initializes the data member with the provided integer value 'val'
            prev = p; // initializes the prev pointer with the provided node pointer 'p', defaults to nullptr if not provided
            next = n; // initializes the next pointer with the provided node pointer 'n', defaults to nullptr if not provided
        }
    };
    // the below are the data members of the DoublyLinkedList class, not Node struct
    Node* head; // Node pointer data member that points to the first node in the doubly linked list
    Node* tail; // Node pointer data member that points to the last node in the doubly linked list

public: // this identifier indicates that everything under it is public to the class
    DoublyLinkedList() { head = nullptr; tail = nullptr; } // constructor of the DoublyLinkedList class, initializes head and tail to nullptr indicating an empty list

    void insert_after(int value, int position) { // member method to insert a new node with the given value after the specified position, takes integer value and position as parameters
        if (position < 0) { // checks if the position is negative
            cout << "Position must be >= 0." << endl; // outputs an error message if the position is negative
            return; // exits the method early
        }

        Node* newNode = new Node(value); // creates a new node with the int value and assigns it to node pointer newNode
        if (!head) { // checks if the list is empty by checking if head is nullptr
            head = tail = newNode; // if the list is empty, sets both head and tail to the new node as it is the only node in the list
            return; // exits the method early
        }

        Node* temp = head; // creates a temporary node pointer temp and initializes it to head to start traversing the list
        for (int i = 0; i < position && temp; ++i) // loops from 0 to position, moving temp to the next node each iteration
            temp = temp->next; // advances temp to the next node in the list by setting it to temp's next pointer

        if (!temp) { // checks if temp is nullptr after the loop, indicating the position went out of bounds of the list
            cout << "Position exceeds list size. Node not inserted.\n"; // outputs an error message if the position exceeds the list size
            delete newNode; // deletes the 
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}