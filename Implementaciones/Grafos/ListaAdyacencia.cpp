#include <iostream>
#include <vector>
#include <cstring> //memset
#include <queue>

using namespace std;

//Número máximo de vertices que el problema puede requerir
//+1 Para indexar desde uno
const int MAXV = 100 + 1;
//Infinito para dijkstra : 2^30
const int INF = 1 << 30;

//Parejas (DistanciaRequerida, nodoAlQueVoy)
vector<pair<int,int> > AdjList[MAXV];
bool visited[MAXV];
//Arreglo de distancias para dijkstra
int distances[MAXV];

//ignoren esto
void dfs(int root);
void bfs(int root);
void dijkstra(int s);


int main() {
    //Numero de vertices y aristas que el problema requiere
    int V, E; 
    cin >> V >> E;    
    
    //Inicializar el grafo (Que ningun vertice tenga aristas)
    for(int i = 0; i < MAXV; i++)
        AdjList[i].clear();
            
    //Añadir aristas
    int from, to, weight;
    for(int i = 0; i < E; i++) {
        cin >> from >> to >> weight;    
        //Crear y agregar arista from -> to con peso weight
        //En la lista de hijos del nodo from
        AdjList[from].push_back(make_pair(weight, to));
        // Si es no dirigido, agregar arista to -> from con:
        // AdjList[to].push_back(make_pair(weight, from));
    }

    //Ejemplo: Imprimir los hijos de todos los nodos
    //Indexando desde 1
    cout << "Contenido del grafo:\n";
    for(int node = 1; node <= V; node++) {
        cout << node << ": ";
        //Todos los elementos en la lista de hijos
        for(int i = 0; i < AdjList[node].size(); i++) {
            pair<int,int> child = AdjList[node][i];
            cout << child.second << " ";
        }
        cout << endl;
    }  
    int root = 1;
    //Ejemplo: Llamar dfs desde un nodo    
    cout << "Dfs:\n";    
    //Poner en falso el arreglo de visitados antes de la llamada
    memset(visited, false, sizeof(visited));
    dfs(root);
    
    //Ejemplo: Bfs desde un nodo
    cout << "Bfs: \n";
    memset(visited, false, sizeof(visited));
    bfs(root);
    
    //Ejemplo: Dijkstra
    cout << "Distancia 1->5\n";
    dijkstra(1);
    //Camino mas corto de 1 a 5
    cout << distances[5] << endl;
}

void dfs(int root) {
    //Para ver el recorrido
    cout << root << endl; 
    
    visited[root] = true;
    //Dfs desde los hijos de root
    for(int i = 0; i < AdjList[root].size(); i++) {
        pair<int,int> child = AdjList[root][i];
        //Si no lo ha visitado
        if(!visited[child.second]) dfs(child.second);
    }
}

void bfs(int root) {
    queue<pair<int,int> > q;
    pair<int, int> s = make_pair(0, root);
    q.push(s);
    visited[s.second] = true;    
    while(!q.empty()) {
        //Sacar siguiente elemento
        pair<int,int> current = q.front();
        q.pop();
        cout << current.second << endl;
        //Todos los hijos no visitados a la cola
        for(int i = 0; i < AdjList[current.second].size(); i++) {
            pair<int,int> child = AdjList[current.second][i];
            if(!visited[child.second]) {
                visited[child.second] = true;
                q.push(child);                                                
            }
        }
    }
}

void dijkstra(int s) {
  	//Inicializar todas las distancias en infinito
  	for(int i = 0; i < MAXV; i++) distances[i] = INF;
  	// Creamos una priority queue de enteros que saque primero el menor valor
	priority_queue <pair<int,int>, vector<pair<int,int> > , greater<pair<int, int> > > q;
	// Insertamos el nodo de origen s con distancia 0
  	q.push(pair<int,int>(0, s));
  	while(!q.empty()) {
      	// Sacamos el nodo con menor distancia
   		int curr_distance = q.top().first;
        int curr_node = q.top().second;
		q.pop();
      	// Si la distancia que estoy procesando es mayor a la que ya habia encontrado, la ignoro
      	// Esta linea sirve para optimizar el algoritmo
      	if(curr_distance > distances[curr_node]) continue;
        //Si la distancia era menor entonces miro qué distancias de mis hijos puedo mejorar
      	for(int i = 0; i < AdjList[curr_node].size(); i++) {
          	int next_node = AdjList[curr_node][i].second; 
          	int next_weight = AdjList[curr_node][i].first;
          	// Si puedo mejorar la distancia a ese nodo, lo añado a la cola
          	if(distances[next_node] > curr_distance + next_weight) {
              // Actualizo la distancia del nuevo nodo
              distances[next_node] = curr_distance + next_weight;
              q.push(make_pair(distances[next_node], next_node));
            }
        }
    }
  	//El arreglo de distancias ahora contiene la distancia
  	//Mas corta de s a cualquier nodo, o INF si no hay camino
}