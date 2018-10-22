#ifndef POSITION_H
#define POSITION_H
struct Position
{
    int Line;
    int Column;
    Position():Line(0),Column(0) {}
    Position(int line, int column):Line(line),Column(column) {}
    int AsIndex(int Width) {return Line*Width + Column; }
};
#endif // POSITION_H
