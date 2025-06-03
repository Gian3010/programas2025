#include <stdio.h>
    int main(){
        int m7 = 0, nposit = 0, p = 1, num, h=0;
        int count35=0;
        while(1){
            scanf("%d", &num);
            if(num == -1){
                break;
            }
            if(num > 0){
                nposit++;
            }
            if(num < -1){
                continue;
            }
            if(num % 7 == 0){
                h++;
                m7=m7+num;
            }
            if(num % 5 == 0 && num % 3 == 0){
                count35++;
                p=p*num;
            }
        }
                        
        printf("%d ", nposit);
        if(h==0){
            printf("0.000000");
        }else{
            float div7=(float)m7/h;
            printf("%.6f ", div7);
        }
        if(count35 == 0){
            printf("1 ");
        }else{
            printf("%d", p);
        }
    }