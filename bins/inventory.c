#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "inventory.h"

extern config_t configuration;

/*Esta función imprime el footer y valida el archivo de salida.*/
status_t process_footer(ADT_Vector_t ** catalog, FILE * finv, FILE * fout, FILE * ffooter, char * argv[])
{
	status_t st;
	
	if(	catalog==NULL||\
		finv==NULL||\
		fout==NULL||\
		argv==NULL)
		return ERROR_NULL_POINTER;

	if(ffooter==NULL){
		save_execution_status_log(finv, ERROR_INVALID_FOOTER_FILE_PATH, NULL);
		fclose(finv);
		ADT_Vector_destroy(catalog);
		fclose(fout);
		/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
		remove(argv[CMD_ARG_OUT]+1);
		return ERROR_INVALID_FOOTER_FILE_PATH;
	}
	if((st=copy_file_txt(ffooter,fout))!=OK)
		return st;
	fclose(ffooter);
	return OK;	
}

/*Esta función imprime el header y valida el archivo de salida.*/
status_t process_header(ADT_Vector_t ** catalog, FILE * finv, FILE * fout, FILE * fheader, char * argv[])
{
	status_t st;
	
	if(	catalog==NULL||\
		finv==NULL||\
		argv==NULL)
		return ERROR_NULL_POINTER;
	
	/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
	if(fout==NULL){
		save_execution_status_log(finv, ERROR_INVALID_OUTPUT_FILE_PATH, NULL);
		fclose(finv);
		ADT_Vector_destroy(catalog);
		/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
		return ERROR_INVALID_OUTPUT_FILE_PATH;
	}
	if(fheader==NULL){
		save_execution_status_log(finv, ERROR_INVALID_HEADER_FILE_PATH, NULL);
		fclose(finv);
		ADT_Vector_destroy(catalog);
		fclose(fout);
		/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
		remove(argv[CMD_ARG_OUT]+1);
		return ERROR_INVALID_HEADER_FILE_PATH;
	}
	if((st=copy_file_txt(fheader,fout))!=OK)
		return st;
	fclose(fheader);
	return OK;
}

/*Esta función destruye el vector y cierra todos los archivos.*/
status_t free_memory(ADT_Vector_t ** catalog, FILE * finv, FILE * fout, FILE * fitems, char * argv[])
{
	status_t st;
	
	if(	catalog==NULL||\
		finv==NULL||\
		fout==NULL||\
		fitems==NULL||\
		argv==NULL)
		return ERROR_NULL_POINTER;
	
	if((st=ADT_Vector_destroy(catalog))!=OK){
	save_execution_status_log(finv,st,NULL);
	fclose(finv);
	fclose(fout);	
	fclose(fitems);
	/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
	remove(argv[CMD_ARG_OUT]+1);
	return st;
	}

	if(fclose(fitems)==EOF){
		save_execution_status_log(finv, ERROR_ITEMS_FILE_CLOSE, NULL);
		fclose(fout);
		fclose(finv);
		/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
		remove(argv[CMD_ARG_OUT]+1);
		return ERROR_ITEMS_FILE_CLOSE;
	}
	if(fclose(fout)==EOF){
		save_execution_status_log(finv, ERROR_OUTPUT_FILE_CLOSE, NULL);
		fclose(finv);
		return ERROR_OUTPUT_FILE_CLOSE;
	}
	if((st=save_execution_status_log(finv,OK, NULL))!=OK){
		fclose(finv);
		return st;
	}
	if(fclose(finv)==EOF)
		return ERROR_INVENTORY_FILE_CLOSE;
	return OK;
}

/*Esta función inicializa un vector y carga todos sus elementos parseando desde un .csv.*/
status_t process_vector(	ADT_Vector_t ** catalog, 
							FILE * finv,
							FILE * flist,
							bool_t * eof,
							ADT_Product_t * aux_product)
{
	status_t st;
	
	if(	catalog==NULL||\
		finv==NULL||\
		flist==NULL||\
		eof==NULL||\
		aux_product==NULL)
		return ERROR_NULL_POINTER;

	if((st=ADT_Vector_new(catalog))!=OK){
		save_execution_status_log(finv,st,NULL);
		fclose(finv);
		fclose(flist);
		return st;
	}
	set_destructor(*catalog,ADT_Product_destroy);
	set_clonator(*catalog,ADT_Product_clone);

	*eof=FALSE;
	
	while(*eof!=TRUE){
		if((st=ADT_Product_parse_csv_line(flist,aux_product,eof))!=OK){
			save_execution_status_log(finv,st,NULL);
			ADT_Vector_destroy(catalog);
			fclose(finv);
			fclose(flist);
			return st;
		}
		if(*eof==TRUE)
			break;

		if((st=ADT_Vector_append(*catalog,aux_product))!=OK){
			save_execution_status_log(finv,st,NULL);
			ADT_Vector_destroy(catalog);
			fclose(finv);
			fclose(flist);
			return st;
		}
		free(aux_product->bar_code);
		free(aux_product->description);
		
	}
	
	fclose(flist);
	
	if((st=ADT_Vector_sort(*catalog,ADT_Product_compare_by_barcode))!=OK){
		save_execution_status_log(finv,st,NULL);
		ADT_Vector_destroy(catalog);
		fclose(finv);
		return st;
	}
	return OK;
}

/*Esta función lee desde archivo los códigos de barras y los procesa, buscándolos en el catálogo y 
luego imprimiendo el producto en el archivo de salida, ya sea en formato HTML o XML.*/	 
status_t process_products(FILE * finv, 
			FILE * fout, 
			FILE * fitems,
			ADT_Vector_t * catalog,
			ADT_Product_t * catalog_product_found, 
			ADT_Product_t * aux_product, 
			bool_t * eof,
			char * argv[])
{
	
	status_t st;
	
	if(	fitems==NULL||\
		finv==NULL||\
		fout==NULL||\
		eof==NULL||\
		aux_product==NULL||\
		catalog_product_found==NULL||\
		argv==NULL||\
		catalog==NULL)
		return ERROR_NULL_POINTER;

	*eof=FALSE;	
		
	while(*eof!=TRUE){

		if((st=read_line(&(aux_product->bar_code),eof,fitems,'\n'))!=OK)
			return st;
		
		if(*eof==TRUE)
			return OK;
		
		if((catalog_product_found=ADT_Vector_look_up(catalog,aux_product,ADT_Product_compare_by_barcode))==NULL){
			save_execution_status_log(finv,ERROR_UNKNOWN_PRODUCT,aux_product->bar_code);
			return ERROR_NULL_POINTER;
		}
		switch(configuration.output_format){
			case DOC_TYPE_HTML:
				st=ADT_Product_print_as_html(fout,catalog_product_found);
				break;
			case DOC_TYPE_XML:
				st=ADT_Product_print_as_xml(fout,catalog_product_found);
				break;
			default:
				st=ERROR_INVALID_OUTPUT_FORMAT;
				break;
		}
		if(st!=OK){
			save_execution_status_log(finv,st,NULL);
			ADT_Vector_destroy(&catalog);
			fclose(finv);
			fclose(fout);
			fclose(fitems);
			/*En la línea siguiente, "+1" se introduce para ignorar el indicador.*/
			remove(argv[CMD_ARG_OUT]+1);
		}
	}
	return st;
}
