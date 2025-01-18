#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef struct poly
{
    int coef;
    int exp;
    struct poly* next;
}LNode,*Linklist;

Linklist readPolynomial(const char* filename);
Linklist com_Poly(Linklist p_head,Linklist q_head,char ope);
void showall(Linklist head);
float addpoly(Linklist head,float x);
Linklist Poly_Multi(Linklist p_head,Linklist q_head);
Linklist Poly_Sub(Linklist p_head,Linklist q_head);
Linklist Poly_Puls(Linklist p_head,Linklist q_head);
Linklist derivative_base(Linklist head);
Linklist initlist();
Linklist bubbleSortList(Linklist head);
void derivative(Linklist head);
void com_derivative();
LNode* Attch(int coef,int exp,LNode* p);
void TwoPoly_com(char ope);
void writePolynomial(Linklist head, const char* filename);
void Delete_Link(Linklist head);

int main()
{
    Linklist New_head,p_head,q_head;
    char ope;
    float num;
    printf("Please input operator(+/-/*/d)(���У�dΪ�����㣩:");
    scanf("%c",&ope);
    getchar();//�����س�����
    if (ope=='d')
    {
        com_derivative();
    }
    else if(ope=='+'||ope=='-'||ope=='*')
    {
        TwoPoly_com(ope);
    }
    else
    {
        printf("Input Error!\n");
        exit(1);
    }
    printf("The linked list has been cleared.");

}
//��ʼ������
Linklist initlist()
{
    Linklist L;
    L = (LNode*)malloc(sizeof(LNode));
    if(L==NULL)
    {
        return NULL;
    }
    else
    {
        L->next = NULL;
        L->exp = -1;
        L->coef = -1;
    }
    return L;
}
//���ӽڵ�
LNode* Attch(int coef,int exp,LNode* p)
{
    LNode *c = (LNode*)malloc(sizeof(LNode));
    c->coef = coef;
    c->exp = exp;
    c->next = NULL;
    if (p==NULL)
    {
        p = c;
    }
    else
    {
        p->next = c;
    }

    return c;
}
//ð������
Linklist bubbleSortList(Linklist head)
{
    Linklist Head = head->next;
    Linklist swapped;
    Linklist p = head->next;

    do
    {
        swapped = NULL;
        p = Head;
        while (p!=NULL&&p->next!=NULL)
        {
               if(p->exp<p->next->exp)
              {
                int temp;
                temp = p->exp;
                p->exp = p->next->exp;
                p->next->exp = temp;
                swapped = p;
                temp = p->coef;
                p->coef = p->next->coef;
                p->next->coef = temp;
                swapped = p;

              }
             p = p->next;

        }
    }while(swapped!=NULL);

    return head;

}
//�󵥴ε�����
Linklist derivative_base(Linklist head)
{
    LNode *p = head->next,*New_Poly;
    Linklist New_head = initlist();
    New_Poly = New_head;
    for (;p!=NULL;p = p->next)
    {
        if(p->exp != 0)
        {
            New_Poly = Attch(p->exp*p->coef,p->exp-1,New_Poly);
        }

    }
    return New_head;
}
//�������ܺ���
void com_derivative()
{
    Linklist p_head = initlist();
    LNode*k = NULL,*p=NULL,*q=NULL;
    printf("Input your polying\n");
    p_head = readPolynomial("Poly1.txt");
    p_head = bubbleSortList(p_head);
    printf("The poly is ");
    showall(p_head);
    writePolynomial(p_head,"Poly1.txt");
    derivative(p_head);
    Delete_Link(p_head);
}
//��k�׵���
void derivative(Linklist head)
{
    LNode *p = head->next;
    int k;
    Linklist New_head = initlist();
    LNode *New_Poly;
    printf("�������󵼽���:");
    scanf("%d",&k);
    getchar();
    if(p->exp<k||k<1)
    {
        printf("Error!\n");
        exit(1);
    }
    else
    {
        for(int i = 1;i<=k;i++)
        {
            if(i==1)
            {
                New_head = derivative_base(head);
            }

            else
            {
                New_head = derivative_base(New_head);
            }
        }
    }

    writePolynomial(New_head,"Poly_New.txt");
    printf("The derivative functional is ");
    showall(New_head);
    Delete_Link(New_head);

    return ;
}
//����ʽ�ӷ�
Linklist Poly_Puls(Linklist p_head,Linklist q_head)
{
    LNode *p = p_head->next,*q = q_head->next,*New_Poly,*k=NULL;
    Linklist New_head = initlist();
    New_Poly = New_head;//ָ��ͷ�ڵ��ָ��

    while((p!=NULL)&&(q!=NULL))
    {
        if(p->exp==q->exp)
        {
            if(p->coef!=-1*q->coef)
            {
                 New_Poly = Attch(p->coef+q->coef,p->exp,New_Poly);
            }

            p = p->next;
            q = q->next;
        }
        else if(p->exp > q->exp)
        {
            New_Poly = Attch(p->coef,p->exp,New_Poly);
            p  =p->next;
        }
        else if(p->exp < q->exp)
        {
            New_Poly = Attch(q->coef,q->exp,New_Poly);
            q = q->next;
        }
    }
    while(p!=NULL)
    {
        New_Poly = Attch(p->coef,p->exp,New_Poly);
        p = p->next;
    }
    while(q!=NULL)
    {
        New_Poly = Attch(q->coef,q->exp,New_Poly);
        q = q->next;
    }


    return New_head;
}
//����ʽ����
Linklist Poly_Sub(Linklist p_head,Linklist q_head)
{
   LNode *p = p_head->next,*q = q_head->next,*New_Poly;
    Linklist New_head = initlist();
    New_Poly = New_head;//ָ��ͷ�ڵ��ָ��

    while((p!=NULL)&&(q!=NULL))
    {
        if(p->exp==q->exp)
        {
            if(p->coef!=q->coef)
            {
                New_Poly = Attch(p->coef-q->coef,p->exp,New_Poly);
            }

            p = p->next;
            q = q->next;
        }
        else if(p->exp > q->exp)
        {
            New_Poly = Attch(p->coef,p->exp,New_Poly);
            p  =p->next;
        }
        else if(p->exp < q->exp)
        {
            New_Poly = Attch(-1*q->coef,q->exp,New_Poly);
            q = q->next;
        }
    }
    while(p!=NULL)
    {
        New_Poly = Attch(p->coef,p->exp,New_Poly);
        p = p->next;
    }
    while(q!=NULL)
    {
        New_Poly = Attch(-1*q->coef,q->exp,New_Poly);
        q = q->next;
    }
    return New_head;
}
//����ʽ�˷�
Linklist Poly_Multi(Linklist p_head,Linklist q_head)
{
    LNode *p = p_head->next,*q = q_head->next,*New_Poly,*k = NULL;
    Linklist New_head = initlist();
    New_Poly = New_head;
    for (p = p_head->next;p!=NULL;p = p->next)
    {
        for(k = q;k!=NULL;k=k->next)
        {
          New_Poly = Attch(p->coef*k->coef,p->exp+k->exp,New_Poly);
        }
    }
    New_head = bubbleSortList(New_head);
    /* = New_head->next;
    k = p->next;
    while(k->next!=NULL&&k!=NULL&&p!=NULL&&k->next->next!=NULL)
    {//�ϲ�ͬ����
        if(p->exp==k->exp)
        {
            p->coef = p->coef+k->coef;
            p->next = k->next;
            p = p->next;
            q = k;
            k = k->next->next;
            free(q);
        }
    }*/

    return New_head;
    }

//�������ʽ��ֵ
float addpoly(Linklist head,float x)
{
    float sum = 0,node;
    LNode *p = head->next;
    while(p!=NULL)
    {
       node = (p->coef)*pow(x,p->exp);
       sum +=  node;
       p = p->next;
    }
    return sum;
}

//չʾ����ʽ������
void showall(Linklist head)
{
    LNode *p = head->next;
    while(p!=NULL)
    {
        if(p->exp == 0)
        {
            printf("%d",p->coef);
        }
        else
        {
            printf("%dx^%d",p->coef,p->exp);
        }

        p = p->next;
        if(p!=NULL&&p->coef>0)
        {
            printf("+");
        }
    }
    printf("\n");
    return ;

}
//��������ʽ����
void TwoPoly_com(char ope)
{
    Linklist New_head,p_head,q_head;
    float num;
    printf("Please input the number:");
    scanf("%f",&num);
    getchar();
    p_head = initlist();
    q_head = initlist();
    printf("Reading your first polying \n");
    p_head = readPolynomial("Poly1.txt");
    p_head = bubbleSortList(p_head);
    printf("The poly1 is:");
    showall(p_head);
    writePolynomial(p_head,"Poly1.txt");
    printf("Reading your second polying\n");
    q_head = readPolynomial("Poly2.txt");
    q_head = bubbleSortList(q_head);
    printf("The poly2 is:");
    showall(q_head);
    writePolynomial(q_head,"Poly2.txt");
    New_head = com_Poly(p_head,q_head,ope);
    writePolynomial(New_head,"Poly_New.txt");
    printf("The New_poly is:");
    showall(New_head);
    float result = addpoly(New_head,num);
    printf("The result is %f\n",result);
    Delete_Link(p_head);
    Delete_Link(q_head);
    return ;
}
//�������ʽ
Linklist readPolynomial(const char* filename)
{
    Linklist head =initlist();
    LNode *p = head;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
        {
        perror("�޷����ļ�");
        return NULL;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        // �Ƴ����з��Ϳո�
        line[strcspn(line, "\n\r\t ")] = 0;

        // ����ϵ����ָ��
        int coef, exp;
        if (sscanf(line, "%d%*[^0-9]%d", &coef, &exp) == 2) {
            // ������ָ����������� "3x^-2" Ӧ����Ϊ coef=3, exp=-2
            char* ptr = strchr(line, '^');
            if (ptr && *(ptr + 1) == '-') {
                exp = -atoi(ptr + 2);
            }
            else {
                exp = atoi(ptr + 1);
            }
            // ���뵽������
            p = Attch(coef,exp,p);
        } else {
            // ��ʽ���󣬴�ӡ���沢��������
            fprintf(stderr, "��ʽ����%s\n", line);
        }
    }

    fclose(file);
    return head;
}
//д����ʽ
void writePolynomial(Linklist head, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("�޷����ļ�");
        return;
    }

   LNode* current = head->next;
    while (current != NULL) {
        if (current->exp != 0) {
            fprintf(file, "%dx^%d", current->coef, current->exp);
        } else {
            fprintf(file, "%d", current->coef);
        }

    if (head == NULL)
        {
        fprintf(file, "0\n");
    }
    current = current->next;
    fprintf(file, "\n");
}

    fclose(file);
}
//������������ʽ
Linklist com_Poly(Linklist p_head,Linklist q_head,char ope)
{
    Linklist New_head = initlist();
    switch (ope)
    {
    case '+':
        New_head = Poly_Puls(p_head, q_head);
        break;
    case '-':
        New_head = Poly_Sub(p_head, q_head);
        break;
    case '*':
        New_head = Poly_Multi(p_head, q_head);
        break;
    default:
        printf("Input error!");
        exit(1);
    }
    return New_head;
}
//ɾ������
void Delete_Link(Linklist head)
{
    LNode *p = head,*q = p;
    while(p!=NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return ;
}
