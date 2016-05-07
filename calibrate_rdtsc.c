#include <stdio.h>
#include <stdlib.h> 
#include <sys/time.h> 
struct timespec zero = {0,0}; 
typedef unsigned int cycle_t; 
typedef unsigned long long int ull;
 
inline cycle_t get_cycles() 
{ 
  cycle_t ret; 
  asm volatile("rdtsc" : "=A" (ret)); 
  return ret; 
} 

static inline ull RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((ull)hi << 32) | lo;
}

int main() {
  struct timeval tv1, tv2;
  
  gettimeofday(&tv1, NULL);
  ull start_micro = tv1.tv_sec * 1000000 + tv1.tv_usec;
  ull start_tsc = RDTSC();
  ull curr_micro;
  while(1) {
    gettimeofday(&tv2, NULL);
    curr_micro = tv2.tv_sec * 1000000 + tv2.tv_usec;
    if((curr_micro - start_micro) > (10 * 1000000)) {
      break;
    }
  }
  ull end_tsc = RDTSC();
  ull time_tsc = end_tsc - start_tsc;
  ull time_micro = curr_micro - start_micro;
  double conversion = (1000 * time_tsc) / time_micro;
  printf("Conversion is %lf cycles per milli-second\n", conversion);
  return 0;
}
