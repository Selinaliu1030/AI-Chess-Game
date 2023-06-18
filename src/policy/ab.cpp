#include <cstdlib>

#include "../state/state.hpp"
#include "./ab.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move AB::get_move(State *state, int depth){
  DFS(state, depth, -1e9, 1e9);
  //state->legal_actions.push_back(state->best_nxt_move);
  return state->best_nxt_move;
}
int AB::DFS(State* cur, int depth, int alpha, int beta)
{
  if(depth == 0)
    return cur->evaluate();

  auto actions = cur->legal_actions;
  cur->alpha = alpha;
  cur->beta = beta;
  for(auto nxt: actions)
  {
    int cnt = DFS(cur->next_state(nxt), depth-1, cur->alpha, cur->beta);
    if(!cur->player && cnt > cur->alpha)//me
    {
      cur->alpha = cnt;
      cur->best_nxt_move = nxt;
      if(cur->alpha > cur->beta)
        return cnt;
    }
    if(cur->player && cnt < cur->beta)//opp
    {
      cur->beta = cnt;
      cur->best_nxt_move = nxt;
      if(cur->alpha > cur->beta)
        return cnt;
    }
  }
  if(!cur->player)//me
    return cur->alpha;
  return cur->beta;
}