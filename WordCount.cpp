#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 统计字符数的函数
void count_characters(FILE *file) {
    int char_count = 0; // 字符计数器
    int c; // 用于读取文件中的每个字符

    // 逐字符读取直到文件结束
    while ((c = fgetc(file)) != EOF) {
        char_count++; // 累加字符计数器
    }

    printf("字符数：%d\n", char_count); // 输出字符总数
}

// 统计单词数的函数
void count_words(FILE *file) {
    int word_count = 0; // 单词计数器
    int c, in_word = 0; // in_word标志当前是否在单词中

    // 逐字符读取直到文件结束
    while ((c = fgetc(file)) != EOF) {
        // 如果遇到空格、换行或逗号，且此前处于单词中，单词计数器累加
        if (isspace(c) || c == ',') {
            if (in_word) {
                word_count++; // 累加单词计数器
                in_word = 0; // 标记离开单词区域
            }
        } else {
            // 不是空格、换行或逗号，标记进入单词区域
            in_word = 1;
        }
    }

    // 文件结尾如果还处于单词状态，则单词计数器累加
    if (in_word) {
        word_count++;
    }

    printf("单词数：%d\n", word_count); // 输出单词总数
}

int main(int argc, char *argv[]) {
    // 检查命令行参数数量是否正确
    if (argc != 3) {
        fprintf(stderr, "用法: %s -c|-w 文件名\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1]; // 获取参数（-c 或 -w）
    char *file_name = argv[2]; // 获取文件名

    // 尝试打开文件
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    // 根据参数决定调用哪个统计函数
    if (strcmp(parameter, "-c") == 0) {
        count_characters(file);
    } else if (strcmp(parameter, "-w") == 0) {
        count_words(file);
    } else {
        fprintf(stderr, "无效参数: %s\n", parameter);
        fclose(file);
        return 1;
    }

    fclose(file); // 关闭文件
    return 0; 
}
