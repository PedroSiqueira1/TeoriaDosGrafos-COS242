#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class AdjMatrGraph{
    private:
    int N;
    int M;
    int** AdjMat;
    string str;

    public:
        AdjMatrGraph(string str){
            this->str = str;
            N = (int)str.at(0) - '0';
            this->M = 0;
            int len = str.length();
            AdjMat = new int*[N];
            for(int i = 0; i < N; i++){
                AdjMat[i] = new int[N];
                for(int j = 0; j < N; j++){
                    AdjMat[i][j] = 0;
                }
            }

            for (int i=0; i < len; i++){
                char c = str[i];
                if (c == '\n' && i < (len-1)){
                    M++;
                    int x,y = 0;
                    x = (int)str.at(i+1) - '0';
                    y = (int)str.at(i+2) - '0';

                    AdjMat[x][y] = 1;
                    AdjMat[y][x] = 1;
                }
            }

        }

        void PrintMat(){
            for (int i = 0; i < N; i++){
                //cout << i << " : ";
                for(int j = 0; j < N; j++){
                    cout << AdjMat[i][j] << " ";
                }
            cout << endl;
            }
        }

        void NumOfEdges(){
            cout << "M is " << M;
        }
};

int main()
{
    string s = "6\n12\n13\n14\n15\n23\n24\n25\n34\n35\n45";

    AdjMatrGraph g(s);
    g.PrintMat();
    g.NumOfEdges();
}
