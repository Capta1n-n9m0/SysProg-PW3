#include "my_string.h"
string create_string(char *s){
    string res={0};
    if(s == NULL) return res;
    uint32_t len = ((strlen(s) / 8) + 1) * BASE_STRING_LEN;
    res.len = strlen(s);
    res.cap = len;
    res.chars = (char *)calloc(len, sizeof(char));
    for(int i = 0; i < strlen(s); i++){
        res.chars[i] = s[i];
    }
    append_char_to_string(&res, '\0');
    return res;
}
void free_string(string *s){
    s->cap = 0;
    s->len = 0;
    free(s->chars);
}

void append_char_to_string(string *s, char c){
    if(s->len < s->cap){
        if(c=='\0'){
            s->chars[s->len] = c;
        }
        else{
            s->chars[s->len++] = c;
        }
    }
    else{
        if(c=='\0'){
            s->cap += BASE_STRING_LEN;
            s->chars = (char *)realloc(s->chars, s->cap);
            s->chars[s->len] = c;
        }
        else {
            s->cap += BASE_STRING_LEN;
            s->chars = realloc(s->chars, s->cap);
            s->chars[s->len++] = c;
        }
    }
}
void append_string_to_string(string *to, string *from){
    for(int i = 0; i < from->len; i++){
        append_char_to_string(to, from->chars[i]);
    }
    append_char_to_string(to, '\0');
}
void append_cstring_to_string(string *to, char *from){
    for(int i = 0; i < strlen(from); i++){
        append_char_to_string(to, from[i]);
    }
    append_char_to_string(to, '\0');
}

string read_string_line(FILE *stream){
    string res = create_string("");
    char c;
    while ( (c = getc(stream)) != '\n')
    {
        append_char_to_string(&res, c);
        if(c == EOF) break;
    }
    append_char_to_string(&res, '\0');
    return res;
}

string_array read_string_array(FILE *stream){
    string_array res;
    res.len = 0;
    res.strings = (string *)calloc(1, sizeof(string));
    while(1){

        res.strings[res.len++] = read_string_line(stream);
        res.strings = (string *)realloc(res.strings, (res.len+1)*sizeof(string));
        if(stream == stdin){
            if(res.strings[res.len-1].len == 0) break;
        }
        else{
            if(res.strings[res.len-1].chars[0] == EOF) break;
        }
    }
    res.len--;
    free_string(&res.strings[res.len]);
    return res;
}

void print_string_array(string_array s){
    for(int i = 0; i < s.len; i++){
        puts(s.strings[i].chars);
    }
}

void free_string_array(string_array *s){
    for(int i = 0; i < s->len; i++){
        free_string(&(s->strings[i]));
    }
    free(s->strings);
    s->len = 0;
}

void append_string_to_string_array(string_array *array, string s){
    array->strings[array->len++] = s;
    array->strings = (string *) realloc(array->strings, (array->len+1) * sizeof (string));
    if(array->strings == NULL){
        fprintf(stderr, "Realloc failed. Check available memory.\n");
        exit(1);
    }
}

string_array create_empty_string_array(){
    string_array res = {0};
    res.strings = (string *) calloc(1, sizeof (string));
    if(res.strings == NULL){
        fprintf(stdin, "Could allocate memory for one string\n");
        exit(1);
    }
    res.len = 0;
    return res;
}
