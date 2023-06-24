#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 21

int dim, n_threads;
int thread_id[N], group[N], path_s[N];
int path[N][2 * N][3];

// Mutex for Operations
pthread_mutex_t lock[N][N];
// Condition for checking again
pthread_cond_t cond[N][N];

// Which group is in each position and how many
int occupied[N][N][2];

void passa_tempo(int tid, int decimos)
{
    struct timespec zzz;

    zzz.tv_sec  = decimos/10;
    zzz.tv_nsec = (decimos%10) * 100L * 1000000L; 

    printf("PTa(%d,%d)\n",tid,decimos);
    nanosleep(&zzz,NULL);
    printf("PTb(%d,%d)\n",tid,decimos);
}

// Position and Group
void enter(int x, int y, int g){
    while(occupied[x][y][0] != g && occupied[x][y][0] != -1)
        pthread_cond_wait(&cond[x][y], &lock[x][y]);
    if(occupied[x][y][0] != g){
        occupied[x][y][0] = g;
        occupied[x][y][1] = 1;
    }
    else
        occupied[x][y][1]++;
}

void exits(int x, int y){
    if(occupied[x][y][1] == 1)
        occupied[x][y][0] = -1;
    else
        occupied[x][y][1]--;
    pthread_cond_signal(&cond[x][y]);
}

void *walk(void *threadid)
{
    int t;
    t = (int)threadid;
    for(int i = 0; i < path_s[t]; i++){
        // Get Position
        int x = path[t][i][0];
        int y = path[t][i][1];
        // Get Wait Time
        int w = path[t][i][2];

        pthread_mutex_lock(&lock[x][y]);
        // Enter
        enter(x, y, group[t]);
        // Exit
        if(i > 0)
            exits(x, y);
        // Wait
        passa_tempo(thread_id[t], w);
        pthread_mutex_unlock(&lock[x][y]);
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
    pthread_t threads[N];
    // Initialize Matrix
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            occupied[i][j][0] = -1;

    // Reading Grid Size and Number of Threads 
    scanf("%d %d", &dim, &n_threads);
    
    // Reading threads
    for(int t = 0; t < n_threads; t++){
        scanf("%d %d %d", &thread_id[t], &group[t], &path_s[t]);
        for(int j = 0; j < path_s[t]; j++)
            scanf("%d %d %d", &path[t][j][0], &path[t][j][1], &path[t][j][2]);
    }

    // Creating threads
    int rc;
    for(int t = 0; t < n_threads; t++){
        rc = pthread_create(&threads[t], NULL, walk, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}