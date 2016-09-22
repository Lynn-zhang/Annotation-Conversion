#define _CRT_SECURE_NO_WARNINGS 1
#include"CommentConvert.h"  


StateType state;

//无状态时调用  随着不断的读入字符进行状态转换
void DoNullState(FILE *read, FILE *write)
{
	char first = fgetc(read);
	char second;

	switch (first)
	{
	case'/':
		second = fgetc(read);
		if (second == '*')
		{
			fputc(first, write);
			fputc('/', write);
			state = C_START;//如果是C注释我们将状态改为C状态，并且将注释开头改为Cpp注释；  
		}
		else if (second == '/')
		{
			fputc(first, write);
			fputc(second, write);
			state = CPP_START; //如果是Cpp注释我们将状态改为Cpp状态；  
		}
		else //普通语句就直接写入；  
		{
			fputc(first, write);
			fputc(second, write);
		}
		break;
	case EOF:
		fputc(first, write);
		state = END_START;//注释结束，状态调整；  
		break;
	default://开始就为普通内容，直接写入；  
		fputc(first, write);
		break;
	}
}

//C转换为Cpp;
void DoCState(FILE *read, FILE *write)  
{
	char first = fgetc(read);
	char second = 0;
	switch (first)
	{
	case '*':
		second = fgetc(read);
		if (second == '/')//舍弃 */；  
		{
			int third = fgetc(read);
			state = NULL_START;
			if (third != '\n')
			{
				fputc('\n', write);
				ungetc(third, read);//ungetc函数的功能是将已读数据还回缓冲区；  


			}
			if (third == '\n')
			{
				fputc(third, write);
			}
		}
		else
		{
			fputc(first, write);
			ungetc(second, read);//将*之后的内容还回缓冲区；  
		}
		break;
	case '\n'://如果是换行，那就是连续注释，就将下一行开头加入Cpp注释；  
		fputc(first, write);
		fputc('/', write);
		fputc('/', write);
		break;
	case EOF:
		fputc(first, write);
		state = END_START;
		break;
	default:
		fputc(first, write);
		break;
	}
}

//C++注释
void DoCppState(FILE *read, FILE *write)  
{
	char first = 0;

	first = fgetc(read);

	switch (first)
	{
	case'\n'://Cpp注释的换行就是一行注释的结束；  
		fputc(first, write);
		state = NULL_START;
		break;
	case EOF:
		fputc(first, write);
		state = END_START;
		break;
	default:
		fputc(first, write);
		break;
	}
}

//根据状态选择不同的处理函数
void ConvertWork(FILE *read, FILE *write)
{
	state = NULL_START;//一开始我们选择无状态  
	while (state != END_START)
	{
		switch (state)
		{
		case NULL_START:
			DoNullState(read, write);
			break;
		case C_START:
			DoCState(read, write);
			break;
		case CPP_START:
			DoCppState(read, write);
			break;
		default:
			break;
		}
	}
}

//文件操作
void CommentConvert()  
{
	FILE *pWrite = NULL;

	//打开提前编辑好的"input.c"文件;  
	FILE *pRead = fopen(INPUTFILENAME, "r");
	if (pRead == NULL)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	//写入新创建的"output.c"文件;  

	pWrite = fopen(OUTPUTFILENAME, "w");
	if (pWrite == NULL)
	{
		fclose(pRead);
		perror("open file for write");
		exit(EXIT_FAILURE);
	}

	//调用操作选项函数;  
	//关闭已经打开的文件;  

	ConvertWork(pRead, pWrite);
	fclose(pRead);
	fclose(pWrite);
}



void test()
{
	CommentConvert();
}

int main()
{
	test();

	system("pause");
	return 0;
}