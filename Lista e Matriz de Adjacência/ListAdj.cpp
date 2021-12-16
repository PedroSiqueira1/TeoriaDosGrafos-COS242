#include<iostream>
#include<list>
using namespace std;

class AdjListGraph{
private:
    int N;
    int M;
    string str;
    list<int> *L;

public:
    AdjListGraph(string str){
        this-> str = str;
        N = (int)str.at(0) - '0';
        int len = str.length();
        L = new list<int>[N];
        for (int i=0; i < len; i++){
            char c = str[i];
            if (c == '\n' && i < (len-1)){
                M++;
                int x,y = 0;
                x = (int)str.at(i+1) - '0';
                y = (int)str.at(i+2) - '0';
                L[x].push_back(y);
                L[y].push_back(x);
            }
        }
    }

    void PrintList(){
        for(int i = 0; i < N; i++){
                cout << "N: " << i << " -> | ";
            for(int x:L[i]){
                cout<<x<<" | ";
            }
            cout<<endl;
        }

    }

    void NumOfEdges(){
        cout << "M is " << M;
    }
};

int main(){
    string s = "6\n12\n13\n14\n15\n23\n24\n25\n34\n35\n45";

    AdjListGraph g(s);
    g.PrintList();
    g.NumOfEdges();
}
