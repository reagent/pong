#ifndef FIELD_H
#define FIELD_H

#include "structs.h"

Field * field_init();
void field_redraw(Field *field);
void field_get_midpoints(Field *field, int *mid_x, int *mid_y);
void field_draw_score(Field *field, Player *player);
void field_destroy(Field *field);

#endif

