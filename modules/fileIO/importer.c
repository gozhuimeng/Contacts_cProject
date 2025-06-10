//
// Created by meng on 25-5-13.
// DOC 文件数据导入器(从文件导入数据)
//

#include "importer.h"
#include "dataFormat.h"
#include "loader.h"

/**
 * 打开文件
 * @param filename
 * @return 文件指针
 */
FILE *openFile_read(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // printf("无法打开文件%s", filename);
        printf("无法找到数据文件%s\n", filename);
        return NULL;
    }
    return file;
}

/**
 * 将文件中的数据加载到节点中
 * @param file
 * @return
 */
Node *loadNode(FILE *file) {
    Node *node = createNode();
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != ',') {
        appendChar(node, ch);
    }
    if (ch != EOF) {
        ungetc(ch, file);
    }
    node->str[node->len] = '\0';
    return node;
}

/**
 * 将文件中的数据加载到行中
 * @param file
 * @return
 */
Row *loadRow(FILE *file) {
    Row *row = createRow();
    int ch = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        if (ch != ',') {
            ungetc(ch, file);
        }
        Node *node = loadNode(file);
        appendRow(row, node);
    }
    if (ch != EOF) {
        ungetc(ch, file);
    }
    return row;
}

/**
 * 向 Grid 中追加数据
 * @param grid
 * @param filename
 * @return
 */
Grid *loadGrid_append(Grid *grid, char *filename) {
    FILE *file = openFile_read(filename);
    if (file == NULL) {
        printf("文件读取异常，无法加载数据\n");
        return grid; // 如果文件打开失败，返回原网格
    }
    int ch = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n') {
            ungetc(ch, file);
        }
        Row *row = loadRow(file);
        appendGrid(grid, row);
    }
    return grid;
}

/**
 * 将文件中的数据加载到 Grid 中
 * @param filename
 * @return
 */
Grid *loadGrid(char *filename) {
    Grid *grid = createGrid();
    return loadGrid_append(grid, filename);
}
