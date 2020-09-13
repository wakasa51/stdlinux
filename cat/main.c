#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]) {
  int i;
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }

  /* テキストにはないが、コマンドライン引数を受け取るようにしてみる */
  int separate_with_file_name;
  int opt;
  while ((opt = getopt(argc, argv, "s")) != -1) {
    switch (opt) {
      case 's':
        separate_with_file_name = 1;
        break;
      default:
        printf("error! \'%c\' \'%c\'\n", opt, optopt);
        return 1;
    }
  }
  for (i = optind; i < argc; i++) {
    if (separate_with_file_name) printf("\n----------%s----------\n\n", argv[i]);
    do_cat(argv[i]);
    if (separate_with_file_name) printf("\n----------%s----------\n\n", argv[i]);
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const char *path) {
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int n;

  fd = open(path, O_RDONLY);
  if (fd < 0) die(path);
  for(;;) {
    n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fd) < 0) die(path);
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
