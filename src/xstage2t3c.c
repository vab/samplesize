/* xstage2t3c.c - source file for function to calculate
 * sample size for two stage study conclude H0 or H1.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage2t3c.h"


struct solution_array
{
	double f[201][3][202];
	double b[201][3][202];
};


int two_stage_h0_h1(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int a1=0, a2=0, b1=0, b2=0, a11=0, b11=0, aa1=0, abest=0, maxn=0;
	double p[3];
	double q[3];
	double sum[3][3];
	double e1, e2, asn;
	double power[3];
	double prob[3];
	double prob12, prob22;
	/*
	double f[201][3][202];
	double b[201][3][202];
	*/
	int i, j, n1, n2, ii;
	int n11, m1, m2, k;

	struct solution_array *sa;

	int xx=0,yy=0,zz=0;

	sa = (struct solution_array *)malloc(sizeof(struct solution_array));
	if(sa == NULL)
	{
		fprintf(stderr,"Malloc Memory Allocation Call Failed.\n");

		return -1;
	}
	for(xx=0;xx<201;xx++)
	{
		for(yy=0;yy<3;yy++)
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

	maxn = nstage1(power[1], power[2], p[1], p[2]);

	/*  printf("<br><b>maxn= %d\n</b><br>",maxn);*/
	fflush(0);

	if(maxn == 0)
	{
		printf("No Solution\n");
		if(sa != NULL)
		{
			free(sa);
		}


		return 0;
	}
	if(maxn > 200)
	{
		printf("ERROR - maxn is greater than 200\n");
		printf("redimension the C program\n");
		if(sa != NULL)
		{
			free(sa);
		}

		return 0;
	}

	/* init p & q */
	q[1] = 1.0 - p[1];
	q[2] = 1.0 - p[2];

	/* initizlize binomial solution arrays */
	/* Do 1 */
	sa->b[1][1][1] = q[1];
	sa->b[1][1][2] = p[1];
	sa->b[1][2][1] = q[2];
	sa->b[1][2][2] = p[2];
	/* end 1 */

	/* Do 15 */
	for(n1=2; n1<=maxn; n1++)
	{
		/* if (n1>=3)
		{
			printf("n1=%d,n11=%d,m1=%d,b1=%d,a1=%d,a11=%d,m2=%d,ii=%d,k=%d\n",n1,n11,m1,b1,a1,a11,m2,ii,k);
		} */

		/* Do 3 */
		for(i=1; i<=2; i++)
		{
			sa->b[n1][i][1]=pow(q[i],(double)n1);
			sa->f[n1][i][1]=sa->b[n1][i][1];
			n11=n1+1;
			/* Do 2 */
			for(j=2; j<=n11; j++)
			{
				sa->b[n1][i][j]=(double)n1*p[i]*sa->b[n1-1][i][j-1]/(double)(j-1);
				sa->f[n1][i][j]=sa->f[n1][i][j-1]+sa->b[n1][i][j];
			} /* End 2 */
		} /* End 3 */

		m1=n1-1;
		/* Do 10 */
		for(b1=1; b1<=m1; b1++)
		{
			b11=b1+1;
			/* Do 11 */
			for(a1=1;a1<=b1;a1++)
			{
				a11=a1+1;
				/* Do 12 */
				for(n2=2; n2<=n1; n2++)
				{
					if(n1+n2 > maxn) break; /* Check: Go to */
					m2=n1+n2-1;
					/* Do 13 */
					for(b2=b1; b2<=m2; b2++)
					{
						/* Do 4 */
						for(ii=1; ii<=2; ii++)
						{
							sum[ii][2]=0.0;
							/* do 5 */
							for(i=a11; i<=b11; i++)
							{
								k=b2-i+2;
								sum[ii][2]=sum[ii][2]+sa->b[n1][ii][i]*sa->f[n2][ii][k];
								/* printf("b[n1:%d,ii:%d,i:%d]:%f\n",n1,ii,i,b[n1+ii*3+i*202]);*/
							} /* End 5 */
						} /* End 4 */

						prob[1]=1.0-sa->f[n1][1][a1]-sum[1][2];
						prob[2]=1.0-sa->f[n1][2][a1]-sum[2][2];

				/*		if((prob[1]<=(power[1]-.01)) || (prob[1]>pow(1))) continue; /* Go to 13 */
						if(prob[1]>power[1]) continue; /* go to 13 */
						if(prob[2]<power[2]) continue; /* go to 13 */
						aa1=a1;
						/* 30 */
						while(prob[2]>=power[2])
						{
							abest=aa1;
							prob12=prob[1];
							prob22=prob[2];
							aa1=aa1+1;
/*							printf("aa1:%d\tb1:%d\n", aa1, b1); */
							if(aa1>b1) break;

							k=b2-aa1+2;
							prob[1]=prob[1]-sa->b[n1][1][aa1]*(1.0-sa->f[n2][1][k]);
							prob[2]=prob[2]-sa->b[n1][2][aa1]*(1.0-sa->f[n2][2][k]);
						}
						e1=(double)n1+(double)n2*(sa->f[n1][1][b1+1]-sa->f[n1][1][abest]);
						e2=(double)n1+(double)n2*(sa->f[n1][2][b1+1]-sa->f[n1][2][abest]);
						asn=(e1+e2)/2.0;
						#ifdef DEBUG_PRINT
						#ifdef SUPER_DEBUG_PRINT
						printf("(%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,abest,b1,n2,b2,prob12,prob22);
						#else
						printf("n1= %d abest=%d b1= %d n2= %d b2= %d\n",n1,abest,b1,n2,b2);
       						printf("%f %f\n",prob12,prob22);
						printf("e1= %f e2= %f asn= %f\n",e1,e2,asn);
						#endif
						#else
         					if(mail == 1)
						{
							email_results_two_stage_h0_h1("Two-Stage:  Stop early only to conclude either H0 or H1",n1,abest,b1,n2,b2,
								prob12,prob22,e1,e2,asn,address);
						}
						else
						{
							print_results_two_stage_h0_h1("Two-Stage:  Stop early only to conclude either H0 or H1",n1,abest,b1,n2,b2,
								prob12,prob22,e1,e2,asn);
						}
						#endif

						if(sa != NULL)
						{
							free(sa);
						}

						
						return 0;
					}
				}
			}
		}
	}

	n1=n1-1;
	printf("n1= %d\n",n1);
	printf("An ERROR has occurred\n");
	printf("n1 cannot exceed the 1 stage sample size\n");

	if(sa != NULL)
	{
		free(sa);
	}



	return 0;
}
