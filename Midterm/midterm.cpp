using namespace std;
#include <string>
#include <iostream>
const int MAXS = 500;
const int MAXC = 26;

class Minimum
{
    int* base;
    int size = 0;
    int capacity = 0;
public:
    Minimum(int c = 1) : capacity(c) { allocate(capacity); }
    Minimum(Minimum& c)
    {
        size = c.size;
        base = new int[size];
        for (int i = 0; i < size; i++)
            base[i] = c.base[i];
    }
    void allocate(int c)
    {
        capacity = c;
        base = new int[capacity];
        for (int i = 0; i < capacity; i++)
            base[i] = 0;
    }
    void pop()
    {
        for (int i = 1; i < size; i++)
            base[i - 1] = base[i];
        size--;
    }
    void set(int v, int offset) { base[offset] = v; size++; }
    int get(int offset) { return base[offset]; }
    int length() { return size; }
    int begin() { return base[0]; }
    int end() { return base[size - 1]; }
    void push(int t) { set(t, size); }
    int operator[] (int offset) { return get(offset); }
};

class Trescence
{
    int out[MAXS];
    int f[MAXS];
    int g[MAXS][MAXC];
    string* arr;
    int key;
    int states = 1;
public:
    Trescence(string* a, int k)
    {
        arr = a;
        key = k;
        memset(out, 0, sizeof out);
        memset(g, -1, sizeof g);
        for (int i = 0; i < k; ++i) 
        {
            const string& word = arr[i];
            int currentState = 0;
            for (int j = 0; j < word.size(); ++j) 
            {
                int ch = word[j] - 'a';
                if (g[currentState][ch] == -1)
                    g[currentState][ch] = states++;
                currentState = g[currentState][ch];
            }
            out[currentState] |= (1 << i);
        }
        for (int ch = 0; ch < MAXC; ++ch)
            if (g[0][ch] == -1)
                g[0][ch] = 0;
        memset(f, -1, sizeof f);
        Minimum min(MAXS);
        for (int ch = 0; ch < MAXC; ++ch) 
        {
            if (g[0][ch] != 0) 
            {
                f[g[0][ch]] = 0;
                min.push(g[0][ch]);
            }
        }
        while (min.length()) 
        {
            int state = min.begin();
            min.pop();
            for (int ch = 0; ch <= MAXC; ++ch) 
            {
                if (g[state][ch] != -1) 
                {
                    int failure = f[state];
                    while (g[failure][ch] == -1)
                        failure = f[failure];
                    failure = g[failure][ch];
                    f[g[state][ch]] = failure;
                    out[g[state][ch]] |= out[failure];
                    min.push(g[state][ch]);
                }
            }
        }
    }
    int Next(int currentState, char nextInput)
    {
        int answer = currentState;
        int ch = nextInput - 'a';
        while (g[answer][ch] == -1)
            answer = f[answer];
        return g[answer][ch];
    }
    void Parse(string text)
    {
        int currentState = 0;
        for (int i = 0; i < text.size(); ++i) 
        {
            currentState = Next(currentState, text[i]);
            if (out[currentState] == 0)
                continue;
            for (int j = 0; j < key; ++j) 
            {
                if (out[currentState] & (1 << j)) 
                {
                    cout << "Word " << arr[j] << " appears from "
                        << i - arr[j].size() + 1 << " to " << i << endl;
                }
            }
        }
    }
};

void main()
{
    string arr[] = { "do","go","dog","god","good","gold" };
    string text = "agodogold";
    int size = sizeof(arr) / sizeof(arr[0]);
    Trescence putre(arr, size);
    putre.Parse(text);
}