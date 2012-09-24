#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <ncurses.h>

void * thread_code(void * arg);
void sig_handler(int sig);
int filecount = 0;
clock_t start, stop;
double total = 0;
struct tms cput;

int main(void){
  
  char file_input [50];
  pthread_t thread1;
  int status;

  signal(SIGINT,sig_handler);
  initscr();

  while(1){

    mvprintw(0,0,"Enter file name: \n");
    getstr(file_input);
    refresh();
    //    fgets(file_input, sizeof file_input, stdin);
    
    if ((status = pthread_create (&thread1, NULL,thread_code, &file_input)) != 0) {
      printf("thread creation error");
      exit(1);
    }
    clear();
  }

}

void * thread_code(void * arg){
  int r, r0;

  char * file = (char *) arg; 
  
  r = rand() % 9;
  r0 = (rand() % 4) + 7;

  if(r < 8){
    total++;
    sleep(1);
  }
  else{
    total += r0;
    sleep(r0);
  }

  mvprintw(0,40,"file %s accessed\n",file);
  refresh();
  filecount++;
  
  return arg;

}
void sig_handler(int sig){
  
  double average = 0;

  average = total / ((double) filecount);

  endwin();

  if(sig == SIGINT){
    printf("^C handled \n");
    printf("File count: %i \n", filecount);
    printf("Average file access time: %f seconds\n", average);

    exit(0);	
  }

}
