#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_string.h"
#include <errno.h>
#include <ctype.h>
#include <getopt.h>

#ifdef _WIN32
#include <windows.h>
#endif


void interpret_errno();
int create_copy(string in, string out, int verbosity);

int main(int argc, char **argv){
    puts("Running Ex1.");
    puts("Here i will copy one file into another.");
    puts("If no arguments provided input is assumed to be foo and output bar");
    char possible_args[] = "i:o:hv";
    int verbosity = 0, c, i_flag = 0, o_flag = 0;
    string input = {0}, output = {0};
    string_array inputs = create_empty_string_array(), outputs = create_empty_string_array();
    while ( (c = getopt(argc, argv, possible_args)) != -1){
        switch (c) {
            case 'i':
                i_flag++;
                input = create_string(optarg);
                append_string_to_string_array(&inputs, input);
                break;
            case 'o':
                o_flag++;
                output = create_string(optarg);
                append_string_to_string_array(&outputs, output);
                break;
            case 'h':
                puts("Here i print help.");
                /*
                 * TODO: Create help page
                 */
                break;
            case 'v':
                verbosity++;
                break;
            case '?':
                /*
                 * TODO: Finish up argument management
                 * https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
                 */
                if (isprint (optopt)) {
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                }
                else {
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                }
                break;
            default:
                free_string_array(&inputs);
                free_string_array(&outputs);
                puts("exiting");
                abort();
        }
    }
    if(i_flag == 0 && o_flag == 0){
        input = create_string("foo");
        output = create_string("bar");
        append_string_to_string_array(&inputs, input);
        append_string_to_string_array(&outputs, output);
    }
    if(o_flag > i_flag){
        printf("[ WARNING ] There are more output files(%d), than input files(%d). ", o_flag, i_flag);
        printf("Leftover output will be omitted.\n");
    }
    if(i_flag > o_flag){
        printf("[   INFO  ] There are more input files(%d) that output files(%d). ", i_flag, o_flag);
        printf("All unspecified outputs will be completed to $file.copy\n");
        for(int i = o_flag; i < i_flag; i++){
            output = create_string(inputs.strings[i].chars);
            append_cstring_to_string(&output, ".copy");
            append_string_to_string_array(&outputs, output);
        }
    }
    for(int i = 0; i < i_flag; i++){
        if(create_copy(inputs.strings[i], outputs.strings[i], verbosity) != 0){
            fprintf(stderr, "Failed to copy %s to %s\n", inputs.strings[i].chars, outputs.strings[i].chars);
        }
    }
    return 0;
    return create_copy(input, output, verbosity);
}

void interpret_errno(){
    int err = errno;
    fprintf(stderr, "Errno: %d\n", err);
    perror("Errno meaning");
}
int create_copy(string in, string out, int verbosity){
    if(verbosity > 0){
        printf("Copying %s to %s\n", in.chars, out.chars);
    }
    struct stat in_stat = {0};
    if(stat(in.chars, &in_stat) == -1){
        fprintf(stderr, "Calling stat on %s was unsuccessful.\n", in.chars);
        fprintf(stderr, "Check if file exists or file permissions.\n");
        interpret_errno();
        return 1;
    }
    long size = in_stat.st_size;
    if(verbosity > 1){
        printf("Size of %s is %ld bytes. Allocating %ld bytes for copying.\n", in.chars, size, size);
    }
    char *buf = (char *) calloc(size, 1);
    if(buf == NULL){
        fprintf(stderr, "Could not allocate %ld bytes for copying\n", size);
        fprintf(stderr, "For now i am trying to do all in one chunk. Latter i will copy in blocks.\n");
        interpret_errno();
        return 2;
    }
    int in_file = open(in.chars, O_RDONLY);
    if(in_file == -1){
        fprintf(stderr, "Could not open %s for read.\n", in.chars);
        fprintf(stderr, "Check if file exists or file permissions.\n");
        interpret_errno();
        return 1;
    }
    if(verbosity > 1){
        printf("Opened %s for read.\n", in.chars);
    }
    size_t bytes_read = read(in_file, buf, size);
    if(bytes_read != size){
        fprintf(stderr, "Couldn't read file %s all at once.\n", in.chars);
        fprintf(stderr, "Read %ld out of %ld.\n", bytes_read, size);
        fprintf(stderr, "Check file name, permissions or size.\n");
        interpret_errno();
        return 3;
    }
    if(verbosity > 1){
        printf("Read %ld bytes of file %s.\n", bytes_read, in.chars);
    }
    int out_file = open(out.chars, O_WRONLY | O_CREAT | O_TRUNC, 0642);
    if(out_file == -1){
        fprintf(stderr, "Could not open for write or create file %s\n", out.chars);
        fprintf(stderr, "Check permissions or available disk space.\n");
        interpret_errno();
        return 4;
    }
    if(verbosity > 1){
        printf("Opened %s for write.\n", out.chars);
    }
    size_t bytes_writen = write(out_file, buf, size);
    if(bytes_writen != size){
        if(bytes_read == -1){
            fprintf(stderr, "Error on writing %ld bytes to %s\n", bytes_writen, out.chars);
            fprintf(stderr, "Code is -1, so error looks fatal.\n");
            interpret_errno();
            return 5;
        }
        else{
            fprintf(stderr, "Retrying write of %s\n",out.chars);
            fprintf(stderr, "Not implemented\n");
            /* TODO: implement retying of file write
             */
            return 5;
        }
    }
    if(verbosity > 1){
        printf("Wrote %ld bytes out of %ld to %s\n", bytes_writen, size, out.chars);
    }
    close(in_file);
    close(out_file);
    free(buf);
    if(verbosity > 1){
        printf("Successfully copied %s to %s\n", in.chars, out.chars);
    }
    return 0;
}

