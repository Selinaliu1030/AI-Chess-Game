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
  auto actions = state->legal_actions;
  Move ret;
  int cnt = -1e9;
  for(auto nxt: actions)
  {
    int tmp = DFS(state->next_state(nxt), depth, -1e9, 1e9, 0);
    if(tmp > cnt)
    {
      cnt = tmp;
      ret = nxt;
    }
  }
  return ret;
}
int AB::DFS(State* cur, int depth, int alpha, int beta, bool max_player)
{
  if(!cur->legal_actions.size())
    return cur->evaluate();
  auto actions = cur->legal_actions;
  if(depth == 0)
    return cur->evaluate();
  int value;
  if(max_player)
  {
    value = -1e9;
    for(auto nxt: actions)
    {
      int tmp = DFS(cur->next_state(nxt), depth-1, alpha, beta, 0);
      if(tmp > value)
        value = tmp;
      if(value > alpha)
        alpha = value;
      if(alpha >= beta)
        break;
    }
    cur->value = value;
    return value;
  }
  else
  {
    value = 1e9;
    for(auto nxt: actions)
    {
      int tmp = DFS(cur->next_state(nxt), depth-1, alpha, beta, 1);
      if(tmp < value)
        value = tmp;
      if(value < beta)
        beta = value;
      if(alpha >= beta)
        break;
    }
    cur->value = value;
    return value;
  }
}