#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<math.h>

int N,M,L;
int* statement;
int flag = 0;

//M个狼人;至少一个但不是所有狼人撒谎;L个人在撒谎
bool if_in(int fact[],int a){
    for(int i=0;i<M;i++)
        {
            if(fact[i]==a)
                return true;
        }
    return false;
}

bool check(int fact[]){
    int liar_n=0;
    int liar_wolf=0;
    for(int i=1;i<=N;i++){
        if(statement[i]>0){
            if(if_in(fact,statement[i])){
                liar_n++;
                if(if_in(fact,i))
                liar_wolf++;
            }
        }
        else{
            if(if_in(fact,abs(statement[i]))==false){
                liar_n++;
                if(if_in(fact,i))
                liar_wolf++;
            }
        }
    }
    if(liar_n == L && liar_wolf>=1 && liar_wolf < M)
        return true;
    else
        return false;
}

void backtrack(int fact[],int index,int count){
    if(flag == 1)
        return;
    if (count == M) {
        if (check(fact)) {
            for (int i = 0; i < M-1; i++) {
                printf("%d ", fact[i]);
            }
            printf("%d", fact[M-1]);
            flag = 1;
        }
        return;
    }
    if (count == M || index == -1) {
        return;
    }
    fact[count] = index + 1;
    backtrack(fact,index - 1, count + 1);
    
    fact[count] = 0;
    backtrack(fact,index - 1,count);
}

int main(){
    int* fact;
    scanf("%d %d %d",&N,&M,&L);
    fact = (int*)malloc((M) * sizeof(int));
    statement = (int*)malloc((N + 1) * sizeof(int));
    for(int i=1;i<=N;i++){
        scanf("%d",&statement[i]);
    }
    for(int i=0;i<M;i++){
        fact[i]=0;
    }
    backtrack(fact,N-1,0);
    if(flag == 0)
        printf("No Solution");
}