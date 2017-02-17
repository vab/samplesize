/* xstage3t1c.c - source file for function to calculate
 * sample size for three stage study conclude H1.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage3t1c.h"


struct solution_array
{
	double f[200][3][202];
	double b[200][3][202];
};


int three_stage_h1(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int b1, b2, b3, b11, bb, bbb;
	int i, j, n1, n2, n3, ii, n11;
	int m1, m2, m3, k1, maxn;

	double p[3];
	double q[3];
	double sum1[3], sum2[3];
	double e1, e2, asn;
	double power[3];
	double prob[3];
	/*
	double f[200][3][201];
	double b[200][3][201];
	*/
	struct solution_array *sa;

	int xx=0,yy=0,zz=0;

	sa = (struct solution_array *)malloc(sizeof(struct solution_array));
	if(sa == NULL)
	{
		fprintf(stderr,"Malloc Memory Allocation Call Failed.\n");

		return -1;
	}
	for(xx=0;xx<200;xx++)
	{
		for(yy=0;yy<3;yy++)
		{
			for(zz=0;zz<203;zz++)
			{
				sa->f[xx][yy][zz] = (double)0.0;
				sa->b[xx][yy][zz] = (double)0.0;
			}
		}
	}


	power[1]=alpha;
	power[2]=powr;
	p[1]=p0;
	p[2] = p[1] + delta;

	maxn=nstage1(power[1], power[2], p[1], p[2]);
/*	printf("<br><b>maxn= %d</b><br>\n",maxn); */
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

	q[1]=1.0-p[1];
	q[2]=1.0-p[2];
	sa->b[1][1][1]=q[1];
	sa->b[1][2][1]=q[2];
	sa->b[1][1][2]=p[1];
	sa->b[1][2][2]=p[2];

	for(n1=2; n1<=maxn; n1++) /* do 15 */
	{
		n11=n1+1;
		for(i=1; i<=2; i++) /* do 3 */
		{
			sa->b[n1][i][1]=pow(q[i],n1);
			sa->f[n1][i][1]=sa->b[n1][i][1];
			for(j=2; j<=n11; j++) /* do 2 */
			{
				sa->b[n1][i][j]=(double)n1*p[i]*sa->b[n1-1][i][j-1]/(double)(j-1);
				sa->f[n1][i][j]=sa->f[n1][i][j-1]+sa->b[n1][i][j];
			} /* end do 2 */
		} /* end do 3 */

		m1=n1-1;
		for(n2=2; n2<=n1; n2++) /* do 10 */
		{
			if(n1+n2 > maxn) break; /* go to 15 */
			m2=n1+n2-1;
			for(n3=2; n3<=n2; n3++) /* do 11 */
			{
				if(n1+n2+n3 > maxn) break; /* go to 10 */
				m3=n1+n2+n3-1;
				for(b1=1; b1<=m1; b1++) /* do 12 */
				{
					b11=b1+1;
					for(b2=b1; b2<=m2; b2++) /* do 13 */
					{
						for(b3=b2; b3<=m3; b3++) /* do 14 */
						{
							for(ii=1; ii<=2; ii++) /* do 4 */
							{
								sum1[ii]=0.0;
								sum2[ii]=0.0;

								for(i=1; i<=b11; i++) /* do 5 */
								{
									k1=b2-i+2;
									if(k1>n2)
										sum1[ii]=sum1[ii]+sa->b[n1][ii][i];
									else if((k1>0) && (k1<=n2))
										sum1[ii]=sum1[ii]+sa->b[n1][ii][i]*sa->f[n2][ii][k1];
								} /* end do 5 */
								for(i=1; i<=b11; i++) /* do 6 */
								{
									bb=b2-i+2;
									for(j=1; j<=bb; j++) /* do 7 */
									{
										bbb=b3-i-j+3;
										if(bbb>n3)
											sum2[ii]=sum2[ii]+sa->b[n1][ii][i]*sa->b[n2][ii][j];
										else if((bbb>0) && (bbb<=n3))
											sum2[ii]=sum2[ii]+sa->b[n1][ii][i]*sa->b[n2][ii][j]*sa->f[n3][ii][bbb];
									} /* end do 7 */
								} /* end do 6 */
								prob[ii]=1.0-sum2[ii];
							} /* end do 4 */

							if(prob[1]>power[1]) continue;
							if(prob[2]<power[2]) continue;

							e1=(double)n1+(double)n2*sa->f[n1][1][b11]+(double)n3*sum1[1];
							e2=(double)n1+(double)n2*sa->f[n1][2][b11]+(double)n3*sum1[2];
							asn=(e1+e2)/2.0;
      
      							#ifdef DEBUG_PRINT
							printf("n1= %d b1= %d n2= %d b2= %d n3=%d b3=%d\n",n1,b1,n2,b2,n3,b3);
							printf("prob1= %f prob2= %f\n",prob[1],prob[2]);
							printf("e1= %f e2= %f asn= %f\n",e1,e2,asn);
							#ifdef SUPER_DEBUG_PRINT
							printf("(%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,n3,b3,prob[1],prob[2]);
							#endif
      							#else
							if(mail == 1)
							{
								email_results_three_stage_h1("Three-Stage:  Stop early only to conclude H1",n1,b1,n2,b2,n3,b3,prob[1],prob[2],e1,e2,asn,address);
							}
							else
							{
								print_results_three_stage_h1("Three-Stage:  Stop early only to conclude H1",n1,b1,n2,b2,n3,b3,
									prob[1],prob[2],e1,e2,asn);

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
	}

	n1=n1-1;
	printf("n1 = %d\n",n1);
	printf("An ERROR has occurred\n");
	printf("n1 cannot exceed the 1 stage sample size\n");

	if(sa != NULL)
	{
		free(sa);
	}



	return 0;
}




