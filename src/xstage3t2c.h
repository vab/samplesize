/* xstage2t2c.h - header file for program to calculation
 * three stage conclude h0 sample sizes.
 * Copyright (C) 2002-2003 James L. Kepner, Ph.D.
 * james.kepner@roswellpark.org
 *
 * This file is part of the Sample Size Calculator.
 *
 * This file is copyright James L. Kepner, Ph.D.
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "nstage1.h"
#include "display_results.h"
#include "email_results.h"


int three_stage_h0(double, double, double, double, int, char *);
