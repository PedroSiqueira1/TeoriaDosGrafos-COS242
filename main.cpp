#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
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

        void printMat(){
            for (int i = 0; i < N; i++){
                //cout << i << " : ";
                for(int j = 0; j < N; j++){
                    cout << AdjMat[i][j] << " ";
                }
            cout << endl;
            }
        }
};

class AdjListGraph{
private:
    int N;
    int min_degree;
    int max_degree = 0;
    int M = 0;
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


    void printList(){
        for(int i = 0; i < N; i++){
                cout << "N: " << i << " -> | ";
            for(int x:L[i]){
                cout<<x<<" | ";
            }
            cout<<endl;
        }
    }

    void numOfEdges(){
        cout << "M is " << M << '\n';
    }

    void find_degrees(){
        list<int> degrees;
        double sum = 0;
        for(int i = 0; i < N; i++){
            degrees.push_back(L[i].size());
            sum += L[i].size();

            if(!min_degree){
                min_degree = L[i].size();
            }

            if (L[i].size() < min_degree){
                min_degree = L[i].size();
            }
            if (L[i].size() > max_degree){
                max_degree = L[i].size();
            }
        }


        cout << min_degree<< '\n';
        cout << max_degree<< '\n';
        cout << sum/N << '\n';
    }

};



int main()
{

    string s = "6\n12\n13\n14\n15\n23\n24\n25\n34\n35\n45\n01";
    int vertices;

    AdjListGraph g(s);
    g.printList();
    //g.numOfEdges();
    g.find_degrees();

    std::ifstream myfile; 
    myfile.open("Grafo.txt");
    std::string myline;
    

    if (myfile.is_open()) { // Checando se arquivo está aberto
        getline(myfile, myline);
        vertices = std::stoi(myline);
        while (myfile.good()){ // Enquanto arquivo não falhar ou chegar no EOF
            std::getline (myfile, myline); 
            std::cout << myline << '\n'; // Printe uma linha
        }
    }
    else{
        std::cout << "Arquivo não conseguiu ser aberto\n";
    }
    return 0;
}

