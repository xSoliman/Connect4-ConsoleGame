#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

struct Player
{
    string name;
    char color;

    void GetName()
    {
        cin >> name;
    }
};

enum Dir
{
    Right = 0, Down, DownRight, DownLeft
};
int dir_row[4] = {0, 1, 1, 1};
int dir_col[4] = {1, 0, 1, -1};

void Connect4Game();

void Intro();

void MainMenu();

void Choice();

void StartGame();

void IntializeBoard(char board[6][7]);

void PrintBoard(char board[6][7]);

bool ValidPos(int freeCapacity[7], int pos);

void GameEnded(char board[6][7], int freeCapacity[7], bool &winner, bool &draw);

void CheckWinner(char board[6][7], bool &winner);

int CheckWithDir(int r, int c, char board[6][7], int dir);

void CheckRows(char board[6][7], bool &winner);

void CheckCols(char board[6][7], bool &winner);

void CheckRDiagonals(char board[6][7], bool &winner);

void CheckLDiagonals(char board[6][7], bool &winner);

void CheckDraw(int freeCapacity[7], bool &draw);

void PrintResult(bool turn, bool winner, Player player[2],char board[6][7]);

void MorseWin();

void MorseDraw();

void PreviousResults();

void ExitGame();


int main()
{
    Connect4Game();

    return 0;
}

void Connect4Game()
{
    while (true)
    {
        Intro();
        MainMenu();
        Choice();
    }
}

void Intro()
{
    cout << "                                   -------------------------------------------------" << endl;
    cout << "                                   | Welcome in the most beautiful Connect 4 Game! |" << endl;
    cout << "                                   -------------------------------------------------" << endl;

}

void MainMenu()
{
    cout << endl;
    cout << "***************************************************" << endl;
    cout << "*                    Main menu                    *" << endl;
    cout << "***************************************************" << endl;
    cout << "*                                                 *" << endl;
    cout << "*                 1: Start new game               *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*            2: View previous games(Coming soon)  *" << endl;
    cout << "*                                                 *" << endl;
    cout << "*                     3: Exit                     *" << endl;
    cout << "*                                                 *" << endl;
    cout << "***************************************************" << endl;
    cout << endl;

}

void Choice()
{
    int ch;
    while(true)
    {
        cout << "Enter your choice : ";
        cin >> ch;
        if(cin.fail()||ch>3||ch<1)
        {
            cout<<"Please enter number between 1 and 3 !"<<endl;
            cin.clear();
            cin.ignore(1000,'\n');
        }
        else
            break;
    }
    switch (ch)
    {
        case 1:
            system("cls");
            StartGame();
            break;
        case 2:
            system("cls");
            PreviousResults();
            break;
        case 3:
            ExitGame();
            break;
    }

}

void StartGame()
{
    Player player[2];
    srand(time(0));
    bool turn = rand() % 2;
    player[turn].color = 'R';
    player[!turn].color = 'Y';

    cout << "Enter player 1 name : ";
    player[0].GetName();
    cout << "Enter player 2 name : ";
    player[1].GetName();
    cout << endl;
    system("cls");
    cout << "     --> " << player[turn].name << " plays first, ";
    player[turn].color == 'R' ? cout << "with Red! <--" << endl : cout << "with Yellow!<--" << endl;
    cout << endl;
    cout << "* \'R\' refers to Red * " << endl;
    cout << "* \'Y\' refers to Yellow * " << endl;
    cout << endl;

    char board[6][7];
    int freeCapacity[7];
    for (int i = 0; i < 7; i++)
        freeCapacity[i] = 6;
    IntializeBoard(board);
    bool winner = 0, draw = 0;
    while (true)
    {
        cout << endl;
        cout << "                   --> it's " << player[turn].name << " turn <--" << endl;
        cout << endl;
        PrintBoard(board);

        int pos;
        while (true)
        {
            cout << "Enter position: ";
            cin >> pos;
            if (!ValidPos(freeCapacity, pos)||cin.fail()){
                cout << "Please choose column has free space and between 1:7 !" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
            }
            else
                break;
        }
        board[freeCapacity[pos - 1] - 1][pos - 1] = player[turn].color;
        freeCapacity[pos - 1]--;
        GameEnded(board, freeCapacity, winner, draw);
        system("cls");
        if (draw || winner)
            break;
        turn = !turn;
        Beep(300,200);
    }
    PrintResult(turn, winner, player,board);

    system("cls");

}

void IntializeBoard(char board[6][7])
{
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            board[i][j] = '.';
}

void PrintBoard(char board[6][7])
{
    for (int i = 0; i < 6; i++)
    {
        cout << "                     ";
        for (int j = 0; j < 7; j++)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << "                     ";
    cout << 1 << " " << 2 << " " << 3 << " " << 4 << " " << 5 << " " << 6 << " " << 7 << endl;
    cout << endl;

}

bool ValidPos(int freeCapacity[7], int pos)
{
    return (pos >= 1 && pos <= 7 && freeCapacity[pos - 1] != 0);
}

void GameEnded(char board[6][7], int freeCapacity[7], bool &winner, bool &draw)
{

    CheckWinner(board, winner);
    CheckDraw(freeCapacity, draw);
}

void CheckWinner(char board[6][7], bool &winner)
{

    CheckRows(board, winner);

    CheckCols(board, winner);

    CheckRDiagonals(board, winner);

    CheckLDiagonals(board, winner);

}

void CheckRows(char board[6][7], bool &winner)
{

    int cntr = 0;
    for (int i = 0; i < 6; i++)
        cntr = max(cntr, CheckWithDir(i, 0, board, Right));
    cntr >= 4 ? winner = 1 : 0;

}

void CheckCols(char board[6][7], bool &winner)
{

    int cntr = 0;
    for (int i = 0; i < 7; i++)
        cntr = max(cntr, CheckWithDir(0, i, board, Down));
    cntr >= 4 ? winner = 1 : 0;

}

void CheckRDiagonals(char board[6][7], bool &winner)
{
    int cntr = 0;

    for (int i = 0; i < 4; i++)
        cntr = max(cntr, CheckWithDir(0, i, board, DownRight));

    for (int i = 0; i < 4; i++)
        cntr = max(cntr, CheckWithDir(i, 0, board, DownRight));

    cntr >= 4 ? winner = 1 : 0;

}

void CheckLDiagonals(char board[6][7], bool &winner)
{

    int cntr = 0;

    for (int i = 6; i >= 3; i--)
    {
        cntr = max(cntr, CheckWithDir(0, i, board, DownLeft));
    }

    for (int i = 0; i < 4; i++)
    {
        cntr = max(cntr, CheckWithDir(i, 6, board, DownLeft));
    }

    cntr >= 4 ? winner = 1 : 0;

}

int CheckWithDir(int r, int c, char board[6][7], int dir)
{

    int cntr = 1, maxCntr = 0;
    while (true)
    {

        if (board[r][c] == board[r + dir_row[dir]][c + dir_col[dir]] && board[r][c] != '.')
        {
            cntr++;
            maxCntr = max(cntr, maxCntr);
        }
        else
            cntr = 1;

        r += dir_row[dir];
        c += dir_col[dir];

        if (r + dir_row[dir] < 0 || r + dir_row[dir] >= 6 || c + dir_col[dir] < 0 || c + dir_col[dir] >= 7)
            break;

    }
    return maxCntr;
}

void CheckDraw(int freeCapacity[7], bool &draw)
{
    bool allFilled = 1;
    for (int i = 0; i < 7; i++)
        if (freeCapacity[i])
            allFilled = 0;

    draw = allFilled;
}

void PrintResult(bool turn, bool winner, Player player[2],char board[6][7])
{
    char ch;

    if (winner)
    {
        cout << "             --------------------------------" << endl;
        cout << "                      "<< player[turn].name << " is the winner" << endl;
        cout << "             --------------------------------" << endl;
        PrintBoard(board);
        cout << "Enter any character to return to the main menu" << endl;
        MorseWin();
        cin >> ch;
    }
    else
    {
        cout << "               -----------------------------" << endl;
        cout << "              |            Draw!!           |" << endl;
        cout << "               -----------------------------" << endl;
        PrintBoard(board);
        cout << "Enter any character to return to the main menu" << endl;
        MorseDraw();
        cin>>ch;
    }

}
void MorseWin()
{

    Beep(550,200);
    cout<<'.';

    Beep(550,500);
    cout<<'-';

    Beep(550,500);
    cout<<'-';

    cout<<" ";

    Beep(550,200);
    cout<<'.';

    Beep(550,200);
    cout<<'.';

    cout<<" ";

    Beep(550,500);
    cout<<'-';

    Beep(550,200);
    cout<<'.';


}
void MorseDraw()
{


    Beep(550,500);
    //cout<<'-';

    Beep(550,200);
    //cout<<'.';

    Beep(550,200);
    //cout<<'.';

    //cout<<" ";

    Beep(550,200);
    //cout<<'.';

    Beep(550,500);
    //cout<<'-';

    Beep(550,200);
    //cout<<'.';

    //cout<<" ";

    Beep(550,200);
    //cout<<'.';

    Beep(550,500);
    //cout<<'-';

    //cout<<" ";

    Beep(550,200);
    //cout<<'.';

    Beep(550,500);
    //cout<<'-';

    Beep(550,500);
    //cout<<'-';

    //cout<<" ";

}
void PreviousResults()
{

}

void ExitGame()
{
    cout<<"Thanks for playing!"<<endl;
    exit(0);
}
