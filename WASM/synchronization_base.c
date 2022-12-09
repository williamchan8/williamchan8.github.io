#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "numbergame.h"
#include "queue.h"

#define MS_TO_NS 1000000

/**
 * @brief Player function to be run in a thread
 * 
 * @param param is the void pointer passed to the thread
 */
void* player(void* param) {
  Game* game = (Game*)param;
  int N = game->N;
  int k;
  struct timespec request = {1, 0};
  int x;
  int points;
  int value;

  pthread_mutex_lock(game->mutex); // Begin critical section: Take slot
  for (k = 0; game->scores[k] != -1; k++);
  game->scores[k] = 0;
  pthread_mutex_unlock(game->mutex); // End critical section

  // Wait for game start signal
  while(!game->active);

  // Play game while there are numbers in play
  while (game->active) {
    pthread_mutex_lock(game->mutex); // Begin critical section: Player pop
    if (queue_size(game->queue)) {
      ++game->held;
      x = queue_pop(game->queue);
      printf("Thread %d popped %d from the queue. ", k, x);
      if (x <= N) {
        printf("Player has scored. Thread %d does not need to push.\n", k);
        points = x;
        value = -1;
      }
      else if ((x % N == k) || (x % N == (k + 1) % N)) {
        printf("Player has scored. Thread %d needs to push 3 * x / 5.\n", k);
        points = 2 * x / 5;
        value = x - points;
      }
      else {
        printf("Player did not score. Thread %d needs to push x - 2.\n", k);
        points = 0;
        value = x - 2;
      }
      queue_print(game->queue);
      pthread_mutex_unlock(game->mutex); // End critical section: Player pop

      request.tv_nsec = x * MS_TO_NS; 
      nanosleep(&request, NULL);

      pthread_mutex_lock(game->mutex); // Begin critical section: Player push
      game->scores[k] += points;
      if (value > -1) {
        printf("Thread %d pushing %d to the queue\n", k, value);
        queue_push(game->queue, value);
        queue_print(game->queue);
      }
      --game->held;
      pthread_mutex_unlock(game->mutex); // End critical section
    }
    else {
      pthread_mutex_unlock(game->mutex); // End critical section: Player pop
    }
  }

  pthread_exit(NULL);
}

/**
 * @brief Main function, also serves as the dealer for the game
 */
int main(int argc, char* argv[]){
  int N, T;

  if (argc > 2) {
    N = atoi(argv[1]);
    T = atoi(argv[2]);
  }
  else {
    return -1;
  }

  srand(time(NULL));
  Game game;
  game_init(&game, N);
  pthread_t threads[N];
  int num;

  // Create all threads
  printf("Number of threads : %d   |   Number of objects: %d\n\n", N, T);
  for (int i = 0; i < N; ++i) {
    printf("Thread %d started\n", i);
    pthread_create(threads + i, NULL, player, (void*)&game);
  }

  // Signal game to start and generate numbers
  game_play(&game, T);

  // Terminate threads and print final score for each player
  for (int i = 0; i < N; ++i) {
    pthread_join(threads[i], NULL);
    printf("Final score for player %d : %d\n", i, game.scores[i]);
  }

  game_exit(&game);
  return 0;
}