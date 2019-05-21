#ifndef __APP_LOGIC_H
#define __APP_LOGIC_H

#include "AppUart.h"
#include "VgaLogic.h"

#define NUM_SET "0123456789"
#define DELIMITER ","

//defines
#define LIJN "lijn"               //er  01
#define CLEARSCHERM "clearscherm" //er  02
#define RECHTHOEK "rechthoek"     //er  03
#define TEKST "tekst"             //er  04
#define BITMAP "bitmap"           //er  05

//Structs
struct struct_lijn
{
  int x_1;
  int y_1;
  int x_2;
  int y_2;
  uint8_t color;
  int weight;
  int reserved;
};

struct struct_text
{
  int x_lup;
  int y_lup;
  uint8_t color;
  char *text;
  char *fontname;
};

struct struct_rectangle
{
  int x_lup;
  int y_lup;
  int x_rdown;
  int y_rdown;
  uint8_t color;
  int style;
};

struct struct_bitmap
{
  int x_lup;
  int y_lup;
  uint8_t bm_nr;
};

struct struct_clearscherm
{
  uint8_t color;
};

int CharToInt(char* src, int error);

void StrSplit(char* src, char* dest, int error);

void CreateObject(char* src, int error);

int foutmeldings_error_logic(int fout);
void StringHandler(char *str_inkomend);
int komma_functie(char *string);
int check_commando(char *functie_naam);
void fill_line_struct(struct struct_lijn *pstr, char *pstring_array[]);
int string_to_kleur(char *kleur);
void fill_line_struct(struct struct_lijn *pstr, char *pstring_array[]);
void fill_text_struct(struct struct_text  *pstr, char *pstring_array[]);
void fill_rectangle_struct(struct struct_rectangle  *pstr, char *pstring_array[]);
void fill_bitmap_struct(struct struct_bitmap  *pstr, char *pstring_array[]);
void fill_clearscherm_struct(struct struct_clearscherm  *pstr, char *pstring_array[]);

void call_line(char *pstring_array);
void call_text(char *pstring_array);


#endif
