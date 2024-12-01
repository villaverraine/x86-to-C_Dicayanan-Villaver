#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

extern void imgCvtGrayIntToDouble(double *output, int *input, int total_elements);

void imgCvtGrayIntToDouble_C(double *output, int *input, int total_elements) {
    const double scale = 1.0 / 255.0;
    int i;
    for (i = 0; i < total_elements; i++) {
        output[i] = input[i] * scale; 
    }
}

int main() {
	int rows;
	int cols;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of columns: ");
    scanf("%d", &cols);
    
    int *input = (int *)malloc(rows * cols * sizeof(int));
    double *output_asm = (double *)malloc(rows * cols * sizeof(double));
    double *output_c = (double *)malloc(rows * cols * sizeof(double));
    srand(time(NULL));

    int i; int j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            input[i * cols + j] = rand() % 256;
        }
    }

    // Total elements
    int total_elements = rows * cols;

    // ASM timer
    struct timespec begin_asm, end_asm;
    clock_gettime(CLOCK_MONOTONIC, &begin_asm);
    imgCvtGrayIntToDouble(output_asm, input, total_elements);
    clock_gettime(CLOCK_MONOTONIC, &end_asm);
    double execTime_asm = (end_asm.tv_sec - begin_asm.tv_sec) * 1000.0 + (end_asm.tv_nsec - begin_asm.tv_nsec) / 1000000.0;

    // C timer
    struct timespec begin_C, end_C;
    clock_gettime(CLOCK_MONOTONIC, &begin_C);
    imgCvtGrayIntToDouble_C(output_c, input, total_elements);
    clock_gettime(CLOCK_MONOTONIC, &end_C);
    double execTime_C = (end_C.tv_sec - begin_C.tv_sec) * 1000.0 + (end_C.tv_nsec - begin_C.tv_nsec) / 1000000.0;

    // validation for entire result vector
    // equality check for float values accounting for precision loss
    // https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
    int are_equal = 1;
    for (i = 0; i < total_elements; i++) {
        if (fabs(output_asm[i] - output_c[i]) > 1e-9) {
            are_equal = 0;
            break;
        }
    }
    
//    printf("Integer Greyscale:\n");
//    for (i = 0; i < rows; i++) {
//    	for (j = 0; j < cols; j++){
//    		 printf("%6d ", input[i * cols + j]);
// 		}
// 		printf("\n");
//    }

//    printf("Double Greyscale:\n");
// 		for (i = 0; i < rows; i++) {
//    	for (j = 0; j < cols; j++){
//    		printf("%6.2lf ", output_asm[i * cols + j]);
// 		}
// 		printf("\n");
//    }

    printf("Assembly function time: %lf ms\n", execTime_asm);
    printf("C function time: %lf ms\n", execTime_C);
    printf("Outputs are %s\n", are_equal ? "equal" : "not equal");

    // Clean up
    free(input);
    free(output_asm);
    free(output_c);

    return 0;
}

