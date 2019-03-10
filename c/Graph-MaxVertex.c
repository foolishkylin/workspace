#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxVertexNum 100
#define INFINITY 65535
#define FALSE 0
#define TRUE 1

typedef  int  VertexType;      
typedef  int  EdgeType;       

typedef struct Node{
	int date;
	struct Node *next;
} Queue;

typedef  struct {
    VertexType  Vertices[MaxVertexNum];             // VertexSet
    EdgeType  Edges[MaxVertexNum][MaxVertexNum];    // EdgeSet
    int  n, e;                                      // the num of Verters and edges
} MGraph;    

// following is a nomal queue
int IsEmpty(Queue *Q)
{
	return Q->next==0;
}

void DeQueue(Queue *Q) 
{
	Queue *Top;
	
	if(IsEmpty(Q))
		printf("\nEmpty queue\n");
	else
	{
		Top=Q->next;
		Q->next=Q->next->next;
		free(Top);
	}
	
	return ;
}

void EnQueue(Queue *Q, int Element) 
{
	Queue *Rear=(Queue *)malloc(sizeof(Queue));
	
	if(Rear==0)
		printf("\nerror\n");
	else
	{
		for(;Q->next;Q=Q->next);
		Rear->next=0;
		Rear->date=Element;
		Q->next=Rear;
	}	
	
	return ;
} 

void MakeEmpty(Queue *Q)
{
	if(Q==0)
		printf("\nmust use CreatQueue first\n");
	else
		while(!IsEmpty(Q))
			DeQueue(Q);
			
	return ;
}

Queue *CreatQueue(void)
{
	Queue *Q;
	
	Q=(Queue *)malloc(sizeof(Queue));
	if(Q==0)
		printf("\nerror\n");
	Q->next=0;
	MakeEmpty(Q);
	
	return Q;
}
// now this is a create function
void CreateMGraph(MGraph *G)
{
    int i, j, k, w; 
    memset(G->Vertices, 0, sizeof(G->Vertices));     //the undefined vertices value is 0
    puts("please enter the number of vertex and edge");
    scanf("%d%d", &G->n, &G->e);                     // input the limit of graph
    for(i = 0; i < G->n; i++)
    {
        puts("please enter the vertex's names");
        scanf("%d", &G->Vertices[i]);
    }
    for(i = 0; i < G->n; i++)
        for(j = 0; j < G->n; j++)
            G->Edges[i][j] = INFINITY;
    puts("please enter the edges and right value");
    for(w = 0; w < G->e; w++)
    {
        scanf("%d%d%d", &i, &j, &k); 
        G->Edges[i][j] = k;
        G->Edges[j][i] = k; // this graph is Undirected Network 
    }
}
// broad first search
void BFS(MGraph G)
{
    Queue *Q = CreatQueue();      //create a empty queue
    int IsVisited[MaxVertexNum];  // to chiek if the vertex is visited
    int U, i;                     //using in loop

    memset(IsVisited, FALSE, sizeof(IsVisited)); //amsume all isn't visited
    for(U = 0; U < G.n; U++)     // loop for all vertexs
    {
        if(!IsVisited[U])        // 
        {
            IsVisited[U] = TRUE;
            printf("Vertex %d is visited\n", G.Vertices[U]);
            EnQueue(Q, G.Vertices[U]);
        }
        while(!IsEmpty(Q))      //until the queue is empty
        {
            DeQueue(Q);
            for(i = 0; i < G.n; i++)
            {
                if(G.Edges[U][i])
                {
                    if(!IsVisited[i])
                    {
                        IsVisited[i] = TRUE; 
                        printf("Vertex %d is visited\n", G.Vertices[i]);
                        EnQueue(Q, G.Vertices[i]);  // enqueue every unvisited vertex
                    }
                }
            }
        }
    }

}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    BFS(G);
    getchar();
    getchar();

    return 0;
}
