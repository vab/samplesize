/* sample_size.h - Main program header file.
 * Copyright (C) 2002-2005 James L. Kepner, Ph.D.
 * james.kepner@cancer.org
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
#include <strings.h>
#include <string.h>
#include <stddef.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "cgi.h"

#include "xstage1.h"
#include "xstage2t1c.h"
#include "xstage2t2c.h"
#include "xstage2t3c.h"
#include "xstage3t1c.h"
#include "xstage3t2c.h"
#include "xstage3t3c.h"
#include "nstage1.h"

#include "2samp_1stg.h"
#include "2samp_2stg_type1.h"
#include "2samp_2stg_type2.h"
#include "2samp_2stg_type3.h"


static void setlimit(void);
