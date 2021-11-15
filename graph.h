#ifndef GRAPH_H
#define GRAPH_H

typedef struct Station Station; // sation --> sommet du graph
typedef struct Voisin Voisin; // voisin des stations 
typedef struct Graph Graph; // struc du graph

typedef struct Station{

	char* nom;

	int totalVoisins;
	int allocatedVoisins; 

	int visited; 

	Voisin** voisins; 

} ;

typedef struct Voisin{

	char* nomLigne;
	int tmp_parcours;
	Station* voisin;

} ;

typedef struct Graph{
	Station** stations;
	int totalStations;
	int allocatedStations; 
} ;

// Fonction agissant sur le graph 

Graph* initGraph(); 
void ajouterLien(Graph* graph, char* depart, char* arrivee, char* nomLigne, int temps); 
void ajouterVoisin(Station* depart, Station* arrivee, char* nomLigne, int temps); 
void ajouterStation(Graph* graph, char* nom); 
int rechercherStationParNom(Graph* graph, char* nom); 
Station** dijkstra(Graph* g, Station* depart, Station* arrivee);
int parcourIndex(int* tab, int length, Graph* g); 
void dijkstra_chemin(Graph* g, Station* depart, Station* arrivee, Station** chemin); 
void inverseStation(Station** arr, int length); 
void nettoie_Graph(Graph* g); 

// Fonction supp --> utiliser par les fonction --> aggissant sur le graph

int rechercherVoisin(Station* depart, Station* arrivee, char* nomLigne);
Voisin* trouverVoisin(Station* depart, Station* arrivee);

#endif 
