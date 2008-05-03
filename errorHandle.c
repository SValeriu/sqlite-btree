#include "sqliteInt.h"
#include <stdio.h>
#include <stdlib.h>

void errorHandle(int rc, const char* msg)
{
	if(rc!=SQLITE_OK){
	  fprintf(stderr,"%s: %s\n",msg,"error message");
	  exit(-1);
	}
}

