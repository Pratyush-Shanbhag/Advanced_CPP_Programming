
#include <climits>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <thread>
#include <map>
#include <chrono>
#include "ConsoleColor.h"

using namespace std;
using namespace std::chrono;

#define LOWER_ASCII 128

/*struct Diagnostics
{
    int ncompares = 0;
    string title = "";
    system_clock::time_point tbegin;
    system_clock::time_point tend;
    Diagnostics() 
    { 
        ncompares = 0; 
        tbegin = system_clock::now();
    }
    Diagnostics(string s) { ncompares = 0; title = s; tbegin = system_clock::now(); }
    void operator ++ (int) { ncompares++; }
    operator int() { return ncompares; }
    void analysis()
    {
        tend = system_clock::now();
        cout << green << "Duration: " << cyan << static_cast<double>((tend - tbegin).count()) / 1000000.0 << endl;
        cout << green << title << " compares = " << cyan << ncompares << endl;
    }
    void Output(string stext, int startindex)
    {
        for (int i = 0; i < stext.length(); i++)
        {
            if (i < startindex)
                cout << yellow << stext[i];
            else
                cout << red << stext[i];
            this_thread::sleep_for(chrono::milliseconds(15));
        }
        cout << white << endl;
    }
};


map<char, int> generateBadCharShift(string pattern)
{
    map<char, int> skipList;
    for (int i = 0; i < pattern.length() - 1; i++)
        skipList[pattern[i]] = pattern.length() - i - 1;
    return skipList;
}


int findSuffixPosition(char badchar, string suffix, string full_term)
{
    for (int offset = full_term.length() + 1; offset > 0; offset--)
    {
        bool flag = true;
        for (int suffix_index = 0; suffix_index < suffix.length(); suffix_index++)
        {
            int term_index = offset - suffix.length() - 1 + suffix_index;
            if (term_index >= 0 && suffix[suffix_index] != 
            full_term[term_index])
            flag = false;
        }
        int term_index = offset - suffix.length() - 1;
        if (flag && (term_index <= 0 || full_term[term_index - 1] != badchar))
            return full_term.length() - offset + 1;
    }
    return -1;
}


map<int, int> generateSuffixShift(string key)
{
    map<int, int> skipList;
    string buffer = "";
    for (int i = 0; i < key.length(); i++)
    {
        skipList[buffer.length()] = findSuffixPosition(key[key.length() - 1 - i], buffer, key);
        buffer = key[key.length() - 1 - i] + buffer;
    }
    return skipList;
}


int getbadChar(char c, map<char, int>& badChar)
{
    auto it = badChar.find(c);
    if (it != badChar.end())
    return badChar[c];
    else
    return badChar.size() + 1;
}


int BoyerMooreHorsepool(string text, string pattern)
{
Diagnostics diag("BoyerMooreBad");
cout << yellow << "pattern: " << pattern << endl;
cout << yellow << "target:  " << text << endl;
map<int, int> goodSuffix = generateSuffixShift(pattern);
for (auto g : goodSuffix) cout << "<" << g.first << "," << g.second << ">" <<
endl;
map<char, int> badChar = generateBadCharShift(pattern);
for (auto b : badChar) cout << "<" << b.first << "," << b.second << ">" << 
endl;
int i = 0;
while (i < text.length() - pattern.length() + 1)
{
diag.Output(text, i);
int j = pattern.length();
while (j > 0 && pattern[j - 1] == text[i + j - 1])
{
diag++;
j -= 1;
}
if (j > 0)
{
int badCharShift = getbadChar(text[i + j - 1], badChar);
int goodSuffixShift = goodSuffix[pattern.length() - j];
cout << cyan << "badCharShift " << badCharShift << " target[" << 
i + j - 1 << "] = " << text[i + j - 1] << endl;
cout << cyan << "goodSuffixShift " << goodSuffixShift << " goodSuffix[" << pattern.length() - j << "] = " << text[goodSuffix[pattern.length() - j]] << endl;
if (badCharShift > goodSuffixShift)
i += badCharShift;
else
i += goodSuffixShift;
}
else
{
diag.analysis();
return i;
}
}
diag.analysis();
return -1;
}*/

struct Diagnostics
{
    int ncompares = 0;
    string title = "";
    system_clock::time_point tbegin;
    system_clock::time_point tend;
    Diagnostics() 
    { 
        ncompares = 0; 
        tbegin = system_clock::now();
    }
    Diagnostics(string s) { ncompares = 0; title = s; tbegin = system_clock::now(); }
    void operator ++ (int) { ncompares++; }
    operator int() { return ncompares; }
    void analysis()
    {
        tend = system_clock::now();
        cout << green << "Duration: " << cyan << static_cast<double>((tend - tbegin).count()) / 1000000.0 << endl;
        cout << green << title << " compares = " << cyan << ncompares << endl;
    }
    void Output(string stext, int startindex)
    {
        for (int i = 0; i < stext.length(); i++)
        {
            if (i < startindex)
                cout << yellow << stext[i];
            else
                cout << red << stext[i];
            this_thread::sleep_for(chrono::milliseconds(15));
        }
        cout << white << endl;
    }
};


map<char, int> generateBadCharShift(string pattern)
{
    map<char, int> skipList;
    for (int i = 0; i < pattern.length() - 1; i++)
        skipList[pattern[i]] = pattern.length() - i - 1;
    return skipList;
}


int findSuffixPosition(char badchar, string suffix, string full_term)
{
    for (int offset = full_term.length() + 1; offset > 0; offset--)
    {
        bool flag = true;
        for (int suffix_index = 0; suffix_index < suffix.length(); suffix_index++)
        {
            int term_index = offset - suffix.length() - 1 + suffix_index;
            if (term_index >= 0 && suffix[suffix_index] != 
            full_term[term_index])
            flag = false;
        }
        int term_index = offset - suffix.length() - 1;
        if (flag && (term_index <= 0 || full_term[term_index - 1] != badchar))
            return full_term.length() - offset + 1;
    }
    return -1;
}


map<int, int> generateSuffixShift(string key)
{
    map<int, int> skipList;
    string buffer = "";
    for (int i = 0; i < key.length(); i++)
    {
        skipList[buffer.length()] = findSuffixPosition(key[key.length() - 1 - i], buffer, key);
        buffer = key[key.length() - 1 - i] + buffer;
    }
    return skipList;
}


int getbadChar(char c, map<char, int>& badChar)
{
    auto it = badChar.find(c);
    if (it != badChar.end())
        return badChar[c];
    else
        return badChar.size() + 1;
}


int BoyerMooreHorsepool(string text, string pattern)
{
    Diagnostics diag("BoyerMooreBad");

    cout << yellow << "pattern: " << pattern << endl;
    cout << yellow << "target:  " << text << endl;

    map<int, int> goodSuffix = generateSuffixShift(pattern);
    for (auto g : goodSuffix)
        cout << "<" << g.first << "," << g.second << ">" << endl;

    map<char, int> badChar = generateBadCharShift(pattern);
    for (auto b : badChar)
        cout << "<" << b.first << "," << b.second << ">" << endl;

    int i = 0;
    while (i < text.length() - pattern.length() + 1)
    {
        diag.Output(text, i);
        int j = pattern.length();
        while (j > 0 && pattern[j - 1] == text[i + j - 1])
        {
            diag++;
            j -= 1;
        }
        if (j > 0)
        {
            int badCharShift = getbadChar(text[i + j - 1], badChar);
            int goodSuffixShift = goodSuffix[pattern.length() - j];

            cout << cyan << "badCharShift " << badCharShift << " target[" << i + j - 1 << "] = " << text[i + j - 1] << endl;
            cout << cyan << "goodSuffixShift " << goodSuffixShift << " goodSuffix[" << pattern.length() - j << "] = " << text[goodSuffix[pattern.length() - j]] << endl;
            
            if (badCharShift > goodSuffixShift)
                i += badCharShift;
            else
                i += goodSuffixShift;
        }
        else
        {
            diag.analysis();
            return i;
        }
    }
    diag.analysis();
    return -1;
}

void testBoyerMooreHorsepool()
{
    cout << purple << "\n<< BoyerMooreHorsepool >>\n";
    string text = "ccacatcatacatalcatalocatalog";
    string pattern = "catalog";
    BoyerMooreHorsepool(text, pattern);
}

int main()
{
    testBoyerMooreHorsepool();
    return 0;
}
