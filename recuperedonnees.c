#include <stdio.h>

/*********************************************************/
/* Affichage matrice                                     */
/* l : Donnee - Nombre de lignes à afficher              */
/* c : Donnee - Nombre de colonnes à afficher            */
/* Mat : D/R - Matrice                                */
/*********************************************************/
void matrice_lecture(int n, int M[n+1][n+1]){
    int i,j;
    for (i=0; i<n;i++){
        for (j=0; j<n;j++){
            scanf("%d", &M[i][j]);
        }
    }
}

void matrice_affichage(int n, int Mat[n+1][n+1]){
	int i,j;
    /* Affichage de la matrice */
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) printf("%2d   ", Mat[i][j]);
        printf("\n");
    }

    printf("\n");
}

void vecteur_affichage(int n , int vec[] ){
    /*************************************************************/
    /* Action vecteur_affichage                                  */
    /* Rôle : Afficher les valeurs contenues da0   20   25   30   40
 1   35   20    0   10   15
 2   40   50   25   10    0
 3   30   40   35   30   15
 4   30    0   25   30 ns le vecteur vec */
    /*  Description des paramètres                               */
    /*    n : Entier - D                                       */
    /*    vec : vecteur [1...n] d'entiers - D                  */
    /*************************************************************/
    for (int i=0; i<n; i++){
        printf("%d ", vec[i]);
    }
    printf("\n");
}

void vecteur_lecture(int n, int vec[]){
    /*********************************************/
    /* Action : Vecteur_lecture                  */
    /* Rôle : Remplir un vecteur vec de taille n */
    /* Description des paramètres                */
    /* n : Entier - Donnée                       */
    /* vec : Vecteur [1...n] d'entiers - R     */
    /*********************************************/
    for (int i =0; i<n;i++){
        scanf("%d", &vec[i]);
    }
}


