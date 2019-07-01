#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

void find_the_median(int A[], int n){
    if(n == 1) return;
    else if(n <= 6){
        int i,j;
        for(i = n-1; j < i; i--){
            for(j = 0; j < i; j++){
                if(A[j] > A[j+1]) swap(A+j, A+j+1);
            }
        }
        swap(A, A+(n+1)/2);
    }
    else{
        int k,l,m;
        k = n / 5;
        for(l = 0; l < 4; l++){
            find_the_median(A + k*l, k);
            swap(A + l, A + k*l);
        }
        find_the_median(A + 4*k, n - 4*k);
        swap(A + 4, A + 4*k);
        find_the_median(A, 5);
    }
}

int quick_select(int A[], int n, int k){
  int i, j, pivot;


  find_the_median(A, n);
  pivot = A[0];
  for(i = j = 1; i < n; i++){
    if(A[i] <= pivot){
      swap(A+i, A+j);
      j++;
    }
  }

  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
