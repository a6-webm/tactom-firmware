#include "glyphs.h"

#define MS(us) (us * 1000)
#define GLYPH_DELAY MS(200)

// unindexed glyphs ------------------------------------------------------------

#define LF_GLYPH_LEN 2
const Ev LF_GLYPH[LF_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define UNKNOWN_GLYPH_LEN 2
const Ev UNKNOWN_GLYPH[UNKNOWN_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

// indexed glyphs --------------------------------------------------------------

#define SP_GLYPH_LEN 2
const Ev SP_GLYPH[SP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define EXC_GLYPH_LEN 2
const Ev EXC_GLYPH[EXC_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define SPEECH_GLYPH_LEN 2
const Ev SPEECH_GLYPH[SPEECH_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define HASH_GLYPH_LEN 2
const Ev HASH_GLYPH[HASH_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define DOLLAR_GLYPH_LEN 2
const Ev DOLLAR_GLYPH[DOLLAR_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define PERC_GLYPH_LEN 2
const Ev PERC_GLYPH[PERC_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define AMP_GLYPH_LEN 2
const Ev AMP_GLYPH[AMP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define APP_GLYPH_LEN 2
const Ev APP_GLYPH[APP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define LPAR_GLYPH_LEN 2
const Ev LPAR_GLYPH[LPAR_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define RPAR_GLYPH_LEN 2
const Ev RPAR_GLYPH[RPAR_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define AST_GLYPH_LEN 2
const Ev AST_GLYPH[AST_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define PLUS_GLYPH_LEN 2
const Ev PLUS_GLYPH[PLUS_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define COM_GLYPH_LEN 2
const Ev COM_GLYPH[COM_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define DASH_GLYPH_LEN 2
const Ev DASH_GLYPH[DASH_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define PERIOD_GLYPH_LEN 2
const Ev PERIOD_GLYPH[PERIOD_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define SLASH_GLYPH_LEN 2
const Ev SLASH_GLYPH[SLASH_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N0_GLYPH_LEN 2
const Ev N0_GLYPH[N0_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N1_GLYPH_LEN 2
const Ev N1_GLYPH[N1_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N2_GLYPH_LEN 2
const Ev N2_GLYPH[N2_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_1},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N3_GLYPH_LEN 2
const Ev N3_GLYPH[N3_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_2},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N4_GLYPH_LEN 2
const Ev N4_GLYPH[N4_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_3},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N5_GLYPH_LEN 2
const Ev N5_GLYPH[N5_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_4},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N6_GLYPH_LEN 2
const Ev N6_GLYPH[N6_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_5},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N7_GLYPH_LEN 2
const Ev N7_GLYPH[N7_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_6},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N8_GLYPH_LEN 2
const Ev N8_GLYPH[N8_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_7},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N9_GLYPH_LEN 9
const Ev N9_GLYPH[N9_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0), .ev_type = DRV_1},
    {.abs_time = MS(0), .ev_type = DRV_2},
    {.abs_time = MS(0), .ev_type = DRV_3},
    {.abs_time = MS(0), .ev_type = DRV_4},
    {.abs_time = MS(0), .ev_type = DRV_5},
    {.abs_time = MS(0), .ev_type = DRV_6},
    {.abs_time = MS(0), .ev_type = DRV_7},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define COL_GLYPH_LEN 2
const Ev COL_GLYPH[COL_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define SCOL_GLYPH_LEN 2
const Ev SCOL_GLYPH[SCOL_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define LT_GLYPH_LEN 2
const Ev LT_GLYPH[LT_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define EQ_GLYPH_LEN 2
const Ev EQ_GLYPH[EQ_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define GT_GLYPH_LEN 2
const Ev GT_GLYPH[GT_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define QMARK_GLYPH_LEN 2
const Ev QMARK_GLYPH[QMARK_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define AT_GLYPH_LEN 2
const Ev AT_GLYPH[AT_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define A_UP_GLYPH_LEN 2
const Ev A_UP_GLYPH[A_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define B_UP_GLYPH_LEN 2
const Ev B_UP_GLYPH[B_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define C_UP_GLYPH_LEN 2
const Ev C_UP_GLYPH[C_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define D_UP_GLYPH_LEN 2
const Ev D_UP_GLYPH[D_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define E_UP_GLYPH_LEN 2
const Ev E_UP_GLYPH[E_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define F_UP_GLYPH_LEN 2
const Ev F_UP_GLYPH[F_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define G_UP_GLYPH_LEN 2
const Ev G_UP_GLYPH[G_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define H_UP_GLYPH_LEN 2
const Ev H_UP_GLYPH[H_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define I_UP_GLYPH_LEN 2
const Ev I_UP_GLYPH[I_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define J_UP_GLYPH_LEN 2
const Ev J_UP_GLYPH[J_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define K_UP_GLYPH_LEN 2
const Ev K_UP_GLYPH[K_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define L_UP_GLYPH_LEN 2
const Ev L_UP_GLYPH[L_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define M_UP_GLYPH_LEN 2
const Ev M_UP_GLYPH[M_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N_UP_GLYPH_LEN 2
const Ev N_UP_GLYPH[N_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define O_UP_GLYPH_LEN 2
const Ev O_UP_GLYPH[O_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define P_UP_GLYPH_LEN 2
const Ev P_UP_GLYPH[P_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Q_UP_GLYPH_LEN 2
const Ev Q_UP_GLYPH[Q_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define R_UP_GLYPH_LEN 2
const Ev R_UP_GLYPH[R_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define S_UP_GLYPH_LEN 2
const Ev S_UP_GLYPH[S_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define T_UP_GLYPH_LEN 2
const Ev T_UP_GLYPH[T_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define U_UP_GLYPH_LEN 2
const Ev U_UP_GLYPH[U_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define V_UP_GLYPH_LEN 2
const Ev V_UP_GLYPH[V_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define W_UP_GLYPH_LEN 2
const Ev W_UP_GLYPH[W_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define X_UP_GLYPH_LEN 2
const Ev X_UP_GLYPH[X_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Y_UP_GLYPH_LEN 2
const Ev Y_UP_GLYPH[Y_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Z_UP_GLYPH_LEN 2
const Ev Z_UP_GLYPH[Z_UP_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define LBRACK_GLYPH_LEN 2
const Ev LBRACK_GLYPH[LBRACK_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define BSLASH_GLYPH_LEN 2
const Ev BSLASH_GLYPH[BSLASH_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define RBRACK_GLYPH_LEN 2
const Ev RBRACK_GLYPH[RBRACK_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define UPCAR_GLYPH_LEN 2
const Ev UPCAR_GLYPH[UPCAR_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define USCORE_GLYPH_LEN 2
const Ev USCORE_GLYPH[USCORE_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define BTICK_GLYPH_LEN 2
const Ev BTICK_GLYPH[BTICK_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define A_GLYPH_LEN 2
const Ev A_GLYPH[A_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define B_GLYPH_LEN 2
const Ev B_GLYPH[B_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define C_GLYPH_LEN 2
const Ev C_GLYPH[C_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define D_GLYPH_LEN 2
const Ev D_GLYPH[D_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define E_GLYPH_LEN 2
const Ev E_GLYPH[E_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define F_GLYPH_LEN 2
const Ev F_GLYPH[F_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define G_GLYPH_LEN 2
const Ev G_GLYPH[G_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define H_GLYPH_LEN 2
const Ev H_GLYPH[H_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define I_GLYPH_LEN 2
const Ev I_GLYPH[I_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define J_GLYPH_LEN 2
const Ev J_GLYPH[J_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define K_GLYPH_LEN 2
const Ev K_GLYPH[K_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define L_GLYPH_LEN 2
const Ev L_GLYPH[L_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define M_GLYPH_LEN 2
const Ev M_GLYPH[M_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define N_GLYPH_LEN 2
const Ev N_GLYPH[N_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define O_GLYPH_LEN 2
const Ev O_GLYPH[O_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define P_GLYPH_LEN 2
const Ev P_GLYPH[P_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Q_GLYPH_LEN 2
const Ev Q_GLYPH[Q_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define R_GLYPH_LEN 2
const Ev R_GLYPH[R_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define S_GLYPH_LEN 2
const Ev S_GLYPH[S_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define T_GLYPH_LEN 2
const Ev T_GLYPH[T_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define U_GLYPH_LEN 2
const Ev U_GLYPH[U_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define V_GLYPH_LEN 2
const Ev V_GLYPH[V_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define W_GLYPH_LEN 2
const Ev W_GLYPH[W_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define X_GLYPH_LEN 2
const Ev X_GLYPH[X_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Y_GLYPH_LEN 2
const Ev Y_GLYPH[Y_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define Z_GLYPH_LEN 2
const Ev Z_GLYPH[Z_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define LBRACE_GLYPH_LEN 2
const Ev LBRACE_GLYPH[LBRACE_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define VBAR_GLYPH_LEN 2
const Ev VBAR_GLYPH[VBAR_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define RBRACE_GLYPH_LEN 2
const Ev RBRACE_GLYPH[RBRACE_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define TILDE_GLYPH_LEN 2
const Ev TILDE_GLYPH[TILDE_GLYPH_LEN] = {
    {.abs_time = MS(0), .ev_type = DRV_0},
    {.abs_time = MS(0) + GLYPH_DELAY, .ev_type = END_GLYPH}};

#define GLYPHS_LEN 95
const int GLYPH_LENS[GLYPHS_LEN] = {
    SP_GLYPH_LEN,     EXC_GLYPH_LEN,    SPEECH_GLYPH_LEN, HASH_GLYPH_LEN,
    DOLLAR_GLYPH_LEN, PERC_GLYPH_LEN,   AMP_GLYPH_LEN,    APP_GLYPH_LEN,
    LPAR_GLYPH_LEN,   RPAR_GLYPH_LEN,   AST_GLYPH_LEN,    PLUS_GLYPH_LEN,
    COM_GLYPH_LEN,    DASH_GLYPH_LEN,   PERIOD_GLYPH_LEN, SLASH_GLYPH_LEN,
    N0_GLYPH_LEN,     N1_GLYPH_LEN,     N2_GLYPH_LEN,     N3_GLYPH_LEN,
    N4_GLYPH_LEN,     N5_GLYPH_LEN,     N6_GLYPH_LEN,     N7_GLYPH_LEN,
    N8_GLYPH_LEN,     N9_GLYPH_LEN,     COL_GLYPH_LEN,    SCOL_GLYPH_LEN,
    LT_GLYPH_LEN,     EQ_GLYPH_LEN,     GT_GLYPH_LEN,     QMARK_GLYPH_LEN,
    AT_GLYPH_LEN,     A_UP_GLYPH_LEN,   B_UP_GLYPH_LEN,   C_UP_GLYPH_LEN,
    D_UP_GLYPH_LEN,   E_UP_GLYPH_LEN,   F_UP_GLYPH_LEN,   G_UP_GLYPH_LEN,
    H_UP_GLYPH_LEN,   I_UP_GLYPH_LEN,   J_UP_GLYPH_LEN,   K_UP_GLYPH_LEN,
    L_UP_GLYPH_LEN,   M_UP_GLYPH_LEN,   N_UP_GLYPH_LEN,   O_UP_GLYPH_LEN,
    P_UP_GLYPH_LEN,   Q_UP_GLYPH_LEN,   R_UP_GLYPH_LEN,   S_UP_GLYPH_LEN,
    T_UP_GLYPH_LEN,   U_UP_GLYPH_LEN,   V_UP_GLYPH_LEN,   W_UP_GLYPH_LEN,
    X_UP_GLYPH_LEN,   Y_UP_GLYPH_LEN,   Z_UP_GLYPH_LEN,   LBRACK_GLYPH_LEN,
    BSLASH_GLYPH_LEN, RBRACK_GLYPH_LEN, UPCAR_GLYPH_LEN,  USCORE_GLYPH_LEN,
    BTICK_GLYPH_LEN,  A_GLYPH_LEN,      B_GLYPH_LEN,      C_GLYPH_LEN,
    D_GLYPH_LEN,      E_GLYPH_LEN,      F_GLYPH_LEN,      G_GLYPH_LEN,
    H_GLYPH_LEN,      I_GLYPH_LEN,      J_GLYPH_LEN,      K_GLYPH_LEN,
    L_GLYPH_LEN,      M_GLYPH_LEN,      N_GLYPH_LEN,      O_GLYPH_LEN,
    P_GLYPH_LEN,      Q_GLYPH_LEN,      R_GLYPH_LEN,      S_GLYPH_LEN,
    T_GLYPH_LEN,      U_GLYPH_LEN,      V_GLYPH_LEN,      W_GLYPH_LEN,
    X_GLYPH_LEN,      Y_GLYPH_LEN,      Z_GLYPH_LEN,      LBRACE_GLYPH_LEN,
    VBAR_GLYPH_LEN,   RBRACE_GLYPH_LEN, TILDE_GLYPH_LEN,
};

const Ev *const INDEXED_GLYPHS[GLYPHS_LEN] = {
    SP_GLYPH,     EXC_GLYPH,    SPEECH_GLYPH, HASH_GLYPH,   DOLLAR_GLYPH,
    PERC_GLYPH,   AMP_GLYPH,    APP_GLYPH,    LPAR_GLYPH,   RPAR_GLYPH,
    AST_GLYPH,    PLUS_GLYPH,   COM_GLYPH,    DASH_GLYPH,   PERIOD_GLYPH,
    SLASH_GLYPH,  N0_GLYPH,     N1_GLYPH,     N2_GLYPH,     N3_GLYPH,
    N4_GLYPH,     N5_GLYPH,     N6_GLYPH,     N7_GLYPH,     N8_GLYPH,
    N9_GLYPH,     COL_GLYPH,    SCOL_GLYPH,   LT_GLYPH,     EQ_GLYPH,
    GT_GLYPH,     QMARK_GLYPH,  AT_GLYPH,     A_UP_GLYPH,   B_UP_GLYPH,
    C_UP_GLYPH,   D_UP_GLYPH,   E_UP_GLYPH,   F_UP_GLYPH,   G_UP_GLYPH,
    H_UP_GLYPH,   I_UP_GLYPH,   J_UP_GLYPH,   K_UP_GLYPH,   L_UP_GLYPH,
    M_UP_GLYPH,   N_UP_GLYPH,   O_UP_GLYPH,   P_UP_GLYPH,   Q_UP_GLYPH,
    R_UP_GLYPH,   S_UP_GLYPH,   T_UP_GLYPH,   U_UP_GLYPH,   V_UP_GLYPH,
    W_UP_GLYPH,   X_UP_GLYPH,   Y_UP_GLYPH,   Z_UP_GLYPH,   LBRACK_GLYPH,
    BSLASH_GLYPH, RBRACK_GLYPH, UPCAR_GLYPH,  USCORE_GLYPH, BTICK_GLYPH,
    A_GLYPH,      B_GLYPH,      C_GLYPH,      D_GLYPH,      E_GLYPH,
    F_GLYPH,      G_GLYPH,      H_GLYPH,      I_GLYPH,      J_GLYPH,
    K_GLYPH,      L_GLYPH,      M_GLYPH,      N_GLYPH,      O_GLYPH,
    P_GLYPH,      Q_GLYPH,      R_GLYPH,      S_GLYPH,      T_GLYPH,
    U_GLYPH,      V_GLYPH,      W_GLYPH,      X_GLYPH,      Y_GLYPH,
    Z_GLYPH,      LBRACE_GLYPH, VBAR_GLYPH,   RBRACE_GLYPH, TILDE_GLYPH,
};

// -----------------------------------------------------------------------------

void queue_events(EvBuf *eb, const Ev *const events, int num_ev) {
  absolute_time_t last_time = eb_last_timestamp(eb);
  for (int i = 0; i < num_ev; i++) {
    eb_queue(eb, events[i], last_time);
  }
}

void queue_glyph_events(EvBuf *eb, char c) {
  if (c >= ' ' && c <= '~') {
    int idx = c - ' ';
    queue_events(eb, INDEXED_GLYPHS[idx], GLYPH_LENS[idx]);
  } else {
    switch (c) {
    case '\n':
      queue_events(eb, LF_GLYPH, LF_GLYPH_LEN);
      break;
    default:
      queue_events(eb, UNKNOWN_GLYPH, UNKNOWN_GLYPH_LEN);
      break;
    }
  }
}
