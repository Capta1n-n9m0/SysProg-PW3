#include <stdio.h>

#define BUFFER_SIZE 2

// FILE *debug;
// void start_debug() __attribute__((constructor));
// void stop_debug() __attribute__((destructor));
// void start_debug(){
//     debug = fopen("debug.txt", "w");
// }
// void stop_debug(){
//     fclose(debug);
// }
//

int my_getchar_b();

int main(){
    puts("Ex3");
    int c = my_getchar_b();
    while(c != '-'){
        printf("%c", c);
        c = my_getchar_b();
    }
    return 0;
}
int my_getchar(){
    // lol, i can use getch here, can't i? :D
    char buf;
    fread(&buf, sizeof(char), 1, stdin);
    if(buf == 0) return EOF;
    return (int)buf;
}

int my_getchar_b(){
    // i dislike this version so much, because
    //  it has small buffer
    //  it works only when buffer can be read
    // i could've done it properly, but there is little time
    static char buf[BUFFER_SIZE] = {0};
    static int cursor = BUFFER_SIZE;
    if(cursor == BUFFER_SIZE){
        fread(buf, sizeof(char ), BUFFER_SIZE, stdin);
        cursor = 0;
    }
    //fprintf(debug, "%d %d:%c\n", cursor, buf[cursor], buf[cursor]);
    return (int)buf[cursor++];
}