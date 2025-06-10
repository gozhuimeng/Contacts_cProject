//
// Created by meng on 25-5-21.
// DOC 主程序
//

#include <stdio.h>
#include <stdlib.h>

#include "modules/tool.h"
#include "modules/fileIO/config.h"
#include "modules/fileIO/dataFormat.h"
#include "modules/fileIO/importer.h"
#include "modules/fileIO/loader.h"
#include "modules/fileIO/saver.h"
#include "modules/func.h"


// void import() {
//     char filename[500];
//     int choice = 0;
//     printf("请输入要导入的文件名(相对路径和绝对路径均可): ");
//     scanf("%s", filename);
//     if (filename[0] == '\0') {
//         printf("非法操作：文件名为空，中断操作\n");
//         return;
//     }
//
//     printf("请选择导入方式:\n");
//     printf("\t1. 覆盖导入\n");
//     printf("\t2. 追加导入\n");
//     scanf("%d", &choice);
//     while (choice != 1 && choice != 2) {
//         printf("非法输入，请重新输入: ");
//         scanf("%d", &choice);
//     }
//     switch (choice) {
//         case 1:
//             break;
//         case 2:
//             printf("请输入追加方式:\n");
//             printf("\t1. 不检查重复项\n");
//             printf("\t2. 检查重复项\n");
//             choice = 0;
//             scanf("%d", &choice);
//             while (choice != 1 && choice != 2) {
//                 printf("非法输入，请重新输入: ");
//                 scanf("%d", &choice);
//             }
//             switch (choice) {
//                 case 1:
//                     break;
//                 case 2:
//                     break;
//             }
//     }
//     Grid *grid = loadGrid(filename);
//     printf("正在导入数据...\n");
// }

// void insert() {
//     printf("插入数据...\n");
// }
//
// void browse() {
//     printf("浏览数据...\n");
// }
//
// void query() {
//     printf("查询数据...\n");
// }
//
// void modify() {
//     printf("修改数据...\n");
// }
//
// void delete() {
//     printf("删除数据...\n");
// }
//
// void save() {
// }

int main() {
    system("chcp 65001 > nul");

    // 数据初始化
    printf("正在加载数据...\n");
    Grid *grid = loadGrid(DATA_FILE_NAME);
    printf("数据加载完成\n");

    int choice = 0;
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("非法输入，请重新输入\n");
            while (getchar() != '\n') {
            } // 清空输入缓冲区
            continue;
        }
        getchar(); // 清除换行符
        switch (choice) {
            case 0:
                // printf("data->len: %d\n", grid->len);
                quit(grid);
                break;
            case 1:
                grid = import_data(grid);
                break;
            case 2:
                grid = insert_data(grid);
                break;
            case 3:
                browse_data(grid);
                break;
            case 4:
                query_data(grid);
                break;
            case 5:
                grid = modify_data(grid);
                break;
            case 6:
                grid = delete_data(grid);
                break;
            case 7:
                export_data(grid);
                break;
            default:
                printf("非法输入，请输入操作选项序号！\n");
        }
    }
}
