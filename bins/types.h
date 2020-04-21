#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{ERROR_NULL_POINTER=0,
			ERROR_INVALID_ARG=1,
			ERROR_INVALID_ARGS_NUMBER=2,
			ERROR_INVALID_OUTPUT_FORMAT=3,
			ERROR_INVALID_ITEMS_FILE_PATH=4,
			ERROR_INVALID_LIST_FILE_PATH=5,
			ERROR_INVALID_OUTPUT_FILE_PATH=6,
			ERROR_INVENTORY_FILE_PATH=7,
			ERROR_INVALID_HEADER_FILE_PATH=8,
			ERROR_INVALID_FOOTER_FILE_PATH=9,
			ERROR_UNKNOWN_PRODUCT=10,
			ERROR_NO_MEMORY=11,
			ERROR_LIST_FILE_CLOSE=12,
			ERROR_ITEMS_FILE_CLOSE=13,
			ERROR_INVENTORY_FILE_CLOSE=14,
			ERROR_OUTPUT_FILE_CLOSE=15,
			ERROR_HEADER_FILE_CLOSE=16,
			ERROR_FOOTER_FILE_CLOSE=17,
			OK=18
			} status_t;


typedef enum {FALSE, TRUE} bool_t;

typedef enum {DOC_TYPE_XML=1, DOC_TYPE_HTML=0} doc_type_t;

typedef struct config_t{
		doc_type_t output_format;
		} config_t;		
#endif
