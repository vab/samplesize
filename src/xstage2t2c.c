/* xstage2t2c.c - source file for function to calculate
 * sample size for two stage study conclude H0.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "xstage2t2c.h"


struct solution_array
{
	double f[201][2][201];
	double b[201][2][201];
};


int two_stage_h0(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	int b1 = 0;
	int b2 = 0;
	int b11 = 0;
	int bb1 = 0;
	int bbest = 0;
	int maxn = 0;
	double p[2];
	double q[2];
	double power[2];
	double prob[2];

	struct solution_array *sa;

	int xx=0,yy=0,zz=0;

	int n1 = 0;
	int i = 0;
	int j = 0;
	int m1 = 0;
	int n2 = 0;
	int m2 = 0;
	int ii = 0;
	double sum = 0.0;
	double prob0 = 0.0;
	double prob1 = 0.0;
	double e1 = 0.0;
	double e2 = 0.0;
	double asn = 0.0;
	
	sa = (struct solution_array *)malloc(sizeof(struct solution_array));
	if(sa == NULL)
	{
		fprintf(stderr,"Malloc Memory Allocation Call Failed.\n");

		return -1;
	}
	for(xx=0;xx<201;xx++)
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

	power[0] = alpha;
	power[1] = powr;
	p[0] = p0;
	p[1] = p[0] + delta;

	maxn = nstage1(power[0],power[1],p[0],p[1]);
	if(maxn == 0)
	{
		printf("No Solution\n");
		if(sa != NULL)
		{
			free(sa);
		}
		
		return 0;
	}
	else if(maxn > 200)
	{
		printf("ERROR - maxn is greater than 200\n");
		printf("The C program must be redimensioned\n");
		if(sa != NULL)
		{
			free(sa);
		}

		
		return 0;
	}	

	q[0] = 1-p[0];
	q[1] = 1-p[1];
	sa->b[1][0][0] = q[0];
	sa->b[1][1][0] = q[1];
	sa->b[1][0][1] = p[0];
	sa->b[1][1][1] = p[1];
	for(n1=2;n1<=maxn;n1++) /* do 15 */
	{
	/*	printf("do 15\n"); */
		for(i=0;i<=1;i++) /* do 3 */
		{
	/*		printf("do 3\n"); */
			sa->b[n1][i][0] = pow(q[i],n1);
			sa->f[n1][i][0] = sa->b[n1][i][0];
			for(j=1;j<=n1;j++) /* do 2 */
			{
	/*			printf("do 2\n");*/
				sa->b[n1][i][j] = n1*p[i]*sa->b[n1-1][i][j-1]/j;
				sa->f[n1][i][j] = sa->f[n1][i][j-1]+sa->b[n1][i][j];
			} /* end do 2 */
		} /* end do 3 */
		m1 = n1 - 1;
		
		for(n2=2;n2<=n1;n2++) /* do 10 */
		{
	/*		printf("do 10\n");*/
			if(n1+n2 > maxn)
			{
				/* stop and return to previous loop */
				break;
			}
			m2 = n1+n2-1;
			for(b1=m1;b1!=-1;b1--) /* do 11 */   /* HERE IS THE FIX */
			{
	/*			printf("do 11\n"); */
				b11 = b1+1;
				for(b2=b1;b2<=m2;b2++) /* do 12 */
				{
				/*	printf("do 12\n");*/
					for(ii=0;ii<=1;ii++) /* do 4 */
					{
				/*		printf("do 4\n"); */
						sum=0.0;
						for(i=b11;i<=n1;i++) /* do 5 */
						{
						/*	printf("do 5\n");*/
							if( (b2-i+1>=1) && (b2-i+1<=n2) )
							{
								sum=sum+sa->b[n1][ii][i]*(1-sa->f[n2][ii][b2-i]);
							}
							else if( (b2-i+1<=0) && (b2-i+1<=n2) )
							{
								sum=sum+sa->b[n1][ii][i];
							}
						} /* end do 5 */
				/*		printf("%10.8f %10.8f\n",prob[ii],sum); */
						prob[ii] = sum;
					} /* end do 4 */
					if(prob[0] > power[0])
					{
						/* go to 12 */
						continue;
					}
					if(prob[1] < power[1])
					{
						/* go to 12 */
						continue;
					}
					/* The following statement controls P(conclude H0|H0) at stage1 */
					bb1=b1;
					for(;;) /* 30 */
					{
						bbest=bb1;
						prob0=prob[0];
						prob1=prob[1];
						e1=n1+n2*(1-sa->f[n1][0][bbest]);
						e2=n1+n2*(1-sa->f[n1][1][bbest]);
						asn=(e1+e2)/2;
						bb1=bb1+1;
						if(bb1>b2)
						{
							#ifdef SUPER_DEBUG_PRINT
							printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,bbest,n2,b2,prob0,prob1);
							#endif
							#ifdef DEBUG_PRINT
							printf("n1=%d bbest=%d n2=%d b2=%d\n",n1,bbest,n2,b2);
							printf("%10.8f %10.8f\n",prob0,prob1);
                        				printf("e1=%10.8f e2=%10.8f asn=%10.8f\n",e1,e2,asn);
							#endif
							if(mail == 1)
							{
								email_results_two_stage_h0("Two-Stage:  Stop early only to conclude H0",n1,bbest,n2,b2,prob0,prob1,e1,e2,asn,address);
							}
							else
							{
								print_results_two_stage_h0("Two-Stage:  Stop early only to conclude H0",n1,bbest,n2,b2,prob0,prob1,e1,e2,asn);
							}
							if(sa != NULL)
							{
								free(sa);
							}

							return 0;	
						}
						if((b2-bb1) == 0)
						{
							prob[0]=prob[0]-sa->b[n1][0][bb1+1];
							prob[1]=prob[1]-sa->b[n1][1][bb1+1];
						}
						else if((b2-bb1) > 0)
						{
							prob[0]=prob[0]-sa->b[n1][0][bb1+1]*(1-sa->f[n2][0][b2-bb1-1]);
							prob[1]=prob[1]-sa->b[n1][1][bb1+1]*(1-sa->f[n2][1][b2-bb1-1]);
						} 
						if( (prob[1]<power[1]) || (prob[0]< 0.0) )
						{
							#ifdef SUPER_DEBUG_PRINT
							printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,bbest,n2,b2,prob0,prob1);
							#endif
							#ifdef DEBUG_PRINT
							printf("n1=%d bbest=%d n2=%d b2=%d\n",n1,bbest,n2,b2);
							printf("%10.8f %10.8f\n",prob0,prob1);
							printf("e1=%10.8f e2=%10.8f asn=%10.8f\n",e1,e2,asn);
							#endif
							if(mail == 1)
							{
								email_results_two_stage_h0("Two-Stage:  Stop early only to conclude H0",n1,bbest,n2,b2,prob0,prob1,e1,e2,asn,address);
							}
							else
							{
								print_results_two_stage_h0("Two-Stage:  Stop early only to conclude H0",n1,bbest,n2,b2,prob0,prob1,e1,e2,asn);
							}

							if(sa != NULL)
							{
								free(sa);
							}
							return 0;
						}
					} /* end 30 */
					/* go to 30 */
				} /* end 12 */
			} /* end 11 */
		} /* do 10 */
	} /* end do 15 */
	
	n1=n1-1;
	printf("%d\n",n1);
	printf("An ERROR has occurred\n");
	printf("n1 cannot exceed the 1 stage sample size\n");

	if(sa != NULL)
	{
		free(sa);
	}

		
	
	return 0;
}
