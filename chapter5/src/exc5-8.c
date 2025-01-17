/* Exercise 5-8. There is no error checking in day_of_year or month_day.
 * remedy this defect */

static char daytab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {

    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 && year % 400 == 0;

    if (year < 0)
        return -1; // error: invalid year
    else if (month < 1 || month > 13)
        return -1; // error: invalid month
    else if (day < 0 || day > daytab[leap][month])
        return -1; // error: invalid day for specific month

    for (i = 1; i < month; i++) day += daytab[leap][i];

    return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int* pmonth, int* pday) {

    int i, leap;

    if (yearday < 0 || yearday > 365) return -1; // error: invalid day

    leap = year % 4 == 0 && year % 100 != 0 && year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++) yearday -= daytab[leap][i];

    *pmonth = i;
    *pday = yearday;

    return 0; // success
}

