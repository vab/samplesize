/* xstage1.c - source file for function to calculate
 * sample size for one stage model.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage1.h"

struct solution_array
{
	double f[201][6][202];
	double b[201][6][202];
};


int one_stage(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int ss = 0;
	int n = 0, i = 0, j = 0;
	double p[2];
	double q[2];

	struct solution_array *sa;
	int xx=0,yy=0,zz=0;

	double beta = 0.0;
	double b0 = 0.0;
	double size = 0.0;
	double power = 0.0;

	sa = (struct solution_array *)malloc(sizeof(struct solution_array));
	if(sa == NULL)
	{
		fprintf(stderr,"Malloc Memory Allocation Call Failed.\n");

		return -1;
	}
	for(xx=0;xx<201;xx++)
	{
		for(yy=0;yy<6;yy++)
		{
			for(zz=0;zz<202;zz++)
			{
				sa->f[xx][yy][zz] = (double)0.0;
				sa->b[xx][yy][zz] = (double)0.0;
			}
		}
	}

	beta = 1.0 - powr;
	p[0] = p0;
	p[1] = p[0] + delta;
	b0 = 1.0-alpha;

	q[0] = 1-p[0];
	q[1] = 1-p[1];
	sa->b[1][0][0] = q[0];
	sa->b[1][1][0] = q[1];
	sa->b[1][0][1] = p[0];
	sa->b[1][1][1] = p[1];

	for(n=2;n<301;n++) /* do 15 */
	{
		for(i=0;i<2;i++) /* do 3 */
		{
			sa->b[n][i][0] = pow(q[i],n);
			sa->f[n][i][0]=sa->b[n][i][0];
			for(j=1;j<n;j++) /* do 2 */
			{
				sa->b[n][i][j]=n*p[i]*sa->b[n-1][i][j-1]/j;
				sa->f[n][i][j]=sa->f[n][i][j-1]+sa->b[n][i][j];
			} /* end do 2 */
		} /* end do 3 */
		for(j=1;j<n;j++) /* do 4 */
		{
			if( (sa->f[n][0][j]>=b0) && (sa->f[n][1][j]<=beta) )
			{
				size=1.0-sa->f[n][0][j];
				power=1.0-sa->f[n][1][j];
				ss=j/*+1*/;
				if(mail == 1)
				{
					email_results_one_stage("One-Stage",n,ss,size,power,address);
				}
				else
				{
					print_results_one_stage("One-Stage",n,ss,size,power);
				}
				if(sa != NULL)
				{
					free(sa);
				}

				return 0;
			}
		}  /* end do 4 */

	} /* end do 15 */

#ifdef DEBUG_PRINT
	printf("n= %d\n",n);
#endif
	if(sa != NULL)
	{
		free(sa);
	}


	return 0;
}
