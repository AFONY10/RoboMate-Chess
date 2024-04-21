#include "Board.h"
#include "Pieces/Bishop.h"
#include "Pieces/King.h"
#include "Pieces/Knight.h"
#include "Pieces/Pawn.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include <thread>
#include <iostream> //Skal fjernes til IMPL
#include <algorithm>

// Constructor
Board::Board()
{
    resetBoard();
    updateLegalMoves(WHITE);
    updateLegalMoves(BLACK);
}

// Destructor
Board::~Board()
{
    std::cout << "Board destrcutor called" << std::endl;
    for (Piece *p : board_)
    {
        if (p != nullptr)
        {
            delete p;
            p = nullptr;
        }
    }
    std::cout << "Board destrcutor completed" << std::endl;
}

// Get the bot
Chess_engine &Board::getBot()
{
    return bot_;
}

// Responsible for setting the position of a piece
bool Board::setPos()
{
    int capture = -1;
    pair<int, int> castle = make_pair(-1, -1);
    Piece *p = board_[fromPos_];
    bool isLegal = false;
    if (p == nullptr || p->getColor() != turn_)
    {
        return isLegal;
    }

    for (const int m : p->getLegalMoves())
    {
        if (toPos_ == m)
        {
            isLegal = true;

            // Check for capture
            if (board_[toPos_] != nullptr)
            {
                if (gamemode_ == PVE && playerColor_ != turn_)
                    capture = toPos_;

                delete board_[toPos_];
                board_[toPos_] = nullptr;
                movesSinceCapture_ = 0;
            }

            // Check for en passant
            else if (p->getType() == PAWN)
            {
                Pawn* pawn = static_cast<Pawn*>(p);

                pair<int, int> lastMove = this->getLastMove();
                vector<int> diagonals = pawn->getDiagonals();
                int legalMove = pawn->getPawnLegalMoves()[0];
                int enPassantPos = toPos_ - legalMove;
                Piece *enPassantBonde = board_[enPassantPos];

                if (find(diagonals.begin(), diagonals.end(), toPos_ - fromPos_) != diagonals.end() // Check if pawn is moving diagonally
                    && enPassantBonde != nullptr                                                 // Check if there is a piece on the en passant position
                    && enPassantBonde->getType() == PAWN                                         // Check if the piece is a pawn
                    && enPassantBonde->getColor() != p->getColor()                               // Check if the pawn is the opposite color
                    && lastMove.second == enPassantPos                                           // Check if the last move was the pawn moving 2 spaces
                    && lastMove.first == lastMove.second + legalMove * 2)                        // Check if the last move was the pawn moving 2 spaces
                {
                    delete enPassantBonde;
                    capture = enPassantPos;
                    board_[enPassantPos] = nullptr;
                    movesSinceCapture_ = 0;
                }
            }

            // Check for castle
            else
            {
                if (p->getType() == KING && p->hasMoved() == false)
                {
                    if (toPos_ - fromPos_ == -2 || toPos_ - fromPos_ == 2)
                    {
                        // Castle
                        int rookPos = toPos_ - fromPos_ == -2 ? fromPos_ - 4 : fromPos_ + 3;
                        Piece *rook = board_[rookPos];
                        if (rook->getType() == ROOK && rook->hasMoved() == false)
                        {
                            int rookToPos = toPos_ - fromPos_ == -2 ? toPos_ + 1 : toPos_ - 1;
                            board_[rookPos] = nullptr;
                            board_[rookToPos] = rook;
                            rook->setPos(rookToPos);

                            castle.first = rookPos;
                            castle.second = rookToPos;
                        }
                    }
                }
                movesSinceCapture_++;
            }

            // Check for promotion
            if (p->getType() == PAWN)
            {
                if (toPos_ < 8 || toPos_ > 55)
                {
                    Color tempColor = p->getColor();
                    delete board_[fromPos_];
                    board_[fromPos_] = nullptr;
                    board_[toPos_] = new Queen(tempColor, toPos_);
                    board_[toPos_]->updateBoard(this);
                    p = board_[toPos_];
                }
            }

            // Move piece from fromPos_ to toPos_
            board_[fromPos_] = nullptr;
            board_[toPos_] = p;
            p->setPos(toPos_);

            setLastMove(fromPos_, toPos_);
            // Place move in previousBoards_ string, so the string contains all previous board states
            previousBoards_.emplace_back(getBoardString());
            break;
        }
    }


    
    if (gamemode_ == PVE && turn_ != playerColor_) {
        if (capture != -1) {
            didCapturePiece();
        } else if (castle.first != -1) {
            emit movePiece(castle.first, castle.second);
            setState(WAITING_FOR_CASTLE_MOVE);
        } else {
            didMovePiece();
        }
    }

    // return true if the move was legal, else false
    return isLegal;
}

// Set the board to default state
void Board::resetBoard()
{

    for (Piece *p : board_)
    {
        if (p != nullptr)
        {
            delete p;
            p = nullptr;
        }
    }

    board_.resize(BOARD_SIZE, nullptr);

    // Put the white pieces
    board_[0] = new Rook(WHITE, 0);
    board_[1] = new Knight(WHITE, 1);
    board_[2] = new Bishop(WHITE, 2);
    board_[3] = new Queen(WHITE, 3);
    board_[4] = whiteKing_ = new King(WHITE, 4);
    board_[5] = new Bishop(WHITE, 5);
    board_[6] = new Knight(WHITE, 6);
    board_[7] = new Rook(WHITE, 7);
    for (int i = 8; i < 16; ++i)
    {
        board_[i] = new Pawn(WHITE, i);
    }

    // Put the black pieces
    board_[56] = new Rook(BLACK, 56);
    board_[57] = new Knight(BLACK, 57);
    board_[58] = new Bishop(BLACK, 58);
    board_[59] = new Queen(BLACK, 59);
    board_[60] = blackKing_ = new King(BLACK, 60);
    board_[61] = new Bishop(BLACK, 61);
    board_[62] = new Knight(BLACK, 62);
    board_[63] = new Rook(BLACK, 63);
    for (int i = 48; i < 56; ++i)
    {
        board_[i] = new Pawn(BLACK, i);
    }

    // Opdater board reference i alle Pieces
    for (long unsigned int i = 0; i < board_.size(); ++i)
    {
        if (board_[i] != nullptr)
            board_[i]->updateBoard(this);
    }
    turn_=WHITE;
    fromPos_ = -1;
    toPos_ = -1;
    movesSinceCapture_ = 0;
    lastMove_ = {-1,-1};

    bot_.reset(difficulty_);


}


// returns true if the position pos on the board is taken, else false
Piece *Board::isSpotTaken(int pos)
{
    return board_[pos];
}

// return legal moves from the position pos on the board
vector<int> Board::getLegalMoves(int pos)
{
    if (board_[pos] != nullptr)
    {
        return board_[pos]->getLegalMoves();
    }
    else
        return {-1};
}

vector<Piece *> Board::getOppositeColors(Color currentColor)
{
    vector<Piece *> oColors;
    // Get all pieces of opposite color on the board
    for (Piece *p : board_)
    {
        if (p != nullptr && p->getColor() != currentColor)
        {
            oColors.emplace_back(p);
        }
    }
    return oColors;
}

// Print the board for debugging purposes
void Board::printBoard() const
{ 
    for (int j = board_.size() - 1; j >= 0; --j)
    {
        int i = (j / 8) * 8 + (7 - (j % 8));
        if ((j + 1) % 8 == 0)
            cout << endl
                 << "|------|------|------|------|------|------|------|------|" << endl
                 << "|";
        if (i < 10)
            cout << "0";

        if (board_[i] != nullptr)
        {
            if (board_[i]->getColor() == WHITE)
            {
                cout << i << ":W";
            }
            else
            {
                cout << i << ":B";
            }

            if (board_[i]->getType() == PAWN)
            {
                cout << "P";
            }
            else if (board_[i]->getType() == KNIGHT)
            {
                cout << "N";
            }
            else if (board_[i]->getType() == BISHOP)
            {
                cout << "B";
            }
            else if (board_[i]->getType() == ROOK)
            {
                cout << "R";
            }
            else if (board_[i]->getType() == QUEEN)
            {
                cout << "Q";
            }
            else if (board_[i]->getType() == KING)
            {
                cout << "K";
            }
        }
        else
        {
            cout << i << ":  ";
        }
        cout << " ";
        cout << "|";
    }

    cout << endl
         << "|------|------|------|------|------|------|------|------|" << endl;
}

// Print the board with legal moves for debugging purposes
void Board::printBoardWithLegalMoves(const vector<int> &legalMoves) const
{
    for (int j = board_.size() - 1; j >= 0; --j)
    {
        int i = (j / 8) * 8 + (7 - (j % 8));
        if ((j + 1) % 8 == 0)
            cout << endl
                 << "|------|------|------|------|------|------|------|------|" << endl
                 << "|";
        if (i < 10)
            cout << "0";

        // Tjek om positionen er et lovlige træk
        bool isLegalMove = find(legalMoves.begin(), legalMoves.end(), i) != legalMoves.end();

        if (board_[i] != nullptr)
        {
            if (board_[i]->getColor() == WHITE)
            {
                cout << i << ":W";
            }
            else
            {
                cout << i << ":B";
            }

            // Print briktypen
            switch (board_[i]->getType())
            {
            case PAWN:
                cout << "P";
                break;
            case KNIGHT:
                cout << "N";
                break;
            case BISHOP:
                cout << "B";
                break;
            case ROOK:
                cout << "R";
                break;
            case QUEEN:
                cout << "Q";
                break;
            case KING:
                cout << "K";
                break;
            }
        }
        else
        {
            // Hvis positionen er et lovlige træk, print et specielt tegn, fx '*'
            cout << i << ":  ";
        }
        cout << (isLegalMove ? "*" : " ");

        cout << "|";
    }

    cout << endl
         << "|------|------|------|------|------|------|------|------|" << endl;
}

// Returns the pieces that are checking the king
vector<Piece *> Board::getPiecesCheckingKing(Color kingColor)
{
    vector<Piece *> oppositePieces = getOppositeColors(kingColor);
    vector<Piece *> piecesCheckingKing;

    for (Piece *p : oppositePieces)
    {
        for (int m : p->getLegalMoves())
        {
            if (board_[m] == (kingColor == WHITE ? whiteKing_ : blackKing_))
            {
                piecesCheckingKing.emplace_back(p);
                break;
            }
        }
    }
    return piecesCheckingKing;
}

// Returns the moves that can defend against a check. (Position of attacking piece or blocking the attack)
vector<int> Board::getCheckDefendingMoves(Color color)
{
    vector<Piece *> piecesCheckingKing = getPiecesCheckingKing(color);
    vector<int> defendingMoves;
    for (Piece *p : piecesCheckingKing)
    {
        defendingMoves.emplace_back(p->getPos());
    }

    // Check for blocking moves
    if (piecesCheckingKing.size() == 1)
    { // Can only block, if only 1 piece is attacking king
        switch (piecesCheckingKing[0]->getType())
        {
        case KNIGHT: // Knight, pawn can't be blocked
        case PAWN:
            break;
        default:
            Piece *king = color == WHITE ? whiteKing_ : blackKing_;
            int kingPos = king->getPos();
            int attackPos = piecesCheckingKing[0]->getPos();

            // Get the direction of the check (from king to attacking piece)
            int posDif = attackPos - kingPos;
            int dir = 0;
            int dist = 0;
            int factors[] = {9, 8, 7, 1};
            for (int f : factors)
            {
                if (posDif % f == 0)
                {
                    dir = f * posDif / abs(posDif);
                    dist = abs(posDif / f);
                    break;
                }
            }

            // All moves between king and attacking piece are blocking moves
            for (int i = 1; i < dist; i++)
            {
                defendingMoves.emplace_back(kingPos + dir * i);
            }
            break;
        }
    }

    return defendingMoves;
}

// Returns true if any piece can make a move, else false.
bool Board::updateLegalMoves(Color color)
{
    bool canMakeMoves = false;
    for (Piece *p : board_)
    {
        if (p != nullptr && p->getColor() == color)
        {
            bool canMove = p->updateLegalMoves();
            if (canMove)
            {
                canMakeMoves = canMove;
            }
        }
    }

    if (color == WHITE)
    {
        whiteCanMove_ = canMakeMoves;
    }
    else
    {
        blackCanMove_ = canMakeMoves;
    }

    return canMakeMoves;
}

// Returns true if the king of the color is in checkmate, else false
bool Board::checkForCheckmate(Color color)
{
    bool colorCanMove = color == WHITE ? blackCanMove_ : whiteCanMove_;

    if (getPiecesCheckingKing(color).size() > 0 && !colorCanMove)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Check if the color is in stalemate
bool Board::checkForStalemate(Color color)
{
    bool colorCanMove = color == WHITE ? whiteCanMove_ : blackCanMove_;

    if (getPiecesCheckingKing(color).size() == 0 && !colorCanMove)
    {
        return true;
    }

    if (hasBoardBeen3Times())
    {
        return true;
    }

    if (deadPosition())
    {
        return true;
    }

    if (movesSinceCapture_ >= 50)
    {
        return true;
    }

    return false;
}

// Returns full string of the current board state
string Board::getBoardString()
{
    string board = "";
    for (long unsigned int i = 0; i < board_.size(); i++)
    {
        if (board_[i] != nullptr)
        {
            switch (board_[i]->getType())
            {
            case PAWN:
                board += "P";
                break;
            case KNIGHT:
                board += "N";
                break;
            case BISHOP:
                board += "B";
                break;
            case ROOK:
                board += "R";
                break;
            case QUEEN:
                board += "Q";
                break;
            case KING:
                board += "K";
                break;
            default:
                board += "0";
                break;
            }
        }
        else
        {
            board += "0";
        }
    }
    return board;
}

// Check if the current board state has been 3 times before, so the game is a draw
bool Board::hasBoardBeen3Times()
{
    int copiesOfBoard = 0;

    for (long unsigned int i = 0; i < previousBoards_.size(); i++)
    {
        if (previousBoards_[i] == getBoardString())
        {
            copiesOfBoard++;
        }
    }

    if (copiesOfBoard >= 3)
    {
        return true;
    }

    else
    {
        return false;
    }
}

// Check if the current board state is a dead position
bool Board::deadPosition()
{
    int wSquareBishops = 0;
    int bSquareBishops = 0;
    int knights = 0;
    bool deadPos = false;

    for (Piece *p : board_)
    {
        if (p != nullptr)
        {
            if (p->getType() == PAWN || p->getType() == QUEEN || p->getType() == ROOK)
            {
                return false;
            }
            else if (p->getType() == BISHOP)
            {
                if (p->getPos() % 2 == 0)
                    bSquareBishops++;
                else
                    wSquareBishops++;
            }
            else if (p->getType() == KNIGHT)
            {
                knights++;
            }
        }
    }

    int bishops = wSquareBishops + bSquareBishops;

    if ((knights == 0 && bishops == 0) ||
        (knights == 0 && bishops == 1) ||
        (knights == 1 && bishops == 0) ||
        (knights == 0 && ((wSquareBishops == 2 && bSquareBishops == 0) ^ (bSquareBishops == 2 && wSquareBishops == 0))))
    {
        deadPos = true;
    }

    return deadPos;
}

// Simulate a move from position from to position to, and return true if the move is legal, else false (in case of self-check)
bool Board::simulateMove(int from, int to)
{
    Piece *movingP = board_[from];
    Piece *tempP = board_[to];

    bool isLegal = true;
    Color color = movingP->getColor();
    int kingPos = color == WHITE ? whiteKing_->getPos() : blackKing_->getPos();

    // Simulate pieces movement
    board_[from] = nullptr;
    board_[to] = movingP;

    // Calc opposite pieces simulated moves
    for (Piece *p : board_)
    {
        if (p != nullptr && p->getColor() != color)
        {
            vector<int> legalMoves = p->calcLegalMoves();
            if (find(legalMoves.begin(), legalMoves.end(), kingPos) != legalMoves.end())
            {
                isLegal = false;
                break;
            }
        }
    }

    // Reset board
    board_[from] = movingP;
    board_[to] = tempP;

    return isLegal;
}

// Set the last move made on board, saved in lastMove_
void Board::setLastMove(int from, int to)
{
    lastMove_ = make_pair(from, to);
}

// Set player color if the game is not currently running
void Board::setPlayerColor(Color color)
{
    if (isGameRunning_) return;
    playerColor_ = color;
}

// Called when a piece is placed on the board. 
void Board::didPlacePiece(int toPos)
{
    // If the game is not running, or the state is not waiting for a piece to be placed, return
    if (!isGameRunning_ ||
           (state_ != WAITING_FOR_PLACE_PIECE &&
            state_ != WAITING_FOR_PLACE_PIECE_IL))
        return;

    toPos_ = toPos;

    // If the state is WAITING_FOR_PLACE_PIECE_IL, check if the piece is placed on the same position as it was lifted from (illegal move)
    if (state_ == WAITING_FOR_PLACE_PIECE_IL) {
        if (toPos_ == fromPos_) {
            toPos_ = -1;
            fromPos_ = -1;
            setState(WAITING_FOR_LIFT_PIECE);
        }
    }
    
    if (fromPos_ != toPos_ && fromPos_ != -1 && toPos_ != -1)
    {
        // If the move is legal, set the position of the piece
        if (setPos())
        {
            turn_ = (turn_ == WHITE) ? BLACK : WHITE;
            emit changeTurn(turn_);
            updateLegalMoves(WHITE);
            updateLegalMoves(BLACK);

            if (checkForCheckmate(turn_))
            {
                emit checkMate(turn_);

                isGameRunning_ = false;
            }
            else if (checkForStalemate(turn_))
            {
                emit staleMate();
                isGameRunning_ = false;
            }

            if (gamemode_ == PVE)
                makeBotMove();
            setState(WAITING_FOR_LIFT_PIECE);

        } 
        // else if illegal, set state to WAITING_FOR_LIFT_PIECE_IL and emit illegalMove() 
        else {

            toPos_ = -1;
            emit illegalMove();
            setState(WAITING_FOR_LIFT_PIECE_IL);
        }   
    }
}

// Called when a piece is lifted from the board
void Board::didLiftPiece(int fromPos)
{
    // Failsafe if the game is not running
    if (!isGameRunning_)
        return;

    // If the state is not waiting for a piece to be lifted, return
    switch (state_) {
    case WAITING_FOR_LIFT_PIECE_IL:
        emit legalmoves(getLegalMoves(fromPos_));
        setState(WAITING_FOR_PLACE_PIECE_IL);
        break;
    case WAITING_FOR_LIFT_PIECE:
        fromPos_ = fromPos;
        emit legalmoves(getLegalMoves(fromPos_));
        setState(WAITING_FOR_PLACE_PIECE);
        break;
    default:
        break;
    }
}

// Called when a piece is captured
void Board::didCapturePiece() {
    if (!isGameRunning_ || state_ != WAITING_FOR_PLACE_PIECE) return;
    emit capturePiece(toPos_);
    setState(WAITING_FOR_DEAD_PIECE);
}

// Called when a piece is moved
void Board::didMovePiece() {
    if (!isGameRunning_ ||
           (state_ != WAITING_FOR_PLACE_PIECE &&
            state_ != WAITING_FOR_DEAD_PIECE &&
            state_ != WAITING_FOR_CASTLE_MOVE))
        return;

    emit movePiece(fromPos_, toPos_);
    setState(WAITING_FOR_MOVE_PIECE);
}

// Set difficulty if the game is not currently running
void Board::setDifficulty(int difficulty) {
    if (isGameRunning_) return;
    difficulty_ = difficulty;
}

// Called when a piece is done moving
void Board::didFinishMovePiece() {
    switch (state_)
    {
    case WAITING_FOR_DEAD_PIECE:
        didMovePiece();
        break;
    case WAITING_FOR_MOVE_PIECE:
        fromPos_ = -1;
        toPos_ = -1;
        setState(WAITING_FOR_LIFT_PIECE);
        break;
    case WAITING_FOR_CASTLE_MOVE:
        didMovePiece();
        break;
    default:
        break;
    }
}

// Called when the game is started
void Board::didStartGame(bool againstBot) {
    // Failsafe if the game is already running
    if (isGameRunning_) return;
    isGameRunning_ = true;
    gamemode_ = againstBot ? PVE : PVP;

    if (gamemode_ == PVE && playerColor_ != WHITE) {
        makeBotMove();
    }
    setState(WAITING_FOR_LIFT_PIECE);
}

/*void Board::gameLoop1v1()
{
    vector<int> moves;
    int moveFrom;
    int moveTo;
    Color turn = WHITE;

    while (true)
    {

        updateLegalMoves(WHITE);
        updateLegalMoves(BLACK);

        if (checkForCheckmate(turn))
        {
            cout << endl
                 << "Checkmate" << endl;
            break;
        }
        else if (checkForStalemate(turn))
        {
            cout << endl
                 << "Stalemate" << endl;
            break;
        }
        else if (playerResigned_)
        {
            cout << endl
                 << "Player has resigned" << endl;
            break;
        }

        cout << "Waiting for player lift piece" << endl;
        while (!playerResigned_)
        {
            if (uart_.didLiftPiece() != -1)
            {
                moveFrom = uart_.didLiftPiece();
                break;
            }
        }
        if (playerResigned_)
        {
            cout << endl
                 << "Player has resigned" << endl;
            break;
        }

        uart_.sendLegalMoves(getLegalMoves(moveFrom));
        cout << "Waiting for player put down piece" << endl;
        while (!playerResigned_)
        {
            if (uart_.didPlacePiece())
            {
                moveTo = uart_.didPlacePiece();
                break;
            }
        }

        if (playerResigned_)
        {
            cout << endl
                 << "Player has resigned" << endl;
            break;
        }
        if (moveTo != moveFrom)
        {
            if (setPos(moveFrom, moveTo, turn))
            {
                turn = (turn == WHITE) ? BLACK : WHITE;
            }
            else
            {
                cout << endl
                     << "Invalid move" << endl;
            }
        }
    }
    playerResigned_ = false;
}

void Board::gameLoop1vBot()
{
    int difficulty = 20;
    Color playerColor = WHITE;
    vector<int> moves;
    int moveFrom;
    int moveTo;
    Color turn = WHITE;
    pair<int, int> botMove;

    getBot().set_difficulty(difficulty);

    while (true)
    {

        updateLegalMoves(WHITE);
        updateLegalMoves(BLACK);

        if (checkForCheckmate(turn))
        {
            cout << endl
                 << "Checkmate" << endl;
            break;
        }
        else if (checkForStalemate(turn))
        {
            cout << endl
                 << "Stalemate" << endl;
            break;
        }
        else if (playerResigned_)
        {
            cout << endl
                 << "Player has resigned" << endl;
            break;
        }

        if (turn == playerColor)
        {

            cout << "Waiting for player lift piece" << endl;
            while (!playerResigned_)
            {
                if (uart_.didLiftPiece() != -1)
                {
                    moveFrom = uart_.didLiftPiece();
                    break;
                }
            }
            if (playerResigned_)
            {
                cout << endl
                     << "Player has resigned" << endl;
                break;
            }

            uart_.sendLegalMoves(getLegalMoves(moveFrom));

            cout << "Waiting for player put down piece" << endl;
            while (!playerResigned_)
            {
                if (uart_.didPlacePiece())
                {
                    moveTo = uart_.didPlacePiece();
                    break;
                }
            }

            if (playerResigned_)
            {
                cout << endl
                     << "Player has resigned" << endl;
                break;
            }

            if (moveTo != moveFrom)
            {
                if (setPos(moveFrom, moveTo, turn))
                {
                    turn = (turn == WHITE) ? BLACK : WHITE;

                    updateLegalMoves(WHITE);
                    updateLegalMoves(BLACK);

                    botMove = getBot().make_move(moveFrom, moveTo);
                    if (setPos(botMove.first, botMove.second, turn))
                    {
                        uart_.sendMove(botMove.first, botMove.second);
                        turn = (turn == WHITE) ? BLACK : WHITE;
                        emit changeTurn(turn);

                        cout << "Waiting for bot finish moving piece" << endl;
                        while (!playerResigned_ && !uart_.didFinishMovePiece())
                        {
                        }
                    }
                    else
                    {
                        cout << "Bot made an invalid move" << endl;
                        break;
                    }
                }
                else
                {

                    cout << endl
                         << "Invalid move" << endl;
                }
            }
        }
    }
    playerResigned_ = false;
} */

// Called when the player resigns
void Board::didPlayerResign()
{
    std::cout << "PLayer resigns"<<std::endl;
    if (!isGameRunning_) return;
    setState(NOT_INGAME);
    isGameRunning_ = false;
    resetBoard();
}

// RoboMate makes a move
void Board::makeBotMove() {
    if (gamemode_ == PVE) {
        pair<int, int> botMove = getBot().make_move(fromPos_, toPos_);
        fromPos_ = botMove.first;
        toPos_ = botMove.second;
        if (setPos())
        {
            turn_ = (turn_ == WHITE) ? BLACK : WHITE;
            emit changeTurn(turn_);

            updateLegalMoves(WHITE);
            updateLegalMoves(BLACK);

            if (checkForCheckmate(turn_))
            {
                emit checkMate(turn_);
                isGameRunning_ = false;
            }
            else if (checkForStalemate(turn_))
            {
                emit staleMate();
                isGameRunning_ = false;
            }
        }
    }
}

// Set the state of the game
void Board::setState(State s) {
    state_ = s;
    switch(state_) {
    case NOT_INGAME:
        cout << endl << "NOT_INGAME" << endl;
        break;
    case WAITING_FOR_DEAD_PIECE:
        cout << endl << "WAITING_FOR_DEAD_PIECE" << endl;
        break;
    case WAITING_FOR_MOVE_PIECE:
        cout << endl << "WAITING_FOR_MOVE_PIECE" << endl;
        break;
    case WAITING_FOR_CASTLE_MOVE:
        cout << endl << "WAITING_FOR_CASTLE_MOVE" << endl;
        break;
    case WAITING_FOR_PLACE_PIECE:
        cout << endl << "WAITING_FOR_PLACE_PIECE" << endl;
        break;
    case WAITING_FOR_LIFT_PIECE:
        cout << endl << "WAITING_FOR_LIFT_PIECE" << endl;
        break;
    case WAITING_FOR_LIFT_PIECE_IL:
        cout << endl << "WAITING_FOR_LIFT_PIECE_IL" << endl;
        break;
    case WAITING_FOR_PLACE_PIECE_IL:
        cout << endl << "WAITING_FOR_PLACE_PIECE_IL" << endl;
        break;
    default:
        cout << endl << "Statenum: " << s << endl;
        break;
    }
}
