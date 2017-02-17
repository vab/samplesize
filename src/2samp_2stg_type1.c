#include "2samp_2stg_type1.h"


struct solution_array_type_1
{
	double b[201][2][201];
	double fb[201][2][201];
};

struct solution_array_type_2
{
	double pd[202][2][402];
	double fpd[202][2][402];
};


int two_samp_2stg_type1(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	double my_pow[2];
	double prob[2];
	double e1 = 0.0;
	double e2 = 0.0;
	double asn = 0.0;
	
	double p[2];
	double q[2];
	
	double tot = 0.0;
	double b0 = 0.0;
	double beta = 0.0;
	
	/* Loop control variables */
	int i = 0;
	int n1 = 0;
	int n2 = 0;
	int j = 0;
	int ii = 0;
	int t = 0;
	int m1 = 0;
	int m2 = 0;
	
	/* Other Vars */
	int nn1 = 0;
	int nn2 = 0;
	int n11 = 0;
	int b1 = 0;
	int b2 = 0;
	
	/* Control Vars Set By Dr. Kepner */
	int nn = 200;
	
	int x = 0;
	
	/* arrays (distribs) */
	struct solution_array_type_1 *b = NULL;
	struct solution_array_type_2 *fp = NULL;
	
	b = (struct solution_array_type_1 *)malloc(sizeof(struct solution_array_type_1));
	if(b == NULL)
	{
		fprintf(stderr,"Memory allocation failed.\n");
		
		return -1;
	}
	memset(b,0x00,sizeof(struct solution_array_type_1));
	
	fp = (struct solution_array_type_2 *)malloc(sizeof(struct solution_array_type_2));
	if(fp == NULL)
	{
		fprintf(stderr,"Memory allocation failed.\n");
		
		return -1;
	}
	memset(fp,0x00,sizeof(struct solution_array_type_2));
	
	/* Init variables */
	my_pow[0] = alpha;
	my_pow[1] = powr;
	b0 = 1.0 - my_pow[0];
	beta = 1.0 - my_pow[1];
	p[0] = p0;
	p[1] = p[0] + delta;
	
	q[0] = 1 - p[0];
	q[1] = 1 - p[1];
	b->b[1][0][0] = q[0];
	b->b[1][1][0] = q[1];
	b->b[1][0][1] = p[0];
	b->b[1][1][1] = p[1];

	/* Start the program */
	for(n1=2;n1<=nn;n1++) /* Loop: 300 */
	{
		m1 = n1 - 1;
		n11 = m1 * -1;
		nn1 = n1 + 1;
		nn2 = 2 * n1 + 1;
		
		/* loop 2 */
		for(i=0;i<2;i++)
		{
			b->b[n1][i][0] = pow(q[i],n1);
			b->fb[n1][i][0] = b->b[n1][i][0];
			
			/* loop 2 */
			for(j=1;j<=n1;j++)
			{
				b->b[n1][i][j]=n1*p[i]*b->b[n1-1][i][j-1]/j;
				b->fb[n1][i][j] = b->fb[n1][i][j-i]+b->b[n1][i][j];
				
				/* loop 3 */
				for(ii=(n1*-1);ii<=n1;ii++)
				{
					tot=0.0;
					/* loop 4 */
					for(t=0;t<=n1;t++)
					{
						if( ((t+ii)<0) || ((t+ii)>n1) ) 
						{
						//	printf("Broken: n1 = %d, T = %d\n",n1,t);
						}
						else
						{
							tot=tot+b->b[n1][0][t]*b->b[n1][i][ii+t];
						}
					} /* end loop 4 */
					
					fp->pd[n1][i][ii] = tot;
					fp->fpd[n1][i][ii] = fp->fpd[n1][i][ii-1] + fp->pd[n1][i][ii];
				} /* end loop 3 */
			}/* end loop 2 */
		}/* end loop 2*/
	
/** Above is the same as 2samp_1stg **/
		/* loop 10 */
		for(n2=2;n2<=n1;n2++)
		{
			m2 = n1+n2-1;
			
			/* loop 12 */
			for(b1=0;b1<=m1;b1++)
			{
				/* loop 13 */
				for(b2=b1;b2<=m2;b2++)
				{
					/* loop 6 */
					for(ii=0;ii<2;ii++)
					{
						tot = 0.0;
						
						/* loop 7 */
						x = n1 * -1;
						for(t=x;t<=b1;t++)
						{
							if( (b2-t) > n2)
							{
								tot = tot + fp->pd[n1][ii][t];
							}
							else
							{
								tot = tot + fp->pd[n1][ii][t]*fp->fpd[n2][ii][b2-t];
							}
						} /* end loop 7 */
						prob[ii] = 1.0 - tot;
					} /* end loop 6 */
					if( (prob[0] < (my_pow[0] + 0.00001) ) && (prob[1] > my_pow[1]) )
					{
						e1=2*n1+2*n2*fp->fpd[n1][0][b1]; /* e1=E[NM/p(0)] */
						e2=2*n1+2*n2*fp->fpd[n1][1][b1]; /* e2=E[NM|p(1)] */
						asn = (e1+e2)/2.0; /* asn = average sample size */
						
						/** print out results.  We're good. **/
						if(mail == 1)
						{
							email_results_two_sample_two_stage_h1("Two Sample Two Stage Type 1: Stop Early Only To Conclude H1", n1, b1, n2, b2,prob[0], prob[1], e1, e2, asn,address);
						}
						else
						{
							print_results_two_sample_two_stage_h1("Two Sample Two Stage Type 1: Stop Early Only To Conclude H1", n1, b1, n2, b2,prob[0], prob[1], e1, e2, asn);
						}

						if(b != NULL)
							free(b);
						if(fp != NULL)
							free(fp);
						
						return 0;
					}
				} /* end loop 13 */
			} /* end loop 12 */
		} /* end loop 10 */
	} /* end loop 300 */
	
	printf("Exiting...  n1 is too large, n1 = %d\n", n1);

	if(b != NULL)
		free(b);
	if(fp != NULL)
		free(fp);

	return 0;
}
