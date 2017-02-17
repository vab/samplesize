/* display_results.c - source file for functions to
 * display results of sample size calculations.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@cancer.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */

#include "display_results.h"

/*  #define DEBUG_PRINT */
// #define SUPER_DEBUG_PRINT 
#define NORMAL 

int print_results_one_stage(char *study_type, int n, int ss, double size, double power)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d) %10.4f %10.4f\n",n,ss,size,power);
#endif
#ifdef DEBUG_PRINT

	printf("%s\n",study_type);
	printf("n=%d b1=%d\n",n,ss);
	printf("%10.8f %10.8f\n\n",size,power);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n</B></TH>\n");
	printf("<TH>b</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n);
	printf("<TD>%d</TD>\n",ss);
	printf("<TD>%10.8f</TD>\n",size);
	printf("<TD>%10.8f</TD>\n",power);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	printf("<LI>Conclude H1 if S >= %d\n",ss+1);
	printf("<LI>Conclude H0 if S <= %d</UL>\n",ss-1);
#endif

	return 0;
}


int print_results_two_stage_h1(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d\n",n1,b1,n2,b2);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Continue to stage two if S1 <= %d\n",b1);
	printf("<LI>Conclude H1 if S1 >= %d</UL>\n",b1+1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	printf("<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	printf("</UL>\n");
#endif

	return 0;
}


int print_results_two_stage_h0(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d\n",n1,b1,n2,b2);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Conclude H0 if S1 <= %d\n",b1);
	printf("<LI>Continue to stage two if S1 >= %d</UL>\n",b1+1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	printf("<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	printf("</UL>\n");
#endif

	return 0;
}

int print_results_two_stage_h0_h1(char *study_type,int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,a1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d a1=%d n2=%d b2=%d\n",n1,b1,a1,n2,b2);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>a1</TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",a1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Conclude H0 if S1 <= %d\n",a1-1);
	printf("<LI>Conclude H1 if S1 >= %d\n",b1+1);
	printf("<LI>Continue to stage two if %d <= S1 <= %d</UL>\n",a1,b1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	printf("<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	printf("</UL>\n");
#endif

	return 0;
}


int print_results_three_stage_h1(char *study_type,int n1,int b1,int n2,int b2,int n3,int b3,
                  double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,n3,b3,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d n3=%d b3=%d\n",n1,b1,n2,b2,n3,b3);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>n3</TH>\n");
	printf("<TH>b3</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%d</TD>\n",n3);
	printf("<TD>%d</TD>\n",b3);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Conclude H1 if S1 >= %d\n",b1+1);
	printf("<LI>Continue to Stage Two if S1 <= %d</UL>\n",b1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H1 if (S1+S2) >= %d\n",b2+1);
	printf("<LI>Continue to Stage Three if (S1+S2) <= %d</UL>\n",b2);
	printf("<B><UL><U>Stage Three</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2+S3) <= %d\n",b3);
	printf("<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n",b3+1);
	printf("</UL>\n");
#endif

	return 0;
}

int print_results_three_stage_h0(char *study_type,int n1, int b1, int n2, int b2, int n3, int b3,
	double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,n3,b3,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d n3=%d b3=%d\n",n1,b1,n2,b2,n3,b3);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><BR>\n",study_type);
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>n3</TH>\n");
	printf("<TH>b3</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%d</TD>\n",n3);
	printf("<TD>%d</TD>\n",b3);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Conclude H0 if S1 <= %d\n", b1);
	printf("<LI>Continue to Stage Two if S1 >= %d</UL>\n",b1+1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2) <= %d\n", b2);
	printf("<LI>Continue to Stage Three if (S1+S2) >= %d</UL>\n", b2+1);
	printf("<B><UL><U>Stage Three</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2+S3) <= %d\n", b3);
	printf("<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n", b3+1);
	printf("</UL>\n");
#endif

	return 0;
}

int print_results_three_stage_h0_h1(int n1, int a1, int b1, int n2, int a2, int b2, int n3, int b3,
	double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,a1,b1,n2,a2,b2,n3,b3,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("Three Stage H0 or H1\n");
	printf("n=%d a1=%d b1=%d n2=%d a2=%d b2=%d n3=%d b3=%d\n",n1,a1,b1,n2,a2,b2,n3,b3);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>Three Stage: Stop early only to conclude H1 or H0</H2><BR>\n");
	printf("<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	printf("<TR>\n");
	printf("<TH><B>n1</B></TH>\n");
	printf("<TH>a1</TH>\n");
	printf("<TH>b1</TH>\n");
	printf("<TH>n2</TH>\n");
	printf("<TH>a2</TH>\n");
	printf("<TH>b2</TH>\n");
	printf("<TH>n3</TH>\n");
	printf("<TH>b3</TH>\n");
	printf("<TH>Size</TH>\n");
	printf("<TH>Apower</TH>\n");
	printf("<TH>e1</TH>\n");
	printf("<TH>e2</TH>\n");
	printf("<TH>asn</TH>\n");
	printf("<TR ALIGN=center>\n");
	printf("<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	printf("<TD>%d</TD>\n",a1);
	printf("<TD>%d</TD>\n",b1);
	printf("<TD>%d</TD>\n",n2);
	printf("<TD>%d</TD>\n",a2);
	printf("<TD>%d</TD>\n",b2);
	printf("<TD>%d</TD>\n",n3);
	printf("<TD>%d</TD>\n",b3);
	printf("<TD>%10.8f</TD>\n",prob1);
	printf("<TD>%10.8f</TD>\n",prob2);
	printf("<TD>%10.8f</TD>\n",e1);
	printf("<TD>%10.8f</TD>\n",e2);
	printf("<TD>%10.8f</TD>\n",asn);
	printf("</TABLE>\n");
	printf("<BR><BR><BR><BR>\n");
	printf("<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<UL><U>Stage One</U></B>\n");
	printf("<LI>Conclude H0 if S1 <= %d\n", a1-1);
	printf("<LI>Conclude H1 if S1 >= %d\n", b1+1);
	printf("<LI>Continue to Stage Two if %d <= S1 <= %d</UL>\n", a1, b1);
	printf("<B><UL><U>Stage Two</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2) <= %d\n", a2-1);
	printf("<LI>Conclude H1 if (S1+S2) >= %d\n", b2+1);
	printf("<LI>Continue to Stage Three if %d <= (S1+S2) <= %d</UL>\n", a2, b2);
	printf("<B><UL><U>Stage Three</U></B>\n");
	printf("<LI>Conclude H0 if (S1+S2+S3) <= %d\n", b3);
	printf("<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n", b3+1);
	printf("</UL>\n");
#endif

	return 0;
}


int print_results_two_sample_one_stage(char *study_type, int n, int ss, int jj, double size, double power)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d) %10.4f %10.4f\n",n,ss,size,power);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d\n",n,ss);
	printf("%10.8f %10.8f\n\n",size,power);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<p>n = %d to each treatment.  Conclude H1 if S-T&gt;= %d\n",n,jj);
	printf("<p>alpha = %10.8f   power = %10.8f\n",size, power);
	printf("</ul>\n");
#endif
	return 0;
}


int print_results_two_sample_two_stage_h1(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d\n",n1,b1,n2,b2);
	printf("alpha = %10.8f power = %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<P>n = %d, to each treatment.  Conclude H1 if S1-T1 &gt; %d\n",n1,b1);
	printf("<P>Otherwise, accrue n2 = %d additional subjects to each treatment.",n2);
	printf("<P>Conclude H1 if (S1-T1) &lt;= %d and ST-T1+S2-T2 &gt; %d\n", b1,b2);
	printf("<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	printf("</ul>\n");
#endif
	return 0;
}


int print_resluts_two_sample_two_stage_h0(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d) %10.4f %10.4f\n",n1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("%s\n",study_type);
	printf("n=%d b1=%d n2=%d b2=%d n3=%d b3=%d\n",n1,b1,n2,b2,n3,b3);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	/* TODO:  This might be bbest instead of b1 below. */
	printf("<p>n1 = %d, to each treatment. Conclude H0 if S1-T1 &lt;= %d\n",n1, b1);
	printf("<p>Otherwise, accrue n2 = %d additional subjects to each treatment.\n", n2); 
	printf("<p>Conclude H1 if (S1-T1) &gt; %d and ST-T1+S2-T2 &gt; %d\n",b1,b2);
	printf("<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	printf("</ul>\n");
#endif

	return 0;
}


int print_results_two_sample_two_stage_h0_h1(char *study_type,int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn)
{
#ifdef SUPER_DEBUG_PRINT
	printf("(%d,%d,%d,%d,%d) %10.4f %10.4f\n",n1,a1,b1,n2,b2,prob1,prob2);
#endif
#ifdef DEBUG_PRINT
	printf("Three Stage H0 or H1\n");
	printf("n=%d a1=%d b1=%d n2=%d a2=%d b2=%d n3=%d b3=%d\n",n1,a1,b1,n2,a2,b2,n3,b3);
	printf("%10.8f %10.8f\n",prob1,prob2);
	printf("e1 = %10.8f e2 = %10.8f asn = %10.8f\n", e1, e2, asn);
#endif
#ifdef NORMAL
	printf("<H2 ALIGN=left>%s</H2><br>\n",study_type);
	printf("<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	printf("<p>Accrue n1 = %d to each treatment\n", n1);
	printf("<p>Conclude H0 if S1-T1 &lt; %d. Conclude H1 if S1-T1 &gt; %d\n", a1, b1);
	printf("<p>Otherwise, accrue n2 = %d additional patients to each treatment.\n",n2);
	printf("<br>\n");
	printf("<p>Conclude H1 only if %d &lt;= S1-T1 &gt;= %d\n", a1,b1);
	printf("<p>and S1-T1+S2-T2 &gt; %d.\n",b2);
	printf("<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	printf("</ul>\n");
#endif

	return 0;
}
