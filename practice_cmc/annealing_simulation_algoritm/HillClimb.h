#ifndef HILLCLIMB_H
#define HILLCLIMB_H

#include <vector>
#include <utility>
#include <random>

using std::vector;
using State = vector<int>;

class HillClimb
{
private:
  double **distance_matrix;
  int parallel_tracks;
  int sessions_in_track;
  int works_in_session;
  double trade_of_coefficient;

  vector<vector<double>> session_distance_matrix;

  std::default_random_engine rng;
  std::uniform_int_distribution<std::default_random_engine::result_type> dist;

  void construct_session_matrix(State);

  // Initialization Schemes
  State random_initialize();
  State greedy_initialize();
  std::pair<int, int> next_state();

  std::vector<std::vector<int>> state_to_sessions(State);
  double score(State);

public:
  // конструктор
  HillClimb(double **, int, int, int, int);

  // график идет наверх
  State hill_climb(bool, double, const int);

  // переход от одного состояния в другое
  double score_increment(int, int, State) const;

  //обновление состояния
  void update_state(int, int, State &);
};

#endif