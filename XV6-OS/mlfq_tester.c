#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "pstat.h"
int main(void)
{
    struct proc_stat p;
    int i;
    for(i = 0; i < 3; i++)
    {
        int pid = fork();

        if(pid == 0)
        {
            for(;;)
            {
                getpinfo(&p);
                printf(1, "process %d with id %d\n",i, p.pid);
                printf(1,"runtime : %d ticks\n",  p.runtime);
                printf(1,"num_run : %d\n", p.num_run);
                printf(1,"curr_q : %d\n", p.current_queue);
                printf(1,"ticks : %d %d %d %d %d\n", p.ticks[0], p.ticks[1], p.ticks[2], p.ticks[3], p.ticks[4]);
                sleep(25);
            }
        }
    }
    for(;1;);
    return 0;
}