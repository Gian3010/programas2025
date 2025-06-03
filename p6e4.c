#include <stdio.h>
 
#define MAX_SIZE 30
 
int main(){
  int A[MAX_SIZE][MAX_SIZE], B[MAX_SIZE][MAX_SIZE], C[MAX_SIZE][MAX_SIZE] = {0}, D[MAX_SIZE][MAX_SIZE] = {0};
  int rowsA, colsA, rowsB, colsB;
 
  scanf("%d %d", &rowsA, &colsA);
  scanf("%d %d", &rowsB, &colsB);
 
  if(rowsA > 30 || colsA > 30 || rowsA <= 0 || colsA <= 0){
    printf("ERRO");
    return 1;
  }
 
  if(rowsB > 30 || colsB > 30 || rowsB <= 0 || colsB <= 0){
    printf("ERRO");
    return 1;
  }
 
  if(colsA != rowsB){
    printf("ERRO");
    return 1;
  }
  
  for(int i = 0; i < rowsA; i++){
    for(int j = 0; j < colsA; j++){
      scanf("%d", &A[i][j]);
    }
  }
  printf("\n");
 
  for(int i = 0; i < rowsB; i++){
    for(int j = 0; j < colsB; j++){
      scanf("%d", &B[i][j]);
    }
  }
  printf("\n");
 
  
  for(int i = 0; i < rowsA; i++){
    for(int j = 0; j < colsA; j++){
      for(int k = 0; k < colsA; k++){
        C[i][j] += A[i][k] * A[k][j];
      }
    }
  }
 
  for(int i = 0; i < rowsA; i++){
    for(int j = 0; j < colsB; j++){
      for(int k = 0; k < colsA; k++){
        D[i][j] += C[i][k] * B[k][j];
      }
    }
  }
 
  for (int i = 0; i < rowsA; i++){
    for (int j = 0; j < colsB; j++)
    {
      printf("%d ", D[i][j]);
    }
   printf("\n");
  }
 
  return 0;
}