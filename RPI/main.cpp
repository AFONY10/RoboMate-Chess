#include <vector>
#include <iostream>
#include <cstdlib>
#include <thread>
#include "Board.h"
#include "Piece.h"
//#include "Chess_engine.h"

using namespace std;

///
///
///  BRUGES IKKE TIL NOGET PÅ RASPBERRY PI
///
///


void gameLoop1v1()
{
    Board board;
    vector<int> moves;
    int moveFrom;
    int moveTo;
    Color turn = WHITE;


    while (true)
    {

        board.updateLegalMoves(WHITE);
        board.updateLegalMoves(BLACK);

        if (board.checkForCheckmate(turn))
        {
            cout << endl
                 << "Checkmate" << endl;
            break;
        }
        else if (board.checkForStalemate(turn))
        {
            cout << endl
                 << "Stalemate" << endl;
            break;
        }

        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        board.printBoard();

        cout << endl
             << "Enter from: ";
        cin >> moveFrom;

        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif

        board.printBoardWithLegalMoves(board.getLegalMoves(moveFrom));

        cout << endl
             << "Enter to: ";
        cin >> moveTo;
        if (moveTo != moveFrom)
        {
            if (board.setPos(moveFrom, moveTo, turn))
            {
                turn = (turn == WHITE) ? BLACK : WHITE;
            }
            else
            {
                #ifdef _WIN32
                system("cls");
                #else
                system("clear");
                #endif

                cout << endl
                     << "Invalid move" << endl;

                #ifdef _WIN32
                std::this_thread::sleep_for(std::chrono::seconds(2));
                #else
                sleep(2);
                #endif
            }
        }
    }
}

void gameLoopRoboMate(Color playerColor, int difficulty = 20) {
    Board board;
    vector<int> moves;
    int moveFrom;
    int moveTo;
    Color turn = WHITE;
    pair<int, int> botMove;

    board.getBot().set_difficulty(difficulty);

    cout << "First: " << botMove.first << " Second: " << botMove.second << endl;

    while (true)
    {

        board.updateLegalMoves(WHITE);
        board.updateLegalMoves(BLACK);

        if (board.checkForCheckmate(turn))
        {
            cout << endl
                 << "Checkmate" << endl;
            break;
        }
        else if (board.checkForStalemate(turn))
        {
            cout << endl
                 << "Stalemate" << endl;
            break;
        }
        #ifdef _WIN32
        //system("cls");
        #else
        system("clear");
        #endif

        if (turn == playerColor) {

            board.printBoard();

            cout << endl
                << "Enter from: " << endl;
            cin >> moveFrom;

            #ifdef _WIN32
            //system("cls");
            #else
            system("clear");
            #endif

            board.printBoardWithLegalMoves(board.getLegalMoves(moveFrom));

            cout << endl
                << "Enter to: " << endl;
            cin >> moveTo;
            if (moveTo != moveFrom)
            {
                if (board.setPos(moveFrom, moveTo, turn))
                {
                    turn = (turn == WHITE) ? BLACK : WHITE;

                    board.updateLegalMoves(WHITE);
                    board.updateLegalMoves(BLACK);

                    botMove = board.getBot().make_move(moveFrom, moveTo);
                    cout << "First: " << botMove.first << " Second: " << botMove.second << endl;
                    if (board.setPos(botMove.first, botMove.second, turn)) {
                        turn = (turn == WHITE) ? BLACK : WHITE;
                    } else {
                        cout << "Bot made an invalid move" << endl;
                        break;
                    }
                }
                else
                {
                    #ifdef _WIN32
                    //system("cls");
                    #else
                    system("clear");
                    #endif

                    cout << endl
                        << "Invalid move" << endl;

                    #ifdef _WIN32
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    #else
                    sleep(2);
                    #endif
                }
            }
        }
    }
}

void testGame() {
    Board board;
    vector<int> moves;
    int moveFrom;
    int moveTo;
    Color turn = WHITE;
    pair<int, int> botMove;

    board.updateLegalMoves(WHITE);

    moves = board.getLegalMoves(5);

    for (int i = 0; i < moves.size(); i++) {
        cout << moves[i] << endl;
    }
    cout << "Printed all moves!" << endl;
}

int main()
{
    cout << "Program started" << endl;
   
    //gameLoopRoboMate(WHITE, 20);

    gameLoop1v1();

    //testGame();

    cout << endl
         << endl
         << "Program ended" << endl;
    int t;
    cin >> t;
    return 0;
}
