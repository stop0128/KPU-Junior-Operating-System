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

void FCFS(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {		// at : �����ð�, bt ����ð�
	printf("  Scheme: First-Come-First-Service\n");
	/* fill in */
	int *at_s, *end_time, *start_time;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																								// *at_s : �����ð� ������ �迭, *end_time : ����ð� �迭, *start_time : ���۽ð� �迭
	int i, time = 0;													// i : for���� i, time: �ð� ����
	int state = PROCESS_OPEN;											// state : ���º���( 1 : OPEN, 2 : CLOSE)
	int searchindex = -1;												// searchindex = �˻��� �ε����� ���� �迭, �ʱ�ȭ��Ŵ

	element item, temp;

	QueueNode **qf, **qr;							// Queue front, rear
	initQueue(&qf, &qr);

	at_s = (int *)calloc(pnum, sizeof(int));
	end_time = (int *)calloc(pnum, sizeof(int));
	start_time = (int *)calloc(pnum, sizeof(int));

	for (i = 0; i < pnum; i++) {												// ���� �ð� ����
		at_s[i] = at[i];
	}

	while (1) {
		searchindex = indexsearch(at_s, pnum, time);			// �����ð��� �ִ� �ε����� ����
		if (searchindex != -1) {								// ��⿡�� ť�� ����
			at_s[searchindex] = -1;								// �˻��� �ȵǰ� pid�� -1�� ����
			item.pid = pid[searchindex];						// �ش� �ε��� pid��
			item.bt = bt[searchindex];							// ����ð��� ť�� �ִ´�.
			enQueue(&qf, &qr, item);
		}
		if (state == PROCESS_OPEN && !emptyQueue(&qf)) {							// ť���� ���μ����� ��ť (���μ����� �����ְ�, ť�� ���� �ʾ��� ��� ��ť)
			temp = deQueue(&qf, &qr);												// temp(���μ���) ���
			searchindex = indexsearch(pid, pnum, temp.pid);							// ť���� ���� pid�� �ε��� �˻�
			start_time[searchindex] = time;											// ������ �ð�
			state = PROCESS_CLOSE;													// ���μ����� �ݴ´�.
		}
		searchindex = indexsearch(pid, pnum, temp.pid);								// �ش� pid �ε��� �˻�
		temp.bt--;																	// ť���� ���� bt(����ð� ����, �� ����)
		if (temp.bt == 0) {															// ����ð��� 0�� ���(������ ������ ���)
			end_time[searchindex] = time;											// �����ð� �迭�� �ְ�
			state = PROCESS_OPEN;													// ���μ����� ����
		}
	
		if (sumarr(bt,pnum) == time) {												// �� ����ð��̶� �ð��� ���� ��� ���μ��� ����
			break;
		}
		time++;																		// �ð�����
	}
	for (i = 0; i < pnum; i++) {
		tt[i] = end_time[i] - at[i] + 1;
	}
	for (i = 0; i < pnum; i++) {
		wt[i] = start_time[i] - at[i];
	}
	free(at_s);																		// �Ҵ� �ڿ� free
	free(end_time);
	free(start_time);
}

void RR(int pnum, int *pid, int *at, int *bt, int *tt, int *wt) {
	char input[10];
	int Q;
	int i = 0;
	int time = 0; //���μ��� ���� �ð�
	int pIndex = 0;//���μ��� �ε���
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


	while (pnum != pIndex || !emptyQueue(&front) || isProcessing != false) {  // ���μ��� �ε��� ���� pnum�� ���� �ʰ� ť�� ������� ������ ��� ����
		if (time == at[pIndex]) { // 1. ���μ��� �ð��� ���μ����� AT�� ������ enqueue      
			inputE.bt = bt[pIndex];
			inputE.pid = pid[pIndex];
			inputE.wt = wt[pIndex];

			enQueue(&front, &rear, inputE);

			pIndex++;                        //���� ���μ��� �غ�
		}
		//////////////AT�� ���� Process Enqueue////////////

		if (!emptyQueue(&front) && isProcessing == false) {   //// ť�� ������� �ʰ�, ���μ����� �������� �ƴ϶�� ��ť

			crntProcess = deQueue(&front, &rear);

			if (crntProcess.bt <= 0) {                  //bt�� 0�̶��
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
		/////////////����� ���μ��� ����//////////////////

		if (timeQ <= 0 && isProcessing == true) {            //�� ���μ����� Ÿ�� ������ �� ��ٸ� ���� ���μ��� �޾ƾ���
			if (!emptyQueue(&front)) {
				enQueue(&front, &rear, crntProcess);
				crntProcess = deQueue(&front, &rear);
				if (crntProcess.bt <= 0) {                  //bt�� 0�̶��
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

		if (timeQ >= 1 && isProcessing == true) {               //Ÿ�� ������ 1 �̻��̰�, ���μ����� �����Ǿ��ٸ� ���
			if (crntProcess.bt >= 0) {                                 //bt�� 0�� �ƴ϶��
				crntProcess.bt -= 1;
				timeQ--;
				if (crntProcess.bt <= 0 && crntProcess.pid != 0) {                              //����� �� ��������
					wt[crntProcess.pid - 1] = crntProcess.wt;
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					crntProcess.pid = 0;
					isProcessing = false;                              //���� ���μ����� ���� �غ� ��
				}

			}
			else {                                                //���� ť�� ����

				crntProcess = deQueue(&rear, &front);
				timeQ = Q;
				crntProcess.bt -= 1;
				timeQ--;
				if (crntProcess.bt <= 0 && crntProcess.pid != 0) {                              //����� �� ��������
					wt[crntProcess.pid - 1] = crntProcess.wt;
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					crntProcess.pid = 0;
					isProcessing = false;                              //���� ���μ����� ���� �غ� ��
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
	int time = 0; //���μ��� ���� �ð�
	int pIndex = 0;//���μ��� �ε���
	int select = 1;
	Lelement crntProcess;
	bool isProcessing = false;
	List list;
	Lelement input;

	list_init(&list);
	while (pnum != pIndex || !list_isEmpty(&list) || isProcessing != false) {  //  ���μ��� �ε��� ���� pnum�� ���� �ʰ� ť�� ������� ������ ��� ����
		if (time == at[pIndex]) { ////1. ���μ��� �ð��� ���μ����� AT�� ������ enqueue      
			input.bt = bt[pIndex];
			input.pid = pid[pIndex];
			input.wt = wt[pIndex];
			list_push_back(&list, input);

			pIndex++;                        //���� ���μ��� �غ�
		}
		if (!list_isEmpty(&list) && isProcessing == false) {   //// ť�� ������� �ʰ�, ���μ����� �������� �ƴ϶�� ��ť
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

		if (isProcessing) {                      //����Ʈ�� ���μ����� �ö�Դٸ� 1 ��ŭ ���
			if (crntProcess.bt != 0) {            // ����Ʈ Ÿ���� 0�� �ƴ϶�� 
				crntProcess.bt -= 1;            // ���
				if (crntProcess.bt == 0) {
					wt[crntProcess.pid - 1] = crntProcess.wt;       //wt ����
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				}
			}
			else {
				//bt�� 0�̶�� ���μ����� ������ �������μ����� �ְ� ���.
				if (!list_isEmpty(&list)) {         //����Ʈ�� ������� �ʴٸ�
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
					else crntProcess.bt -= 1;            // ���
					if (crntProcess.bt == 0) {
						wt[crntProcess.pid - 1] = crntProcess.wt;       //wt ����
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					}
				}
				else {  //����ִٸ�
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
	int time = 0; //���μ��� ���� �ð�
	int pIndex = 0;//���μ��� �ε���
	int select = 1;
	Lelement crntProcess;
	bool isProcessing = false;
	List list;
	Lelement input;

	list_init(&list);
	while (pnum != pIndex || !list_isEmpty(&list) || isProcessing != false) {  //  ���μ��� �ε��� ���� pnum�� ���� �ʰ� ť�� ������� ������ ��� ����
		if (time == at[pIndex]) { ////1. ���μ��� �ð��� ���μ����� AT�� ������ enqueue      
			input.bt = bt[pIndex];
			input.pid = pid[pIndex];
			input.wt = wt[pIndex];
			input.R = 1;
			list_push_back(&list, input);

			pIndex++;                        //���� ���μ��� �غ�
		}
		if (!list_isEmpty(&list) && isProcessing == false) {   //// ť�� ������� �ʰ�, ���μ����� �������� �ƴ϶�� ��ť
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

		if (isProcessing) {                      //����Ʈ�� ���μ����� �ö�Դٸ� 1 ��ŭ ���
			if (crntProcess.bt != 0) {            // ����Ʈ Ÿ���� 0�� �ƴ϶�� 
				crntProcess.bt -= 1;            // ���
				if (crntProcess.bt == 0) {
					wt[crntProcess.pid - 1] = crntProcess.wt;       //wt ����
					tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				}
			}
			else {
				//bt�� 0�̶�� ���μ����� ������ �������μ����� �ְ� ���.
				if (!list_isEmpty(&list)) {         //����Ʈ�� ������� �ʴٸ�
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
					else crntProcess.bt -= 1;            // ���
					if (crntProcess.bt == 0) {
						wt[crntProcess.pid - 1] = crntProcess.wt;       //wt ����
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
					}
				}
				else {  //����ִٸ�
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
	int time = 0; //���μ��� ���� �ð�
	int pIndex = 0;//���μ��� �ε���
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

	//���μ��� ����

	// pnum �� pindex�� ���� �ʰ�, FCFS, RRť�� ������� �ʰ�, FCFS ���μ���, RR���μ����� true�� �ƴϸ� ����
	while (pnum != pIndex || emptyQueue(&FCFSfront) == 0 || emptyQueue(&RRfront) == 0 || isFCFSProcessing == true || isRRProcessing == true) {  //  ���μ��� �ε��� ���� pnum�� ���� �ʰ� ť�� ������� ������ ��� ����
		if (time == at[pIndex]) {				// 1. ���μ��� �ð��� ���μ����� AT�� ������ enqueue      
			inputE.bt = bt[pIndex];
			inputE.pid = pid[pIndex];
			inputE.wt = wt[pIndex];

			if (inputE.bt >= 5) {
				enQueue(&RRfront, &RRrear, inputE);
			}
			else
				enQueue(&FCFSfront, &FCFSrear, inputE);

			pIndex++;                        //���� ���μ��� �غ�

		}
		if (toggle == FCFS_ && isRRProcessing == true) {         //RR ���μ��� ������ , FCFS �� ������ ��� RRqueue�� enqueue
			enQueue(&RRfront, &RRrear, crntProcess);
			isRRProcessing = false;
		}
		if (toggle == FCFS_ && isRRProcessing == false) {
			if (crntProcess.bt <= 0 && isFCFSProcessing == true) {               //bt �� 0���� �۰ų� ������ ���μ��� ����� ���� ���̹Ƿ�
				wt[crntProcess.pid - 1] = crntProcess.wt;       //wt ����
				tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
				if (!emptyQueue(&RRfront)) {                              //RR ���ʷΰ����ϴµ� RR�� ����ִٸ� FCFS��..
					toggle = RR_;
					isFCFSProcessing = false;
				}
				else
					isFCFSProcessing = true;
			}

			if (emptyQueue(&FCFSfront) == 0 && isFCFSProcessing == false && toggle == FCFS_) {   //// ť�� ������� �ʰ�, ���μ����� �������� �ƴ϶�� ��ť
				crntProcess = deQueue(&FCFSfront, &FCFSrear);
				if (crntProcess.bt <= 0) {                  //bt�� 0�� ���μ������
					while (crntProcess.bt <= 0) {
						if (!emptyQueue(&FCFSfront)) {                        //FCFS ť�� ������� �ʴٸ�
							crntProcess = deQueue(&FCFSfront, &FCFSrear);         //dequeue
							isFCFSProcessing = true;
						}
						else {                                          //����ִٸ�
							isFCFSProcessing = false;
							toggle = RR_;
							break;
						}
					}
				}
				else isFCFSProcessing = true;
			}
			else if (emptyQueue(&FCFSfront) && isFCFSProcessing == false && toggle == FCFS_) {      //FCFS ť�� ����ְ� FCFS�� ���μ������� �ƴ϶�� 
				toggle = RR_;                                                      //RR��
			}

			if (isFCFSProcessing) {                      //ť�� ���μ����� �ö�Դٸ� 1 ��ŭ ���
				if (crntProcess.bt != 0) {            // ����Ʈ Ÿ���� 0�� �ƴ϶�� 
					crntProcess.bt -= 1;            // ���
				}
				else {
					if (!emptyQueue(&FCFSfront)) {         //ť�� ������� �ʴٸ�
						crntProcess = deQueue(&FCFSfront, &FCFSrear);
						if (crntProcess.bt <= 0) {                  //bt�� 0�� ���μ������
							while (crntProcess.bt <= 0) {
								if (!emptyQueue(&FCFSfront)) {                        //FCFS ť�� ������� �ʴٸ�
									crntProcess = deQueue(&FCFSfront, &FCFSrear);         //dequeue
									isFCFSProcessing = true;
								}
								else {                                          //����ִٸ�
									isFCFSProcessing = false;
									toggle = RR_;
									break;
								}
							}
						}
						else {
							crntProcess.bt -= 1;            // ���
						}
					}
					else {  //����ִٸ�
						isFCFSProcessing = false;
					}
				}
			}
		}

		if (toggle == RR_ && isFCFSProcessing == false) {
			if (!emptyQueue(&RRfront) && isRRProcessing == false) {   //// ť�� ������� �ʰ�, ���μ����� �������� �ƴ϶�� ��ť

				crntProcess = deQueue(&RRfront, &RRrear);
				timeQ = Q;
				isRRProcessing = true;
			}
			else if (emptyQueue(&RRfront) && isRRProcessing == false) {//����ִٸ� FCFS��
				isRRProcessing = false;
				toggle = FCFS_;
			}


			/////////////����� ���μ��� ����//////////////////

			if (timeQ <= 0 && isRRProcessing == true) {            //�� ���μ����� Ÿ�� ������ �� ��ٸ� ���� ���μ��� �޾ƾ���
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
			if (timeQ >= 1 && isRRProcessing == true) {               //Ÿ�� ������ 1 �̻��̰�, ���μ����� �����Ǿ��ٸ� ���
				if (crntProcess.bt >= 0) {                                 //bt�� 0�� �ƴ϶��
					crntProcess.bt -= 1;
					timeQ--;
					if (crntProcess.bt <= 0) {//����� �� ��������
						wt[crntProcess.pid - 1] = crntProcess.wt;
						tt[crntProcess.pid - 1] = crntProcess.wt + bt[crntProcess.pid - 1];
						isRRProcessing = false;                              //���� ���μ����� ���� �غ� ��
						toggle = FCFS_;
					}
					if (timeQ == 0) {
						//���� ���μ����� ���� �غ� ��
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

	pid = (int*)calloc(pnum, sizeof(int));				 // (����, ������)
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

