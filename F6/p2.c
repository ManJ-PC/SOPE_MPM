#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h> 

#define STDERR 2 
#define NUMITER 1000000

int total = 0;

void * thrfunc(void * arg) { 
  int *sub = (int *)malloc(sizeof(int));
  
  *sub = 0;
  fprintf(stderr, "Starting thread %c\n", *(char *) arg); 
  while (total < NUMITER) {
    write(STDERR, arg, 1); 
    total++;
    (*sub)++;
  }
  return sub; 
}

int main() {  
  pthread_t ta, tb;
  int *sub1, *sub2;
  
  pthread_create(&ta, NULL, thrfunc, "1"); 
  pthread_create(&tb, NULL, thrfunc, "2"); 
  pthread_join(ta, (void **) &sub1); 
  pthread_join(tb, (void **) &sub2); 
  printf("\nT1: %d   T2: %d     Total: %d\n", *sub1, *sub2, *sub1 + *sub2);
  free(sub1);
  free(sub2);
  return 0; 
}
