#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
typedef struct matrix
{
    int vertex[MAX];
    int edge[MAX][MAX];
    int vernum;
}MTGraph;

void read_graph_file(MTGraph *graph)//读取文件
{

    FILE *file = fopen("input_graph.txt", "r");
    if (!file) {
        printf("无法打开文件\n");
        exit(1);
    }
    
    fscanf(file, "%d", &graph->vernum); //读顶点个数
    // memset(graph->vertex ,1, sizeof(graph->vertex));
    memset(graph->edge,0, sizeof(graph->edge));

    int u,v,w;
    while (fscanf(file, "%d %d %d", &u, &v, &w) != EOF) //读边
    {
        graph->edge[u][v] = w;  //无向图，两边都赋值
        graph->edge[v][u] = w;
    }

    fclose(file);
}
void show_graph(MTGraph graph)//展示图
{
    int v = graph.vernum;//顶点数
    int i = 0;
    int j = 0;
    printf("EDGE  WEIGHT\n");
    for(i=0;i<v;i++)
    {
        for(j=i+1;j<v;j++)
        {
            if(graph.edge[i][j]!=0)//避免输出重复的边
            {
                printf("%d-%d   %d\n",i,j,graph.edge[i][j]);
            }

        }
    }
}
void select(int *a,int *index,int num)//找出最小值
{
    int i,j;
    // int flag=0;
    i=0;
    // printf("start");
    while(a[i]==0&&i<num)
    {
        i++;
    }
    if(!(i<num))
    {
        *index=-1;
        return ;
    }
    else
    {
        *index = i;
    }
    
    for(;i<num;i++)
    {   
        //  printf("i= %d,value = %d\n",i,a[i]);
        if(a[i]<a[*index]&&a[i]!=0)
        {
            // printf("start\n");
            *index = i;
        }
    }
}
int num(MTGraph *MST)
{
    int v=MST->vernum;
    int i;
    int sum=0;
    for(i=0;i<v;i++)
    {
        sum+=MST->vertex[i];
    }
    return sum;
}
void zero(int *a,int num)
{
    for (int i=0;i<num;i++)
    {
        a[i]=0;
    }
}
void Prim(MTGraph graph,MTGraph *MST)
{
    int v = graph.vernum;
    int i,j,min_index[v];
    int index;
    i=0;
    j=0;
    int min[v];//存每个点最小值的数组；
    int len=0;
    memset(MST->edge, 0, sizeof(MST->edge));
    memset(MST->vertex, 0, sizeof(MST->vertex));
    MST->vertex[0]=1;
    while(len!=v)
    {
    zero(min,v);
    zero(min_index,v);
        for(i=1;i<v;i++)
        {
            if(MST->vertex[i]!=1)//找某一点最小权值边
            {
                for(j=0;j<v;j++)//初始化最小值
                {
                    if(graph.edge[i][j]!=0&&MST->vertex[j]==1)
                    {
                        min[i]=graph.edge[i][j];
                        min_index[i]=j;
                        break;
                    }
                }
                if(!(j<v))
                {
                    continue;
                }
                for(;j<v;j++)
                {
                    if(MST->vertex[j]==1&&(graph.edge[i][j]<=min[i])&&graph.edge[i][j]!=0)
                    {
                        min[i]=graph.edge[i][j];
                        min_index[i]=j;
                    }
                }
            }
        }
        select(min,&index,v);
        if(index<0)
        {
            continue;
        }
        MST->vertex[index]=1;
        MST->edge[index][min_index[index]] = min[index];
        MST->edge[min_index[index]][index] = min[index];
        printf("new_node: i=%d,j=%d,weight = %d\n",index,min_index[index],min[index]);
        len=num(MST);
        // printf("len=%d\n",len);
    }

}
void write_MST_in_file(MTGraph MST)
{
    FILE *fp= fopen("output_MSTree.txt","w");
    int v = MST.vernum;//顶点数
    int i = 0;
    int j = 0;
    fprintf(fp,"%d\n",v);
    for(i=0;i<v;i++)
    {
        for(j=i+1;j<v;j++)
        {
            if(MST.edge[i][j]!=0)//避免输出重复的边
            {
                fprintf(fp,"%d-%d %d\n",i,j,MST.edge[i][j]);
            }

        }
    }
    fclose(fp);
}

int main()
{
    MTGraph graph,MST;
    read_graph_file(&graph);
    int v = graph.vernum;
    MST.vernum=v;
    printf("The graph is:\n");
    show_graph(graph);
    Prim(graph,&MST);
    printf("The MST is :\n");
    show_graph(MST);
    write_MST_in_file(MST);
}
