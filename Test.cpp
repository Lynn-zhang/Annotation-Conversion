#define _CRT_SECURE_NO_WARNINGS 1
#include"CommentConvert.h"  


StateType state;

//��״̬ʱ����  ���Ų��ϵĶ����ַ�����״̬ת��
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
			state = C_START;//�����Cע�����ǽ�״̬��ΪC״̬�����ҽ�ע�Ϳ�ͷ��ΪCppע�ͣ�  
		}
		else if (second == '/')
		{
			fputc(first, write);
			fputc(second, write);
			state = CPP_START; //�����Cppע�����ǽ�״̬��ΪCpp״̬��  
		}
		else //��ͨ����ֱ��д�룻  
		{
			fputc(first, write);
			fputc(second, write);
		}
		break;
	case EOF:
		fputc(first, write);
		state = END_START;//ע�ͽ�����״̬������  
		break;
	default://��ʼ��Ϊ��ͨ���ݣ�ֱ��д�룻  
		fputc(first, write);
		break;
	}
}

//Cת��ΪCpp;
void DoCState(FILE *read, FILE *write)  
{
	char first = fgetc(read);
	char second = 0;
	switch (first)
	{
	case '*':
		second = fgetc(read);
		if (second == '/')//���� */��  
		{
			int third = fgetc(read);
			state = NULL_START;
			if (third != '\n')
			{
				fputc('\n', write);
				ungetc(third, read);//ungetc�����Ĺ����ǽ��Ѷ����ݻ��ػ�������  


			}
			if (third == '\n')
			{
				fputc(third, write);
			}
		}
		else
		{
			fputc(first, write);
			ungetc(second, read);//��*֮������ݻ��ػ�������  
		}
		break;
	case '\n'://����ǻ��У��Ǿ�������ע�ͣ��ͽ���һ�п�ͷ����Cppע�ͣ�  
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

//C++ע��
void DoCppState(FILE *read, FILE *write)  
{
	char first = 0;

	first = fgetc(read);

	switch (first)
	{
	case'\n'://Cppע�͵Ļ��о���һ��ע�͵Ľ�����  
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

//����״̬ѡ��ͬ�Ĵ�����
void ConvertWork(FILE *read, FILE *write)
{
	state = NULL_START;//һ��ʼ����ѡ����״̬  
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

//�ļ�����
void CommentConvert()  
{
	FILE *pWrite = NULL;

	//����ǰ�༭�õ�"input.c"�ļ�;  
	FILE *pRead = fopen(INPUTFILENAME, "r");
	if (pRead == NULL)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	//д���´�����"output.c"�ļ�;  

	pWrite = fopen(OUTPUTFILENAME, "w");
	if (pWrite == NULL)
	{
		fclose(pRead);
		perror("open file for write");
		exit(EXIT_FAILURE);
	}

	//���ò���ѡ���;  
	//�ر��Ѿ��򿪵��ļ�;  

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