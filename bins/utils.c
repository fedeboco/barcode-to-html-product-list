#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "utils.h"

/*Esta función lee desde un archivo y guarda una cadena en line*/
status_t read_line(char ** line, bool_t * eof,FILE * finput,char delimiter){
	size_t alloc_size, used_size;
	char * aux;
	char c;
	
	if(line==NULL||eof==NULL||finput==NULL)
		return ERROR_NULL_POINTER;
	if((*line=malloc(sizeof(char)*LINE_INIT_CHOP))==NULL)
		return ERROR_NO_MEMORY;

	alloc_size=LINE_INIT_CHOP;
	used_size=0;
	*eof=FALSE;
	while((c=fgetc(finput))!=EOF&&c!=delimiter){
		if(used_size==alloc_size-1){
			if((aux=realloc(*line,(alloc_size+LINE_CHOP_SIZE)*sizeof(char)))==NULL){
				free(*line);
				*line=NULL;
				return ERROR_NO_MEMORY;
			}
			alloc_size+=LINE_CHOP_SIZE;
			*line=aux;
		}
		(*line)[used_size++]=c;
	}
	if(c==EOF){
		*eof=TRUE;
	}
	(*line)[used_size]='\0';
	return OK;
}

/*Esta función copia una cadena pidiendo memoria para su copia.*/
char * strdup(const char * s2)
{
	char * s1;
	
	if(s2==NULL)
		return NULL;
	if((s1=malloc(sizeof(char)*(strlen(s2)+1)))==NULL)
		return NULL;
	strcpy(s1,s2);
	return s1;
}

/*Esta función divide una cadena en n cadenas al encontrar el parametro separador (sep).*/
char ** split_string(char * s, char * sep, size_t * len)
{
	size_t i,n;
	char * s2, *p, *q;
	char ** fields;
	
	if(s==NULL||len==NULL||sep==NULL)
		return NULL;
	
	s2=strdup(s);
	
	for(i=0,n=0;s[i];i++)
		if(s[i]==*sep)
			n++;
	n++;
	if((fields=(char**)malloc(n*sizeof(char*)))==NULL)
	{
		free(s2);
		*len=0;
		return NULL;
	}
	
	for(q=s, i=0;(p=strtok(q,sep))!=NULL;i++,q=NULL)
	{
		if((fields[i]=strdup(p))==NULL)
		{
			destroy_strings(fields,i);
			*len=0;
			return NULL;
		}
	}
	
	*len=i;
	free(s2);
	return fields;
}

/*Precondición: no puede recibir NULL.*/
void destroy_strings(char ** fields, size_t i){
	size_t j;

	if(fields!=NULL)
		for(j=0; j<=i;j++){
			free(fields[j]);
			fields[j]=NULL;
		}
}

/*=========IMPRESION DE ARCHIVO DE SALIDA=========*/

/*Esta función copia el contenido del archivo de entrada en el archivo de salida,
ambos archivos abiertos en modo texto.*/
status_t copy_file_txt(FILE * fi, FILE * fo){

	char * line;
	bool_t eof;
	status_t st;	

	if(fo==NULL||fi==NULL){
		return ERROR_NULL_POINTER;
	}
	eof=FALSE;
	while(eof!=TRUE){
		if((st=read_line( &line, &eof, fi,'\n'))!=OK)
			return st;
		fprintf(fo, "%s\n", line);
	}
	free(line);
	return OK;
}
