#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>


#define BLOCK_SIZE 32

void print_matrix_sample(double *M,int ROWS, int COLS)
{
	int i, j;
	for (i = 10; i >= 0; i--)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%.2f\t", M[j * COLS + i]);
		}
		printf("\n");
	}
}


void init_grid_U(double * grid, double * grid_prev, int ROWS, int COLS)
{
#pragma omp parallel
        {
        #pragma omp single
                {
                        printf("Number of OMP Threads = %d \n",omp_get_num_threads());
                }
        #pragma omp for
                for (int i = 0; i < ROWS; i++) {
                        for (int j = 0; j < COLS; j++) {
                                grid    [i * (COLS) + j] = 0.0;
                                grid_prev[i * (COLS) + j] = 0.0;

                                // --- Boundary condition on the left, right and upper walls. The boundary condition on the lower wall is vanishing temperature
                                if (i == (ROWS - 1) || i == 0 || j == (COLS - 1))
                                {
                                        grid    [i * (COLS) + j] = 20.0;
                                        grid_prev[i * (COLS) + j] = 20.0;
                                }
                        }
                }
        }
}


__global__ void compute_gridpoints_GPU(double * grid, double * grid_prev, const int ROWS, const int COLS)
{
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	int j = blockDim.y * blockIdx.y + threadIdx.y;

	if (i < ROWS - 1 && j < COLS - 1 && i > 0 && j > 0)
	{
		grid[j * COLS + i] = (grid[j * COLS + (i - 1)] + grid[j * COLS + (i + 1)] + grid[(j - 1) * COLS + i] + grid[(j + 1) * COLS + i] ) * 0.25;

	}
}


int main()
{

	const int ROWS         = 10000+2;                           // --- Grid size is N x N
	const int COLS         = 10000+2;                           // --- Grid size is N x N
	const int MAX_ITER  = 1000;                         // --- Maximum number of iterations

	struct timeval start_time_CPU, stop_time_CPU, elapsed_time_CPU;
	struct timeval start_time_GPU, stop_time_GPU, elapsed_time_GPU;



	// --- Allocating host memory variables
	double *h_grid             = (double *)malloc( (ROWS) * (COLS) * sizeof(double));
	double *h_grid_prev         = (double *)malloc( (ROWS) * (COLS) * sizeof(double));

	// --- Allocating device memory variables
	double *d_grid;            
	cudaMalloc(&d_grid, (ROWS) * (COLS) * sizeof(double));
	double *d_grid_prev;        
	cudaMalloc(&d_grid_prev, (ROWS) * (COLS) * sizeof(double));

	// --- Host array initialization

        gettimeofday(&start_time_CPU,NULL);
	init_grid_U(h_grid, h_grid_prev, ROWS, COLS);
        gettimeofday(&stop_time_CPU,NULL);
	print_matrix_sample(h_grid,ROWS,COLS);
	cudaMemcpy(d_grid,       h_grid,        ROWS * COLS * sizeof(double), cudaMemcpyHostToDevice);
	cudaMemcpy(d_grid_prev,       h_grid_prev,        ROWS * COLS * sizeof(double), cudaMemcpyHostToDevice);




	// --- Device iterations
	dim3 DimBlock(BLOCK_SIZE, BLOCK_SIZE);
	dim3 DimGrid((COLS+DimBlock.x-1)/DimBlock.x,(ROWS+DimBlock.y-1)/DimBlock.y);
	printf("DimBlock.x = %d DimBlock.y = %d\n",DimBlock.x,DimBlock.y);
	printf("DimGrid.x = %d DimGrid.y = %d\n",DimGrid.x,DimGrid.y);


        gettimeofday(&start_time_GPU,NULL);
	for (int h = 0; h < MAX_ITER; h++)
	{
		compute_gridpoints_GPU<<<DimGrid, DimBlock>>>(d_grid, d_grid_prev, ROWS,COLS);

		// --- Pointers swap
		//temp = d_grid;
		//d_grid = d_grid_prev;
		//d_grid_prev = temp;
	}
        gettimeofday(&stop_time_GPU,NULL);

	cudaMemcpy(h_grid, d_grid, (ROWS) * (COLS) * sizeof(double), cudaMemcpyDeviceToHost);
	print_matrix_sample(h_grid,ROWS,COLS);
        timersub(&stop_time_CPU, &start_time_CPU, &elapsed_time_CPU);
        timersub(&stop_time_GPU, &start_time_GPU, &elapsed_time_GPU);

        printf("CPU Time: %f   GPU Time: %f \n", elapsed_time_CPU.tv_sec+elapsed_time_CPU.tv_usec/1000000.0, elapsed_time_GPU.tv_sec+elapsed_time_GPU.tv_usec/1000000.0);

	free(h_grid);
	free(h_grid_prev);
	cudaFree(d_grid);
	cudaFree(d_grid_prev);

	return 0;
}
