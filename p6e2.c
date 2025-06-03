#include <stdio.h>
#define j  30
#define k  30     
#define num 101 
//delimitando a matriz// 
    int main(){
        int v[j][k]={0}, l, c;
        scanf("%d", &l);
        scanf("%d", &c);
        for(int i=0 ; i<l ; i++){
            for(int h=0 ; h<c ; h++){
                scanf("%d", &v[i][h]);
            }
        }//fazendo a leitura da matriz//
        printf("\n");
        int t[c][l];
        for(int i=0 ; i<c ; i++){
            for(int h=0 ; h<l ; h++){
                t[i][h]=v[h][i];
                printf("%d ", t[i][h]);
            }
            printf("\n");
        }  
        
        
        
        return 0;   
    }