#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//indiquer la taille de la matrice avant de lancer le programme
int SizeTab=6;
int Tab[6+1][6+1]={{0}};


//Les variables du programme. La flemme de les placer en parametre
int i,y,j,z,valeur,min,indiceMini,Sommemini=0,CoutTotal=0;
int ValRegret=0, RegretMax=0;
int CoordRegety=0,CoordRegetx=0;


//Nom du fichier a lire
char chaine[] = "data/Classeur3Copie.csv";

void decalerTableau(){

    //décalage colonne
    for (i = CoordRegety; i < SizeTab; ++i) {
        for (j = 0; j < SizeTab; ++j) {
            Tab[j][i]=Tab[j][i+1];
        }
    }
//décalage ligne
    for (i = CoordRegetx; i < SizeTab; ++i) {
        for (j = 0; j < SizeTab; ++j) {
            Tab[i][j]=Tab[i+1][j];
        }
    }

}
void lecturefichier(){
	//fonction qui permet de lire le fichier
    FILE* fichier = NULL;
    //fichier = fopen("annexe1bis.csv", "r+");
    fichier = fopen(chaine, "r+");
    if (fichier != NULL) {
        // On peut lire et écrire dans le fichier
        for (i = 0; i <SizeTab;++i) {
            for (y = 0; y <SizeTab; ++y) {
                fscanf(fichier,"%d;",&Tab[i][y]);
                printf("%d ",Tab[i][y]);
            }
            printf("\n");
        }
        fclose(fichier);
        printf("\n");
    }
    else {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s",chaine);
        exit(EXIT_FAILURE);
    }
}

void afficherTableau(){
    printf("\n");
    for (i=0; i<SizeTab+1; ++i) {
        for (j = 0; j < SizeTab+1; ++j) {
            printf("%d ",Tab[i][j]);
        }
        printf("\n");

    }
}

void RechercheReduction(){
    // recherche des minimuns et reduction de la matrice
    for (i = 1; i < SizeTab; ++i) {
        for (j= 1; j <SizeTab; ++j) {
            valeur=Tab[i][j];

            if (j==1){
                if (valeur==-1) {
                    min=Tab[i][j+1];
                    indiceMini=j+1;
                } else{
                    min=valeur;
                    indiceMini=j;
                }

            } else if (valeur<min && valeur!=-1){
                min=valeur;
                indiceMini=j;
            }
        }
        //printf("La valeur mini est %d a l'indique %d\n", min,indiceMini);
        for (j= 1; j <SizeTab; ++j) {
            if (Tab[i][j]!=-1)
                Tab[i][j]=Tab[i][j]-min;
        }
        Sommemini=Sommemini+min;
    }
    afficherTableau();
// recherche des minimuns et reduction de la matrice colonne
    printf("\n");
    printf("\n");
    for (i = 1; i < SizeTab; ++i) {
        for (j= 1; j <SizeTab; ++j) {
            valeur=Tab[j][i];
            if (j==1){
                if (valeur==-1) {
                    min=Tab[j+1][i];
                    indiceMini=j+1;
                } else{
                    min=valeur;
                    indiceMini=j;
                }
            } else if (valeur<min && valeur!=-1){
                min=valeur;
                indiceMini=j;
            }
        }
        //printf("La valeur mini est %d a l'indique %d\n", min,indiceMini);
        for (j= 1; j <SizeTab; ++j) {
            if (Tab[j][i]!=-1)
                Tab[j][i]=Tab[j][i]-min;
        }
        Sommemini=Sommemini+min;

    }
}

void ecritureFichier(){
    FILE* fichier = NULL;

    fichier = fopen(chaine, "w");

    if (fichier != NULL)
    {
        // On l'écrit dans le fichier
        for (i=0; i<SizeTab; ++i) {
            for (j = 0; j < SizeTab; ++j) {
                fprintf(fichier,"%d;",Tab[i][j]);
            }
            fprintf(fichier,"\n");
        }
        fclose(fichier);
    }
}

int main() {
    int flag=1;
    int TrajetSelectDepart=0,TrajetSelectArrive=0;

    lecturefichier();

    while(flag==1) {
        Sommemini=0;
    RechercheReduction();

    printf("La sommu cup est %d \n", Sommemini);
        afficherTableau();

    //calcule de la valeur du noeu
    printf(" \n  \nCalcul du Regret \n");
    for (i=1; i<SizeTab; ++i) {
        for (j = 1; j < SizeTab; ++j) {

            ValRegret=0;
            if (Tab[i][j]==0) {
                //printf("Detection d'un zero pour i=%d,j=%d \n",i,j);

                //recherche mini dans la collone
                for (y = 1; y < SizeTab; ++y) {
                    //printf("valeur %d \n", valeur);
                    if (y!=i) {
                        valeur = Tab[y][j];
                        if (y == 1) {
                            if (valeur == -1) {
                                min = Tab[y + 1][j];
                            } else {
                                min = valeur;
                            }
                        }else if (valeur<min && valeur!=-1){
                            min=valeur;
                            indiceMini=j;
                        }
                    }
                }
                //printf("Mini colonne %d \n", min);
                ValRegret = ValRegret + min;

                //recherche mini dans la ligne
                for (y = 1; y < SizeTab; ++y) {
                    //printf("valeur %d \n", valeur);
                    //printf("affichge i %d y %d ",i,y);

                    if (j!=y) {
                        //printf("Valeur %d coordonnee y=%d j=%d\n",Tab[i][y],i,y);
                        valeur = Tab[i][y];
                        if (y==1) {
                            //printf("pour y = 0\n");
                            if (valeur == -1) {
                                min = Tab[i][y+1];
                            } else {
                                min=valeur;
                            }
                        }else if (valeur<min && valeur!=-1){
                            min=valeur;
                            indiceMini=j;
                        }
                    }
                }
                ValRegret = ValRegret + min;
                //printf("La valeur mini est %d \n", min);
                //printf("Le regret est de %d pour le point %d %d\n\n", ValRegret, i,j);

                //printf("Le regret est de %d pour le point %d %d\n", ValRegret,i,j);
                if (RegretMax<ValRegret){
                    RegretMax=ValRegret;
                    CoordRegety=j;
                    CoordRegetx=i;
                    TrajetSelectDepart=Tab[j][0];
                    TrajetSelectArrive=Tab[0][i];
                }
            }
        }


    }
    printf("\nLe regret max est %d de coordonnee %d;%d\n",RegretMax,CoordRegetx,CoordRegety);
        CoutTotal=Sommemini+CoutTotal;
        printf("Cout totoal = %d\n",CoutTotal);

    decalerTableau();
    printf("La somme supprimer est %d\n",Sommemini);
    SizeTab=SizeTab-1;
        afficherTableau();


        printf("La trajet selectionner est %d %d\n",TrajetSelectArrive,TrajetSelectDepart);

    //TODO  suppresion des sous tournées
    if (SizeTab==2){
        flag=0;
    }
        flag=0;
        ecritureFichier();
    }




    printf("Cout totoal de la mort= %d",CoutTotal);
    return 0;
}