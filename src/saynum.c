#include "t2s.h"

/*
**              Integer to Readable ASCII Conversion Routine.
**
** Synopsis:
**
**      say_cardinal(value)
**      	long int     value;          -- The number to output
**
**	The number is translated into a string of phonemes
**
*/

static char *Cardinals[] = 
{
  "z*IHrOW ",	"w*AHn ",	"t*UW ",		"THr*IY ",
  "f*AOr ",	"f*AYv ",	"s*IHks ",	"s*EHvn ",
  "*EYt ",		"n*AYn ",		
  "t*EHn ",	"IY.l*EHvAXn ",	"tw*EHlv ",	"TH~ER.t*IYn ",
  "f~AO.t*IYn ",	"f~IHf.t*IYn ", 	"sIHk.st*IYn ",	"s~EHvn.t*IYn ",
  "~EY.t*IYn ",	"n~AYn.t*IYn "
} ;

static char *Twenties[] = 
{
  "tw*EHntIY ",	"TH*ERtIY ",	"f*AOtIY ",	"f*IHftIY ",
  "s*IHkstIY ",	"s*EHvntIY ",	"*EYtIY ",	"n*AYntIY "
} ;

static char *Ordinals[] = 
{
  "z*IHrOWTH ",	"f*ERst ",	"s*EHkAHnd ",	"TH*ERd ",
  "f*AOTH ",	"f*IHfTH ",	"s*IHksTH ",	"s*EHvnTH ",
  "*EYtTH ",	"n*AYnTH ",		
  "t*EHnTH ",	"IY.l*EHvnTH ",	"tw*EHlvTH ",	"TH~ER.t*IYnTH ",
  "f~AO.t*IYnTH ",	"f~IHf.t*IYnTH ", 	"sIHk.st*IYnTH ",	"s~EHvn.t*IYnTH ",
  "~EY.t*IYnTH ",	"n~AYn.t*IYnTH "
} ;

static char *Ord_twenties[] = 
{
  "tw*EHntIATH ","TH*ERtIATH ",	"f*AOtIATH ",	"f*IHftIATH ",
  "s*IHkstIATH ","s*EHvntIATH ","*EYtIATH ",	"n*AYntIATH "
} ;


/*
** Translate a number to phonemes.  This version is for CARDINAL numbers.
**	 Note: this is recursive.
*/
export void say_cardinal(long int value)
{
  if (value < 0)
    {
      outstring("mAYnAHs ");
      value = (-value);
      if (value < 0)	/* Overflow!  -32768 */
	{
	  outstring("IHnfIHnIHtIY ");
	  return;
	}
    }

  if (value >= 1000000000L)	/* Billions */
    {
      say_cardinal(value/1000000000L);
      outstring("bIHlIYAXn ");
      value = value % 1000000000;
      if (value == 0)
	return;		/* Even billion */
      if (value < 100)	/* as in THREE BILLION AND FIVE */
	outstring("AEnd ");
    }

  if (value >= 1000000L)	/* Millions */
    {
      say_cardinal(value/1000000L);
      outstring("mIHlIYAXn ");
      value = value % 1000000L;
      if (value == 0)
	return;		/* Even million */
      if (value < 100)	/* as in THREE MILLION AND FIVE */
	outstring("AEnd ");
    }

  /* Thousands 1000..1099 2000..99999 */
  /* 1100 to 1999 is eleven-hundred to nineteen-hundred */
  if ((value >= 1000L && value <= 1099L) || value >= 2000L)
    {
      say_cardinal(value/1000L);
      outstring("TH*AWznd ");
      value = value % 1000L;
      if (value == 0)
	return;		/* Even thousand */
      if (value < 100)	/* as in THREE THOUSAND AND FIVE */
	outstring("AEnd ");
    }

  if (value >= 100L)
    {
      outstring(Cardinals[value/100]);
      outstring("HH*AHndrAXd ");
      value = value % 100;
      if (value == 0)
	return;		/* Even hundred */
    }

  if (value >= 20)
    {
      outstring(Twenties[(value-20)/ 10]);
      value = value % 10;
      if (value == 0)
	return;		/* Even ten */
    }

  outstring(Cardinals[value]);
  return;
} 


/*
** Translate a number to phonemes.  This version is for ORDINAL numbers.
**	 Note: this is recursive.
*/
export void say_ordinal(long int value)
{

  if (value < 0)
    {
      outstring("mAHnAXs ");
      value = (-value);
      if (value < 0)	/* Overflow!  -32768 */
	{
	  outstring("IHnfIHnIHtIY ");
	  return;
	}
    }

  if (value >= 1000000000L)	/* Billions */
    {
      say_cardinal(value/1000000000L);
      value = value % 1000000000;
      if (value == 0)
	{
	  outstring("bIHlIYAXnTH ");
	  return;		/* Even billion */
	}
      outstring("bIHlIYAXn ");
      if (value < 100)	/* as in THREE BILLION AND FIVE */
	outstring("AEnd ");
    }

  if (value >= 1000000L)	/* Millions */
    {
      say_cardinal(value/1000000L);
      value = value % 1000000L;
      if (value == 0)
	{
	  outstring("mIHlIYAXnTH ");
	  return;		/* Even million */
	}
      outstring("mIHlIYAXn ");
      if (value < 100)	/* as in THREE MILLION AND FIVE */
	outstring("AEnd ");
    }

  /* Thousands 1000..1099 2000..99999 */
  /* 1100 to 1999 is eleven-hunderd to ninteen-hunderd */
  if ((value >= 1000L && value <= 1099L) || value >= 2000L)
    {
      say_cardinal(value/1000L);
      value = value % 1000L;
      if (value == 0)
	{
	  outstring("TH*AWzndTH ");
	  return;		/* Even thousand */
	}
      outstring("TH*AWznd ");
      if (value < 100)	/* as in THREE THOUSAND AND FIVE */
	outstring("AEnd ");
    }

  if (value >= 100L)
    {
      outstring(Cardinals[value/100]);
      value = value % 100;
      if (value == 0)
	{
	  outstring("HH*AHndrAXdTH ");
	  return;		/* Even hundred */
	}
      outstring("HH*AHndrAXd ");
    }

  if (value >= 20)
    {
      if ((value%10) == 0)
	{
	  outstring(Ord_twenties[(value-20)/ 10]);
	  return;		/* Even ten */
	}
      outstring(Twenties[(value-20)/ 10]);
      value = value % 10;
    }

  outstring(Ordinals[value]);
  return;
} 
