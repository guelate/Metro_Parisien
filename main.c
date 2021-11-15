#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define MAX_BUFFER_SIZE 1000


// Fonction qui va lire les lignes du fichier : metros.txt
void lireLigne(Graph* graph, char* ligne)
{
    char* debut; 
    char* fin; 
    char* station; 
    char* StationVu; 
    char* nomLigne;
    char* temps_str;
    int temps;
    unsigned int taille; 


    debut = strchr(ligne, '(');
    debut++; // 3) L1 :La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<-> ...
    fin = strchr(ligne, ')'); // ) L1 :La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...

    taille = fin - debut;// 1

    temps_str = (char*)(malloc(sizeof(char) * 10));
    temps_str[taille] = '\0'; 
    
    strncpy(temps_str, debut, taille); 

    temps = atoi(temps_str); 

    debut = ++fin; // L1 :La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...

    fin = strchr(ligne, ':'); // :La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...

    taille = fin - debut; // 4

    nomLigne = (char*)(malloc(sizeof(char) * 10)); 

    strncpy(nomLigne, debut, taille); 

    nomLigne[taille] = '\0'; 

    debut = ++fin; // La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...
    fin = strstr(debut, "<->"); // <->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...
    taille = fin - debut;// 10



    StationVu = NULL;

    while (fin != NULL) 
    {
        
        station = (char*)(malloc(sizeof(char) * 50));
		

        strncpy(station, debut, taille); 

        station[taille] = '\0';


        if (StationVu != NULL) 
        {
            ajouterLien(graph, StationVu, station, nomLigne, temps);
        }


        debut = fin + 3;//Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot ...
        fin = strstr(debut, "<->"); //<->Pont de Neuilly ..
        taille = fin - debut;// 23 

        if (fin == NULL) 
        {
            taille = strlen(debut);
            strncpy(station, debut, taille);
            station[taille] = '\0';
            ajouterLien(graph, StationVu, station, nomLigne, temps);
        }

		free(StationVu);
        StationVu = (char *)(malloc(sizeof(char) * strlen(station) + 1)); 

        
        strcpy(StationVu, station);
		free(station);
		
    }

	free(StationVu);
	free(temps_str);
    free(nomLigne);
}

//Ouvrir fichier metros dans l'onglet 
//Fonction qui permet d'entrer les stations 

Station* lireStation(Graph * g) 
{
    char* tmp = (char*)(malloc(sizeof(char) * 50));

    fgets(tmp, 50, stdin); 
    tmp[strcspn(tmp, "\r\n")] = 0; 

    int index = rechercherStationParNom(g, tmp); 

    while (index == -1) 
    {
        printf("La station n'existe pas , veuillez reessayer\n"); 
        
        fgets(tmp, 50, stdin); 
        tmp[strcspn(tmp, "\r\n")] = 0; 
        index = rechercherStationParNom(g, tmp);
    }

	free(tmp);
	
    return g->stations[index]; 
}

int main(int argc, char * argv[]){
  
    FILE* fichier;
    Station* depart;
    Station* arrivee;

    fichier = fopen("metros.txt", "r");
    if (fichier == NULL) {
        printf("Erreur\n");
    
    }

    Graph* graph = initGraph();
	
// Lecture de metros.txt ligne/ligne 
    while (!feof(fichier)) 
    {
        char* buffer = (char*)(malloc(sizeof(char) * MAX_BUFFER_SIZE));

        fgets(buffer, MAX_BUFFER_SIZE, fichier);

        lireLigne(graph, buffer); 
		
		free(buffer);
    }
    
    
    printf("Veuillez entrer la station de depart\n");
    depart = lireStation(graph);
    printf("Veuillez entrer la station d'arrivee\n");
    arrivee = lireStation(graph);
    
    Station ** chemin = dijkstra(graph, depart, arrivee);  

    dijkstra_chemin(graph, depart, arrivee, chemin); 

    free(chemin);  

    nettoie_Graph(graph);
	
	free(graph);

    fclose(fichier);

	return 0;
}