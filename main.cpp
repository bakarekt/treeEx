#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Định nghĩa Node
struct Node {
    string value; // Giá trị tại node (toán hạng hoặc toán tử)
    Node* left;   // Con trái
    Node* right;  // Con phải

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Lớp biểu diễn cây biểu thức
class ExpressionTree {
private:
    Node* root;

    // Duyệt trung tố (Infix)
    void duyetInfix(Node* node) {
        if (node == nullptr) return;
        if (!isOperator(node->value)) cout << node->value << " ";
        else {
            cout << "( ";
            duyetInfix(node->left);
            cout << node->value << " ";
            duyetInfix(node->right);
            cout << ") ";
        }
    }

    // Duyệt tiền tố (Prefix)
    void duyetPrefix(Node* node) {
        if (node == nullptr) return;
        cout << node->value << " ";
        duyetPrefix(node->left);
        duyetPrefix(node->right);
    }

    // Duyệt hậu tố (Postfix)
    void duyetPostfix(Node* node) {
        if (node == nullptr) return;
        duyetPostfix(node->left);
        duyetPostfix(node->right);
        cout << node->value << " ";
    }

    // Kiểm tra toán tử
    bool isOperator(const string& value) {
        return value == "+" || value == "-" || value == "*" || value == "/" || value == "^";
    }

public:
    // Hàm khởi tạo
    ExpressionTree() : root(nullptr) {}

    //Kiểm tra rỗng
    bool isEmpty() {
        return root == nullptr;
    }

    Node* getRoot() {
        return root;
    }

    void insertRoot(const string& value, Node* left = nullptr, Node* right = nullptr) {
        root = new Node(value);
        root->left = left;
        root->right = right;
    }

    void insertNode(Node* parent, const string& value, bool leftChild) {
        if (leftChild && parent->left == nullptr) {
            parent->left = new Node(value);
        } else if (!leftChild && parent->right == nullptr) {
            parent->right = new Node(value);
        } else {
            cout << "Node đã có con tại vị trí này!" << endl;
        }
    }

    void printInfix() {
        duyetInfix(root);
        cout << endl;
    }

    void printPrefix() {
        duyetPrefix(root);
        cout << endl;
    }

    void printPostfix() {
        duyetPostfix(root);
        cout << endl;
    }
};

int main() {
    ExpressionTree tree;

    // Xây dựng cây biểu thức
    Node* a = new Node("a");
    Node* b = new Node("b");
    Node* c = new Node("c");
    Node* d = new Node("d");
    Node* h = new Node("h");
    Node* f = new Node("f");
    Node* e = new Node("e");

    Node* five = new Node("5");
    Node* six = new Node("6");
    Node* oneHalf = new Node("1/2");

    Node* c6 = new Node("^");
    c6->left = c;
    c6->right = six;

    Node* bc6 = new Node("*");
    bc6->left = b;
    bc6->right = c6;

    Node* div = new Node("/");
    div->left = bc6;
    div->right = d;

    Node* a5 = new Node("*");
    a5->left = a;
    a5->right = five;

    Node* leftSubtree = new Node("-");
    leftSubtree->left = a5;
    leftSubtree->right = div;

    Node* hf = new Node("-");
    hf->left = h;
    hf->right = f;

    Node* eHalf = new Node("^");
    eHalf->left = e;
    eHalf->right = oneHalf;

    Node* rightSubtree = new Node("*");
    rightSubtree->left = hf;
    rightSubtree->right = eHalf;

    tree.insertRoot("+", leftSubtree, rightSubtree);

    // In kết quả
    cout << "Trung tố (Infix): ";
    tree.printInfix();

    cout << "Tiền tố (Prefix): ";
    tree.printPrefix();

    cout << "Hậu tố (Postfix): ";
    tree.printPostfix();

    return 0;
}
