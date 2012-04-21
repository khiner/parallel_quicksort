/* File: qsort_seq.c (Jingke Li for CS415/515)
**
** Quicksort algorithm (Sequential version).
**
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MIN_SIZE 10 

int *array = NULL;

/* Swap two array elements 
 */
void swap(int a, int b)
{
    if (a == b) return;
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

/* Bubble sort for the base cases
 */
void bubble_sort(int low, int high)
{
    if (low > high) return;
    int i, j;
    for (i = low; i <= high; i++)
        for (j = i+1; j <= high; j++) 
            if (array[i] > array[j])
                swap(i, j);
}

/* Partition the array into two halves and return
 * the middle index
 */
int partition(int low, int high)
{
    /* Use the lowest element as pivot */
    int pivot = array[low], middle = low, i;
 
    swap(low, high);
    for(i=low; i<high; i++) {
        if(array[i] < pivot) {
            swap(i, middle);
            middle++;
        }
    }
    swap(high, middle);
  
    return middle;
}
 
/* Quicksort the array 
 */
void quicksort(int low, int high)
{
    if (high - low < MIN_SIZE) {
        bubble_sort(low, high);
        return;
    }
    int middle = partition(low, high);
    quicksort(low, middle-1);
    quicksort(middle+1, high);
}
 
/* Main routine for testing quicksort
 */
int main(int argc, char **argv)
{
    int N, i, j;
    char ans;
  
    /* check command line first */
    if (argc < 2) {
        printf ("Usage : qsort_seq <array_size>\n");
        exit(0);
    }
    if ((N=atoi(argv[1])) < 2) {
        printf ("<array_size> must be greater than 2\n");
        exit(0);
    }

    /* init an array with values 1. N-1 */
    array = (int *) malloc(sizeof(int) * N);
    for (i=0; i<N; i++)
        array[i] = i+1;

    /* randomly permute array elements */
    srand(time(NULL));
    for (i=0; i<N; i++) {
        j = (rand()*1./RAND_MAX)*(N-1);
        swap(i, j);
    }
#ifdef DEBUG
    printf("Want to see the input array (y/n)? ");
    scanf("%c", &ans);
    if (ans=='y') {
        for (i=0; i<N; i++)
            printf("%d, ", array[i]);
        printf("\n");
    }
#endif /* DEBUG */

    quicksort(0, N-1);

    //#ifdef DEBUG
    /* Verify the result */
    for (i=0; i<N-1; i++) {
        if (array[i]>array[i+1]) {
            printf("Verification failed, array[%d]=%d, array[%d]=%d\n",
                   i, array[i], i+1, array[i+1]);
            return;
        }
    }
    printf("Sorting result verified!\n");
    //#endif /* DEBUG */
}
