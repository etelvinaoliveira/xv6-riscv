#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2){
    printf("Argumento inválido\n");
    exit(1);
  }

  int ticket = settickets(atoi(argv[1]));

  if(ticket == -1){
    printf("Falha ao alocar tickets\n");
    exit(1);
  }

  printf("Tickets alocados com sucesso\n");
  exit(0);
}
