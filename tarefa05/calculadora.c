#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignumops.h"

int main() {
    int n, i;

    scanf("%d ", &n);

    for(i = 0; i < n; i++) {
        char op;
        char aS[25] = "", bS[25] = "";

        scanf(" %c ", &op);
        scanf(" %s %s", aS, bS);

        BigNum a = bignum_create(aS);
        BigNum b = bignum_create(bS);
        BigNum numRes;

        if(op == '+') {
            numRes = bignumops_add(a, b);
        } else if (op == '-') {
            numRes = bignumops_sub(a, b);
        } else if(op == '*') {
            numRes = bignumops_mul(a, b);
        } else {
            return 0;
        }

        char res[50] = "";
        bignum_compile(numRes, res);
        printf("%s\n", res);
    }

    return 0;
}