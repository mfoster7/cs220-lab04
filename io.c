#include <stdio.h>
#include <stdint.h>
#include "chess.h"

uint8_t notation_to_index(char file, char rank){
	uint8_t index;
	if(file < 'a' || file > 'h' || rank < '1' || rank > '8'){
		return INVALID_INDEX;
	}
	index = (8 - (rank - '0')) * 8 + file - 'a';
	/*printf("%d\n", index);*/
	return index;
}

char get_piece_at(uint8_t i){
	if(IS_SET(king_pos, i)){
		return 'K';
	}else{
		return ' ';
	}
}

void display_board(){
	unsigned int i = 0, j = 0;
	printf("\n ----------------------------------\n");
	for(i = 0; i < 8; i++) {
		printf("%d |", 8-i);
		for(j = 0; j < 8; j++) {
			printf(" %c |", get_piece_at(i*8+j));
		}
		printf("\n ----------------------------------\n");
	}
	printf("    a   b   c   d   e   f   g   h\n");
	printf("\n");
}

Move get_move(){
	char s[128];
	unsigned int error;
	Move m = {INVALID_INDEX, INVALID_INDEX};

	error = 0;
	do{
		if(error == 1){
			printf("Try again.\n");
		}
		
		error = 0;

		printf("Enter move: ");
		fgets(s, 127, stdin);

		s[5] = '\0';

		printf("s[0] = %c, s[1] = %c, s[2] = %c, s[3] = %c, s[4] = %c\n", s[0],s[1],s[2],s[3],s[4]);

		m.from = notation_to_index(s[0], s[1]);
		if(m.from == INVALID_INDEX){
			printf("Invalid from.\n");
			error = 1;
			continue;
		}

		if(s[2] != '-'){
			printf("A '-' expected after from square.\n");
			error = 1;
			continue;
		}
	
		m.to = notation_to_index(s[3], s[4]);
		if(m.to == INVALID_INDEX){
			printf("Invalid to.\n");
			error = 1;
			continue;
		}
	} while (error == 1);

	return m;
}
