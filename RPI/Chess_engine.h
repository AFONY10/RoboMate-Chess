#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <optional>
#include <vector>
#include "Chess_engine.h"

#include "subprocess.h"

using namespace std;

class Chess_engine {
private:
    subprocess_s stockfish_process_;
    int skill_level_; //
    int depth_; //
    string current_fen_ = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    optional<string> convertToChessNotation(int);
    int convertToNumber(const string&);
    string convertMoveToNotation(pair<int, int>);
    void getSkillAndDepthFromDifficulty(int, int &, int &);
    pair<pair<int, int>, string> get_best_move(string &);
    bool update_fen(string &, string &);
public:
    Chess_engine(int skill_level = 10);
    ~Chess_engine();
    pair<int, int> make_move(int, int);
    void reset(int);
    pair<int, int> get_last_move();
    void set_difficulty(int);
};