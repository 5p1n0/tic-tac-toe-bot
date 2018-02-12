#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"player.h"

static unsigned int M = 0,N = 0,K = 0,C = 0;
static unsigned short **BOARD = NULL;

static unsigned short **ushort_matrix_alloc (int row, int col)
{
    unsigned short **m = NULL;
    unsigned int i;

    if ((m = (unsigned short **)calloc (row, sizeof(unsigned short *))) != NULL)
    {
        if((m[0] = (unsigned short *)calloc(row*col,sizeof(unsigned short))) == NULL)
        {
            free(m);
            m = NULL;
        }
        else
        {
            for (i = 1; i < row; i++)
            {
                m[i] = &m[i - 1][col];
            }
        }
    }

    return m;
}

static void ushort_matrix_free (unsigned short **m)
{
  free(m[0]);
  free(m);
}


int setup_player (unsigned int m, unsigned int n, unsigned int k)
{
	time_t seed = time(NULL);
	M = m;
	N = n;
	K = k;
	C = M*N;
	if ((BOARD = ushort_matrix_alloc(M,N)) == NULL)
    {
        return 0;
    }

	srand(seed);
	return 1;
}

void free_player()
{
	M = N = K = 0;
	ushort_matrix_free(BOARD);
	BOARD = NULL;
}

int set_opponent_move (unsigned int i, unsigned int j)
{
	if (i >= M || j >= N)
    {
        return 0;
    }

	BOARD[i][j] = 1;
	C--;

	return 1;
}

int get_next_move(unsigned int *i, unsigned int *j)
{
	unsigned int X = rand() % C;

	for (*i = 0; *i < M; (*i)++)
    {
		for (*j = 0; *j < N; (*j)++)
        {
			if (BOARD[*i][*j] == 0)
            {
				if(X == 0)
				{
					BOARD[*i][*j] = 1;
					C--;
					return 1;
				}
                else
                {
                    X--;
                }
			}
        }
    }

	return 0;
}
