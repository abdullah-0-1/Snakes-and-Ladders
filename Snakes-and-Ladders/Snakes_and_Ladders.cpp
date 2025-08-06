#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<time.h>
#include<string>
using namespace std;
#define cap 100
#define rows 80 
#define columns 100


void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// ****************************************************

void DrawLine(int p1r, int p1c, int p2r, int p2c, char sym = -37)
{
    for (float a = 0.0011; a < 1; a += 0.01)
    {
        int r = p1r * (1 - a) + p2r * (a);
        int c = p1c * (1 - a) + p2c * (a);
        if (p1r == p2r)
        {
            r = p1r;
        }
        if (p1c == p2c)
        {
            c = p1c;
        }
        if (r >= 80 || c >= 120 || r < 0 || c < 0)
        {
            continue;
        }

        gotoRowCol(r, c);
        cout << sym;
    }
}

void PrintSquare(int sr, int sc, int rdim, int cdim)
{
    for (int r = 0; r < rdim; r++)
    {
        for (int c = 0; c < cdim; c++)
        {
            if (r == 0 || c == 0 || r == rdim - 1 || c == cdim - 1)
            {
                gotoRowCol(r + sr, c + sc);
                cout << char(-37);
            }
        }
    }
}

void PrintGrid(int rdim, int cdim)
{
    int col = 1;
    for (int r = 0; r < 10; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            color(col);
            PrintSquare(r * rdim, c * cdim, rdim, cdim);
            col++;
            if (col == 15)
            {
                col = 1;
            }
        }
    }
}

void CellNum(int pos, int& cri, int& cci)
{
    pos = 100 - pos;
    cri = pos / 10;
    cci = pos % 10;
    if (cri % 2 != 0)
    {
        cci = 10 - cci - 1;
    }
}

void PrintInMiddle(int val, int cri, int cci, int rdim, int cdim)
{
    gotoRowCol(cri * rdim + (rdim / 2), cci * cdim + (cdim / 2) - 1);
    cout << val;
}

void BoardNum(int rdim, int cdim)
{
    int cri, cci;
    for (int pos = 1; pos <= 100; pos++)
    {
        CellNum(pos, cri, cci);
        PrintInMiddle(pos, cri, cci, rdim, cdim);
    }
}

void PrintWholeBoard(int rdim, int cdim)
{
    color(7);
    PrintGrid(rdim, cdim);
    BoardNum(rdim, cdim);
}

void init(int& Psize, string Names[], int& Scount, int SS[], int SE[], int& Lcount, int LS[], int LE[], char Psym[])
{
    color(7);
    int V;
    ifstream rdr("snakes.txt");
    ifstream rdr2("ladders.txt");
    Psize = 0;
    Scount = 0;
    Lcount = 0;
    gotoRowCol(rows / 2, columns + 10);
    cout << "Enter Number of Players Playing: ";
    cin >> Psize;
    gotoRowCol(rows / 2 + 2, columns + 10);
    cout << "Enter Player Names: ";
    int c = 1;
    for (int i = 0; i < Psize; i++)
    {
        gotoRowCol(rows / 2 + 2 + c, columns + 10);
        cout << c << ")";
        cin >> Names[i];
        c++;
    }

    c = 1;
    gotoRowCol(rows / 2, columns + 50);
    cout << "Enter Symbols of player: ";
    char S;
    for (int i = 0; i < Psize; i++)
    {
        gotoRowCol(rows / 2 + 2 + c, columns + 50);
        cout << c << ")";
        cin >> S;
        Psym[i] = S;
        c++;
    }


    rdr >> Scount;
    for (int i = 0; i < Scount; i++)
    {
        rdr >> V, SS[i] = V;
        rdr >> V, SE[i] = V;
    }
    V = 0;
    rdr2 >> Lcount;
    for (int i = 0; i < Lcount; i++)
    {
        rdr2 >> V, LS[i] = V;
        rdr2 >> V, LE[i] = V;
    }
}

void TurnDisplay(string SingleName, int turn)
{
    color(turn + 1);
    gotoRowCol(rows + 2, columns / 2);
    cout << "\"" << SingleName << "\"" << " Take Your Turn...";
}

void PrintDice(int n)
{
    color(1);
    switch (n)
    {
    case 1:
    {
        gotoRowCol(10, columns + 20);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(10, columns + 20);
        cout << " ";
    }
    case 2:
    {
        gotoRowCol(5, columns + 15);
        cout << char(-37);
        gotoRowCol(15, columns + 25);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(5, columns + 15);
        cout << " ";
        gotoRowCol(15, columns + 25);
        cout << " ";
    }
    case 3:
    {
        gotoRowCol(5, columns + 15);
        cout << char(-37);
        gotoRowCol(10, columns + 20);
        cout << char(-37);
        gotoRowCol(15, columns + 25);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(5, columns + 15);
        cout << " ";
        gotoRowCol(10, columns + 20);
        cout << " ";
        gotoRowCol(15, columns + 25);
        cout << " ";
    }
    case 4:
    {
        gotoRowCol(5, columns + 15);
        cout << char(-37);
        gotoRowCol(15, columns + 25);
        cout << char(-37);
        gotoRowCol(15, columns + 15);
        cout << char(-37);
        gotoRowCol(5, columns + 25);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(5, columns + 15);
        cout << " ";
        gotoRowCol(15, columns + 25);
        cout << " ";
        gotoRowCol(15, columns + 15);
        cout << " ";
        gotoRowCol(5, columns + 25);
        cout << " ";
    }
    case 5:
    {
        gotoRowCol(5, columns + 15);
        cout << char(-37);
        gotoRowCol(15, columns + 25);
        cout << char(-37);
        gotoRowCol(15, columns + 15);
        cout << char(-37);
        gotoRowCol(5, columns + 25);
        cout << char(-37);
        gotoRowCol(10, columns + 20);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(5, columns + 15);
        cout << " ";
        gotoRowCol(15, columns + 25);
        cout << " ";
        gotoRowCol(15, columns + 15);
        cout << " ";
        gotoRowCol(5, columns + 25);
        cout << " ";
        gotoRowCol(10, columns + 20);
        cout << " ";
    }
    case 6:
    {
        gotoRowCol(5, columns + 15);
        cout << char(-37);
        gotoRowCol(15, columns + 25);
        cout << char(-37);
        gotoRowCol(15, columns + 15);
        cout << char(-37);
        gotoRowCol(5, columns + 25);
        cout << char(-37);
        gotoRowCol(10, columns + 15);
        cout << char(-37);
        gotoRowCol(10, columns + 25);
        cout << char(-37);
        Sleep(100);
        gotoRowCol(5, columns + 15);
        cout << " ";
        gotoRowCol(15, columns + 25);
        cout << " ";
        gotoRowCol(15, columns + 15);
        cout << " ";
        gotoRowCol(5, columns + 25);
        cout << " ";
        gotoRowCol(10, columns + 15);
        cout << " ";
        gotoRowCol(10, columns + 25);
        cout << " ";
    }
    }
}

int RollDice()
{
    int seed = time(0);
    int n = 0, sum = 0;
    srand(seed);
    do
    {
        while (!_kbhit())
        {
            n = rand() % 6 + 1;
            PrintDice(n);
            Sleep(100);
        }
        gotoRowCol(5, columns + 35);
        cout << "you got : " << n;
        while (_kbhit())
        {
            _getch();
        }
        sum = sum + n;
        if (sum >= 18)
        {
            return 0;
        }
    } while (n == 6);
    return sum;
}

void ChangePos(int& pos, int d)
{
    if (pos == 0)
    {
        if (d > 6)
        {
            d = d - 6;
            pos = pos + d;
        }
    }
    else
    {
        if (pos + d > 100)
        {
            pos = pos;
        }
        else
            pos = pos + d;
    }
}

void PrintPlayerPos(int PPos, int Psym, int rdim, int cdim, int turn)
{
    color(turn + 1);
    int cri, cci;
    CellNum(PPos, cri, cci);
    if (turn == 0)
    {
        gotoRowCol((rdim * cri + 1 + (rdim / 4) - 1), (cdim * cci + 1 + (cdim / 4) - 1));
        cout << char(Psym);
    }
    else if (turn == 1)
    {
        gotoRowCol((rdim * cri + (3 * rdim / 4) - 1), (cdim * cci + (cdim / 4) - 1));
        cout << char(Psym);
    }
    else if (turn == 2)
    {
        gotoRowCol((rdim * cri + (rdim / 4) - 1), (cdim * cci + (3 * cdim / 4) - 1));
        cout << char(Psym);
    }
    else if (turn == 3)
    {
        gotoRowCol((rdim * cri + (3 * rdim / 4) - 1), (cdim * cci + (3 * cdim / 4) - 1));
        cout << char(Psym);
    }
}

bool SnakeCheck(int& PPos, int Scount, int SS[], int SE[])
{
    for (int i = 0; i < Scount; i++)
    {
        if (SS[i] == PPos)
        {
            PPos = SE[i];
            return true;
        }
    }
    return false;
}

bool LadderCheck(int& PPos, int Lcount, int LS[], int LE[])
{
    for (int i = 0; i < Lcount; i++)
    {
        if (LS[i] == PPos)
        {
            PPos = LE[i];
            return true;
        }
    }
    return false;
}

void TurnChange(int& turn, int Psize)
{
    turn++;
    turn = turn % Psize;
}

void PrintSnakes(int Scount, int SS[], int SE[], int rdim, int cdim)
{
    color(4);
    int SScri, SScci, SEcri, SEcci;
    for (int i = 0; i < Scount; i++)
    {
        CellNum(SS[i], SScri, SScci);
        CellNum(SE[i], SEcri, SEcci);
        DrawLine((rdim * SScri + 2 + (rdim / 4) - 1), (cdim * SScci + 2 + (cdim / 4) - 1), (rdim * SEcri + 2 + (rdim / 4) - 1), (cdim * SEcci + 2 + (cdim / 4) - 1));
    }
}

void PrintLadders(int Lcount, int LS[], int LE[], int rdim, int cdim)
{
    color(2);
    int LScri, LScci, LEcri, LEcci;
    for (int i = 0; i < Lcount; i++)
    {
        CellNum(LS[i], LScri, LScci);
        CellNum(LE[i], LEcri, LEcci);
        DrawLine((rdim * LScri + 2 + (rdim / 4) - 1), (cdim * LScci + 2 + (cdim / 4) - 1), (rdim * LEcri + 2 + (rdim / 4) - 1), (cdim * LEcci + 2 + (cdim / 4) - 1));
    }
}

void WinnersDisplay(string Winners[], int wins)
{
    int c = 1;
    for (int i = 0; i < wins; i++)
    {
        gotoRowCol(rows / 2 + 10 + c, columns + 50);
        cout << c << ")" << Winners[i] << endl;
    }
}

// *********************************//
int main()
{
    int prevPos;
    int rdim = rows / 10, cdim = columns / 10;
    int dice;
    int turn = 0;
    char Psym[cap] = {};
    int Psize, PPos[cap] = {};
    string Names[cap] = {};
    int Scount, SS[cap] = {}, SE[cap] = {};
    int Lcount, LS[cap] = {}, LE[cap] = {};
    int Wins = 0;
    string Winners[cap] = {};

    _getch();
    PrintWholeBoard(rdim, cdim);
    init(Psize, Names, Scount, SS, SE, Lcount, LS, LE, Psym);
    PrintSnakes(Scount, SS, SE, rdim, cdim);
    PrintLadders(Lcount, LS, LE, rdim, cdim);



    hideConsoleCursor();
    do {
        TurnDisplay(Names[turn], turn);
        PrintSquare(0, columns + 10, 20, 20);
        _getch();
        dice = RollDice();
        prevPos = PPos[turn];
        ChangePos(PPos[turn], dice);
        PrintPlayerPos(prevPos, ' ', rdim, cdim, turn);
        PrintPlayerPos(PPos[turn], Psym[turn], rdim, cdim, turn);

        prevPos = PPos[turn];
        if (SnakeCheck(PPos[turn], Scount, SS, SE))
        {
            PrintPlayerPos(prevPos, ' ', rdim, cdim, turn);
            PrintPlayerPos(PPos[turn], Psym[turn], rdim, cdim, turn);
        }

        prevPos = PPos[turn];
        if (LadderCheck(PPos[turn], Lcount, LS, LE))
        {
            PrintPlayerPos(prevPos, ' ', rdim, cdim, turn);
            PrintPlayerPos(PPos[turn], Psym[turn], rdim, cdim, turn);
        }

        if (PPos[turn] == 100)
        {
            Winners[Wins] = Names[turn], Wins++;
        }

        do
        {
            TurnChange(turn, Psize);
        } while (PPos[turn] == 100);
    } while (Wins < Psize - 1);

    WinnersDisplay(Winners, Wins);

    gotoRowCol(rows, columns);
    _getch();
    return 0;
}
