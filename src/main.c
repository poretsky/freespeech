
/*
    Copyright (C) 1996 Alistair Conkie

    You may distribute under the terms of the GNU General Public
    Licence as specified in the README file.
*/

#include "t2s.h"
extern int getopt(int, char **, char *);

char version[] =  "FreeSpeech-UK-C-0.4";

int main(int argc, char **argv)
{

  CONFIG config_struct;
  BUFFER buffer_struct;
  LING_LIST ling_list_struct;
  SENT sent_struct;
  SPROSOD_LIST spl_struct;
  SPN ps_struct;
#ifdef FREEPHONE_OBSOLETE
  ACOUSTIC as_struct;
#endif

  CONFIG *config = &config_struct;
  BUFFER *buffer = &buffer_struct;
  LING_LIST *ling_list = &ling_list_struct;
  SENT *sent = &sent_struct;
  SPROSOD_LIST *spl = &spl_struct;
  SPN *ps = &ps_struct;
#ifdef FREEPHONE_OBSOLETE
  ACOUSTIC *as = &as_struct;
#endif

  int c;
  int errflg = 0;

  extern char *optarg;
  extern int optind;

#ifdef FREEPHONE_OBSOLETE
  strcpy(config->prog,argv[0]);
#endif
  config->input_file = "-";
  config->output_file = "-";
  config->hash_file = "-";
#ifdef FREEPHONE_OBSOLETE
  config->diphone_file = "-";
  config->format = "sun8k";
  strcpy(config->prog,"high_level");
  config->type = _MBROLA_;
#endif

  while((c = getopt(argc,argv,"i:o:h:")) != -1)
    switch(c) {
    case 'i':
      config->input_file = optarg;
      break;
    case 'o':
      config->output_file = optarg;
      break;
#ifdef FREEPHONE_OBSOLETE
    case 'd':
      config->diphone_file = optarg;
      break;
#endif
    case 'h':
      config->hash_file = optarg;
      break;
#ifdef FREEPHONE_OBSOLETE
    case 'f':
      config->format = optarg;
      break;
    case 's':       /* ``signal/synthesis''  */
      strcpy(config->prog,"low_level");
      break;
    case 'l':   /* ``linguistic''  */
      strcpy(config->prog,"high_level");
      config->type = _SPN_;
      break;
    case 'm':   /* ``MBROLA''  */
      strcpy(config->prog,"high_level");
      config->type = _MBROLA_;
      break;
    case 't':   /* ``silent Test flag''  */
      strcpy(config->prog,"test_diphones");
      break;
#endif
    default:
      errflg++;
    }
  if((optind!=argc) || errflg /* || (argc==1) */) {
    (void)fprintf(stderr, "usage: %s\n",argv[0]);
    (void)fprintf(stderr,"\t-i  input text file or - for standard input (default)\n");
    (void)fprintf(stderr,"\t-o  output file or - for standard output (default)\n");
    /* (void)fprintf(stderr,"\t-d   diphone files (default)\n");
       (void)fprintf(stderr,"\t-f output format (sun8k - default, sun10k, soundblaster8, .spn)\n");  */
    (void)fprintf(stderr,"\t-h  dictionary in hash format (no default)\n");
    /*(void)fprintf(stderr,"\t-l    linguistic (processing only)\n");*/
    /*(void)fprintf(stderr,"\t-m    linguistic (MBROLA only)\n");*/
    /* (void)fprintf(stderr,"\t-s   force use of synth prog only\n");  */

    exit (2);
  }

#ifdef FREEPHONE_OBSOLETE
  init(config, buffer, ling_list, sent, spl, ps, as);

  if(!strcmp(config->prog,"low_level")) {
    go2(config, ps, as);
  } else if(!strcmp(config->prog,"high_level")) {
#else
  init(config, buffer, ling_list, sent, spl, ps);
#endif
    go3(config, buffer, ling_list, sent, spl, ps);
#ifdef FREEPHONE_OBSOLETE
  } else if(!strcmp(config->prog,"test_diphones")) {
#ifdef DEBUG
    test_diphones(config, sent, spl, ps, as);
#endif
    ;
  } else {
    go(config, buffer, ling_list, sent, spl, ps, as);
  }

  terminate(config, buffer, ling_list, sent, spl, ps, as);
#else
  terminate(config, buffer, ling_list, sent, spl, ps);
#endif

  return(0);
}
