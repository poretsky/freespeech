/* lexholder.c
 *
 * Lexicon database holding utility.
 */

/*
 * Copyright (C) 2010 Igor B. Poretsky <poretsky@mlbox.ru>
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

#ifdef FBSD_DATABASE
#include <db.h>
#else
#include <db_185.h>
#endif

#include <fcntl.h>


/* Command line error codes */
#define CL_OK 0
#define CS_CONFLICT 1
#define NO_DB_FILE 2


static const char *usage =
  "Lexical database holding utility.\n\n"

  "This utility is designed for constructing, managing, testing and querying\n"
  "lexical database providing pronunciation info for English words.\n\n"

  "Usage:\t%s [options] <db_path>\n\n"

  "When filling and updating the database, new records are read\n"
  "from the standard input. When extracting data from the database\n"
  "the result is printed to the standardoutput.\n"
  "This behaviour can be changed by the \"-f\" switch.\n\n"

  "If no options are specified, the program reads it's standard input\n"
  "and stores it's content in the database.\n\n"

  "The recognized options are as follows:\n\n"

  "-h -- Print this help (the only option not requiring the database path)\n"
  "-l -- List database content\n"
  "-s <word> -- Search specified word\n"
  "-d <word> -- Delete record for specified word\n"
  "-f <file> -- Use specified file instead of standard input or output\n"
  "-r -- Replace mode\n"
  "-q -- Don't print messages about ignoring duplicates\n\n";


int main(int argc, char *argv[])
{
  FILE *fp = NULL;
  DB *db;
  DBT key, value;
  char line[256];
  char *f = NULL, *d = NULL, *s = NULL;
  int i, n, q = 0, ret = NO_DB_FILE, mode = R_NOOVERWRITE;

  /* Parse command line */
  if(argc==1)
    {
      (void)fprintf(stderr, usage, argv[0]);
      return EXIT_FAILURE;
    }
  while((n = getopt(argc,argv,"f:s:d:lqrh")) != -1)
    switch(n)
      {
      case 'f':
        if (strcmp(optarg, "-"))
          f = optarg;
        break;
      case 'd':
        if (d || s) ret = CS_CONFLICT;
        else d = optarg;
        break;
      case 's':
        if (d || s) ret = CS_CONFLICT;
        else s = optarg;
        break;
      case 'l':
        if (d || s) ret = CS_CONFLICT;
        else s = line;
        break;
      case 'r':
        mode = 0;
        break;
      case 'q':
        q = 1;
        break;
      case 'h':
        (void)fprintf(stderr, usage, argv[0]);
        return EXIT_SUCCESS;
      default:
        (void)fprintf(stderr, usage, argv[0]);
        return EXIT_FAILURE;
      }
  if (optind && argv[optind])
    ret = CL_OK;
  switch (ret)
    {
    case CS_CONFLICT:
      (void)fprintf(stderr,
                    "Ambiguous options in command line\n");
      return EXIT_FAILURE;
    case NO_DB_FILE:
      (void)fprintf(stderr, "DB file must be specified\n");
      return EXIT_FAILURE;
    default:
      break;
    }

  /* Open file for input or output if necessary */
  if (!d)
    {
      if (f)
        fp = fopen(f, s ? "w" : "r");
      else fp = s ? stdout : stdin;
      if (!fp)
        {
          (void)fprintf(stderr, "Can't open file %s\n", f);
          return EXIT_FAILURE;
        }
    }

  /* Open the database in appropriate mode */
  db = dbopen(argv[optind], s ? O_RDONLY : (O_RDWR | O_CREAT), 0644, DB_HASH, NULL);
  if (!db)
    {
      (void)fprintf(stderr, "Cannot open the database %s\n", argv[optind]);
      return EXIT_FAILURE;
    }

  ret = EXIT_SUCCESS;
  if (s == line) /* List database content */
    {
      for (n = 0; !db->seq(db, &key, &value, R_NEXT); n++)
        {
          (void)strncpy(line, key.data, key.size);
          (void)fprintf(fp, "%s %s\n", line, (char *)value.data);
        }
      (void)fprintf(stderr, "%i records extracted.\n", n);
    }
  else if (s) /* Lookup database for specified word */
    {
      key.data = s;
      key.size = strlen(s);
      if (db->get(db, &key, &value, 0))
        ret = EXIT_FAILURE;
      else (void)fprintf(fp, "%s\n", (char *)value.data);
    }
  else if (d) /* Delete record for specified word */
    {
      key.data = d;
      key.size = strlen(d);
      ret = db->del(db, &key, 0) ? EXIT_FAILURE : EXIT_SUCCESS;
    }
  else /* Fill the database */
    {
      for (i = 0, n = 1; fgets(line, 256, fp); n++)
        {
          key.data = strtok(line," ");
          key.size = strlen(key.data);
          value.data = strtok(NULL,"\n");
          value.size = strlen(value.data) + 1;
          ret = db->put(db, &key, &value, mode);
          if (ret < 0)
            break;
          else if (ret)
            {
              if (!q)
                (void)fprintf(stderr, "%s:%i: warning: Duplicate entry. Ignored.\n",
                              f ? f : "stdin", n);
              i++;
            }
        }
      if (ret < 0)
        {
          (void)fprintf(stderr, "%s:%i: error: Database insertion failure. Exiting now.\n",
                        f ? f : "stdin", n);
          ret = EXIT_FAILURE;
        }
      else
        {
          (void)fprintf(stderr, "%i words processed.\n", --n);
          (void)fprintf(stderr, "%i duplicates ignored.\n", i);
          (void)fprintf(stderr, "%i records put into the database.\n", n - i);
          ret = EXIT_SUCCESS;
        }
    }

  /* All done */
  (void)db->close(db);
  (void)fclose(fp);
  return ret;
}
