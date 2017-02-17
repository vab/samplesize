/* xstage3t2c.c - source file for function to calculate
 * sample size for three stage study conclude H0.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage3t2c.h"


struct solution_array
{
	double f[200][2][201];
	double b[200][2][201];
};


int three_stage_h0(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int b1, b2, b3, b11, b21, b22, b31, b32;
	int iflag;
	int i, j, n1, n2, n3, ii;
	int m1, m2, m3, k2, k3, maxn;

	double p[2];
	double q[2];
	double sum1[2], sum2[2];
	double e1, e2, asn;
	double power[2];
	double prob[2];
	/*
	double f[200][2][201];
	double b[200][2][201];
	*/
	struct solution_array *sa;

	int xx=0,yy=0,zz=0;

	time_t current, last_time, elapse, start;

	sa = (struct solution_array *)malloc(sizeof(struct solution_array));
	if(sa == NULL)
	{
		fprintf(stderr,"Malloc Memory Allocation Call Failed.\n");

		return -1;
	}
	for(xx=0;xx<200;xx++)
	{
		for(yy=0;yy<2;yy++)
		{
			for(zz=0;zz<201;zz++)
			{
				sa->f[xx][yy][zz] = (double)0.0;
				sa->b[xx][yy][zz] = (double)0.0;
			}
		}
	}

	start = time(NULL);
	last_time = 0;
  
	iflag=0;
	p[0] = p0;
	power[0] = alpha;
	power[1] = powr;

	p[1] = p[0] + delta;

	maxn=nstage1(power[0], power[1], p[0], p[1]);

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

	for(i=0; i<=1; i++)
	{
		q[i]=1.0-p[i];
		sa->b[1][i][0]=q[i];
		sa->b[1][i][1]=p[i];
	}

	for(n1=2; n1<=maxn; n1++)
	{

		current = time(NULL);
		elapse = current - start;
		if ( last_time != elapse )
		{
		/*	printf("\n<br>Calculating... Elapsed time:  %d seconds.<br>", (int) elapse );*/
			last_time = elapse;
		}
		fflush(0);

		m1=n1-1;
		for(i=0; i<=1; i++)
		{
			sa->b[n1][i][0]=pow(q[i], (double)n1);
			sa->f[n1][i][0]=sa->b[n1][i][0];
			/*printf("f[%d][%d][0]=%E b=%E\n",n1,i,f[n1][i][0],b[n1][i][0]);*/
			for(j=1; j<=n1; j++)
			{
				sa->b[n1][i][j]=(double)n1*p[i]*sa->b[n1-1][i][j-1]/(double)j;
				sa->f[n1][i][j]=sa->f[n1][i][j-1]+sa->b[n1][i][j];
				/*printf("f[%d][%d][%d]=%E b=%E\n",n1,i,j,f[n1][i][j],b[n1][i][j]); */
			}
		}

		for(n2=2; n2<=n1; n2++)
		{
			if(n1+n2 > maxn) break;
			m2=n1+n2-1;
			for(n3=2; n3<=n2; n3++)
			{
				/*  if(n1>=24 && n2>=24 && n3>=20)  printf("n1=%d n2=%d n3=%d\n",n1,n2,n3);*/
				if(n1+n2+n3 > maxn) break;
				m3=n1+n2+n3-1;
				for(b3=m3; b3>=0; b3--)
				{
					if(b3<=m2) b31=b3;
					else b31=m2;
					for(b2=b31; b2>=0; b2--)
					{
						b21=b2+1;
						if(b2<=m1) b22=b2;
						else b22=m1;
						for(b1=b22; b1>=0; b1--)
						{
							b11=b1+1;
							for(ii=0; ii<=1; ii++)
							{
								sum1[ii]=0.0;
								sum2[ii]=0.0;
								for(i=b11; i<=n1; i++)
								{
									k2=b2-i;
									if(k2>=0 && k2<=n2)
										sum1[ii]=sum1[ii]+sa->b[n1][ii][i]*sa->f[n2][ii][k2];
									else if(k2>n2)
										sum1[ii]=sum1[ii]+sa->b[n1][ii][i];
								}

								for(i=b11; i<=n1; i++)
								{
									b32=0;
									if (b21-i > 0) b32=b21-i;
									for(j=b32; j<=n2; j++)
									{
										k3=b3-i-j;
										if(k3>=0 && k3<=n3)
											sum2[ii]=sum2[ii]+sa->b[n1][ii][i]*sa->b[n2][ii][j]*sa->f[n3][ii][k3];
										else if(k3>n3)
											sum2[ii]=sum2[ii]+sa->b[n1][ii][i]*sa->b[n2][ii][j];
									}
								}
								prob[ii]=1.0-sa->f[n1][ii][b1]-sum1[ii]-sum2[ii];
							}
							if(prob[0]>power[0]) continue;
							if(prob[1]<power[1]) continue;

							e1=(double)(n1+n2+n3)-(double)(n2+n3)*sa->f[n1][0][b1]
								-(double)n3*sum1[0];
							e2=(double)(n1+n2+n3)-(double)(n2+n3)*sa->f[n1][1][b1]
								-(double)n3*sum1[1];
							asn=(e1+e2)/2.0;

							#ifdef SUPER_DEBUG_PRINT
							printf("(%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,n3,b3,prob[0],prob[1]);
							#endif
							
							if(mail == 1)
							{
								email_results_three_stage_h0(n1,b1,n2,b2,n3,b3,prob[0],prob[1],e1,e2,asn,address);
							}
							else
							{
								print_results_three_stage_h0("Three Stage: Stop early only to conclude H0",n1,b1,n2,b2,n3,b3,prob[0],prob[1],e1,e2,asn);
							}

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

	current = time(NULL);
	elapse = current - start;
/*	printf("<br><br><b>Total Run time: %d seconds</b><br>\n", (int) elapse);*/
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


