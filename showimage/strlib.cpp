/*** analog 2.1 ***/
/* Please read Readme.html, or http://www.statslab.cam.ac.uk/~sret1/analog/  */

/*** utils.c; lots of little functions to do odd little things ***/

#include "analhea2.h"

/* First, wildcard matching. */

flag matchq(char *string, char *pattern, flag whole)
/* [<][>][^][v][top][bottom][index][help] */
{        /* Match with no *'s, whole or start of string against pattern */
  flag answer;

  for (answer = TRUE; answer == TRUE && *pattern != '\0' ; ) {
    answer = (*string == *pattern || *pattern == '?') && (*string != '\0');
    string++;
    pattern++;
  }

  if (whole && *string != '\0')
    return(FALSE);

  return(answer);
}

flag wildmatch(char *string, char *pattern, char **w1, char **w2)
/* [<][>][^][v][top][bottom][index][help] */
{   /* w1 and &w2 changed to reflect part of string represented by final *   */
  char *c;
  flag matched;
  int len;
  char tempstr[MAXSTRINGLENGTH];
  flag tempflag;

  strcpy(tempstr, pattern);   /* so pattern won't be destroyed by strtok */

  if ((c = strrchr(tempstr, '*')) == NULL) {   /* no *'s */
    *w1 = string;
    *w2 = string;
    return(matchq(string, pattern, TRUE));
  }
  else {
    *w2 = string + MAX(strlen(string) - strlen(c + 1), 0);
    if (!matchq(*w2, c + 1, TRUE))      /* if tail portions don't match */
      return(0);
    *c = '\0';   /* o/wise we'll end up matching the tail twice */
    c = strtok(tempstr, "*");
    if (pattern[0] == '*') {   /* don't need to match against beginning */
      tempflag = ON;
      *w1 = string;
    }
    else {
      tempflag = OFF;
      if (matchq(string, c, FALSE) == FALSE)
        return(FALSE);    /* check first bit matches beginning of string */
      *w1 = string + strlen(c); /* w1 measures where we're up to in string */
      if (*w1 > *w2)
        return(FALSE);   /* start and end of pattern overlapped in string */
    }
    if (tempflag && c == NULL)
      return(TRUE);  /* this only occurs with patterns like "*nomorestars" */
    else while (tempflag || ((c = strtok((char *)NULL, "*")) != NULL)) {
      /* if tempflag, c is already set to after initial *  */
      tempflag = OFF;
      matched = FALSE;
      len = strlen(c);
      while (*w1 + len <= *w2 && matched == FALSE) {
        if (matchq(*w1, c, FALSE) == TRUE)
          matched = TRUE;
        else
          (*w1)++;
      }
      if (!matched)
        return(FALSE);
      else
        *w1 += len;
    }
    return(TRUE);  /* if got this far, matched everything */
  }
}

int strtomonth(char month[4])  /* convert 3 letter month abbrev. to int */
/* [<][>][^][v][top][bottom][index][help] */
{
  int monthno = ERR;

  switch (month[0]) {
  case 'A':
    switch (month[1]) {
    case 'p':
      monthno = 3;
      break;
    case 'u':
      monthno = 7;
      break;
    }
    break;
    case 'D':
    monthno = 11;
      break;
  case 'F':
    monthno = 1;
    break;
    case 'J':
    switch (month[1]) {
    case 'a':
      monthno = 0;
      break;
    case 'u':
      switch (month[2]) {
      case 'l':
        monthno = 6;
        break;
      case 'n':
        monthno = 5;
        break;
      }
      break;
    }
    break;
  case 'M':
    switch (month[2]) {
    case 'r':
      monthno = 2;
      break;
    case 'y':
      monthno = 4;
      break;
    }
    break;
  case 'N':
    monthno = 10;
    break;
  case 'O':
    monthno = 9;
      break;
  case 'S':
    monthno = 8;
    break;
  }

  return(monthno);

}

int dayofdate(int date, int monthno, int year)  /* day of week of given date */
/* [<][>][^][v][top][bottom][index][help] */
{
  extern int dateoffset[];

  int x;
  x = dateoffset[monthno] + date + year + (year / 4) + 5 -
    ISLEAPJF(monthno, year);
  return(x % 7);
}

int minsbetween(int date1, int monthno1, int year1, int hr1, int min1,
/* [<][>][^][v][top][bottom][index][help] */
                int date2, int monthno2, int year2, int hr2, int min2)
{
  extern int dateoffset[];

  int x, y;
  x = dateoffset[monthno1] + date1 + year1 * 365 + (year1 / 4) -
    ISLEAPJF(monthno1, year1);
  y = dateoffset[monthno2] + date2 + year2 * 365 + (year2 / 4) -
    ISLEAPJF(monthno2, year2);

  return((y - x) * 1440 + (hr2 - hr1) * 60 + (min2 - min1));
}

long timecode(int date, int monthno, int year, int hr, int min)
/* [<][>][^][v][top][bottom][index][help] */
{   /* calculate a 'timecode', i.e. increasing function of time */

  return((year - 1990) * 535680 +       /* 60 * 24 * 31 * 12 */
         monthno * 44640 +
         date * 1440 +
         hr * 60 +
         min);
}

struct timestruct startofweek(struct timestruct atime)
/* [<][>][^][v][top][bottom][index][help] */
{  /* given a time, what is the time at the start of that week? */

  extern int monthlength[];

  extern int weekbeginson;

  struct timestruct answer;
  int day;
  
  day = dayofdate(atime.date, atime.monthno, atime.year);

  answer.date = atime.date - day + weekbeginson;
           /* giving a weekbeginson-day in [date - 6, date + 6] */
  if (answer.date > atime.date)
    answer.date -= 7;
  answer.monthno = atime.monthno;
  answer.year = atime.year;

  if (answer.date <= 0) {
    answer.monthno--;
    if (answer.monthno == -1) {
      answer.monthno = 11;
      answer.year--;
    }
    answer.date = monthlength[answer.monthno] + answer.date +
      ISLEAPFEB(answer.monthno, answer.year);
  }

  answer.code = timecode(answer.date, answer.monthno, answer.year,
                         answer.hr = 0, answer.min = 0);

  return(answer);

}

FILE *fopenlog(char *name, char logtype[14], flag *ispipe)
/* [<][>][^][v][top][bottom][index][help] */
{             /* open a logfile with a particular name for reading */
#ifndef NOPIPES
  extern FILE *popen();
#endif

  extern char *commandname;
#ifndef NOPIPES
  extern struct loglist *uncompresshead;
#endif
  extern flag warnq, anywarns, stdin_used;
  extern int debug;

  FILE *f;
#ifndef NOPIPES
  struct loglist *uncompressp;
  char *w1, *w2;
  char command[MAXSTRINGLENGTH];
#endif

  *ispipe = OFF;

  if (STREQ(name, "stdin") || STREQ(name, "-")) {
    if (stdin_used) {
      if (warnq) {
        fprintf(stderr,
                "%s: Warning: stdin already used; cannot use it as %s\n",
                commandname, logtype);
        anywarns = ON;
      }
    }
    else {
      f = stdin;
      stdin_used = ON;
      if (debug > 0)
        fprintf(stderr, "F: Opening stdin as %s\n", logtype);
    }
  }
  else {
#ifdef VMS
    f = fopen(name, "r", "shr=upd");
#else
    f = fopen(name, "r");
#endif
    if (f == NULL) {
      if (warnq) {
        fprintf(stderr, "%s: Warning: Failed to open %s %s: ignoring it\n",
                commandname, logtype, name);
        anywarns = ON;
      }
    }
    else {
      if (debug > 0)
        fprintf(stderr, "F: Opening %s as %s\n", name, logtype);
#ifndef NOPIPES
      for (uncompressp = uncompresshead; uncompressp -> name[0] != '\0' &&
           !(*ispipe); uncompressp = uncompressp -> next) {
        if (wildmatch(name, uncompressp -> name, &w1, &w2)) {
          fclose(f);
          strcpy(command, uncompressp -> prefix);
          strcat(command, " ");
          strncat(command, name, MAXSTRINGLENGTH - strlen(command) - 1);
          f = popen(command, "r");
          *ispipe = ON;
          if (debug > 0)
            fprintf(stderr, "F:   Using %s to uncompress it\n",
                    uncompressp -> prefix);
        }
      }
#endif
    }
  }

  return(f);
}

int fcloselog(FILE *f, char *name, char logtype[14], flag ispipe)
/* [<][>][^][v][top][bottom][index][help] */
{     /* close it again */  /* logtype only used if NOPIPES off */
#ifndef NOPIPES
  extern int pclose();
#endif

  extern int debug;

#ifndef NOPIPES
  extern char *commandname;
  extern flag warnq, anywarns;
#endif

  int rc;

  if (debug > 0)
    fprintf(stderr, "F: Closing %s\n", STREQ(name, "-")?"stdin":name);
  if (!ispipe)
    rc = fclose(f);    /* Not much can go wrong with fclose. I hope. */
#ifndef NOPIPES
  else if ((rc = pclose(f)) != 0 && warnq) {
    fprintf(stderr, "%s: Warning: Problems uncompressing %s %s\n",
            commandname, logtype, name);
    anywarns = ON;
  }
#endif
  return(rc);
}

void int3printf(FILE *outf, int x, char sepchar, int fieldwidth)
/* [<][>][^][v][top][bottom][index][help] */
                    /* print +ve integer with separators every 3 digits */
{                   /* assume fieldwidth is 0, or large enough */
  extern int aq;

  int i = 1, len = 0;

  if (sepchar == '\0') {
    if (fieldwidth == 0)
      fprintf(outf, "%d", x);
    else
      fprintf(outf, "%*d", fieldwidth, x);
  }

  else {
    while (x / 1000 >= i) {   /* i * 1000 might overflow */
      i *= 1000;     /* find how big x is, so we know where to start */
      len += 4;
    }

    if (fieldwidth == 0)
      fprintf(outf, "%d", (x / i) % 1000);
    else
      fprintf(outf, "%*d", fieldwidth - len, (x / i) % 1000);
                           /* now run down again, printing each clump */

    for ( i /= 1000; i >= 1; i /= 1000) {
      if (aq == HTML)
        htmlputc(sepchar, outf);
      else
        fprintf(outf, "%c", sepchar);
      fprintf(outf, "%03d", (x / i) % 1000);
    }
  }
}

void double3printf(FILE *outf, double x, char sepchar, int fieldwidth)
/* [<][>][^][v][top][bottom][index][help] */
                         /* the same, only with +ve INTEGER doubles */
{
  extern int aq;

  int i = 0;

  x += 0.1;   /* to make sure floors go in the right direction */

  if (x < 0.6) {
    for (i = fieldwidth; i > 1; i--)
      fprintf(outf, " ");
    fprintf(outf, "0");
  }

  else if (sepchar == '\0') {
    if (fieldwidth == 0)
      fprintf(outf, "%.0f", x);
    else
      fprintf(outf, "%*.0f", fieldwidth, x);
  }

  else {

    while (x >= 1000) {
      x /= 1000;
      i++;
    }

    if (i == 0) {
      if (fieldwidth == 0)
        fprintf(outf, "%d", (int)ROUND(x));
      else
        fprintf(outf, "%*d", fieldwidth - 4 * i, (int)ROUND(x));
    }
    else if (fieldwidth == 0)
      fprintf(outf, "%d", (int)floor(x));
    else
      fprintf(outf, "%*d", fieldwidth - 4 * i, (int)floor(x));

    for ( ; i >= 1; i--) {
      x -= (int)x;
      x *= 1000;
      if (aq == HTML)
        htmlputc(sepchar, outf);
      else
        fprintf(outf, "%c", sepchar);
      if (i == 1)
        fprintf(outf, "%03d", (int)ROUND(x));
      else
        fprintf(outf, "%03d", (int)floor(x));
    }
  }
}

void doublefprintf(FILE *outf, double x)
/* [<][>][^][v][top][bottom][index][help] */
{                 /* print a double in %f format without trailing zeros */
  extern char decpoint;

  int prec = 0;
  double d;

  /* first calculate how many decimal places we need */

  for (d = x - floor(x); d - floor(d + 0.000005) > 0.00001; d *= 10)
    prec++;

  /* now print it */

  if (prec > 0) {
    fprintf(outf, "%d", (int)floor(x));
    fprintf(outf, "%c%0*d", decpoint, prec, (int)ROUND(d));
  }
  else
    fprintf(outf, "%d", (int)ROUND(x));
}

void *xmalloc(size_t size)
/* [<][>][^][v][top][bottom][index][help] */
{    /* the same as malloc, only checks for out of memory */

  extern char *commandname;
  extern flag sq;

  void *answer;

  if ((answer = malloc(size)) == NULL) {
    fprintf(stderr, "%s: Ran out of memory: cannot continue\n", commandname);
    if (sq == ON) {
#ifdef MAC
      fprintf(stderr, "  Try allocating more memory or using approximate host counting.\n");
#else
      fprintf(stderr, "  Try turning hostname counting off or using approximate host counting.\n");
#endif
    }
    exit(ERR);
  }

  return(answer);
}

void *xcalloc(size_t nelem, size_t elsize)
/* [<][>][^][v][top][bottom][index][help] */
{    /* ditto calloc */

  extern char *commandname;
  extern flag sq;

  void *answer;

  if ((answer = calloc(nelem, elsize)) == NULL) {
    fprintf(stderr, "%s: Ran out of memory: cannot continue\n", commandname);
    if (sq == ON) {
#ifdef MAC
      fprintf(stderr, "  Try allocating more memory or using approximate host counting.\n");
#else
      fprintf(stderr, "  Try turning hostname counting off or using approximate host counting.\n");
#endif
    }
    exit(ERR);
  }

  return(answer);
}

char *strtolower(char *string)
/* [<][>][^][v][top][bottom][index][help] */
{         /* convert a string to lower case */

  char *c;

  for (c = string ; *c != '\0'; c++)
    *c = tolower(*c);

  return(string);
}

flag strtolowerf(char *string)
/* [<][>][^][v][top][bottom][index][help] */
{         /* convert a string, return whether any changes required */

  char *c;
  flag ans = FALSE;

  for (c = string ; *c != '\0'; c++) {
    if (isupper(*c)) {
      ans = TRUE;
      *c = tolower(*c);
    }
  }

  return(ans);
}

char *strtoupper(char *string)
/* [<][>][^][v][top][bottom][index][help] */
{         /* convert a string to upper case */

  char *c;

  for (c = string; *c != '\0'; c++)
    *c = toupper(*c);

  return(string);
}

int hoststrcmp(char *hostn1, char *hostn2)
/* [<][>][^][v][top][bottom][index][help] */
{   /* given two reversed hostnames, what is their "alphabetical" order? */

  char hostn1cpy[MAXSTRINGLENGTH], hostn2cpy[MAXSTRINGLENGTH];
  char *part11, *part12, *part13, *part14, *part2;
  int tempint1, tempint2;

  if (!isdigit(*hostn1)) {
    if (isdigit(*hostn2))
      return(-1);    /* all numbers come after all letters */
    else
      return(strcmp(hostn1, hostn2));   /* both non-numbers; usual alphabet */
  }
  else if (!isdigit(*hostn2))
    return(1);
  else  {
    /* the difficult case; both numerical. Convert bits to numbers */
    strcpy(hostn1cpy, hostn1);   /* because strtok destroys the string */
    strcpy(hostn2cpy, hostn2);
    part11 = strtok(hostn1cpy, ".");
    part12 = strtok((char *)NULL, ".");
    part13 = strtok((char *)NULL, ".");
    part14 = strtok((char *)NULL, ".");

    part2 = strtok(hostn2cpy, ".");
    tempint1 = atoi(part11);
    tempint2 = atoi(part2);
    if (tempint1 != tempint2)
      return(tempint1 - tempint2);
    else {
      part2 = strtok((char *)NULL, ".");
      if (part12 == NULL && part2 == NULL)
        return(0);
      else if (part12 == NULL)
        return(-999);
      else if (part2 == NULL)
        return(999);
      else {
        tempint1 = atoi(part12);
        tempint2 = atoi(part2);
        if (tempint1 != tempint2)
          return(tempint1 - tempint2);
        else {
          part2 = strtok((char *)NULL, ".");
          if (part13 == NULL && part2 == NULL)
            return(0);
          else if (part13 == NULL)
            return(-999);
          else if (part2 == NULL)
            return(999);
          else {
            tempint1 = atoi(part13);
            tempint2 = atoi(part2);
            if (tempint1 != tempint2)
              return(tempint1 - tempint2);
            else {
              part2 = strtok((char *)NULL, ".");
              if (part14 == NULL && part2 == NULL)
                return(0);
              else if (part14 == NULL)
                return(-999);
              else if (part2 == NULL)
                return(999);
              else {
                tempint1 = atoi(part14);
                tempint2 = atoi(part2);
                if (tempint1 != tempint2)
                  return(tempint1 - tempint2);
                else
                  return(0);
              }
            }
          }
        }
      }
    }
  }
}

/* Next, whether a host name is a numeric IP address */
/* Actually we only check whether it consists only of digits & dots */

flag isnumeric(char *name)
/* [<][>][^][v][top][bottom][index][help] */
{
  for ( ; *name != '\0'; name++)
    if (!isdigit(*name) && *name != '.')
      return(FALSE);
  return(TRUE);
}

