#define _GNU_SOURCE   
#include <stdio.h>    
#include <stdlib.h>  
#include <stdbool.h> 
#include <assert.h>  
#include <string.h>   
#include <errno.h>  
#include <math.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include "./nDPI/src/include/ndpi_api.h"

extern int ndpi_predict_linear(u_int32_t *values, u_int32_t num_values,
			       u_int32_t predict_period, u_int32_t *predicted_value,
			       float *c, float *m);

void testToolDisco() {
  u_int32_t mem[10];
  char *filename = "toolDisk.c";
  unsigned long disk_size, used, free;
  struct statvfs buf;
  printf("Collecting data every 10 seconds...\n");
  for(int i = 0; i < 10; i++){
    if (!statvfs(filename, &buf)) {
      disk_size = buf.f_blocks * buf.f_bsize;
      free = buf.f_bfree * buf.f_bsize;
      used = disk_size - free;
      mem[i] = used;
    } else {
      printf("Couldn't get file system statistics\n");
      exit(1);
    }
    printf("Istant: %d, Busy disk: %d KB\n", i, mem[i]);
    sleep(10);
  }
		

  u_int32_t predicted_value;
  float c, m;
  int ret_val;
  ret_val = ndpi_predict_linear(mem, 10, 6, &predicted_value, &c, &m);

  if(ret_val == 0){
    printf("Computation OK\n");
  }else{
    printf("Error in computation\n");
  }

  printf("The y-intercept is: %f\n", c);
  printf("The slope is: %f\n", m);
  printf("The predicted value is: %d\n", predicted_value);
}

int main(int argc, char *argv[]){
  testToolDisco();
  return 0;
}
