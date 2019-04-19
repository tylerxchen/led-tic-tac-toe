// pin macros
const int CLK = 2;
const int DT = 3;

// variables
int game[3][3]; // empty represented by 0, red represented by 1, blue represented by 2
int turn;
int cursorCol;
int cursorRow;
int gameChanged;
volatile int changePos;

void setup()
{
    Serial.begin(9600);
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    memset(game, 0, sizeof(game[0][0])*3*3);
    turn = 1;
    cursorCol = 0;
    cursorRow = 0;
    gameChanged = 0;
    changePos = 0;
    printBoard();
    attachInterrupt(digitalPinToInterrupt(CLK), readEncoder, CHANGE);
}

void loop()
{
    if (changePos) {
	cursorRow = (cursorRow + ((cursorCol + changePos) / 3)) % 3;
	cursorCol = (cursorCol + changePos) % 3;
	changePos = 0;
	gameChanged = 1;
    }
    if (gameChanged) {
	printBoard();
	gameChanged = 0;
    }
}

void printBoard()
{
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    Serial.print(game[i][j]);
	    if (i == cursorRow && j == cursorCol)
		Serial.print("*");
	}
	Serial.println();
    }
    Serial.println();
}

void readEncoder()
{
    if (digitalRead(DT) != digitalRead(CLK)) {
	changePos = 1;
    }
}

void mark(int game[3][3], int i, int j, int player)
{
    if (!game[i][j]) {
	game[i][j] = player;
    }

    gameChanged = 1;
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
