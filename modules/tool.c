//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#include <stdio.h>
#include <stdbool.h>

#include "fileIO/dataFormat.h"
#include "tool.h"

#include <stdlib.h>
#include <string.h>

#include "fileIO/loader.h"

bool check_row_equal(const Row *row1, const Row *row2) {
    if (row1 == NULL || row2 == NULL) {
        return false;
    }
    if (row1->len != row2->len) {
        return false;
    }
    for (int j = 0; j < row1->len; j++) {
        const Node *node1 = row1->data[j];
        const Node *node2 = row2->data[j];
        if (node1->len != node2->len || strcmp(node1->str, node2->str) != 0) {
            return false;
        }
    }
    return true;
}

/**
 * 检查数据是否一致
 * @param grid1
 * @param grid2
 * @return
 */
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
        if (!check_row_equal(row1, row2)) {
            return false;
        }
    }
    return true;
}

/**
 * 检查行是否存在于网络中
 * @param grid
 * @param row
 * @return
 */
bool check_row_existing(const Grid *grid, const Row *row) {
    for (int i = 0; i < grid->len; i++) {
        // Row *row2 = grid->data[i];
        // if (row->len == row2->len) {
        //     for (int j = 0;j< row->len; j++) {
        //         const Node *node1 = row->data[j];
        //         const Node *node2 = row2->data[j];
        //         if (node1->len != node2->len || strcmp(node1->str, node2->str) != 0) {
        //             break; // 如果有一个节点不相等，则跳出循环
        //         }
        //         if (j == row->len - 1) { // 如果所有节点都相等
        //             return true;
        //         }
        //     }
        // }
        if (check_row_equal(grid->data[i], row)) {
            return true;
        }
    }
    return false;
}


/**
 * 检查网格中是否有同名行
 * @param grid
 * @param row
 * @return
 */
bool check_row_name_existing(const Grid *grid, const Row *row) {
    for (int i = 0; i < grid->len; i++) {
        Row *row2 = grid->data[i];
        if (row2->data[0]->len == row->data[0]->len && strcmp(row2->data[0]->str, row->data[0]->str) == 0) {
            return true;
        }
    }
    return false;
}

Grid *select_by_name(const Grid *grid) {
    char name[100];
    Grid *tempGrid = createGrid();
    printf("请输入姓名: ");
    scanf("%s", name);
    for (int i = 0; i < grid->len; i++) {
        if (strcmp(name, grid->data[i]->data[0]->str) == 0) {
            appendGrid(tempGrid, grid->data[i]);
        }
    }
    return tempGrid;
}

Row *modify_row(Row *row) {
    while (1) {
        int choice = 0;
        printf("=====请选择=====\n");
        printf("1. 姓名\n");
        printf("2. 籍贯\n");
        printf("3. 电话号码1\n");
        printf("4. 电话号码2\n");
        printf("5. 电子邮箱\n");
        printf("0. 结束修改\n");
        printf("请输入操作选项序号: ");
        while (scanf("%d", &choice)!=1||choice < 0 || choice > 5) {
            printf("非法输入，请重新输入\n");
            scanf("%d", &choice);
        }
        switch (choice) {
            case 0:
                return row;
            case 1:
                char name[100];
                printf("请输入姓名: ");
                scanf("%s", name);
                overwriteData(row->data[0], name);
                break;
            case 2:
                char native[100];
                printf("请输入籍贯: ");
                scanf("%s", native);
                overwriteData(row->data[1], native);
                break;
            case 3:
                long long phone1;
                printf("请输入电话号码1: ");
                while (scanf("%lld", &phone1) != 1 || phone1 < 10000000000 || phone1 > 19999999999) {
                    printf("电话号码格式错误，请重新输入: ");
                    // printf("%lld", phone1);
                }
                char phone1_str[20];
                sprintf(phone1_str, "%lld", phone1);
                overwriteData(row->data[2], phone1_str);
                break;
            case 4:
                long long phone2;
                printf("请输入电话号码2: ");
                while (scanf("%lld", &phone2) != 1 || phone2 < 10000000000 || phone2 > 19999999999) {
                    printf("电话号码格式错误，请重新输入: ");
                }
                char phone2_str[20];
                sprintf(phone2_str, "%lld", phone2);
                overwriteData(row->data[3], phone2_str);
                break;
            case 5:
                char email[100];
                printf("请输入电子邮箱: ");
                scanf("%s", email);
                overwriteData(row->data[4], email);
                break;
        }
    }
}

Grid *modify_item(Grid *grid, const Row *row) {
    int index = -1;
    for (int i = 0; i < grid->len; i++) {
        if (check_row_equal(grid->data[i], row)) {
            index = i;
            break;
        }
    }
    if (index == -1 || index == grid->len) {
        printf("执行出错，中断操作\n");
        return grid;
    }
    modify_row(grid->data[index]);
    return grid;
}

Grid * delete_item(Grid *grid, const Row *row) {
    printf("是否确认删除该行数据？(y/n): ");
    char choice;
    while (scanf("%c", &choice) != 1 || (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N')) {
        printf("非法输入，请输入 y 或 n: ");
        while (getchar() != '\n') {} // 清空输入缓冲区
    }
    if (choice == 'Y' || choice == 'y') {
        for (int i = 0; i < grid->len; i++) {
            if (check_row_equal(grid->data[i], row)) {
                for (int j = i; j < grid->len - 1; j++) {
                    grid->data[j] = grid->data[j + 1];
                }
                grid->len--;
            }
        }
    }else {
        printf("取消删除操作\n");
    }
    return grid;
}

/**
 * 打印单行数据
 * @param row
 */
void print_item(const Row *row) {
    if (row == NULL || row->len == 0) {
        return;
    }
    // printf("姓名\t\t籍贯\t\t电话号码1\t\t电话号码2\t\t电子邮箱\n");
    // printf("%-8s %-8s %-14s %-14s %-25s\n", "姓名", "籍贯", "电话1", "电话2", "邮箱");
    printf("%-8s %-8s %-16s %-16s %-30s\n",
           row->data[0]->str,
           row->data[1]->str,
           row->data[2]->str,
           row->data[3]->str,
           row->data[4]->str);
    // TODO: 调整输出格式
    // for (int i = 0; i < row->len; i++) {
    //     printf("%s\t\t", row->data[i]->str);
    // }
}
