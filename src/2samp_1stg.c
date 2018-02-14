#include "2samp_1stg.h"


struct solution_array_type_1
{
	double b[201][2][402];
	double fb[201][2][201];
};

struct solution_array_type_2
{
	double pd[201][2][402];
	double fpd[201][2][402];
};

int two_samp_1stg(double alpha, double delta, double p0, double powr, int mail, char *address)
{
	double my_pow[2];

	double p[2];
	double q[2];

	double tot = 0.0;
	double b0 = 0.0;
	double power = 0.0;
	double beta = 0.0;
	double size = 0.0;

	/* Loop control variables */
	int i = 0;
	int n1 = 0;
	int j = 0;
	int ii = 0;
	int t = 0;
	int m1 = 0;
	int jj = 0;

	/* Other Vars */
	/*
	int nn1 = 0;
	int nn2 = 0;
	int n11 = 0;
	*/

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

	fp = (struct solution_array_type_2 *)malloc(sizeof(struct solution_array_type_2));
	if(fp == NULL)
	{
		fprintf(stderr,"Memory allocation failed.\n");

		return -1;
	}

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
//		n11 = n11 - m1;
/*		n11 = (m1 * -1);
		nn1 = n1 + 1;
		nn2 = 2 * n1 + 1;
*/

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

		/* loop 10 */
		for(j=0;j<=m1;j++)
		{
			if( (fp->fpd[n1][0][j] >= b0) && (fp->fpd[n1][1][j]<=beta) )
			{
				size = 1.0 - fp->fpd[n1][0][j];
				power = 1.0 - fp->fpd[n1][1][j];
				jj=j+1;
				if(mail == 1)
				{
					email_results_two_sample_one_stage("Two Sample One Stage", n1, j, jj, size, power,address);
				}
				else
				{
					print_results_two_sample_one_stage("Two Sample One Stage", n1, j, jj, size, power);
				}

				if(b != NULL)
					free(b);
				if(fp != NULL)
					free(fp);

				return 0;
			}
			else
			{
				continue;
			}
		} /* end loop 10 */
	} /* end loop 300 */

	printf("Exiting...  n1 is too large, n1 = %d\n", n1);

	if(b != NULL)
		free(b);
	if(fp != NULL)
		free(fp);

	return 0;
}
