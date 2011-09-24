/* in utils.c */
extern flag matchq(char *string, char *pattern, flag whole);
extern flag wildmatch(char *string, char *pattern, char **w1, char **w2);
extern int strtomonth(char month[4]);
extern int dayofdate(int date, int monthno, int year);
extern int minsbetween(int date1, int monthno1, int year1, int hr1, int min1,
  int date2, int monthno2, int year2, int hr2, int min2);
extern long timecode(int date, int monthno, int year, int hr, int min);
extern struct timestruct startofweek(struct timestruct atime);
extern FILE *fopenlog(char *name, char logtype[14], flag *ispipe);
extern int fcloselog(FILE *f, char *name, char logtype[14], flag ispipe);
extern void int3printf(FILE *outf, int x, char sepchar, int fieldwidth);
extern void double3printf(FILE *outf, double x, char sepchar, int fieldwidth);
extern void doublefprintf(FILE *outf, double x);
extern void *xmalloc(size_t size);
extern void *xcalloc(size_t nelem, size_t elsize);
extern char *strtolower(char *string);
extern flag strtolowerf(char *string);
extern char *strtoupper(char *string);
extern int hoststrcmp(char *hostn1, char *hostn2);
extern flag isnumeric(char *name);
