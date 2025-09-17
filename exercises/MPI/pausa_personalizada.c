
#if defined(_AIX)
#include <errno.h>
#include <sys/time.h>
int new_sleep (int *amount)
{
        struct timestruc_t Requested, Remaining;
        double famount = *amount;
        int rc;
        while (famount > 0.0) {
                Requested.tv_sec = (int) famount;
                Requested.tv_nsec =
                        (int) ((famount - Requested.tv_sec)*1000000000.);
                rc = nsleep ( &Requested, &Remaining );
                if ((rc == -1) && (errno == EINTR)) {
                        /* Sleep interrupted.  Resume it */
                        famount = Remaining.tv_sec + Remaining.tv_nsec /
                                                        1000000000.;
                        continue;
                }
                else /* Completed sleep.  Set return to zero */
                {
                                return (0);
                }
        }    /* end of while */

        /* famount = 0.; exit */
        return (0);
}

#elif defined(__INTEL_COMPILER) || (__PGI)
#include <unistd.h>
int new_sleep (int *amount)
{
  unsigned int secs = *amount, remain;
  remain=sleep(secs);
  while(remain) {
    remain=sleep(remain);
  }

  return 0;
}
int new_sleep_(int *amount)
{
  return(new_sleep(amount));
}

/* A simulated version of IBMs irtc() */
#include <sys/time.h>
long int irtc() {
  struct timeval tv;
    gettimeofday ( &tv, (struct timezone*)0 );
    return 1000*( tv.tv_sec * 1000000 + tv.tv_usec);
}
long int irtc_() {
  return irtc();
}
#else
#error No new_sleep function defined
#endif
