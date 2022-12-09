  #include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "queue.hpp"

/**
 * @brief Game structure maintains resources to handle a single game
 */
typedef struct Game {
  Queue* queue;

  /**
   * N stores the total possible number of players in the game
   * held stores the count of numbers held by sleeping players
   * active is a boolean signaling if the game is active
   * scores is an array containing the score of each player
   */
  int N, held, active, *scores;

  /** mutex to limit game resource access to one player or dealer at a time */
  pthread_mutex_t* mutex;
} Game;

/**
 * @brief Initializes a Game struct and allocates necessary memory
 * @param g is a pointer to the Game to initialize
 * @param N is the number of players the game
 */
void game_init(Game* g, int N);

/**
 * @brief Uninitializes a Game and deallocates its contents
 * @param g is a pointer to the Game to exit
 */
void game_exit(Game* g);

/**
 * @brief Starts and deals numbers to a game until it finishes
 * @param g is a pointer to the Game
 * @param T is the count of numbers to generate and deal
 */
void game_play(Game* g, int T);