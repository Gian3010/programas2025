#include <stdio.h>
 
    int main(){
        int ld, base=1, n=0;
        long int bi;
        scanf("%ld", &bi);
        while(bi > 0){
            ld=bi%10;
            bi=bi/10;
            n=n+ld*base;
            base=base*2;
 
        }
    printf("%d", n);
    return 0;
    }