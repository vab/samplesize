/* xstage3t3c.c - source file for function to calculate
 * sample size for three stage study conclude H0 or H1.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage3t3c.h"

struct solution_array
{
	double f[200][3][201];
	double b[200][3][201];
};


int three_stage_h0_h1(double alpha, double delta, double p0, 
			double powr, int mail, char *address)
{
	int a1 = 0,a2 = 0,a11 = 0,a21 = 0,b21 = 0,b31 = 0,bb1 = 0,bb2 = 0,b12 = 0,b22 = 0;
	int b1 = 0, b2 = 0, b3 = 0, b11 = 0;
	int i = 0, j = 0, ii = 0, n1 = 0, n2 = 0, n3 = 0, n11 = 0 ,n21 = 0, n31 = 0;
	int m1 = 0, m2 = 0, m3 = 0, k1 = 0, k2 = 0, maxn = 0;

	double p[3];
	double q[3];
	double sum = 0.0, sum2 = 0.0, sum3 = 0.0, asn = 0.0;
	double e[3];
	double power[3];
	double prob[3];
/*	double f[200][3][201];
	double b[200][3][201]; */
	int xx=0,yy=0,zz=0;

	struct solution_array *sa;

	time_t elapse, start, current, last_time;

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
			for(zz=0;zz<201;zz++)
			{
				sa->f[xx][yy][zz] = (double)0.0;
				sa->b[xx][yy][zz] = (double)0.0;
			}
		}
	}

	start = time(NULL);
	last_time = 0;

	p[1] = p0;
	power[1] = alpha;
	power[2] = powr;

	p[2] = p[1] + delta;

	maxn=nstage1(power[1], power[2], p[1], p[2]);

	#ifdef DEBUG
	printf("<br><b>maxn= %d</b>\n",maxn);
	#endif
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

	for(i=1; i<=2; i++) /* do 1 */
	{
		q[i]=1.0-p[i];
		sa->b[1][i][1]=q[i];
		sa->b[1][i][2]=p[i];
	} /* end do 1*/

	for(n1=2; n1<=maxn; n1++) /* do 9 */
	{
		/*    printf("n1=%d\n",n1); */
		n11=n1+1;
		m1=n1;

		current = time(NULL);
		elapse = current - start;
		if ( last_time != elapse )
		{
		/*	printf("\n<br>Calculating... Elapsed time:  %d seconds.<br>", (int) elapse );*/
			last_time = elapse;
		}
		fflush(0);

		for(i=1; i<=2; i++) /* do 3 */
		{
			sa->b[n1][i][1]=pow(q[i], (double)n1);
			sa->f[n1][i][1]=sa->b[n1][i][1];
			for(j=2; j<=n11; j++) /* do 2 */
			{
				sa->b[n1][i][j]=(double)n1*p[i]*sa->b[n1-1][i][j-1]/(double)(j-1);
				sa->f[n1][i][j]=sa->f[n1][i][j-1]+sa->b[n1][i][j];
			} /* end do 2 */
		} /* end do 3 */
		for(n2=2; n2<=n1; n2++) /* do 10 */
		{
			/*      printf("n1=%d n2=%d\n",n1,n2); */
			if((n1+n2) > maxn) break; /* go to 9 */
			n21=n2+1;
			m2=n1+n2;
			for(n3=2; n3<=n2; n3++) /* do 11 */
			{
			/*        printf("n1=%d n2=%d n3=%d\n",n1,n2,n3); */
				if((n1+n2+n3) > maxn) break; /* go to 10 */
				m3=n1+n2+n3;
				n31=n3+1;
				for(b1=0; b1<=m1; b1++) /* do 12 */
				{
					b11=b1+1;
					b12=b1;
					if(b1>m1) b12=m1;
					for(b2=b1; b2<=m2; b2++) /* do 13 */
					{
						b21=b2+1;
						b22=b2;
						if(b2>m2) b22=m2;
						for(b3=b2; b3<=m3; b3++) /* do 14 */
						{
							b31=b3+1;
							for(a1=b12; a1>=2; a1--) /* do 15 */
							{
								a11=a1+1;
								for(a2=b22; a2>=a1; a2--) /* do 16 */
								{
									a21=a2+1;
									for(ii=1; ii<=2; ii++) /* do 4 */
									{
										sum2=0.0;
										sum3=0.0;
										for(i=a11; i<=b11; i++) /* do 5 */
										{
											k1=a21-i;
											if(k1>n21)
											{
												sum2=sum2+sa->b[n1][ii][i];
											}
											else if((k1>0) && (k1<=n21))
											{
												sum2=sum2+sa->b[n1][ii][i]*sa->f[n2][ii][k1];
											}
											bb1=0; /* bb1 = 1 ? */
											if(a2-i+2 > 0)
											{
												bb1=a2-i+2;
											}
											bb2=n21;
											if(b21-i+1 < n21)
											{
												bb2=b21-i+1;
											}
											for(j=bb1; j<=bb2; j++) /* do 6 */
											{
												k2=b3-i-j+3;
												if(k2>n31)
												{
													sum3=sum3+sa->b[n1][ii][i]*sa->b[n2][ii][j];
												}
												else if((k2>0) && (k2<=n31))
												{
													sum3=sum3+sa->b[n1][ii][i]*sa->b[n2][ii][j]*sa->f[n3][ii][k2];
												}
											} /* end do 6 */
										} /* end do 5 */
										prob[ii]=1.0-sa->f[n1][ii][a1]-sum2-sum3;
									} /* end do 4 */
									if(prob[1]>power[1]) continue;
									if(prob[2]<power[2]) continue;
									
									/* end loops */
									for(ii=1; ii<=2; ii++) /* do 40 */
									{
										sum=0.0;
										for(i=a11; i<=b11; i++) /* do 41 */
										{
											sum=sum+sa->b[n1][ii][i]*(sa->f[n2][ii][b2-i+2]-sa->f[n2][ii][a21-i]);
										} /* end do 41 */
										e[ii]=n1+n2*(sa->f[n1][ii][b11]-sa->f[n1][ii][a11])+n3*sum;
									} /* end do 40 */
									asn=(e[1]+e[2])/2.0;
									#ifdef DEBUG_PRINT
									#ifdef SUPER_DEBUG_PRINT
									printf("(%d,%d,%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,a1,b1,n2,a2,b2,n3,b3,prob[1],prob[2]);
									#else
									printf("n1=%d a1=%d b1=%d n2=%d a2=%d b2=%d n3=%d b3=%d\n",
									n1,a1,b1,n2,a2,b2,n3,b3);
									printf("%f %f \n",prob[1],prob[2]);
									printf("e1=%f e2=%f asn=%f \n",e[1],e[2],asn);
									#endif
									#else
									if(mail == 1)
									{
										email_results_three_stage_h0_h1(n1,a1,b1,n2,a2,b2,n3,b3,prob[1],prob[2],e[1],e[2],asn,address);
									}
									else
									{
										print_results_three_stage_h0_h1(n1,a1,b1,n2,a2,b2,n3,b3,prob[1],prob[2],e[1],e[2],asn);
									}

									#endif
									current = time(NULL);
									elapse = current - start;

									if(sa != NULL)
									{
										free(sa);
									}
									
									return 0;
								} /* end do 16 */
							} /* end do 15 */
						} /* end do 14 */
					} /* end do 13 */
				} /* end do 12 */
			} /* end do 11 */
		} /* end do 10 */
	} /* end do 9 */

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

