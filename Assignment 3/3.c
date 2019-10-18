#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int menu()
{
	int Choice;
	printf("\n\n\n1) Create Matrix \n");
	printf("2) Display Matrices \n");
	printf("3) Multiplcation Matrices \n");
	printf("\n Enter Choice   :  ");
	scanf("%d" , &Choice);

	return Choice;
}

void Create(int row , int column , int **Matrix_A , int **Matrix_B)
{
	Matrix_A = (int **)malloc(row * sizeof(int *));

	for (int i = 0; i < column; i++)
		Matrix_A[i] = (int *)malloc(column * sizeof(int));


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {

			printf("Enter Matrix A[%d][%d] :  " , i , j );
			scanf("%d" , &Matrix_A[i][j]);
		}
	}

	printf("\t\t\n\n\n Matrix B :   \n\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%5d", Matrix_A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	Matrix_B = (int **)malloc(row * sizeof(int *));

	for (int i = 0; i < column; i++)
		Matrix_B[i] = (int *)malloc(column * sizeof(int));


	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {

			printf("Enter Matrix_B A[%d][%d] :  " , i , j );
			scanf("%d" , &Matrix_B[i][j]);
		}
	}

	printf("\t\t\n\n\n Matrix B :   \n\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			printf("%5d", Matrix_B[i][j]);
		}
		printf("\n");
	}
}




int main(int argc, char const *argv[])
{
	int row_A = 2 , row_B = 2 , column_A = 2 ,column_B = 2 ,  **Matrix_A , **Matrix_B;
	switch(menu())
	{
		case 1:	
				// printf("Enter Row of Matrix A :  \n");
				// scanf("%d" , &row_A);

				// printf("Enter Row of Matrix A:  \n");
				// scanf("%d" , &column_A);

				// printf("Enter Row of Matrix A :  \n");
				// scanf("%d" , &row_B);

				// printf("Enter Row of Matrix A:  \n");
				// scanf("%d" , &column_B);

				if(column_A == row_B )
					Create(row_A,column_A ,Matrix_A,Matrix_B);
				else
					printf("Error! column of first matrix not equal to row of second.\n");



			break;			
	}
	
	return 0;
}