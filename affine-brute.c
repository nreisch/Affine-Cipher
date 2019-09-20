/**
	Affine Cipher 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int findMax(int *);
void zero_out_array(int *alphabet);
int count = 0;

int main(int argc, char ** argv) {
	 int ch, shift=-1, mult=1, x;
	 //if( argc>1) shift = atoi(argv[1]);
	 //if( argc>2) mult = atoi(argv[2]);
	 int alphabet[26];
	 int primes[] = {
	 	1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25
	 };
	 
	 FILE *infile = fopen(argv[1],"r");

	 int i = 0, j = 0;
	 for(;i<12;i++) {
	 	mult = primes[i];
	 	j = 0;
	 while(j<26) {
	 	shift = j;
	 	zero_out_array(alphabet);
		 while( (ch=getc(infile)) != EOF ) {
			 if( isalpha(ch) ) {
				 x = ch & 0x1f;
				 x = (mult*x+shift)%26;
			 if( x==0 ) x=26;
			 	ch = (ch&0xe0) + x;
			 }
			 putchar( ch );
			 alphabet[ch - 'a']++;
		 }
		 char val = findMax(alphabet) + 'a';
		 if(val == 'e' || val == 'a' || val == 'i') { 
		 	printf("BROKEN: mult: %d, shift: %d", mult, shift);
		 }
		 // count++;
		 // printf("%d ",count);
		 printf("\n---------------------------- \n");
		 ++j;
		 fseek(infile, 0, SEEK_SET);
	 	}
	}
	return 0;
}

int findMax(int *alphabet) {
	// Find the distribution with the greatest max
	int max = 0;
	char letter_index;
	int i = 0;
	for(;i<26;i++){
		if(alphabet[i] > max) {
			max = alphabet[i];
			letter_index = i;
		}
	}
	return letter_index;
}

void zero_out_array(int *alphabet) {
	int i = 0;
	for(;i<26;i++) {
		alphabet[i] = 0;
	}

}