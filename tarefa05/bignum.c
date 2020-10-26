#ifndef _BIGNUM_H
#define _BIGNUM_H

#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BigNum bignum_create(char str[]) {
    BigNum num = NULL;

    int size = strlen(str);
    for(int i = 0; i < size; i++) {
        num = bignum_push(num, str[i] - '0');
    }

    return num;
}

void bignum_destroy(BigNum num) {
    if(num != NULL) {
        bignum_destroy(num->next);
        free(num);
    }
}

BigNum bignum_push(BigNum num, int data) {
    BigNum newPoint = malloc(sizeof(BigNumNode));
    if(newPoint == NULL) {
        printf("Erro! Não há memória disponível!\n");
        exit(0);
    }
    
    newPoint->data = data;
    newPoint->next = num;
    return newPoint;
}

void bignum_compile(BigNum num, char str[]) {
    if(num == NULL) return;
    num = bignum_rev(num);
    BigNum first = num;

    int left = 0, cur = 0;
    char convert[5] = "", res[50] = "";
    while(num != NULL) {
        int data = num->data + left;

        sprintf(convert, "%d", data);

        if(data >= 10) {
            int last = strlen(convert) - 1;
            res[cur] = convert[last];
            convert[last] = '\000';
            left = strtol(convert, NULL, 10);
        } else {
            left = 0;
            res[cur] = convert[0];
        }

        cur++;
       
        num = num->next;
    }

    if(left > 0) {
        res[cur] = (char)(left + '0');
        cur++;
    }

    int i = 0;
    while(cur >= 0) {
        cur--;
        str[i] = res[cur];
        i++;
    }

    bignum_destroy(first);

    if(i > 0) {
        int len = i;

        int lZeros = 0;
        while(str[lZeros] == '0') {
            lZeros++;
        }

        for(i = 0; i < len; i++) {
            str[i] = str[i + lZeros];
        }

        while(lZeros > 0) {
            i--;
            str[i] = 0x0;
            lZeros--;
        }

        if(strlen(str) == 0) {
            str[0] = '0';
        }
    }
}

short int bignum_cmp(BigNum a, BigNum b) {
    int cmp = 0;

    while(a != NULL && b != NULL) {
        if(a->data > b->data) cmp = 1;
        if(a->data < b->data) cmp = -1;

        a = a->next;
        b = b->next;

        if(a == NULL) {
            if(b == NULL) return cmp;
            return -1;
        }

        if(b == NULL) return 1;
    }

    return cmp;
}

BigNum bignum_rev(BigNum num) {
    if(num == NULL) return NULL;

    BigNum rev = NULL;
    BigNum cur = num;
    while(cur->next != NULL) {
        rev = bignum_push(rev, cur->data);
        cur = cur->next;
    }

    rev = bignum_push(rev, cur->data);
    bignum_destroy(num);
    return rev;
}

#endif