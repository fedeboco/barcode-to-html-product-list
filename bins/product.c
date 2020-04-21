#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product.h"

/*Esta funcion compara 2 productos por su código de barras*/
int ADT_Product_compare_by_barcode(const void * item_prod,const void * product){		

	ADT_Product_t *item=((ADT_Product_t*)item_prod);
	ADT_Product_t *prod=((ADT_Product_t*)product);

	char * barcode_product;
	char * barcode_item;
	size_t i;

	if((barcode_item=strdup(item->bar_code))==NULL)
		return ERROR_NULL_POINTER;
	if((barcode_product=strdup(prod->bar_code))==NULL)
		return ERROR_NULL_POINTER;

	for(i=0; barcode_item[i] && barcode_product[i]; i++){
		if(barcode_item[i] > barcode_product[i])
			return 1;
			
		if(barcode_item[i] < barcode_product[i])
			return -1;
			
	}
	return 0;			
}

/*Esta función clona un producto a una variable auxiliar*/ 
status_t ADT_Product_clone(void ** prod_a, const void * prod_b){

	ADT_Product_t * temp;
	const ADT_Product_t * pb = (const ADT_Product_t *)prod_b;

	if(prod_b==NULL||prod_a==NULL)
		return ERROR_NULL_POINTER;
	
	if((temp=(ADT_Product_t*)malloc(sizeof(ADT_Product_t)))==NULL)
		return ERROR_NO_MEMORY;

	if((temp->bar_code=strdup(pb->bar_code))==NULL)
		return ERROR_NULL_POINTER;
	if((temp->description=strdup(pb->description))==NULL)
		return ERROR_NULL_POINTER;

	temp->price=pb->price;
	*prod_a=temp;
	return OK;
}

/*Esta función obtiene una linea de un archivo de texto catalogo.csv y extrae sus 3
campos en forma estática: bar_code, description y price.
La longitud máxima de cada campo se establece en products.h*/
status_t ADT_Product_parse_csv_line(FILE * flist, ADT_Product_t * prod, bool_t * eof){

	char * line;
	char * temp;
	size_t str_len;
	status_t st;
	
	char ** fields;
	
	if(flist==NULL||prod==NULL)
		return ERROR_NULL_POINTER;

	if((st=read_line(&line,eof,flist,'\n'))!=OK)
		return st;
	if((fields=split_string(line,CATALOG_DELIMITER_CHAR,&str_len))==NULL)
		return ERROR_NULL_POINTER;
	free(line);
	
	if(*eof==TRUE)
		return OK;
	
	prod->bar_code=fields[BAR_CODE_FIELD_NUMBER];
	prod->description=fields[DESCRIPTION_FIELD_NUMBER];
	prod->price=strtod(fields[PRICE_FIELD_NUMBER],&temp);

	free(fields);
			
	if(*temp && *temp!='\n')
		return ERROR_UNKNOWN_PRODUCT;	

	return OK;
}

/*Esta función destruye un puntero u arreglo*/
status_t ADT_Product_destroy(void * ptr){
	
	ADT_Product_t * temp=(ADT_Product_t *)ptr;

	if(ptr==NULL)
		return ERROR_NULL_POINTER;
	
	free(temp);
	temp=NULL;
	return OK;
}

/*Esta función imprime un producto en el archivo de salida en formato HTML.*/
status_t ADT_Product_print_as_html(FILE * fo, const ADT_Product_t * prod){

	if(fo==NULL||prod==NULL)
		return ERROR_NULL_POINTER;
	fprintf(fo, "%s\n", TAG_TR_COLOR2);
	fprintf(fo, "%s%s%s\n", TAG_TD, prod->description, TAG_TD_CLOSE);
	fprintf(fo, "%s$ %.2f%s\n", TAG_TD_ALIGN, prod->price, TAG_TD_CLOSE);
	fprintf(fo, "%s%s%s\n", TAG_TD_ALIGN, prod->bar_code, TAG_TD_CLOSE);
	fprintf(fo, "%s\n", TAG_TR_CLOSE);
	return OK;
}

/*Esta función imprime un producto en el archivo de salida en formato XML.*/
status_t ADT_Product_print_as_xml(FILE * fo, const ADT_Product_t * product){

	if(fo==NULL||product==NULL)
		return ERROR_NULL_POINTER;
	fprintf(fo, "%s\n", TAG_PRODUCT);
	fprintf(fo, "%s%s%s\n", TAG_ID, product->bar_code, TAG_ID_CLOSE);
	fprintf(fo, "%s%s%s\n", TAG_DESCRIPTION, product->description, TAG_DESCRIPTION_CLOSE);
	fprintf(fo, "%s%f%s\n", TAG_PRICE, product->price, TAG_PRICE_CLOSE);
	fprintf(fo, "%s\n", TAG_PRODUCT_CLOSE);
	return OK;
}
