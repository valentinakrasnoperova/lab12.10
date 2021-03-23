#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
    Node* left,
            * right;
    int info;
};

void CreateBin(char* fname);
void ReadBin(char* fname, Node*& root);
void PrintTree(Node* root, int level);
void PrintTreeFound(Node* root, int level, int find);
Node* Insert(Node* p, int value);
Node* FindMin(Node* root);
Node* rightRotation(Node* r);
Node* leftRotation(Node* r);
int Height(Node* root);
int BFactor(Node* root);
Node* balanceHeight(Node* r);
Node* deleteMin(Node* p);
Node* Delete(Node* p, int value);

int main()
{

    char fname[61];
    int value, find;
    int ch;
    Node* root = NULL;
    do
    {
        cout << "Виберіть дію:" << endl << endl;
        cout << " [1] - Запис значень вузлів у бінарний файл" << endl;
        cout << " [2] - Зчитування значень з файлу та створення бінарного дерева " << endl;
        cout << " [3] - Виведення бінарного дерева:" << endl;
        cout << " [4] - Видалення з бінарного дерева вказаного вузла" << endl;
        cout << " [5] - Пошук вказаного вузла в бінарному дереві" << endl;
        cout << " [6] - Глибина дерева" << endl;
        cout << " [0] - завершення роботи програми" << endl << endl;
        cout << "Введіть значення: "; cin >> ch;
        cout << endl;
        switch (ch)
        {
            case 1:
                cin.get();
                cin.sync();
                cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
                CreateBin(fname);
                break;
            case 2:
                cin.get();
                cin.sync();
                cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
                ReadBin(fname, root);
                cout << "Бінарне дерево створено!" << endl;
                break;
            case 3:
                PrintTree(root, 0);
                cout << endl;
                break;
            case 4:
                cout << "Введіть вузол, що буде видалений: "; cin >> value;
                root = Delete(root, value);
                cout << endl;
                break;
            case 5:
                cout << "Введіть вузол для пошуку: "; cin >> find;
                PrintTreeFound(root, 0, find);
                break;
            case 6:
                cout << "Глибина дерева = " << Height(root) << endl;
                break;
            case 0:
                exit(1);
            default:
                cout << "Ви ввели помилкове значення! "
                        "Слід ввести число - номер вибраного пункту меню" << endl;
        }
    } while (ch != '0');

    return 0;
}

void CreateBin(char* fname)
{
    ofstream fout(fname, ios::binary);
    if (!fout)
    {
        cerr << "Помилка запису файлу '" << fname << "'" << endl;
        return;
    }
    int value, N;
    cout << "Введіть кількість вузлів бінарного дерева: "; cin >> N;
    for (int i = 0; i < N; i++)
    {
        cout << "Значення вузла: "; cin >> value;
        fout.write((char*)&value, sizeof(value));
    }
    cout << endl;
}

void ReadBin(char* fname, Node*& root)
{
    ifstream fin(fname, ios::binary);
    if (!fin)
    {
        cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
        return;
    }
    int value;
    while (fin.read((char*)&value, sizeof(value)))
    {
        root = Insert(root, value);
    }
}

void PrintTree(Node* root, int level)
{
    if (root != NULL)
    {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << "   ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

void PrintTreeFound(Node* root, int level, int find)
{
    if (root != NULL)
    {
        PrintTreeFound(root->right, level + 1, find);
        for (int i = 1; i <= level; i++)
            cout << "    ";
        if (root->info == find)
            cout << "(" << root->info << ")" << endl;
        else
            cout << root->info << endl;
        PrintTreeFound(root->left, level + 1, find);
    }
}

Node* FindMin(Node* root)
{
    if (root->left != NULL)
        return FindMin(root->left);
    else
        return root;
}

Node* rightRotation(Node* p)
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    return q;
}

Node* leftRotation(Node* q)
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    return p;
}
int Height(Node* root)
{
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root)
{
    return Height(root->right) - Height(root->left);
}

Node* balanceHeight(Node* p)
{
    if (BFactor(p) == 2)
    {
        if (BFactor(p->right) < 0)
            p->right = rightRotation(p->right);
        return leftRotation(p);
    }
    if (BFactor(p) == -2)
    {
        if (BFactor(p->left) > 0)
            p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    return p;
}

Node* Insert(Node* p, int value)
{
    if (!p)
    {
        p = new Node;
        p->info = value;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    if (value < p->info)
        p->left = Insert(p->left, value);
    else
    if (value > p->info)
        p->right = Insert(p->right, value);
    return balanceHeight(p);
}

Node* deleteMin(Node* p)
{
    if (p->left == 0)
        return p->right;
    p->left = deleteMin(p->left);
    return balanceHeight(p);
}

Node* Delete(Node* p, int value)
{
    if (!p)
        return 0;
    if (value < p->info)
        p->left = Delete(p->left, value);
    else if (value > p->info)
        p->right = Delete(p->right, value);
    else
    {
        Node* q = p->left;
        Node* r = p->right;
        delete p;
        if (!r)
            return q;
        Node* min = FindMin(r);
        min->right = deleteMin(r);
        min->left = q;
        return balanceHeight(min);
    }
    return balanceHeight(p);
}