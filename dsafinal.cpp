#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// ----------------------- Custom Queue -----------------------
class Queue {
private:
    struct Node {
        string data;
        Node* next;
        Node(string val) : data(val), next(nullptr) {}
    };
    Node* front;
    Node* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!empty()) pop();
    }

    void push(string val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void pop() {
        if (!front) return;
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    string peek() {
        return front ? front->data : "";
    }

    bool empty() {
        return front == nullptr;
    }
};

// ----------------------- Custom Stack -----------------------
class Stack {
private:
    struct Node {
        string data;
        Node* next;
        Node(string val) : data(val), next(nullptr) {}
    };
    Node* top;
public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!empty()) pop();
    }

    void push(string val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) return;
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    string peek() {
        return top ? top->data : "";
    }

    bool empty() {
        return top == nullptr;
    }

    // Copy constructor for deep copy
    Stack(const Stack& other) : top(nullptr) {
        if (!other.top) return;
        Node* temp = other.top;
        Node* prev = nullptr;
        while (temp) {
            Node* newNode = new Node(temp->data);
            if (!top) {
                top = newNode;
            }
            else {
                prev->next = newNode;
            }
            prev = newNode;
            temp = temp->next;
        }
    }
};

// ----------------------- Custom Linked List -----------------------
class LinkedList {
public:
    struct Node {
        string name;
        string id;
        Node* next;
        Node* prev;
        Node(string n, string i) : name(n), id(i), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(string name, string id) {
        Node* newNode = new Node(name, id);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }

    void display() {
        Node* temp = head;
        while (temp) {
            cout << "Name: " << temp->name << ", Member ID: " << temp->id << endl;
            temp = temp->next;
        }
    }
};

// ----------------------- Book Class -----------------------
class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isAvailable;
    Book(string t, string a, string i) : title(t), author(a), ISBN(i), isAvailable(true) {}
    void display() {
        cout << "Title: " << title << ", Author: " << author << ", ISBN: " << ISBN << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// ----------------------- Node for BST -----------------------
class TreeNode {
public:
    Book* book;
    TreeNode* left;
    TreeNode* right;
    TreeNode(Book* b) : book(b), left(nullptr), right(nullptr) {}
};

// ----------------------- BST for Book Catalog -----------------------
class BST {
public:
    TreeNode* root;
    BST() : root(nullptr) {}

    TreeNode* insert(TreeNode* node, Book* book) {
        if (!node) return new TreeNode(book);
        if (book->title < node->book->title)
            node->left = insert(node->left, book);
        else
            node->right = insert(node->right, book);
        return node;
    }

    void insert(Book* book) {
        root = insert(root, book);
    }

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        node->book->display();
        inorder(node->right);
    }

    void displayAll() {
        inorder(root);
    }

    Book* search(TreeNode* node, string title) {
        if (!node) return nullptr;
        if (node->book->title == title) return node->book;
        if (title < node->book->title)
            return search(node->left, title);
        else
            return search(node->right, title);
    }

    Book* search(string title) {
        return search(root, title);
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    // Remove function to delete a node from the BST
    TreeNode* remove(TreeNode* root, string title) {
        if (!root) return root;

        // Search for the node to be deleted
        if (title < root->book->title) {
            root->left = remove(root->left, title);
        }
        else if (title > root->book->title) {
            root->right = remove(root->right, title);
        }
        else {
            // Node to be deleted is found

            // Case 1: Node has no children (leaf node)
            if (!root->left && !root->right) {
                delete root;
                return nullptr;
            }
            // Case 2: Node has one child
            else if (!root->left) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: Node has two children
            else {
                // Find the in-order successor (smallest in the right subtree)
                TreeNode* temp = minValueNode(root->right);
                root->book = temp->book;  // Copy the in-order successor's content to the current node
                root->right = remove(root->right, temp->book->title);  // Delete the in-order successor
            }
        }
        return root;
    }

    // Public remove function
    void remove(string title) {
        root = remove(root, title);
    }
};

// Maximum number of books the graph can store
const int MAX_BOOKS = 100;

class Graph {
private:
    string books[MAX_BOOKS];  // Array to store book titles
    bool adjMatrix[MAX_BOOKS][MAX_BOOKS];  // Adjacency matrix
    int bookCount;  // Current number of books in the graph

    // Helper function to find the index of a book by its title
    int findBookIndex(const string& title) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i] == title) return i;
        }
        return -1;  // Book not found
    }

public:
    Graph() : bookCount(0) {
        // Initialize the adjacency matrix to false
        for (int i = 0; i < MAX_BOOKS; i++) {
            for (int j = 0; j < MAX_BOOKS; j++) {
                adjMatrix[i][j] = false;
            }
        }
    }

    // Add a book to the graph
    void addBook(const string& title) {
        if (bookCount >= MAX_BOOKS) {
            cout << "Graph is full. Cannot add more books." << endl;
            return;
        }
        if (findBookIndex(title) != -1) {
            cout << "Book already exists in the graph." << endl;
            return;
        }
        books[bookCount++] = title;
    }

    // Add a relationship (edge) between two books
    void addRelationship(const string& book1, const string& book2) {
        int index1 = findBookIndex(book1);
        int index2 = findBookIndex(book2);

        if (index1 == -1 || index2 == -1) {
            cout << "One or both books not found in the graph." << endl;
            return;
        }

        adjMatrix[index1][index2] = true;
        adjMatrix[index2][index1] = true;  // For undirected graph
    }

    // Display recommendations for a given book (BFS approach)
    void recommendBooks(const string& title) {
        int index = findBookIndex(title);
        if (index == -1) {
            cout << "Book not found in the graph." << endl;
            return;
        }

        cout << "Recommendations for \"" << title << "\":" << endl;
        for (int i = 0; i < bookCount; i++) {
            if (adjMatrix[index][i]) {
                cout << "- " << books[i] << endl;
            }
        }
    }

    // Display the adjacency matrix
    void displayGraph() {
        cout << "\n--- Adjacency Matrix ---" << endl;
        cout << "   ";
        for (int i = 0; i < bookCount; i++) {
            cout << books[i] << "\t";
        }
        cout << endl;

        for (int i = 0; i < bookCount; i++) {
            cout << books[i] << "\t";
            for (int j = 0; j < bookCount; j++) {
                cout << adjMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }
};

// ----------------------- Library Class -----------------------
class Library {
private:
    BST catalog;
    LinkedList members;
    Queue borrowRequests;
    Stack transactionHistory;
    Graph bookGraph;

public:
    // Load books from file
    void loadBooksFromFile(const string& filename) {
        ifstream file(filename);
        if (file) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string title, author, ISBN;
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, ISBN, ',');
                Book* book = new Book(title, author, ISBN);
                catalog.insert(book);  // Insert into catalog
                bookGraph.addBook(title);  // Add to the graph
            }
            file.close();
        }
    }


    // Save books to file
    void saveBooksToFile(const string& filename) {
        ofstream file(filename);
        if (file) {
            saveBooksToFileHelper(catalog.root, file);
            file.close();
        }
    }

    // Recursive function to save books to file
    void saveBooksToFileHelper(TreeNode* node, ofstream& file) {
        if (node) {
            file << node->book->title << "," << node->book->author << "," << node->book->ISBN << endl;
            saveBooksToFileHelper(node->left, file);
            saveBooksToFileHelper(node->right, file);
        }
    }

    // Load members from file
    void loadMembersFromFile(const string& filename) {
        ifstream file(filename);
        if (file) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string name, id;
                getline(ss, name, ',');
                getline(ss, id, ',');
                members.add(name, id);
            }
            file.close();
        }
    }

    // Save members to file
    void saveMembersToFile(const string& filename) {
        ofstream file(filename);
        if (file) {
            LinkedList::Node* temp = members.head;
            while (temp) {
                file << temp->name << "," << temp->id << endl;
                temp = temp->next;
            }
            file.close();
        }
    }

    // Remove a book
    void removeBook(string title) {
        Book* book = catalog.search(title);
        if (book) {
            catalog.remove(title);
            saveBooksToFile("books.txt");
            cout << "Book removed: " << title << endl;
            transactionHistory.push("Removed book: " + title);
        }
        else {
            cout << "Book not found!" << endl;
        }
    }

    // Display all books
    void displayBooks() {
        cout << "eN";
        catalog.displayAll();
    }

    // Add a new member
    void addMember(string name, string memberId) {
        members.add(name, memberId);
        saveMembersToFile("members.txt");
        transactionHistory.push("Added member: " + name);
    }

    // Remove a member
    void removeMember(string memberId) {

        LinkedList::Node* temp = members.head;
        LinkedList::Node* prev = nullptr;

        while (temp) {
            if (temp->id == memberId) {
                if (prev) prev->next = temp->next;
                else members.head = temp->next;
                delete temp;
                saveMembersToFile("members.txt");
                cout << "Member removed: " << memberId << endl;
                transactionHistory.push("Removed member: " + memberId);
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Member not found!" << endl;
    }

    // Display all members
    void displayMembers() {
        members.display();
    }

    // Borrow a book
    void borrowBook(string title) {
        Book* book = catalog.search(title);
        if (book && book->isAvailable) {
            book->isAvailable = false;
            saveBooksToFile("books.txt");
            cout << "Book borrowed: " << title << endl;
            transactionHistory.push("Borrowed book: " + title);
        }
        else {
            cout << "Book not available, added to waiting list." << endl;
            borrowRequests.push(title);
        }
    }

    // Return a book
    void returnBook(string title) {
        Book* book = catalog.search(title);
        if (book) {
            book->isAvailable = true;
            saveBooksToFile("books.txt");
            cout << "Book returned: " << title << endl;
            transactionHistory.push("Returned book: " + title);
        }
        else {
            cout << "Book not found!" << endl;
        }
    }

    // Display transaction history
    void displayHistory() {
        Stack temp = transactionHistory;
        while (!temp.empty()) {
            cout << temp.peek() << endl;
            temp.pop();
        }
    }
    // Add a book to the system and the graph
    void addBook(string title, string author, string ISBN) {
        Book* newBook = new Book(title, author, ISBN);
        catalog.insert(newBook);  // Insert into catalog (BST)
        bookGraph.addBook(title);  // Add to the book graph
        cout << "Book added: " << title << endl;
    }

    // Add a relationship between two books
    void addBookRelationship(string book1, string book2) {
        bookGraph.addRelationship(book1, book2);
    }

    // Recommend books
    void recommendBooks(string title) {
        bookGraph.recommendBooks(title);
    }

    // Display the graph
    void displayGraph() {
        bookGraph.displayGraph();
    }
};
// ----------------------- Main Function -----------------------
int main() {
    Library library;

    // Load data from files
    library.loadBooksFromFile("books.txt");
    library.loadMembersFromFile("members.txt");

    int choice;
    string title, author, ISBN, memberId, name;

    while (true) {
        cout << "\n--- KSK Library Management System ---\n";
        cout << "1. Admin\n2. Member\n3. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string username;
            int password;
            cout << "Username: " << endl;
            cin >> username;
            cout << "Password: " << endl;
            cin >> password;
            if (username == "Irtazafarooq" && password == 7788 || username == "Hamza" && password == 1122)
            {
                int adminChoice;
                do {
                    cout << "\n--- Admin Menu ---\n";
                    cout << "1. Display Books\n2. Add Book\n3. Remove Book\n4. Display Members\n5. Add Member\n6. Remove Member\n7. Display History\n8. Add RelationShip btw Book\n9. Display Graph\n10. Back to Main Menu\nEnter choice: ";
                    cin >> adminChoice;
                    cin.ignore();

                    switch (adminChoice) {

                    case 1: library.displayBooks(); break;
                    case 2:
                        cout << "Enter title: "; getline(cin, title);
                        cout << "Enter author: "; getline(cin, author);
                        cout << "Enter ISBN: "; getline(cin, ISBN);
                        library.addBook(title, author, ISBN);
                        break;
                    case 3:
                        cout << "Enter title to remove: "; getline(cin, title);
                        library.removeBook(title);
                        break;
                    case 4: library.displayMembers(); break;
                    case 5:
                        cout << "Enter member name: "; getline(cin, name);
                        cout << "Enter member ID: "; getline(cin, memberId);
                        library.addMember(name, memberId);
                        break;
                    case 6:
                        cout << "Enter member ID to remove: "; getline(cin, memberId);
                        library.removeMember(memberId);
                        break;
                    case 7: library.displayHistory(); break;
                    case 8:
                        cout << "Enter the title of the first book: ";
                        getline(cin, title);
                        cout << "Enter the title of the related book: ";
                        getline(cin, author);  // Using `author` as the second book title variable
                        library.addBookRelationship(title, author);
                        break;
                    case 9:
                        library.displayGraph();
                        break;
                    }
                } while (adminChoice != 10);
            }
            else
            {
                cout << "Wrong Password";
            }
        }

        else if (choice == 2) {
            string username;
            int password;
            cout << "Username: " << endl;
            cin >> username;
            cout << "Password: " << endl;
            cin >> password;
            if (username == "Irtaza" && password == 7788 || username == "Hamza" && password == 1122)
            {
                int memberChoice;
                do {
                    cout << "\n--- Member Menu ---\n";
                    cout << "1. Display Books\n2. Borrow Book\n3. Return Book\n4. Recommended books\n5. Back to Main Menu\nEnter choice: ";
                    cin >> memberChoice;
                    cin.ignore();

                    switch (memberChoice) {
                    case 1: library.displayBooks(); break;
                    case 2:
                        cout << "Enter title to borrow: "; getline(cin, title);
                        library.borrowBook(title);
                        break;
                    case 3:
                        cout << "Enter title to return: "; getline(cin, title);
                        library.returnBook(title);
                        break;
                    case 4:
                        library.displayGraph();
                    }

                } while (memberChoice != 5);
            }
            else
            {
                cout << "Wrong password";
            }
        }
        else if (choice == 3)
        {
            break;
        }
    }
    return 0;
}
   
