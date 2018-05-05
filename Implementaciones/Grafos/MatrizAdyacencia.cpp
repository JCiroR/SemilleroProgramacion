#include <iostream>
#include <algorithm>

using namespace std;

//Número máximo de vertices que el problema puede requerir
//+1 Para indexar desde uno
const int MAXV = 100 + 1;

int main() {
    //Numero de vertices y aristas que el problema requiere
    int V, E; 
    cin >> V >> E;
    int AdjMat[MAXV][MAXV];
    //Inicializar el grafo en -1    
    for(int i = 0; i < MAXV; i++)
        for(int j = 0; j < MAXV; j++)
            AdjMat[i][j] = -1;
    //Añadir aristas    
    int from, to, weight;
    for(int i = 0; i < E; i++) {
        cin >> from >> to >> weight;
        //Agregar arista from -> to con peso weight
        AdjMat[from][to] = weight;
        // Si es no dirigido, agregar arista to -> from con: 
        // AdjMat[to][from] = weight;
    }
    //Ejemplo: Imprimir los hijos de todos los nodos
    //Indexando desde 1    
    for(int node = 1; node <= V; node++) {
        cout << node << ": ";
        for(int i = 1; i <= V; i++) {
            //Si hay una arista node -> i
            if(AdjMat[node][i] != -1)
                cout << i << " ";
        }
        cout << endl;
    }
}