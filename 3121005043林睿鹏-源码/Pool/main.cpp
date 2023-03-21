#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Rain.h"

int main() {
	while (true)
	{
		Screen S;
		InitScreen(S);
		char user_en; // ��������û�����Ļس�
		RainNode fallIntoWater[COLUMN]; // �����洢����ˮ����ε���Ϣ
		int last_index = 0; // ����ˮ�е���ε����һ��Ԫ�ص��±�
		int en_times = 0; // ��Ӧ�û������룬ʵ���������ı䣬����ܶȸı�
		int den = 0; // �ı�����ܶ�
		int code = 0;
		int c = 0; // ������뻺��
		RainType type = 0;
		int offsetY = 0;
		int wind_flag = 0; // Ϊ0ʱ�����޷磬Ϊ1ʱ�����з�
		int aa = 0;
		do {
			code = 0;
			wind_flag = 0;
			system("cls");
			printf("=====�����ͽ��������ġ�����ҹ�ꡱ=====\n");
			printf("|----- 1: ���Ǳ��ҹ,����ϸ���� -----|\n");
			printf("|----- 2: ����ǧ����,��ɫ����� -----|\n");
			printf("|----- 3: �뿪 ----------------------|\n");
			printf("======================================");
			printf("\n�������Ӧָ�");
			scanf("%d", &code);
			while ((c = getchar()) != '\n' && c != EOF); // ������뻺��
		}while (code < 1 || code > 3);

		switch (code)//ע�����涼�Ǻ�����������ʽ �������붼Ҫ�����Լ����� 
		{
			case 1:
				type = '|';
				offsetY = 0;
				wind_flag = 0;
				break;
			case 2:
				type = '/';
				offsetY = COLUMN / 2 - 1;
				wind_flag = 1;
				break;
			case 3:
				return 1;
		}
		system("cls");
		do {
			en_times++;
			if (en_times <= getRand(ROW * 2, ROW * 3)) {
				en_times <= getRand(ROW, ROW * 2 - 1) ? den = COLUMN / 5 : den = COLUMN / 20;
			} else {
				en_times = 0;
			}
			CreateRain(S, type, den, offsetY);
			flush(S); // ��flush�ʹ��׷ֿ�������ͬʱ���ҲҪ������
			if (wind_flag == 1) CreateThunder(S);
			PrintScreen(S, fallIntoWater, last_index);
			last_index = 0;
			printf("\n����ENTER������0+ENTER�뿪(Ϊ�ﵽ���Ч������Ŵ󴰿ڣ�������ѹENTER��)");
			user_en = getchar();
			dropRain(S, wind_flag);
			last_index = TouchWater(S, fallIntoWater);
			system("cls");
		} while (10 == user_en);
		freeScreen(S);
	}
	return 0;
}