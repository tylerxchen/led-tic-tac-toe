// pin macros

// variables
int game[3][3]; // empty represented by 0, red represented by 1, blue represented by 2

void setup()
{
    memset(game, 0, sizeof(game)*3*3);
    
}

void loop()
{
    
}

void mark(int game[3][3], int i, int j, int player)
{
    if (!game[i][j]) {
	game[i][j] = player;
    }
}

int check_win(int game[3][3])
{
    // check rows
    for (int i = 0; i < 3; i++) {
        if (game[i][0] && game[i][0] == game[i][1] && game[i][1] == game[i][2])
	    return game[i][0];
    }

    // check cols
    for (int j = 0; j < 3; j++) {
	if (game[0][j] && game[0][j] == game[1][j] && game[1][j] == game[2][j])
	    return game[0][j];
    }

    // check diagonal
    if (game[0][0] && game[0][0] == game[1][1] && game[1][1] == game[2][2])
	return game[0][0];

    // check anti-diagonal
    if (game[0][2] && game[0][2] == game[1][1] && game[1][1] == game[2][0])
	return game[0][2];

    // return 0 if there's no winner
    return 0;
}

int check_tie(int game[3][3])
{
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    if (!game[i][j])
		return 0;
	}
    }

    return 1;
}
