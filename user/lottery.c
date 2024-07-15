#include "kernel/types.h"
#include "kernel/pstat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  const char * output_file = "./results.csv";
  int n_processos = 3;
  struct pstat pinfo;

  if(argv[1][0]>='1'){
    n_processos = atoi(argv[1]);
  }

  int file = open(output_file, O_WRONLY);

  int processos[n_processos];
  
  for(int i = 0; i<n_processos; i++){
    processos[i] = fork();
    if(processos[i] < 0) { 
      exit(1);
    } 
    if (processos[i]==0)
    {
      settickets((i+1)*10);
    }
  }

  for (int i = 0; i < 100; i++){
    getpinfo((uint64)&pinfo);
    for (int j = 0; j < NPROC; j++){
      for(int k = 0; k < n_processos; k++){
        if(pinfo.pid[j] == processos[k]){
          fprintf(file, "%d,%d\n", pinfo.ticks[j], pinfo.pid[j]);
          //fprintf(2, "%d,%d\n", pinfo.ticks[j], pinfo.pid[j]);
        }
      }
    } 
  }
  close(file);

  exit(0);
}