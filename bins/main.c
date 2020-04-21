#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "vector.h"
#include "product.h"
#include "main.h"
#include "log.h"
#include "utils.h"
#include "inventory.h"

config_t configuration;

int main(int argc, char * argv[]){

	status_t st;
	FILE *finv, *flist, *fitems, *fout, *fheader, *ffooter;
	ADT_Vector_t * catalog;
	ADT_Product_t aux_product;
	ADT_Product_t catalog_product_found;
	bool_t eof;

	if((finv=fopen(INVENTORY_FILE_PATH, "at"))==NULL)
		return EXIT_FAILURE;
	if((st=validate_arguments(argc, argv))!=OK){
		save_execution_status_log(finv, st, NULL);
		fclose(finv);
		return EXIT_FAILURE;
	}
	/*En la siguiente llamada a fopen(), se comienza a leer la ruta del archivo
	a partir de la posición 1 ("+1") para poder ignorar así el caracter indicador 
	de comienzo de argumento el cual ya fué validado en validate_arguments().
	En posteriores llamadas se hará una mención más breve al respecto.*/
	if((flist=fopen((argv[CMD_ARG_LIST]+1), "rt"))==NULL){
		save_execution_status_log(finv, ERROR_INVALID_LIST_FILE_PATH, NULL);
		fclose(finv);
		return EXIT_FAILURE;
	}

	if((st=process_vector(&catalog,finv,flist,&eof,&aux_product))!=OK)
		return EXIT_FAILURE;
 
	/*En el fopen siguiente, "+1" se introduce para ignorar el indicador.*/
	fout=fopen((argv[CMD_ARG_OUT]+1), "wt");

	if(configuration.output_format==DOC_TYPE_HTML)
		fheader=fopen(HTML_HEADER_FILE_PATH,"rt");
	else if(configuration.output_format==DOC_TYPE_XML)
		fheader=fopen(XML_HEADER_FILE_PATH,"rt");

	/*La siguiente linea valida fheader y fout*/
	if((st=process_header(&catalog,finv,fout,fheader,argv))!=OK)
			return EXIT_FAILURE;

	/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
	if((fitems=fopen((argv[CMD_ARG_ITEMS]+1), "rt"))==NULL){ 
		save_execution_status_log(finv, ERROR_INVALID_ITEMS_FILE_PATH, NULL);
		fclose(finv);
		return EXIT_FAILURE;
	}
		
	if((st=process_products(finv,fout,fitems,catalog,&catalog_product_found,&aux_product,&eof,argv))!=OK)
		return EXIT_FAILURE;
		
	if(configuration.output_format==DOC_TYPE_HTML)
		ffooter=fopen(HTML_FOOTER_FILE_PATH,"rt");
	else if(configuration.output_format==DOC_TYPE_XML)
		ffooter=fopen(XML_FOOTER_FILE_PATH,"rt");

	if((st=process_footer(&catalog,finv,fout,ffooter,argv))!=OK)
			return EXIT_FAILURE;
	
	if((st=free_memory(&catalog,finv,fout,fitems,argv))!=OK)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

/*Esta función valida los argumentos que recibe el programa. La cantidad
de argumentos que recibe y la posición de cada argumento son configurables en 
main.h*/
status_t validate_arguments(int argc, char * argv[]){
	
	size_t i;
	status_t st;

	if(argv==NULL)
		return ERROR_NULL_POINTER;
	if(argc!=MAX_ARGS){
		return ERROR_INVALID_ARGS_NUMBER;
	}
	for(i=1; i< MAX_ARGS; i++){
		if(argv[i][0] != ARG_START_INDICATOR)
			return ERROR_INVALID_ARG;
	}
	if((st=get_output_format(argv[CMD_ARG_FORMAT], &(configuration.output_format))) != OK){
		return st;	
	}
	return OK;
}

/*Esta función obtiene el formato de salida (HTML o XML)
a partir de los argumentos ingresados.*/
status_t get_output_format(const char * str_format, doc_type_t * fmt){

	if(str_format==NULL || fmt==NULL)
		return ERROR_NULL_POINTER; 
	/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
	if(!strcmp(str_format+1, ARG_DOC_TYPE_XML)){
		*fmt = DOC_TYPE_XML;
		return OK;
	}
	/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
	if(!strcmp(str_format+1, ARG_DOC_TYPE_HTML)){ 				
		*fmt = DOC_TYPE_HTML;
		return OK;
	}else{
		return ERROR_INVALID_OUTPUT_FORMAT;
	}
}

