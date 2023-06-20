#include "student_predictor.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

your_own::your_own() {
  int idx_bit = 14;
  num_predictor_entry = pow(2, idx_bit);
  pred_arr = new int[num_predictor_entry];
  for (int i = 0; i < num_predictor_entry; i++)
  {
      pred_arr[i] = 4;
  }
};
your_own::~your_own() {
  if (pred_arr != NULL) delete[] pred_arr;
}
/* warning!!! Don't change argument of these function   */
int your_own::get_pred(int pc) {
  int idx = pc % num_predictor_entry;
  int prediction = pred_arr[idx];
  if (prediction >= 4)
  {
      return 1;
  }
  else
  {
      return 0;
  }
}
void your_own::update(int pc, int res) {
  int idx = pc % num_predictor_entry;
  int *arr = pred_arr;
  if (res == 1) {   // taken
      int temp = arr[idx];
      if (temp == 7)
      {
          // stay
      }
      else
      {
          arr[idx] = ++temp;
      }
  } else {  // not taken
      int temp = arr[idx];
      if (temp == 0)
      {
          // stay
      }
      else
      {
          arr[idx] = --temp;
      }
  }
}
