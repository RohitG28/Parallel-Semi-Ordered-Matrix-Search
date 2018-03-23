/** Commands

gcc -o semi_ordered_matrix_search -fopenmp semi_ordered_matrix_search.c
./semi_ordered_matrix_search 
export OMP_NUM_THREADS=3

**/


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//Function declaration
void search(int rows, int columns, long int** matrix, int row_l, int row_r, int col_l, int col_r, long int x, int* i, int* j);

int main (int argc, char *argv[]) 
{
	int nthreads;

	int i = -1, j = -1;

	long int K = 99999999;

	int N = 40000;

	
	/**
	int matrix[5][5] = {	{0, 6, 8, 9, 11}, 
				{20, 22, 28, 29, 31}, 
				{36, 38, 50, 61, 63}, 
				{64, 66, 100, 122, 128}, 
				{68, 70, 101, 123, 129}};
	**/

	
	//Generate matrix
	long int** matrix = (long int**)malloc(N*sizeof(long int*));

	//double start_time = omp_get_wtime();


	//Create a semi-ordered matrix
	//#pragma omp parallel for
	for(int x = 0;x<N;x++){
		matrix[x] = (long int*)malloc(N*sizeof(long int));

		for(int y = 0;y<N;y++){
			matrix[x][y] = (x*(long int)N)+(y+1);
			//printf("%d\n",matrix[x][y]);
		}
	}

	
	double start_time = omp_get_wtime();

	/* Fork a team of threads giving them their own copies of variables */
	#pragma omp parallel
	{	

		#pragma omp single
		{
			nthreads = omp_get_num_threads();
			printf("No of threads: %d\n",nthreads );
			search(N, N, matrix, 0, N-1, 0, N-1, K, &i, &j);
		}			
		
	}  /* All threads join master thread and disband */

	
	double time = omp_get_wtime() - start_time;

	printf("%d %d\n",i,j);

	printf("Time: %lf\n", time);


	return 0;

}


void search(int rows, int columns, long int** matrix, int row_l, int row_r, int col_l, int col_r, long int x, int* i, int* j){

	/**
	int tid = omp_get_thread_num();
    printf("Hello world from omp thread %d\n", tid);
    **/

	if(row_l>row_r || col_l>col_r)
		return;
		
	int row_mid = (row_l+row_r)/2;
	int col_mid = (col_l+col_r)/2;


	int value = matrix[row_mid][col_mid];

	//If element found
	if(value==x)
	{
		*i = row_mid;
		*j = col_mid;
		return;
	}

	//Divide and conquer
	if(value>x)
	{
		#pragma omp task untied
		search(rows,columns,matrix, row_l, row_mid-1, col_l, col_r, x, i,j);

		#pragma omp task untied
		search(rows,columns,matrix, row_mid, row_r, col_l, col_mid-1, x,i,j);
	}

	else
	{
		#pragma omp task untied
		search(rows,columns,matrix, row_l, row_r, col_mid+1, col_r, x,i,j);

		#pragma omp task untied
		search(rows,columns,matrix, row_mid+1, row_r, col_l, col_mid, x,i,j);
	}

	return;
}