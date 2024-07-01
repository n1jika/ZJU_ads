#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tnode* node; 
struct tnode{
	int key;
	int index;
	node left;
	node right;
	node parent;
};

node root = NULL;

void renew_index(node a){
	if(a->parent)
		if(a->parent->left==a)
			a->index=a->parent->index*2;
		else 
			a->index=a->parent->index*2+1;
	else 
		a->index=1;
	if(a->left)
		renew_index(a->left);
	if(a->right)
		renew_index(a->right);
}

int check(node a){
	if(a)
	{
		if(check(a->left)>=check(a->right))
			return check(a->left)+1;
		else
			return check(a->right)+1;
	}
	return 0;
}

int find(int x,int y){
	int ll,rr,lr,rl;
	ll=x*2*2;
	rr=(x*2+1)*2+1;
	rl=(x*2+1)*2;
	lr=x*2*2+1;
	int left,right;
	left=ll;
	right=ll;
	while(left<=y){
		if(y>=left&&y<=right)
			return 1;
		left=left*2;
		right=right*2+1;
	}
	left=rr;
	right=rr;
	while(left<=y){
		if(y>=left&&y<=right)
			return 2;
		left=left*2;
		right=right*2+1;
	}
	left=lr;
	right=lr;
	while(left<=y){
		if(y>=left&&y<=right)
			return 3;
		left=left*2;
		right=right*2+1;
	}
	left=rl;
	right=rl;
	while(left<=y){
		if(y>=left&&y<=right)
			return 4;
		left=left*2;
		right=right*2+1;
	}
}

void LL(node a){
	if(a->right!=NULL)
		a->right->parent=a->parent;
	a->parent->left=a->right;
	if(a->parent->parent){
		if(a->parent->parent->left==a->parent)
			a->parent->parent->left=a;
		else
			a->parent->parent->right=a;
	a->right=a->parent;
	a->parent=a->parent->parent;
	a->right->parent=a;
	}
	else{
		a->right=a->parent;
		a->parent=NULL;
		a->right->parent=a;
		root=a;
	}
	renew_index(a);
}

void RR(node a){
	if(a->left!=NULL)
		a->left->parent=a->parent;
	a->parent->right=a->left;
	if(a->parent->parent){
		if(a->parent->parent->left==a->parent)
			a->parent->parent->left=a;
		else
			a->parent->parent->right=a;
	a->left=a->parent;
	a->parent=a->parent->parent;
	a->left->parent=a;
	}
	else{
		a->left=a->parent;
		a->parent=NULL;
		a->left->parent=a;
		root=a;
	}
	renew_index(a);
}

void LR(node a){
	RR(a);
	LL(a);
}

void RL(node a){
	LL(a);
	RR(a);
}

int main(){
	int n,cha,x,y;
	int in[21];
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&in[i]);
	}
	node t,now=NULL;
	root =(struct tnode*)malloc(sizeof(struct tnode));
	root->key=in[0];
	root->index=1;
	root->left=NULL;
	root->right=NULL;
	root->parent=NULL;
	for(int i=1;i<n;i++){
		t =(struct tnode*)malloc(sizeof(struct tnode));
		now=(struct tnode*)malloc(sizeof(struct tnode));
		now=root;
		while(1){
			if(in[i]<now->key){
				if(now->left)
					now=now->left;
				else
					break;
			}
		else if(in[i]>now->key){
			if(now->right)
				now=now->right;
			else
				break;
			}
		}
		if(in[i]<now->key){
			now->left=(struct tnode*)malloc(sizeof(struct tnode));
			now->left->index=now->index*2;
			now->left->parent=now;
			now=now->left;
			now->left=NULL;
			now->right=NULL;
			now->key=in[i];
		}
		else if(in[i]>now->key){
			now->right=(struct tnode*)malloc(sizeof(struct tnode));
			now->right->index=now->index*2+1;
			now->right->parent=now;
			now=now->right;
			now->left=NULL;
			now->right=NULL;
			now->key=in[i];
		}
		for(t=now;t!=NULL;t=t->parent){
			cha=abs(check(t->left)-check(t->right));
			if(cha>1){
				x=t->index;
				y=now->index;
				switch(find(x,y)){
					case 1:
						LL(t->left);
						break;
					case 2:
						RR(t->right);
						break;
					case 3:
						LR(t->left->right);
						break;
					case 4:
						RL(t->right->left);
						break;
				}
			}
		}
	}
	printf("%d",root->key);
}