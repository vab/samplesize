/* nstage1.c - Source file for function to compute
 * one stage of multi-stage sample size calculations.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "nstage1.h"


/*  a C function to return 'n' for the 1 stage model
 *  n is the one stage sample size.  The sample size
 *  of other study types must be less than or equal 
 *  to n.
 */
int nstage1(double pow1, double pow2, double p0, double p1)
{	
	int ss = 0;
	int n = 0, i = 0, j = 0;
	double p[2];
	double q[2];

	double f[501][2][502];
	double b[501][2][502];
	double alpha = 0.0;
	double beta = 0.0;
	double b0 = 0.0;
	double size = 0.0;
	double power = 0.0;

	alpha = pow1;
	beta = 1.0 - pow2;
	p[0] = p0;
	p[1] = p1;
	b0 = 1.0-alpha;

	q[0] = 1-p[0];
	q[1] = 1-p[1];
	b[1][0][0] = q[0];
	b[1][1][0] = q[1];
	b[1][0][1] = p[0];
	b[1][1][1] = p[1];

	for(n=2;n<301;n++) /* do 15 */
	{
		for(i=0;i<2;i++) /* do 3 */
		{
			b[n][i][0] = pow(q[i],n);
			f[n][i][0]=b[n][i][0];
			for(j=1;j<n;j++) /* do 2 */
			{
				b[n][i][j]=n*p[i]*b[n-1][i][j-1]/j;
				f[n][i][j]=f[n][i][j-1]+b[n][i][j];
			} /* end do 2 */
		} /* end do 3 */
		for(j=1;j<n;j++) /* do 4 */
		{
			if( (f[n][0][j]>=b0) && (f[n][1][j]<=beta) )
			{
				size=1.0-f[n][0][j];
				power=1.0-f[n][1][j];
				ss=j++;

				return n;
			}
		}  /* end do 4 */


	} /* end do 15 */


	return n;
}
