/*
 * Adaptation of NetBSD code for RTEMS by Victor V. Vengerov <vvv@oktet.ru>
 */
/*	$NetBSD: msdosfs_conv.c,v 1.10 1994/12/27 18:36:24 mycroft Exp $	*/
/*
 * Written by Paul Popelka (paulp@uts.amdahl.com)
 * 
 * You can do anything you want with this software, just don't say you wrote
 * it, and don't remove this notice.
 * 
 * This software is provided "as is".
 * 
 * The author supplies this software to be publicly redistributed on the
 * understanding that the author is not responsible for the correct
 * functioning of this software in any circumstances and is not liable for
 * any damages caused by this software.
 * 
 * October 1992
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <rtems.h>
#include "msdos.h"
/*
 * Days in each month in a regular year.
 */
static u_short regyear[] = {
	31, 28, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31
};

/*
 * Days in each month in a leap year.
 */
static u_short leapyear[] = {
	31, 29, 31, 30, 31, 30,
	31, 31, 30, 31, 30, 31
};

/*
 * Variables used to remember parts of the last time conversion.  Maybe we
 * can avoid a full conversion.
 */
static u_long lasttime;
static u_long lastday;
static u_short lastddate;
static u_short lastdtime;

/*
 * Convert the unix version of time to dos's idea of time to be used in
 * file timestamps. The passed in unix time is assumed to be in GMT.
 */
void
msdos_date_unix2dos(unsigned int t, unsigned short *ddp, 
                    unsigned short *dtp)
{
	u_long days;
	u_long inc;
	u_long year;
	u_long month;
	u_short *months;

	/*
	 * If the time from the last conversion is the same as now, then
	 * skip the computations and use the saved result.
	 */
	if (lasttime != t) {
		lasttime = t;
		lastdtime = (((t % 60) >> 1) << MSDOS_DT_2SECONDS_SHIFT)
		    + (((t / 60) % 60) << MSDOS_DT_MINUTES_SHIFT)
		    + (((t / 3600) % 24) << MSDOS_DT_HOURS_SHIFT);

		/*
		 * If the number of days since 1970 is the same as the last
		 * time we did the computation then skip all this leap year
		 * and month stuff.
		 */
		days = t / (24 * 60 * 60);
		if (days != lastday) {
			lastday = days;
			for (year = 1970;; year++) {
				inc = year & 0x03 ? 365 : 366;
				if (days < inc)
					break;
				days -= inc;
			}
			months = year & 0x03 ? regyear : leapyear;
			for (month = 0; month < 12; month++) {
				if (days < months[month])
					break;
				days -= months[month];
			}
			lastddate = ((days + 1) << MSDOS_DD_DAY_SHIFT)
			    + ((month + 1) << MSDOS_DD_MONTH_SHIFT);
			/*
			 * Remember dos's idea of time is relative to 1980.
			 * unix's is relative to 1970.  If somehow we get a
			 * time before 1980 then don't give totally crazy
			 * results.
			 */
			if (year > 1980)
				lastddate += (year - 1980) << 
				             MSDOS_DD_YEAR_SHIFT;
		}
	}
	*dtp = lastdtime;
	*ddp = lastddate;
}

/*
 * The number of seconds between Jan 1, 1970 and Jan 1, 1980. In that
 * interval there were 8 regular years and 2 leap years.
 */
#define	SECONDSTO1980	(((8 * 365) + (2 * 366)) * (24 * 60 * 60))

static u_short lastdosdate;
static u_long lastseconds;

/*
 * Convert from dos' idea of time to unix'. This will probably only be
 * called from the stat(), and fstat() system calls and so probably need
 * not be too efficient.
 */
unsigned int
msdos_date_dos2unix(unsigned int dd, unsigned int dt)
{
	u_long seconds;
	u_long m, month;
	u_long y, year;
	u_long days;
	u_short *months;

	seconds = ((dt & MSDOS_DT_2SECONDS_MASK) >> MSDOS_DT_2SECONDS_SHIFT)
	    + ((dt & MSDOS_DT_MINUTES_MASK) >> MSDOS_DT_MINUTES_SHIFT) * 60
	    + ((dt & MSDOS_DT_HOURS_MASK) >> MSDOS_DT_HOURS_SHIFT) * 3600;
	/*
	 * If the year, month, and day from the last conversion are the
	 * same then use the saved value.
	 */
	if (lastdosdate != dd) {
		lastdosdate = dd;
		days = 0;
		year = (dd & MSDOS_DD_YEAR_MASK) >> MSDOS_DD_YEAR_SHIFT;
		for (y = 0; y < year; y++)
			days += y & 0x03 ? 365 : 366;
		months = year & 0x03 ? regyear : leapyear;
		/*
		 * Prevent going from 0 to 0xffffffff in the following
		 * loop.
		 */
		month = (dd & MSDOS_DD_MONTH_MASK) >> MSDOS_DD_MONTH_SHIFT;
		if (month == 0) {
			month = 1;
		}
		for (m = 0; m < month - 1; m++)
			days += months[m];
		days += ((dd & MSDOS_DD_DAY_MASK) >> MSDOS_DD_DAY_SHIFT) - 1;
		lastseconds = (days * 24 * 60 * 60) + SECONDSTO1980;
	}
	return seconds + lastseconds;
}

static const u_char msdos_map[] = {
/* 00 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 08 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 10 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 18 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 20 */ 0x00, 0x21, 0x00, 0x23, 0x24, 0x25, 0x26, 0x27, /*  !"#$%&' */
/* 28 */ 0x28, 0x29, 0x00, 0x00, 0x00, 0x2D, 0x2E, 0x00, /* ()*+,-./ */
/* 30 */ 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, /* 01234567 */
/* 38 */ 0x38, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* 89:;<=>? */
/* 40 */ 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* @ABCDEFG */
/* 48 */ 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* HIJKLMNO */
/* 50 */ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, /* PQRSTUVW */
/* 58 */ 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x00, 0x5E, 0x5F, /* XYZ[\]^_ */
/* 60 */ 0x60, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* `abcdefg */
/* 68 */ 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, /* hijklmno */
/* 70 */ 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, /* pqrstuvw */
/* 78 */ 0x58, 0x59, 0x5A, 0x5B, 0x7C, 0x00, 0x7E, 0x00, /* xyz{|}~  */
/* 80 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 88 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 90 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 98 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* A0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* A8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* B0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* B8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* C0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* C8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* D0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* D8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* E0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* E8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* F0 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* F8 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
/*
 * Convert a unix filename to a DOS filename. Return -1 if wrong name is
 * supplied.
 */
int
msdos_filename_unix2dos(char *un, int unlen, char *dn)
{
	int i;
	u_char c;

	/*
	 * Fill the dos filename string with blanks. These are DOS's pad
	 * characters.
	 */
	for (i = 0; i <= 10; i++)
		dn[i] = ' ';

	/*
	 * The filenames "." and ".." are handled specially, since they
	 * don't follow dos filename rules.
	 */
	if (un[0] == '.' && unlen == 1) {
		dn[0] = '.';
		return 0;
	}
	if (un[0] == '.' && un[1] == '.' && unlen == 2) {
		dn[0] = '.';
		dn[1] = '.';
		return 0;
	}

	/*
	 * Copy the unix filename into the dos filename string upto the end
	 * of string, a '.', or 8 characters. Whichever happens first stops
	 * us. This forms the name portion of the dos filename. Fold to
	 * upper case.
	 */
	for (i = 0; i <= 7 && unlen && (c = *un) && c != '.'; i++) {
		if ((dn[i] = msdos_map[c]) == 0)
                        return -1;
		un++;
		unlen--;
	}

	/*
	 * Strip any further characters up to a '.' or the end of the
	 * string.
	 */
	while (unlen && (c = *un)) {
		un++;
		unlen--;
		/* Make sure we've skipped over the dot before stopping. */
		if (c == '.')
			break;
	}

	/*
	 * Copy in the extension part of the name, if any. Force to upper
	 * case. Note that the extension is allowed to contain '.'s.
	 * Filenames in this form are probably inaccessable under dos.
	 */
	for (i = 8; i <= 10 && unlen && (c = *un); i++) {
		if ((dn[i] = msdos_map[c]) == 0)
		        return -1;
		un++;
		unlen--;
	}
	return 0;
}
