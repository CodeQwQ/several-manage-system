#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book{
    int id;         //ͼ����
    char name[25];  //ͼ������
    int count;      //ͼ������
}Book;
typedef struct Reader{
    int id;         //���߱��
    char name[20];  //��������
}Reader;
typedef struct Admin{
	char name[20];  //����Ա���� 
	int num;   	    //����Ա���
}Admin;  

int id; //����ʹ��ϵͳ���û�������Ա����id
char rname[20];
Book books[110];                  //ͼ��
Reader readers[110];			  //����
Admin admins[10];                 //����Ա
char borrowerList[110][100];      //ÿ��������Щ���ڽ� 
char borrowedBookList[110][100];  //ÿ���˽�����Щ��

//��������load�������ǽ��ļ��д洢�����ݼ��ص��ڴ���
void loadReaders() {
    FILE *fp1 = fopen("readers.txt", "r");
	FILE *fp2 = fopen("borrowedBookList.txt", "r");
	if(fp1 == NULL || fp2 == NULL){
		printf("ERROR\n");
		return;
	}
	char t[100];
	int i = 0;
	while(fgets(t, 100, fp1) != NULL){  //��ȡ������Ϣ��name������Ϣ��������t��
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(readers[i].name, t); //����
		readers[i].id = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
	while(fgets(t, 100, fp2) != NULL){  //��ȡ����Щ���ڽ裬����Ϣ��������t��
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(borrowedBookList[i], t); //����
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
	fclose(fp1);
	fclose(fp2);
}

void loadAdmins() {
    FILE *fp1 = fopen("admin.txt", "r");
	if(fp1 == NULL){
		printf("ERROR\n");
		return;
	}
	char t[100];
	int i = 0;
	while(fgets(t, 100, fp1) != NULL){  //��ȡ����Ա����������t��
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(admins[i].name, t);	//t���Ƹ�admins[i].name
		admins[i].num = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
	fclose(fp1);
}

void loadBooks() {	//����ͼ����Ϣ
    FILE *fp1 = fopen("books.txt", "r");
	FILE *fp2 = fopen("booksLeft.txt", "r");
	FILE *fp3 = fopen("borrowerList.txt", "r");
	if(fp1 == NULL || fp2 == NULL || fp3 == NULL){
		printf("ERROR\n");
		return;
	}
	char t[100];
	int i = 0;
    //��ȡͼ�����֣��趨id
	while(fgets(t, 100, fp1) != NULL){
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(books[i].name, t);
		books[i].id = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
    //��ȡ����ͼ��Ŀ��
	while(fgets(t, 100, fp2) != NULL){
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		if(!strcmp(t, "end")){
			books[i].count = -1;    //��ʾ�����ڸ�ͼ��
			break;
		}
		int n = atoi(t);    //���ַ���tת��Ϊ����n
		books[i].count = n; 
		i++;
	}
	i = 0;
    //��ȡ�ڽ�ͼ������
	while(fgets(t, 100, fp3) != NULL){
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(borrowerList[i], t);
		i++;
		if(!strcmp(t, "end"))	break;
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

//���µ�store��������Ϊ�˽��ڴ��е����ݴ洢�������е��ļ��У��־û��洢
void storeBorrowerList(){
	FILE *fw = fopen("borrowerList.txt", "w");
	if(fw == NULL){
		printf("ERRiOR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(borrowerList[i], "no"))	fputc('\n', fw); //�����no��˵��û���˽��i����
		else {
			fputs(borrowerList[i], fw);
			fputc('\n', fw);
		}
		if(!strcmp(borrowerList[i], "end"))	break; //����������־
	}
	fclose(fw);
}

void storeBookLeft(){   //�洢ͼ��Ŀ��
	FILE *fw = fopen("booksLeft.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		char x[10];
		if(books[i].count == -1){
			fputs("end", fw);
			break;
		}
		itoa(books[i].count, x, 10);    //������books[i].countת��Ϊ�ַ���x
		fputs(x, fw);
		fputc('\n', fw);
	}
	fclose(fw);
}

void storeBooks(){  //�洢ͼ������
	FILE *fw = fopen("books.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		fclose(fw);
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, "end")){
			fputs("end", fw);   //���ý�����־
			fclose(fw);
			return;
		}
		fputs(books[i].name, fw);
		fputc('\n', fw);
	}
}

void storeReaders(){    //�洢��������
	FILE *fw = fopen("readers.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(readers[i].name, "end")){
			fputs("end", fw);	//readers[i].name��ȡ���
			fclose(fw);
			return;
		}
		fputs(readers[i].name, fw);
		fputc('\n', fw);
	}	
}

void storeAdministrators(){ //�洢����Ա����
	FILE *fw = fopen("admin.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(admins[i].name, "end")){
			fputs("end", fw);	//admins[i].name��ȡ���
			fclose(fw);
			return;
		}
		fputs(admins[i].name, fw);
		fputc('\n', fw);
	}
}

void storeBorrowedBookList(){   //�洢ͼ���ڽ�����
	FILE *fw = fopen("borrowedBookList.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int k;
	for(k = 0; k < 100; k++){
		fputs(borrowedBookList[k], fw);
		fputc('\n', fw);
		if(!strcmp(borrowedBookList[k], "end"))	break;
	}
	fclose(fw);
}

void modifyBook() {
	char bname[20];
    printf("����ͼ�����֣�\n");
    scanf("%s", bname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(bname, books[i].name)){	//�ҵ�������Ӧ��ͼ��
			flag = 1;
			printf("�������ּ���ȷ���޸�ͼ�����һ��Ϣ��1.���� 2.���\n");
			int opt;
			scanf("%d",&opt);
			if (opt == 1) {
				printf("������������\n");
				scanf("%s", bname);
				strcpy(books[i].name, bname);
				printf("�ɹ�\n");
				storeBooks();
			} else if (opt == 2) {
				printf("������º�Ŀ�棺\n");
				int cnt;
				scanf("%d", &cnt);
				books[i].count = cnt;
				storeBookLeft();
			}
			break;
		}
		if(!strcmp(books[i].name, "end")) break;
	}
}

void addBook() {
    char bname[20];
    printf("����ͼ�����֣�\n");
    scanf("%s", bname);
    int i, flag = 0;
    //����books���飬�ҵ�endԪ�أ���ͼ����ӵ���λ�ã�����endԪ�غ���һλ
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, "end")){
			strcpy(books[i].name, bname);
			books[i].id = i;
			books[i].count = 3; //ͼ�����ʼ��Ϊ3
			strcpy(books[i+1].name, "end");
			strcpy(borrowerList[i], "no");  //��ʱ��ͼ����ʱû�˽赽
			strcpy(borrowerList[i+1], "end");   //��β��־�Ƶ���i+1��λ��
			books[i+1].count = -1;  //��i+1���鲻����
			flag = 1;   //��־���ͼ��ɹ�
			break;
		}
	}
    //����3��store()���������ļ��е���Ϣ���־û��洢
	storeBookLeft();
	storeBooks();
	storeBorrowerList();
	if (flag) 
        printf("�ɹ�\n");
	else
        printf("ʧ��\n");
}

int findNotBank(char* s) {
	int i;
	for (i = 0; i < strlen(s); i++) {
		if (s[i] != ' ' && s[i] != '\0') {
			break;
		}
	}
	return i;
}

void deleteBook() {
    char bname[20];
    printf("����ͼ������:\n");
    scanf("%s", bname);
    int i, flag = 0;
    //����Ѱ�Ҹ�ͼ�鲢ɾ��
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			if (!strcmp(borrowerList[i],"no")) {
				strcpy(borrowerList[i], "");
			}
			int k = findNotBank(borrowerList[i]);
			if (k < strlen(borrowerList[i])) {	//��ͼ���ж����ڽ�	
				printf("ʧ��\n");
				return;
			}
			strcpy(books[i].name, "null");  //��Ϊnull��Ϊɾ��
			books[i].count = 0;
			flag = 1;
			break;
		}
	}
	storeBookLeft();
	storeBooks();
	if(flag)
        printf("�ɹ�\n");
	else
        printf("ʧ��\n");
}


void queryBook() {
	char bname[20];
	printf("����ͼ�����֣�\n");
	scanf("%s", bname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(bname, books[i].name)){ 	//�ҵ�������Ӧ��ͼ��
			flag = 1;
			printf("����: %s\n", books[i].name);
			printf("id: %d\n", books[i].id);
			printf("���: %d\n", books[i].count);
			printf("������: %s\n", borrowerList[i]);
		}
		if(!strcmp(books[i].name, "end"))	break;
	}
	if (!flag) {
		printf("δ�ҵ���ͼ��\n");
	}
}

void addReader() {
	char rname[20], reroot[20];
	printf("�������������\n");
	scanf("%s", rname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(readers[i].name, "end")){
			strcpy(readers[i].name, rname);
			readers[i].id = i;
			strcpy(readers[i+1].name, "end");
			flag = 1;
			break;
		}
	}
	storeReaders();	//�����ļ��е�����
	if(flag)	
		printf("��ӳɹ�\n");
	else	
		printf("���ʧ��\n");
}


void deleteReader() {
	char rname[20];
	printf("�������������\n");
	scanf("%s", rname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(readers[i].name, rname)){
			//strcmp()���ط�0��˵�����߻��������飬ֻҪȫ�����飬�ſ���ɾ���ö�����Ϣ
			if(strlen(borrowedBookList[i]) != 0){	
				printf("ʧ��\n");
				return;
			}
			strcpy(readers[i].name, "null");
			flag = 1;
			break;
		}
	}
	storeReaders();
	if(flag)
		printf("ɾ���ɹ�\n");
	else
		printf("ɾ��ʧ��\n");
}

void modifyReader() {
	char rname[20];
	printf("�������������\n");
	scanf("%s", rname);
	int i;
	for(i = 0; i < 100; i++){		
		if(!strcmp(rname, readers[i].name)){
			printf("�޸ĺ�Ķ���������");
			scanf("%s",&rname);
			strcpy(readers[i].name, rname);
			storeReaders();
		}
		if(!strcmp(readers[i].name, "end")) {
			break;
		}
	}
}

void queryReader() {
	char rname[20];
	printf("�������������\n");
	scanf("%s", rname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){		
		if(!strcmp(rname, readers[i].name)){
			printf("����: %s\n", readers[i].name);
			printf("id: %d\n", readers[i].id);
			printf("�ڽ�ͼ��: %s\n", borrowedBookList[i]);
			flag = 1;
		}
		if(!strcmp(readers[i].name, "end")) {
			break;
		}
	}
	if (!flag) {
		printf("δ�ҵ��ö���\n");
	}
}

void borrowBook(){
	char bname[20];
	printf("��������:\n");
	scanf("%s", bname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			if(books[i].count == 0){
				printf("ͼ����ʱû�п��\n");
				return;
			}else{
				books[i].count--;
				if(!strcmp(borrowerList[i], "end")){
					strcpy(borrowerList[i], rname);	//���end���ǵ�������ranme�ĳ���С��3
					strcpy(borrowerList[i+1], "end");
				}else{
					strcat(borrowerList[i], " ");
					strcat(borrowerList[i], rname);
				}
				int j;
				for(j = 0; j < 100; j++){
					if(!strcmp(readers[j].name, rname)){
						if(!strcmp(borrowedBookList[j], "end")){
							//bname��"end"���ǵ�
							strcpy(borrowedBookList[j], bname);
							strcpy(borrowedBookList[j+1], "end");
						}else{
							strcat(borrowedBookList[j], " ");
							strcat(borrowedBookList[j], bname);
						}
					}
				}
				flag = 1;
				break;
			}
		}
	}
	//�����ļ�����
	storeBorrowerList();
	storeBorrowedBookList();
	storeBookLeft();
	if(flag)
		printf("�ɹ�\n");
	else
		printf("ʧ��\n");
	loadBooks();
	loadReaders();
}

void returnBook() {
	char bname[20];
	printf("��������:\n");
	scanf("%s", bname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			books[i].count++;
			char *des1 = strstr(borrowerList[i], rname), *des2 = strstr(borrowerList[i], rname);
			char p[100];
			des1 += strlen(rname);	//desc1��desc2�ַ������˻����˵�����
			if(des1 != NULL){
				strcpy(p, des1);
				strcpy(des2, p);	//��rname��borrowerList[i]��ɾ��
			}
			int j;
			for(j = 0; j < 100; j++){
				if(!strcmp(readers[j].name, rname)){
					char *des3 = strstr(borrowedBookList[j], bname), *des4 = strstr(borrowedBookList[j], bname);
					char q[100];
					des3 += strlen(bname);	//desc3��desc4���˱������������
					if(des3 != NULL){
						strcpy(q, des3);
						strcpy(des4, q);	//��bname��borrowedBookList[j]ɾ��
					}
				}
			}
			flag = 1;
			break;
		}
	}
	storeBorrowerList();
	storeBorrowedBookList();
	storeBookLeft();
	if(flag)	printf("�ɹ�\n");
	else	printf("ʧ��\n");
	loadBooks();
	loadReaders();
}

void queryBookById() {
	printf("%s\n", borrowedBookList[id]);
}

//�����Ƿ����username��Ӧ���û�
int existUser(char* username) {
	int flag = 0;
	int i = 0; 
	for (; i < 100; i++) {
		if (!strcmp(readers[i].name, username)){
			id = i;
			strcpy(rname, readers[i].name);
			flag = 1;
			break;
		}
		if(!strcmp(readers[i].name, "end")){
			break;
		}
	}
	return flag;
}

//�����Ƿ����admin��Ӧ�Ĺ���Ա
int existAdmin(char* admin) {
	int flag = 0;
	int i = 0;
	for (; i < 100; i++) {
		if (!strcmp(admins[i].name, admin)){
			flag = 1;
			break;
		}
		if(!strcmp(admins[i].name, "end")){
			break;
		}
	}
	return flag;
}

//����Ŀ�ʼ����
void start(char sign, char* username) {
    int opt = 1;
    if (sign == 'a') {
        if (!existAdmin(username)) {
			printf("�û������Ϸ�\n");
            return;
        }
        while (opt != 0) {
            printf("\n--------ͼ��ݹ���ϵͳ(admin)-----------\n");
            printf("| �����ѡ�����²���(������Ӧ���ּ�):         |\n");
            printf("| 0.�˳�����                                  |\n");
            printf("| 1.¼��ͼ����Ϣ                              |\n");
            printf("| 2.ɾ��ͼ����Ϣ                              |\n");
            printf("| 3.�޸�ͼ����Ϣ                              |\n");
            printf("| 4.��ѯͼ����Ϣ                              |\n");
            printf("| 5.¼�������Ϣ                              |\n");
            printf("| 6.ɾ��������Ϣ                              |\n");
            printf("| 7.�޸Ķ�����Ϣ                              |\n");
            printf("| 8.��ѯ������Ϣ                              |\n");
            printf("----------------------------------------------\n");
            scanf("%d",&opt);
            switch (opt) {
                case 0:
                    return;
                case 1:
                    addBook();
                    break;
                case 2:
                    deleteBook();
                    break;
                case 3:
                    modifyBook();
                    break;
                case 4:
                    queryBook();
                    break;
                case 5:
                    addReader();
                    break;
                case 6:
                    deleteReader();
                    break;
                case 7:
                    modifyReader();
                    break;
                case 8:
                    queryReader();
                    break;
                default:
                    printf("���벻�Ϸ�");
                    break;
            }
        }
    } else {
		if (!existUser(username)) {
			printf("�û������Ϸ�\n");
			return;
		}
        while (opt != 0) {
            printf("\n--------ͼ��ݹ���ϵͳ(reader)------------------\n");
            printf("| �����ѡ�����²���(������Ӧ���ּ�):           |\n");
            printf("| 0.�˳�����                                  |\n");
            printf("| 1.����                                      |\n");
            printf("| 2.����                                      |\n");
            printf("| 3.��ѯͼ��                                  |\n");
			printf("| 4.��ѯ�Լ�����ͼ��                           |\n");
            printf("----------------------------------------------\n");
            scanf("%d",&opt);
            switch (opt) {
                case 0:
                    return;
                case 1:
                    borrowBook();
                    break;
                case 2:
                    returnBook();
                    break;
                case 3:
                    queryBook();
                    break;
				case 4:
					queryBookById();
					break;
                default:
                    printf("���벻�Ϸ�");
                    break;
            }
        }
    }
}

/*
Libsim -a(-u) xxxx
��һ������Ϊ��ִ�г������ƣ��ڶ�������Ϊ�û���ݣ�-a��ʾ����Ա��-u��ʾ���ߣ�����������Ϊ�û���
*/
int main(int argc, char *argv[]) {
	loadAdmins();
	loadBooks();
	loadReaders();
    if (!strcmp(argv[1], "-a")) {
        start('a', argv[2]);
    } else if (!strcmp(argv[1], "-u")) {
		start('u', argv[2]);
    } else {
        printf("����������Ϸ�\n");
    }
	printf("�ټ�\n");
}
