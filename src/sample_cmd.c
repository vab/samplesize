/* sample_cmd.c - Main program file for test program.
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
	double alpha = 0.05;
	double p0 = 0.1;
	double delta = 0.15;
	double power = 0.8;

	int mail = 0;
	char *address = NULL;

	printf("Test results for the study designs:\n\n");

	while(p0 < 0.9)
	{
		printf("Test Values:\n");
		printf("alpha: %f, delta: %f, p0: %f, power: %f\n\n",alpha,delta,p0,power);

		printf("One Stage:\n");
		one_stage(alpha,delta,p0,power,mail,address);

		printf("Two Stage (H1):\n");
		two_stage_h1(alpha,delta,p0,power,mail,address);

		printf("Two Stage (H0):\n");
		two_stage_h0(alpha,delta,p0,power,mail,address);

		printf("Two Stage (H0 or H1):\n");
		two_stage_h0_h1(alpha, delta, p0, power, mail,address);

		printf("Three Stage (H1):\n");
		three_stage_h1(alpha,delta,p0,power,mail,address);

		printf("Three Stage (H0):\n");
		three_stage_h0(alpha,delta,p0,power,mail,address);

		printf("Three Stage (H1 or H0):\n");
		three_stage_h0_h1(alpha,delta,p0,power,mail,address);

		/* Two stage studies */
		printf("Two Sample One Stage:\n");
		two_samp_1stg(alpha,delta,p0,power,mail,address);

		printf("Two Sample Two Stage (H1):\n");
		two_samp_2stg_type1(alpha,delta,p0,power,mail,address);

		printf("Two Sample Two Stage (H0):\n");
		two_samp_2stg_type2(alpha,delta,p0,power,mail,address);

		printf("Two Sample Two Stage (H0 or H1):\n");
		two_samp_2stg_type3(alpha,delta,p0,power,mail,address);

		p0 = p0 + 0.1;
	}

	return 0;
}
