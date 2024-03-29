/*
    Copyright (C) 1996 Alistair Conkie

    You may distribute under the terms of the GNU General Public
    Licence as specified in the README file.
*/


/* 
   This mapping is the definitive mapping from the
   ARPA phoneme list to the Edin. diphone list. Note that there are
   some symbols which may not be recognised in one or other system

   The mapping is not 1 - 1
*/
#include "t2s.h"

static char *nrl_edin[][2] = {
  {	" ", "| ",},
  {	"IY", "ee ",},
  {	"EY", "ai ",},
  {	"AE", "aa ",},
  {	"AO", "aw ",},
  {	"UH", "oo ",},
  {	"ER", "er ",},
  {	"AH", "u ",},
  {	"AW", "ou ",},
  {	"IH", "i ",},
  {	"EH", "e ",},
  {	"AA", "ar ",},
  {	"OW", "oa ",},
  {	"UW", "uu ",},
  {	"AX", "a ",},
  {	"AY", "ie ",},
  {	"OY", "oi ",},
  {	"OH", "o ",},
  {	"IA", "eer ",},
  {	"EA", "air ",},
  {	"UA", "oor ",},
  {	"p", "p ",},
  {	"t", "t ",},
  {	"k", "k ",},
  {	"f", "f ",},
  {	"TH", "th ",},
  {	"s", "s ",},
  {	"SH", "sh ",},
  {	"HH", "h ",},
  {	"n", "n ",},
  {	"l", "l ",},
  {	"y", "y ",},
  {	"CH", "ch ",},
  {	"WH", "w ",},
  {	"b", "b ",},
  {	"d", "d ",},
  {	"g", "g ",},
  {	"v", "v ",},
  {	"DH", "dh ",},
  {	"z", "z ",},
  {	"ZH", "zh ",},
  {	"m", "m ",},
  {	"NG", "ng ",},
  {	"w", "w ",},
  {	"r", "r ",},
  {	"JH", "j ",},			/* problem  */
  {	"","",},
};


export void nrl_edin_conv(char *str, char *str2)
{
  int i;
  
  strcpy(str2,"");
  
  while(*str) {
    i = 0;
    while(nrl_edin[i][0] != '\0') {
      if(!strncmp(str,nrl_edin[i][0],strlen(nrl_edin[i][0])))
	break;
      i++;
    }
    strcat(str2,nrl_edin[i][1]);
    str += strlen(nrl_edin[i][0]);
  }
}
