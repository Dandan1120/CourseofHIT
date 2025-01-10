#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    char val;
    int weight;
    int parent;
    int lchild;
    int rchild;

}HTNODE,*HuffmanTree;//哈夫曼节点

typedef struct Hcode
{
    char cd[20];
}HCODE;//哈夫曼编码
void initialize_table(HTNODE *HT)//频率表初始化
{
    int i;
    if(!HT)
    {
        printf("ERROR");
        exit(1);
    }
    for (i = 0;i<=255;i++)
    {
        HT[i].lchild = 0;
        HT[i].parent = 0;
        HT[i].rchild = 0;
        HT[i].weight = 0;
    }
    return ;
}


float read_file_and_count_frequencies( HTNODE *freq_table) //读取文件
{
    FILE *file = fopen("data.txt", "r");
    float n = 0;
    if (!file)
        {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }//异常处理

    char ch;
        while ((ch = fgetc(file)) !=EOF)
            {
                n++;

        freq_table[ch].weight++;
    }//给频率表赋值

    fclose(file);
    return n;
}
int num_vaild(HTNODE *freq_table)//计算有效的字母数
{
    int i;
    int num = 0;
    for(i = 0;i<=255;i++)
    {
        if(freq_table[i].weight>0)
        {
            num++;
        }
    }
    return num;
}

HTNODE* CreateHuffmanTreeNodes(HTNODE *freq_table)//创建哈夫曼树节点
{
    int num = num_vaild(freq_table);
    int m = 2*num-1,k;
    k = 1;
    if(num<=1)
    {
        printf("ERROR!");
        HTNODE *HT=NULL;
        return HT;
    }
    int i;
    HTNODE *HT= (HTNODE*)malloc(sizeof(HTNODE)*(m+1));
    for (i = 0;i<=m;i++)//初始化哈夫曼树节点
    {
        HT[i].lchild = 0;
        HT[i].rchild = 0;
        HT[i].parent = 0;
        HT[i].weight = 0;
        HT[i].val = '\0';
    }
   for (i = 0;i<=255;i++)
   {
        if(freq_table[i].weight!=0)
        {
            HT[k].weight = freq_table[i].weight;
            HT[k].val = i;
            k++;
        }
   }

   return HT;
}
void Select(HTNODE *HT, int n, int *s1, int *s2)//选出两个权重最小的结点
{
    int i;
    *s1 = -1;
    *s2 = -1;
    for (i = 1; i <= n; i++) 
    {
        if (HT[i].parent == 0) 
        {
            if (*s1 == -1 || HT[i].weight < HT[*s1].weight)
            {
                *s2 = *s1;
                *s1 = i;
            } 
            else if (*s2 == -1 || HT[i].weight < HT[*s2].weight)
            {
                *s2 = i;
            }
        }
    }
}

void CreateHuffmanTree(HTNODE *HT,int n)//创建哈夫曼树
{
    int i,s1,s2;
    int m = 2*n-1;
    for(i = n+1;i<=m;i++)
    {
        Select(HT,i-1,&s1,&s2);
        HT[i].weight = HT[s1].weight+HT[s2].weight;
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;

    }
}
void showall_HT(HTNODE *HT,int num)//展示节点
{
    int i = 1;
    int n = 2*num-1;
    for( ;i<=n;i++)
    {
        if(HT[i].val=='\n')
        {
            printf("index = %d,val =  ,weight = %d,parent = %d,lchild = %d,rchild = %d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        }
        else
        {
             printf("index = %d,val = %c,weight = %d,parent = %d,lchild = %d,rchild = %d\n",i,HT[i].val,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
        }
       
    }
    return ;

}

void HuffmanEnCoding(HTNODE *HT,HCODE **HC,int n)//创建哈夫曼编码
{
    int i = 1;
    char index;
    char cd[n];
    int start;
    int c,f;
    if(!*HC)
    {
        printf("ERROR");
    }
    for(i = 1;i<=n;i++)
    {   start = n-1;
        index = HT[i].val;
        cd[start] = '\0';
        c = i;
        f = HT[i].parent;
        while(f!=0)
        {
            start--;
            if(HT[f].lchild==c)
            {
                cd[start]='0';
            }
            else if(HT[f].rchild==c)
            {
                cd[start]='1';
            }
            c = f;
            f = HT[f].parent;

        }

        strcpy((*HC)[index].cd,&cd[start]);
        if(index =='\n')
        {
            printf("val = ,code = %s\n",(*HC)[index].cd);
        }
        else
        {
             printf("val = %c,code = %s\n",index,(*HC)[index].cd);
        }
       
    }
    return ;
}

void EnCoding(HCODE *HC)//给文件进行哈夫曼编码
{
    FILE *file = fopen("data.txt", "r");
    FILE *out = fopen("code_out.txt","w");
    if(!file)
    {
        printf("Open Failure");
        exit(1);
    }

     char ch;
        while ((ch = fgetc(file))!=EOF)
        {
        fprintf(out,"%s",HC[ch].cd);
        }

    fclose(file);
    fclose(out);

}
float DeCoding(HTNODE *HT,int num)//解码编码好的文件，并将解码结果写入文本文件
{
    FILE *file = fopen("code_out.txt","r");
    FILE *newStream = fopen("output.txt","w");
    char ch;
    int n = 2*num-1;
    int i ;
    for(i = 1;i<=n;i++)
    {
        if(HT[i].parent==0)
        {
            break;
        }
    }
    int root = i;
    float m = 0;
    int c = root;
    ch=fgetc(file);
    m++;
   while(ch!=EOF)
    {
        c=root;
        while(HT[c].lchild!=0||HT[c].rchild!=0)
    {
        if(ch=='1')
        {
            c=HT[c].rchild;
        }

        else if(ch=='0')
        {
            c=HT[c].lchild;
        }
        ch=fgetc(file);
        
        if(ch==EOF)
        {
            break;
        }
        m++;
    }

        fprintf(newStream,"%c",HT[c].val);
    }

    fclose(file);
    fclose(newStream);

    return m;
}
void Compare()//比较源文件和解码后的文件是否相同
{
    FILE *fp_1,*fp_2;
    fp_1 = fopen("data.txt", "r");
    fp_2 = fopen("output.txt","r");
    char ch_1,ch_2;
    int flag=1;
    do
    {
        ch_1=fgetc(fp_1);
        ch_2 = fgetc(fp_2);
        if(ch_1!=ch_2)
        {
            flag=0;
            break;
        }
    }while(ch_1!=EOF||ch_2!=EOF);
    if(flag)
    {
        printf("Susseccful!\n");
    }
    else if(!flag)
    {
        printf("Failure!");
    }
    return ;
}

int main()
{
    HTNODE *freq_table = (HTNODE*)malloc(sizeof(HTNODE)*256);
    initialize_table(freq_table);
    float orignal_size =  read_file_and_count_frequencies(freq_table);
    int num = num_vaild(freq_table);
    HTNODE *HT =  CreateHuffmanTreeNodes(freq_table);
    free(freq_table);
    CreateHuffmanTree(HT,num);
    showall_HT(HT,num);
    HCODE *HC ;
    HC = (HCODE*)malloc(256*sizeof(HCODE));//内存分配
    HuffmanEnCoding(HT,&HC,num);
    EnCoding(HC);
    free(HC);
    float Huffman_size=DeCoding(HT,num);
    Huffman_size *= sizeof(char);
    orignal_size *= sizeof(char)*8;
    float ratio = Huffman_size/orignal_size;
    Compare();
    printf("Compression Ratio: %.2f%%\n", ratio * 100);
    return 0;
}
