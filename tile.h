#ifndef TILE_H
#define TILE_H

#include "board.h"
#include "position.h"

#include <string>
#include <iostream>
class Board;
class Tile
{
public:
    enum TileType
    {
        Empty,
        Visited,
        Wall,
        DeadEnd,
        Exit
    };

    Tile(Board* board);
    void SetPath(std::string path);
    void SetPosition(int row, int col);
    bool Next();
    bool GoRight();
    bool GoDown();
    bool DropLastDirection();
    bool DropAllCheckedDirections();
    void DoubleThePath();
    Position GetPosition() { return m_position; }
    std::string GetPath() { return m_path; }
    TileType GetType();
    void SetType(TileType type);
    Tile& operator=(const Tile& other);
private:
    void PathToPosition();
    Position m_position;
    std::string m_path;
    Board* m_board;
    char m_face;
    int m_iterator;
};
#endif // TILE_H
