/*
 * Copyright (c) 2000 Silicon Graphics, Inc.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Further, this software is distributed without any warranty that it is
 * free of the rightful claim of any third person regarding infringement
 * or the like.  Any license provided herein, whether implied or
 * otherwise, applies only to this software file.  Patent licenses, if
 * any, provided herein do not apply to combinations of this program with
 * other software, or any other product whatsoever.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Contact information: Silicon Graphics, Inc., 1600 Amphitheatre Pkwy,
 * Mountain View, CA  94043, or:
 *
 * http://www.sgi.com
 *
 * For further information regarding this notice, see:
 *
 * http://oss.sgi.com/projects/GenInfo/NoticeExplan/
 */

/*
 * AUTHOR	: William Roske
 * CO-PILOT	: Dave Fenner
 * DATE STARTED	: 03/30/92
 *
 *  Calls chmod(2) with different modes and expects success.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "test.h"
#include "safe_macros.h"

static int modes[] = { 0, 07, 070, 0700, 0777, 02777, 04777, 06777 };

char *TCID = "chmod02";
int TST_TOTAL = ARRAY_SIZE(modes);

#define FNAME "test_file"

static void setup(void);
static void cleanup(void);

int main(int ac, char **av)
{
	int lc, i;

	tst_parse_opts(ac, av, NULL, NULL);

	setup();

	for (lc = 0; TEST_LOOPING(lc); lc++) {

		tst_count = 0;

		for (i = 0; i < TST_TOTAL; i++) {

			TEST(chmod(FNAME, modes[i]));

			if (TEST_RETURN == -1) {
				tst_resm(TFAIL | TTERRNO,
					 "chmod(%s, %#o) failed", FNAME, modes[i]);
			} else {
				tst_resm(TPASS,
					 "chmod(%s, %#o) returned %ld",
					 FNAME, modes[i], TEST_RETURN);
			}
		}

	}

	cleanup();
	tst_exit();
}

static void setup(void)
{
	tst_sig(NOFORK, DEF_HANDLER, cleanup);

	TEST_PAUSE;

	tst_tmpdir();

	SAFE_FILE_PRINTF(cleanup, FNAME, "File content\n");
}

static void cleanup(void)
{
	tst_rmdir();
}
