#include <stdio.h>
 int main(){
    int v1[20], m, M, s=0, no=0;
    float med, v2[20];
    for (int i=0 ; i<20 ; i++)
    {
        scanf("%d", &v1[i]);
        if(v1[i]!=0){
            no=no+1;
        }
        s=s+v1[i];
    }
    m=v1[0];
    M=v1[0];
    
    for (int i=0 ; i<20 ; i++){
        if(v1[i] < m){
            m=v1[i];
        }if(v1[i] > M){
            M=v1[i];
        }
    }
    med=(float)s/no;
    for (int i = 0 ; i < 20 ; i++) {
        if (M != m) {
            v2[i] = (float)(v1[i] - m) / (M - m);
        } else {
            v2[i] = 0;
        }
    }
    printf("%d ", M);
    printf("%d\n", m);
    printf("%.3f\n", med);
    for(int i = 0 ; i < 20 ; i++){
        printf("%.3f ", v2[i]);
    }
    return 0;
 }