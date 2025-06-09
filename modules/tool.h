//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#ifndef TOOL_H
#define TOOL_H

#include<stdbool.h>

#include "fileIO/dataFormat.h"

bool check_grid_equal(const Grid *grid1, const Grid *grid2);

bool check_row_existing(const Grid *grid, const Row *row);

#endif //TOOL_H
