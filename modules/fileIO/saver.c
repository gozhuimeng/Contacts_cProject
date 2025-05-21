//
// Created by meng on 25-5-21.
// DOC 文件保存器
//

#include <stdio.h>
#include "saver.h"
#include "dataFormat.h"
#include "loader.h"

FILE *openFile_write(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件%s\n", filename);
        return NULL;
    }
    return file;
}

Node *buildString(const Row *row) {
    Node *string = createNode();
    for (int i = 0; i < row->len; i++) {
        loadData(string,row->data[i]->str);
        if (i != row->len - 1) {
            appendChar(string, ',');
        }
    }
    return string;
}

void saveFile(char *filename, const Grid *grid) {
    FILE *file = openFile_write(filename);
    for (int i = 0; i < grid->len; i++) {
        Node *string = buildString(grid->data[i]);
        fprintf(file, "%s\n", string->str);
        freeNode(&string);
    }
}

