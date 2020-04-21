#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>
#include "types.h"
#include "english.h"

#define MSG_ERROR_PREFIX	"Error: "
#define OUTPUT_DELIMITER	'|'

status_t save_execution_status_log(FILE * , status_t , char *);
status_t print_date(FILE * );
status_t print_status(FILE * , status_t , char *);

#endif
