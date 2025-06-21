//
// Created by meng on 25-5-21.
// DOC 数据结构
//

#ifndef DATAFORMAT_H
#define DATAFORMAT_H

// 定义节点结构体(动态字符串)
typedef struct {
    char *str; // 字符串内容
    int len; // 长度
    int size; // 分配空间大小
} Node;

// 定义行结构体(动态节点数组)
typedef struct {
    Node **data;
    int len;
    int size;
} Row;

// 定义表结构体(动态行数组)
typedef struct {
    Row **data;
    int len;
    int size;
} Grid;

#endif //DATAFORMAT_H
