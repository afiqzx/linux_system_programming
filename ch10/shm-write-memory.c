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

  const float numbers[3] = {3.13, 2.718, 1.202};

  if((fd = shm_open(memid, O_RDWR | O_CREAT, 0600)) == -1) {
      perror("Cannot open memory fd");
      return 1;
  }


  /* truncate memory to DATASIZE */
  if((ftruncate(fd, DATASIZE)) == -1) {
      perror("Cannot truncate memory");
      return 1;
  }

  /* map using file descriptor */
  addr = mmap(NULL, DATASIZE, PROT_WRITE, MAP_SHARED, fd, 0);
  if(addr == MAP_FAILED) {
      perror("Failed to map memory");
      return 1;
  }

  /* copy data to memory */
  memcpy(addr, numbers, sizeof(numbers));

  /* wait for enter */
  printf("Hit enter when finished");
  getchar();

  /* clean up */
  munmap(addr, DATASIZE);
  shm_unlink(memid);


  return 0;
}
