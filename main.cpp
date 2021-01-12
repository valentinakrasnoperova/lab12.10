#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef int Info;
static bool flag = false;

struct Node {
    Node *left,
            *right;
    Info info;
};

Node *CreateTree(int nodeCount);

Node *addNode(Node *root, int value);

void PrintTree(Node *root, int level);


int searchNode(Node *temp, int value){
    if(temp == NULL){
        printf("Tree is empty\n");
    }
    else{
        if(temp->info == value){
            flag = true;
            return flag;
        }
        if(flag == false && temp->left != NULL){
            searchNode(temp->left, value);
        }
        if(flag == false && temp->right != NULL){
            searchNode(temp->right, value);
        }
    }
}

void deletDeepest(struct Node* root, struct Node* d_node) {
    queue<struct Node*> q;
    q.push(root);

    struct Node* temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp == d_node) {
            temp = NULL;
            delete (d_node);
            return;
        }
        if (temp->right) {
            if (temp->right == d_node) {
                temp->right = NULL;
                delete (d_node);
                return;
            }
            else
                q.push(temp->right);
        }

        if (temp->left) {
            if (temp->left == d_node) {
                temp->left = NULL;
                delete (d_node);
                return;
            }
            else
                q.push(temp->left);
        }
    }
}

Node* deletion(Node* root, int key)
{
    if (root == NULL)
        return NULL;

    if (root->left == NULL && root->right == NULL) {
        if (root->info == key)
            return NULL;
        else
            return root;
    }

    queue<struct Node*> q;
    q.push(root);

    struct Node* temp;
    struct Node* key_node = NULL;

    while (!q.empty()) {
        temp = q.front();
        q.pop();

        if (temp->info == key)
            key_node = temp;

        if (temp->left)
            q.push(temp->left);

        if (temp->right)
            q.push(temp->right);
    }

    if (key_node != NULL) {
        int x = temp->info;
        deletDeepest(root, temp);
        key_node->info = x;
    }
    return root;
}

int maxDepth(Node* root)
{
    if (root == NULL)
        return 0;

    // Create an empty queue for level order tarversal
    queue<Node *> q;

    // Enqueue Root and initialize height
    q.push(root);
    int height = 0;

    while (1)
    {
        // nodeCount (queue size) indicates number of nodes
        // at current lelvel.
        int nodeCount = q.size();
        if (nodeCount == 0)
            return height;

        height++;

        // Dequeue all nodes of current level and Enqueue all
        // nodes of next level
        while (nodeCount > 0)
        {
            Node *node = q.front();
            q.pop();
            if (node->left != NULL) {
                cout << node->info << " ";
                q.push(node->left);
            }
            if (node->right != NULL)  {
                cout << node->info << " ";

                q.push(node->right);
            }
            nodeCount--;
        }
    }
}


int main() {
    int menu;
    Node* root;
    int N;

    while(true) {
        cout << "1: Створити бінарне дерево" << endl;
        cout << "2: Вивести бінарне дерево" << endl;
        cout << "3: Додати елемент" << endl;
        cout << "4: Пошук елемента:" << endl;
        cout << "5: Видалення елемента:" << endl;
        cout << "6: Максимальна глибина дерева:" << endl;
        cout << "Виберіть пункт меню:" << endl;
        cin >> menu;
        cout << endl;
        switch (menu) {
            case 1:
                cout << "Enter nodes count: ";
                cin >> N;
                root = CreateTree(N);
                break;
            case 2:
                PrintTree(root, 0);
                break;
            case 3:
                cout << "Введіть значення нового елемента:" << endl;
                int value;
                cin >> value;
                root = addNode(root, value);
                break;
            case 4:
                cout << "Введіть значення елемента який шукаєте:" << endl;
                int search;
                cin >> search;
                flag = false;
                bool searched;
                searched = searchNode(root, search);
                if (searched) {
                    cout << "Елемент знайдено!" << endl;
                } else {
                    cout << "Елемент не знайдено" << endl;
                }
                break;
            case 5:
                cout << "Введіть значення  елемента:" << endl;
                int key;
                cin >> key;
                root = deletion(root, key);
                break;
            case 6:
                int maxDep;
                maxDep = maxDepth(root);
                cout << "Максимальна глибина: " << maxDep;
                break;
        }
    }

    return 0;
}

Node *CreateTree(int nodeCount) {
    if (nodeCount == 0)
        return NULL;
    else {
        Node *newNode = new Node;
        cout << " Enter node value: ";
        cin >> newNode->info;
        int leftCount = nodeCount / 2;
        int rightCount = nodeCount - leftCount - 1;
        newNode->left = CreateTree(leftCount);
        newNode->right = CreateTree(rightCount);
        return newNode;
    }
}

Node *addNode(Node *root, Info value) {
    if (!root) {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    if (value < root->info) root->left = addNode(root->left, value);
    else if (value > root->info) root->right = addNode(root->right, value);

    return root;
}

void PrintTree(Node *root, int level) {

    if (root != NULL) {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <=level; i++)
            cout << " ";
        cout << root->info <<endl;
        PrintTree(root->left, level + 1);
    }
}