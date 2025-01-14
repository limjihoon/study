#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int Q5 (void){
	int a = 5000;

	printf("%d->%d\n%x->%x\n", a, a&0xFFFFF000, a, a& ~((1<<12) - 1));
	return 0;
}


struct Data{
	int data;
	struct Data* link;
};
void stack_add(struct Data **stackptr, int data){
	struct Data* t;
	t=(*stackptr);

	(*stackptr) = (struct Data*)malloc(sizeof(struct Data));
	(*stackptr)->data = data;
	(*stackptr)->link=t;
}
int Q6(void){
	struct Data *stackptr = NULL;

	printf("Q6) ");
	stack_add(&stackptr, 55);

	printf("%d\n", stackptr->data);
	return 0;
}



int Q7(void){
	char buf[100];
	int i, cnt =0;

	printf("Q7)아스키코드값이 홀수인 문자갯수를 출력할 문자 : ");
	gets(buf);
	fflush(stdin);

	for(i=0;i<strlen(buf) || buf[i]!='\0'; i++){
		if(buf[i]&1)
			cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}


int Q8(void){
	char a;

	printf("Q8)대문자 <-> 소문자 변환 할 문자 : ");
	scanf("%c", &a);
	fflush(stdin);

	printf("%c\n", a^0x20);
	return 0;
}

int matrix_init(int (*data)[2], int num){
	int i, j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			data[i][j]=num;
}
int matrix_add(int (*dst)[2], int (*data1)[2], int (*data2)[2]){
	int i, j;
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
			dst[i][j]=data1[i][j]+data2[i][j];
}
int matrix_mul(int (*dst)[2], int (*data1)[2], int (*data2)[2]){
	int i, j, k;
	matrix_init(dst, 0);
	for(i=0;i<2;i++)
		for(j=0;j<2;j++){
			for(k=0;k<2;k++)
				dst[i][j]+=data1[i][k]*data2[k][j];
		}
}
int Q91011(void){
	int data[2][2];
	int data1[2][2];
	int data2[2][2];
	int i,j;

	matrix_init(data,0);
	matrix_init(data1,1);
	matrix_init(data2,2);
	
	matrix_add(data, data1, data2);
	matrix_mul(data, data1, data2);
	
	printf("Q91011)\n");
	for(i=0;i<2;i++){
		for(j=0;j<2;j++)
			printf("%d\t", data[i][j]);
		printf("\n");
	}
	return 0;
}


void exchaptr(int** a, int** b){
	int* temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}
int Q15(void){
	int a=1;
	int b=2;
	int *apt=&a, *bpt=&b;
	int **aptt=&apt, **bptt=&bpt;
	
	printf("%d, %d\n", (**aptt), (**bptt));
	exchaptr(aptt, bptt);
	printf("%d, %d\n", (**aptt), (**bptt));

	return 0;
}

int main(void){
	Q5();
//	Q6();
//	Q7();
//	Q8();
//	Q91011();
//	Q15();
}
