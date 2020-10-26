typedef struct BigNumNode {
    int data;
    struct BigNumNode *next;
} BigNumNode;

typedef struct BigNumNode * BigNum;

BigNum bignum_create(char str[]);
void bignum_destroy(BigNum list);

BigNum bignum_push(BigNum num, int value);

void bignum_compile(BigNum num, char str[]);

BigNum bignum_rev(BigNum num);
short int bignum_cmp(BigNum a, BigNum b);