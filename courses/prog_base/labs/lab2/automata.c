#include <stdio.h>
#include <stdlib.h>

int run(int moves[], int movesLen, int res[], int resLen){
    enum action { POP = -7,
    PUSH,
    CONTINUE,
    BREAK,
    REPEAT,
    INITIALISATION };

    int act[4][4] = {CONTINUE, REPEAT, CONTINUE, 777,
		7, BREAK, BREAK, BREAK,
		BREAK, POP, POP, 77,
		BREAK, 13, BREAK, 7777};
    int state[4][4] = {0, 2, 1, 3,
        2, 333, 333, 333,
        333, 3, 3, 1,
        333, 0, 333, 0};
    enum action currentState = INITIALISATION;
    int currentPosition = 0;
    int num, i, j = 0;
    for (i = 0; i < movesLen; i++)
	{
	    currentState = INITIALISATION;
		switch (moves[i]) {
				case 8:
				    num = 0;
				    break;
				case 16:
				    num = 1;
				    break;
				case 26:
				    num = 2;
				    break;
				case 206:
				    num = 3;
				    break;
				default:
				    num = 4;
				    currentState = 0; break;
		}
		if (num != 4 && act[currentPosition][num] > 0)
		  {
			  res[j] = act[currentPosition][num];
			  j++;
          }
        else{
			currentState = act[currentPosition][num];
		switch(currentState){
        case BREAK:
            i = movesLen;
			int a;
			for (a = j; a < resLen; a++)
				res[a] = 0;
			return j;
			break;
        case POP:
            if (j!=0){
                j--;
                res[j] = 0;
            }
            break;
        case REPEAT:
            i--;
            break;
		}
		}
		if (j == resLen)
			i = movesLen;

		currentPosition = state[currentPosition][num];

	}
	int c = j;
	while (j++ < resLen)
	{
		res[j - 1] = 0;
	}
	return c;
}

