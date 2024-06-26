#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

//2-2 부산헹(1)에서 수정
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 //마동석 체력
#define STM_MAX 5 //마동석 체력
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_min 0 //어그로 범위
#define AGGRO_max 5

//마동성 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

//좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

//마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

int citizen_num[100], citizen_num1[100], citizen_num_aggro[100], citizen_num_aggro1[100], zombie_num[100], zombie_num1[100];
int citizen_number, max_number;

// 함수선언
//기본 입력
void line(int, int, int, int, int);// 열차 출력
int train_lenfth();//기차 길이
int madongseok_stamina();//마동석 체력
int percentile_probability(); // 확률입력
int madongseok_move(int, int);//마동석 움직이기 입력
int action_ma(int, int);// 마동석 행동 규칙 입력
//이동부분
//마동석
int Madongseok(int, int);//마동석이 왼쪽으로 움직이면
int madongseok(int, int, int, int); //마동석이 움직이지 않으면
int Ma_percent1(int);//마동석 붙들기 확률
//시민
int citizen_percent1(int, int); //시민 움직이기
int citizen_percent_aggro(int, int, int);//시민 어그로
//좀비
int zombie_percent1(int, int, int, int, int, int, int, int);// 좀비 움직이기
//상태창
void ma_write(int, int, int, int, int);// 마동석 이동 상태창
void ma_aggro_write(int, int, int, int, int);//마동석 어그로 , 체력 상태창
void citizen_write(int, int, int, int);//시민 이동 상태창
void zombie_write(int, int, int, int);//좀비 상태창
//최대,최소값
int over(int);//마동석 체력
int over2(int);// 마동석 어그로
int over3(int);//시민 어그로

// 3-2 추가
int villain_percent1(int, int, int);//3-2 빌런 움직이기
int villain_percent_aggro(int, int, int);//3-2 빌런 어그로
int zombie_percent2(int, int, int, int, int, int, int, int, int, int);//3-2 좀비 이동
int villain_citizen_chang(int, int);// 3 - 2 빌런->시민
int citizen_villain_chang(int, int, int);// 3 - 2 시민->빌런
void villain_write(int, int, int);//3-2 빌런 상태창
int over4(int);// 3-2 빌런 어그로

//3-3 추가
int zombie_percent3(int, int, int, int, int, int, int);//3-3 좀비 이동

//3-3,3-4 추가
void line3(int, int, int, int);//3-3,3-4 열차 출력
int citize_place(int);//3-3,3-4 시민 숫자 및 배치
void citize_array(int);//3-3,3-4 시민 정렬
void citizen_percent3(int, int);//3-3,3-4 시민들 확률로 움직이기
void citizen_percent_chang(int);//3-3,3-4 전 값 시민 저장
void citizen_num_aggro_chang(int);//3-3,3-4 전 값 시민 어그로 저장
void citizen_percent_aggro3(int);//3-3,3-4 시민들 어그로
void citizens_write(int);//3-3 3-4 시민 상태창
void over5(int);// 3-3 3-4 시민들 어그로

//3-4 추가
int zombie_percent4(int, int, int, int, int, int, int, int, int);//3-4 좀비 이동
void zombie_percent_chang(int);//3-4 좀비저장
void zombies_write(int);//3-4 좀비 상태창
void zero_number(void);//3-4 시민들 초기화

void line(int len, int citizen, int zombie, int Ma, int villain) {
    int turn = 0;
    while (turn <= 2) {
        turn++;
        if (turn == 2) {
            for (int i = 0; i < len; i++) { // 2번째줄
                if (i == 0 || i == len - 1)
                    printf("#");
                else if (i == citizen) //시민 출력
                    printf("C");
                else if (i == villain)//3-2 빌런 출력
                    printf("V");
                else if (i == zombie) //좀비 출력
                    printf("Z");
                else if (i == Ma) // 마동석 출력
                    printf("M");
                else printf(" "); // 빈칸 출력
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

void line3(int len, int zombie, int Ma, int citizen_number) {
    int turn = 0;
    while (turn <= 2) {
        turn++;
        if (turn == 2) {
            for (int i = 0; i < len; i++) { // 2번째줄
                if (i == 0 || i == len - 1)
                    printf("#");
                else if (i == zombie) //좀비 출력
                    printf("Z");
                else if (i == Ma) // 마동석 출력
                    printf("M");
                else {
                    int z = 0;
                    for (int j = 0; j < citizen_number; j++)
                    {
                        if (i == citizen_num[j]) {
                            printf("C"); z = 1; break;
                        }
                        else if (i == zombie_num[j]) {
                            printf("Z"); z = 1; break;
                        }
                    }
                    if (z != 1)
                        printf(" ");
                }
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

//2-2 부산헹(1)에서 수정
//입력부분
int train_lenfth() { //기차길이 입력
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
int madongseok_stamina() { // 마동석 체력 입력
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
int percentile_probability() { //확률 입력
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
int madongseok_move(int Ma, int zombie) { //  마동석 움직이는 입력
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
int action_ma(int Ma, int zombie) { //마동석 행동 규칙 입력
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

//이동부분
//마동석
int Madongseok(int Ma, int ma_move) { // 왼쪽으로 움직일 시
    if (ma_move == MOVE_LEFT)
        Ma--;
    return Ma;
}

int madongseok(int Ma, int ma_move, int zombie, int ma_aggro) { // 마동석 이동방향
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
int Ma_percent1(int percent) { // 마동석 붙들기 확률
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

//시민
int citizen_percent1(int citizen, int percent) {// 시민 움직이기
    int citizen_percent = rand() % 100;
    if (citizen_percent < (100 - percent))
        citizen--;
    return citizen;
}

int citizen_percent_aggro(int citizen_aggro, int citizen, int citizen_chang) { // 2 ,3-2시민 어그로
    if (citizen_chang - 1 == citizen)
        citizen_aggro++;
    else citizen_aggro--;
    return citizen_aggro;
}
//좀비
int zombie_percent1(int turn, int percent, int success, int zombie, int Ma, int citizen, int citizen_aggro, int ma_aggro) { // 좀비 움직이기
    if (turn % 2 != 0) {
        if (success == 0) {
            int zombie_percent = rand() % (100 - percent);
            if (zombie_percent < percent) {
                if (citizen != zombie - 1) {
                    if (citizen_aggro >= ma_aggro)
                        zombie--;
                    else if (Ma != zombie + 1) zombie++;
                }
            }
        }
    }
    return zombie;
}

//3-2 빌런
int villain_percent1(int citizen, int citizen_chang, int villain) {//3-2 빌런
    if (citizen_chang - 1 == citizen)
        villain--;
    return villain;
}
int villain_percent_aggro(int villain, int villain_aggro, int villain_chang) { // 빌런 어그로
    if (villain_chang - 1 == villain)
        villain_aggro++;
    else villain_aggro--;
    return villain_aggro;
}
int villain_citizen_chang(int citizen, int villain) { //3-2 빌런 시민 바꾸기 발암시도
    int percent2 = rand() % 100;
    printf("빌런 확률 : %d\n", percent2);
    if (citizen != 1) {
        if (percent2 < 30) {
            if (citizen == villain - 1)
                villain--;
            else if (citizen == villain + 1)
                villain++;
        }
    }
    return villain;
}
int citizen_villain_chang(int citizen, int villain, int villain_chang) { //3-2 빌런 시민 바꾸기 발암시도
    if (citizen == villain) {
        if (villain == villain_chang - 1)
            citizen++;
        else citizen--;
    }
    return citizen;
}

// 3-2 좀비
int zombie_percent2(int turn, int percent, int success, int zombie, int Ma, int citizen, int citizen_aggro, int ma_aggro, int villain, int villain_aggro) { // 3-2 좀비 움직이기
    if (turn % 2 != 0) {
        if (success == 0) {
            int zombie_percent = rand() % (100 - percent);
            if (zombie_percent < percent) {
                if (citizen != zombie - 1 && villain != zombie - 1) {
                    if (citizen_aggro >= ma_aggro || villain_aggro >= ma_aggro)
                        zombie--;
                    else if (Ma != zombie + 1) zombie++;
                }
            }
        }
    }
    return zombie;
}

//3-3, 3-4 시민들
int citize_place(int len) { // 3-3, 3-4 시민 숫자, 배치
    int citizen_number = rand() % ((len / 2) - (len / 4) + 1) + (len / 4);
    printf("citizen_number : %d\n", citizen_number);
    for (int i = 0; i < citizen_number; i++) {
        if (i != citizen_number - 1) {
            citizen_num[i] = rand() % (len - 8) + 2;
            if (i != 0) {
                for (int j = 0; j < i; j++) {
                    while (citizen_num[j] == citizen_num[i]) {
                        citizen_num[i] = rand() % (len - 8) + 2;
                    }
                }
            }
        }
        else citizen_num[citizen_number - 1] = len - 6;
    }
    return citizen_number;
}

void citize_array(int citizen_number) {//3-3,3-4 정렬
    for (int i = 0; i < citizen_number - 1; i++) {
        for (int j = 0; j < citizen_number - 1; j++) {
            if (citizen_num[j] > citizen_num[j + 1]) {
                int tmp = citizen_num[j];
                citizen_num[j] = citizen_num[j + 1];
                citizen_num[j + 1] = tmp;
            }
        }
    }
}

void citizen_percent_chang(int citizen_number) {// 3-3 3-4 시민 저장
    for (int i = 0; i < citizen_number; i++)
        citizen_num1[i] = citizen_num[i];
}
void citizen_num_aggro_chang(int citizen_number) { // 3-3 3-4 시민 어그로 저장
    for (int i = 0; i < citizen_number; i++)
        citizen_num_aggro1[i] = citizen_num_aggro[i];
}
void citizen_percent3(int percent, int citizen_number) {// 3-3 3-4 시민들 움직이기 
    for (int i = 0; i < citizen_number; i++) {
        if (citizen_num[i] != -1 && citizen_num[i] != 0) {
            int citizen_percent = rand() % 100;
            if (citizen_percent < (100 - percent)) {
                citizen_num[i] = citizen_num[i] - 1;
                if (i != 0) {
                    if (citizen_num[i - 1] == citizen_num[i])
                        citizen_num[i] = citizen_num[i] + 1;
                }
            }
        }
    }
}
void citizen_percent_aggro3(int citizen_number) { // 3-3 3-4 시민들 어그로
    for (int i = 0; i < citizen_number; i++) {
        if (citizen_num[i] != citizen_num1[i]) {
            citizen_num_aggro[i] = citizen_num_aggro[i] + 1;
        }
        else citizen_num_aggro[i] = citizen_num_aggro[i] - 1;
    }
}
//3-3, 3-4 좀비
int zombie_percent3(int turn, int success, int zombie, int Ma, int ma_aggro, int max_number, int percent) { // 3-3 좀비 움직이기
    if (turn % 2 != 0) {
        if (success == 0) {
            int zombie_percent = rand() % (100 - percent);
            if (zombie_percent < percent) {
                if (citizen_num[max_number] != zombie - 1) {
                    if (citizen_num_aggro[max_number] >= ma_aggro)
                        zombie--;
                    else if (Ma != zombie + 1) zombie++;
                }
            }
        }
    }
    return zombie;
}
int zombie_percent4(int turn, int success, int zombie, int Ma, int ma_aggro, int max_number, int zombie_number, int zombies_turn, int percent) { //3-4 좀비
    if (turn % 2 != 0) {
        if (success == 0) {
            int zombie_percent = rand() % (100 - percent);
            if (zombie_percent < percent) {
                if (citizen_num[max_number] != zombie - 1) {
                    if (citizen_num_aggro[max_number] >= ma_aggro) {
                        if (zombie_num[0] + 1 != zombie)
                            zombie--;
                    }
                    else if (Ma != zombie + 1) zombie++;
                }
            }
        }
    }
    for (int i = 1; i <= zombie_number; i++) {
        if (zombie_num[i] != 0 && zombies_turn != 1) {// 바뀐 좀비
            if (citizen_num[max_number] + 1 != zombie_num[zombie_number]) {
                int zombie_percent = rand() % (100 - percent);
                if (zombie_percent < percent) {
                    if (citizen_num_aggro[max_number] >= ma_aggro) {
                        zombie_num[i] = zombie_num[i] - 1;
                        if (i != 1) {
                            if (zombie_num[i - 1] == zombie_num[i])
                                zombie_num[i] = zombie_num[i] + 1;
                        }
                    }
                    else if (Ma != zombie_num[i] + 1)
                        zombie_num[i] = zombie_num[i] + 1;
                }
            }
        }
    }
    return zombie;
}

void zombie_percent_chang(int zombie_number) {// 3-4 좀비 저장
    for (int i = 0; i < zombie_number; i++)
        zombie_num1[i] = zombie_num[i];
}


// 상태창
//마동석
void ma_write(int ma_chang, int Ma, int ma_aggro, int ma_aggro_chang, int stamina) { // 마동석 왼쪽으로 움직이기
    if (ma_chang == Ma)
        printf("madongseok: stay %d", Ma);//마동석이 움직이지 않을때
    else printf("madongseok: %d -> %d ", ma_chang, Ma);
    if (ma_aggro == ma_aggro_chang)
        printf("(aggro: % d, stamina: %d)\n\n", ma_aggro, stamina);
    else printf("(aggro:%d->%d, stamina: %d)\n\n", ma_aggro_chang, ma_aggro, stamina);
}
void ma_aggro_write(int ma_aggro_chang, int ma_aggro, int stamina_chang, int stamina, int Ma) { //마동석 행동결과
    if (ma_aggro_chang == ma_aggro)
        printf("madongseok: %d (aggro:%d,", Ma, ma_aggro);
    else printf("madongseok: %d (aggro:%d->%d,", Ma, ma_aggro_chang, ma_aggro);
    if (stamina_chang == stamina)
        printf("stamina: % d)\n\n", stamina);
    else printf("stamina: % d-> % d)\n\n", stamina_chang, stamina);
}
//2,3-2시민
void citizen_write(int citizen, int citizen_chang, int citizen_aggro, int citizen_aggro_chang) {
    if (citizen == citizen_chang)
        printf("citizen: stay %d", citizen); // 시민 움직이지 않을때
    else
        printf("citizen: %d -> %d", citizen_chang, citizen); // 시민 움직일때
    if (citizen_aggro == citizen_aggro_chang)
        printf("(aggro:%d)\n", citizen_aggro); //aggro가 전 같을때
    else printf("(aggro:%d->%d)\n", citizen_aggro_chang, citizen_aggro); //aggro가 전 다를때
}

void citizens_write(int citizen_number) { //3-3 3-4 스테이지 / 시민
    for (int i = 0; i < citizen_number; i++) {
        if (citizen_num[i] != -1 && citizen_num[i] != 0) {
            if (citizen_num[i] == citizen_num1[i])
                printf("citizen%d: stay %d", i, citizen_num[i]); // 시민 움직이지 않을때
            else
                printf("citizen%d: %d -> %d", i, citizen_num1[i], citizen_num[i]); // 시민 움직일때
            if (citizen_num_aggro[i] == citizen_num_aggro1[i])
                printf("(aggro:%d)\n", citizen_num_aggro[i]); //aggro가 전 같을때
            else printf("(aggro:%d->%d)\n", citizen_num_aggro1[i], citizen_num_aggro[i]); //aggro가 전 다를때
        }
    }
}
//빌런
void villain_write(int villain, int villain_chang, int villain_aggro) {   //3-2 빌런 상태창
    if (villain == villain_chang)
        printf("villain: %d(aggro:%d)\n", villain, villain_aggro); // 3-2 빌런 움직이지 않을때
    else printf("villain: %d -> %d(aggro:%d)\n", villain_chang, villain, villain_aggro); // 빌런 움직일때
}
//좀비
void zombie_write(int turn, int zombie, int zombie_chang, int success) { //좀비 상태창
    if (turn % 2 == 1) {
        if (zombie == zombie_chang) {
            if (success == 1)
                printf("zombie: stay %d(pull cannot move)\n\n", zombie); // 좀비 확률로 움직이지 않을때
            else printf("zombie: stay %d\n\n", zombie);
        }
        else  printf("zombie: %d -> %d\n\n", zombie_chang, zombie); // 좀비 움직일때
    }
    else printf("zombie: stay %d(cannot move)\n\n", zombie);
}
void zombies_write(int zombie_number) { //3-4 스테이지 / 좀비
    for (int i = 1; i <= zombie_number; i++) {
        if (zombie_num[i] != 0) {
            if (zombie_num[i] == zombie_num1[i])
                printf("zombie%d: stay %d\n", i, zombie_num[i]);
            else  printf("zombie%d: %d -> %d\n", i, zombie_num1[i], zombie_num[i]); // 좀비 움직일때
        }
        else break;
    }
}

//최대, 최소값
int over(int stamina) { // 마동석 체력
    if (STM_MIN >= stamina)
        stamina = STM_MIN;
    else if (STM_MAX <= stamina)
        stamina = STM_MAX;
    return stamina;
}
int over2(int ma_aggro) { // 마동석 어그로
    if (AGGRO_min >= ma_aggro)
        ma_aggro = AGGRO_min;
    else if (AGGRO_max <= ma_aggro)
        ma_aggro = AGGRO_max;
    return ma_aggro;
}
int over3(int citizen_aggro) { // 시민어그로
    if (AGGRO_min >= citizen_aggro)
        citizen_aggro = AGGRO_min;
    else if (AGGRO_max <= citizen_aggro)
        citizen_aggro = AGGRO_max;
    return citizen_aggro;
}
int over4(int villain_aggro) { // 빌런 어그로
    if (AGGRO_min >= villain_aggro)
        villain_aggro = AGGRO_min;
    else if (AGGRO_max <= villain_aggro)
        villain_aggro = AGGRO_max;
    return villain_aggro;
}

void over5(int citizen_number) { // 시민 어그로
    for (int i = 0; i < citizen_number; i++) {
        if (AGGRO_min >= citizen_num_aggro[i])
            citizen_num_aggro[i] = AGGRO_min;
        else if (AGGRO_max <= citizen_num_aggro[i])
            citizen_num_aggro[i] = AGGRO_max;
    }
}

void zero_number() { // 시민 배열 초기화
    for (int i = 0; i < 100; i++) {
        citizen_num[i] = 0;
        citizen_num1[i] = 0;
        citizen_num_aggro[i] = 0;
        citizen_num_aggro1[i] = 0;
    }
}

int main(void) {
    srand((unsigned int)time(NULL));
    printf("\n\n//////////////////////////////////////////\n\n");
    printf("     start!!!!!!!    \n");
    printf("\n//////////////////////////////////////////\n\n");
    //초기화, 초기상태
    int len = train_lenfth(); //기차길이
    int stamina = madongseok_stamina(); // 마동석 체력
    int percent = percentile_probability(); //확률
    int citizen, zombie, Ma, villain;
    int citizen_chang, zombie_chang, ma_chang;
    int citizen_aggro_chang, ma_aggro_chang, stamina_chang;
    int citizen_aggro, ma_aggro;
    int success, dead, turn;
    //초기값
    citizen = len - 6;
    zombie = len - 3;
    Ma = len - 2;
    villain = 0;
    citizen_aggro = AGGRO_min;
    ma_aggro = AGGRO_min;
    dead = 0;
    turn = 0;
    success = 0;
    line(len, citizen, zombie, Ma, villain); // 상태출력
    printf("\n");
    while (1)
    {
        while (1) {
            // 전 값 입력
            citizen_chang = citizen;
            citizen_aggro_chang = citizen_aggro;
            zombie_chang = zombie;
            ma_chang = Ma;
            ma_aggro_chang = ma_aggro;
            stamina_chang = stamina;
            turn++;
            //이동구간
            citizen = citizen_percent1(citizen, percent); //시민이동
            citizen_aggro = citizen_percent_aggro(citizen_aggro, citizen, citizen_chang); // 시민 어그로
            citizen_aggro = over3(citizen_aggro);
            zombie = zombie_percent1(turn, percent, success, zombie, Ma, citizen, citizen_aggro, ma_aggro);//좀비이동
            line(len, citizen, zombie, Ma, villain); //상태출력
            citizen_write(citizen, citizen_chang, citizen_aggro, citizen_aggro_chang); //시민 글씨
            zombie_write(turn, zombie, zombie_chang, success);//좀비 글씨
            int ma_move = madongseok_move(Ma, zombie); // 마동석 이동(입력)
            printf("\n");
            ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // 마동석 어그로
            ma_aggro = over2(ma_aggro);
            Ma = Madongseok(Ma, ma_move); // 마동석 이동
            line(len, citizen, zombie, Ma, villain); // 상태출력
            ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // 마동석 움직이는 글씨
            stamina_chang = stamina;
            ma_aggro_chang = ma_aggro;
            if (citizen == 1) { // 맨 왼쪽에 도착 할 경우 시민 이김
                printf("YOU WIN!\n");
                printf("Next stage(4/1)\n");
                printf("***************************\n");
                printf("***************************\n\n\n");
                break;
            }
            success = 0;
            printf("citizen does nothing. \n");
            //좀비가 옆에 있을때
            if (citizen - 1 == zombie && Ma - 1 == zombie) { // 시민 어그로 vs 마동석 어그로가 같을때
                if (citizen_aggro <= ma_aggro) {
                    stamina--;
                    stamina = over(stamina);
                    if (stamina == STM_MIN) // 마동석의 체력이 min이면 끝
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
            else if (Ma - 1 == zombie) { // 마동석과 붙어 있을때
                stamina--;
                stamina = over(stamina);
                if (stamina == STM_MIN) {
                    printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
                }
                printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
                stamina_chang = stamina;
            }
            else if (citizen + 1 == zombie) { // 시민과 붙어 있을때
                printf("\nGAME OVER! citizen dead ...\n"); dead = 1; break;
            }
            else printf("zombie attacked nobody.\n"); // 아무도 안붙어 있을때
            //마동석 행동 규칙
            int action = action_ma(Ma, zombie);
            if (action == ACTION_REST) { //휴식
                ma_aggro--;
                stamina++;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                printf("madongsrok rests...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PROVOKE) { //도발
                ma_aggro = AGGRO_max;
                printf("madongsrok provoked zombie...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PULL) { //붙들기
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
        //3-2 스테이지 2 : 빌런
        printf("스테이지 2 : 빌런\n\n");
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
            citizen = citizen_percent1(citizen, percent); // 시민이동
            citizen_aggro = citizen_percent_aggro(citizen_aggro, citizen, citizen_chang); // 시민 어그로
            citizen_aggro = over3(citizen_aggro); // 시민 어그로 오버
            villain = villain_percent1(citizen, citizen_chang, villain); // 빌런 이동
            villain_aggro = villain_percent_aggro(villain, villain_aggro, villain_chang); // 빌런 어그로
            villain_aggro = over4(villain_aggro); // 빌런 어그로 오버
            zombie = zombie_percent2(turn, percent, success, zombie, Ma, citizen, citizen_aggro, ma_aggro, villain, villain_aggro);//좀비이동
            line(len, citizen, zombie, Ma, villain);
            citizen_write(citizen, citizen_chang, citizen_aggro, citizen_aggro_chang); //시민 글씨
            zombie_write(turn, zombie, zombie_chang, success);//좀비 글씨
            villain_write(villain, villain_chang, villain_aggro);
            citizen_chang = citizen;
            villain_chang = villain;
            success = 0;
            int ma_move = madongseok_move(Ma, zombie); // 마동석 이동(입력)
            printf("\n");
            ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // 마동석 어그로
            ma_aggro = over2(ma_aggro);
            Ma = Madongseok(Ma, ma_move); // 마동석 이동
            villain = villain_citizen_chang(citizen, villain);
            citizen = citizen_villain_chang(citizen, villain, villain_chang);//발암시도
            line(len, citizen, zombie, Ma, villain);
            ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // 마동석 움직이는 글씨
            stamina_chang = stamina;
            ma_aggro_chang = ma_aggro;
            if (citizen == 1) { // 맨 왼쪽에 도착 할 경우 시민 이김
                printf("YOU WIN!\n");
                printf("Next stage(4/2)\n");
                printf("***************************\n");
                printf("***************************\n\n\n");
                break;
            }
            printf("citizen does nothing. \n");
            //좀비가 옆에 있을때
            if (citizen - 1 == zombie && Ma - 1 == zombie) { // 시민 어그로 vs 마동석 어그로가 같을때
                if (citizen_aggro <= ma_aggro) {
                    stamina--;
                    stamina = over(stamina);
                    if (stamina == STM_MIN) // 마동석의 체력이 min이면 끝
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
            else if (Ma - 1 == zombie) { // 마동석과 붙어 있을때
                stamina--;
                stamina = over(stamina);
                if (stamina == STM_MIN) {
                    printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
                }
                printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
                stamina_chang = stamina;
            }
            else if (citizen + 1 == zombie) { // 시민과 붙어 있을때
                printf("\nGAME OVER! citizen dead ...\n"); dead = 1; break;
            }
            else printf("zombie attacked nobody.\n"); // 아무도 안붙어 있을때
            //마동석 행동 규칙
            int action = action_ma(Ma, zombie);
            if (action == ACTION_REST) { //휴식
                ma_aggro--;
                stamina++;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                printf("madongsrok rests...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PROVOKE) { //도발
                ma_aggro = AGGRO_max;
                printf("madongsrok provoked zombie...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PULL) { //붙들기
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
        //3-3. 스테이지3: 시민'들'
        printf("스테이지3: 시민'들'\n\n");
        zombie = len - 3;
        Ma = len - 2;
        ma_aggro = AGGRO_min;
        dead = 0;
        turn = 0;
        success = 0;
        int num = 0;//마지막 시민이 나가기 위한 임의의 값
        int citizen_number = citize_place(len); //시민숫자, 장소
        int max_number = citizen_number - 1;
        citize_array(citizen_number);
        while (1) {
            printf("\n");
            zombie_chang = zombie;
            ma_chang = Ma;
            ma_aggro_chang = ma_aggro;
            stamina_chang = stamina;
            citizen_percent_chang(citizen_number); // 이동하기 전 저장
            turn++;
            //이동구간
            citizen_percent3(percent, citizen_number);//시민들 이동
            citizen_percent_aggro3(citizen_number);//시민들 어그로
            over5(citizen_number);
            zombie = zombie_percent3(turn, success, zombie, Ma, ma_aggro, max_number, percent);//좀비이동
            line3(len, zombie, Ma, citizen_number); //상태출력
            citizens_write(citizen_number);//시민들 글씨
            citizen_percent_chang(citizen_number);// 이동하기 전 저장
            zombie_write(turn, zombie, zombie_chang, success);//좀비 글씨
            success = 0;
            int ma_move = madongseok_move(Ma, zombie); // 마동석 이동(입력)
            printf("\n");
            ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // 마동석 어그로
            ma_aggro = over2(ma_aggro);
            Ma = Madongseok(Ma, ma_move); // 마동석 이동
            line3(len, zombie, Ma, citizen_number); // 상태출력
            ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // 마동석 움직이는 글씨
            stamina_chang = stamina;
            ma_aggro_chang = ma_aggro;
            if (citizen_num[max_number] == 1) { // 맨 왼쪽에 도착 할 경우 시민 이김
                printf("YOU WIN!\n");
                printf("Next stage(4/3)\n");
                printf("***************************\n");
                printf("***************************\n\n\n");
                break;
            }
            //좀비가 옆에 있을때
            if (citizen_num[max_number] + 1 == zombie && Ma - 1 == zombie) { // 시민 어그로 vs 마동석 어그로가 같을때
                if (citizen_num_aggro[max_number] <= ma_aggro) {
                    stamina--;
                    stamina = over(stamina);
                    if (stamina == STM_MIN) // 마동석의 체력이 min이면 끝
                    {
                        printf("\n GAME OVER madongseok dead... \n");
                        dead = 1;
                        break;
                    }
                    printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", citizen_num_aggro[max_number], ma_aggro, stamina_chang, stamina);
                    stamina_chang = stamina;
                }
                else {
                    citizen_num[max_number] = -1;
                    printf("citizen%d had been attacked by zombie\n %d citizen(s) alive(s)", max_number, max_number);
                    max_number = max_number - 1;
                    if (citizen_num[max_number] == 0) {
                        printf("\n GAME OVER citizens dead... \n");
                        dead = 1; break;
                    }
                }
            }
            else if (Ma - 1 == zombie) { // 마동석과 붙어 있을때
                stamina--;
                stamina = over(stamina);
                if (stamina == STM_MIN) {
                    printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
                }
                printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
                stamina_chang = stamina;
            }
            else if (citizen_num[max_number] + 1 == zombie) { // 시민과 붙어 있을때
                citizen_num[max_number] = -1;
                printf("citizen%d had been attacked by zombie\n %d citizen(s) alive(s)", max_number, max_number);
                max_number = max_number - 1;
                if (citizen_num[max_number] == 0) {
                    printf("\n GAME OVER citizens dead... \n");
                    dead = 1; break;
                }
            }
            else printf("citizen does nothing. \n zombie attacked nobody.\n"); // 아무도 안붙어 있을때

            //마동석 행동 규칙
            int action = action_ma(Ma, zombie);
            if (action == ACTION_REST) { //휴식
                ma_aggro--;
                stamina++;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                printf("madongsrok rests...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PROVOKE) { //도발
                ma_aggro = AGGRO_max;
                printf("madongsrok provoked zombie...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PULL) { //붙들기
                ma_aggro = ma_aggro + 2;
                stamina--;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                success = Ma_percent1(percent);
                printf("%d", success);
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            if (citizen_num[num] == 1) {
                citizen_num[num] = 0;
                num++;
            }
            citizen_num_aggro_chang(citizen_number); // 어그로 저장
            printf("===========================\n\n");
        }
        if (dead == 1)
            break;
        //3-4. 스테이지4
        printf("스테이지4: 시민'들'vs 좀비'들'\n\n");
        zombie = len - 3;
        Ma = len - 2;
        ma_aggro = AGGRO_min;
        dead = 0;
        turn = 0;
        success = 0;
        zero_number();
        int zombie_number = 1; // 시민 -> 좀비로 바뀐 좀비 넘버
        int zombies_turn = 0;
        num = 0;//마지막 시민이 나가기 위한 임의의 값
        citizen_number = citize_place(len); //시민숫자, 장소 랜덤
        max_number = citizen_number - 1; //시민 최고값
        citize_array(citizen_number);
        while (1) {
            printf("\n");
            zombie_chang = zombie;
            ma_chang = Ma;
            ma_aggro_chang = ma_aggro;
            stamina_chang = stamina;
            citizen_percent_chang(citizen_number); // 이동하기 전 저장
            turn++;
            //이동구간
            citizen_percent3(percent, citizen_number);//시민들 이동
            citizen_percent_aggro3(citizen_number);//시민들 어그로
            over5(citizen_number);
            zombie = zombie_percent4(turn, success, zombie, Ma, ma_aggro, max_number, zombie_number, zombies_turn, percent);//좀비이동
            line3(len, zombie, Ma, citizen_number); //상태출력
            //시민들 글씨 출력
            citizens_write(citizen_number);//시민들 글씨
            citizen_percent_chang(citizen_number);// 시민 이동하기 전 저장
            zombie_write(turn, zombie, zombie_chang, success);//좀비 글씨
            zombies_write(zombie_number);//좀비들 글씨
            zombie_percent_chang(zombie_number);//좀비 이동하기 전 저장
            zombies_turn = 0;
            success = 0;
            int ma_move = madongseok_move(Ma, zombie); // 마동석 이동(입력)
            printf("\n");
            ma_aggro = madongseok(Ma, ma_move, zombie, ma_aggro); // 마동석 어그로
            ma_aggro = over2(ma_aggro);
            Ma = Madongseok(Ma, ma_move); // 마동석 이동
            line3(len, zombie, Ma, citizen_number); // 상태출력
            ma_write(ma_chang, Ma, ma_aggro, ma_aggro_chang, stamina); // 마동석 움직이는 글씨
            stamina_chang = stamina;
            ma_aggro_chang = ma_aggro;
            if (citizen_num[max_number] == 1) { // 맨 왼쪽에 도착 할 경우 시민 이김
                printf("YOU WIN!\n");
                printf("***************************\n");
                printf("***************************\n\n\n");
                break;
            }
            //좀비가 옆에 있을때
            if (Ma - 1 == zombie) {// 시민 어그로 vs 마동석 어그로가 같을때
                if (citizen_num[max_number] + 1 == zombie_num[zombie_number] || citizen_num[max_number] + 1 == zombie) {
                    if (citizen_num_aggro[max_number] <= ma_aggro) {
                        stamina--;
                        stamina = over(stamina);
                        if (stamina == STM_MIN) // 마동석의 체력이 min이면 끝
                        {
                            printf("\n GAME OVER madongseok dead... \n");
                            dead = 1;
                            break;
                        }
                        printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina: %d -> %d)\n", citizen_num_aggro[max_number], ma_aggro, stamina_chang, stamina);
                        stamina_chang = stamina;
                    }
                    else {
                        zombie_num[zombie_number] = citizen_num[max_number];
                        citizen_num[max_number] = -1;
                        printf("citizen%d turned into a zombie\n %d citizen(s) alive(s)", max_number, max_number);
                        zombie_number++;
                        max_number--;
                        if (citizen_num[max_number] == 0) {
                            printf("\n GAME OVER citizens dead... \n");
                            dead = 1; break;
                        }
                        zombies_turn = 1;
                    }


                }
            }
            else if (Ma - 1 == zombie) { // 마동석과 붙어 있을때
                stamina--;
                stamina = over(stamina);
                if (stamina == STM_MIN) {
                    printf("\n GAME OVER madongseok dead... \n"); dead = 1; break;
                }
                printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", stamina_chang, stamina);
                stamina_chang = stamina;
            }
            else if (citizen_num[max_number] + 1 == zombie || citizen_num[max_number] + 1 == zombie_num[zombie_number - 1]) { // 시민과 붙어 있을때
                zombie_num[zombie_number] = citizen_num[max_number];
                citizen_num[max_number] = -1;
                printf("citizen%d turned into a zombie\n %d citizen(s) alive(s)", max_number, max_number);
                max_number--;
                zombie_number++;
                if (citizen_num[max_number] == 0) {
                    printf("\n GAME OVER citizens dead... \n");
                    dead = 1; break;
                }
                zombies_turn = 1;
            }
            else printf("citizen does nothing. \n zombie attacked nobody.\n"); // 아무도 안붙어 있을때
            //마동석 행동 규칙
            int action = action_ma(Ma, zombie);
            if (action == ACTION_REST) { //휴식
                ma_aggro--;
                stamina++;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                printf("madongsrok rests...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PROVOKE) { //도발
                ma_aggro = AGGRO_max;
                printf("madongsrok provoked zombie...\n");
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            else if (action == ACTION_PULL) { //붙들기
                ma_aggro = ma_aggro + 2;
                stamina--;
                stamina = over(stamina);
                ma_aggro = over2(ma_aggro);
                success = Ma_percent1(percent);
                printf("%d", success);
                ma_aggro_write(ma_aggro_chang, ma_aggro, stamina_chang, stamina, Ma);
            }
            citizen_num_aggro_chang(citizen_number); // 어그로 저장
            zombie_percent_chang(zombie_number);// 좀비들 위치 저장
            if (citizen_num[num] == 1) {
                citizen_num[num] = 0;
                num++;
            }
            printf("===========================\n\n");
        }
        printf("\n\n//////////////////////////////////////////\n\n");
        printf("     Congratulate You win    \n");
        printf("\n//////////////////////////////////////////\n\n");
        break;
    }
    return 0;
}