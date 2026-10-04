#include <iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include <algorithm>
using namespace std;
//'0'=48 'A'=65
void show_land(vector<vector<char>>& visible_land) {
    cout << "  1 2 3 4 5 6 7 8\n";
    for (char i = 'A'; i <= 'H'; ++i) {
        cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            cout << visible_land[i-65][j] << " ";
        }
        cout << i << " ";
        cout << endl;
    }
    cout << "  1 2 3 4 5 6 7 8\n";

}
//initializing the land for view
void initialize_vector(vector<vector<char>>& visible_land) {
    visible_land.resize(8);
    for (int i = 0; i < 8; ++i) {
        visible_land[i].resize(8, '#');
    }
}

void mines_identification(vector<vector<char>> &meaning,int  mines_number) {
    meaning.resize(8);
    for (int i = 0; i < 8; ++i) {
        meaning[i].resize(8, '0');
    }
    
    //randomizing mines
    for (int i=0; i<mines_number;i++)
    {
        int k = rand() % 8, j = rand() % 8;
        if (meaning[k][j] == '*') {
            i -= 1;
            continue;
        }
        meaning[k][j] = '*';
        //+1 to every place around
        for (int t = k - 1; t <= k + 1; ++t) {
            for (int tt = (j - 1); tt <= (j + 1); tt++) {
                //check for out of range
                if (t > 7 || t < 0 || tt>7 || tt < 0) continue;
                if (meaning[t][tt] == '*') continue;
                meaning[t][tt] = int(meaning[t][tt]) + 1; // moves '0' to'1' etcc
            }
        }
        
    }
}
void land_revealing(vector<vector<char>> &visible_land, vector<vector<char>>& meaning, int row, int column, bool& game_is_running) {
    //check used turns
    if (visible_land[row][column] != meaning[row][column]) visible_land[row][column] = meaning[row][column];
    else cout << "you already made this turn but ok\n";
        
    if (visible_land[row][column] == '*') 
    {
        cout << "you know that you lost right?\n";
        game_is_running = false;
        show_land(visible_land);
    }
}

void mineCheck(vector<vector<char>>& meaning, int row, int column) {
    if (meaning[row][column] == '*') cout << "you lost bububu!";

}



bool win_checker(vector<vector<char>> &visible_land, int  mines_number) {
    int c = 0;
    for (int i = 0; i < 8; ++i) {
        c += count(visible_land[i].begin(), visible_land[i].end(), '#');
    }
    if (c == mines_number)
    {
        cout << "you win wow";
        return true;
    }
    else return false;
}

void getValidInput(int& row, int&column) {
    int col_int;
    char r_char;
    cout << "make your turn(example a1): ";
     //only correct type input
    if (cin >> r_char >> col_int) {
        //a->A and else
        r_char = toupper(r_char);

        //check correct size
        if (r_char >= 'A' && r_char <= 'H' && col_int >= 1 && col_int <= 8) {
            row = r_char - 'A';
            column = col_int - 1; //move for index
            return;
        }
        else cout << "wrong place selected, type right!!!";

    }
    else {
        cin.clear();// absolute wrong input type
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ai construction to clear console input
        cout << "try again, but use example properly";
    }

}



int main()
{
    bool game_is_running = true;

    int mines_number = 9;
    vector<vector<char>> visible_land;
    initialize_vector(visible_land);

    srand(time(nullptr));// time=random seed

    vector<vector<char>> meaning;
    mines_identification(meaning, mines_number);

    while (game_is_running) {
        show_land(visible_land);

        int row, col;
        getValidInput(row, col);

        land_revealing(visible_land, meaning, row, col, game_is_running);

        if (!game_is_running || win_checker(visible_land, mines_number)) {
            game_is_running = false;
        }
    }
    
}

