#include <stdio.h>
#define j  30
#define k  30     
#define num 101 
//delimitando a matriz// 
    int main(){
        int v[j][k]={0}, l, c;
        scanf("%d", &l);
        scanf("%d", &c);
        int b[j][k], lb, cb;
        scanf("%d", &lb);
        scanf("%d", &cb);
        if(l > 30 || c > 30 || lb > 30 || cb > 30){
            printf("ERRO");
            return 0;
        }
        if(c!=lb){
            printf("ERRO");
            return 0;
        }
        for(int i=0 ; i<l ; i++){
            for(int h=0 ; h<c ; h++){
                scanf("%d", &v[i][h]);
            }
        }//leitura a//
        int C[j][k]={0};
        for(int i=0 ; i<lb ; i++){
            for(int h=0 ; h<cb ; h++){
                scanf("%d", &b[i][h]);
            }
        }//leitura b//
        for(int i=0 ; i<l ; i++){
            printf("\n");
            for(int h=0 ; h<cb ; h++){
                for(int y=0 ; y<c ;y++){
                    C[i][h]=C[i][h]+v[i][y]*b[y][h];
                }
                printf("%d ", C[i][h]);   
            }
        }
        
    
                   
    
}