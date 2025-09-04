#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

#define DATASIZE 128

int main(void) {
  int fd;
  float *addr;
  const char memid[] = "/my_memory";

  const float numbers[3];

  if((fd = shm_open(memid, O_RDONLY, 0600)) == -1) {
      perror("Cannot open memory fd");
      return 1;
  }


  /* map using file descriptor */
  addr = mmap(NULL, DATASIZE, PROT_READ, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED) {
      perror("Failed to map memory");
      return 1;
  }

  /* copy data to memory */
  memcpy((float*)numbers, addr, sizeof(numbers));

  for(int i = 0; i < 3; i++) {
      printf("Number %d: %.3f\n", i, numbers[i]);
  }

  return 0;
}
