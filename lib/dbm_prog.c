#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#ifdef FBSD_DATABASE
#include <db.h>
#else
#include <ndbm.h>
#endif

#ifdef FBSD_DATABASE	/* this needs to be explicit  */
HASHINFO openinfo = {
        128,           /* bsize */
        8,             /* ffactor */
        75000,         /* nelem */
        2048 * 1024,   /* cachesize */
        NULL,          /* hash */
        0              /* lorder */
};
#endif

int main(int argc, char *argv[])
{
#ifdef FBSD_DATABASE
	DBT inKey, inVal;
	DB * db;
#else
	DBM * db;
	datum Key;
	datum Val;
#endif

	FILE *ifd;
	char line[256];
	char *iptr;
	char *optr;
        extern char *optarg;
        extern int optind;

	char c;
	int  i;

	/* read in file name  */
	if(argc==1) {
        (void)fprintf(stderr, "Usage: %s",argv[0]);
        (void)fprintf(stderr,"\t-o output_file_without_extention -i input_file\n");
                exit(2);
	}
	while((c = getopt(argc,argv,"i:o:")) != -1) {
                switch(c) {
                        case 'i':
                                iptr = optarg;
                                break;
                        case 'o':
                                optr = optarg;
                                break;
			default:
				(void)fprintf(stderr, "Usage: %s",argv[0]);
				(void)fprintf(stderr,"\t-o output_file_without_extention -i input_file\n");
				exit(2);
		}
	}

	if(!strcmp(iptr,"-")) {
		ifd = stdin;
        } else if ((ifd=fopen(iptr,"r")) == NULL) {
                (void)fprintf(stderr,"Can't open file %s\n",iptr);
                exit(1);
        }


#ifdef FBSD_DATABASE
        db = dbopen(optr,O_RDWR|O_CREAT, 0000644, DB_HASH, &openinfo);

	while(fgets(line,256,ifd)) {
		inKey.data = strtok(line," ");
		inKey.size = strlen(inKey.data)+1;
		inVal.data = strtok(NULL,"\n");
		inVal.size = strlen(inVal.data)+1;
                (db->put)(db,&inKey,&inVal,R_NOOVERWRITE);

		i++;
		fprintf(stderr,"%d\r",i);
	}

        (void)(db->close)(db);
#else
        db = dbm_open(optr,O_RDWR|O_CREAT, 0000644);

	while(fgets(line,256,ifd)) {
		Key.dptr = strtok(line," ");
		Key.dsize = strlen(Key.dptr)+1;
		Val.dptr = strtok(NULL,"\n");
		Val.dsize = strlen(Val.dptr)+1;
		dbm_store(db,Key,Val,DBM_INSERT);

		i++;
		fprintf(stderr,"%d\r",i);
	}

        dbm_close(db);
#endif

	return(0);
}
