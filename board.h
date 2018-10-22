#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "position.h"

#include <string>
#include <iostream>
class Tile;
class Board {
public:
    Board();
    void GetInfoFromString(std::string input_str);
    void ResetAllVisited(Position position);
    void MarkVisited(Position position);
    char operator()(int line, int col);
    int GetBoardX() const { return m_boardX; }
    int GetBoardY() const { return m_boardY; }
    int GetSolLengthMin() { return m_insMin; }
    int GetSolLengthMax() { return m_insMax; }
    int GetLevel() const { return m_level; }
    Board* GetSubBoard(int originLine, int originColumn, int lines, int columns);
    Board operator+(const Board& board) const;
    void BackupData() { m_dataBackup.assign(m_data); }
    void RestoreData() { m_data.assign(m_dataBackup); }
    void MergeFromOffset(int offsetRow, int offsetCol, int wide);

    Tile* CreateTile();
    friend std::ostream& operator<< (std::ostream &out, Board& board);
    friend std::ostream& operator<< (std::ostream &out, Board* board);
    friend class Tile;

    void Mark(Position position, char c);
private:
    int m_insMin;
    int m_insMax;
    int m_boardX;
    int m_boardY;
    int m_level;
    std::string m_data;
    std::string m_dataBackup;
};

#endif // BOARD_H
