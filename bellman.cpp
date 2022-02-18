#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>
#include <limits.h>


using namespace std;

class AdjListGraphDir{
private:

    int M = 0;
    string str;
    vector <float> edges;

public:
    int N;
    AdjListGraphDir(string str){
        this->str = str;
        this->M = 0;
        vector<float> nums;
        
        stringstream stream(str);
        while(1) { // Pega os números entre os espaços
            float n;
            stream >> n;
            if(!stream)
                break;
            nums.push_back(n);
        }
        
        N = nums[0] + 1;
        
        int len = nums.size();
        M = (len - 1)/3;
        
        this -> edges;         
        for(int i = 1; i < len; i++){
            edges.push_back(nums[i]);
        }
        
    }
    
    void printVec(){
        for (int i = 0; i < M*3; i++){
            cout << edges[i] << ",";
        }
        cout << "\n" << M << " and " << edges.size();
    }
    
    void bellman(int src){
        
        float dist[N]; 
    
        for (int i = 0; i < N; i++){
            dist[i] = INT_MAX;
    
        }

        dist[src] = 0;
        for (int count = 0; count <= N - 1; count++) {
            for (int i = 0; i < edges.size(); i = i + 3){
                    
                    int u = edges[i];
                    int vertice = edges[i + 1];
                    float weight = edges[i + 2];
                   
                    if (dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                        dist[vertice] = dist[u] + weight;
                    }
            }

        }
        
        
        for (int i = 0; i < edges.size(); i = i + 3){
                    
                int u = edges[i];
                int vertice = edges[i + 1];
                float weight = edges[i + 2];
               
                if (dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                    cout << "Tem ciclo negativo!" << endl;
                }
        }
        cout <<"Vertice \t Distância da Origem" << endl;
        for (int i = 0; i < N; i++){
            cout  << i << " \t\t"<<dist[i]<< endl;
        }

    }
};

int main(){

    string s = "11\n11 10 1\n3 4 2\n5 7 3\n10 2 4\n1 3 5\n1 11 6\n10 1 7";
    string a = "4\n0 1 1\n1 2 -1\n2 3 -1\n3 0 -1";
    
    AdjListGraphDir f(a);
    f.bellman(0);

    return 0;
}
