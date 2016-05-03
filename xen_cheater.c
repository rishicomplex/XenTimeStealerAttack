#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> 
struct timespec zero = {0,0}; 
typedef unsigned int cycle_t; 
typedef unsigned long long int ull;

#define CYCLES_PER_MILLISECOND 2394559

ull count = 0;

void interruptHandler(int dummy) {
  printf("Number of loops: %llu\n", count);
  exit(0);
}
 
static inline ull RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((ull)hi << 32) | lo;
}

ull convertCyclesToMilliseconds(ull cycles) {
  return (cycles / CYCLES_PER_MILLISECOND);
}

int main(int argc, char *argv[]) {
  int segment;
  if(argc == 1) {
    segment = 27;
  }
  else {
    segment = atoi(argv[1]);
  }
  signal(SIGINT, interruptHandler);
  ull prev = RDTSC();
  ull curr;
  ull diff;

  while(1) {
    curr = RDTSC();
    diff = curr - prev;
    count++;
    if(convertCyclesToMilliseconds(diff) > segment) {
      
      //printf("Pre-empting \n");
      usleep(500);
      prev = RDTSC();
    }
  }
  
  return 0;
}
