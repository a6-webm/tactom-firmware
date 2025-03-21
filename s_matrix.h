typedef unsigned char u8;
typedef struct s_matrix {
  u8 sel;
  u8* row_cache;
  u8* col_cache;
} s_matrix;

void s_matrix_init(s_matrix *s_m);

void s_matrix_select(s_matrix *s_m, u8 sel_idx);

void s_matrix_free(s_matrix s_m);
