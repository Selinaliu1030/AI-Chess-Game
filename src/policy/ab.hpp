#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class AB{
public:
  static Move get_move(State *state, int depth);
  static int DFS(State* cur, int depth, int alpha, int beta, bool max_player);
};