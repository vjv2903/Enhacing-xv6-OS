#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "pstat.h"

int
main(int argc, char *argv[])
{
    int id = fork();
    if (id == 0) 
    {
        set_priority(30, 0);
        double z, d = 1, x = 0;
        for (int i = 0; i < 5; ++i) 
        {
            for (int j = 0; j < 10; ++j) 
            {
                for (z = 0; z < 2000000; z += d) 
                {
                    x = x + 3.14 * 89.64; // useless calcs
                }
            }
        }
        #ifdef MLFQ
        struct proc_stat ps;
        getpinfo(&ps);
        printf(1, "\nPID == %d\n", ps.pid);
        printf(1,"Run_time = %d\n", ps.runtime);
        printf(1,"Num_run = %d\n", ps.num_run);
        printf(1,"current_queue=%d\n", ps.current_queue);
        printf(1, "ticks : ");
        for(int i=0;i<5;i++) 
        {
            printf(1, "%d ", ps.ticks[i]);
        }
        printf(1, "\n");
        #endif
        printf(1, "test 3 ended\n");
        exit();
    }
    int wtime, rtime;
    waitx(&wtime, &rtime);
    printf(1, "wait = %d run = %d\n", wtime, rtime);
    exit();
}
