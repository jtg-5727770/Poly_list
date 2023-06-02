#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode { // ��� Ÿ��
	int coef;
	int expon;
	struct ListNode* link;
} ListNode;
// ���� ����Ʈ ���
typedef struct ListType { // ����Ʈ ��� Ÿ��
	int size;
	ListNode* head;
	ListNode* tail;
} ListType;
// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// ����Ʈ ��� ���� �Լ�
ListType* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}
// plist�� ���� ����Ʈ�� ����� ����Ű�� ������, coef�� ���, 
// expon�� ����
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp =
		(ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("�޸� �Ҵ� ����");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

void parse_poly(ListType* plist, char* poly)
{
	char* context;
	char* term;
	char* delimiter = "+";
	term = strtok_s(poly, delimiter, &context);
	while (term != NULL) {
		// �� �׸��� �Ľ��Ͽ� ����� ���� ����
		int coef, expon;
		sscanf_s(term, "%dx%d", &coef, &expon);
		insert_last(plist, coef, expon);
		term = strtok_s(NULL, delimiter, &context);
	}
}

// list3 = list1 + list2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;
	while (a && b) {
		if (a->expon == b->expon) { // a�� ���� > b�� ����
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}
		else if (a->expon > b->expon) { // a�� ���� == b�� ����
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}
		else { // a�� ���� < b�� ����
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}
	// a�� b���� �ϳ��� ���� ������ �Ǹ� �����ִ� �׵��� ���
    // ��� ���׽����� ����
	for (; a != NULL; a = a->link)
		insert_last(plist3, a->coef, a->expon);
	for (; b != NULL; b = b->link)
		insert_last(plist3, b->coef, b->expon);
}

void poly_print(ListType* plist)
{
	ListNode* p = plist->head;
	printf("�� ���׽��� ��: ");
	for (; p; p = p->link) {
		printf("%dx^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

int main(void) {
	ListType* list1, * list2, * list3;
	char poly1[100];
	char poly2[100];

	list1 = create();
	list2 = create();
	list3 = create();
	
	printf("ù��° ���׽��� �Է��ϼ���: ");
	scanf_s("%s", poly1, 100);
	parse_poly(list1, poly1);
	

	printf("�ι�° ���׽��� �Է��ϼ���: ");
	scanf_s("%s", poly2, 100);
	parse_poly(list2, poly2);
	
	poly_add(list1, list2, list3);
	poly_print(list3);
	
	free(list1); free(list2); free(list3);
	system("pause");
	return 0;
}