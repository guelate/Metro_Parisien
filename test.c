#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(){


char* deb;
char* fin;
unsigned int len;
char* temps_str;
int temps;
char* nomLigne;
char* ligne = "1 (3) L1 :La Defense<->Esplanade de La Defense<->Pont de Neuilly<->Les Sablons<->Porte Maillot<->Argentine<->Charles de Gaulle - Etoile<->George V<->Franklin-D. Roosevelt<->Champs Elysees - Clemenceau<->Concorde<->Tuileries<->Palais Royal - Musee du Louvre<->Louvre - Rivoli<->Chatelet<->Hotel de Ville<->Saint-Paul<->Bastille<->Gare de Lyon<->Reuilly - Diderot<->Nation<->Porte de Vincennes<->Saint-Mande - Tourelle<->Berault<->Chateau de Vincennes";

deb = strchr(ligne,'(');
deb++;
//printf("%s\n",deb);
fin = strchr(ligne,')');
//printf("%s\n",fin);
len = fin - deb;
//printf("%d\n",len);

temps_str = (char*)(malloc(sizeof(char) * 10));
//temps_str[0] = '0';
temps_str[len] = '\0'; // chaine à 2 élément vlr 0 et 1 = \n

strncpy(temps_str, deb, len);
temps = atoi(temps_str);
deb = ++fin;
//printf("%s\n",deb);

fin = strchr(ligne, ':'); 
//printf("%s\n",fin);
len = fin - deb;
//printf("%d\n",len);

nomLigne = (char*)(malloc(sizeof(char) * 10));
strncpy(nomLigne, deb, len);
nomLigne[len] = '\0';

deb = ++fin;
//printf("%s\n",deb);
fin = strstr(deb, "<->"); //<->Esplanade de La Defense<->Pont de Neuilly
//printf("%s\n",fin);
len = fin - deb;
//printf("%d\n",len);

deb = fin + 3;


fin = strstr(deb, "<->");
len = fin - deb;
printf("%d\n",len);


}















/*
char str1[] = "00"; 
char str2[] = "00";
int i = strcmp(str1,str2);

char* tmp = (char*)(malloc(sizeof(char) * 50));

fgets(tmp, 50, stdin); // commenté ici 
int i = strcspn(tmp, "\r\n");
tmp[i] = 3;


taille d'une chaine avant qu'on détecte l'élément d'une autre chaine 
int size = strcspn(str1, str2); 
printf("%c\r",str1[2]);
*/