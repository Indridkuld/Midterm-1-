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
            delete newNode; // deletes the newNode object and releases its memory to prevent memory leaks
            return; // exits the method early
        }

        newNode->next = temp->next; // sets the new node's next pointer to temp's next pointer, linking the new node to the node after temp
        newNode->prev = temp; // sets the new node's prev pointer to temp, linking the new node back to temp
        if (temp->next) // checks if temp's next pointer is not nullptr, meaning temp is not the last node
            temp->next->prev = newNode; // updates the next node's prev pointer to point back to the new node
        else // if temp's next pointer is nullptr, meaning temp is the last node
            tail = newNode; // updates the tail pointer of the list to point to the new node as it is now the last node
        temp->next = newNode; // sets temp's next pointer to the new node, linking temp to the new node
    } 

    void delete_val(int value) {  // member method to delete the node with the specified value, takes integer value as parameter
        if (!head) return; // checks if the list is empty by checking if head is nullptr, exits early if it is

        Node* temp = head; // creates a temporary node pointer temp and initializes it to head to start traversing the list
        
        while (temp && temp->data != value) // loops through the list until temp is nullptr or temp's data matches the specified value
            temp = temp->next; // advances temp to the next node in the list by setting it to temp's next pointer

        if (!temp) return; // checks if temp is nullptr after the loop, indicating the value was not found in the list, exits early if it is

        if (temp->prev) // checks if temp's prev pointer is not nullptr, meaning temp is not the first node
            temp->prev->next = temp->next; // if it is not the first node, updates the previous node's next pointer to skip temp and point to temp's next node
        else // if temp's prev pointer is nullptr, meaning temp is the first node
            head = temp->next; // sets the head pointer of the list to temp's next node, effectively removing temp from the front of the list

        if (temp->next) // checks if temp's next pointer is not nullptr, meaning temp is not the last node
            temp->next->prev = temp->prev; // if it is not the last node, updates the next node's prev pointer to skip temp and point to temp's previous node
        else // if temp's next pointer is nullptr, meaning temp is the last node
            tail = temp->prev; // sets the tail pointer of the list to temp's previous node, effectively removing temp from the end of the list

        delete temp; // deletes the temp object and releases its memory to prevent memory leaks
    }

    void delete_pos(int pos) { // member method to delete the node at the specified position, takes integer position as parameter
        if (!head) { // checks if the list is empty by checking if the head pointer is nullptr
            cout << "List is empty." << endl; // outputs an error message if the list is empty
            return; // exits the method early
        }
    
        if (pos == 1) { // checks if the specified position is 1, indicating the first node
            pop_front(); // calls the pop_front method to remove the first node from the list
            return; // exits the method early
        }
    
        Node* temp = head; // creates a temporary node pointer temp and initializes it to head to start traversing the list
    
        for (int i = 1; i < pos; i++){ // loops from 1 to pos-1, moving temp to the next node each iteration
            if (!temp) { // checks if temp is nullptr during the loop, indicating the position went out of bounds of the listj
                cout << "Position doesn't exist." << endl; // outputs an error message if the position doesn't exist
                return; // exits the method early
            }
            else // if temp is not nullptr
                temp = temp->next; // sets temp to temp's next pointer, moving to the next node in the list
        }
        if (!temp) { // checks if temp is nullptr after the loop, in other words the position went out of bounds of the list
            cout << "Position doesn't exist." << endl; // outputs an error message if the position doesn't exist
            return; // exits the method early
        }
    
        if (!temp->next) { // checks if temp's next pointer is nullptr, indicating temp is the last node
            pop_back(); // calls the pop_back method to remove the last node from the list
            return; // exits the method early
        }
        // the below code handles the case where temp is neither the first nor the last node, and fixes the pointers to remove temp from the list
        Node* tempPrev = temp->prev; // creates a new node pointer tempPrev and initializes it to temp's prev pointer, pointing to the node before temp
        tempPrev->next = temp->next; // sets tempPrev's next pointer to temp's next pointer, effectively skipping over temp in the list
        temp->next->prev = tempPrev;  // sets temp's next node's prev pointer to tempPrev, skipping over temp in the list
        delete temp; // deletes the temp object and releases its memory to prevent memory leaks
    }

    void push_back(int v) { // member method to add a new node with the specified value to the end of the list, takes integer value 'v' as parameter
        Node* newNode = new Node(v); // creates a new node with the 'v' value and assigns it to node pointer newNode
        if (!tail) // checks if the list is empty by checking if tail is nullptr
            head = tail = newNode; // if the list is empty, sets both head and tail to the new node as it is the only node in the list
        else { // if the list is not empty
            tail->next = newNode; // sets the current tail's next pointer to the new node, linking the last node to the new node
            newNode->prev = tail; // sets the new node's prev pointer to the current tail, linking the new node back to the last node
            tail = newNode; // sets the tail pointer of the list to the new node, making it the new last node in the list
        }
    }
    
    void push_front(int v) { // member method to add a new node with the specified value to the front of the list, takes integer value 'v' as parameter
        Node* newNode = new Node(v); // creates a new node with the 'v' value and assigns it to node pointer newNode
        if (!head) // checks if the list is empty by checking if head is nullptr
            head = tail = newNode; // if the list is empty, sets both head and tail to the new node as it is the only node in the list
        else { // if the list is not empty
            newNode->next = head; // sets the new node's next pointer to the current head, linking the new node to the first node
            head->prev = newNode; // sets the current head's prev pointer to the new node, linking the first node back to the new node
            head = newNode; // sets the head pointer of the list to the new node, making it the new first node in the list
        }
    }
    
    void pop_front() { // member method to remove the first node from the list, does not take any parameters

        if (!head) { // checks if the list is empty by checking if head is nullptr
            cout << "List is empty." << endl; // outputs an error message if the list is empty
            return; // exits the method early
        }

        Node * temp = head; // creates a temporary node pointer temp and initializes it to head to keep track of the node to be deleted

        if (head->next) { // checks if head's next pointer is not nullptr, meaning there is more than one node in the list
            head = head->next; // if there is more than one node, updates head to point to the second node in the list
            head->prev = nullptr; // sets the new head's prev pointer to nullptr, as it is now the first node in the list
        }
        else // if head's next pointer is nullptr, meaning there is only one node in the list
            head = tail = nullptr; // sets both head and tail to nullptr, indicating the list is now empty
        delete temp; // deletes the temp object and releases its memory to prevent memory leaks
    }

    void pop_back() { // member method to remove the last node from the list, does not take any parameters
        if (!tail) { // checks if the list is empty by checking if tail is nullptr
            cout << "List is empty." << endl; // outputs an error message if the list is empty
            return; // exits the method early
        }
        Node * temp = tail; // creates a temporary node pointer temp and initializes it to tail to keep track of the node to be deleted

        if (tail->prev) { // checks if tail's prev pointer is not nullptr, checking if there is more than one node in the list
            tail = tail->prev; // if there is more than one node, updates tail to point to the second-to-last node in the list
            tail->next = nullptr; // sets the new tail's next pointer to nullptr, as it is now the last node in the list
        }
        else // if tail's prev pointer is nullptr, there is only one node in the list
            head = tail = nullptr;  // sets both head and tail to nullptr, indicating the list is now empty
        delete temp; // deletes the temp object and releases its memory to prevent memory leaks
    }

    void every_other_element() {} // temp 
 
    ~DoublyLinkedList() { // destructor of the DoublyLinkedList class, called when an object of the class is destroyed at the end of its scope
        while (head) { // loops while head is not nullptr, ie. there are still nodes in the list
            Node* temp = head; // creates a temporary node pointer temp and initializes it to head to keep track of the node to be deleted
            head = head->next; // updates head to point to the next node in the list
            delete temp; // deletes the temp object and releases its memory to prevent memory leaks
        }
    }
    void print() { // print method to display the elements of the list from head to tail
        Node* current = head; // creates a temporary node pointer current and initializes it to head to start traversing the list
        if (!current) { // checks if current is nullptr, indicating the list is empty
            cout << "List is empty." << endl; // message indicating the list is empty
            return; // exits the method early
        }
        while (current) { // loops through the list while current is not nullptr
            cout << current->data << " "; // outputs the data of the current node followed by a space
            current = current->next; // advances current to the next node in the list by setting it to current's next pointer
        }
        cout << endl; // outputs a newline character after printing all elements
    }

    void print_reverse() { // print method to display the elements of the list from tail to head, reversed 
        Node* current = tail; // creates a temporary node pointer current and initializes it to tail to start traversing the list in reverse
        if (!current) {  // checks if current is nullptr, indicating the list is empty
            cout << "List is empty." << endl; // message that the list is empty
            return; // exits the method early
        }
        while (current) { // loops through the list while current is not nullptr
            cout << current->data << " "; // outputs the data of the current node followed by a space
            current = current->prev; // moves current to the previous node in the list by setting it to current's prev pointer
        }
        cout << endl; // outputs a newline character after printing all elements
    }
};

int main() { // main function, drives the program execution
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0; // indicates successful program termination
}