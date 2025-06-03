#include <stdio.h>
 int main(){
     int i, n, v1[50], h;
     scanf("%d", &n);
     if(n>50){
         printf("Erro");
         return 0;}
     if(n<2){
         printf("Erro");
         return 0;}
     for(i=0;i<n;i++){
         scanf("%d", &v1[i]);}
     for(i=n-1;i>=0;i--){
         printf("%d ", v1[i]);
     }
    return 0; 
 }