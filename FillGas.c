#include<stdio.h>
#include<math.h>

int  Distance, D_avg, N, Dis_now = 0;
float cost = 0,C_max, Capacity = 0.00;

struct Station
{
    float P;
    int D;
};
typedef struct Station Station;

int next_station(Station S[]){
    int k = 0;
    for(k=0;k<N;k++){
        if(Dis_now<S[k].D){
            break;
        }
    }
    return k;
}

int main(){
    scanf("%f %d %d %d",&C_max, &Distance, &D_avg, &N);
    Station S[N];
    for(int i=0;i<N;i++){
        scanf("%f %d",&S[i].P,&S[i].D);
        for(int j=i;j>0;j--){
            if(S[j].D<S[j-1].D){
                Station temp;
                temp = S[j];
                S[j]=S[j-1];
                S[j-1]=temp;
            }
            else
                break;
        }
    }
    int next;
    int can= 1;
    while(Dis_now < Distance){
        next=next_station(S);
        int k = next,flag = 0;
        printf("%d\n",next);
        if(next == N){
            if(Dis_now + C_max*D_avg < Distance){
                printf("The maximum travel distance = %.2f",Dis_now + C_max*D_avg);
                can = 0;
                break;
            }
            else{
                float gas_up = (Distance - Dis_now) / (float)D_avg;
                if(gas_up>Capacity)
                    cost += (gas_up - Capacity) * S[next-1].P;
                break;
            }
        }
        else if(next == 0){
            printf("The maximum travel distance = 0.00");
            can = 0;
            break;
        }
        else{
            if(Dis_now + C_max*D_avg < S[next].D){
                printf("The maximum travel distance = %.2f",Dis_now + C_max*D_avg);
                can = 0;
                break;
            }
            else{
                while(k<N){
                    if(Dis_now + C_max*D_avg >= S[k].D && S[k].P<=S[next-1].P){
                        flag = 1;
                        float gas_up = (S[k].D - Dis_now) / (float)D_avg;
                        if(gas_up>Capacity){
                            cost += (gas_up - Capacity) * S[next-1].P;
                            printf("2 %f * %f %f\n",gas_up-Capacity,S[next -1].P,Capacity);
                            Capacity = gas_up;
                        break;
                        }
                        else{
                            break;
                        }
                    }
                    k++;
                }
                if(flag == 0)
                {
                    cost += (C_max -Capacity)*S[next -1].P;
                    printf("3 %f * %f %f\n",C_max -Capacity,S[next -1].P,Capacity);
                    Capacity =  C_max;
                }
            }
        }
        if(flag == 0){
        Capacity -= (float)(S[next].D-Dis_now) / (float)D_avg;
        Dis_now = S[next].D;
        }
        else
        {
            Capacity -= (float)(S[k].D-Dis_now) / (float)D_avg;
            Dis_now = S[k].D;
        }
    }
    if(can == 1)
        printf("%.2f",cost);
}