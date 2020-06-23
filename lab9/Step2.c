#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
	char buffer[10000];
	FILE *fp;
	fp = fopen(argv[1], "rb");
	while(fread(buffer, sizeof(buffer), 1, fp)){	//reads from the text file and puts it in a buffer of size 10,000
	}
	fclose(fp);
	return 0;
}
