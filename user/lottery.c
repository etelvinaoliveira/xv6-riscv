#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int n_processos = 3;
  int tickets[] = {10, 20, 30};
  int processos[n_processos];

  for (int i = 0; i < n_processos; i++) {
    processos[i] = fork();
    if (processos[i] < 0) 
    {
      printf("Fork failed\n");
      exit(1);
    }
    
    if (processos[i] == 0) 
    {
      // Processo filho
      settickets(tickets[i]);
      while(1);  
    }
  }

  //imprimindo os valores que serão usados nos gráficos
  printf("PID Tickets Ticks\n");

  struct pstat pinfo;
  for (int i = 0; i < 50; i++)
  {
    sleep(5);
    getpinfo((uint64)&pinfo);
    for (int j = 0; j < NPROC; j++) 
    {
      for (int k = 0; k < n_processos; k++)
      {
        if (pinfo.pid[j] == processos[k]) 
        {
          printf("%d %d %d\n", pinfo.pid[j], pinfo.tickets[j], pinfo.ticks[j]);
        }
      }
    }
  }
  
  for (int i = 0; i < n_processos; i++)
  {
    kill(processos[i]);
  }
  exit(0);
}
