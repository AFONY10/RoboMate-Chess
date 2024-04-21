#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <optional>
#include <vector>
#include "Chess_engine.h"

using namespace std;

// Constructor for the chess engine
Chess_engine::Chess_engine(int skill_level)
{
    const char *command_line[] = {"./Stockfish/src/stockfish", NULL};
    int result = subprocess_create(command_line, subprocess_option_combined_stdout_stderr, &stockfish_process_);
    if (0 != result)
    {
        std::cerr << "Failed to start Stockfish." << std::endl;
        std::cerr << "Error code:"<<result<<std::endl;
        exit(1);
    }

    FILE *stockfish_input = subprocess_stdin(&stockfish_process_);
    fputs("uci\n", stockfish_input);
    fflush(stockfish_input);

    set_difficulty(skill_level);
}

// Destructor for the chess engine
Chess_engine::~Chess_engine()
{
    // FILE *p_stdin = subprocess_stdin(&stockfish_process_);
    // FILE *p_stdout = subprocess_stdout(&stockfish_process_);
    // FILE *p_stderr = subprocess_stderr(&stockfish_process_);
    /*if (p_stdin)
        fclose(p_stdin);
    if (p_stdout)
        fclose(p_stdout);
    if (p_stderr)
        fclose(p_stderr);*/

    if(subprocess_destroy(&stockfish_process_)!=0){
        std::cout << "subprocess destroying" << std::endl;
    }
}

// Calculate skill level and depth from chosen difficulty
void Chess_engine::getSkillAndDepthFromDifficulty(int difficulty, int &skillLevel, int &depth)
{
    if (difficulty <= 0)
    {
        skillLevel = 1;
        depth = 1;
        return;
    }

    skillLevel = (difficulty + 1) / 2;
    depth = (difficulty + 1) / 2;

    if (difficulty % 2 == 0)
    {
        depth--;
    }

    if (skillLevel > 20)
        skillLevel = 20;
    if (depth > 20)
        depth = 20;
}

// Set the difficulty of the chess engine
void Chess_engine::set_difficulty(int level)
{
    getSkillAndDepthFromDifficulty(level, skill_level_, depth_);
    FILE *p_stdin = subprocess_stdin(&stockfish_process_);
    if (!p_stdin)
    {
        cerr << "Failed to get stdin for the Stockfish process." << endl;
        return;
    }
    fprintf(p_stdin, "setoption name Skill Level value %d\n", skill_level_);
    fflush(p_stdin);
}

// Get the best move from the chess engine and make the move
pair<int, int> Chess_engine::make_move(int start_pos, int end_pos)
{
    auto start_notation = convertToChessNotation(start_pos);
    auto end_notation = convertToChessNotation(end_pos);
    if (!start_notation || !end_notation)
    {
        cout << "Invalid move chess engine3" << endl;
        return {-1, -1};
    }
    string move = *start_notation + *end_notation;
    // moves_history_.push_back(move);
    auto result = get_best_move(move);

    pair<int, int> return_move_pair = result.first;
    string bestMove = result.second;
    if (return_move_pair == pair<int, int>{-1, -1} || bestMove == "")
    {
        cout << "Failed to get best move" << endl;
        return {-1, -1};
    }

    if (!update_fen(move, bestMove))
    {
        cout << "Failed to update fen" << endl;
        return {-1, -1};
    }
    return return_move_pair;
}

// Get the best move from the chess engine
pair<pair<int, int>, string> Chess_engine::get_best_move(string &move)
{
    FILE *p_stdin = subprocess_stdin(&stockfish_process_);
    FILE *p_stdout = subprocess_stdout(&stockfish_process_);
    if (!p_stdin || !p_stdout)
    {
        cout << "Failed to get stdio for the Stockfish process." << endl;
        return {{-1, -1}, ""};
    }
    fprintf(p_stdin, "position fen %s moves %s\n", current_fen_.c_str(), move.c_str());
    fprintf(p_stdin, "go movetime %d depth %d\n", 7000, depth_);
    fflush(p_stdin);
    // Læs Stockfish's output
    string stockfish_output = "";
    char buffer[128];
    while (true)
    {
        ssize_t amount_read = subprocess_read_stdout(&stockfish_process_, buffer, sizeof(buffer));
        if (amount_read > 0)
        {
            stockfish_output.append(buffer, amount_read);
            if (stockfish_output.find("bestmove") != std::string::npos)
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    string bestMove;
    size_t pos = stockfish_output.find("bestmove");
    if (pos != string::npos)
    {
        bestMove = stockfish_output.substr(pos + 9, 4);
        int startPos = convertToNumber(bestMove.substr(0, 2));
        int endPos = convertToNumber(bestMove.substr(2, 2));
        return {{startPos, endPos}, bestMove};
    }
    return {{-1, -1}, ""};
}

// Update the fen based on the move and best move
bool Chess_engine::update_fen(string &move, string &bestMove)
{

    FILE *p_stdin = subprocess_stdin(&stockfish_process_);
    FILE *p_stdout = subprocess_stdout(&stockfish_process_);
    if (!p_stdin || !p_stdout)
    {
        cout << "Failed to get stdio for the Stockfish process." << endl;
        return false;
    }
    fprintf(p_stdin, "position fen %s moves %s %s\n", current_fen_.c_str(), move.c_str(), bestMove.c_str());
    fprintf(p_stdin, "d\n");
    fflush(p_stdin);

    string stockfish_output = "";

    string fen;
    bool fenStart = false;
    char buffer[128];
    while (true)
    {
        ssize_t amount_read = subprocess_read_stdout(&stockfish_process_, buffer, sizeof(buffer));
        if (amount_read > 0)
        {
            stockfish_output.append(buffer, amount_read);
            if (stockfish_output.find("Fen: ") != std::string::npos)
            {
                fenStart = true;
            }
            if (fenStart)
            {
                size_t fenEnd = stockfish_output.find("\n", stockfish_output.find("Fen: "));
                if (fenEnd != std::string::npos)
                {
                    fen = stockfish_output.substr(stockfish_output.find("Fen: ") + 5, fenEnd - (stockfish_output.find("Fen: ") + 5));
                    break;
                }
            }
        }
        else
        {
            return false;
            break;
        }
    }
    current_fen_ = fen;
    return true;
}

// Convert the number to chess notation (e.g 17 -> b3) 
optional<string> Chess_engine::convertToChessNotation(int num)
{
    if (num < 0 || num > 63)
        return nullopt;

    char files[] = "abcdefgh";
    char rank = '1' + (num / 8);
    char file = files[num % 8];

    return string(1, file) + rank;
}

// Convert the chess notation to a number (e.g b3 -> 17)
int Chess_engine::convertToNumber(const string &notation)
{
    if (notation.size() != 2)
        return -1;

    char file = notation[0];
    char rank = notation[1];

    int fileNum = file - 'a';
    int rankNum = rank - '1';

    return rankNum * 8 + fileNum;
}

// Convert the move to chess notation (e.g 17 to 25 -> b3b4)
string Chess_engine::convertMoveToNotation(pair<int, int> move)
{
    auto start_notation = convertToChessNotation(move.first);
    auto end_notation = convertToChessNotation(move.second);

    if (!start_notation || !end_notation)
    {
        return "";
    }

    return *start_notation + *end_notation;
}

// Reset the chess engine
void Chess_engine::reset(int level)
{
    // moves_history_.clear();
    current_fen_ = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    set_difficulty(level);
    FILE *p_stdin = subprocess_stdin(&stockfish_process_);
    if (!p_stdin)
    {
        cerr << "Failed to get stdin for the Stockfish process." << endl;
        return;
    }
    fprintf(p_stdin, "position startpos\n");
    fflush(p_stdin);
}
