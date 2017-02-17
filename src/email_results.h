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

int email_results_Three_stage_h0_h1(char *, int, int, int, int, int, int, int, int, double, double,
	double, double, double, char *);

int email_results_two_sample_one_stage(char *, int, int, int, double, double, char *);

int email_results_two_sample_two_stage_h1(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn, char *);

int email_resluts_two_sample_two_stage_h0(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn, char *);

int email_results_two_sample_two_stage_h0_h1(char *study_type,int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn, char *);
