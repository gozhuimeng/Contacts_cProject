//
// Created by meng on 25-5-23.
// DOC 工具函数
//

#include "tool.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "fileIO/dataFormat.h"
#include "fileIO/loader.h"

/**
 * 检查两个数据行是否一致
 * @param row1
 * @param row2
 * @return
 */
bool check_row_equal(const Row *row1, const Row *row2) {
    if (row1 == NULL || row2 == NULL) {
        // 如果有一个行为空，则认为不一致
        return false;
    }
    if (row1->len != row2->len) {
        // 如果行长度不一致，则认为不一致
        return false;
    }
    for (int j = 0; j < row1->len; j++) {
        // 遍历行中的每个节点
        const Node *node1 = row1->data[j];
        const Node *node2 = row2->data[j];
        if (node1->len != node2->len || strcmp(node1->str, node2->str) != 0) {
            // 比对节点长度和内容
            return false;
        }
    }
    return true;
}

/**
 * 检查数据表是否一致
 * @param grid1
 * @param grid2
 * @return
 */
bool check_grid_equal(const Grid *grid1, const Grid *grid2) {
    if (grid1 == NULL || grid2 == NULL) {
        // 如果有一个网格为空，则认为不一致
        return true;
    }
    if (grid1->len != grid2->len) {
        // 如果网格长度不一致，则认为不一致
        return false;
    }
    for (int i = 0; i < grid1->len; i++) {
        // 遍历网格中的每一行
        const Row *row1 = grid1->data[i];
        const Row *row2 = grid2->data[i];
        if (!check_row_equal(row1, row2)) {
            // 检查每一行是否一致
            return false;
        }
    }
    return true;
}

/**
 * 检查行是否存在于表中
 * @param grid
 * @param row
 * @return
 */
bool check_row_existing(const Grid *grid, const Row *row) {
    for (int i = 0; i < grid->len; i++) {
        // 遍历数据表中的每一行
        if (check_row_equal(grid->data[i], row)) {
            // 如果找到一致的行，则返回true
            return true;
        }
    }
    return false;
}


/**
 * 检查数据表中是否有同名行
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

/**
 * 通过姓名在数据表中查询行
 * @param grid
 * @return Grid
 */
Grid *select_by_name(const Grid *grid) {
    // 初始化变量
    char name[100];
    Grid *tempGrid = createGrid(); // 创建缓存数据表
    printf("请输入姓名: ");
    scanf("%s", name);
    for (int i = 0; i < grid->len; i++) {
        if (strcmp(name, grid->data[i]->data[0]->str) == 0) {
            appendGrid(tempGrid, grid->data[i]); // 如果姓名匹配，则将该行添加到缓存数据表中
        }
    }
    return tempGrid; // 返回缓存数据表
}

/**
 * 修改数据行内容
 * @param row
 * @return Row
 */
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
        while (scanf("%d", &choice) != 1 || choice < 0 || choice > 5) {
            // 输入检查
            printf("非法输入，请重新输入\n");
            scanf("%d", &choice);
        }
        switch (choice) {
            case 0: // 结束修改
                return row;
            case 1: // 修改姓名
                char name[100];
                printf("请输入姓名: ");
                scanf("%s", name);
                overwriteData(row->data[0], name); // 覆盖姓名数据
                break;
            case 2: // 修改籍贯
                char native[100];
                printf("请输入籍贯: ");
                scanf("%s", native);
                overwriteData(row->data[1], native); // 覆盖籍贯数据
                break;
            case 3: // 修改电话号码1
                long long phone1;
                printf("请输入电话号码1: ");
                while (scanf("%lld", &phone1) != 1 || phone1 < 10000000000 || phone1 > 19999999999) {
                    // 输入检查
                    printf("电话号码格式错误，请重新输入: ");
                }
                char phone1_str[20];
                sprintf(phone1_str, "%lld", phone1); // 将电话号码转换为字符串
                overwriteData(row->data[2], phone1_str); // 覆盖电话号码1数据
                break;
            case 4: // 修改电话号码2
                long long phone2;
                printf("请输入电话号码2: ");
                while (scanf("%lld", &phone2) != 1 || phone2 < 10000000000 || phone2 > 19999999999) {
                    printf("电话号码格式错误，请重新输入: ");
                }
                char phone2_str[20];
                sprintf(phone2_str, "%lld", phone2);
                overwriteData(row->data[3], phone2_str);
                break;
            case 5: // 修改电子邮箱
                char email[100];
                printf("请输入电子邮箱: ");
                scanf("%s", email);
                overwriteData(row->data[4], email);
                break;
        }
    }
}

/**
 * 修改数据表中的数据行
 * @param grid
 * @param row
 * @return Grid
 */
Grid *modify_item(Grid *grid, const Row *row) {
    int index = -1;
    for (int i = 0; i < grid->len; i++) {
        // 遍历数据表中的每一行
        if (check_row_equal(grid->data[i], row)) {
            // 查找行
            index = i;
            break;
        }
    }
    if (index == -1 || index == grid->len) {
        // 查找结果为空
        printf("执行出错，中断操作\n");
        return grid;
    }
    modify_row(grid->data[index]); // 调用修改数据行函数
    return grid;
}

/**
 * 删除数据表中的数据行
 * @param grid
 * @param row
 * @return Grid
 */
Grid *delete_item(Grid *grid, const Row *row) {
    printf("是否确认删除该行数据？(y/n): ");
    char choice;
    while (scanf("%c", &choice) != 1 || (choice != 'y' && choice != 'n' && choice != 'Y' && choice != 'N')) {
        // 输入检查
        printf("非法输入，请输入 y 或 n: ");
        while (getchar() != '\n') {
        } // 清空输入缓冲区
    }
    if (choice == 'Y' || choice == 'y') {
        for (int i = 0; i < grid->len; i++) {
            if (check_row_equal(grid->data[i], row)) {
                // 查找行
                for (int j = i; j < grid->len - 1; j++) {
                    grid->data[j] = grid->data[j + 1]; // 将后面的行前移
                }
                grid->len--; // 减少数据表长度
            }
        }
    } else {
        printf("取消删除操作\n");
    }
    return grid; // 返回修改后的数据表
}

/**
 * 打印单行数据
 * @param row
 */
void print_item(const Row *row) {
    if (row == NULL || row->len == 0) {  // 检查行是否为空或长度为0
        return;
    }
    printf("%-8s %-8s %-16s %-16s %-30s\n",
           row->data[0]->str,
           row->data[1]->str,
           row->data[2]->str,
           row->data[3]->str,
           row->data[4]->str);
}
