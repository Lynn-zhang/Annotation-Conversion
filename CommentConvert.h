#ifndef __COMMENT_CONVERT_H__  
#define __COMMENT_CONVERT_H__  

#include<stdio.h>  
#include<stdlib.h>  


#define INPUTFILENAME "input.c"  
#define OUTPUTFILENAME "output.c"  

typedef enum CONVERT_START//ö�ٱ�ʾ����ѡ�  
{
	NULL_START,
	C_START,
	CPP_START,
	END_START
}StateType;

void CommentConvert();
void ConvertWork(FILE *read, FILE *write);//ע��ת������ѡ�����  
void DoCState(FILE *read, FILE *write);//C ת��Ϊ cpp������  
void DoNullState(FILE *read, FILE *write);//��ͨ����ת��������  
void DoCppState(FILE *read, FILE *write);//cpp ת�� C ������  

#endif //__COMMENT_CONVERT_H__  
