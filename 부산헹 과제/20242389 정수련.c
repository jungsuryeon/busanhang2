#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//2-2 �λ���(1)���� ����
#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define STM_MIN 0 //������ ü��
#define STM_MAX 5 //������ ü��
#define PROB_MIN 10 // Ȯ��
#define PROB_MAX 90
#define AGGRO_min 0 //��׷� ����
#define AGGRO_max 5

//������ �̵� ����
#define MOVE_LEFT 1
#define MOVE_STAY 0

//������ ���� ���
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

//������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// �Լ�����
//�⺻ �Է�
void line(int, int, int, int, int);// ���� ���
int train_lenfth();//���� ����
int madongseok_stamina();//������ ü��
int percentile_probability(); // Ȯ���Է�
int madongseok_move(int, int);//������ �����̱� �Է�
int action_ma(int, int);// ������ �ൿ ��Ģ �Է�
//�̵��κ�
//������
int Madongseok(int, int);//�������� �������� �����̸�
int madongseok(int, int, int, int); //�������� �������� ������
int Ma_percent1(int);//������ �ٵ�� Ȯ��
//�ù�
int citizen_percent1(int, int); //�ù� �����̱�
int citizen_percent_aggro(int, int, int);//�ù� ��׷�
//����
int zombie_percent1(int, int, int, int, int, int, int, int);// ���� �����̱�
//����â
void ma_write(int, int, int, int, int);// ������ �̵� ����â
void ma_aggro_write(int, int, int, int, int);//������ ��׷� , ü�� ����â
void citizen_write(int, int, int, int);//�ù� �̵� ����â
void zombie_write(int, int, int, int);//���� ����â
//�ִ�,�ּҰ�
int over(int);//������ ü��
int over2(int);// ������ ��׷�
int over3(int);//�ù� ��׷�

// 3-2 �߰�
int villain_percent1(int, int, int);//3-2 ���� �����̱�
int villain_percent_aggro(int, int, int);//3-2 ���� ��׷�
int zombie_percent2(int, int, int, int, int, int, int, int, int, int);//3-2 ���� �̵�
int villain_citizen_chang(int, int);// 3 - 2 ����->�ù�
int citizen_villain_chang(int, int, int);// 3 - 2 �ù�->����
void villain_write(int, int, int);//3-2 ���� ����â
int over4(int);// 3-2 ���� ��׷�


void line(int len, int citizen, int zombie, int Ma, int villain) {
	int turn = 0;
	while (turn <= 2) {
		turn++;
		if (turn == 2) {
			for (int i = 0; i < len; i++) { // 2��°��
				if (i == 0 || i == len - 1)
					printf("#");
				else if (i == citizen) //�ù� ���
					printf("C");
				else if (i == villain)//3-2 ���� ���
					printf("V");
				else if (i == zombie) //���� ���
					printf("Z");
				else if (i == Ma) // ������ ���
					printf("M");
				else printf(" "); // ��ĭ ���
			}
			printf("\n");
		}
		else {
			for (int i = 0; i < len; i++)
				printf("#");
			printf("\n");
		}

	}
}

//2-2 �λ���(1)���� ����
//�Էºκ�
int train_lenfth() { //�������� �Է�
	int len;
	while (1)
	{
		printf("train lenfth(%d~%d) >>", LEN_MIN, LEN_MAX);
		scanf_s("%d", &len);
		if (len >= LEN_MIN && len <= LEN_MAX)
			break;
	}
	return len;
}
int madongseok_stamina() { // ������ ü�� �Է�
	int stamina;
	while (1)
	{
		printf("madongseok stamina(%d~%d) >>", STM_MIN, STM_MAX);
		scanf_s("%d", &stamina);
		if (stamina >= STM_MIN && stamina <= STM_MAX)
			break;
	}
	return stamina;
}
int percentile_probability() { //Ȯ�� �Է�
	int percent;
	while (1)
	{
		printf("percentile probability  'p'(%d~%d)>>", PROB_MIN, PROB_MAX);
		scanf_s("%d", &percent);
		if (percent >= PROB_MIN && percent <= PROB_MAX)
			break;
	}
	return percent;
}
int madongseok_move(int Ma, int zombie) { //  ������ �����̴� �Է�
	int ma_move;
	while (1)
	{
		if (Ma - 1 != zombie) {
			printf("madongseok move(%d:stay,%d:left)>>", MOVE_STAY, MOVE_LEFT);
			scanf_s("%d", &ma_move);
			if (ma_move == MOVE_STAY || ma_move == MOVE_LEFT) break;
		}
		else {
			printf("madongseok move(%d:stay)>>", MOVE_STAY);
			scanf_s("%d", &ma_move);
			if (ma_move == MOVE_STAY) break;
		}
	}
	return ma_move;
}
int action_ma(int Ma, int zombie) { //������ �ൿ ��Ģ �Է�
	int action;
	while (1)
	{
		if (Ma - 1 != zombie) {
			printf("madongseok action(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
			scanf_s("%d", &action);
		}
		else {
			printf("madongseok action(%d.rest, %d.provoke, %d. pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_PULL);
			scanf_s("%d", &action);
		}
		if (action == ACTION_REST || action == ACTION_PROVOKE || action == ACTION_PULL)
			break;
	}
	return action;
}

//�̵��κ�
//������
int Madongseok(int Ma, int ma_move) { // �������� ������ ��
	if (ma_move == MOVE_LEFT)
		Ma--;
	return Ma;
}

int madongseok(int Ma, int ma_move, int zombie, int ma_aggro) { // ������ �̵�����
	if (Ma - 1 != zombie) {
		if (ma_move == MOVE_STAY)
			ma_aggro--;
		else if (ma_move == MOVE_LEFT) {
			ma_aggro++;
		}
	}
	else ma_aggro--;
	return ma_aggro;
}
int Ma_percent1(int percent) { // ������ �ٵ�� Ȯ��
	int success;
	int Ma_percent = rand() % 100;
	if (Ma_percent < (100 - percent)) {
		success = 1;
		printf("madongseok pulled zombie...Next turn, it cant't move\n");
	}
	else {
		success = 0;
		printf("madongseok failed to pull zombie\n");
	}
	return success;
}

//�ù�
int citizen_percent1(int citizen, int percent) {// �ù� �����̱�
	int citizen_percent = rand() % 100;
	if (citizen_percent < (100 - percent))
		citizen--;
	return citizen;
}

int citizen_percent_aggro(int citizen_aggro, int citizen, int citizen_chang) { // 2 ,3-2�ù� ��׷�
	if (citizen_chang - 1 == citizen)
		citizen_aggro++;
	else citizen_aggro--;
	return citizen_aggro;
}
//����
int zombie_percent1(int turn, int percent, int success, int zombie, int Ma, int citizen, int citizen_aggro, int ma_aggro) { // ���� �����̱�
	if (turn % 2 != 0) {
		if (success == 0) {
			if (citizen != zombie - 1) {
				if (citizen_aggro >= ma_aggro)
					zombie--;
				else if (Ma != zombie + 1) zombie++;
			}
		}
	}
	return zombie;
}

//3-2 ����
int villain_percent1(int citizen, int citizen_chang, int villain) {//3-2 ����
	if (citizen_chang - 1 == citizen)
		villain--;
	return villain;
}
int villain_percent_aggro(int villain, int villain_aggro, int villain_chang) { // ���� ��׷�
	if (villain_chang - 1 == villain)
		villain_aggro++;
	else villain_aggro--;
	return villain_aggro;
}
int villain_citizen_chang(int citizen, int villain) { //3-2 ���� �ù� �ٲٱ� �߾Ͻõ�
	int percent2 = rand() % 100;
	printf("���� Ȯ�� : %d\n", percent2);
	if (percent2 < 30) {
		if (citizen == villain - 1)
			villain--;
		else if (citizen == villain + 1)
			villain++;
	}
	return villain;
}
int citizen_villain_chang(int citizen, int villain, int villain_chang) { //3-2 ���� �ù� �ٲٱ� �߾Ͻõ�
	if (citizen == villain) {
		if (villain == villain_chang - 1)
			citizen++;
		else citizen--;
	}
	return citizen;
}

// 3-2 ����
int zombie_percent2(int turn, int percent, int success, int zombie, int Ma, int citizen, int citizen_aggro, int ma_aggro, int villain, int villain_aggro) { // 3-2 ���� �����̱�
	if (turn % 2 != 0) {
		if (success == 0) {
			if (citizen != zombie - 1 && villain != zombie - 1) {
				if (citizen_aggro >= ma_aggro || villain_aggro >= ma_aggro)
					zombie--;
				else if (Ma != zombie + 1) zombie++;
			}
		}
	}
	return zombie;
}


// ����â
//������
void ma_write(int ma_chang, int Ma, int ma_aggro, int ma_aggro_chang, int stamina) { // ������ �������� �����̱�
	if (ma_chang == Ma)
		printf("madongseok: stay %d", Ma);//�������� �������� ������
	else printf("madongseok: %d -> %d ", ma_chang, Ma);
	if (ma_aggro == ma_aggro_chang)
		printf("(aggro: % d, stamina: %d)\n\n", ma_aggro, stamina);
	else printf("(aggro:%d->%d, stamina: %d)\n\n", ma_aggro_chang, ma_aggro, stamina);
}
void ma_aggro_write(int ma_aggro_chang, int ma_aggro, int stamina_chang, int stamina, int Ma) { //������ �ൿ���
	if (ma_aggro_chang == ma_aggro)
		printf("madongseok: %d (aggro:%d,", Ma, ma_aggro);
	else printf("madongseok: %d (aggro:%d->%d,", Ma, ma_aggro_chang, ma_aggro);
	if (stamina_chang == stamina)
		printf("stamina: % d)\n\n", stamina);
	else printf("stamina: % d-> % d)\n\n", stamina_chang, stamina);
}
//2,3-2�ù�
void citizen_write(int citizen, int citizen_chang, int citizen_aggro, int citizen_aggro_chang) {
	if (citizen == citizen_chang)
		printf("citizen: stay %d", citizen); // �ù� �������� ������
	else
		printf("citizen: %d -> %d", citizen_chang, citizen); // �ù� �����϶�
	if (citizen_aggro == citizen_aggro_chang)
		printf("(aggro:%d)\n", citizen_aggro); //aggro�� �� ������
	else printf("(aggro:%d->%d)\n", citizen_aggro_chang, citizen_aggro); //aggro�� �� �ٸ���
}

//����
void villain_write(int villain, int villain_chang, int villain_aggro) {   //3-2 ���� ����â
	if (villain == villain_chang)
		printf("villain: %d(aggro:%d)\n", villain, villain_aggro); // 3-2 ���� �������� ������
	else printf("villain: %d -> %d(aggro:%d)\n", villain_chang, villain, villain_aggro); // ���� �����϶�
}
//����
void zombie_write(int turn, int zombie, int zombie_chang, int success) { //���� ����â
	if (turn % 2 == 1) {
		if (zombie == zombie_chang) {
			if (success == 1)
				printf("zombie: stay %d(pull cannot move)\n\n", zombie); // ���� Ȯ���� �������� ������
			else printf("zombie: stay %d\n\n", zombie);
		}
		else  printf("zombie: %d -> %d\n\n", zombie_chang, zombie); // ���� �����϶�
	}
	else printf("zombie: stay %d(cannot move)\n\n", zombie);
}


//�ִ�, �ּҰ�
int over(int stamina) { // ������ ü��
	if (STM_MIN >= stamina)
		stamina = STM_MIN;
	else if (STM_MAX <= stamina)
		stamina = STM_MAX;
	return stamina;
}
int over2(int ma_aggro) { // ������ ��׷�
	if (AGGRO_min >= ma_aggro)
		ma_aggro = AGGRO_min;
	else if (AGGRO_max <= ma_aggro)
		ma_aggro = AGGRO_max;
	return ma_aggro;
}
int over3(int citizen_aggro) { // �ùξ�׷�
	if (AGGRO_min >= citizen_aggro)
		citizen_aggro = AGGRO_min;
	else if (AGGRO_max <= citizen_aggro)
		citizen_aggro = AGGRO_max;
	return citizen_aggro;
}
int over4(int villain_aggro) { // ���� ��׷�
	if (AGGRO_min >= villain_aggro)
		villain_aggro = AGGRO_min;
	else if (AGGRO_max <= villain_aggro)
		villain_aggro = AGGRO_max;
	return villain_aggro;
}

int main(void) {
	srand((unsigned int)time(NULL));
	//�ʱ�ȭ, �ʱ����
	int len = train_lenfth(); //��������
	int stamina = madongseok_stamina(); // ������ ü��
	int percent = percentile_probability(); //Ȯ��
	int citizen, zombie, Ma, villain;
	int citizen_chang, zombie_chang, ma_chang;
	int citizen_aggro_chang, ma_aggro_chang, stamina_chang;
	int citizen_aggro, ma_aggro;
	int success, dead, turn;
	//�ʱⰪ
	citizen = len - 6;
	zombie = len - 3;
	Ma = len - 2;
	villain = 0;
	citizen_aggro = AGGRO_min;
	ma_aggro = AGGRO_min;
	dead = 0;
	turn = 0;
	success = 0;
	line(len, citizen, zombie, Ma, villain); // �������
	printf("\n");
	while (1)
	{
		while (1) {
			// �� �� �Է�
			citizen_chang = citizen;
			citizen_aggro_chang = citizen_aggro;
			zombie_chang = zombie;
			ma_chang = Ma;
			ma_aggro_chang = ma_aggro;
			stamina_chang = stamina;
			turn++;
			//�̵�����
			citizen = citizen_percent1(citizen, percent); //�ù��̵�
			citizen_aggro = citizen_percent_aggro(citizen_aggro, citizen, citizen_chang); // �ù� ��׷�
			citizen_aggro = over3(citizen_aggro);
			zombie = zombie_percent1(turn, percent, success, zombie, Ma, citizen, citizen_aggro, ma_aggro);//�����̵�
			line(len, citizen, zombie, Ma, villain); //�������
			citizen_write(citizen, citizen_chang, citizen_aggro, citizen_aggro_chang); //�ù� �۾�
			zombie_write(turn, zombie, zombie_chang, success);//���� �۾�
			int ma_move = madongseok_move(Ma, zombie); // ������ �̵�(�Է�)
			printf("\n");
			ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // ������ ��׷�
			ma_aggro = over2(ma_aggro);
			Ma = Madongseok(Ma, ma_move); // ������ �̵�
			line(len, citizen, zombie, Ma, villain); // �������
			ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // ������ �����̴� �۾�
			stamina_chang = stamina;
			ma_aggro_chang = ma_aggro;
			if (citizen == 1) { // �� ���ʿ� ���� �� ��� �ù� �̱�
				printf("YOU WIN!\n");
				printf("Next stage(4/1)\n");
				printf("***************************\n");
				printf("***************************\n\n\n");
				break;
			}
			success = 0;
			printf("citizen does nothing. \n");
			//���� ���� ������
			if (citizen - 1 == zombie && Ma - 1 == zombie) { // �ù� ��׷� vs ������ ��׷ΰ� ������
				if (citizen_aggro <= ma_aggro) {
					stamina--;
					stamina = over(stamina);
					if (stamina == STM_MIN) // �������� ü���� min�̸� ��
					{
						printf("\n GAME OVER madongseok dead... \n");
						dead = 1;
						break;
					}
					printf("Zomibe attacked madongseok(aggeo: %d vs. %d, madongseok stamina: %d -> %d)\n", citizen_aggro, ma_aggro, stamina_chang, stamina);
					stamina_chang = stamina;
				}
				else { printf("\n GAME OVER! citizen dead ...\n"); dead = 1; break; }
			}
			else if (Ma - 1 == zombie) { // �������� �پ� ������
				stamina--;
				stamina = over(stamina);
				if (stamina == STM_MIN) {
					printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
				}
				printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
				stamina_chang = stamina;
			}
			else if (citizen + 1 == zombie) { // �ùΰ� �پ� ������
				printf("\nGAME OVER! citizen dead ...\n"); dead = 1; break;
			}
			else printf("zombie attacked nobody.\n"); // �ƹ��� �Ⱥپ� ������
			//������ �ൿ ��Ģ
			int action = action_ma(Ma, zombie);
			if (action == ACTION_REST) { //�޽�
				ma_aggro--;
				stamina++;
				stamina = over(stamina);
				ma_aggro = over2(ma_aggro);
				printf("madongsrok rests...\n");
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			else if (action == ACTION_PROVOKE) { //����
				ma_aggro = AGGRO_max;
				printf("madongsrok provoked zombie...\n");
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			else if (action == ACTION_PULL) { //�ٵ��
				ma_aggro = ma_aggro + 2;
				stamina--;
				stamina = over(stamina);
				ma_aggro = over2(ma_aggro);
				success = Ma_percent1(percent);
				printf("%d", success);
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			printf("===========================\n\n");
		}
		if (dead == 1)
			break;
		//3-2 �������� 2 : ����
		printf("�������� 2 : ����\n\n");
		citizen = len - 7;
		zombie = len - 3;
		Ma = len - 2;
		citizen_aggro = AGGRO_min;
		ma_aggro = AGGRO_min;
		dead = 0;
		turn = 0;
		success = 0;
		villain = len - 6;
		int villain_aggro = AGGRO_min;
		int villain_chang;
		while (1) {
			citizen_chang = citizen;
			citizen_aggro_chang = citizen_aggro;
			zombie_chang = zombie;
			villain_chang = villain;
			ma_chang = Ma;
			ma_aggro_chang = ma_aggro;
			stamina_chang = stamina;
			turn++;
			citizen = citizen_percent1(citizen, percent); // �ù��̵�
			citizen_aggro = citizen_percent_aggro(citizen_aggro, citizen, citizen_chang); // �ù� ��׷�
			citizen_aggro = over3(citizen_aggro); // �ù� ��׷� ����
			villain = villain_percent1(citizen, citizen_chang, villain); // ���� �̵�
			villain_aggro = villain_percent_aggro(villain, villain_aggro, villain_chang); // ���� ��׷�
			villain_aggro = over4(villain_aggro); // ���� ��׷� ����
			zombie = zombie_percent2(turn, percent, success, zombie, Ma, citizen, citizen_aggro, ma_aggro, villain, villain_aggro);//�����̵�
			line(len, citizen, zombie, Ma, villain);
			citizen_write(citizen, citizen_chang, citizen_aggro, citizen_aggro_chang); //�ù� �۾�
			zombie_write(turn, zombie, zombie_chang, success);//���� �۾�
			villain_write(villain, villain_chang, villain_aggro);
			citizen_chang = citizen;
			villain_chang = villain;
			success = 0;
			int ma_move = madongseok_move(Ma, zombie); // ������ �̵�(�Է�)
			printf("\n");
			ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // ������ ��׷�
			ma_aggro = over2(ma_aggro);
			Ma = Madongseok(Ma, ma_move); // ������ �̵�
			villain = villain_citizen_chang(citizen, villain);
			citizen = citizen_villain_chang(citizen, villain, villain_chang);//�߾Ͻõ�
			line(len, citizen, zombie, Ma, villain);
			ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // ������ �����̴� �۾�
			stamina_chang = stamina;
			ma_aggro_chang = ma_aggro;
			if (citizen == 1) { // �� ���ʿ� ���� �� ��� �ù� �̱�
				printf("YOU WIN!\n");
				printf("Next stage(4/2)\n");
				printf("***************************\n");
				printf("***************************\n\n\n");
				break;
			}
			printf("citizen does nothing. \n");
			//���� ���� ������
			if (citizen - 1 == zombie && Ma - 1 == zombie) { // �ù� ��׷� vs ������ ��׷ΰ� ������
				if (citizen_aggro <= ma_aggro) {
					stamina--;
					stamina = over(stamina);
					if (stamina == STM_MIN) // �������� ü���� min�̸� ��
					{
						printf("\n GAME OVER madongseok dead... \n");
						dead = 1;
						break;
					}
					printf("Zomibe attacked madongseok(aggeo: %d vs. %d, madongseok stamina: %d -> %d)\n", citizen_aggro, ma_aggro, stamina_chang, stamina);
					stamina_chang = stamina;
				}
				else { printf("\n GAME OVER! citizen dead ...\n"); dead = 1; break; }
			}
			else if (Ma - 1 == zombie) { // �������� �پ� ������
				stamina--;
				stamina = over(stamina);
				if (stamina == STM_MIN) {
					printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
				}
				printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
				stamina_chang = stamina;
			}
			else if (citizen + 1 == zombie) { // �ùΰ� �پ� ������
				printf("\nGAME OVER! citizen dead ...\n"); dead = 1; break;
			}
			else printf("zombie attacked nobody.\n"); // �ƹ��� �Ⱥپ� ������
			//������ �ൿ ��Ģ
			int action = action_ma(Ma, zombie);
			if (action == ACTION_REST) { //�޽�
				ma_aggro--;
				stamina++;
				stamina = over(stamina);
				ma_aggro = over2(ma_aggro);
				printf("madongsrok rests...\n");
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			else if (action == ACTION_PROVOKE) { //����
				ma_aggro = AGGRO_max;
				printf("madongsrok provoked zombie...\n");
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			else if (action == ACTION_PULL) { //�ٵ��
				ma_aggro = ma_aggro + 2;
				stamina--;
				stamina = over(stamina);
				ma_aggro = over2(ma_aggro);
				success = Ma_percent1(percent);
				printf("%d", success);
				ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
			}
			printf("===========================\n\n");
		}
		if (dead == 1)
			break;
	}
	return 0;
}