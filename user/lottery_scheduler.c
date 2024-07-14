#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"
#include <stdio.h>

int
main(int argc, char *argv[])
{
  char output_file = "results.csv";
  int n_processos;
  struct pstat pinfo;

  if(argv[0]>=3){
    n_processos = atoi(argv[0]);
  }

  FILE *file = fopen(output_file, "w");

  int processos[n_processos];
  
  for(int i = 0; i<n_processos; i++){
    processos[i] = fork();
    if(processos[i] < 0) exit(1);
  }

  for (int i = 0; i < n_processos; i++){
    settickets((i+1)*10);
  }

  for (int i = 0; i < 100; i++){
    getpinfo(&pinfo);
    for (int j = 0; j < NPROC; j++){
      for(int k = 0; k < n_processos; k++){
        if(pinfo.pid[j] == processos[k]){
          fprintf(file, "%d,%d\n", pinfo.ticks[j], pinfo.pid[j]);
        }
      }
    } 
  }

  exit(0);
}