#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;


class AdjMatrGraph{
    private:
    int N;
    int M;
    bool** AdjMat;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    double sum = 0; 
    string str;
    bool** visited;
    map<int, bool> visitedDFS;

   public:
        AdjMatrGraph(string str){
            this->str = str;
            N = (int)str.at(0) - '0';
            this->M = 0;
            int len = str.length();
            AdjMat = new bool*[N];
            for(int i = 0; i < N; i++){
                AdjMat[i] = new bool[N];
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
    bool* visited;
    int* parent;
    int* level;
    map<int, bool> visitedDFS;

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
        visited = new bool[N];
        parent = new int[N];
        level = new int[N];

        for( int i = 0; i < N; i++){
            visited[i] = 0;
            parent[i] = 0;
            level[i] = 0;
        }
        //Marca a raiz como marcado
        visited[value] = true;
        parent[value] = -1;
        level[value] = 0;
        //Cria a fila e coloca o valor na fila
        list<int> Q;
        list<int>::iterator i;
        Q.push_back(value);
        
        //Enquanto Q não estiver vazia
        while(!Q.empty()){
            //retira v de Q
            int v = Q.front();
            Q.pop_front();
            //para todo vizinho w de v:
            for(i = L[v].begin(); i!=L[v].end(); i++){
                int w = *i;
                //Se não estiver nos visitados
                if(!visited[w]){
                    //Marca como visitado
                     visited[w] = true;
                     //Coloca no Q
                     Q.push_back(w);
                     parent[w] = v;
                     level[w] = level[v] + 1;
                }
            }
        }
        
        //for(int i = 0; i < N; i++){
        //    cout << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
        //}
    }

    void DFS(int v){

        visitedDFS[v] = true;
        cout << v << " ";

        
        // Recur for all the vertices adjacent
        // to this vertex
        list<int>::iterator i;
        for (i = L[v].begin(); i != L[v].end(); ++i){
            
            if (!visitedDFS[*i]){
                DFS(*i);
            }
        }
    }
    
    void Distance(int n1, int n2){
        BFS(n1);
        cout << "The distance between " << n1 << " and " << n2 << " is " << level[n2] << endl;
    }
    
    void Diameter(){
        int d = 0;
        for(int i = 0; i < N; i++){
            BFS(i);
            for(int k = 0; k < N; k++){
                if (level[k] > d){
                    d = level[k];
                }
            }
        }
        cout << "The diameter is " << d << endl;
    }
    
    void CheckLevel(int n){
        cout << "The level of " << n << " is " << level[n] << endl;
    }
    
    void CheckParent(int n){
        cout << "The parent of " << n << " is " << parent[n] << endl;
    }
};

//Para usar chame a BFS partindo da raiz que deseja.
//Logo em seguida use CheckParent ou CheckLevel para ver o
//pai ou o nível, respectivamente. Caso chame a BFS ou Diameter ou
//distância este valor mudará.

int main(){

    string s = "6\n12\n13\n15\n24\n25\n35\n45\n01";
    //int vertices;
    AdjListGraph g(s);
    
    g.printList();
    

    //g.find_degrees();
    g.Distance(4,3);
    g.Diameter();
    g.BFS(3);
    g.CheckLevel(3);
    g.CheckParent(3);
    std::ifstream myfile; 
    myfile.open("Grafo.txt");
    std::string myline;
    
    return 0;
}
