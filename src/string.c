#include "string.h"

bool strequ(const char* str1, const char* str2) {
    strsz i = 0;

    while(true) {
        if(str1[i] != str2[i])
            return false;

        if(str1[i] == 0)
            break;

        i++;
    }

    return true;
}

bool streqi(const char* str1, const char* str2) {
    strsz i = 0;

    while(true) {
        if(charup(str1[i]) != charup(str2[i]))
            return false;

        if(str1[i] == 0)
            break;

        i++;
    }

    return true;
}

void strcat(char* dest, const char* src) {
    strsz sz = strlen(dest);
    strsz osz = strlen(src);

    for(strsz i = 0; i < osz; i++) {
        dest[sz + i] = src[i];
    }

    dest[sz + osz] = 0;
}

uint strlen(const char* str) {
    strsz sz = 0;

    while(str[sz] != 0)
        sz++;

    return sz;
}

void strclr(char* str) {
    str[0] = 0;
}

void strcpy(char* dest, const char* src) {
    for(strsz i = 0; src[i] != 0; i++) {
        dest[i] = src[i];
    }
}

void itos(int v, char* buf) {
    uint32 uv = v < 0? v * -1 : v;
    uint32 tmp = uv;
    strsz i = 0;

    if(v < 0) {
        buf[i] = '-';
        i++;
    }

    while(tmp != 0) {
        i++;
        tmp /= 10;
    }

    if(i == 0)
        i++;

    buf[i] = 0;

    do {
        i--;

        buf[i] = 48 + (uv % 10);
        
        uv /= 10;
    } while(uv != 0);
}

void xtos(int x, char* buf) {    
    uint32 uv = (uint32) x;
    uint32 tmp = uv;
    strsz i = 0;

    do {
        i++;
        tmp /= 16;
    } while(tmp != 0);

    if(i == 0)
        i++;

    buf[i] = 0;

    do {
        i--;

        char ch = uv % 16;
        buf[i] = (ch > 9? 55 : 48) + ch;
        
        uv /= 16;
    } while(uv != 0);
}

int stoi(const char* a) {
    int result = 0;
    int8 or = 1;

    strsz i = 0;

    if(a[i] == '-') {
        or *= -1;
        i++;
    }

    while(a[i] != 0) {
        int chn = a[i] - 48;

        if(chn > 9) {
            return result;
        }

        result = result * 10 + chn;

        i++;
    }

    return result * or;
}

char charup(char ch) {
    return ch >= 65 && ch <= 91? ch + 0x20 : ch;
}

char charlow(char ch) {
    return ch >= 97 && ch <= 123? ch - 0x20 : ch;
}