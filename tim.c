/* time example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

int main ()
{
  time_t timer;
  struct tm y2k;
  int seconds, a, b, c, d;
  int mins;
  int hours;


  time(&timer);  /* get current time; same as: timer = time(NULL)  */

  seconds = (int)timer;

  mins = seconds / 60 % 60;

  hours = seconds / 360 % 24;

	a = mins%10;
	b = mins/10;
	c = hours%10;
	d = hours/10;
  printf ("%d seconds since January 1, 2000 in the current timezone\n", seconds);
  printf ("%d %d : %d %d\n", d, c, b, a);
  printf ("%d : %d \n", hours, mins);

  return 0;
}
