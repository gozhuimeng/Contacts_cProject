//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#include <stdio.h>
#include <stdbool.h>

#include "fileIO/dataFormat.h"
#include "tool.h"

#include <string.h>

bool check_grid_equal(const Grid *grid1, const Grid *grid2) {
    if (grid1 == NULL || grid2 == NULL) {
        return true;
    }
    if (grid1->len != grid2->len) {
        return false;
    }
    for (int i = 0; i < grid1->len; i++) {
        const Row *row1 = grid1->data[i];
        const Row *row2 = grid2->data[i];
        if (row1->len != row2->len) {
            return false;
        }
        for (int j = 0; j < row1->len; j++) {
            const Node *node1 = row1->data[j];
            const Node *node2 = row2->data[j];
            if (node1->len != node2->len) {
                return false;
            }
            if (strcmp(node1->str, node2->str)) {
                return false;
            }
        }
    }
    return true;
}
