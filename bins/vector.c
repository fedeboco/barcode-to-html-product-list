#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "vector.h"

/*Agrega un elemento al vector de forma dinámica.
Clonator copia un nuevo dato al vector, previamente solicitando memoria para
el mismo. Clonator se configura en set_clonator y el clonador depende
del tipo de dato utilizado.*/
status_t ADT_Vector_append(ADT_Vector_t * vector,const void * elem){

	void ** aux;
	status_t st;

	if(vector==NULL||elem==NULL)
		return ERROR_NULL_POINTER;
	if((aux=(void**)realloc(vector->elems,(vector->size+1)*sizeof(void*)))==NULL){
		return ERROR_NO_MEMORY;
	}
	vector->elems=aux;
	if((st=(vector->clonator(&(vector->elems[vector->size++]),elem)))!=OK)	
		return st;
	return OK;
}

/*Esta primitiva realiza una búsqueda binaria a lo largo de todo un ADT_Vector_t en función de un target 
(elemento a encontrar) y un criterio de comparación cmp*/
void * ADT_Vector_look_up(const ADT_Vector_t * vector, const void * target, comparator_t cmp){
	
	int top, bottom, middle;
	
	top=vector->size-1;
	bottom=0;
	while(top >= bottom){
		middle = (top+bottom)/2;
		if(cmp(target,vector->elems[middle])==0)
			return vector->elems[middle];
		if(cmp(target,vector->elems[middle])>0)
			bottom=middle+1;
		if(cmp(target,vector->elems[middle])<0)
			top=middle-1;
	}
	return NULL;
}

/*Esta primitiva ordena el vector en función de un criterio de comparación
basado en el puntero a función pf y valiendose de un ordenamiento de tipo 
"insertion sort".*/
status_t ADT_Vector_sort(ADT_Vector_t * vector, comparator_t pf){

	void * aux;
	size_t i, j;

	if(vector==NULL)
		return ERROR_NULL_POINTER;

	for(i=1; i<vector->size; i++){
		aux=vector->elems[i];
		for(j=i; j>0 && ((*pf)(vector->elems[j-1], aux)>0); j--){
			vector->elems[j]=vector->elems[j-1];
		}
		vector->elems[j]=aux;
	}
	return OK;
}

/*Destruye un ADT_Vector_t*/
status_t ADT_Vector_destroy(ADT_Vector_t ** vector){
	status_t st;
	size_t i;
	
	if(vector==NULL)
		return ERROR_NULL_POINTER;
	for(i=0;i<(*vector)->size;i++){
		if((st=((*vector)->destructor((*vector)->elems[i])))!=OK){
			(*vector)->elems[i]=NULL;
			return st;
		}
	}
	free((*vector)->elems);
	free(*vector);
	*vector=NULL;
	return OK;
}

/*Crea un nuevo ADT_Vector_t y establece como precondiciones una inicialización
de su arreglo de punteros a NULL y su largo a 0.*/
status_t ADT_Vector_new(ADT_Vector_t ** vector){
	
	if(vector==NULL)
		return ERROR_NULL_POINTER;
	
	if((*vector=(ADT_Vector_t*)malloc(sizeof(ADT_Vector_t)))==NULL)
		return ERROR_NO_MEMORY;
	(*vector)->elems=NULL;
	(*vector)->size=0;
	return OK;
}

/*Configura destructor, es decir, vincula vector_destructor con el pf destroy*/
status_t set_destructor(ADT_Vector_t * vector, destructor_t destroy){
	
	if(vector==NULL||destroy==NULL)
		return ERROR_NULL_POINTER;
	
	vector->destructor=destroy;
	return OK;
}

/*Configura clonator, es decir, vincula vector_destructor con el pf destroy*/
status_t set_clonator(ADT_Vector_t * vector, clonator_t elem_clonator){
	
	if(vector==NULL)
		return ERROR_NULL_POINTER;
	
	vector->clonator=elem_clonator;
	return OK;
}


