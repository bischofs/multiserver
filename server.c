#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>

void * thread_code(void * arg);
void sig_handler(int sig);
int main(void){

  char file_input [50];
  pthread_t thread1;
  int status;

  signal(SIGINT,sig_handler);

  while(1){

    printf("Enter file name: ");
    fgets(file_input, sizeof file_input, stdin);
    
    if ((status = pthread_create (&thread1, NULL,thread_code, NULL)) != 0) {
      printf("thread creation error");
      exit(1);
    }
  }

  printf("Stats ");


}
void * thread_code(void * arg){
  int r, r0;
  r = rand() % 11;
  r0 = (rand() * 3) + 7; 
  if(r <= 8){
    sleep(1);
  }
  else{
    sleep(r0);
  }

}
void sig_handler(int sig){
 
 if(sig == SIGINT){
    printf(" handled /n");
    exit(0);	
  }

}
