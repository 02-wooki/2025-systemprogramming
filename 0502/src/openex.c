#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
  int f;
  if ((f = open(argv[1], O_RDWR)) == -1)
    printf("파일 열기 오류\n");
  else
    printf("파일 %s 열기 성공 : %d\n", argv[1], f);

  close(f);
  exit(0);
} 