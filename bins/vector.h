#ifndef TDA_VECTOR_H
#define TDA_VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


typedef status_t (*destructor_t)(void *);
typedef status_t (*get_t)(void *);
typedef status_t (*look_up_t)(void *);
typedef status_t (*sort_t)(void *);
typedef status_t (*clonator_t)(void ** ,const void*);
typedef int (*comparator_t)(const void * ,const void *);

typedef struct ADT_Vector_t{
	void ** elems;
	size_t size;
	look_up_t find_elem;
	destructor_t destructor;
	clonator_t clonator;
}ADT_Vector_t;

/*Prototipos de primitivas del ADT===============================*/
status_t ADT_Vector_append(ADT_Vector_t *,const void *);
void * ADT_Vector_look_up(const ADT_Vector_t *, const void *, comparator_t);
status_t ADT_Vector_sort(ADT_Vector_t *, comparator_t);
status_t ADT_Vector_new(ADT_Vector_t **);
status_t ADT_Vector_destroy(ADT_Vector_t **);
status_t set_destructor(ADT_Vector_t *, destructor_t);
status_t set_clonator(ADT_Vector_t *, clonator_t);
/*Fin Prototipos=================================================*/

#endif
