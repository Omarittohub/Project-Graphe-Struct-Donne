#include <stdio.h>
#define D 0
#include "Liste.h"
#include <limits.h>
#include <stdlib.h>

typedef struct {
  int *Head;             // Head
  struct liste_int Succ; // Successeur
  struct liste_flt Cout; // Cout

} Grph_H;

typedef struct {
  int debut; // Head
  int fin;
  int cout;

} Camion;

void premiertoursc(int n, float M[n + 1][n + 1], int *T, int ID) {

  float min = M[0][ID];
  int min_j = ID, i = ID, tot = n + 1;
  T[0] = ID;
  for (int p = 0; p < tot; p++) {
    M[p][0] = -1;
    M[p][ID] = -1;
  }
  for (int k = 1; k < tot - 1; k++) {
    for (int j = 0; j < tot; j++) {
      if (i != j && M[i][j] <= min && M[i][j] != -1) {
        min = M[i][j];
        min_j = j;
      }
    }
    T[k] = min_j;
    for (int p = 0; p < tot; p++) {
      M[p][min_j] = -1;
    }
    i = min_j;
    min = M[i][0];
    int test = 0;
    while (min == -1 || min == 0) {
      test++;
      min = M[i][test];
    }
  }
}

void inserer_int(int *tab, int pos, int s, int value) {

  if (pos + 5 > s) {
    tab = (int *)realloc(tab, (pos + 1) * sizeof(int));
  }
  tab[pos] = value;
}

void inserer_float(float *tab, int pos, int s, float value) {
  if (pos + 5 > s) {
    tab = (float *)realloc(tab, (pos + 1) * sizeof(float));
  }
  tab[pos] = value;
}

void split_algorithm(int *T, int Q, int n, float dist[n + 1][n + 1], int *q,
                     Grph_H *H) {
  int load, i, j;
  float cost;
  int indCour = 0; // Current index for SUCC and COUT arrays

  for (i = 0; i < n; i++) { // Start from 0 because T[0] is the first client
    j = i;
    load = 0; // a new vehicle is commissioned
    int firstClient = 1;

    while (j < n && load + q[T[j]] <= Q) {
      load += q[T[j]];

      if (firstClient) {
        cost = dist[D][T[j]] + dist[T[j]][D];
        firstClient = 0;
      } else {
        cost = cost - dist[T[j - 1]][D] + dist[T[j - 1]][T[j]] + dist[T[j]][D];
      }

      if (H->Head[i] == -1) {
        H->Head[i] = indCour;
      }
      if (H->Head[i + 1] == -1) {
        H->Head[i + 1] = indCour + 1;
      } else {
        H->Head[i + 1]++;
      }

      liste_int_add(&H->Succ, T[j]);
      liste_flt_add(&H->Cout, cost);
      indCour++;

      j++;
    }
  }
}

void bellmanFord(Grph_H *H, int n, struct liste_int *chemin, int *pi) {

  int pere[n];
  int source = 0;

  // Initialisation
  for (int i = 0; i < n; i++) {
    pi[i] = INT_MAX;
    pere[i] = -1;
  }
  pi[source] = 0;
  pere[source] = source;

  // Relaxation des arêtes
  for (int i = 0; i < n - 1; i++) {
    for (int u = 0; u < n; u++) {
      for (int k = H->Head[u]; k < H->Head[u + 1]; k++) {
        int v = H->Succ.lst_int[k];
        int weight = H->Cout.lst_flt[k];
        if (pi[u] != INT_MAX && pi[u] + weight < pi[v]) {
          pi[v] = pi[u] + weight;
          pere[v] = u;
        }
      }
    }
  }

  // Vérification des cycles de poids négatif
  for (int u = 0; u < n; u++) {
    for (int k = H->Head[u]; k < H->Head[u + 1]; k++) {
      int v = H->Succ.lst_int[k];
      int weight = H->Cout.lst_flt[k];
      if (pi[u] != INT_MAX && pi[u] + weight < pi[v]) {
        printf("Graph contains a negative-weight cycle\n");
        return;
      }
    }
  }

  // Reconstruction du chemin le plus court du sommet source au dernier sommet
  int current = n - 1; // Dernier nœud
  int index = 0;

  while (current != source) {
    printf("current : %d\n", current);
    liste_int_add(chemin, current);
    current = pere[current];
    if (current == -1) {
      printf("No path from source to the last node\n");
      return;
    }
  }
  
  liste_int_add(chemin, source);
}

void convert_chemin_camions(int *chemin, Camion *camion, int *cou_cam, int n) {
  int i = 0;
  while (chemin[i] != 0) {
    camion[i].debut = chemin[i + 1] + 1;
    camion[i].fin = chemin[i];
    i++;
  }

  printf(" n :%d\n", n);

  for (int i = 0; i < n; i++) {
    printf(" i : %d\n", i);
    camion[i].cout = cou_cam[i] - cou_cam[i+1];
  }
}

int main() {

  int n, Q;
  scanf("%d",&n); // nombre de clients
  scanf("%d", &Q); // quantité maximale par véhicule

  float M[n + 1][n + 1];
  int q[n];
  int T[n];
  
  // Read q vector
  vecteur_lecture(n, q);
  
  // Read distance matrix
  matrice_lecture(n, M);
  
  
  // Initialize T array before calling tourgeant
  for (int i = 0; i < n; i++) {
      T[i] = 0;
  }

/* 
  float M[6][6] = {{0, 20, 25, 30, 40, 35}, {20, 0, 10, 15, 40, 50},
                   {25, 10, 0, 30, 40, 35}, {30, 15, 30, 0, 25, 30},
                   {40, 40, 40, 25, 0, 15}, {35, 50, 35, 30, 15, 0}};
  float M2[6][6] = {{0, 20, 25, 30, 40, 35}, {20, 0, 10, 15, 40, 50},
                    {25, 10, 0, 30, 40, 35}, {30, 15, 30, 0, 25, 30},
                    {40, 40, 40, 25, 0, 15}, {35, 50, 35, 30, 15, 0}};
  int T[5];
  int n = 5;
  int Q = 10;
  int q[6] = {0, 5, 4, 4, 2, 7}; */ 
  int nbclient = 1;
  struct liste_int chemin;
  chemin.size = 0;

  premiertoursc(n, M, T, nbclient);
  Grph_H H;

  H.Head = (int *)malloc((n + 2) * sizeof(int));
  H.Succ.size = 0;
  H.Cout.size = 0;

  for (int i = 0; i <= n + 1; i++) {
    H.Head[i] = -1;
  }

  split_algorithm(T, Q, n, M, q, &H);

  int pi[100];

  bellmanFord(&H, 6, &chemin, pi);
  for (int i = 0; i < 4; i++) {
    printf("%d ", chemin.lst_int[i]);
  }

  printf("\n");

  printf("\n");
  int cout_par_camion[chemin.size - 1];
  for (int i = 0; i < 4; i++) {
    cout_par_camion[i] = pi[chemin.lst_int[i]];
    printf("%d\n", cout_par_camion[i]);
  }

  Camion camions[chemin.size - 1];
  convert_chemin_camions(chemin.lst_int, camions, cout_par_camion, chemin.size - 1);

  printf("\nCamion 1 : %d -> %d [%d]\n", camions[0].debut, camions[0].fin,
         camions[0].cout);
  printf("Camion 2 : %d -> %d [%d]\n", camions[1].debut, camions[1].fin,
         camions[1].cout);
  printf("Camion 3 : %d -> %d [%d]\n", camions[2].debut, camions[2].fin,
         camions[2].cout);

  return 0;
}
