#include "numbergame.hpp"

void game_init(Game* g, int N) {
  g->queue = new Queue(NULL, 2 * N + 1);
  g->N = N;
  g->held = 0;
  g->active = 0;
  g->scores = (int*)malloc(N * sizeof(int));
  for (int i = 0; i < N; ++i) {
    g->scores[i] = -1;
  }
  g->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(g->mutex, NULL);
}

void game_exit(Game* g) {
  delete g->queue;
  pthread_mutex_destroy(g->mutex);
  free(g->mutex);
}

void game_play(Game* g, int T) {
  int num;

  // Signal the game to start
  g->active = 1;

  // Generate T numbers
  for (int i = 0; i < T;) {
    pthread_mutex_lock(g->mutex); // Begin critical section: Dealer push
    if (g->queue->size() <= g->N) {
      num = (rand() % 40) + 1;
      printf("Dealer is pushing %d to the queue.\n", num);
      g->queue->push(num);
      g->queue->print();
      ++i;
    }
    pthread_mutex_unlock(g->mutex); // End critical section
  }

  // Wait until no numbers remain in play before ending game
  while (g->active) {
    pthread_mutex_lock(g->mutex); // Begin critical section: Count numbers
    g->active = g->held + g->queue->size();
    pthread_mutex_unlock(g->mutex); // End critical section
  }
}