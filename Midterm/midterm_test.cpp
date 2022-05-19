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
    unique_ptr<vector<int> > base;
    int size = 0;
    int capacity = 0;
    public:
        Minimum(int c = 1) : capacity(c) { allocate(capacity); }
        Minimum(Minimum& c)
        {
            size = c.size;
            base = make_unique<vector<int> >(vector<int>(size));
            copy(c.base.get()->begin(), c.base.get()->end(), base.get()->begin());
        }

        void allocate(int c)
        {
            capacity = c;
            base = make_unique<vector<int> >(vector<int>(capacity, 0));
        }
        void pop()
        {
            base.get()->erase(base.get()->begin());
            size--;
        }
        void set(int v, int offset) { base.get()->at(offset) = v; size++; }
        int get(int offset) { return base.get()->at(offset); }
        int length() { return size; }
        int begin() { return base.get()->front(); }
        int end() { return base.get()->back(); }
        void push(int t) { set(t, size); }
        int operator[] (int offset) { return get(offset); }
};

class Trescence
{
    vector<int> out = vector<int>(MAXS);
    vector<int> f = vector<int>(MAXS);
    vector<vector<int> > g = vector<vector<int> >(MAXS, vector<int> (MAXC));
    vector<string> arr;
    int key;
    int states = 1;
    public:
        Trescence(vector<string> a)
        {
            arr = a;
            key = a.size();
            fill(out.begin(), out.end(), 0);
            for_each(g.begin(), g.end(), [] (vector<int> &v) { fill(v.begin(), v.end(), -1); });
            for (int i = 0; i < key; ++i) 
            {
                const string& word = arr.at(i);
                int currentState = 0;
                for (int j = 0; j < word.size(); ++j) 
                {
                    int ch = word[j] - 'a';
                    if (g.at(currentState).at(ch) == -1)
                        g.at(currentState).at(ch) = states++;
                    currentState = g.at(currentState).at(ch);
                }
                out.at(currentState) |= (1 << i);
            }

            for (int ch = 0; ch < MAXC; ++ch)
                if (g.at(0).at(ch) == -1)
                    g.at(0).at(ch) = 0;
            fill(f.begin(), f.end(), -1);
            Minimum min(MAXS);

            for (int ch = 0; ch < MAXC; ++ch) 
            {
                if(g.at(0).at(ch) != 0)
                {
                    f.at(g.at(0).at(ch)) = 0;
                    min.push(g.at(0).at(ch));
                }
            }

            while (min.length()) 
            {
                int state = min.begin();
                min.pop();
                for (int ch = 0; ch < MAXC; ++ch)
                {
                    if(g.at(state).at(ch) != -1)
                    {
                        int failure = f.at(state);
                        while(g.at(failure).at(ch) == -1)
                            failure = f.at(failure);
                        failure = g.at(failure).at(ch);
                        f.at(g.at(state).at(ch)) = failure;
                        out.at(g.at(state).at(ch)) |= out.at(failure);
                        min.push(g.at(state).at(ch));
                    }
                }
            }

        }
        int Next(int currentState, char nextInput)
        {
            int answer = currentState;
            int ch = nextInput - 'a';
            while(g.at(answer).at(ch) == -1)
                answer = f.at(answer);
            return g.at(answer).at(ch);
        }
        void Parse(string text)
        {
            int currentState = 0;
            for (int i = 0; i < text.size(); ++i) 
            {
                currentState = Next(currentState, text[i]);
                if(out.at(currentState) == 0)
                    continue;
                for (int j = 0; j < key; ++j) 
                {
                    if (out.at(currentState) & (1 << j)) 
                    {
                        cout << "Word " << arr.at(j) << " appears from "
                            << i - arr.at(j).size() + 1 << " to " << i << endl;
                    }
                }
            }
        }
};

int main()
{
    vector<string> arr{ "do","go","dog","god","good","gold" };
    string text = "agodogold";
    Trescence putre(arr);
    putre.Parse(text);

    return 0;
}