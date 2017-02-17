/* display_results.h - Header file for functions to
 * display results of sample size calculations.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@cancer.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>


/* You can get rid of the display_results files if you want
   merging the code back into the individual files.  I just
   pulled it out for clarity to parallel with email_results.
*/
int print_results_one_stage(char *, int, int, double, double);

int print_results_two_stage_h1(char *, int, int, int, int,
          double, double, double, double, double);

int print_results_two_stage_h0(char *, int, int, int, int,
        double, double, double, double, double);

int print_results_two_stage_h0_h1(char *, int, int, int, int, int,
           double, double, double, double, double);

int print_results_three_stage_h1(char *, int, int, int, int, int, int,
         double, double, double, double, double);

int print_results_three_stage_h0(char *,int, int, int, int, int, int,
			double, double, double, double, double);

int print_results_three_stage_h0_h1(int, int, int, int, int, int, int, int,
			double, double, double,double,double);

int print_results_two_sample_one_stage(char *, int, int, int, double, double);

int print_results_two_sample_two_stage_h1(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn);

int print_resluts_two_sample_two_stage_h0(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn);

int print_results_two_sample_two_stage_h0_h1(char *study_type,int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn);
