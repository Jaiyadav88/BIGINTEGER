#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"
BIGINT initialize(char *str)
{   int i=0;
    BIGINT res;
    res.head=NULL;
    res.sign='+';
    res.size=0;
    if(str[0]=='-')
    {
        res.sign='-';
        i++;
    }
    else
    {
        res.sign='+';
    }
    int k=1;
    while(str[i]!='\0')
    {   
        
        inserthead(&res,str[i]-'0');
        i++;
        res.size+=1;
    }
    return res;
}
void inserthead(BIGINT *res ,int data)
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    if(res->head==NULL)
    {
        res->head=temp;
        return;
    }
    temp->next=res->head;
    res->head=temp;
}
void display(BIGINT a)
{
    if(a.sign=='-')
     printf("-");
    if(a.head==NULL)
    {
        printf("0");
        return;
    }
    displayreverse(a.head);
    printf("\n");
}
void displayreverse(struct node *head)
{
    if(head==NULL)
     return;
    displayreverse(head->next);
    printf("%d",head->data);
}
BIGINT add(BIGINT num1,BIGINT num2)
{
    BIGINT res;
    res.head = NULL;
    res.sign = '+';
    res.size = 0;

    if (num1.sign == '-' && num2.sign == '+')
    {
        num1.sign = '+';
        return sub(num2, num1);
    }
    else if (num1.sign == '+' && num2.sign == '-')
    {
        num2.sign = '+';
        return sub(num1, num2);
    }
    else if (num1.sign == '-' && num2.sign == '-')
    {
        num1.sign = '+';
        num2.sign = '+';
        res = add(num1, num2);
        res.sign = '-';
        return res;
    }
    else
    {
        struct node *temp1=num1.head;
        struct node *temp2=num2.head;
        int carry=0;
        while(temp1!=NULL&&temp2!=NULL)
        {
            int sum=temp1->data+temp2->data+carry;
            carry=sum/10;
            sum=sum%10;
            inserthead(&res,sum);
            temp1=temp1->next;
            temp2=temp2->next;
        }
        while(temp1!=NULL)
        {
            int sum=temp1->data+carry;
            carry=sum/10;
            sum=sum%10;
            inserthead(&res,sum);
            temp1=temp1->next;
        }
        while(temp2!=NULL)
        {
            int sum=temp2->data+carry;
            carry=sum/10;
            sum=sum%10;
            inserthead(&res,sum);
            temp2=temp2->next;
        }
        if(carry!=0)
        {
            inserthead(&res,carry);
        }
    }
    res.head=reverse(res.head);
    return res;
}
struct node* reverse(struct node *head)
{
    struct node *prev=NULL;
    struct node *curr=head;
    struct node *next=NULL;
    while(curr!=NULL)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    head=prev;
    return head;
}
BIGINT sub(BIGINT num1, BIGINT num2) {
    struct node* l1 = num1.head;
    struct node* l2 = num2.head;
    BIGINT num3;
    num3.head = NULL;
    num3.sign = '+';
    num3.size = 0;
    if (num1.sign == '+' && num2.sign == '-') {
        num2.sign = '+';
        num3 = add(num1, num2);
        num2.sign = '-';
        num3.sign = '+';
        return num3;
    } else if (num1.sign == '-' && num2.sign == '+') {
        num1.sign = '+';
        num3 = add(num2, num1);
        num1.sign = '-';
        num3.sign = '-';
        return num3;
    }
    if(num1.sign=='-'&&num2.sign=='-')
    {
        num1.sign='+';
        num2.sign='+';
        num3=sub(num2,num1);
        num1.head=reverse(num1.head);
        num2.head=reverse(num2.head);
        if(compare(num1,num2)==1)
        {
            num3.sign='-';
        }
        else
        {
            num3.sign='+';
        }
        num1.head=reverse(num1.head);
        num2.head=reverse(num2.head);
        return num3;
    }
    num1.head=reverse(num1.head);
    num2.head=reverse(num2.head);
    if (compare(num1,num2)==-1) {
        struct node* temp = l1;
        l1 = l2;
        l2 = temp;
        num3.sign = '-';
    }
    num1.head=reverse(num1.head);
    num2.head=reverse(num2.head);
    int sub = 0;
    int borrow = 0;
    while (l1 != NULL && l2 != NULL) {
        sub = l1->data - l2->data + borrow;
        if (sub < 0) {
            borrow = -1;
            sub = sub + 10;
        } else {
            borrow = 0;
        }
        inserttail(&num3, sub);
        l1 = l1->next;
        l2 = l2->next;
    }
    while (l1 != NULL) {
        sub = l1->data + borrow;
        if(sub<0)
        {
            borrow=-1;
            sub=sub+10;
        }
        else
        {
            borrow=0;
        }
        inserttail(&num3, sub);
        l1 = l1->next;
    }
    num3.head=reverse(num3.head);
    while(num3.head->data==0&&num3.size>1)
    {
        num3.head=num3.head->next;
        num3.size-=1;
    }
    num3.head=reverse(num3.head);
    return num3;
}
int compare(BIGINT num1,BIGINT num2)
{   
    if(length(num1.head)>length(num2.head))
    {
        return 1;
    }
    else if(length(num1.head)<length(num2.head))
    {
        return -1;
    }
    else
    {
        struct node *temp1=num1.head;
        struct node *temp2=num2.head;
        while(temp1!=NULL&&temp2!=NULL)
        {
            if(temp1->data>temp2->data)
            {
                return 1;
            }
            else if(temp1->data<temp2->data)
            {
                return -1;
            }
            temp1=temp1->next;
            temp2=temp2->next;
        }
        return 0;
    }
}
void inserttail(BIGINT *num,int element)
{
    struct node *temp=(struct node*)malloc(sizeof(struct node));
    if(temp==NULL)
    {
        printf("memory allocation failed\n");
        return;
    }
    temp->data=element;
    temp->next=NULL;
    num->size+=1;
    if(num->head==NULL)
    {
        num->head=temp;
        return;
    }
    struct node *itr=num->head;
    while(itr->next!=NULL)
    {
        itr=itr->next;
    }
    itr->next=temp;    
}
BIGINT mul(BIGINT n1, BIGINT n2) {
    
    struct node* num1 = n1.head;
    struct node* num2 = n2.head;
    if (num1 == NULL || num2 == NULL) {
        BIGINT result;
        result.head = NULL;
        result.sign = '+';
        result.size = 0;
        return result;
    }
    BIGINT result,mid;
    result.head = NULL;
    result.sign = '+';
    result.size = 0;
    int carry = 0, product = 0, i = 0;
    while (num2 != NULL) {
        struct node* num1 = n1.head;
        carry = 0;
        mid.head = NULL;
        mid.sign = '+';
        mid.size = 0;
        for (int j = 0; j < i; j++) {
            inserttail(&mid, 0);
        }
        while (num1 != NULL) {
            product = (num1->data) * (num2->data) + carry;
            inserttail(&mid, product % 10);
            carry = product / 10;
            num1 = num1->next;
        }
        if (carry > 0) {
            inserttail(&mid, carry);
        }
        result = add(mid, result);
        struct node* current = mid.head;
        while (current != NULL) {
            struct node* next = current->next;
            free(current);
            current = next;
        }
        num2 = num2->next;
        i++;
    }
    if (n1.sign != n2.sign) {
        result.sign = '-';
    }
    return result;
}
BIGINT div1(BIGINT num1, BIGINT num2) {
    BIGINT res;
    res.head=NULL;
    res.sign='+';
    res.size=0;
    if (num2.head==NULL) {
        printf("Division by zero error\n");
        return res;
    }
    if (num1.head == NULL) {
        return res;
    }
    if (cmp(num1, num2) == -1) {
        return res;
    }
    //Code to perform division of two big integers
    BIGINT temp = num1;
    BIGINT quotient;
    quotient.head = NULL;
    quotient.sign = '+';
    quotient.size = 0;
    while (cmp(temp, num2) >= 0) {
        temp = sub(temp, num2);
        quotient = add(quotient, initialize("1"));
    }
    return quotient;
}
BIGINT mod(BIGINT num1,BIGINT num2)
{
    //modulos of number
    BIGINT res;
    res.head = NULL;
    res.sign = '+';
    res.size = 0;
    if (num2.head == NULL) {
        printf("Division by zero error\n");
        return res;
    }
    if (num1.head == NULL) {
        return res;
    }
    if (cmp(num1, num2) == -1) {
        return res;
    }
    // Perform division of two big integers by repeated addition
    BIGINT temp = num1;
    while (cmp(temp, num2) >= 0) {
        temp = sub(temp, num2);
    }
    return temp;
}
struct node *createNode(int data)
{
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}
int length(struct node *head)
{
    int count=0;
    while(head!=NULL)
    {
        count++;
        head=head->next;
    }
    return count;
}
int cmp(BIGINT num1,BIGINT num2)
{   num1.head=reverse(copyLinkedList(num1.head));
    num2.head=reverse(copyLinkedList(num2.head));
    if(length(num1.head)>length(num2.head))
    {
        return 1;
    }
    else if(length(num1.head)<length(num2.head))
    {
        return -1;
    }
    else
    {
        struct node *temp1=num1.head;
        struct node *temp2=num2.head;
        while(temp1!=NULL&&temp2!=NULL)
        {
            if(temp1->data>temp2->data)
            {
                return 1;
            }
            else if(temp1->data<temp2->data)
            {
                return -1;
            }
            temp1=temp1->next;
            temp2=temp2->next;
        }
        return 0;
    }
}
struct node* copyLinkedList(struct node* head) {
    struct node* newHead = NULL;
    struct node* newTail = NULL;
    while (head != NULL) {
        struct node* newNode = createNode(head->data);
        if (newHead == NULL) {
            newHead = newNode;
            newTail = newNode;
        } else {
            newTail->next = newNode;
            newTail = newNode;
        }
        head = head->next;
    }
    return newHead;
}


