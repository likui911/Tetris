#include "Square.h"

Square::Square() :m_iRow{ 0 }, m_iCol{ 0 }
{
}

Square::Square(int col, int row) : m_iRow{ row }, m_iCol{ col }
{
}

Square::~Square()
{
}