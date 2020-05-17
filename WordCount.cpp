#include <stdio.h>
#include <string.h>
int* getCharNum(char* filename, int* totalNum);
int main() {
    char filename[30];
    int totalNum[2] = {0,0}; //totalNum[0]: 总字符数  totalNum[1]: 总单词数
    char op[10];
    scanf_s("%s", op,sizeof(op));
    scanf_s("%s", filename, sizeof(filename));
    getCharNum(filename, totalNum); 
    if (strcmp(op, "-c") == 0) {
            printf("字符数:%d", totalNum[0]);
    }
    else if(strcmp(op, "-w") == 0) {
            printf("单词数:%d", totalNum[1]);
    }
    else {
        printf("Error!\n");
    }
    return 0;
}


int* getCharNum(char* filename, int* totalNum) {
    FILE* fp;  // 指向文件的指针
    char buffer[1000];  //缓冲区，存储读取到的每行的内容
    int bufferLen;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int blank = 0;  // 上个字符是否是空格
    if ((fp = fopen(filename, "rb")) == NULL) {
        perror(filename);
        return NULL;
    }
    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while (fgets(buffer, 1003, fp) != NULL) {
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        for (i = 0; i < bufferLen; i++) {
            c = buffer[i];
            if (c == ' ' || c == '\t') {  // 遇到空格
                !blank && totalNum[1]++;  // 如果上个字符不是空格，那么单词数加1
                blank = 1;
            }
            else if (c != '\n' && c != '\r') {  // 忽略换行符
                totalNum[0]++;  // 如果既不是换行符也不是空格，字符数加1
                blank = 0;
            }
        }
        !blank && totalNum[1]++;  // 如果最后一个字符不是空格，那么单词数加1
        blank = 1;  // 每次换行重置为1
    }
    return totalNum;
}
