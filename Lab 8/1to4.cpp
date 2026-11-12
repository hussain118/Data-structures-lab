
#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int value)
{
    Node* n = new Node;

    n->data = value;
    n->left = NULL;
    n->right = NULL;

    return n;
}

Node* insert(Node* root, int value, int depth, bool report)
{
    if (root == NULL)
    {
        if (report)
            cout << value << " inserted at depth "
                 << depth << endl;

        return createNode(value);
    }

    if (value < root->data)
        root->left = insert(root->left, value, depth + 1, report);

    else if (value > root->data)
        root->right = insert(root->right, value, depth + 1, report);

    return root;
}

// Search whether value exists
bool search(Node* root, int value)
{
    while (root != NULL)
    {
        if (root->data == value)
            return true;

        if (value < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return false;
}

// Lowest Common Ancestor
Node* LCA(Node* root, int a, int b)
{
    while (root != NULL)
    {
        if (a < root->data && b < root->data)
            root = root->left;

        else if (a > root->data && b > root->data)
            root = root->right;

        else
            return root;
    }

    return NULL;
}

// Find smallest value in right subtree
Node* findMin(Node* root)
{
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Remove smallest node from subtree
Node* removeMin(Node* root)
{
    if (root->left == NULL)
    {
        Node* temp = root->right;
        delete root;
        return temp;
    }

    root->left = removeMin(root->left);

    return root;
}

// Deletion counters
int noChild = 0;
int oneChild = 0;
int twoChildren = 0;

// Delete using successor
Node* deleteNode(Node* root, int value, int depth)
{
    if (root == NULL)
        return NULL;

    if (value < root->data)
    {
        root->left = deleteNode(root->left, value, depth + 1);
    }
    else if (value > root->data)
    {
        root->right = deleteNode(root->right, value, depth + 1);
    }
    else
    {
        cout << value << " depth " << depth << ", ";

        // No child
        if (root->left == NULL && root->right == NULL)
        {
            cout << "no child" << endl;
            noChild++;

            delete root;
            return NULL;
        }

        // One child
        else if (root->left == NULL || root->right == NULL)
        {
            cout << "one child" << endl;
            oneChild++;

            Node* temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            delete root;
            return temp;
        }

        // Two children
        else
        {
            Node* successor = findMin(root->right);

            cout << "two children, replaced by "
                 << successor->data << endl;

            twoChildren++;

            root->data = successor->data;

            root->right = removeMin(root->right);
        }
    }

    return root;
}

// KTH largest
void kthLargest(Node* root, int& k, int& answer)
{
    if (root == NULL)
        return;

    // Right first
    kthLargest(root->right, k, answer);

    k--;

    if (k == 0)
    {
        answer = root->data;
        return;
    }

    // Then left
    kthLargest(root->left, k, answer);
}

void preorder(Node* root)
{
    if (root == NULL)
        return;

    cout << root->data << " ";

    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);

    cout << root->data << " ";
}

int height(Node* root)
{
    if (root == NULL)
        return -1;

    int l = height(root->left);
    int r = height(root->right);

    if (l > r)
        return l + 1;

    return r + 1;
}

int countNodes(Node* root)
{
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left)
             + countNodes(root->right);
}

int main()
{
    Node* root = NULL;

    int initial[] =
    {
        50, 25, 75, 10, 35, 60,
        90, 5, 30, 40, 55, 65
    };

    for (int i = 0; i < 12; i++)
        root = insert(root, initial[i], 0, false);

    // LCA 30 40
    cout << "LCA 30 40 = ";

    if (search(root, 30) && search(root, 40))
        cout << LCA(root, 30, 40)->data << endl;
    else
        cout << "LCA not possible" << endl;

    // LCA 5 40
    cout << "LCA 5 40 = ";

    if (search(root, 5) && search(root, 40))
        cout << LCA(root, 5, 40)->data << endl;
    else
        cout << "LCA not possible" << endl;

    // LCA 55 90
    cout << "LCA 55 90 = ";

    if (search(root, 55) && search(root, 90))
        cout << LCA(root, 55, 90)->data << endl;
    else
        cout << "LCA not possible" << endl;

    // LCA 30 99
    cout << "LCA 30 99: ";

    if (search(root, 30) && search(root, 99))
        cout << LCA(root, 30, 99)->data << endl;
    else
        cout << "LCA not possible" << endl;

    // INS 62
    root = insert(root, 62, 0, true);

    // DEL 75
    root = deleteNode(root, 75, 0);

    // KTH 3
    int k = 3;
    int answer = -1;

    kthLargest(root, k, answer);

    cout << "KTH 3 = " << answer << endl;

    // DEL 25
    root = deleteNode(root, 25, 0);

    // KTH 8
    k = 8;
    answer = -1;

    kthLargest(root, k, answer);

    cout << "KTH 8 = " << answer << endl;

    // DEL 5
    root = deleteNode(root, 5, 0);

    // DEL 35
    root = deleteNode(root, 35, 0);

    cout << "\nPostorder: ";
    postorder(root);

    cout << "\nHeight " << height(root);

    cout << "\nNodes " << countNodes(root);

    cout << "\nDeletion kinds: no child " << noChild
         << ", one child " << oneChild
         << ", two children " << twoChildren << endl;

    return 0;
}
