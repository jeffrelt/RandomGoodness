
//#include <stdlib.h>
#include <stdio.h>

int getInt(const char* s, int* save_value){
// returns the number of characters "eaten"
// sets the integer sent via save_value pointer

	int count = 0;
	int val;
	*save_value = 0;
	int neg = 0;
	while( (val = s[count]) && (val < '0' || val > '9' )){
		++count;
	}
	if( count && s[-1] == '-' )
		neg = 1;
	while( (val = s[count]) ){
		if( val < '0' || val > '9' )
			break;
		*save_value = *save_value * 10 + val - '0';
		++count;
	}
	if(neg)
		*save_value *= -1;
	return count;
}



int main(int argc, const char** argv){
	if(argc < 3){
		printf("Two parameters must be sent\n");
		return 2;
	}
	const char* a = argv[1];
	const char* b = argv[2];
	while( *a && *b ){
		int val_a, val_b;
		a += getInt(a, &val_a);
		b += getInt(b, &val_b);
		printf("%i:%i\n", val_a,val_b);
		if( val_a < val_b ){
			printf("%s < %s\n", argv[1], argv[2]);
			return -1;
		}
		if( val_a > val_b ){
			printf("%s > %s\n", argv[1], argv[2]);
			return 1;
		}
	}
	if( *a ){
		printf("%s > %s\n", argv[1], argv[2]);
		return -1;
	}
	if( *b ){
		printf("%s < %s\n", argv[1], argv[2]);
		return 1;
	}
	printf("%s == %s\n", argv[1], argv[2]);
	return 0;

}
