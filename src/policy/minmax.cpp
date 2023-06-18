#include <cstdlib>

#include "../state/state.hpp"
#include "./minmax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minmax::get_move(State *state, int depth){
  DFS(state, depth);
  state->legal_actions.push_back(state->best_nxt_move);
  return state->best_nxt_move;
}
int Minmax::DFS(State* cur, int depth)
{
  if(depth == 0)
    return cur->evaluate();
  auto actions = cur->legal_actions;
  int best_state_max = 0, best_state_min = 1e9;
  for(auto nxt: actions)
  {
    int cnt = DFS(cur->next_state(nxt), depth-1);
    if(!cur->player && cnt > best_state_max)//me
    {
      best_state_max = cnt;
      cur->best_nxt_move = nxt;
    }
    if(cur->player && cnt < best_state_min)//opp
    {
      best_state_min = cnt;
      cur->best_nxt_move = nxt;
    }
  }
  if(!cur->player)//me
    return best_state_max;
  return best_state_min;
}