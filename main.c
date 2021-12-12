#include <stdio.h>
#include <stdlib.h>

int main() {
    int vertices;
    char filename[50] = "Grafo.txt";
    char text;
    char c[1];
    FILE *fptr;

     // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Não foi possível abrir o arquivo \n");
        exit(0);
    }
    

    fscanf(fptr, "%[^\n]", c);
    vertices = c;



    // Read contents from file
    text = fgetc(fptr);
    while (text != EOF)
    {
        printf ("%c", text);
        text = fgetc(fptr);
    }
  
    fclose(fptr);
    printf(vertices);
    return 0;

}
