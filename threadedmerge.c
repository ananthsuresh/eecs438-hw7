// Chris Fietkiewicz. Merge sort, based on sample code
// from http://www.zentut.com/c-tutorial/c-merge-sort/
// Bug fixed on March 25 (line 76).
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>
 
void merge(int* a, int* tmp, int left, int mid, int right);
void msort(int* a, int* tmp, int left, int right);
void display(int* a,const int size);
 
int main(int argc, char *argv[]) {
    const int N = atoi(argv[1]);
    const int P = atoi(argv[2]);

	int* a = malloc(sizeof(int) * N);
	int* tmp = malloc(sizeof(int) * N);
	int i;
    for (i = 0; i < N; i++)
		a[i] = N - i;
    // printf("Array before sorting:\n");
    // display(a,N);
    omp_set_num_threads(P);
    struct timeval start_time, stop_time, elapsed_time;  // timers
    gettimeofday(&start_time,NULL); // Unix timer
    int tid;

    #pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        int start = tid * (N/P);
        int end = ((tid + 1) * (N/P)) - 1;
        msort(a, tmp, start, end);  
    }

    int j;
    int right;
    int split;
    for(j = 2; j <= P; j++){
        right = (j * (N/P)) - 1;
        split = (j-1) * (N/P);
        merge(a,tmp,0,split,right);
    }
    
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
    printf("%f seconds\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0);
    
    // printf("Array after sorting:\n");
    // display(a,N);
	free(a);
	free(tmp);
    return 0;
}


// Recursive sort
void msort(int* a, int* tmp, int left, int right) {
    int mid;
    if (right > left) {
        mid = (right + left) / 2;
        msort(a, tmp, left, mid);
        msort(a, tmp, mid + 1, right);
        merge(a, tmp, left, mid + 1, right);
    }
}
 
// Merge two subarrays
void merge(int* a, int* tmp, int left, int mid, int right) {
    int i, left_end, count, tmp_pos;
    left_end = mid - 1;
    tmp_pos = left;
    count = right - left + 1;
 
	// Main merge
    while ((left <= left_end) && (mid <= right)) {
        if (a[left] <= a[mid]) {
            tmp[tmp_pos] = a[left];
            tmp_pos++;
            left++;
        } else {
            tmp[tmp_pos] = a[mid];
            tmp_pos++;
            mid++;
        }
    }
 
	// Copy remainder of left
    while (left <= left_end) {
        tmp[tmp_pos] = a[left];
        left++;
        tmp_pos++;
    }

	// Copy remainder of right
    while (mid <= right) {
        tmp[tmp_pos] = a[mid];
        mid++;
        tmp_pos++;
    }
 
	// Copy temp array back to original
    for (i = 0; i < count; i++) {
        a[right] = tmp[right];
        right--;
    }
}

// Utility for printing
void display(int* a, const int size) {
    int i;
    for(i = 0; i < size; i++)
        printf("%d ",a[i]);
 
    printf("\n");
}