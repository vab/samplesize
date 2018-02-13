/* datastructures.c - Main datastructure routine source file.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "datastructures.h"


void free_name_value_pair_dllst(struct name_value_pair_dllst *the_list)
{
	struct name_value_pair_dllst *walk_pair = NULL;
	struct name_value_pair_dllst *next_pair = NULL;

	if(the_list != NULL)
	{
		walk_pair = (struct name_value_pair_dllst *)get_first_pair(the_list);
		while(walk_pair != NULL)
		{
			next_pair = walk_pair->next;
			free(walk_pair->name);
			free(walk_pair->value);
			free(walk_pair);
			walk_pair = next_pair;
		}
	}

	return;
}

struct name_value_pair_dllst *get_first_pair(struct name_value_pair_dllst *the_list)
{
	if(the_list != NULL)
	{
		while(the_list->prev != NULL)
		{
			the_list = the_list->prev;
		}
	}

	return the_list;
}

char *get_value(struct name_value_pair_dllst *the_list,char *name)
{
	if(the_list == NULL) return NULL;
	/* Rewind to the beginning */
	the_list = get_first_pair(the_list);

	while(memcmp(the_list->name,name,strlen(name)) != 0)
	{
		the_list = the_list->next;
		if(the_list == NULL) return NULL;
	}

	return the_list->value;
}

struct value_dllst *get_first_value(struct value_dllst *values)
{
	if(values != NULL)
	{
		while(values->prev != NULL)
		{
			values = values->prev;
		}
	}

	return values;
}

