#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct PriorityQueue {
	int values[MAX];
	int capacity;
	int front;
	int rear;
	int numberOfElems;
} PriorityQueue;

void Insert(PriorityQueue *pq, int value)
{
	//check if it is full
	if (pq->numberOfElems == pq->capacity)
	{
		printf("PQ full - no insertions!\n");
		return;
	}

	//if PQ is empty
	if (pq->numberOfElems == 0)
	{
		pq->front = 0;
		pq->rear = (pq->rear + 1) % pq->capacity;
		pq->values[pq->rear] = value;
		pq->numberOfElems++;
		return;
	}

	// if it is the largest elem (lowest priority => add in the back)
	if (pq->values[pq->rear] != -1 && pq->values[pq->rear] <= value)
	{
		pq->rear = (pq->rear + 1) % pq->capacity;
		pq->values[pq->rear] = value;
		pq->numberOfElems++;
		return;
	}

	// If it requires moving elems in the array
	int x = 0;

	int startIndex = pq->front;
	int endIndex = pq->rear;

	if (pq->front > pq->rear)
	{
		endIndex = endIndex + pq->capacity;
	}

	for (int i = startIndex; i <= endIndex && x < pq->numberOfElems;)
	{
		int index = i % pq->capacity;
		if (value < pq->values[index])
		{
			// pomeri sve elemente niza za jedno mesto unazad od reara do i-tog
			int lastElemIndex = pq->rear + 1;
			if (pq->front > pq->rear)
			{
				lastElemIndex = lastElemIndex + pq->capacity;
			}
			pq->rear = (pq->rear + 1) % pq->capacity;

			for (int j = lastElemIndex; j > index;)
			{
				int previous = (j - 1) % pq->capacity;

				int newElemIndex = j % pq->capacity;
				pq->values[newElemIndex] = pq->values[previous];
				j--;
			}

			pq->values[index] = value;
			pq->numberOfElems++;
			break;
		}
		i = i + 1;
		x++;
	}

}

int Remove(PriorityQueue *pq)
{
	//check if it is empty
	if (pq->numberOfElems == 0)
	{
		printf("PQ empty - no deletions!\n");
		return -1;
	}

	int value = pq->values[pq->front];
	pq->values[pq->front] = -1;
	pq->front = (pq->front + 1) % pq->capacity;
	pq->numberOfElems--;
	return value;
}

int GetMaxCapacity(PriorityQueue *pq)
{
	return pq->capacity;
}

int GetNumberOfElems(PriorityQueue *pq)
{
	return pq->numberOfElems;
}

int PeakFirstElem(PriorityQueue *pq)
{
	if (pq->numberOfElems == 0)
	{
		printf("PQ empty - no values!\n");
		return -1;
	}

	return pq->values[pq->front];
}

void main() {
	PriorityQueue *pq = NULL;
	int maxCapacity, choice, number;

	while (1) {

		printf("\n1. Inicijalizacija reda.\n"
			"2. Ucitavanje elemenata.\n"
			"3. Prikazivanje prvog elementa.\n"
			"4. Brisanje elemenata.\n"
			"5. Maksimalni kapacitet.\n"
			"6. Broj elemenata.\n"
			"0. Izlaz.\n"
			"Vas izbor?\n");
		scanf("%d", &choice);

		switch (choice) {

		case 1:
			printf("Unesite maksimalni kapacitet niza\n");
			scanf("%d,", &maxCapacity);

			if (maxCapacity > MAX)
			{
				maxCapacity = MAX;
			}
			// Initialization of PQ, ascending (0 ,1, 2, 3 ..)
			pq = malloc(sizeof(PriorityQueue));
			pq->front = -1;
			pq->rear = -1;
			pq->numberOfElems = 0;
			pq->capacity = maxCapacity;
			break;

			// Add item into PQ
		case 2:
			printf("Unesite element u red.\n");
			scanf("%d", &number);
			Insert(pq, number);
			break;

		case 3:
			int val = PeakFirstElem(pq);
			printf("PQ peaked value %d\n", val);
			break;

		case 4:
			val = Remove(pq);
			printf("PQ removed value %d\n", val);
			break;

		case 5:
			int cap = GetMaxCapacity(pq);
			printf("PQ max capacity %d\n", cap);
			break;

		case 6:
			int numbOfElem = GetNumberOfElems(pq);
			printf("PQ number of elems %d\n", numbOfElem);
			break;

		case 0:
			printf("Uspesno ste izasli iz programa.\n");
			exit(1);

			free(pq);
		}
	}
}