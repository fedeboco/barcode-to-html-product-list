#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

#define CATALOG_DELIMITER_CHAR "|"
#define CART_ITEMS_DELIMITER ','
#define MAX_PRICE 15
#define MAX_BAR_CODE 	14
#define MAX_DESCRIPTION 100

#define BAR_CODE_FIELD_NUMBER 0
#define DESCRIPTION_FIELD_NUMBER 1
#define PRICE_FIELD_NUMBER 2

typedef struct ADT_Product_t{
	char * bar_code;
	char * description;
	double price;
}ADT_Product_t;

int ADT_Product_compare_by_barcode(const void * ,const void *);
status_t get_cart_item_barcode(FILE *, char *, bool_t *);
status_t ADT_Product_parse_csv_line(FILE *, ADT_Product_t *, bool_t *);
status_t ADT_Product_clone(void **, const void *);
status_t ADT_Product_destroy(void *);
status_t ADT_Product_print_as_html(FILE * , const ADT_Product_t * );
status_t ADT_Product_print_as_xml(FILE * , const ADT_Product_t * );

/*======MACROS PARA EL FORMATO DEL PRODUCTO HTML======*/
#define TAG_TR_COLOR2		"<tr bgcolor=\"#ffffcc\">"
#define TAG_TD			"<td>"
#define TAG_TD_ALIGN		"<td align=\"center\">"
#define TAG_TD_CLOSE		"</td>"
#define TAG_TR_CLOSE		"</tr>"
/*=======MACROS PARA EL FORMATO DEL PRODUCTO XML==========*/
#define TAG_PRODUCT		"<product>"
#define TAG_ID			"<id>"
#define TAG_ID_CLOSE		"</id>"
#define TAG_DESCRIPTION		"<description>"
#define TAG_DESCRIPTION_CLOSE	"</description>"
#define TAG_PRICE		"<price>"
#define TAG_PRICE_CLOSE		"</price>"
#define TAG_PRODUCT_CLOSE	"</product>"
/*===================================*/

#endif
