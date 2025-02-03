#ifndef LISTE_H
#define LISTE_H

struct liste_int {
  int *lst_int;
  int size;
};

struct liste_flt {
  float *lst_flt;
  int size;
};

void liste_int_add(struct liste_int *lst, int val);

void liste_flt_add(struct liste_flt *lst, float val);

#endif