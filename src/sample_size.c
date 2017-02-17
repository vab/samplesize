/* sample_size.c - Main program file.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@cancer.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "sample_size.h"


int main(int argc, char *argv[])
{
	char *method = NULL;
	long content_length = 0;
	char *content = NULL;
	char *val = NULL;
	char *val_2 = NULL;
	char *val_3 = NULL;
	char *val_4 = NULL;
	char *val_5 = NULL;
	char *val_6 = NULL;
	char *val_7 = NULL;

	double alpha = 0.0;
	double delta = 0.0;
	double p0 = 0.0;
	double power = 0.0;

	int mail = 0;

	struct name_value_pair_dllst *form = NULL;

	setlimit();

	/* Get the Search Info. */
	method = (char *)getenv("REQUEST_METHOD");

	if(method == NULL)
        {
		/* Program is probably being run from command Line. */
		do_error_page("The method is null.  You cannot run this program from the command line.\n");

		return 0;
	}
	else if(strcmp(method,"GET") == 0)
	{
		/* Program should only be called with POST method. */
		do_error_page("Program called with GET method rather than POST");

		return 0;
	}
	else if(strcmp(method,"POST") == 0)
	{
		/* Valid Search attempt */
		content_length = atoi(getenv("CONTENT_LENGTH"));
		if(content_length < 3)
		{
			do_error_page("Please make sure to fill in all the requested variables.");

			return 0;
		}
		else if(content_length > 1000)
		{
			do_error_page("Excessive content length detected.  Please use less than 100 characters.");

			return 0;
		}
		/* Read in the QUERY */
		content = (char *)malloc(content_length+1);
                if(content == NULL)
                {
                        do_error_page("Server was unable to malloc memory.  Server out of memory.");

			return 0;
		}
                fread(content,1,content_length,stdin);
                content[content_length] = '\0';

		/* Process the CGI Form. */
		form = parse_name_value_pairs(content);
	}
	else
	{
		/* This should never occur.  Must be some type of corruption. */
		do_error_page("There was some type of corruption of the method variable. Non-Compliant web browser?");

		return 0;
	}


	val = get_value(form,"alpha");
	if(val == NULL)
	{
		do_error_page("You must specify an alpha.\n");

		return 0;
	}
	alpha = atof(val);
	val_2 = get_value(form,"del");
	if(val_2 == NULL)
	{
		do_error_page("You must specify a delta.\n");

		return 0;
	}
	delta = atof(val_2);
	val_3 = get_value(form,"p0");
	if(val_3 == NULL)
	{
		do_error_page("You must specify a p0.\n");

		return 0;
	}
	p0 = atof(val_3);
	val_4 = get_value(form,"power");
	if(val_4 == NULL)
	{
		do_error_page("You must specify a power.\n");

		return 0;
	}
	power = atof(val_4);

	val_5 = get_value(form,"mail");
	mail = atoi(val_5);

	val_6 = get_value(form,"address");
	if((mail) && (val_6 == NULL))
	{
		do_error_page("You must enter a valid email address if you would like to have the the study results emailed to you..");
		
		return 0;
	}
	else if(mail == 1)
	{
		/* Security Test of Mail */
		if( (strchr(val_6, '\'') != NULL) || (strchr(val_6, ';') != NULL) || (strchr(val_6, '|') != NULL)
		     || (strchr(val_6, '\\') != NULL) || (strchr(val_6, '&') != NULL) || (strchr(val_6, '$') != NULL)
		     || (strchr(val_6, '(') != NULL)  || (strchr(val_6, ')') != NULL) || (strchr(val_6, '[') != NULL)
		     || (strchr(val_6, ']') != NULL)  || (strchr(val_6, '<') != NULL)  || (strchr(val_6, '>') != NULL)
		     || (strchr(val_6, '`') != NULL)  || (strchr(val_6, '*') != NULL))
		{
			do_error_page("I'm sorry, for security reasons we cannot accept your email address.  Please, contact <A HREF=\"mailto:james.kepner@cancer.org\">Dr. Kepner</a>.");

			return 0;
		}

		printf("Content-type: text/html\n\n");
		print_header();
		printf("<P><B>Test Values:</B> alpha: %f, delta: %f, p0: %f, power: %f\n",alpha,delta,p0,power);
		printf("<P>Thank you for using the Sample Size calculator.<P>Your results will be\n");
		printf("emailed to you at: %s\n",val_6);
		printf("<P>You may close your browser window at any time.\n");

		fflush(0);
	}
	else
	{
		printf("Content-type: text/html\n\n");
		print_header();

		printf("<P><B>Test Values:</B> alpha: %f, delta: %f, p0: %f, power: %f\n",alpha,delta,p0,power);
		printf("<P>If no results appear, please resubmit your request and ask to have the results emailed to you.\n");
		printf("<P>Please Wait, Calculating...\n");
		
		fflush(0);
	}

	val_7 = get_value(form,"study_type");
	if(val_7 == NULL)
	{
		do_error_page("There seems to be a problem with the web page.  Study Type was null.\n");

		return 0;
	}

	if (strcmp(val_7, "One-Stage") == 0)
	{
		one_stage(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Two-Stage: stop early only to conclude H1") == 0 )
	{
		two_stage_h1(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Two-Stage: stop early only to conclude H0") == 0 )
	{
		two_stage_h0(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Two-Stage: stop early to conclude either H0 or H1") == 0 )
	{
		two_stage_h0_h1(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Three-Stage: stop early only to conclude H0") == 0 )
	{
		three_stage_h0(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Three-Stage: stop early only to conclude H1") == 0 )
	{
		three_stage_h1(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Three-Stage: stop early to conclude either H0 or H1") == 0 )
	{
		three_stage_h0_h1(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Two-Sample: One-Stage") == 0)
	{
		two_samp_1stg(alpha, delta, p0, power, mail, val_6);
	}
	else if ( strcmp(val_7, "Two-Sample: Two-Stage: stop early only to conclude H0") == 0)
	{
		two_samp_2stg_type2(alpha,delta,p0,power,mail,val_6);
	}
	else if ( strcmp(val_7, "Two-Sample: Two-Stage: stop early only to conclude H1") == 0)
	{
		two_samp_2stg_type1(alpha,delta,p0,power,mail,val_6);
	}
	else if ( strcmp(val_7, "Two-Sample: Two-Stage: stop early to conclude either H0 or H1") == 0)
	{
		two_samp_2stg_type3(alpha,delta,p0,power,mail,val_6);
	}
	else
	{
		printf("<b><center>Error in calling correct Stage.<br>Please alert\n");
		printf("Dr. Kepner <a href=\"mailto:James.Kepner@cancer.org\">James.Kepner@cancer.org</a></center></b>");
	}

	print_footer();

	fflush(0);

	free_name_value_pair_dllst(form);

	
	return 0;
}


static void setlimit(void)
{
	struct rlimit lim;

	if (getrlimit(RLIMIT_STACK, &lim) != 0)
	{
		(void)printf("Couldn't retrieve limit\n");

		return;
	}
	lim.rlim_cur = 4294967295;
	if (setrlimit(RLIMIT_STACK, &lim) != 0)
	{
		(void)printf("Couldn't set limit\n");

		return;
	}
	
	return;
}
