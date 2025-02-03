#include "Liste.h"
#include <stdlib.h>

void liste_int_add(struct liste_int *lst, int val) {
  if(lst->size==0){
    lst->lst_int = malloc((1) * sizeof(int));
  }
  
  lst->lst_int = realloc(lst->lst_int, (lst->size + 1) * sizeof(int));
  lst->lst_int[lst->size] = val;
  lst->size++;
  
}

void liste_flt_add(struct liste_flt *lst, float val) {
  if(lst->size==0){
    lst->lst_flt = malloc((1) * sizeof(int));
  }
  
  lst->lst_flt = realloc(lst->lst_flt, (lst->size + 1) * sizeof(float));
  lst->lst_flt[lst->size] = val;
  lst->size++;
  
}
