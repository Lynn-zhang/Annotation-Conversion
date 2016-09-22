#ifndef __COMMENT_CONVERT_H__  
#define __COMMENT_CONVERT_H__  

#include<stdio.h>  
#include<stdlib.h>  


#define INPUTFILENAME "input.c"  
#define OUTPUTFILENAME "output.c"  

typedef enum CONVERT_START//枚举表示操作选项；  
{
	NULL_START,
	C_START,
	CPP_START,
	END_START
}StateType;

void CommentConvert();
void ConvertWork(FILE *read, FILE *write);//注释转换操作选项函数；  
void DoCState(FILE *read, FILE *write);//C 转换为 cpp函数；  
void DoNullState(FILE *read, FILE *write);//普通语句空转换函数；  
void DoCppState(FILE *read, FILE *write);//cpp 转换 C 函数；  

#endif //__COMMENT_CONVERT_H__  
