#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>


using namespace std;


class AdjMatrGraph{
    private:
    int N;
    int M;
    int** AdjMat;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    double sum = 0; 
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

        void printMat(){
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

        double findMean(){
            return sum/N;
        }

        int findMedian(){
            std::sort(std::begin(degrees), std::end(degrees));
            if (N % 2 != 0){
                return degrees.at(N / 2);
            }
            else{
                return degrees.at((((N - 1) / 2) + degrees.at(N / 2)) / 2);
            }
        }

        void find_degrees(){
        for(int i = 0; i < N; i++){
            int cont = 0;
            for(int j = 0; j < N; j++){
                if(AdjMat[i][j] == 1){
                    cont++;
                }
            }
            degrees.push_back(cont);  // Adicionando grau do vértice à lista
            sum += cont; // Somando os graus dos vértices
 
            if(!min_degree){
                min_degree = cont;
            }
            if (cont < min_degree){
                min_degree = cont;
            }

            if (cont > max_degree){
                max_degree = cont;
            }
        }
        

        ofstream answer;
        answer.open("Resposta.txt");
        if (answer.is_open()){
            answer << "O grafo possui " << to_string(N) << " vértices \n";
            answer << "O grafo possui " << to_string(M) << " arestas \n";
            answer << "O grau mínimo é " << min_degree<< '\n';
            answer << "O grau máximo é " << max_degree<< '\n';
            answer << "A média dos graus é " << findMean() << '\n';
            answer << "A mediana dos graus é " << findMedian() << '\n';
            answer.close();

        }
        

        cout << "O grau mínimo é " << min_degree<< '\n';
        cout << "O grau máximo é " << max_degree<< '\n';
        cout << "A média dos graus é " << findMean() << '\n'; // Média calculada dividindo a soma dos vértices pelo número de vértices
        cout << "A mediana dos graus é " << findMedian() << '\n'; 
    }



};

class AdjListGraph{
private:
    int N;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees; 
    int M = 0;
    double sum = 0;
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

    double findMean(){
        return sum/N;
    }



    int findMedian(){
        std::sort(std::begin(degrees), std::end(degrees));
        if (N % 2 != 0){
            return degrees.at(N / 2);
        }
        else{
            return degrees.at((((N - 1) / 2) + degrees.at(N / 2)) / 2);
        }
    }

    void find_degrees(){
        for(int i = 0; i < N; i++){

            degrees.push_back((L[i].size())); // Adicionando grau do vértice à lista
            sum += L[i].size(); // Somando os graus dos vértices

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

        ofstream answer;
        answer.open("Resposta.txt");
        if (answer.is_open()){
            answer << "O grafo possui " << to_string(N) << " vértices \n";
            answer << "O grafo possui " << to_string(M) << " arestas \n";
            answer << "O grau mínimo é " << min_degree<< '\n';
            answer << "O grau máximo é " << max_degree<< '\n';
            answer << "A média dos graus é " << findMean() << '\n';
            answer << "A mediana dos graus é " << findMedian() << '\n';
            answer.close();

        }
        

        cout << "O grau mínimo é " << min_degree<< '\n';
        cout << "O grau máximo é " << max_degree<< '\n';
        cout << "A média dos graus é " << findMean() << '\n'; // Média calculada dividindo a soma dos vértices pelo número de vértices
        cout << "A mediana dos graus é " << findMedian() << '\n'; 
    }
    
        void BFS(int value){
        //Lista de marcados em boolean
        int k = 0;
        visited = new bool[N];
        map< string, map<int,int> >bfstree;
        vector<int> vec;
        vector<int> parent;
        vector<int> level;
        
        for( int i = 0; i < N; i++){
            visited[i] = 0;
        }
        //Marca a raiz como marcado
        visited[value] = true;
        //Cria a fila e coloca o valor na fila
        list<int> Q;
        list<int>::iterator i;
        Q.push_back(value);
        vec.push_back(value);
        parent.push_back(0);
        level.push_back(0);
        
        //Enquanto Q não estiver vazia
        while(!Q.empty()){
            //retira v de Q
            int v = Q.front();
            Q.pop_front();
            k++;
            
            //para todo vizinho w de v:
            for(i = L[v].begin(); i!=L[v].end(); i++){
                int w = *i;
                //Se não estiver nos visitados
                if(!visited[w]){
                    //Marca como visitado
                     visited[w] = true;
                     //Coloca no Q
                     Q.push_back(w);
                     //Coloca, respectivamente, o valor, o pai e o nível
                     vec.push_back(w);
                     parent.push_back(v);
                     level.push_back(k);
                }
            }
        }
        int len = vec.size();
        for(int i = 0; i < len; i++){
            if (i < 1){
               cout << "number: " << vec[i] << " / level:" << level[i] << " / parent: none" << endl;
            }
            if(i >= 1){
                cout << "number: " << vec[i] << " / level:" << level[i] << " / parent: " << parent[i] << endl;
            }
        
        }
    }

};



int main(){

    string s = "6\n12\n13\n14\n15\n23\n24\n25\n34\n35\n45\n01";
    int vertices;
    AdjListGraph g(s);
    g.printList();
    
    g.find_degrees();

    std::ifstream myfile; 
    myfile.open("Grafo.txt");
    std::string myline;
    
    return 0;
}

