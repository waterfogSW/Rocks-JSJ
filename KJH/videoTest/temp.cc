#include<bits/stdc++.h>
using namespace std;

int main()
{
    ifstream fin;
    fin.open("Sample.mp4");
    char ch;
    bitset<8> bit;
    while(!fin.eof())
    {
        fin.get(ch);
        bit = ch;
        cout << bit << '\n';
    }
    
    fin.close();
    return 0;
}