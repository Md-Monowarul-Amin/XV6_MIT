#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc <= 1){
    printf("error; not enough arguments !!");
    exit(1);
  }
    int time;
    time = atoi(argv[1]);
    sleep(time);
//   for(i = 1; i < argc; i++){
//     write(1, argv[i], strlen(argv[i]));
//     if(i + 1 < argc){
//       write(1, " ", 1);
//     } else {
//       write(1, "\n", 1);
//     }
//   }
  exit(0);
}