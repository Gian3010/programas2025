#include <stdio.h>
#define c 30
#define l 30
#define num 101    
    int main(){
        int m[l][c], j, h;
        int val[num]= {0};
        scanf("%d", &j);
        scanf("%d", &h);
        for(int i = 0 ; i < j ; i++){
            for(int k = 0 ; k < h ; k++){
                scanf("%d", &m[i][k]);
            }
        }
        for(int i = 0 ; i < j ; i++){
            for(int k = 0 ; k < h ; k++){
                int n=m[i][k];
                val[n]++;
            }
        }
         for(int i = 0 ; i < num ; i++ ){
            if(val[i]>0){
                printf("%d %d\n",i ,val[i]);
            }
         }


        return 0;
    }