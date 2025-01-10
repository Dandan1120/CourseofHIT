#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
typedef struct matrix
{
    int parent[MAX];
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

void initial_parent(MTGraph *graph)//初始化父节点
{
    int i;
    int v=graph->vernum;
    for(i=0;i<v;i++)
    {
        graph->parent[i]=i;
    }
}
int find_parent(MTGraph MST,int index)//递归找妈妈
{
    int root;
    int i;
    if(MST.parent[index]==index)
    {
        return index;
    }
    else 
    {
        return find_parent(MST,MST.parent[index]);
    }
}
int root_num(MTGraph *MST)
{
    int v=MST->vernum;
    int i;
    int num=0;
    for(i=0;i<v;i++)
    {
        if(MST->parent[i]==i)
        {
              num++;
        }
      
    }
    return num;
}
void select(MTGraph graph, MTGraph MST,int *index_1,int *index_2)//找出最小值及其关联边
{
   int i,j;
   int v=graph.vernum;
   int min=10000;
   for(i=0;i<v;i++)
   {
    for(j=i+1;j<v;j++)
    {
        if(graph.edge[i][j]<=min&&graph.edge[i][j]!=0)//找最小值
        {           
           if(find_parent(MST,i)!=find_parent(MST,j))//不在同一棵树里
           { 
            // printf("parent_1= %d,parent_2 = %d\n",find_parent(MST,i),find_parent(MST,j));
            min=graph.edge[i][j];
            *index_1=i;
            *index_2=j; 
            //  printf("inedx_1 = %d,index_2 = %d\n",i,j);
           }
        }
    }
   }
}
void kruscal(MTGraph graph,MTGraph *MST)
{
    int i,j;
    int index_1,index_2;
    int v=graph.vernum;
    int num=0;
    while(num!=1)
    {
        
        select(graph,*MST,&index_1,&index_2);
        // printf("%d parent is %d\n",index_2,find_parent(*MST,index_2));
        MST->edge[index_1][index_2]=graph.edge[index_1][index_2];
        MST->edge[index_2][index_1]=graph.edge[index_2][index_1];//加入最小边
        MST->parent[find_parent(*MST,index_2)]=find_parent(*MST,index_1);  //合并两个集合
        num=root_num(MST);
        printf("new:inedx_1 = %d,index_2 = %d,weight = %d\n",index_1,index_2,MST->edge[index_1][index_2]);
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
    initial_parent(&MST);
    printf("The graph is:\n");
    show_graph(graph);
    kruscal(graph,&MST);
    printf("The MST is :\n");
    show_graph(MST);
    write_MST_in_file( MST);
}
