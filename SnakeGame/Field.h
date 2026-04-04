#pragma once
#include "Constants.h"
#include "Cell.h"

namespace SnakeGame
{
    struct Field
    {
        Cell cells[NUMBER_CELLS][NUMBER_CELLS] = {};
    };

    void InitField(Field& field);
}
