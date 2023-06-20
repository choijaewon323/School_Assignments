#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// this is simple 1-bit predictor. 
// predictor return 1(taken) when pred_arr entry set as 1.

class your_own {
 private:
  int num_predictor_entry;
  int *pred_arr;

 public:
  your_own();
  your_own(int, int);
  ~your_own();
  int get_pred(int);
  void update(int, int);
};
