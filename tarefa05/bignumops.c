#ifndef _BIGNUMOPS_H
#define _BIGNUMOPS_H

#include "bignumops.h"

#include <stdlib.h>

BigNum bignumops_add(BigNum a, BigNum b) {
    BigNum res = NULL;

    while(a != NULL || b != NULL) {
        int aData = 0, bData = 0;

        if(a != NULL) {
            aData = a->data;
            a = a->next;
        }

        if(b != NULL) {
            bData = b->data;
            b = b->next;
        }

        res = bignum_push(res, aData + bData);
    }

    bignum_destroy(a);
    bignum_destroy(b);

    return res;
}

BigNum bignumops_sub(BigNum a, BigNum b) {
    BigNum res = NULL, big, small;
    short int comp = bignum_cmp(a, b);

    if(comp == 0) {
        res = bignum_push(res, 0);
        return res;
    } else {
        if(comp == 1) {
            big = a;
            small = b;
        } else {
            big = b;
            small = a;
        }
    }

    while(big != NULL || small != NULL) {
        int bigData = 0, smallData = 0;

        if(big != NULL) {
            bigData = big->data;
            big = big->next;
        }

        if(small != NULL) {
            smallData = small->data;
            small = small->next;
        }

        res = bignum_push(res, bigData - smallData);
    }

    res = bignum_rev(res);

    BigNum final = NULL;
    BigNum first = res;

    while(res != NULL) {
        int data = res->data;
        if(data < 0) {
            data += 10;
            res->next->data--;
        }
        final = bignum_push(final, data);

        res = res->next;
    }

    bignum_destroy(first);
    bignum_destroy(a);
    bignum_destroy(b);

    return final;
}

BigNum bignumops_mul(BigNum a, BigNum b) {
    BigNum res = NULL, big, small;
    short int comp = bignum_cmp(a, b);

    if(comp != -1) {
        big = a;
        small = b;
    } else {
        big = b;
        small = a;
    }

    int smallSize = 0;
    BigNum n = small;
    while(n != NULL) {
        smallSize++;
        n = n->next;
    }

    small = bignum_rev(small);
    BigNum bigStep = big;

    int x = smallSize - 1, xS = 0;
    while(bigStep != NULL) {
        BigNum s = small;
        BigNum b = bigStep;

        if(x >= 0) {
            for(xS = 0; xS < x; xS++) {
                s = s->next;
            }
            x--;
        }

        int r = 0;

        while(s != NULL && b != NULL) {
            r += s->data * b->data;
            s = s->next;
            b = b->next;
        }

        if(x < 0) {
            bigStep = bigStep->next;
        }

        res = bignum_push(res, r);
    }

    bignum_destroy(big);
    bignum_destroy(small);
    
    return res;
}

#endif