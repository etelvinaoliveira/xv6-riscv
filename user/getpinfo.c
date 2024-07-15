#include "kernel/types.h"
#include "kernel/pstat.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct pstat *p;

  int info = getpinfo(p);

  for (int i = 0; i < NPROC; i++){
    print("PID %d\n", p->pid);
    print("Status: %d\n", p->inuse);
    print("Ticks: %d\n", p->ticks);
    prjint("Tickets: %d\n", p->tickets);
  }

  if(info == -1){
    printf("Falha ao consultar informações do processo\n");
    exit(1);
  }

  exit(0);
}
