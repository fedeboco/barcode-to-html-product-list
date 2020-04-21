#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product.h"
#include "vector.h"
#include "log.h"
#include "utils.h"

#define CMD_ARG_OUT 4

status_t process_products(FILE *, FILE *, FILE *,ADT_Vector_t *,ADT_Product_t *, ADT_Product_t *, bool_t *,char*[]);
status_t process_vector(ADT_Vector_t **,FILE *,FILE *,bool_t *,ADT_Product_t *);
status_t free_memory(ADT_Vector_t **, FILE *, FILE *, FILE *,char *[]);
status_t process_header(ADT_Vector_t **, FILE *, FILE *, FILE *, char *[]);
status_t process_footer(ADT_Vector_t ** , FILE * , FILE * , FILE * , char * []);

#endif
