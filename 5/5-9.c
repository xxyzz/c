#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {
  printf("day_of_year(2020, 8, 10): %d\n", day_of_year(2020, 8, 10));
  printf("day_of_year(2020, 2019, 10): %d\n", day_of_year(2020, 2019, 10));
  printf("day_of_year(2020, 8, 42): %d\n", day_of_year(2020, 8, 42));

  int month, day;
  month_day(1989, 155, &month, &day);
  printf("month_day(1989, 155) month: %d, day: %d\n", month, day);
  month_day(1989, -155, &month, &day);
  printf("month_day(1989, -155) month: %d, day: %d\n", month, day);
  return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
  int leap;

  if (year < 1)
    return -1;
  if (month < 1 || month > 12)
    return -1;

  leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
  char *tabp = daytab[leap] + 1;
  if (day < 1 || day > *(tabp + month))
    return -1;
  while (--month)
    day += *tabp++;
  return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i = 1, leap = 0;

  if (year > 0 && yearday > 0) {
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    char *tabp = daytab[leap] + 1;
    if ((!leap && yearday <= 365) || (leap && yearday <= 366))
      while (yearday > *tabp) {
        yearday -= *tabp++;
        i++;
      }
    else {
      i = -1;
      yearday = -1;
    }
  } else {
    i = -1;
    yearday = -1;
  }

  *pmonth = i;
  *pday = yearday;
}
