#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char in_file[] = "foo";
const char out_file[]= "bar";

int main(int argc, char **argv){
    struct stat in = {0};
    int res = stat(in_file, &in);
    char *buf = (char *)calloc(in.st_size, 1);
    int foo = open(in_file, O_RDONLY);
    int n = read(foo, buf, in.st_size);
    int bar = open(out_file, O_CREAT | O_WRONLY, 0642);
    write(bar, buf, n);
    free(buf);
    close(foo);
    close(bar);
    return res;
}