#include <stdio.h>
#include <time.h>
#include "types.h"
#include "english.h"
#include "log.h"

/*Diccionario de errores*/
char * err_arr[]={
			MSG_ERROR_NULL_POINTER,
			MSG_ERROR_INVALID_ARG,
			MSG_ERROR_INVALID_ARGS_NUMBER,
			MSG_ERROR_INVALID_OUTPUT_FORMAT,
			MSG_ERROR_INVALID_ITEMS_FILE_PATH,
			MSG_ERROR_INVALID_LIST_FILE_PATH,
			MSG_ERROR_INVALID_OUTPUT_FILE_PATH,
			MSG_ERROR_INVENTORY_FILE_PATH,
			MSG_ERROR_INVALID_HEADER_FILE_PATH,
			MSG_ERROR_INVALID_FOOTER_FILE_PATH,
			MSG_ERROR_UNKNOWN_PRODUCT,
			MSG_ERROR_NO_MEMORY,
			MSG_ERROR_LIST_FILE_CLOSE,
			MSG_ERROR_ITEMS_FILE_CLOSE,
			MSG_ERROR_INVENTORY_FILE_CLOSE,
			MSG_ERROR_OUTPUT_FILE_CLOSE,
			MSG_ERROR_HEADER_FILE_CLOSE,
			MSG_ERROR_FOOTER_FILE_CLOSE,
			MSG_OK
};


/*Esta función recibe un flujo, un status_t y un size_t. Imprime en el flujo: la fecha y hora del sistema, el mensaje asociado al status_t y en caso de contener un error de producto inexistente, también imprime el código de barra del producto (size_t)*/
status_t save_execution_status_log(FILE * fo, status_t st, char * barcode){
	
	if(fo==NULL)
		return ERROR_NULL_POINTER;
	print_date(fo);
	fputc(OUTPUT_DELIMITER, fo);
	print_status(fo, st, barcode);
	return OK;
}

/*Esta función recibe un flujo e imprime en él la fecha y hora del sistema. No puede recibir un file NULL*/
status_t print_date(FILE * fo){
	time_t sys_time;
	struct tm * date;
	
	if(fo==NULL)
		return ERROR_NULL_POINTER;
	
	sys_time=time(NULL);
	date=localtime(&sys_time);
	fprintf(fo, "%02d-%02d-%d %02d:%02d:%02d", date->tm_mday, date->tm_mon+1, date->tm_year+1900, date->tm_hour, date->tm_min, date->tm_sec);
	return OK;
}

/*Esta función recibe una variable de tipo status_t e imprime por el flujo (fo) el mensaje de error asociado a ese status_t, según el diccionario global de errores especificado. No puede recibir un file NULL.
Si recibe barcode==NULL, implica que el error no se encuentra relacionado con el producto por lo cual el programa ignora la impresión del contenido del puntero.*/
status_t print_status(FILE * fo, status_t st, char * barcode){	
	
	if(fo==NULL)
		return ERROR_NULL_POINTER;
	
	if(st==OK){
		fprintf(fo, "%s\n", err_arr[st]);
		return OK;
	}
	if(st==ERROR_UNKNOWN_PRODUCT){
		fprintf(fo, "%s: %s ", MSG_ERROR_PREFIX, err_arr[st]);
		if(barcode!=NULL)
			fprintf(fo,"(%s)",barcode);
		fputc('\n',fo);
		return OK;		
	}else{
		fprintf(fo, "%s: %s\n", MSG_ERROR_PREFIX, err_arr[st]);
		return OK;
	}
}

