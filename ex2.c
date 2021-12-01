#include <stdio.h>

int my_getchar();

int main(){
    puts("Ex2");
    int c;
    while((c = my_getchar()) != EOF){
        printf("%c", c);
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