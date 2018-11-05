#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 2
#define K 2
#define N 2
#define NUM_THREADS 10

int A[M][K] = {{5, 4}, {3, 4}};
int B[K][N] = {{5, 9}, {3, 7}};
int S[M][N];

struct v
{
    int i; /* row */
    int j; /* column */
};

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{

    int i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < M; j++){

            //Assign a row and column for each thread
            struct v *data = (struct v *)malloc(sizeof(struct v));
            data->i = i;
            data->j = j;
            /* Now create the thread passing it data as a parameter */
            pthread_t tid;       //Thread ID
            pthread_attr_t attr; //Set of thread attributes
            //Get the default attributes
            pthread_attr_init(&attr);
            //Create the thread
            pthread_create(&tid, &attr, runner, data);
            //Make sure the parent waits for all thread to complete
            pthread_join(tid, NULL);
        }
    }

    //Print out the resulting matrix
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", S[i][j]);
        }
        printf("\n");
    }
}

//The thread will begin control in this function
void *runner(void *param)
{
    struct v *data = param; // the structure that holds our data

    //Row multiplied by column
    //assign the sum to its coordinate

    S[data->i][data->j] = A[data->i][data->j] + B[data->i][data->j];;

    //Exit the thread
    pthread_exit(0);
}