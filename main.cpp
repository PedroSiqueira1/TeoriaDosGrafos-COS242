#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>



using namespace std;


class AdjMatrGraph{
    private:
    int M;
    int** AdjMat;
    int min_degree;
    int max_degree = 0;
    vector<int> degrees;
    double sum = 0; 
    string str;
    bool** visited;
    list<int> components;
    bool* visitedbfs;
    int* parent;
    int* level;

    public:
    int N;
        AdjMatrGraph(string str){
            this->str = str;
            this->M = 0;
            string s = str.substr(2);
            //cout << s;
            vector<int> nums;
            
            stringstream stream(str);
            while(1) {
               int n;
               stream >> n;
                if(!stream)
                    break;
                nums.push_back(n);
            }

            //int len = nums.size();
            N = nums.at(0) + 1;
            AdjMat = new int*[N];
            for(int i = 0; i < N; i++){
                AdjMat[i] = new int[N];
                for(int j = 0; j < N; j++){
                    AdjMat[i][j] = 0;
                }
            }
            int len = 0;
            for (int element: nums){
                len++; 
            }
            cout << len;
            int x,y = 0;
            for(int i = 1; i < len; i = i + 2){
                x = nums[i];
                int k = i + 1;
                y = nums[k];
                cout << x << " and " << y << endl;
                AdjMat[x][y] = 1;
                AdjMat[y][x] = 1;
            }
            M = (len - 1)/2;
            

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
    
        void DFS(int v, bool visited[]){
        components.push_back(v);
        visited[v] = true;
        //cout << v << " ";

        
        // Recur for all the vertices adjacent
        // to this vertex
        list<int>::iterator i;
        for (int i = 0; i < N; i++){
            
            if (AdjMat[v][i] == 1 && !visited[i]){
                DFS(i,visited);
            }
        }

    }

    void connectedComponents(){
        // Mark all the vertices as not visited
        int numcc = 0;
        bool* visitedcc = new bool[N];
        for (int v = 0; v < N; v++)
            visitedcc[v] = false;
    
        for (int v = 0; v < N; v++) {
            if (visitedcc[v] == false) {
                // print all reachable vertices
                // from v
                numcc++;
                DFS(v,visitedcc);
                cout << "A componente tem " << components.size() << " vertices" <<"\n";
                components.sort();
                cout << "Componentes: ";
                for (auto const &i: components) {
                    cout << i << " ";
                }
                components.clear();


                cout << "\n";
            }
        }
        cout << "O grafo possui " << numcc << " componentes conexas";
        delete[] visitedcc;
    }
        void BFS(int value){
        visitedbfs = new bool[N];
        parent = new int[N];
        level = new int[N];

        for( int i = 0; i < N; i++){
            visitedbfs[i] = 0;
            parent[i] = 0;
            level[i] = 0;
        }
        //Marca a raiz como marcado
        visitedbfs[value] = true;
        parent[value] = -1;
        level[value] = 0;
        //Cria a fila e coloca o valor na fila
        list<int> Q;
        //list<int>::iterator i;
        Q.push_back(value);
        
        int v;
        //Enquanto Q não estiver vazia
        while(!Q.empty()){
            //retira v de Q
            v = Q.front();
            Q.pop_front();
            cout << v;
            //para todo vizinho w de v:
            for(int i = 0; i < N+1; i++){
                //Se não estiver nos0 visitados
                if(visitedbfs[i] == 0 && AdjMat[v][i] == 1){
                    //Marca como visitado
                     visitedbfs[i] = true;
                     //Coloca no Q
                     Q.push_back(i);
                     parent[i] = v;
                     level[i] = level[v] + 1;
                }
            }
        }
    
        for(int i = 0; i < N; i++){
            cout << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
        }    
            
    }
    
    void CheckLevel(int n){
        cout << "The level of " << n << " is " << level[n] << endl;
    }
    
    void CheckParent(int n){
        cout << "The parent of " << n << " is " << parent[n] << endl;
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
    
    

};

class AdjListGraph{
private:
    
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
    vector<int> parentdfs;
    vector<int> leveldfs;
    list<int> components;

public:
    int N;
    AdjListGraph(string str){
        this->str = str;
        this->M = 0;
        string s = str.substr(2);
        //cout << s;
        vector<int> nums;
        
        stringstream stream(str);
        while(1) {
            int n;
            stream >> n;
            if(!stream)
                break;
            //Num.push_back(n);
            nums.push_back(n);
        }
        this-> str = str;
        N = nums[0] + 1;
        cout << N;
        L = new list<int>[N];
        int len = nums.size();
        int x,y = 0;
        for(int i = 1; i < len; i = i + 2){
            x = nums[i];
            int k = i + 1;
            y = nums[k];
            L[x].push_back(y);
            L[y].push_back(x);
        }
        M = (len - 1)/2;
    }


    void printList(){
        for(int i = 0; i < N+1; i++){
                cout << "N: " << i << " -> | ";
            for(int x:L[i]){
                cout << x <<" | ";
            }
            
            cout << endl;
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
        
        for(int i = 0; i < N; i++){
            cout << "number: " << i << " / level:" << level[i] << " / parent: " << parent[i] << endl;
        }
    }

    void DFS(int v, bool visited[]){
        components.push_back(v);
        visited[v] = true;
        if (parentdfs.empty() == true){
            parentdfs[v] = -1;
            leveldfs[v] = 0; 
        }  

        
        // Recur for all the vertices adjacent
        // to this vertex
        list<int>::iterator i;
        for (i = L[v].begin(); i != L[v].end(); ++i){
            
            if (!visited[*i]){
                parentdfs[*i] = v;
                leveldfs[*i] = level[v] + 1;
                DFS(*i, visited);
            }
        }
    }

    void connectedComponents(){
        
        // Mark all the vertices as not visited
        int numcc = 0;
        bool* visitedcc = new bool[N];
        for (int v = 0; v < N; v++){
            visitedcc[v] = false;
        }
    
        for (int v = 0; v < N; v++) {
            if (visitedcc[v] == false) {
                // print all reachable vertices
                // from v
                numcc++;
                DFS(v,visitedcc);
                cout << "A componente tem " << components.size() << " vertices" <<"\n";
                components.sort();
                cout << "Componentes: ";
                for (auto const &i: components) {
                    cout << i << " ";
                }
                components.clear();
                parentdfs.clear();
                leveldfs.clear();


                cout << "\n";
            }
        }
        cout << "O grafo possui " << numcc << " componentes conexas" << endl;
        delete[] visitedcc;
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
    
    void CheckLevelBFS(int n){
        cout << "The level of " << n << " is " << level[n] << endl;
    }
    
    void CheckParentBFS(int n){
        cout << "The parent of " << n << " is " << parent[n] << endl;
    }
    void CheckLevelDFS(int n){
        cout << "The level of " << n << " is " << leveldfs[n] << endl;
    }
    
    void CheckParentDFS(int n){
        cout << "The parent of " << n << " is " << parentdfs[n] << endl;
    }
};

//Para usar chame a BFS partindo da raiz que deseja.
//Logo em seguida use CheckParent ou CheckLevel para ver o
//pai ou o nível, respectivamente. Caso chame a BFS ou Diameter ou
//distância este valor mudará.

int main(){

    string s = "11\n11 10\n3 4\n 5 7\n10 2\n1 3\n1 11\n10 1";

    //AdjMatrGraph g(s);
    //g.printMat();
    
    //g.BFS(3);

    AdjListGraph g(s);
    //g.printList();
    //g.connectedComponents();
    //g.find_degrees();
    //g.Distance(4,3);
    //g.Diameter();
    g.BFS(3);
    //g.CheckLevelBFS(3);
    //g.CheckParentDFS(3);
    std::ifstream myfile; 
    myfile.open("Grafo.txt");
    std::string myline;
    
    return 0;
}
