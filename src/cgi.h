/* cgi.h - CGI functions
 * Copyright (C) 2001-2003 Dr. James L. Kepner
 * james.kepner@roswellpark.org
 *
 * This file is part of samplesize
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datastructures.h"


void print_header(void);
void print_footer(void);
void do_error_page(char *);
struct name_value_pair_dllst *parse_name_value_pairs(char *);
void CGIHexToASCII(char *);
