#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class AdjMatrGraph{
    private:
    int N;
    int** AdjMat;
    string str;

    public:
        AdjMatrGraph(string str){
            this->str = str;
            this->N = 0;
            stringstream IntValue(str.substr(0,1));
            IntValue >> N;
            int M = 0;
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
                    //M++;
                    int x,y = 0;
                    x = (int)str.at(i+1) - '0';
                    y = (int)str.at(i+2) - '0';

                    AdjMat[x-1][y-1] = 1;
                    AdjMat[y-1][x-1] = 1;

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
};

int main()
{
    string s = "5\n12\n13\n14\n15\n23\n24\n25\n34\n35\n45";

    AdjMatrGraph g(s);
    g.PrintMat();
}
