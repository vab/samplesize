/* email_results.h - Header file for functions to email
 * results of sample size calculations.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>


/* One Stage Results */
int email_results_one_stage(char *, int, int, double, double, char *);

/* Two Stage Results */
int email_results_two_stage_h1(char *, int, int, int, int, double, double, double,
	double, double, char *);

int email_results_two_stage_h0(char *, int, int, int, int, double, double, double,
	double, double, char *);

int email_results_two_stage_h0_h1(char *, int,int,int,int,int,double, double, double,
	double, double, char *);

/* Three Stage Results */
int email_results_three_stage_h1(char *, int, int, int, int, int, int, double, double, double,
	double, double, char *);

int email_results_three_stage_h0(int, int, int, int, int, int, double, double, double, double,
	double, char *);

int email_results_three_stage_h0_h1(int, int, int, int, int, int, int, int, double, double, double,
	double, double, char *);

/* Two Sample Results */
int email_results_two_sample_one_stage(char *, int, int, int, double, double, char *);

int email_results_two_sample_two_stage_h1(char *, int, int, int, int, double, double, double,
	double, double, char *);

int email_resluts_two_sample_two_stage_h0(char *, int, int, int, int, double, double, double,
	double, double, char *);

int email_results_two_sample_two_stage_h0_h1(char *, int, int, int, int, int, double, double,
	double, double, double, char *);
