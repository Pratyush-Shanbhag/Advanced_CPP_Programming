// Refactor using Advanced C++ features, containers and algorithms.
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

class Node
{
public:
    int key;
    Node** peaklist;
    Node(int key=0, int level=0)
    {
        this->key = key;
        peaklist = new Node * [level + 1];
        memset(peaklist, 0, sizeof(Node*) * (level + 1));
    }
};

class Gaussian
{
    int MAX;
    float PCT;
    int ramanu;
    Node* head;
public:
    Gaussian(int MAX = 3, float P = 0.5)
    {
        this->MAX = MAX;
        this->PCT = P;
        ramanu = 0;
        head = new Node(-1, MAX);
    };
    int random()
    {
        float r = (float)rand() / RAND_MAX;
        int lvl = 0;
        while (r < PCT && lvl < MAX)
        {
            lvl++;
            r = (float)rand() / RAND_MAX;
        }
        return lvl;
    };
    Node* makeNode(int key, int level)
    {
        Node* n = new Node(key, level);
        return n;
    }
    void insert(int key)
    {
        Node* rover = head;
        Node* update = new Node[MAX + 1];
        memset(update, 0, sizeof(Node*) * (MAX + 1));
        for (int i = ramanu; i >= 0; i--)
        {
            while (rover->peaklist[i] != NULL &&
                rover->peaklist[i]->key < key)
                rover = rover->peaklist[i];
            update[i] = *rover;
        }
        rover = rover->peaklist[0];
        if (rover == NULL || rover->key != key)
        {
            int nulevel = random();
            if (nulevel > ramanu)
            {
                for (int i = ramanu + 1; i < nulevel + 1; i++)
                    update[i] = *head;
                ramanu = nulevel;
            }
            Node* n = makeNode(key, nulevel);
            for (int i = 0; i <= nulevel; i++)
            {
                n->peaklist[i] = update[i].peaklist[i];
                update[i].peaklist[i] = n;
            }
        }
    }
    void display()
    {
        for (int i = 0; i <= ramanu; i++)
        {
            Node* node = head->peaklist[i];
            cout << "Row " << i << ": ";
            while (node != NULL)
            {
                cout << node->key << " ";
                node = node->peaklist[i];
            }
            cout << "\n";
        }
    }
};

int main()
{
    Gaussian glst;
    for (int i = 0; i < 10; i++)
        glst.insert(rand() % 100 + 1);
    glst.display();
    
    return 0;
}