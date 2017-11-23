#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "list.h"
#include "BinarySearchTree.h"

#define INPUT_FILE "plist.dat"
#define PROCESS_OPEN 1
#define PROCESS_CLOSE 0
#define RR_ 0
#define FCFS_ 1
typedef enum { false, true } bool;

int selectScheme() {
	char input[10];
	int num;

	printf("\n");
	printf("  1. First-Come-First-Service\n");
	printf("  2. Round-Robin\n");
	printf("  3. Shortest-Remaining-Time-Next\n");
	printf("  4. High-Response-Ratio-Next\n");
	printf("  5. NewIdea\n");
	printf("  6. Exit\n");
	printf("Select scheduling scheme: ");
	gets(input);
	num = atoi(input);
	fflush(stdin);
	printf("\n");

	return num;
}

int indexsearch(int *arr, int pnum, int item) {
	int i;
	
	for (i = 0; i < pnum; i++) {
		if (arr[i] == item) {
			return i;
		}
	}
	return -1;
}

int sumarr(int *arr, int pnum) {
	int sum = 0, i;

	for (i = 0; i < pnum; i++) {
		sum = sum + arr[i];
	}
	return sum;
}

void printResult(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	int i, sum_tt = 0, sum_wt = 0;

	printf("%15s %15s %15s %15s %15s\n", "Process id", "Arrive time", "Burst time", "Turnaround time", "Waiting time");
	for (i = 0; i<pnum; ++i) {
		printf("%15d %15d %15d %15d %15d\n", pid[i], at[i], bt[i], tt[i], wt[i]);
		sum_tt += tt[i];
		sum_wt += wt[i];
	}

	printf("  avg. of TT: %.2f\n", (float)sum_tt / pnum);
	printf("  avg. of WT: %.2f\n", (float)sum_wt / pnum);
}

void FCFS(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {		// at : 도착시간, bt 수행시간
	printf("  Scheme: First-Come-First-Service\n");
	/* fill in */
	int *at_s, *end_time, *start_time;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																								// *at_s : 도착시간 복사할 배열, *end_time : 종료시간 배열, *start_time : 시작시간 배열
	int i, time = 0;													// i : for문용 i, time: 시간 변수
	int state = PROCESS_OPEN;											// state : 상태변수( 1 : OPEN, 2 : CLOSE)
	int searchindex = -1;												// searchindex = 검색된 인덱스를 넣을 배열, 초기화시킴

	element item, temp;

	QueueNode **qf, **qr;							// Queue front, rear
	initQueue(&qf, &qr);

	at_s = (int *)calloc(pnum, sizeof(int));
	end_time = (int *)calloc(pnum, sizeof(int));
	start_time = (int *)calloc(pnum, sizeof(int));

	for (i = 0; i < pnum; i++) {												// 도착 시간 복사
		at_s[i] = at[i];
	}

	while (1) {
		searchindex = indexsearch(at_s, pnum, time);			// 도착시간에 있는 인덱스를 리턴
		if (searchindex != -1) {								// 대기에서 큐로 삽입
			at_s[searchindex] = -1;								// 검색이 안되게 pid를 -1로 설정
			item.pid = pid[searchindex];						// 해당 인덱스 pid와
			item.bt = bt[searchindex];							// 수행시간을 큐에 넣는다.
			enQueue(&qf, &qr, item);
		}
		if (state == PROCESS_OPEN && !emptyQueue(&qf)) {							// 큐에서 프로세서로 디큐 (프로세서가 열려있고, 큐가 비지 않았을 경우 디큐)
			temp = deQueue(&qf, &qr);												// temp(프로세서) 계산
			searchindex = indexsearch(pid, pnum, temp.pid);							// 큐에서 꺼낸 pid의 인덱스 검색
			start_time[searchindex] = time;											// 시작한 시간
			state = PROCESS_CLOSE;													// 프로세서를 닫는다.
		}
		searchindex = indexsearch(pid, pnum, temp.pid);								// 해당 pid 인덱스 검색
		temp.bt--;																	// 큐에서 꺼낸 bt(수행시간 감소, 즉 연산)
		if (temp.bt == 0) {															// 수행시간이 0일 경우(연산이 끝났을 경우)
			end_time[searchindex] = time;											// 끝난시간 배열에 넣고
			state = PROCESS_OPEN;													// 프로세서를 연다
		}
	
		if (sumarr(bt,pnum) == time) {												// 총 수행시간이랑 시간이 같을 경우 프로세서 종료
			break;
		}
		time++;																		// 시간증가
	}
	for (i = 0; i < pnum; i++) {
		tt[i] = end_time[i] - at[i] + 1;
	}
	for (i = 0; i < pnum; i++) {
		wt[i] = start_time[i] - at[i];
	}
	free(at_s);																		// 할당 자원 free
	free(end_time);
	free(start_time);
}

void RR(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	char input[10];
	int Q;
	int i = 0;
	int time = 0; //프로세스 실행 시간
	int pIndex = 0;//프로세스 인덱스
	QueueNode **front;
	QueueNode **rear;
	bool isProcessing = false;
	element inputE;
	element crntProcess;
	int timeQ;

	initQueue(&front, &rear);
	do
	{
		system("cls");
		printf("Scheme: Round-Robin\n");
		printf("time quantum: ");
		gets(input);
		fflush(stdin);
		input[9] = '\0';
		Q = atoi(input);

		fflush(stdin);

		timeQ = Q;
	} while (Q <= 0 || Q >= 90000000);


	while (pnum != pIndex || !emptyQueue(&front) || isProcessing != false) {  // 프로세스 인덱스 값이 pnum과 같지 않고 큐가 비어있지 않으면 계속 실행
		if (time == at[pIndex]) { // 1. 프로세스 시간이 프로세스의 AT와 같으면 enqueue      
			inputE.bt = bt[pIndex];
			inputE.pid = pid[pIndex];
			inputE.wt = wt[pIndex];

			enQueue(&front, &rear, inputE);

			pIndex++;                        //다음 프로세스 준비
		}
		//////////////AT랑 같은 Process Enqueue////////////

		if (!emptyQueue(&front) && isProcessing == false) {   //// 큐가 비어있지 않고, 프로세스가 실행중이 아니라면 디큐

			crntProcess = deQueue(&front, &rear);

			if (crntProcess.bt <= 0) {                  //bt가 0이라면
				while (crntProcess.bt <= 0) {
					if (!emptyQueue(&front)) {
						crntProcess = deQueue(&front, &rear);
						timeQ = Q;
						isProcessing = true;
					}
					else {
						isProcessing = false;
						break;
					}
				}
			}
			else {
				timeQ = Q;
				isProcessing = true;
			}
		}
		/////////////계산할 프로세스 선정//////////////////

		if (timeQ <= 0 && isProcessing == true) {            //그 프로세스가 타임 퀀텀을 다 썼다면 다음 프로세스 받아야함
			if (!emptyQueue(&front)) {
				enQueue(&front, &rear, crntProcess);
				crntProcess = deQueue(&front, &rear);
				if (crntProcess.bt <= 0) {                  //bt가 0이라면
					while (crntProcess.bt <= 0) {
						if (!emptyQueue(&front)) {
							crntProcess = deQueue(&front, &rear);
							timeQ = Q;
							isProcessing = true;
						}
						else {
							isProcessing = false;
							break;
						}
					}
				}
				else    timeQ = Q;
			}
			else
			{
				timeQ = Q;
			}

		}

		if (timeQ >= 1 && isProcessing == true) {               //타임 퀀텀이 1 이상이고, 프로세스가 선정되었다면 계산
			if (crntProcess.bt >= 0) {                                 //bt가 0이 아니라면
				crntProcess.bt -= 1;
				timeQ--;
				if (crntProcess.bt <= 0 && crntProcess.pid != 0) {                              //계산이 다 끝났으면
					wt[crntProcess.pid - 1] = crntProcess.wt;
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					crntProcess.pid = 0;
					isProcessing = false;                              //다음 프로세스를 받을 준비를 함
				}

			}
			else {                                                //다음 큐를 삽입

				crntProcess = deQueue(&rear, &front);
				timeQ = Q;
				crntProcess.bt -= 1;
				timeQ--;
				if (crntProcess.bt <= 0 && crntProcess.pid != 0) {                              //계산이 다 끝났으면
					wt[crntProcess.pid - 1] = crntProcess.wt;
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					crntProcess.pid = 0;
					isProcessing = false;                              //다음 프로세스를 받을 준비를 함
				}

			}
		}

		addWt(&front);
		time++;
	}
}

void SRTN(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	system("cls");
	printf("  Scheme: Shortest-Remaining-Time-Next\n");

	int i = 0;
	int time = 0; //프로세스 실행 시간
	int pIndex = 0;//프로세스 인덱스
	int select = 1;
	Lelement crntProcess;
	bool isProcessing = false;
	List list;
	Lelement input;

	list_init(&list);
	while (pnum != pIndex || !list_isEmpty(&list) || isProcessing != false) {  //  프로세스 인덱스 값이 pnum과 같지 않고 큐가 비어있지 않으면 계속 실행
		if (time == at[pIndex]) { ////1. 프로세스 시간이 프로세스의 AT와 같으면 enqueue      
			input.bt = bt[pIndex];
			input.pid = pid[pIndex];
			input.wt = wt[pIndex];
			list_push_back(&list, input);

			pIndex++;                        //다음 프로세스 준비
		}
		if (!list_isEmpty(&list) && isProcessing == false) {   //// 큐가 비어있지 않고, 프로세스가 실행중이 아니라면 디큐
			crntProcess = list_erasebt(&list);

			if (crntProcess.bt <= 0) {
				while (crntProcess.bt <= 0) {
					if (!list_isEmpty(&list)) {
						list_erasebt(&list);
						isProcessing = true;
					}
					else {
						isProcessing = false;
						break;
					}
				}
			}
			else
				isProcessing = true;
		}

		if (isProcessing) {                      //리스트에 프로세스가 올라왔다면 1 만큼 계산
			if (crntProcess.bt != 0) {            // 버스트 타임이 0이 아니라면 
				crntProcess.bt -= 1;            // 계산
				if (crntProcess.bt == 0) {
					wt[crntProcess.pid - 1] = crntProcess.wt;       //wt 복사
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				}
			}
			else {
				//bt가 0이라면 프로세스를 끝내고 다음프로세스를 넣고 계산.
				if (!list_isEmpty(&list)) {         //리스트가 비어있지 않다면
					crntProcess = list_erasebt(&list);
					if (crntProcess.bt <= 0) {
						while (crntProcess.bt <= 0) {
							if (!list_isEmpty(&list)) {
								crntProcess = list_erasebt(&list);
							}
							else {
								isProcessing = false;
								break;
							}
						}
						crntProcess.bt -= 1;
					}
					else crntProcess.bt -= 1;            // 계산
					if (crntProcess.bt == 0) {
						wt[crntProcess.pid - 1] = crntProcess.wt;       //wt 복사
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					}
				}
				else {  //비어있다면
					isProcessing = false;
				}
			}
		}
		addWtList(&list);
		time++;
	}
}

void print_list(List *list, Node* cursor)
{
	Node * node = list->head;
	while (node != NULL)
	{
		if (node == cursor)
			printf("pid : %d -> ", node->data.pid);
		else
			printf("pid : %d -> ", node->data.pid);
		node = node->next;
	}
	printf("\n");
}

void HRRN(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	system("cls");
	printf("  Scheme: High-Response-Ratio-Next\n");

	int i = 0;
	int time = 0; //프로세스 실행 시간
	int pIndex = 0;//프로세스 인덱스
	int select = 1;
	Lelement crntProcess;
	bool isProcessing = false;
	List list;
	Lelement input;

	list_init(&list);
	while (pnum != pIndex || !list_isEmpty(&list) || isProcessing != false) {  //  프로세스 인덱스 값이 pnum과 같지 않고 큐가 비어있지 않으면 계속 실행
		if (time == at[pIndex]) { ////1. 프로세스 시간이 프로세스의 AT와 같으면 enqueue      
			input.bt = bt[pIndex];
			input.pid = pid[pIndex];
			input.wt = wt[pIndex];
			input.R = 1;
			list_push_back(&list, input);

			pIndex++;                        //다음 프로세스 준비
		}
		if (!list_isEmpty(&list) && isProcessing == false) {   //// 큐가 비어있지 않고, 프로세스가 실행중이 아니라면 디큐
			crntProcess = list_erase(&list);

			if (crntProcess.bt <= 0) {
				while (crntProcess.bt <= 0) {
					if (!list_isEmpty(&list)) {
						list_erase(&list);						
						isProcessing = true;
					}
					else {
						isProcessing = false;
						break;
					}
				}
			}
			else
				isProcessing = true;
		}

		if (isProcessing) {                      //리스트에 프로세스가 올라왔다면 1 만큼 계산
			if (crntProcess.bt != 0) {            // 버스트 타임이 0이 아니라면 
				crntProcess.bt -= 1;            // 계산
				if (crntProcess.bt == 0) {
					wt[crntProcess.pid - 1] = crntProcess.wt;       //wt 복사
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				}
			}
			else {
				//bt가 0이라면 프로세스를 끝내고 다음프로세스를 넣고 계산.
				if (!list_isEmpty(&list)) {         //리스트가 비어있지 않다면
					crntProcess = list_erase(&list);
					if (crntProcess.bt <= 0) {
						while (crntProcess.bt <= 0) {
							if (!list_isEmpty(&list)) {
								crntProcess = list_erase(&list);
							}
							else {
								isProcessing = false;
								break;
							}
						}
						crntProcess.bt -= 1;
					}
					else crntProcess.bt -= 1;            // 계산
					if (crntProcess.bt == 0) {
						wt[crntProcess.pid - 1] = crntProcess.wt;       //wt 복사
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					}
				}
				else {  //비어있다면
					isProcessing = false;
				}
			}
		}
		addWtList(&list);
		time++;
	}
}

void NewIdea(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	system("cls");
	printf("   Scheme : NewIdea\n");
	char input[10];
	int Q;
	int i = 0;
	int time = 0; //프로세스 실행 시간
	int pIndex = 0;//프로세스 인덱스
	QueueNode **FCFSfront;
	QueueNode **FCFSrear;

	QueueNode **RRfront;
	QueueNode **RRrear;
	bool isRRProcessing = false;
	bool isFCFSProcessing = false;
	element inputE;
	element crntProcess;
	int timeQ;
	bool toggle = 1;
	do
	{

		printf("time quantum: ");
		gets(input);
		fflush(stdin);
		input[9] = '\0';
		Q = atoi(input);
		fflush(stdin);
		timeQ = Q;
	} while (Q <= 0 || Q >= 90000000);

	initQueue(&FCFSfront, &FCFSrear);
	initQueue(&RRfront, &RRrear);

	//프로세스 시작

	// pnum 이 pindex와 같지 않고, FCFS, RR큐가 비어있지 않고, FCFS 프로세싱, RR프로세싱이 true가 아니면 실행
	while (pnum != pIndex || emptyQueue(&FCFSfront) == 0 || emptyQueue(&RRfront) == 0 || isFCFSProcessing == true || isRRProcessing == true) {  //  프로세스 인덱스 값이 pnum과 같지 않고 큐가 비어있지 않으면 계속 실행
		if (time == at[pIndex]) {				// 1. 프로세스 시간이 프로세스의 AT와 같으면 enqueue      
			inputE.bt = bt[pIndex];
			inputE.pid = pid[pIndex];
			inputE.wt = wt[pIndex];

			if (inputE.bt >= 5) {
				enQueue(&RRfront, &RRrear, inputE);
			}
			else
				enQueue(&FCFSfront, &FCFSrear, inputE);

			pIndex++;                        //다음 프로세스 준비

		}
		if (toggle == FCFS_ && isRRProcessing == true) {         //RR 프로세싱 끝나고 , FCFS 할 차례일 경우 RRqueue에 enqueue
			enQueue(&RRfront, &RRrear, crntProcess);
			isRRProcessing = false;
		}
		if (toggle == FCFS_ && isRRProcessing == false) {
			if (crntProcess.bt <= 0 && isFCFSProcessing == true) {               //bt 가 0보다 작거나 같으면 프로세스 계산이 끝난 것이므로
				wt[crntProcess.pid - 1] = crntProcess.wt;       //wt 복사
				tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				if (!emptyQueue(&RRfront)) {                              //RR 차례로가야하는데 RR이 비어있다면 FCFS로..
					toggle = RR_;
					isFCFSProcessing = false;
				}
				else
					isFCFSProcessing = true;
			}

			if (emptyQueue(&FCFSfront) == 0 && isFCFSProcessing == false && toggle == FCFS_) {   //// 큐가 비어있지 않고, 프로세스가 실행중이 아니라면 디큐
				crntProcess = deQueue(&FCFSfront, &FCFSrear);
				if (crntProcess.bt <= 0) {                  //bt가 0인 프로세스라면
					while (crntProcess.bt <= 0) {
						if (!emptyQueue(&FCFSfront)) {                        //FCFS 큐가 비어있지 않다면
							crntProcess = deQueue(&FCFSfront, &FCFSrear);         //dequeue
							isFCFSProcessing = true;
						}
						else {                                          //비어있다면
							isFCFSProcessing = false;
							toggle = RR_;
							break;
						}
					}
				}
				else isFCFSProcessing = true;
			}
			else if (emptyQueue(&FCFSfront) && isFCFSProcessing == false && toggle == FCFS_) {      //FCFS 큐가 비어있고 FCFS가 프로세싱중이 아니라면 
				toggle = RR_;                                                      //RR로
			}

			if (isFCFSProcessing) {                      //큐에 프로세스가 올라왔다면 1 만큼 계산
				if (crntProcess.bt != 0) {            // 버스트 타임이 0이 아니라면 
					crntProcess.bt -= 1;            // 계산
				}
				else {
					if (!emptyQueue(&FCFSfront)) {         //큐가 비어있지 않다면
						crntProcess = deQueue(&FCFSfront, &FCFSrear);
						if (crntProcess.bt <= 0) {                  //bt가 0인 프로세스라면
							while (crntProcess.bt <= 0) {
								if (!emptyQueue(&FCFSfront)) {                        //FCFS 큐가 비어있지 않다면
									crntProcess = deQueue(&FCFSfront, &FCFSrear);         //dequeue
									isFCFSProcessing = true;
								}
								else {                                          //비어있다면
									isFCFSProcessing = false;
									toggle = RR_;
									break;
								}
							}
						}
						else {
							crntProcess.bt -= 1;            // 계산
						}
					}
					else {  //비어있다면
						isFCFSProcessing = false;
					}
				}
			}
		}

		if (toggle == RR_ && isFCFSProcessing == false) {
			if (!emptyQueue(&RRfront) && isRRProcessing == false) {   //// 큐가 비어있지 않고, 프로세스가 실행중이 아니라면 디큐

				crntProcess = deQueue(&RRfront, &RRrear);
				timeQ = Q;
				isRRProcessing = true;
			}
			else if (emptyQueue(&RRfront) && isRRProcessing == false) {//비어있다면 FCFS로
				isRRProcessing = false;
				toggle = FCFS_;
			}


			/////////////계산할 프로세스 선정//////////////////

			if (timeQ <= 0 && isRRProcessing == true) {            //그 프로세스가 타임 퀀텀을 다 썼다면 다음 프로세스 받아야함
				if (!emptyQueue(&RRfront)) {
					enQueue(&RRfront, &RRrear, crntProcess);
					crntProcess = deQueue(&RRfront, &RRrear);
					timeQ = Q;
					toggle = FCFS_;
					isRRProcessing = false;
				}
				else if (emptyQueue(&FCFSfront))
				{
					timeQ = Q;
				}
			}
			if (timeQ >= 1 && isRRProcessing == true) {               //타임 퀀텀이 1 이상이고, 프로세스가 선정되었다면 계산
				if (crntProcess.bt >= 0) {                                 //bt가 0이 아니라면
					crntProcess.bt -= 1;
					timeQ--;
					if (crntProcess.bt <= 0) {//계산이 다 끝났으면
						wt[crntProcess.pid - 1] = crntProcess.wt;
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
						isRRProcessing = false;                              //다음 프로세스를 받을 준비를 함
						toggle = FCFS_;
					}
					if (timeQ == 0) {
						//다음 프로세스를 받을 준비를 함
						toggle = FCFS_;
					}

				}
			}
		}


		addWt(&FCFSfront);
		addWt(&RRfront);

		time++;
	}
}

int main(void) {
	FILE *fp;
	int pnum, i, exit = 0;
	int *pid, *at, *bt, *tt, *wt;

	fp = fopen(INPUT_FILE, "r");
	//read the number of processes 
	//++
	if (fp == NULL) {
		printf("\nfile open error!!!");
		return 0;
	}
	//++
	fscanf(fp, "%d", &pnum);

	pid = (int*)calloc(pnum, sizeof(int));				 // (개수, 사이즈)
	at = (int*)calloc(pnum, sizeof(int));
	bt = (int*)calloc(pnum, sizeof(int));
	tt = (int*)calloc(pnum, sizeof(int));
	wt = (int*)calloc(pnum, sizeof(int));

	for (i = 0; i<pnum; ++i) {
		fscanf(fp, "%d %d %d", &pid[i], &at[i], &bt[i]);
	}

	fclose(fp);

	while (!exit) {
		switch (selectScheme()) {
		case 1:
			FCFS(pnum, pid, at, bt, tt, wt);
			break;
		case 2:
			RR(pnum, pid, at, bt, tt, wt);
			break;
		case 3:
			SRTN(pnum, pid, at, bt, tt, wt);
			break;
		case 4:
			HRRN(pnum, pid, at, bt, tt, wt);
			break;
		case 5:
			NewIdea(pnum, pid, at, bt, tt, wt);
			break;
		case 6:
			exit = 1;
			continue;
		default:
			continue;
		}

		printResult(pnum, pid, at, bt, tt, wt);
		memset(tt, 0, sizeof(int)*pnum);
		memset(wt, 0, sizeof(int)*pnum);
	}

	return 0;
}

