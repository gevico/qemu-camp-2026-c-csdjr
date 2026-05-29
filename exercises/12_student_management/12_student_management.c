#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    char name[50];
    int age;
} Student;

int main() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    
    Student *students[3];
    
    for (int i = 0; i < 3; i++) 
    {
        Student *stu = malloc(sizeof(Student));
        if (stu == NULL) {
            printf("内存分配失败\n");
            fclose(file);
            return 1;
        }
        if (fscanf(file, "%19s %49s %d", stu->id, stu->name, &stu->age) != 3) {
            printf("文件格式错误\n");
            free(stu);
            fclose(file);
            return 1;
        }
        students[i] = stu;
    }
    fclose(file);
    
    for (int i = 0; i < 3; i++) 
    {
        printf("学号：%s, 姓名：%s, 年龄：%d\n", 
               students[i]->id, 
               students[i]->name, 
               students[i]->age);
    }
    
    for (int i = 0; i < 3; i++) 
    {
        free(students[i]);
    }
    
    return 0;
}