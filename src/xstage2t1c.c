/* xstage2t1c.c - source file for function to calculate
 * sample size for two stage study conclude H1.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage2t1c.h"

struct solution_array
{
	double f[201][6][202];
	double b[201][6][202];
};

int two_stage_h1(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int b1 = 0;
	int b2 = 0;
	int b11 = 0;
	int maxn = 0;
	
	double p[3];
	double q[3];
	double sum = 0.0;
	double e1 = 0.0;
	double e2 = 0.0;
	double asn = 0.0;
	double prob[3];
	double power[3];
	/*
	double f[201][6][202];
	double b[201][6][202];
	*/
	struct solution_array *sa;

	int xx=0,yy=0,zz=0;

	int n1 = 0;
	int n11 = 0;
	int i = 0;
	int j = 0;
	int m1 = 0;
	int n2 = 0;
	int m2 = 0;
	int ii = 0;
	int k = 0;

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

	power[1] = alpha;
	power[2] = powr;
	p[1] = p0;
	p[2] = p[1] + delta;

	maxn = nstage1(power[1],power[2],p[1],p[2]);
	if(maxn == 0)
	{
		printf("No Solution\n");
		if(sa != NULL)
		{
			free(sa);
		}
		
		return -1;
	}
	else if(maxn > 200)
	{
		printf("Maxn is greater than 200.\n");
		printf("The program must be redimensioned\n");
		if(sa != NULL)
		{
			free(sa);
		}
		
		return -1;
	}
	
	q[1] = 1-p[1];
	q[2] = 1-p[2];
	sa->b[1][1][1] = q[1];
	sa->b[1][2][1] = q[2];
	sa->b[1][1][2] = p[1];
	sa->b[1][2][2] = p[2];

	for(n1=2;n1<=maxn;n1++) /* do 15 */
	{
		n11=n1+1;
		for(i=1;i<=2;i++) /* do 3 */
		{
			sa->b[n1][i][1]=pow(q[i],n1);
			sa->f[n1][i][1]=sa->b[n1][i][1];
			for(j=2;j<=n11;j++) /* do 2 */
			{
				sa->b[n1][i][j]=n1*p[i]*sa->b[n1-1][i][j-1]/(j-1);
				sa->f[n1][i][j]=sa->f[n1][i][j-1]+sa->b[n1][i][j];
			} /* end do 2 */
		} /* end do 3 */
		m1=n1-1;
		for(b1=1;b1<=m1;b1++) /* do 10 */
		{
			b11=b1+1;
			for(n2=2;n2<=n1;n2++) /* do 11 */
			{
				if(n1+n2 > maxn)
				{
					/* stop and return to the prev loop */
					break;
				}
				m2=n1+n2-1;
				for(b2=b1;b2<=m2;b2++) /* do 12 */
				{
					for(ii=1;ii<=2;ii++) /* do 4 */
					{
						sum=0.0;
						for(i=1;i<=b11;i++) /* do 5 */
						{
							k=b2-i+2;
							if(k>n2)
							{
								sum=sum+sa->b[n1][ii][i];
							}
							else if(k<=n2)
							{
								sum=sum+sa->b[n1][ii][i]*sa->f[n2][ii][k];
							}		
						} /* end do 5 */
						prob[ii] = 1-sum;
					} /* end do 4 */	
					if(prob[1] > power[1])
					{
						continue;
					}
					if(prob[2] < power[2])
					{
						continue;
					}
					e1=n1+n2*sa->f[n1][1][b1+1];
					e2=n1+n2*sa->f[n1][2][b1+1];
					asn=(e1+e2)/2;
					#ifdef SUPER_DEBUG_PRINT
					printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,prob[1],prob[2]);
					#endif
					#ifdef DEBUG_PRINT
					printf("n1=%d b1=%d n2=%d b2=%d\n",n1,b1,n2,b2);
					printf(" %10.8f %10.8f\n",prob[1], prob[2]);
					printf(" e1=%10.8f e2=%10.8f asn=%10.8f\n",e1,e2,asn);
					#endif
					if(mail == 1)
					{
						email_results_two_stage_h1("Two-Stage:  Stop early only to conclude H1",n1,b1,n2,b2,prob[1],prob[2],e1,e2,asn,address);
					}
					else
					{
						print_results_two_stage_h1("Two-Stage:  Stop early only to conclude H1",n1,b1,n2,b2,prob[1],prob[2],e1,e2,asn);
					}
					if(sa != NULL)
					{
						free(sa);
					}

					return 0;
				} /* end do 12 */
			} /* end do 11 */
		} /* end do 10 */
	} /* end do 15 */

	n1=n1-1;
	printf("%d\n",n1);
	printf("An ERROR has occured\n");
	printf("n1 cannot exceed the stage 1 sample size\n");

	if(sa != NULL)
	{
		free(sa);
	}

	return 0;
}
