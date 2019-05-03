
//Verplict


int API_draw_text (int x_lup, int y_lup, int color, char *text, char *fontname, int fontsize, int fontsytle, int reserved);
int API_draw_line (int x_1, int y_1, int x_2, y2, int color, int weight, int reserved);
int API_draw_rectangle (int x_lup, int y_lup, int x_rdown, int y_rdown, int color, int style, int reserved, int reserved);
int API_draw_bitmap (int x_lup, int y_lup, int bm_nr);
int API_clearscreen (int color);


//Optioneel
int API_wait (int msecs);
int API_repeat_commands (int nr_previous_commands, int iterations, int reserved);
int API_execute (void);
int API_draw_circle (int x, int y, int radius, int color, int reserved);
int API_draw_figure (int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x_4, int y_4, int x_5, int y_5, int color, int reserved);
