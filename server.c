#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>


void * thread_code(void * arg);
void sig_handler(int sig);
int file_Count = 0;
clock_t start, stop;
double total = 0;
struct tms cput;

int main(void){
  
  char file_input [50];
  pthread_t thread1;
  int status;
  void * result;

  signal(SIGINT,sig_handler);


  while(1){

    printf("Enter file name: ");

    fgets(file_input, sizeof file_input, stdin);
    
    if ((status = pthread_create (&thread1, NULL,thread_code, &file_input)) != 0) {
      printf("thread creation error");
      exit(1);
    }
    


  }



}
void * thread_code(void * arg){
  int r, r0;
  char * file = (char *) arg; 
  r = rand() % 9;
  r0 = (rand() % 4) + 7;
  // start = times(&cput) / CLOCKS_PER_SEC * 1000;
  if(r < 8){
    total++;
    sleep(1);
   
  }
  else{
    total += r0;
    sleep(r0);

  }
  //stop = times(&cput) / CLOCKS_PER_SEC * 1000;
  
  //total += (((double) stop) - ((double) start));
  

  file_Count++;
  
  return arg;

}
void sig_handler(int sig){
  
  double average = 0;

  printf("total= %f\n",total);  
  //average = total / ((double) file_Count + 1);
  average = total / ((double) file_Count + 1);

  if(sig == SIGINT){
    printf(" handled \n");
    printf("File count %i \n", file_Count + 1);
    printf("Average file access time, %f \n", average);
    exit(0);	
  }

}
