#define OK 1
#define ERROR -1
#define TRUE 2
#define FALSE -2
#define OVERFLOW 0

#define ROW 40 // ����Ϊ6������ROW < COLUMUN - 20
#define COLUMN 80 // ����Ϊ21

typedef int Status;
typedef char RainType;
typedef char WaterType;
typedef char* Thunder;
enum Color
{
	RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PURPLE
};

typedef struct RainNode{
	RainType rainType = '|'; // �����״
	int x = 0; // x������
	int y = 0; // y������
	int offsetY = 0; // y��ƫ��������������紵�����
	int waterRingNum = 0; // ������ˮȦ����Ŀ
	Color color = RED; // ö�����ͣ�ָ����ɫ
	int tag = 0; // Ϊ0�������꣬Ϊ1�������ڣ�Ϊ2����б���������
} *EveryRain;

typedef struct waterNode {
	WaterType w; // ˮ������״
	int move_times = 0; // ˮ���ƶ���ƫ����
	int tag = 0; // Ϊ0����Ϊ������ˮ��Ϊ�����������Ϊˮ��
} *Water;

typedef struct SqQueue {
	EveryRain elem;  // �洢�ռ�Ļ�ַ
	int front;        // ��ͷλ��
	int rear;         // ��βλ�ָ꣬ʾ��βԪ�ص���һλ��
	int maxSize;      // ��󳤶�
} RainSqQueue;

typedef struct ScreenNode{
	RainSqQueue rain; // ��Ŵ��ڵ�ȫ����ε�ѭ������
	RainType (*screenIndex)[COLUMN]; // ��Ӧ��Ļ�ϵ����꣬������ʾ���ݣ�����ָ��
	Water water; // ��Ļ�·���ˮ
} Screen; // ��Ļ

void InitScreen(Screen &S); // ��ʼ����Ļ״̬
Status	CreateRain(Screen& S, RainType type, int en_times, int offsetY); // ������Σ����ѡȡrain�����Ԫ�ز������
Status dropRain(Screen &S, int wind_flag); // ��������
void flush(Screen S); // ˢ��һ�Σ����µ�����Ԥ�浽��ʾ�����У�������Σ����ף��磬ˮ��
void PrintScreen(Screen S, RainNode* fallIntoWater, int last_index_rain); // ˢ��һ����Ļ
int TouchWater(Screen& S, RainNode *fallIntoWater); // ��ˮʱ�ᷢ����һϵ�з�Ӧ
void CreateWaterRing(Screen &S, RainNode e); // ����ˮ��
void CheckWaterRing(Water water, int op); // ��ÿ�δ�ӡˮ֮ǰ�����ˮ��
void CreateThunder(Screen& S); // �����׵�
Status EnQueue_Sq(RainSqQueue& Q, RainNode e); // ���
Status DeQueue_Sq(RainSqQueue& Q); // ����
Status QueueEmpty_Sq(RainSqQueue Q); // �������п�
void freeScreen(Screen& S); // �����ٵĿռ�free��
int getRand(int min, int max); //���������������ұ�����