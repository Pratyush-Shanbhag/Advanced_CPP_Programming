#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

const int MAXS = 500;
const int MAXC = 26;

class Minimum
{
    //int* base;
    shared_ptr<vector<int> > base;
    int size = 0;
    int capacity = 0;
    public:
        Minimum(int c = 1) : capacity(c) { allocate(capacity); }
/*        Minimum(Minimum& c)
        {
            size = c.size;
            //base = new int[size];
            base = make_shared<vector<int> >(c.base.get());
            //for (int i = 0; i < size; i++)
                //base[i] = c.base[i];
                //base.get()[i] = c.base.get()[i];
        }
*/
        void allocate(int c)
        {
            capacity = c;
            //base = new int[capacity];
            base = make_shared<vector<int> >(vector<int>(capacity, 0));
            /*for (int i = 0; i < capacity; i++)
                //base[i] = 0;
                base.get()[i] = 0;*/
        }
        void pop()
        {
            /*for (int i = 1; i < size; i++)
                //base[i - 1] = base[i];
                base.get()->at(i-1) = base.get()->at(i);
            size--;*/
            base.get()->erase(base.get()->begin());
            size--;
        }
        //void set(int v, int offset) { base[offset] = v; size++; }
        void set(int v, int offset) { base.get()->at(offset) = v; size++; }
        //int get(int offset) { return base[offset]; }
        int get(int offset) { return base.get()->at(offset); }
        int length() { return size; }
        //int begin() { return base[0]; }
        int begin() { return base.get()->front(); }
        //int end() { return base[size - 1]; }
        int end() { return base.get()->back(); }
        void push(int t) { set(t, size); }
        int operator[] (int offset) { return get(offset); }
};

class Trescence
{
    //int out[MAXS];
    vector<int> out = vector<int>(MAXS);
    //int f[MAXS];
    vector<int> f = vector<int>(MAXS);
    //int g[MAXS][MAXC];
    vector<vector<int> > g = vector<vector<int> >(MAXS, vector<int> (MAXC));
    //string* arr;
    vector<string> arr;
    int key;
    int states = 1;
    public:
        //Trescence(string* a, int k)
        Trescence(vector<string> a)
        {
            arr = a;
            key = a.size();
            //memset(out, 0, sizeof out);
            fill(out.begin(), out.end(), 0);
            //memset(g, -1, sizeof g);
            for(int i = 0; i < g.size(); i++) {
                fill(g.at(i).begin(), g.at(i).end(), -1);
            }
            //for (int i = 0; i < k; ++i) 
            for (int i = 0; i < key; ++i) 
            {
                //const string& word = arr[i];
                const string& word = arr.at(i);
                int currentState = 0;
                for (int j = 0; j < word.size(); ++j) 
                {
                    int ch = word[j] - 'a';
                    //if (g[currentState][ch] == -1)
                    if (g.at(currentState).at(ch) == -1)
                        //g[currentState][ch] = states++;
                        g.at(currentState).at(ch) = states++;
                    //currentState = g[currentState][ch];
                    currentState = g.at(currentState).at(ch);
                }
                //out[currentState] |= (1 << i);
                out.at(currentState) |= (1 << i);
            }

            for (int ch = 0; ch < MAXC; ++ch)
                //if (g[0][ch] == -1)
                if (g.at(0).at(ch) == -1)
                    //g[0][ch] = 0;
                    g.at(0).at(ch) = 0;
            //memset(f, -1, sizeof f);
            fill(f.begin(), f.end(), -1);
            Minimum min(MAXS);

            for (int ch = 0; ch < MAXC; ++ch) 
            {
                //if (g[0][ch] != 0) 
                if(g.at(0).at(ch) != 0)
                {
                    //f[g[0][ch]] = 0;
                    f.at(g.at(0).at(ch)) = 0;
                    //min.push(g[0][ch]);
                    min.push(g.at(0).at(ch));
                }
            }

            while (min.length()) 
            {
                int state = min.begin();
                min.pop();
                //for (int ch = 0; ch <= MAXC; ++ch)
                for (int ch = 0; ch < MAXC; ++ch)
                {
                    //if (g[state][ch] != -1) 
                    if(g.at(state).at(ch) != -1)
                    {
                        //int failure = f[state];
                        int failure = f.at(state);
                        //while (g[failure][ch] == -1)
                        while(g.at(failure).at(ch) == -1)
                            //failure = f[failure];
                            failure = f.at(failure);
                        //failure = g[failure][ch];
                        failure = g.at(failure).at(ch);
                        //f[g[state][ch]] = failure;
                        f.at(g.at(state).at(ch)) = failure;
                        //out[g[state][ch]] |= out[failure];
                        out.at(g.at(state).at(ch)) |= out.at(failure);
                        //min.push(g[state][ch]);
                        min.push(g.at(state).at(ch));
                    }
                }
            }

        }
        int Next(int currentState, char nextInput)
        {
            int answer = currentState;
            int ch = nextInput - 'a';
            //while (g[answer][ch] == -1)
            while(g.at(answer).at(ch) == -1)
                //answer = f[answer];
                answer = f.at(answer);
            //return g[answer][ch];
            return g.at(answer).at(ch);
        }
        void Parse(string text)
        {
            int currentState = 0;
            for (int i = 0; i < text.size(); ++i) 
            {
                currentState = Next(currentState, text[i]);
                //if (out[currentState] == 0)
                if(out.at(currentState) == 0)
                    continue;
                for (int j = 0; j < key; ++j) 
                {
                    //if (out[currentState] & (1 << j))
                    if (out.at(currentState) & (1 << j)) 
                    {
                        /*cout << "Word " << arr[j] << " appears from "
                            << i - arr[j].size() + 1 << " to " << i << endl;*/
                        cout << "Word " << arr.at(j) << " appears from "
                            << i - arr.at(j).size() + 1 << " to " << i << endl;
                    }
                }
            }
        }
};

int main()
{
    //string arr[] = { "do","go","dog","god","good","gold" };
    vector<string> arr{ "do","go","dog","god","good","gold" };
    string text = "agodogold";
    //int size = sizeof(arr) / sizeof(arr[0]);
    //Trescence putre(arr, size);
    Trescence putre(arr);
    putre.Parse(text);

    return 0;
}