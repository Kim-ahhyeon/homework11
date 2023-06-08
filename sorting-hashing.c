/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE//MAX_HASH_TABLE_SIZE	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);//int형을 반환하는 함수 initialize(int **a) 정의
int freeArray(int *a);//int형 함수 freeArray(int *a) 정의
void printArray(int *a);//void형 함수 printArray(int *a) 정의

int selectionSort(int *a);//int형 함수 selectionSort(int *a) 정의
int insertionSort(int *a);//int형 함수 insertionSort(int *a) 정의
int bubbleSort(int *a);//int형 함수 bubbleSort(int *a) 정의
int shellSort(int *a);//int형 함수 shellSort(int *a) 정의
/* recursive function으로 구현 */
int quickSort(int *a, int n);//int형 함수 quickSort(int *a, int n) 정의


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);//int형 함수 hashCode(int key) 정의

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);//int형 함수 hashing(int *a, int **ht) 정의

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);//int형 함수 search(int *ht, int key) 정의


int main()
{
	char command;        //char형 변수 command 선언
	int *array = NULL;   //int형 포인터 변수 *array 선언, NULL로 초기화
	int *hashtable = NULL; //int형 포인터 변수 *hashtable 선언, NULL로 초기화
	int key = -1;         //int형 변수 key 선언 후 -1로 초기화
	int index = -1;       //int형 변수 index 선언 후 -1로 초기화

	srand(time(NULL));   //난수 생성

	printf("[----- [Kimahhyeon] [2022041010] -----]\n");

	do{
		printf("--------------------------------------------------------------- \n"); //---------------------------------------------------------------- 출력
		printf("                        Sorting & Hashing                       \n"); //                        Sorting & Hashing                        출력
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
		printf(" Initialize       = z           Quit             = q\n"); // Initialize       = z           Quit             = q 출력
		printf(" Selection Sort   = s           Insertion Sort   = i\n"); // Selection Sort   = s           Insertion Sort   = i 출력
		printf(" Bubble Sort      = b           Shell Sort       = l\n"); // Bubble Sort      = b           Shell Sort       = l 출력
		printf(" Quick Sort       = k           Print Array      = p\n"); // Quick Sort       = k           Print Array      = p 출력
		printf(" Hashing          = h           Search(for Hash) = e\n"); // Hashing          = h           Search(for Hash) = e 출력
		printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력

		printf("Command = "); //Command =  출력
		scanf(" %c", &command); //command 값을 scanf로 입력받음.

		switch(command) { //제어식이 command
		case 'z': case 'Z': //command가 'z'이거나 'Z'일 경우
			initialize(&array);//initialize(&array) 함수 호출
			break;          //break문
		case 'q': case 'Q': //command가 'q'이거나 'Q'일 경우
			freeArray(array);//freeArray(array) 함수 호출
			break;          //break문
		case 's': case 'S': //command가 's'이거나 'S'일 경우
			selectionSort(array);//selectionSort(array) 함수 호출
			break;          //break문
		case 'i': case 'I': //command가 'i'이거나 'I'일 경우
			insertionSort(array);//insertionSort(array) 함수 호출
			break;          //break문
		case 'b': case 'B': //command가 'b'이거나 'B'일 경우
			bubbleSort(array);//bubbleSort(array) 함수 호출
			break;          //break문
		case 'l': case 'L': //command가 'l'이거나 'L'일 경우
			shellSort(array);//shellSort(array) 함수 호출
			break;          //break문
		case 'k': case 'K': //command가 'k'이거나 'K'일 경우
			printf("Quick Sort: \n");                                                    //Quick Sort:  출력
			printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력
			printArray(array);                                                           //printArray(array) 함수 호출
			quickSort(array, MAX_ARRAY_SIZE);                                            //quickSort(array, MAX_ARRAY_SIZE) 함수 호출
			printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력
			printArray(array);                                                           //printArray(array) 함수 호출

			break; //break문

		case 'h': case 'H': //command가 'k'이거나 'K'일 경우
			printf("Hashing: \n");                                                      //Hashing:  출력
			printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력
			printArray(array);//printArray(array) 함수 호출
			hashing(array, &hashtable);//hashing(array, &hashtable) 함수 호출
			printArray(hashtable);//printArray(hashtable) 함수 호출
			break; //break문

		case 'e': case 'E': //command가 'k'이거나 'K'일 경우
			printf("Your Key = ");//Your Key =  출력
			scanf("%d", &key);    //key 값을 scanf로 입력받음.
			printArray(hashtable);//printArray(hashtable) 함수 호출
			index = search(hashtable, key);//index에 search(hashtable, key) 값 대입
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);//key = %d, index = %d,  hashtable[%d] = 출력
			break; //break문

		case 'p': case 'P': //command가 'k'이거나 'K'일 경우
			printArray(array);
			break;
		default: //위의 경우가 모두 아닐 경우
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //       >>>>>   Concentration!!   <<<<<      출력
			break; //break문
		}

	}while(command != 'q' && command != 'Q'); //command가 'q'가 아니고 'Q'가 아니면

	return 1; //1 값 반환
}

int initialize(int** a)
{
	int *temp = NULL; //포인터 변수 *temp 선언, NULL로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {  //*a가 NULL일 경우
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //temp에 동적할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else            //*a가 NULL이 아니면
		temp = *a;    //temp에 *a 값 대입

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
		temp[i] = rand() % MAX_ARRAY_SIZE;  //배열 temp[i]에 랜덤값(MAX_ARRAY_SIZE로 나눈 나머지값) 대입

	return 0; //0 값 반환
}

int freeArray(int *a)
{
	if(a != NULL) //a가 NULL이 아니면
		free(a);//a 메모리 주소 해제
	return 0;//0 값 반환
}

void printArray(int *a)
{
	if (a == NULL) { //a가 NULL이면
		printf("nothing to print.\n"); //nothing to print. 출력
		return; //0 값 반환
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
		printf("a[%02d] ", i); //a[%02d] 출력
	printf("\n");              //줄바꿈
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
		printf("%5d ", a[i]);  //a[i] 출력
	printf("\n");         //줄바꿈
}


int selectionSort(int *a)
{
	int min;     //int형 변수 min 선언
	int minindex;//int형 변수 minindex 선언
	int i, j;   //int형 변수 i, j 선언

	printf("Selection Sort: \n");                                                //Selection Sort:  출력
	printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력

	printArray(a); //printArray(a) 함수 호출

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
	{
		minindex = i; //minindex에 i 값 대입
		min = a[i]; //min에 a[i] 값 대입
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //j를 i+1로 초기화, MAX_ARRAY_SIZE까지 반복문 실행
		{
			if (min > a[j]) //min이 a[j]보다 크다면
			{
				min = a[j]; //min에 a[j] 값 대입
				minindex = j;//minindex에 j 값 대입
			}
		}
		a[minindex] = a[i]; //a[minindex]에 a[i] 값 대입
		a[i] = min;//a[i]에 min 값 대입
	}

	printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력
	printArray(a); //printArray(a) 함수 호출
	return 0; //0 값 반환
}

int insertionSort(int *a)
{
	int i, j, t; //int형 변수 i, j, t 선언

	printf("Insertion Sort: \n");                                               //Insertion Sort:  출력
	printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력

	printArray(a); //printArray(a) 함수 호출

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//i=1부터 MAX_ARRAY_SIZE까지 반복문 실행
	{
		t = a[i]; //t에 a[i] 값 대입
		j = i;    //j에 i 값 대입
		while (a[j-1] > t && j > 0) //a[j-1]가 t보다 크고 j가 0보다 크면
		{
			a[j] = a[j-1]; //a[j]에 a[j-1] 대입
			j--; //j 감소연산자
		}
		a[j] = t;//a[j]에 t 값 대입
	}

	printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
	printArray(a);//printArray(a) 함수 호출

	return 0; //0 값 대입
}

int bubbleSort(int *a)
{
	int i, j, t; //int형 변수 i, j, t 선언

	printf("Bubble Sort: \n");                                                  //Bubble Sort:  출력
	printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력

	printArray(a); //printArray(a) 함수 호출

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//j=0부터 MAX_ARRAY_SIZE까지 반복문 실행
		{
			if (a[j-1] > a[j]) //a[j-1]가 a[j]보다 크다면
			{
				t = a[j-1];   //t에 a[j-1] 값 대입
				a[j-1] = a[j];//a[j-1]에 a[j] 값 대입
				a[j] = t; //a[j]에 t 값 대입
			}
		}
	}

	printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
	printArray(a); //printArray(a) 함수 호출

	return 0; //0 값 반환
}

int shellSort(int *a)
{
	int i, j, k, h, v; //int형 변수 i, j, t, h, v 선언

	printf("Shell Sort: \n");//Shell Sort:  출력
	printf("----------------------------------------------------------------\n");//---------------------------------------------------------------- 출력

	printArray(a);//printArray(a) 함수 호출

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//h를 MAX_ARRAY_SIZE/2로 초기화, h가 0보다 크면 반복문 실행, h=h/2
	{
		for (i = 0; i < h; i++) //i를 0으로 초기화, i가 h보다 작으면 반복문 실행
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //j를 i+h로 초기화, MAX_ARRAY_SIZE까지 반복문 실행, j=j+h
			{
				v = a[j]; //v에 a[j] 값 대입
				k = j;//k에 j 값 대입
				while (k > h-1 && a[k-h] > v)//k가 h-1보다 크고 a[k-h]가 v보다 크다면
				{
					a[k] = a[k-h];//a[k]에 a[k-h] 값 대입
					k -= h;//k=k-h
				}
				a[k] = v; //a[k]에 v 값 대입
			}
		}
	}
	printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
	printArray(a); //printArray(a) 함수 호출

	return 0;//0 값 반환
}

int quickSort(int *a, int n)
{
	int v, t; //int형 변수 v, t 선언
	int i, j;//int형 변수 i, j 선언

	if (n > 1) //n이 1보다 크면
	{
		v = a[n-1]; //v에 a[n-1] 값 대입
		i = -1;//i를 -1로 초기화
		j = n - 1;//j에 n - 1 값 대입

		while(1) //반복문 무한
		{
			while(a[++i] < v); //a[++i]가 v보다 작다면
			while(a[--j] > v);//a[--j]가 v보다 크다면

			if (i >= j) break;//i가 j보다 크거나 같다면, break문
			t = a[i]; //t에 a[i] 값 대입
			a[i] = a[j];//a[i]에 a[j] 값 대입
			a[j] = t;//a[j]에 t 값 대입
		}
		t = a[i]; //t에 a[i] 값 대입
		a[i] = a[n-1];//a[i]에 a[n-1] 값 대입
		a[n-1] = t;//a[n-1]에 t 값 대입

		quickSort(a, i);//quickSort(a, i) 함수 호출
		quickSort(a+i+1, n-i-1);//quickSort(a+i+1, n-i-1) 함수 호출
	}


	return 0; //0 값 반환
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //key를 MAX_HASH_TABLE_SIZE로 나눈 나머지 값 반환
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //int형 포인터 변수 *hashtable선언, NULL로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { //*ht가 NULL이면
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //hashtable 동적할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else { //*ht가 NULL이 아니면
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
		hashtable[i] = -1; //hashtable[i]에 -1 값 대입

	int key = -1; //int형 변수 key 선언, -1로 초기화
	int hashcode = -1;//int형 변수 hashcode 선언, -1로 초기화
	int index = -1; //int형 변수 index 선언, -1로 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//i=0부터 MAX_ARRAY_SIZE까지 반복문 실행
	{
		key = a[i]; //key에 a[i] 값 대입
		hashcode = hashCode(key);//hashcode에 hashCode(key) 값 대입

		if (hashtable[hashcode] == -1)//hashtable[hashcode]가 -1이면
		{
			hashtable[hashcode] = key;//hashtable[hashcode]에 key 값 대입
		} else 	{ //hashtable[hashcode]가 -1이 아니면

			index = hashcode;   //index에 hashcode 값 대입

			while(hashtable[index] != -1)//hashtable[index]가 -1이 아니면
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//index에 (++index)를 MAX_HASH_TABLE_SIZE로 나눈 나머지값 대입
			}
			hashtable[index] = key;//hashtable[index]에 key 값 대입
		}
	}

	return 0;//0 값 반환
}

int search(int *ht, int key)
{
	int index = hashCode(key); //int형 변수 index 선언, hashCode(key) 값 대입

	if(ht[index] == key) //ht[index]가 key라면
		return index;   //index 값 반환

	while(ht[++index] != key)//ht[++index]가 key 값이 아니라면
	{
		index = index % MAX_HASH_TABLE_SIZE;//index에 index를 MAX_HASH_TABLE_SIZE로 나눈 나머지 값 대입
	}
	return index;//index 값 반환
}



