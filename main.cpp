#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream myfile; 
    myfile.open("Grafo.txt");
    std::string myline;

    if (myfile.is_open()) { // Checando se arquivo está aberto
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