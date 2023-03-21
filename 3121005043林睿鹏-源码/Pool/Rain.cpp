#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Rain.h"


void InitScreen(Screen& S) {
    S.rain.elem = (EveryRain)malloc(sizeof(RainNode) * ROW * COLUMN + 1); // �������⼸����ʼ��
    S.rain.front = 0;
    S.rain.rear = 0;
    S.rain.maxSize = ROW * COLUMN + 1;
    S.screenIndex = (RainType(*)[COLUMN])malloc(sizeof(RainType) * ROW * COLUMN); // 1ά����*COLUMN
    S.water = (Water)malloc(sizeof(waterNode) * COLUMN);
    if (S.rain.elem == NULL || S.screenIndex == NULL || S.water == NULL) return;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            S.screenIndex[i][j] = 32;
        }
    }
  
    for (int i = 0; i < COLUMN; i++) {
        S.water[i].w = '~';
        S.water[i].move_times = 0;
        S.water[i].tag = 0;
    }
}

void freeScreen(Screen& S) {
    // free(S.rain.elem);S.rain.elem = NULL��// ̫���ˣ��˴�����free
    // ��Ϊ�ṹ���ڴ����S��ַ=S.rain�ĵ�ַ=S.rain.elem�ĵ�ַ������free�ͻ������S��free��
    // ���Ͼ�����д���ˣ�����S�ֲ��������뿪ѭ����û�ˣ����ⲻ���´�С�İ�
    free(S.screenIndex); // ָ�������ָ�룬ֱ���ͷż���
    free(S.water);
    S.screenIndex = NULL;
    S.water = NULL;
}

// ������Σ����ѡȡrain�����Ԫ�ز������
Status	CreateRain(Screen& S, RainType type, int en_times, int offsetY) {
    // ���ѡȡ�±꣬�������������Ŀ�����������ɫ
    if (NULL == S.rain.elem)return ERROR;
    // ���ѡȡ����
    for (int j = 0; j < COLUMN; j++) {
        int n = getRand(1, 80) % en_times;
        if (0 == n) { // ��ѡ��
            RainNode e;
            e.rainType = type; // ��ͬ�������β�ͬ
            e.x = 0;
            e.y = j; // ��Ӧ��һ��
            e.offsetY = offsetY; // ��Ӧ��һ��
            e.waterRingNum = getRand(1, 3);
            e.color = (Color)getRand(0, 6); // �˴�ǿ������ת��
            e.tag = 1;
            EnQueue_Sq(S.rain, e); // ���
        }
    }
    return OK;
}

/*
    ���������
*/
Status dropRain(Screen& S, int wind_flag) {
    if (NULL == S.rain.elem)return ERROR;
    RainSqQueue Q = S.rain;
    // �������У�Ȼ�������ǵ�y��������
    for (int j = Q.front; j != Q.rear; j = (j + 1) % Q.maxSize) {
        Q.elem[j].x++;
        // �˴���wind_flag��������Ϊ�˺��ڲ�����������ʱ������
        if (wind_flag == 1) {
            // ƫ��������0����y���ڵ���0���ż�1��Ҳ����˵��y��СΪ-1
            if (Q.elem[j].offsetY > 0 && Q.elem[j].y >= 0) {
                Q.elem[j].y--;
                Q.elem[j].offsetY--;
            }
            // �˴���һ�����ѷ��ֵ�bug���Ǿ���ִ���������if֮��y��Ϊ-1��ͬʱ�Ӵ�ˮ�棬����tagδ�޸ģ����²�����water[-1]
            if (Q.elem[j].y < 0) {
                Q.elem[j].tag = 2;
            }
        }
    }
    return OK;
}

/*
    ˢ��һ�Σ����µ�����Ԥ�浽��ʾ�����У�������Σ����ף��磬ˮ��
*/
void flush(Screen S) {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            S.screenIndex[i][j] = 32;
        }
    }
    RainSqQueue Q = S.rain;
    for (int j = Q.front; j != Q.rear; j=(j+1)%Q.maxSize) {
         int x = Q.elem[j].x;
         int y = Q.elem[j].y;
         // ����yΪ-1�����
         y < 0 ? S.screenIndex[x][0] = 32 : S.screenIndex[x][y] = Q.elem[j].rainType;
    }

}


/*
    ��ӡ����Ļ��ǰ��������
*/
void PrintScreen(Screen S, RainNode* fallIntoWater, int last_index_rain) {
    // ��ӡ��Ļ����
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            printf("%c", S.screenIndex[i][j]);
        }
        printf("\n");
    }
 
    // ��ӡˮ
    CheckWaterRing(S.water, 1);
    for (int i = 0; i < COLUMN; i++) {
        printf("%c", S.water[i].w);
    }
    printf("\n");
    CheckWaterRing(S.water, -1); // ��ԭˮ��

    // ��ӡ�����Ϣ
    if (fallIntoWater == NULL) return;
    printf("�������ң�����Ϊ����ˮ�����ε���Ϣ:\n");
    for (int i = 0; i < last_index_rain; i++) {
        printf("��%d�������ɫΪ: ", i + 1);
        switch (fallIntoWater[i].color)
        {
        case RED:
            printf("RED\n");
            break;
        case ORANGE:
            printf("ORANGE\n");
            break;
        case YELLOW:
            printf("YELLOW\n");
            break;
        case GREEN:
            printf("GREEN\n");
            break;
        case CYAN:
            printf("CYAN\n");
            break;
        case BLUE:
            printf("BLUE\n");
            break;
        case PURPLE:
            printf("PURPLE\n");
            break;
        default:
            break;
        }
    }
}

/*
    ������ˮʱ����Ĩȥ���ڣ����Ҳ���ˮ��
*/
int TouchWater(Screen &S, RainNode* fallIntoWater) {
    // �������һ��λ�õ���Σ���drop�����󣬲���ˮ������Ĩ�������������ѭ������Ĵ���
    // Ĩȥ���ڣ�ֱ�ӳ�ȥѭ����������ľͺ��ˣ���Ϊ�ҵ�flush������ˢ��һ����ʾ����
    // �Ӷ�ͷ�������COLUMN��(һ�����COLUMN��)����x�������һ�еģ��Ͱ�tag��Ϊ0�����ҳ�ջ
    int the_last_rain = 0;
    int pre_front = 0; // ��¼��1ǰ��frontֵ
    for (int i = 0; i < COLUMN; i++) {
        if (S.rain.elem[S.rain.front].x == ROW) {
            RainNode e = S.rain.elem[S.rain.front];
            pre_front = S.rain.front;
            DeQueue_Sq(S.rain); // ɾ����Щ��ˮ�ģ��˴��ĳ�ջ��Ҫ��S�����ܶԾֲ�����
            // ��tagΪ1ʱ�Ų���ˮ�������Ϊ2�������磬������ˮ��
            if (e.tag == 1) {
                CreateWaterRing(S, e);// �ĳ�ˮ�����˴�����ȥ�Ĳ���ҲҪ��S�������Ǿֲ�����
            }
            S.rain.elem[pre_front].tag = 0;
            fallIntoWater[the_last_rain++] = e;// �����ˮ��ε���ɫ
        }
    }
    return the_last_rain; // ������������һ���±�
}

// ����ˮ��
void CreateWaterRing(Screen &S, RainNode e) {
    // ���ǵ��߽�����
    int y = e.y; // e����ʱ��y����
    if (y < 0) return; // �¸�if���������
    S.water[y].move_times = S.water[y].tag = e.waterRingNum;
}

/*
    ��ÿ�δ�ӡˮ֮ǰ�����ˮ��
    @param op Ϊ1ʱ�������沨��Ϊ-1ʱ����ԭˮ��
*/
void CheckWaterRing(Water water, int op) {
    // ע��߽�����
    for (int i = 0; i < COLUMN; i++) {
        if (op == 1) {
            if (water[i].tag != 0) {
                int offsetLeft = i - (water[i].move_times - water[i].tag + 1);
                int offsetRight = i + (water[i].move_times - water[i].tag + 1);
                if (offsetLeft >= 0) {
                    water[offsetLeft].w = '(';
                }
                if (offsetRight <= COLUMN - 1) {
                    water[offsetRight].w = ')';
                }
                water[i].tag--; // ��һ�Σ��´ξͻ�ƫ�Ƹ�Զ
            }
        } else if(op == -1) {
            if (water[i].tag == 0) {
                water[i].w = '~';
                water[i].move_times = 0;
            }
        }
    }
}

// ��������
void CreateThunder(Screen& S) {
    // �趨�׵�ĵ�λ����
    int len = ROW / 8;
    // �ӱ߽�������������ѡȡ������׵�
    for (int i = len + 1; i < COLUMN; i = i + len + 2) {
        int num = getRand(1, 10);// 1 / 5�ĸ���
        if (num % 5 == 0) {
            // �����׵�
            int indexX1 = 0; // x����
            int indexY1 = i;
            int indexX2 = 0;
            int indexY2 = 0;
            int indexX3 = 0;
            int indexY3 = 0;
            for (int offset = 0; offset < len; offset++) {
                S.screenIndex[indexX1++][indexY1 - offset] = '/';
                indexX2 = indexX1 - 1;
                indexY2 = indexY1 - offset;
            }
            for (int offset = 0; offset < len; offset++) {
                S.screenIndex[indexX2][indexY2 + offset + 1] = '_';
                indexX3 = indexX2;
                indexY3 = indexY2 + offset + 1;
            }
            for (int offset = 0; offset < len; offset++) {
                S.screenIndex[++indexX3][indexY3 - offset] = '/';
            }
        }
    }
}

Status EnQueue_Sq(RainSqQueue& Q, RainNode e) {
    // ����ǰ���в������ڶ��е�βԪ��֮�󣬲���Ԫ�� e Ϊ�µĶ���βԪ��
    if (Q.front == (Q.rear + 1) % Q.maxSize) return ERROR;
    Q.elem[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.maxSize;
    return OK;
}

Status DeQueue_Sq(RainSqQueue& Q) {
    // �����в��գ���ɾ������Q�е�ͷԪ��
    if (TRUE == QueueEmpty_Sq(Q)) return ERROR; // �ӿձ���
    Q.front = (Q.front + 1) % Q.maxSize; // Q.frontѭ����1
    return OK;
}

Status QueueEmpty_Sq(RainSqQueue Q) { // �ж϶���Q�Ƿ�գ������򷵻�TRUE������FALSE
    return Q.front == Q.rear ? TRUE : FALSE;
}

// ����ұ����䣬���������
int getRand(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}