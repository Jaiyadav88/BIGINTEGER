#ifndef BigInteger_h
#define BigInteger_h
 struct node {
    int data;
    struct node* next;
};
typedef struct biginteger {
    struct node* head;
    char sign;
    long int size;
}BIGINT;
 BIGINT initialize(char *);
 void display(BIGINT);
 void inserthead(BIGINT*,int);
 void displayreverse(struct node *);
 BIGINT add(BIGINT,BIGINT);
 BIGINT  sub(BIGINT,BIGINT);
 BIGINT mul(BIGINT,BIGINT);
 BIGINT div1(BIGINT,BIGINT);
 BIGINT mod(BIGINT,BIGINT);
 int length(struct node *);
 struct node* copyLinkedList(struct node*);
 int compare(BIGINT,BIGINT);
 void inserttail(BIGINT *,int);
 int cmp(BIGINT num1,BIGINT num2);
 struct node *createNode(int);
 struct node * reverse(struct node *);
#endif
