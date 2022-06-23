#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

class Node
{
public:
    int key;
    //Node** peaklist;
    vector<shared_ptr<Node> > peaklist;
    Node(int key=0, int level=0)
    {
        this->key = key;
        //peaklist = new Node * [level + 1];
        peaklist.reserve(level+1);
        //memset(peaklist, 0, sizeof(Node*) * (level + 1));
        fill(peaklist.begin(), peaklist.end(), nullptr);
    }
};

class Gaussian
{
    int MAX;
    float PCT;
    int ramanu;
    //Node* head;
    shared_ptr<Node> head;
public:
    Gaussian(int MAX = 3, float P = 0.5)
    {
        this->MAX = MAX;
        this->PCT = P;
        ramanu = 0;
        //head = new Node(-1, MAX);
        head = make_shared<Node>(-1, MAX);
        cout << "head key: " << head->key << endl;
    }
    int random()
    {
        //float r = (float)rand() / RAND_MAX;
        float r = static_cast<float>(rand()) / RAND_MAX;
        int lvl = 0;
        while (r < PCT && lvl < MAX)
        {
            lvl++;
            //r = (float)rand() / RAND_MAX;
            r = static_cast<float>(rand()) / RAND_MAX;
        }
        return lvl;
    }
    //Node* makeNode(int key, int level)
    shared_ptr<Node> makeNode(int key, int level)
    {
        //Node* n = new Node(key, level);
        shared_ptr<Node> n = make_shared<Node>(key, level);
        return n;
    }
    void insert(int key)
    {
        //Node* rover = head;
        shared_ptr<Node> rover = head;
        //Node* update = new Node[MAX + 1]; //
        //memset(update, 0, sizeof(Node*) * (MAX + 1)); //
        vector<Node> update(MAX + 1);
        //fill(update.begin(), update.end(), NULL);
    
        for (int i = ramanu; i >= 0; i--)
        {
            //while (rover->peaklist[i] != NULL &&
            bool b = rover->peaklist[i] != NULL;
            cout << "condition: " << b << endl;
            cout << rover->peaklist[i]->key << endl;
            while (rover->peaklist[i] != NULL &&
                //rover->peaklist[i]->key < key)
                  rover->peaklist[i]->key < key)
                //rover = rover->peaklist[i];
                rover = rover->peaklist[i];
            //update[i] = *rover;
            //Node no = rover;
            update[i] = *rover;
        }
        //rover = rover->peaklist[0];
        rover = rover->peaklist[0];
        //if (rover == NULL || rover->key != key)
        if (rover == NULL || rover->key != key)
        {
            int nulevel = random();
            if (nulevel > ramanu)
            {
                for (int i = ramanu + 1; i < nulevel + 1; i++)
                    //update[i] = *head;
                    update[i] = *head;
                ramanu = nulevel;
            }
            //Node* n = makeNode(key, nulevel);
            shared_ptr<Node> n = makeNode(key, nulevel);
            for (int i = 0; i <= nulevel; i++)
            {
                //n->peaklist[i] = update[i].peaklist[i];
                n->peaklist[i] = update[i].peaklist[i];
                update[i].peaklist[i] = n;
            }
        }
    }
    void display()
    {
        for (int i = 0; i <= ramanu; i++)
        {
            //Node* node = head->peaklist[i];
            shared_ptr<Node> node = head->peaklist[i];
            cout << "Row " << i << ": ";
            while (node != NULL)
            {
                cout << node->key << " ";
                //node = node->peaklist[i];
                node = node->peaklist[i];
            }
            cout << "\n";
        }
    }
};

int main()
{
    Gaussian glst;
    for (int i = 0; i < 10; i++) //
        glst.insert(rand() % 100 + 1);
    glst.display();
    
    return 0;
}