#include "s_matrix.h"
#include <hardware/gpio.h>
#include <stdlib.h>

#define ROWS 4
#define COLS 3
const u8 ROW_GPIOS[ROWS] = {2, 3, 4, 5};
const u8 COL_GPIOS[COLS] = {6, 7, 8};

u8 row(u8 idx) { return idx / COLS; }

u8 col(u8 idx) { return idx % COLS; }

void put(s_matrix *s_m, u8 idx, bool b) {
  gpio_put(s_m->row_cache[idx], b);
  gpio_put(s_m->col_cache[idx], b);
}

void off(s_matrix *s_m, u8 idx) { put(s_m, idx, false); }

void on(s_matrix *s_m, u8 idx) { put(s_m, idx, true); }

void s_matrix_init(s_matrix *s_m) {
  for (int i = 0; i < ROWS; i++) {
    gpio_init(ROW_GPIOS[i]);
    gpio_set_dir(ROW_GPIOS[i], true); // set as output
    gpio_put(ROW_GPIOS[i], false);
  }
  for (int i = 0; i < COLS; i++) {
    gpio_init(COL_GPIOS[i]);
    gpio_set_dir(COL_GPIOS[i], true); // set as output
    gpio_put(COL_GPIOS[i], false);
  }
  s_m->col_cache = malloc(sizeof(u8) * ROWS * COLS);
  s_m->row_cache = malloc(sizeof(u8) * ROWS * COLS);
  for (int i = 0; i < ROWS * COLS; i++) {
    s_m->row_cache[i] = ROW_GPIOS[row(i)];
    s_m->col_cache[i] = COL_GPIOS[col(i)];
  }
  s_m->sel = 0;
  on(s_m, 0);
}

void s_matrix_select(s_matrix *s_m, u8 sel_idx) {
  off(s_m, s_m->sel);
  on(s_m, sel_idx);
  s_m->sel = sel_idx;
}

void s_matrix_free(s_matrix s_m) {
  free(s_m.col_cache);
  free(s_m.row_cache);
}
