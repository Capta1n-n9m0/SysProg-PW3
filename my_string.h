#pragma once

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define BASE_STRING_LEN 8

typedef struct{
    uint32_t len;
    uint32_t cap;
    char *chars;
}string;

string create_string(char *s);
void free_string(string *s);

void append_char_to_string(string *s, char c);
void append_string_to_string(string *to, string *from);
void append_cstring_to_string(string *to, char *from);

string read_string_line(FILE *stream);


typedef struct{
    uint32_t len;
    string *strings;
}string_array;


string_array read_string_array(FILE *stream);

void print_string_array(string_array s);

void free_string_array(string_array *s);
void append_string_to_string_array(string_array *array, string s);
string_array create_empty_string_array();

