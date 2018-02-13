/* cgi.c - CGI functions
 * Copyright (C) 2001-2005 Dr. James L. Kepner
 * james.kepner@cancer.org
 *
 * This file is part of samplesize
 */

#include "cgi.h"


void print_header(void)
{
	printf("<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	printf("<BODY BGCOLOR=#FFFFFF\n");
	printf("<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	printf("<TR VALIGN=top>\n");
	printf("<TD ROWSPAN=2><IMG SRC=\"images/acs.png\"></TD>\n");
	printf("<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	printf("</FONT></FONT></TD>\n");
	printf("</TR>\n");
	printf("<TR>\n");
	printf("<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	printf("<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	printf("your comments, suggestions, and corrections to\n");
	printf("<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	printf("</TR>\n");
	printf("<TR>\n");
	printf("<TD COLSPAN=2>\n");
	printf("</TD>\n");
	printf("</TR>\n");
	printf("</TABLE>\n");
	printf("<HR SIZE=0 WIDTH=100%%>\n");

	return;
}

void print_footer(void)
{
	printf("<HR SIZE=0 WIDTH=100%%>\n");
	printf("<CENTER><H6>Kepner Sample Size Calculator\n");
	printf("<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:vab@protonmail.com\">vab@protonmail.com</A>]</H6></CENTER>\n");
	printf("</BODY></HTML>\n");

	return;
}

void do_error_page(char *error)
{
	printf("Content-Type: text/html\n\n");
	printf("<HTML><HEAD><TITLE>Sample Size System Error</TITLE></HEAD><BODY>\n");
	printf("<CENTER><H1>Sample Size System Error</H1></CENTER>\n");
	printf("The following Sample Size System Error Occurred:\n");
	printf("%s\n",error);
	printf("</BODY></HTML>\n\n");

	return;
}

struct name_value_pair_dllst *parse_name_value_pairs(char *data)
{
	struct name_value_pair_dllst *cgidata = NULL;

	char *dataptr = NULL;
    char *name = NULL;
    char *true_name = NULL;
    char *true_value = NULL;


	cgidata = (struct name_value_pair_dllst *)malloc(sizeof(struct name_value_pair_dllst));
	if(cgidata == NULL)
	{
		fprintf(stderr,"Malloc call failed: Out of memory.\n");

		return NULL;
	}

	cgidata->prev = NULL;
	cgidata->next = NULL;
	cgidata->name = NULL;
	cgidata->value = NULL;

	dataptr = &data[0];

    name = (char *)strtok(dataptr,"&");
    do
    {
		true_name = &name[0];
		true_value = (char *)memchr(name,'=',strlen(name));
		true_value[0] = '\0';
                true_value++;
                if(true_value == NULL) fprintf(stderr,"Unexpected Error: The value is null.");
		CGIHexToASCII(true_value);

		cgidata->name = (char *)malloc(strlen(true_name)+2);
		strncpy(cgidata->name,true_name,strlen(true_name)+1);
		cgidata->value = (char *)malloc(strlen(true_value)+2);
		strncpy(cgidata->value,true_value,strlen(true_value)+1);
		cgidata->next = (struct name_value_pair_dllst *)malloc(sizeof(struct name_value_pair_dllst));
		if(cgidata->next == NULL)
		{
			fprintf(stderr,"Failed to malloc:  out of memory\n");
			return NULL;
		}
		cgidata->next->prev = cgidata;
		cgidata = cgidata->next;
		cgidata->next = NULL;
		cgidata->name = NULL;
		cgidata->value = NULL;

    } while((name = (char *)strtok('\0',"&")));
	cgidata = cgidata->prev;
	free(cgidata->next);
	cgidata->next=NULL;

	return cgidata;
}

/*
   This code in part came from "C Unleashed", it was written by Chad
   Dixon. ISBN: 0-672-31896-2
*/
void CGIHexToASCII(char *s)
{
        static const char *Hex = "0123456789ABCDEF";
        unsigned int Ascii=0;
        char *p;
        char *Match;
        int Error = 0;

        for(p = s; !Error && *s !='\0'; s++)
        {
                if(*s == '%')
                {
                        s++;
                        if((Match = (char *)strchr(Hex, *s)) != NULL)
                        {
                                Ascii = (unsigned int)(Match - Hex);

                                s++;
                                if((Match = (char *)strchr(Hex, *s)) != NULL)
                                {
                                        Ascii <<= 4;
                                        Ascii |= (unsigned int)(Match - Hex);

                                        *p++ = (char)Ascii;
                                }
                        }
                }
                else if(*s == '+')
                {
                          *p++ = ' ';
                }
                else
                {
                     *p++ = *s;
                }
        }
        *p  = '\0';
}
