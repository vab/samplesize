/* email_results.c - Source file for functions to email
 * results of sample size calculations.
 * Copyright (C) 2002-2005 James L. Kepner, Ph.D.
 * james.kepner@cancer.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */
#include "email_results.h"


/* one Stage Results */
int email_results_one_stage(char *study_type, int n, int ss, double size, double power, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

		/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");


	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n</B></TH>\n");
	fprintf(sendmail,"<TH>b</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n);
	fprintf(sendmail,"<TD>%d</TD>\n",ss);
	fprintf(sendmail,"<TD>%f</TD>\n",size);
	fprintf(sendmail,"<TD>%f</TD>\n",power);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	fprintf(sendmail,"<LI>Conclude H1 if S >= %d\n",ss+1);
	fprintf(sendmail,"<LI>Conclude H0 if S <= %d</UL>\n",ss-1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}

/* Two Stage Results */
int email_results_two_stage_h1(char *study_type,int n1,int b1,int n2,int b2,double prob1,double prob2,double e1,double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");
	

	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Continue to stage two if S1 <= %d\n",b1);
	fprintf(sendmail,"<LI>Conclude H1 if S1 >= %d</UL>\n",b1+1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);


	return 0;
}

int email_results_two_stage_h0(char *study_type,int n1,int b1,int n2,int b2,double prob1,double prob2,double e1,double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");

	
	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if S1 <= %d\n",b1);
	fprintf(sendmail,"<LI>Continue to stage two if S1 >= %d</UL>\n",b1+1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}

int email_results_two_stage_h0_h1(char *study_type, int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");


	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>a1</TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",a1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rule: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if S1 <= %d\n",a1-1);
	fprintf(sendmail,"<LI>Conclude H1 if S1 >= %d\n",b1+1);
	fprintf(sendmail,"<LI>Continue to stage two if %d <= S1 <= %d</UL>\n",a1,b1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2) <= %d\n",b2);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2) >= %d</UL>\n",b2+1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}

/* Three Stage Results */
int email_results_three_stage_h0(int n1, int b1, int n2, int b2, int n3, int b3,
	double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");


	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>Three Stage: Stop early only to conclude H0</H2><BR>\n");
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>n3</TH>\n");
	fprintf(sendmail,"<TH>b3</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%d</TD>\n",n3);
	fprintf(sendmail,"<TD>%d</TD>\n",b3);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if S1 <= %d\n", b1);
	fprintf(sendmail,"<LI>Continue to Stage Two if S1 >= %d</UL>\n",b1+1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2) <= %d\n", b2);
	fprintf(sendmail,"<LI>Continue to Stage Three if (S1+S2) >= %d</UL>\n", b2+1);
	fprintf(sendmail,"<B><UL><U>Stage Three</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2+S3) <= %d\n", b3);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n", b3+1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}

int email_results_three_stage_h1(char *study_type, int n1,int b1,int n2,int b2,int n3,int b3,
                  double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");


	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>n3</TH>\n");
	fprintf(sendmail,"<TH>b3</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%d</TD>\n",n3);
	fprintf(sendmail,"<TD>%d</TD>\n",b3);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H1 if S1 >= %d\n",b1+1);
	fprintf(sendmail,"<LI>Continue to Stage Two if S1 <= %d</UL>\n",b1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2) >= %d\n",b2+1);
	fprintf(sendmail,"<LI>Continue to Stage Three if (S1+S2) <= %d</UL>\n",b2);
	fprintf(sendmail,"<B><UL><U>Stage Three</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2+S3) <= %d\n",b3);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n",b3+1);
	fprintf(sendmail,"</UL>\n");
	
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}

int email_results_three_stage_h0_h1(int n1, int a1, int b1, int n2, int a2, int b2, int n3, int b3,
	double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");


	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<TABLE BORDER=0 CELLSPACING=0 CELLPADDING=0 width=\"600\">\n");
	fprintf(sendmail,"<TR VALIGN=top>\n");
/*	fprintf(sendmail,"<TD ROWSPAN=2><IMG SRC=\"images/rpci.png\"></TD>\n"); */
	fprintf(sendmail,"<TD ROWSPAN=2></TD>\n");
	fprintf(sendmail,"<TD><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-1\">\n");
	fprintf(sendmail,"</FONT></FONT></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD><B><FONT FACE=\"Arial,Helvetica\">American Cancer Society</FONT></B>\n");
	fprintf(sendmail,"<BR><FONT FACE=\"Arial, Helvetica\"><FONT SIZE=\"-2\">Please feel free to forward\n");
	fprintf(sendmail,"your comments, suggestions, and corrections to\n");
	fprintf(sendmail,"<B><A HREF=\"mailto:James.Kepner@cancer.org\">Dr. James L. Kepner</B></FONT></A></TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TD COLSPAN=2>\n");
	fprintf(sendmail,"</TD>\n");
	fprintf(sendmail,"</TR>\n");
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");

	fprintf(sendmail,"<H2 ALIGN=left>Three Stage: Stop early only to conclude H1 or H0</H2><BR>\n");
	fprintf(sendmail,"<TABLE BORDER=1 ALIGN=left WIDTH=600 CELLBORDER=1 CELLSPACING=1>\n");
	fprintf(sendmail,"<TR>\n");
	fprintf(sendmail,"<TH><B>n1</B></TH>\n");
	fprintf(sendmail,"<TH>a1</TH>\n");
	fprintf(sendmail,"<TH>b1</TH>\n");
	fprintf(sendmail,"<TH>n2</TH>\n");
	fprintf(sendmail,"<TH>a2</TH>\n");
	fprintf(sendmail,"<TH>b2</TH>\n");
	fprintf(sendmail,"<TH>n3</TH>\n");
	fprintf(sendmail,"<TH>b3</TH>\n");
	fprintf(sendmail,"<TH>Size</TH>\n");
	fprintf(sendmail,"<TH>Apower</TH>\n");
	fprintf(sendmail,"<TH>e1</TH>\n");
	fprintf(sendmail,"<TH>e2</TH>\n");
	fprintf(sendmail,"<TH>asn</TH>\n");
	fprintf(sendmail,"<TR ALIGN=center>\n");
	fprintf(sendmail,"<TD><STRONG><FONT COLOR=green>%d</FONT></STRONG></TD>\n",n1);
	fprintf(sendmail,"<TD>%d</TD>\n",a1);
	fprintf(sendmail,"<TD>%d</TD>\n",b1);
	fprintf(sendmail,"<TD>%d</TD>\n",n2);
	fprintf(sendmail,"<TD>%d</TD>\n",a2);
	fprintf(sendmail,"<TD>%d</TD>\n",b2);
	fprintf(sendmail,"<TD>%d</TD>\n",n3);
	fprintf(sendmail,"<TD>%d</TD>\n",b3);
	fprintf(sendmail,"<TD>%f</TD>\n",prob1);
	fprintf(sendmail,"<TD>%f</TD>\n",prob2);
	fprintf(sendmail,"<TD>%f</TD>\n",e1);
	fprintf(sendmail,"<TD>%f</TD>\n",e2);
	fprintf(sendmail,"<TD>%f</TD>\n",asn);
	fprintf(sendmail,"</TABLE>\n");
	fprintf(sendmail,"<BR><BR><BR><BR>\n");
	fprintf(sendmail,"<P><B>&nbsp &nbsp &nbsp <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<UL><U>Stage One</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if S1 <= %d\n", a1-1);
	fprintf(sendmail,"<LI>Conclude H1 if S1 >= %d\n", b1+1);
	fprintf(sendmail,"<LI>Continue to Stage Two if %d <= S1 <= %d</UL>\n", a1, b1);
	fprintf(sendmail,"<B><UL><U>Stage Two</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2) <= %d\n", a2-1);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2) >= %d\n", b2+1);
	fprintf(sendmail,"<LI>Continue to Stage Three if %d <= (S1+S2) <= %d</UL>\n", a2, b2);
	fprintf(sendmail,"<B><UL><U>Stage Three</U></B>\n");
	fprintf(sendmail,"<LI>Conclude H0 if (S1+S2+S3) <= %d\n", b3);
	fprintf(sendmail,"<LI>Conclude H1 if (S1+S2+S3) >= %d</UL>\n", b3+1);
	fprintf(sendmail,"</UL>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"<BR>Implemented in C by <A HREF=\"http://cryptnet.net/people/vab/\">V. Alex Brennen</A> [<A HREF=\"mailto:codepoet@dublin.ie\">codepoet@dublin.ie</A>]</H6></CENTER>\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}


int email_results_two_sample_one_stage(char *study_type, int n, int ss, int jj, double size, double power, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");

	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<p>n = %d to each treatment.  Conclude H1 if S-T&gt;= %d\n",n,jj);
	fprintf(sendmail,"<p>alpha = %10.8f   power = %10.8f\n",size, power);
	fprintf(sendmail,"</ul>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}


int email_results_two_sample_two_stage_h1(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");

	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<p>n = %d, to each treatment.  Conclude H1 if S1-T1 &gt; %d\n",n1,b1);
	fprintf(sendmail,"<p>Otherwise, accrue n2 = %d additional subjects to each treatment.",n2);
	fprintf(sendmail,"<p>Conclude H1 if (S1-T1) &lt;= %d and ST-T1+S2-T2 &gt; %d\n", b1,b2);
	fprintf(sendmail,"<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	fprintf(sendmail,"</ul>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}


int email_resluts_two_sample_two_stage_h0(char *study_type, int n1, int b1, int n2, int b2,
                  double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");

	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	/* TODO:  This might be bbest instead of b1 below. */
	fprintf(sendmail,"<p>n1 = %d, to each treatment. Conclude H0 if S1-T1 &lt;= %d\n",n1, b1);
	fprintf(sendmail,"<p>Otherwise, accrue n2 = %d additional subjects to each treatment.\n", n2); 
	fprintf(sendmail,"<p>Conclude H1 if (S1-T1) &gt; %d and ST-T1+S2-T2 &gt; %d\n",b1,b2);
	fprintf(sendmail,"<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	fprintf(sendmail,"</ul>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);

	return 0;
}


int email_results_two_sample_two_stage_h0_h1(char *study_type,int n1,int a1,int b1,int n2,int b2,
    double prob1, double prob2, double e1, double e2, double asn, char *address)
{
	FILE	*sendmail;

	/* open up a pipe to sendmail */
	sendmail = popen("/usr/sbin/sendmail -t", "w");
	if(sendmail == NULL)
	{
		fprintf(stderr,"Couldn't Open Sendmail\n");

		return -1;
	}

	/* Send the actual email */
	fprintf(sendmail,"From: James.Kepner@cancer.org\n");
	fprintf(sendmail,"To: %s\n",address);
	fprintf(sendmail,"Subject: Kepner Sample Size Results\n");
	fprintf(sendmail,"MIME-Version: 1.0\n");
	fprintf(sendmail,"Content-type: text/html\n");
	fprintf(sendmail,"\n");

	fprintf(sendmail,"<HTML><HEAD><TITLE>Kepner Sample Size Calculator</TITLE></HEAD>\n");
	fprintf(sendmail,"<BODY BGCOLOR=#FFFFFF\n");
	fprintf(sendmail,"<H2 ALIGN=left>%s</H2><br>\n",study_type);
	fprintf(sendmail,"<P><B>&nbsp; &nbsp; &nbsp; <FONT COLOR=green>Decision Rules: </FONT></B><UL>\n");
	fprintf(sendmail,"<p>Accrue n1 = %d to each treatment\n", n1);
	fprintf(sendmail,"<p>Conclude H0 if S1-T1 &lt; %d. Conclude H1 if S1-T1 &gt; %d\n", a1, b1);
	fprintf(sendmail,"<p>Otherwise, accrue n2 = %d additional patients to each treatment.\n",n2);
	fprintf(sendmail,"<br>\n");
	fprintf(sendmail,"<p>Conclude H1 only if %d &lt;= S1-T1 &gt;= %d\n", a1,b1);
	fprintf(sendmail,"<p>and S1-T1+S2-T2 &gt; %d.\n",b2);
	fprintf(sendmail,"<p>alpha = %10.8f power = %10.8f e1 = %10.8f e2 = %10.8f asn = %10.8f\n", prob1, prob2, e1, e2, asn);
	fprintf(sendmail,"</ul>\n");

	fprintf(sendmail,"<HR SIZE=0 WIDTH=100%%>\n");
	fprintf(sendmail,"<CENTER><H6>Kepner Sample Size Calculator\n");
	fprintf(sendmail,"</BODY></HTML>\n");

	pclose(sendmail);


	return 0;
}
