#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int Data;

typedef struct _Node {
    Data d;
    struct _Node* prev;
    struct _Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int numOfData;
} Deque;

void DequeInit(Deque* DQ) {
    DQ->head = malloc(sizeof(Node));
    DQ->tail = malloc(sizeof(Node));

    DQ->head->prev = NULL;
    DQ->tail->next = NULL;

    DQ->head->next = DQ->tail;
    DQ->tail->prev = DQ->head;

    DQ->numOfData = 0;
}

unsigned int DCount(const Deque* DQ) {
    return DQ->numOfData;
}

bool DIsEmpty(const Deque* DQ) {
    return !DCount(DQ);
}

void DPushFront(Deque* DQ, const Data d) {
    Node* newNode = malloc(sizeof(Node));

    newNode->d = d;

    newNode->next = DQ->head->next;
    newNode->next->prev = newNode;

    newNode->prev = DQ->head;
    DQ->head->next = newNode;

    DQ->numOfData++;
}

void DPushRear(Deque* DQ, const Data d) {
    Node* newNode = malloc(sizeof(Node));

    newNode->d = d;

    newNode->prev = DQ->tail->prev;
    newNode->prev->next = newNode;

    newNode->next = DQ->tail;
    DQ->tail->prev = newNode;

    DQ->numOfData++;
}

Data DPeekFront(const Deque* DQ) {
    if (DIsEmpty(DQ) == false) {
        return DQ->head->next->d;
    }
    return -1;
}

Data DPeekRear(const Deque* DQ) {
    if (DIsEmpty(DQ) == false) {
        return DQ->tail->prev->d;
    }
    return -1;
}

Data DPopFront(Deque* DQ) {
    if (DIsEmpty(DQ) == false) {
        Data ret = DPeekFront(DQ);

        Node* cur = DQ->head->next;
        Node* left = cur->prev;
        Node* right = cur->next;

        left->next = right;
        right->prev = left;

        free(cur);

        DQ->numOfData--;

        return ret;
    }
    return -1;
}

Data DPopRear(Deque* DQ) {
    if (DIsEmpty(DQ) == false) {
        Data ret = DPeekRear(DQ);

        Node* cur = DQ->tail->prev;
        Node* left = cur->prev;
        Node* right = cur->next;

        left->next = right;
        right->prev = left;

        free(cur);

        DQ->numOfData--;

        return ret;
    }
    return -1;
}

// for debug
void DShow(Deque* DQ) {
    if (DIsEmpty(DQ) == false) {
        int nod = DQ->numOfData;
        Node* cur;

        cur = DQ->head->next;
        printf("(head) ");
        for (int i = 0; i < nod; i++) {
            printf("%d ", cur->d);
            cur = cur->next;
        }
        printf("(tail)\n");

        cur = DQ->tail->prev;
        printf("(tail) ");
        for (int i = 0; i < nod; i++) {
            printf("%d ", cur->d);
            cur = cur->prev;
        }
        printf("(head)\n");
    }
    else {
        printf("nothing to show!\n");
    }
}


int main(void) {
    Deque* DQ1 = (Deque*)malloc(sizeof(Deque));
    DequeInit(DQ1);

    int n; // 명령 갯수
    scanf("%d", &n);
    getchar();

    int ans[n];
    int ansidx = 0;

    int sel;
    for (int i = 0; i < n; i++) {
        sel = -1;
        scanf("%d", &sel);
        getchar();

        switch (sel) {
            case 1: {
                // push front
                int x;
                scanf("%d", &x);
                getchar();

                DPushFront(DQ1, x);
                break;
            }
            case 2: {
                // push rear
                int x;
                scanf("%d", &x);
                getchar();

                DPushRear(DQ1, x);
                break;
            }
            case 3: {
                // pop front
                ans[ansidx++] = DPopFront(DQ1);
                break;
            }
            case 4: {
                // pop rear
                ans[ansidx++] = DPopRear(DQ1);
                break;
            }
            case 5: {
                // count
                ans[ansidx++] = DCount(DQ1);
                break;
            }
            case 6: {
                // isempty
                ans[ansidx++] = DIsEmpty(DQ1);
                break;
            }
            case 7: {
                // peek front
                ans[ansidx++] = DPeekFront(DQ1);
                break;
            }
            case 8: {
                // peek rear
                ans[ansidx++] = DPeekRear(DQ1);
                break;
            }
            default: {
                // printf("selection error!\n");
                break;
            }
        }
    }

    for (int i = 0; i < ansidx; i++) {
        printf("%d\n", ans[i]);
    }

    free(DQ1);
}
