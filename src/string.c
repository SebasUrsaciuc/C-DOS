#include "string.h"

bool str_equ(const char* str1, const char* str2) {
    str_sz i = 0;

    while(true) {
        if(str1[i] != str2[i])
            return false;

        if(str1[i] == 0)
            break;

        i++;
    }

    return true;
}

bool str_eqi(const char* str1, const char* str2) {
    str_sz i = 0;

    while(true) {
        if(str_charUp(str1[i]) != str_charUp(str2[i]))
            return false;

        if(str1[i] == 0)
            break;

        i++;
    }

    return true;
}

void str_cat(char* dest, const char* src) {
    str_sz sz = str_len(dest);
    str_sz osz = str_len(src);

    for(str_sz i = 0; i < osz; i++) {
        dest[sz + i] = src[i];
    }

    dest[sz + osz] = 0;
}

uint str_len(const char* str) {
    str_sz sz = 0;

    while(str[sz] != 0)
        sz++;

    return sz;
}

void str_clear(char* str) {
    str[0] = 0;
}

void str_copy(char* dest, const char* src) {
    for(str_sz i = 0; src[i] != 0; i++) {
        dest[i] = src[i];
    }
}

void str_fromInt(int v, char* buf) {
    uint32 uv = v < 0? v * -1 : v;
    uint32 tmp = uv;
    str_sz i = 0;

    if(v < 0) {
        buf[i] = '-';
        i++;
    }

    while(tmp != 0) {
        i++;
        tmp /= 10;
    }

    if(i == 0) {
        i++;
    }

    buf[i] = 0;

    do {
        i--;

        buf[i] = 48 + (uv % 10);
        
        uv /= 10;
    } while(uv != 0);
}

void str_fromHex(int x, char* buf) {    
    uint32 uv = (uint32) x;
    uint32 tmp = uv;
    str_sz i = 0;

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

int str_toInt(const char* a) {
    int result = 0;
    int8 or = 1;

    str_sz i = 0;

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