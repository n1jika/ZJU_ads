#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

typedef struct Edge{
    int to;  //which vertex it direct
    int weight; //the weight of the edge
    struct Edge* next; // next edge
} Edge;

typedef struct {
    Edge* head;
} Vertex;

typedef struct Node{
    int vertex; //number of the vertex
    unsigned int dis; //distance from the start to this vertex
    struct Node* left;// left child
    struct Node* right;// right child
    int npl;//the npl
} Node;

//Merge two leftist heaps
Node* merge(Node* h1, Node* h2){
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;
    //If one of the heaps is empty, return the other heap

    if(h1->dis > h2->dis) {
        Node* temp = h1;
        h1 = h2;
        h2 = temp;
    }//Ensure h1's dist is less than or equal to h2's dist

    h1->right = merge(h1->right, h2);
    //Recursively merge the right child

    if(h1->left == NULL){
        h1->left=h1->right;
        h1->right = NULL;
    }// If the left child is empty, set the right child as the left child
    else{
        if(h1->left->npl<h1->right->npl){
            Node* temp = h1->left;
            h1->left = h1->right;
            h1->right = temp;
        }//If the npl of the left child is less than the right child's npl, swap left and right children
    }
    if(h1->right == NULL) h1->npl = 0;
    else h1->npl = h1->right->npl+1;
    return h1;
}

//Create a new node
Node* creatNode(int x,int y){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex=x; //the number of this vertex
    newNode->dis=y;//the distance form it to the source node 
    newNode->right=NULL;
    newNode->left=NULL;
    newNode->npl=0;//the initial npk
    return newNode;
}

//Insert a node into the leftist heap
Node* insert(Node* root, int x, int y){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode = creatNode(x,y);
    return merge(root,newNode);//insert it to the leftist Heap
}

// Delete the minimum node from the leftist heap
Node* deleteMin(Node* root) {
    if (root == NULL) 
        return NULL;
    Node* left = root->left;
    Node* right = root->right;
    root->left=root->right=NULL;
    return merge(left, right);//build a new Leftist Heap after deleting
}

void dijkstra(int N_v, Vertex graph[],int source){
    int* distances = (int*)malloc(N_v * sizeof(int));
    int* visit = (int*)malloc(N_v * sizeof(int));//judge if the vertex had been visited
    Node* Heap = (Node*)malloc(sizeof(Node));
    Heap = NULL;

    for(int i=0;i<N_v;i++){
        distances[i] = INT_MAX;//initial the dis
        visit[i]=0;//initial that every node hasn't been visited
        if(i == source){
            Heap = insert(Heap,i,0);
            distances[i] = 0;//at first only insert the source node
        }
    }

    while(Heap!= NULL){
        Node* minNode = (Node*)malloc(sizeof(Node));
        minNode =Heap;
        Heap = deleteMin(Heap);//delete the node which has minnum dis
        int a = minNode->vertex;

        Edge* current = graph[a].head;
        while(current!=NULL&&visit[a]==0){//every node only can be visited one time
            int v =current->to;
            int weight = current->weight;
            if(distances[a]!=INT_MAX &&distances[a]+weight<distances[v]){//renew the distances
                distances[v] =distances[a]+weight;
                Heap = insert(Heap,v ,distances[v]);//insert it to the Leftist Heap
            }
            current = current->next;
        }
        visit[a]=1;//after visit vertex a,update visit[a] to 1
        free(minNode);
    }
    free(distances);
    free(Heap);
}

//adjlist for all the edges
void addEdge(Vertex graph[],int from, int to, int weight) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->weight = weight;
    newEdge->next = graph[from].head;
    graph[from].head = newEdge;
}


int main(){
    clock_t start, end;//record the time
    double cpu_time_used;

    char filename[] = "D://work//ADS//output//input.txt";

    int N_v,N_e,source;
    FILE *file = fopen(filename, "r");//read the data from the file
    if (file == NULL) {
        printf("无法打开文件 %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d %d", &N_v, &N_e, &source);//read the data from the file
    Vertex* Graph = (Vertex*)malloc(N_v * sizeof(Vertex));//build the graph
     for (int i = 0; i < N_v; i++) {
        Graph[i].head = (Edge*)malloc(sizeof(Edge));
        Graph[i].head=NULL;
    }
    for(int i=0;i<N_e;i++){
        int from, to ,w;
        fscanf(file, "%d %d %d", &from, &to, &w);
        addEdge(Graph,from, to, w);
    }//build the adjlist
    fclose(file);

    start = clock();

    dijkstra(N_v,Graph,source);

    end = clock();
    free(Graph);
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;//calculate how much time it costs
    printf("程序执行的时间：%f 秒\n", cpu_time_used);

    return 0;
}