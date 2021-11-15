#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

// Fonction qui cherche une station dans le graph

int rechercherStationParNom(Graph* graph, char* nom)
{
	int index = 0; 
	while (index < graph->totalStations) 
	{
		char* stationName = graph->stations[index]->nom; 

		if (strcmp(stationName, nom) == 0) 
		{
			break;
		}

		index++;
	}

	if (index < graph->totalStations) 
	{
		return index;
	}
	else
	{
		return -1; 
	}
}


int rechercherVoisin(Station* depart, Station* arrivee, char* nomLigne)
{
	int index = 0; 

	while (index < depart->totalVoisins)
	{
		Voisin* voisin = depart->voisins[index];

		if (strcmp(voisin->voisin->nom, arrivee->nom) == 0 )
		{
			if(strcmp(nomLigne, voisin->nomLigne) == 0) break;
			
		}

		index++;
	}

	if (index < depart->totalVoisins)
	{
		return index;
	}
	else
	{
		return -1;
	}

}


// Fonction qui cherche le : voisin-->nom d'un sommet (station)
Voisin* trouverVoisin(Station* depart, Station* arrivee)
{
	int index = 0; 

	while (index < depart->totalVoisins)
	{
		Voisin* voisin = depart->voisins[index]; 
		
		if (strcmp(voisin->voisin->nom, arrivee->nom) == 0) 
		{
			return voisin; 
		}

		index++;
	}
}

// Fonction qui va ajouter une station au graph (sommet)

void ajouterStation(Graph* graph, char* nom)
{

	int newAllocation;
	Station** newStations;
	int i;
	Station* nouvelleStation = (Station*)(malloc(sizeof(Station)));

	nouvelleStation->nom = nom;

	nouvelleStation->voisins = (Voisin**)(malloc(2 * sizeof(Voisin*)));
	nouvelleStation->allocatedVoisins = 2; 
	nouvelleStation->totalVoisins = 0;
	nouvelleStation->visited = 0;

	if (graph->totalStations < graph->allocatedStations)
	{
		graph->stations[graph->totalStations++] = nouvelleStation;
	}
	else
	{
		newAllocation = 2 * graph->allocatedStations;

		graph->allocatedStations = newAllocation;

		newStations = (Station**)(malloc(newAllocation * sizeof(Station*)));

		for (i = 0; i < graph->totalStations; i++)
		{
			newStations[i] = graph->stations[i];
		}

		free(graph->stations);
		graph->stations = newStations;

		graph->stations[graph->totalStations++] = nouvelleStation;
	}
	
}

// Fonction qui ajoute les voisins de chaque station 
void ajouterVoisin(Station* depart, Station* arrivee, char * nomLigne, int temps)
{
	Voisin* newVoisin = (Voisin*)(malloc(sizeof(Voisin)));
	newVoisin->nomLigne = nomLigne;
	newVoisin->tmp_parcours = temps;
	newVoisin->voisin = arrivee;
	Voisin** newAllocation;
	int i;

	if (depart->allocatedVoisins < depart->totalVoisins + 1)
	{
		newAllocation = (Voisin**)(malloc(sizeof(Voisin*) * 2 * depart->allocatedVoisins));
		
		depart->allocatedVoisins = 2 * depart->allocatedVoisins;

		for (i = 0; i < depart->totalVoisins; i++)
		{
			newAllocation[i] = depart->voisins[i];
		}

		free(depart->voisins);
		depart->voisins = newAllocation;
	}

	depart->voisins[depart->totalVoisins++] = newVoisin;
	
}


// Fonction qui fait les liens entre les stations (arrêtes)
void ajouterLien(Graph* graph,  char* depart,  char* arrivee, char* nomLigne, int temps)
{
	//rechercher la station dans le graph 
	int stationDepartIndex = rechercherStationParNom(graph, depart); 
	int stationArriveeIndex = rechercherStationParNom(graph, arrivee); 
	
	char * depart_cpy = (char*)(malloc(sizeof(char) * strlen(depart) + 1));
	char * arrivee_cpy = (char*)(malloc(sizeof(char) * strlen(arrivee) + 1));
	char * nomLigne_cpy;
	
	strcpy(depart_cpy, depart);
	strcpy(arrivee_cpy, arrivee);

	Station* stationDep;
	Station* stationArr;

	// ajout de la station --> pas présente 
	if (stationDepartIndex == -1) 
	{
		
		ajouterStation(graph, depart_cpy);
		stationDepartIndex = rechercherStationParNom(graph, depart_cpy);		
	}
	else
	{
		free(depart_cpy);
	}
	

	stationDep = graph->stations[stationDepartIndex];

	if (stationArriveeIndex == -1)
	{
		ajouterStation(graph, arrivee_cpy);
		stationArriveeIndex = rechercherStationParNom(graph, arrivee_cpy);
	}
	else
	{
		free(arrivee_cpy);
	}


	stationArr = graph->stations[stationArriveeIndex];

	if (rechercherVoisin(stationDep, stationArr, nomLigne) == -1)
	{
		nomLigne_cpy =  (char*)(malloc(sizeof(char) * strlen(nomLigne) + 1));
		stpcpy(nomLigne_cpy, nomLigne);
		ajouterVoisin(stationDep, stationArr, nomLigne_cpy, temps);
	}
	
	if (rechercherVoisin(stationArr, stationDep, nomLigne) == -1)
	{
		nomLigne_cpy =  (char*)(malloc(sizeof(char) * strlen(nomLigne) + 1));
		stpcpy(nomLigne_cpy, nomLigne);
		ajouterVoisin(stationArr, stationDep, nomLigne_cpy, temps);
	}
	
}

// Fonction qui renvoie un Index (le + petit)
int parcourIndex(int* tab, int length, Graph* g) 
{
	int i;

	int min = INT_MAX;
	int minIndex = -1;

	for (i = 0; i < length; i++)
	{
		if (tab[i] < min && g->stations[i]->visited == 1)
		{
			min = tab[i];
			minIndex = i;
		}
	}

	return minIndex;
}

// Fonction inversant les vlr d'un tab 

void inverseStation(Station** tab, int length) 
{

	int dep = 0;
	int fin = length - 1;
	Station* tmp;

	while (dep < fin)
	{ 
		tmp = tab[dep]; 
		tab[dep] = tab[fin];
		tab[fin] = tmp; 

		dep++;
		fin--;
	}
}

// Fonction qui complète ---> Station** dijkstra

void dijkstra_chemin(Graph* g, Station* depart, Station* arrivee, Station** chemin) 
{
	Station** cheminFinal = (Station**)(malloc(sizeof(Station*) * g->totalStations)); 
	Station* currStation; 
	Voisin* voisin;
	char* nomLigne = "";
	int taille = 0; 
	int i;
	int indexArr = rechercherStationParNom(g, arrivee->nom); 
	int ligneTime = 0; 
	int totalTime = 0;

	currStation = chemin[indexArr]; 
	cheminFinal[taille++] = arrivee; 
	cheminFinal[taille++] = currStation; 
	while (currStation != depart) 
	{
		indexArr = rechercherStationParNom(g, currStation->nom); 
		currStation = chemin[indexArr]; 

		cheminFinal[taille++] = currStation; 
	}
// mise en ordre du chemin 
	inverseStation(cheminFinal, taille);
									
// Affichage du chemin final 

	for (i = 0; i < taille-1; i++) 
	{
		
		voisin = trouverVoisin(cheminFinal[i], cheminFinal[i + 1]); 

		totalTime += voisin->tmp_parcours; 

		if (i == 0) 
		{
			nomLigne = voisin->nomLigne; 
			printf("Prendre la ligne %s de %s jusqu'a ", nomLigne, depart->nom);
			ligneTime += voisin->tmp_parcours; // affichage du temps de correspondance pour la ligne 
		}
		else
		{ // Dans le cas ou la ligne du voisin --> != . On change de correspondance --> ligne 
			if (strcmp(nomLigne, voisin->nomLigne) != 0)
			{
			
				nomLigne = voisin->nomLigne; 

				printf(" %s (corresponde : %d minutes). \n Puis prendre la ligne %s jusqu'a ", cheminFinal[i]->nom, ligneTime, voisin->nomLigne);
				ligneTime = voisin->tmp_parcours;
			}
			else
			{
				ligneTime += voisin->tmp_parcours;
			}
		}

	}
	
	printf("%s (correspondance : %d minutes). \n Vous etes arrive ! Temps total : %d minutes\r\n", arrivee->nom, ligneTime, totalTime);
	
	free(cheminFinal);

}


// Fonction qui implémente l'algo de dijkstra
Station** dijkstra(Graph *g, Station* depart, Station* arrivee)
{

	int* distance = (int*)(malloc(sizeof(int) * g->totalStations));
	Station ** chemin = (Station**)(malloc(sizeof(Station*) * g->totalStations)); 

	int i;
	int depIndex = rechercherStationParNom(g, depart->nom); 
	int arrIndex = rechercherStationParNom(g, arrivee->nom);

	int minIndex;

	Voisin* currVoisin; 
	int voisinIndex;

	for (i = 0; i < g->totalStations; i++)
	{
		if (i != depIndex)
		{
			distance[i] = INT_MAX; 
		}
		else
		{
			distance[i] = 0; 
		}

		chemin[i] = NULL;
		
	}

	g->stations[depIndex]->visited = 1; 

	while (g->stations[arrIndex]->visited != 2) 
	{
		minIndex = parcourIndex(distance, g->totalStations, g); 
// nb total de voisin de la station indexé qui a le + petit index
		for (i = 0; i < g->stations[minIndex]->totalVoisins; i++) 
		{ // chercher chaque voisin de i de la station indexé 
			currVoisin = g->stations[minIndex]->voisins[i]; 
			voisinIndex = rechercherStationParNom(g, currVoisin->voisin->nom); 

			if (currVoisin->voisin->visited != 2)
			{// ajout de station dans le chemin 
				if (distance[voisinIndex] > distance[minIndex] + currVoisin->tmp_parcours)
				{ 
					distance[voisinIndex] = distance[minIndex] + currVoisin->tmp_parcours; 
					chemin[voisinIndex] = g->stations[minIndex]; 
					
				}
				
				currVoisin->voisin->visited = 1;
			}
		
		}

		g->stations[minIndex]->visited = 2; 

	}

	free(distance);

	return chemin; 
}

Graph* initGraph()
{
	
	Graph*  graph = (Graph*)(malloc(sizeof(Graph)));
	graph->totalStations = 0;
	graph->allocatedStations = 400;
	graph->stations = (Station**)(malloc(400 * sizeof(Station*)));
	
	return graph;
}

void nettoie_Graph(Graph* g)
{
	int i = 0;
	int j = 0;
	Station* currStation; 
	Voisin* currVoisin; 

	for (i = 0; i < g->totalStations; i++)
	{
		currStation = g->stations[i];
		
		for (j = 0; j < currStation->totalVoisins; j++)
		{
			currVoisin = currStation->voisins[j];
			free(currVoisin->nomLigne);
			free(currVoisin);
		}

		free(currStation->nom);
		free(currStation->voisins);
		free(currStation);
	}
	
	free(g->stations);
}

