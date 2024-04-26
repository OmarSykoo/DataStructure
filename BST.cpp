#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class T>
class BST {
  private:
    struct Node {
        T value;
        Node *left;
        Node *right;
        Node(T value = 0, Node *left = nullptr, Node *right = nullptr) : value(value), left(left), right(right) {}
    };
    Node *root = nullptr;
    int size = 0;

    Node *remove(Node *root, T value) {
        if (root == nullptr)
            return root;
        if (root->value < value)
            root->right = remove(root->right, value);
        else if (root->value > value)
            root->left = remove(root->left, value);
        else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
                return root;
            } else if (root->left == nullptr && root->right) {
                Node *temp = root->right;
                delete root;
                return temp;
            } else if (root->left && root->right == nullptr) {
                Node *temp = root->left;
                delete root;
                return temp;
            } else {
                Node *temp = root->right;

                while (temp->left)
                    temp = temp->left;

                root->value = temp->value;
                root->right = remove(root->right, temp->value);
                return root;
            }
        }
    }

    void inOrder(Node *next, vector<T> &arr) {
        if (!next)
            return;
        inOrder(next->left, arr);
        arr.push_back(next->value);
        inOrder(next->right, arr);
    }

    void dfsLeft(Node *next, vector<T> &arr) {
        if (!next)
            return;
        arr.push_back(next->value);
        dfsLeft(next->left, arr);
        dfsLeft(next->right, arr);
    }

    void dfsRight(Node *next, vector<T> &arr) {
        if (!next)
            return;
        dfsRight(next->left, arr);
        dfsRight(next->right, arr);
        arr.push_back(next->value);
    }

    void bfs(Node *next, vector<T> &arr) {
        queue<Node *> qq;
        qq.push(next);
        while (!qq.empty()) {
            arr.push_back(qq.front()->value);
            if (qq.front()->left)
                qq.push(qq.front()->left);
            if (qq.front()->right)
                qq.push(qq.front()->right);
            qq.pop();
        }
    }

  public:
    bool search(T value) {
        Node *curr = root;
        while (curr != nullptr) {
            if (curr->value == value)
                return true;
            else if (curr->value < value && curr->right)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return false;
    }

    void push(T value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node *curr = root;

        while (true) {
            if (value == curr->value) {
                return;
            } else if (value > curr->value) {
                if (!curr->right)
                    break;
                else
                    curr = curr->right;
            } else {
                if (!curr->left)
                    break;
                else
                    curr = curr->left;
            }
        }

        if (value > curr->value)
            curr->right = new Node(value);
        else
            curr->left = new Node(value);
    }

    void remove(T value) {
        if (!search(value))
            return;
        root = remove(root, value);
    }

    vector<T> inOrder() {
        vector<T> ans;
        inOrder(root, ans);
        return ans;
    }

    vector<T> preOrder() {
        vector<T> ans;
        dfsLeft(root, ans);
        return ans;
    }

    vector<T> postOrder() {
        vector<T> ans;
        dfsRight(root, ans);
        return ans;
    }

    vector<T> BFS() {
        vector<T> ans;
        bfs(root, ans);
        return ans;
    }
};

int main() {
    BST<int> myTree;
    myTree.push(40);
    myTree.push(30);
    myTree.push(50);
    myTree.push(20);
    myTree.push(35);
    myTree.push(45);
    myTree.push(90);

    cout << "Orderd List\n";
    for (int i : myTree.inOrder())
        cout << i << ' ';
    cout << '\n';
    cout << '\n';

    cout << "PreOrder List\n";

    for (int i : myTree.preOrder())
        cout << i << ' ';
    cout << '\n';
    cout << '\n';

    cout << "PostOrder List\n";

    for (int i : myTree.inOrder())
        cout << i << ' ';
    cout << '\n';
    cout << '\n';

    cout << "breadth First Search List\n";

    for (int i : myTree.BFS())
        cout << i << ' ';
    cout << '\n';
    cout << '\n';

    myTree.remove(45);

    cout << "this is just a test\n";

    for (int i : myTree.preOrder())
        cout << i << ' ';
    cout << '\n';
}
