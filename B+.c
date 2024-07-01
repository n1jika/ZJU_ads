#include<stdio.h>
#include<stdlib.h>

typedef struct tnode* node; 
struct tnode{
	int key[4];
    int key_n,child_n;
	node parent;
    node children[4];
};

node root = NULL;
node now = NULL;
int now_key = 0;

void find(int x){
    int flag=1;
    while(now->children[0]){
        int k = now->key_n;
        for(int i=0;i<now->key_n;i++){
            if(now->key[i]>x){
                k=i;
                break;
            }
        }
        if(now->children[k]){
            now=now->children[k];
        }
    }
    if(now->children[0]==NULL && now->children[1]==NULL && now->children[2]==NULL){
        int m = now->key_n;
        for(int i=0;i<now->key_n;i++){
            if(now->key[i]>x){
                m=i;
                break;
            }
            if(now->key[i]==x)
                flag = 0;
        }
        if(flag == 0){
            printf("Key %d is duplicated\n",x);
        }
        else{
            for(int i=now->key_n;i>m;i--){
                now->key[i]=now->key[i-1];
            }
            now->key[m] = x;
            now->key_n++;
        }
    }
}

void change(node t){//renew node t's keys
node y;
if(t->children[0]){
    t->key_n=0;
        for(int i=0;i<t->child_n-1;i++){
            y=t->children[i+1];
            while(y->children[0])
                y=y->children[0];
            t->key[t->key_n++]=y->key[0];
        }
    }  
}

void bl(node t){
    change(t);
    if(t->children[0])
        bl(t->children[0]);
    if(t->children[1])
        bl(t->children[1]);
    if(t->children[2])
        bl(t->children[2]);
    if(t->children[3])
        bl(t->children[3]);
}

void split_leaf(){
    if(now->parent){
        node newx = (node)malloc(sizeof(struct tnode));
        newx->key[0]=now->key[2];
        newx->key[1]=now->key[3];
        now->key_n=2;
        newx->parent=now->parent;
        newx->child_n=0;
        newx->key_n=2;
        for(int i=0;i<4;i++)
            newx->children[i]=NULL;
        now->parent->child_n++;
        int m=now->parent->child_n-1;
        for(int i=0;i<now->parent->child_n-1;i++){
            if(newx->key[0]<now->parent->children[i]->key[0]){
                m=i;
                break;
            }
        }
        for(int i=now->parent->child_n;i>m;i--){
            now->parent->children[i]=now->parent->children[i-1];
        }
        now->parent->children[m]=newx;
    }
    else{//when the root is a leaf and has 4 keys
        node new1 = (node)malloc(sizeof(struct tnode));
        node new2 = (node)malloc(sizeof(struct tnode));
        new1->parent=now;
        new2->parent=now;
        new1->child_n=0;
        new2->child_n=0;
        new1->key_n=2;
        new2->key_n=2;
        new1->key[0]=now->key[0];
        new1->key[1]=now->key[1];
        new2->key[0]=now->key[2];
        new2->key[1]=now->key[3];
        for(int i=0;i<4;i++){
            new1->children[i]=NULL;
            new2->children[i]=NULL;
        }
        now->children[now->child_n++]=new1;
        now->children[now->child_n++]=new2;
        now->key[0]=new2->key[0];
        now->key_n=1;
    }
}

void split_nonleaf(){
    if(now->parent){
        node newx = (node)malloc(sizeof(struct tnode));
        newx->parent=now->parent;
        newx->child_n=2;
        newx->children[0]=now->children[2];
        newx->children[1]=now->children[3];
        newx->children[0]->parent=newx;
        newx->children[1]->parent=newx;
        now->child_n=2;
        now->children[2]=NULL;
        now->children[3]=NULL;
        newx->children[2]=NULL;
        newx->children[3]=NULL;
        now->parent->child_n++;
        int m=now->parent->child_n-1;
        newx->key[0]=now->key[1];
        for(int i=0;i<now->parent->child_n-1;i++){
            if(newx->key[0]<now->parent->children[i]->key[0]){
                m=i;
                break;
            }
        }
        for(int i=now->parent->child_n;i>m;i--){
            //for(int j=0;j<now->parent->children[i-1]->child_n;j++){
                //now->parent->children[i-1]->children[j]->parent=now->parent->children[i];
            //}
            now->parent->children[i]=now->parent->children[i-1];
        }
        now->parent->children[m]=newx;                                     
    }
    else{//while the root has 4 children
        node new1 = (node)malloc(sizeof(struct tnode));
        node new2 = (node)malloc(sizeof(struct tnode));
        new1->parent=now;
        new2->parent=now;
        new1->child_n=2;
        new2->child_n=2;
        new1->children[0]=now->children[0];
        new1->children[1]=now->children[1];
        new2->children[0]=now->children[2];
        new2->children[1]=now->children[3];
        new1->children[0]->parent=new1;
        new1->children[1]->parent=new1;
        new2->children[0]->parent=new2;
        new2->children[1]->parent=new2;
        now->children[0]=new1;
        now->children[1]=new2;
        now->child_n=2;
        now->children[2]=NULL;
        now->children[3]=NULL;
        new1->children[2]=NULL;
        new1->children[3]=NULL;
        new2->children[2]=NULL;
        new2->children[3]=NULL;
    }
}

void insert(int x){
    if(root==NULL){
        root=(node)malloc(sizeof(struct tnode));
        root->key_n=0;
        root->child_n=0;
        root->key[root->key_n++]=x;
        root->parent=NULL;
        for(int i=0;i<4;i++)
            root->children[i]=NULL;
    }
    else{
        now = root;
        now_key = 0;
        find(x);
        bl(root);
        if(now->key_n>3){
            split_leaf();
            bl(root);
        }
        while(now->parent!=NULL){
            now=now->parent;
            if(now->child_n>3){
                split_nonleaf();
                bl(root);
            }
        }
    }
}

node queue[10000];
int front, rear;

void enqueue(node t)
{
	front = (front + 1) % 10000;
	queue[front] = t;
}
 
node dequeue()
{
	rear = (rear + 1) % 10000;
	return queue[rear];
}
 
void print(node t)
{
	if (!t)
        return;
	node tmp;
	enqueue(t);
	int cur = 1;
	int curnum = 1;
	int nextnum = 0;
	while (front != rear){
		tmp = dequeue();
		if (tmp->child_n>0){
			curnum--;
			printf("[%d", tmp->key[0]);
			if (tmp->children[0]){
				enqueue(tmp->children[0]);
				nextnum++;
			}
			if (tmp->key_n>1){
				printf(",%d]", tmp->key[1]);
			}
			else printf("]");
            if (tmp->children[1]){
				enqueue(tmp->children[1]);
				nextnum++;
				}
			if (tmp->children[2]){
				enqueue(tmp->children[2]);
				nextnum++;
			}
			if (curnum == 0){
				printf("\n");
				cur++;
				curnum = nextnum;
				nextnum = 0;
			}
		}
		else{
			printf("[%d", tmp->key[0]);
			if (tmp->key_n>1)
                printf(",%d", tmp->key[1]);
			if (tmp->key_n>2)
                printf(",%d]", tmp->key[2]);
			else 
                printf("]");
		}
	}
	printf("\n");
}

int main(){
    int N;
    int* input=(int*)malloc(sizeof(int));
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",input+i);
        now = (node)malloc(sizeof(struct tnode));
        insert(input[i]);
    }
    front = 0;
    rear = 0;
    print(root);
}