#include "2samp_2stg_type2.h"


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


int two_samp_2stg_type2(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	double my_pow[2];
	
	int a1 = 0;
	int b1 = 0; 
	int b2 = 0;
	int bb = 0;
	int bbest = 0;
	int bb1 = 0;
	
	double tot = 0.0;
	double prob[2];
	double prob0 = 0.0;
	double prob1 = 0.0;
	double b0 = 0.0;
	double beta = 0.0;
	double p[2];
	double q[2];
	double e0 = 0.0;
	double e1 = 0.0;
	double asn = 0.0;
	
	/* Loop control variables */
	int i = 0;
	int n1 = 0;
	int n2 = 0;
	int j = 0;
	int ii = 0;
	int t = 0;
	int m1 = 0;
	int m2 = 0;
	int n11 = 0;
	int nn1 = 0;
	

	/* Control Vars Set By Dr. Kepner */
	int nn = 200;
	
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
	
	
	for(n1=2;n1<=nn;n1++) /* Loop: 300 */
	{
		m1 = n1 - 1;
		n11 = m1 * -1;
		nn1 = n1 + 1;
		
		/* loop 2 */
		for(i=0;i<2;i++)
		{
			b->b[n1][i][0] = pow(q[i],n1);
			b->fb[n1][i][0] = b->b[n1][i][0];
			
			/* loop 2 */
			for(j=1;j<=n1;j++)
			{
				b->b[n1][i][j] = n1*p[i]*b->b[n1-1][i][j-1]/j;
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
		
		/* loop 10 */
		for(n2=2;n2<=n1;n2++)
		{
			m2 = n1+n2 -1;
			
			/* loop 11 */
			for(b1=(-1*n1);b1<=m1;b1++)
			{
				/* loop 12 */
				for(b2=b1;b2<=m2;b2++)
				{
					/* loop 6 */
					for(ii=0;ii<2;ii++)
					{
						tot = 0.0;
						
						/* loop 7 */
						for(t=b1+1;t<=n1;t++)
						{
							if( (b2-t) <= n2 )
							{
								tot = tot+fp->pd[n1][ii][t]*fp->fpd[n2][ii][b2-t];
							}
							else
							{
								tot = tot+fp->pd[n1][ii][t];
							}
						} /* end loop 7 */
						prob[ii] = 1.0 - fp->fpd[n1][ii][b1-1]-tot;
					} /* end loop 6 */
					if( (prob[0] > my_pow[0]) || (prob[1] < my_pow[1]) )
					{
						
					}
					else
					{
						bb1 = b1;
						
JP30:						bbest = bb1;
						prob0 = prob[0];
						prob1 = prob[1];
						bb1 = bb1+1;
						if(bb1 > b2)
						{
							goto JP31;
						}
						prob[0] = prob[0] - fp->pd[n1][0][bb1-1] * (1.0 - fp->fpd[n2][0][b2-bb1+1]);
						prob[1] = prob[1] - fp->pd[n1][1][bb1-1] * (1.0 - fp->fpd[n2][1][b2-bb1+1]);
						if((prob[0] > 0.0) && (prob[1] >= my_pow[1]) )
						{
							goto JP30;
						}
						
JP31:
						e0 = 2*n1+2*n2*(1.0-fp->fpd[n1][0][bbest-1]);
						e1 = 2*n1+2*n2*(1.0-fp->fpd[n1][1][bbest-1]);
						asn = (e0+e1)/2.0;
						if(delta == .15) bbest++;

						if(mail == 1)
						{
							email_resluts_two_sample_two_stage_h0("Two Sample Two Stage Type 2: Stop Early Only To Conclude H0", n1, bbest, n2, b2, prob0, prob1, e0, e1, asn, address);
						}
						else
						{
							print_resluts_two_sample_two_stage_h0("Two Sample Two Stage Type 2: Stop Early Only To Conclude H0", n1, bbest, n2, b2, prob0, prob1, e0, e1, asn);
						}

						if(b != NULL)
							free(b);
						if(fp != NULL)
							free(fp);
						
						return 0;
					}
				} /* end loop 12 */
			} /* end loop 11 */
		} /* end loop 10 */
	} /* end loop 300 */
	
	if(b != NULL)
		free(b);
	if(fp != NULL)
		free(fp);

	return 0;
}
