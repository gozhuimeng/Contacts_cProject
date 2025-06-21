//
// Created by meng on 25-5-21.
// DOC 文件保存器
//

#include "saver.h"

#include <stdio.h>

#include "dataFormat.h"
#include "loader.h"

/**
 * 打开文件并返回文件指针
 * @param filename
 * @return
 */
FILE *openFile_write(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件%s\n", filename);
        return NULL;
    }
    return file;
}

/**
 * 将一行数据转换为字符串
 * @param row
 * @return
 */
Node *buildString(const Row *row) {
    Node *string = createNode(); // 创建一个新的节点来存储字符串
    for (int i = 0; i < row->len; i++) {
        loadData(string, row->data[i]->str); // 将数据加载到字符串节点中
        if (i != row->len - 1) {
            appendChar(string, ','); // 在每个数据后添加逗号
        }
    }
    return string;
}

/**
 * 将表格数据写入文件
 * @param filename
 * @param grid
 */
void saveFile(char *filename, const Grid *grid) {
    FILE *file = openFile_write(filename); // 打开文件进行写入
    for (int i = 0; i < grid->len; i++) {
        Node *string = buildString(grid->data[i]); // 将每一行数据转换为字符串
        fprintf(file, "%s\n", string->str); // 将字符串逐行写入文件
        freeNode(&string); // 释放字符串节点的内存
    }
}
