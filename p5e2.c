#include <stdio.h>
 int main(){
  int v1[5]= {0}, v2[5]={0}, p, num=0, h;
  while (num<5)
  {
    scanf("%d", &v1[num]);
    if (v1[num]>=-10 && v1[num]<=10)
    {
        num++;
    }    
  }
  scanf("%d", &p);
   if (p == 0) {
        printf("1 1 1 1 1\n");
        return 0;
    }
  while(p<0||p>10){
  scanf("%d", &p);
  if (p == 0) {
    printf("1 1 1 1 1\n");
    return 0;
  }
  
  } 
  for(int i=0 ; i<5 ; i++){
    h=1;
    v2[i]=v1[i];
    h=v2[i];
    for(int j=2;j<=p;j++){        
        v2[i]=v2[i]*h;
        } 
    printf("%d ", v2[i]);
    }
 
   return 0;
  
 }