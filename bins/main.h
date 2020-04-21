#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "product.h"

#define MAX_ARGS		5
#define CMD_ARG_FORMAT		1
#define CMD_ARG_ITEMS		2
#define CMD_ARG_LIST		3
#define ARG_START_INDICATOR	'-'
#define INVENTORY_FILE_PATH "./inventory.log"
#define HTML_HEADER_FILE_PATH "./html_header.txt"
#define XML_HEADER_FILE_PATH "./xml_header.txt"
#define HTML_FOOTER_FILE_PATH "./html_footer.txt"
#define XML_FOOTER_FILE_PATH "./xml_footer.txt"
#define ARG_DOC_TYPE_XML "xml"
#define ARG_DOC_TYPE_HTML "html"

status_t get_output_format(const char * , doc_type_t * );
status_t validate_arguments(int , char * []);

#endif

