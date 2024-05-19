#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ͳ���ַ����ĺ���
void count_characters(FILE *file) {
    int char_count = 0; // �ַ�������
    int c; // ���ڶ�ȡ�ļ��е�ÿ���ַ�

    // ���ַ���ȡֱ���ļ�����
    while ((c = fgetc(file)) != EOF) {
        char_count++; // �ۼ��ַ�������
    }

    printf("�ַ�����%d\n", char_count); // ����ַ�����
}

// ͳ�Ƶ������ĺ���
void count_words(FILE *file) {
    int word_count = 0; // ���ʼ�����
    int c, in_word = 0; // in_word��־��ǰ�Ƿ��ڵ�����

    // ���ַ���ȡֱ���ļ�����
    while ((c = fgetc(file)) != EOF) {
        // ��������ո񡢻��л򶺺ţ��Ҵ�ǰ���ڵ����У����ʼ������ۼ�
        if (isspace(c) || c == ',') {
            if (in_word) {
                word_count++; // �ۼӵ��ʼ�����
                in_word = 0; // ����뿪��������
            }
        } else {
            // ���ǿո񡢻��л򶺺ţ���ǽ��뵥������
            in_word = 1;
        }
    }

    // �ļ���β��������ڵ���״̬���򵥴ʼ������ۼ�
    if (in_word) {
        word_count++;
    }

    printf("��������%d\n", word_count); // �����������
}

int main(int argc, char *argv[]) {
    // ��������в��������Ƿ���ȷ
    if (argc != 3) {
        fprintf(stderr, "�÷�: %s -c|-w �ļ���\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1]; // ��ȡ������-c �� -w��
    char *file_name = argv[2]; // ��ȡ�ļ���

    // ���Դ��ļ�
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        return 1;
    }

    // ���ݲ������������ĸ�ͳ�ƺ���
    if (strcmp(parameter, "-c") == 0) {
        count_characters(file);
    } else if (strcmp(parameter, "-w") == 0) {
        count_words(file);
    } else {
        fprintf(stderr, "��Ч����: %s\n", parameter);
        fclose(file);
        return 1;
    }

    fclose(file); // �ر��ļ�
    return 0; 
}
