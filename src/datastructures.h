/* datastructures.h - Data Structures Definitions 
 * and Data Structure Routines Header File.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */
 

#ifndef DATASTRUCTURES
#define DATASTRUCTURES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct name_value_pair_dllst
{
	unsigned char *name;
	unsigned char *value;

	struct name_value_pair_dllst *prev;
	struct name_value_pair_dllst *next;
};

struct value_dllst
{
	unsigned char *value;

	struct value_dllst *next;
	struct value_dllst *prev;
};


void free_name_value_pair_dllst(struct name_value_pair_dllst *);
struct name_value_pair_dllst *get_first_pair(struct name_value_pair_dllst *);
char *get_value(struct name_value_pair_dllst *,char *);

struct value_dllst *get_first_value(struct value_dllst *);
#endif
