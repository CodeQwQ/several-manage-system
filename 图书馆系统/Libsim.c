#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book{
    int id;         //图书编号
    char name[25];  //图书名称
    int count;      //图书数量
}Book;
typedef struct Reader{
    int id;         //读者编号
    char name[20];  //读者名字
}Reader;
typedef struct Admin{
	char name[20];  //管理员姓名 
	int num;   	    //管理员编号
}Admin;  

int id; //现在使用系统的用户（管理员）的id
char rname[20];
Book books[110];                  //图书
Reader readers[110];			  //读者
Admin admins[10];                 //管理员
char borrowerList[110][100];      //每本书有哪些人在借 
char borrowedBookList[110][100];  //每个人借了哪些书

//以下三个load函数，是将文件中存储的数据加载到内存中
void loadReaders() {
    FILE *fp1 = fopen("readers.txt", "r");
	FILE *fp2 = fopen("borrowedBookList.txt", "r");
	if(fp1 == NULL || fp2 == NULL){
		printf("ERROR\n");
		return;
	}
	char t[100];
	int i = 0;
	while(fgets(t, 100, fp1) != NULL){  //读取读者信息：name，将信息读到数组t中
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(readers[i].name, t); //复制
		readers[i].id = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
	while(fgets(t, 100, fp2) != NULL){  //读取有哪些书在借，将信息读到数组t中
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(borrowedBookList[i], t); //复制
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
	while(fgets(t, 100, fp1) != NULL){  //读取管理员姓名到数组t中
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(admins[i].name, t);	//t复制给admins[i].name
		admins[i].num = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
	fclose(fp1);
}

void loadBooks() {	//加载图书信息
    FILE *fp1 = fopen("books.txt", "r");
	FILE *fp2 = fopen("booksLeft.txt", "r");
	FILE *fp3 = fopen("borrowerList.txt", "r");
	if(fp1 == NULL || fp2 == NULL || fp3 == NULL){
		printf("ERROR\n");
		return;
	}
	char t[100];
	int i = 0;
    //读取图书名字，设定id
	while(fgets(t, 100, fp1) != NULL){
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		strcpy(books[i].name, t);
		books[i].id = i;
		i++;
		if(!strcmp(t, "end"))	break;
	}
	i = 0;
    //读取所有图书的库存
	while(fgets(t, 100, fp2) != NULL){
		if(t[strlen(t)-1] == '\n')	t[strlen(t)-1] = '\0';
		if(!strcmp(t, "end")){
			books[i].count = -1;    //表示不存在该图书
			break;
		}
		int n = atoi(t);    //将字符串t转化为整数n
		books[i].count = n; 
		i++;
	}
	i = 0;
    //读取在借图书名单
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

//以下的store函数都是为了将内存中的数据存储到磁盘中的文件中，持久化存储
void storeBorrowerList(){
	FILE *fw = fopen("borrowerList.txt", "w");
	if(fw == NULL){
		printf("ERRiOR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(borrowerList[i], "no"))	fputc('\n', fw); //如果是no，说明没有人借第i本书
		else {
			fputs(borrowerList[i], fw);
			fputc('\n', fw);
		}
		if(!strcmp(borrowerList[i], "end"))	break; //遇到结束标志
	}
	fclose(fw);
}

void storeBookLeft(){   //存储图书的库存
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
		itoa(books[i].count, x, 10);    //将整数books[i].count转化为字符串x
		fputs(x, fw);
		fputc('\n', fw);
	}
	fclose(fw);
}

void storeBooks(){  //存储图书名字
	FILE *fw = fopen("books.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		fclose(fw);
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, "end")){
			fputs("end", fw);   //设置结束标志
			fclose(fw);
			return;
		}
		fputs(books[i].name, fw);
		fputc('\n', fw);
	}
}

void storeReaders(){    //存储读者姓名
	FILE *fw = fopen("readers.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(readers[i].name, "end")){
			fputs("end", fw);	//readers[i].name读取完毕
			fclose(fw);
			return;
		}
		fputs(readers[i].name, fw);
		fputc('\n', fw);
	}	
}

void storeAdministrators(){ //存储管理员姓名
	FILE *fw = fopen("admin.txt", "w");
	if(fw == NULL){
		printf("ERROR\n");
		return;
	}
	int i;
	for(i = 0; i < 100; i++){
		if(!strcmp(admins[i].name, "end")){
			fputs("end", fw);	//admins[i].name读取完毕
			fclose(fw);
			return;
		}
		fputs(admins[i].name, fw);
		fputc('\n', fw);
	}
}

void storeBorrowedBookList(){   //存储图书在借名单
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
    printf("输入图书名字：\n");
    scanf("%s", bname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(bname, books[i].name)){	//找到书名对应的图书
			flag = 1;
			printf("按下数字键，确认修改图书的哪一信息：1.书名 2.库存\n");
			int opt;
			scanf("%d",&opt);
			if (opt == 1) {
				printf("输入新书名：\n");
				scanf("%s", bname);
				strcpy(books[i].name, bname);
				printf("成功\n");
				storeBooks();
			} else if (opt == 2) {
				printf("输入更新后的库存：\n");
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
    printf("输入图书名字：\n");
    scanf("%s", bname);
    int i, flag = 0;
    //遍历books数组，找到end元素，将图书添加到此位置，并将end元素后移一位
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, "end")){
			strcpy(books[i].name, bname);
			books[i].id = i;
			books[i].count = 3; //图书库存初始化为3
			strcpy(books[i+1].name, "end");
			strcpy(borrowerList[i], "no");  //此时该图书暂时没人借到
			strcpy(borrowerList[i+1], "end");   //结尾标志移到第i+1个位置
			books[i+1].count = -1;  //第i+1本书不存在
			flag = 1;   //标志添加图书成功
			break;
		}
	}
    //以下3个store()函数更新文件中的信息，持久化存储
	storeBookLeft();
	storeBooks();
	storeBorrowerList();
	if (flag) 
        printf("成功\n");
	else
        printf("失败\n");
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
    printf("输入图书姓名:\n");
    scanf("%s", bname);
    int i, flag = 0;
    //遍历寻找该图书并删除
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			if (!strcmp(borrowerList[i],"no")) {
				strcpy(borrowerList[i], "");
			}
			int k = findNotBank(borrowerList[i]);
			if (k < strlen(borrowerList[i])) {	//该图书有读者在借	
				printf("失败\n");
				return;
			}
			strcpy(books[i].name, "null");  //置为null即为删除
			books[i].count = 0;
			flag = 1;
			break;
		}
	}
	storeBookLeft();
	storeBooks();
	if(flag)
        printf("成功\n");
	else
        printf("失败\n");
}


void queryBook() {
	char bname[20];
	printf("输入图书名字：\n");
	scanf("%s", bname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(bname, books[i].name)){ 	//找到书名对应的图书
			flag = 1;
			printf("书名: %s\n", books[i].name);
			printf("id: %d\n", books[i].id);
			printf("库存: %d\n", books[i].count);
			printf("借书人: %s\n", borrowerList[i]);
		}
		if(!strcmp(books[i].name, "end"))	break;
	}
	if (!flag) {
		printf("未找到该图书\n");
	}
}

void addReader() {
	char rname[20], reroot[20];
	printf("输入读者姓名：\n");
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
	storeReaders();	//更新文件中的内容
	if(flag)	
		printf("添加成功\n");
	else	
		printf("添加失败\n");
}


void deleteReader() {
	char rname[20];
	printf("输入读者姓名：\n");
	scanf("%s", rname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(readers[i].name, rname)){
			//strcmp()返回非0，说明读者还有所借书，只要全部还书，才可以删除该读者信息
			if(strlen(borrowedBookList[i]) != 0){	
				printf("失败\n");
				return;
			}
			strcpy(readers[i].name, "null");
			flag = 1;
			break;
		}
	}
	storeReaders();
	if(flag)
		printf("删除成功\n");
	else
		printf("删除失败\n");
}

void modifyReader() {
	char rname[20];
	printf("输入读者姓名：\n");
	scanf("%s", rname);
	int i;
	for(i = 0; i < 100; i++){		
		if(!strcmp(rname, readers[i].name)){
			printf("修改后的读者姓名：");
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
	printf("输入读者姓名：\n");
	scanf("%s", rname);
	int i;
	int flag = 0;
	for(i = 0; i < 100; i++){		
		if(!strcmp(rname, readers[i].name)){
			printf("姓名: %s\n", readers[i].name);
			printf("id: %d\n", readers[i].id);
			printf("在借图书: %s\n", borrowedBookList[i]);
			flag = 1;
		}
		if(!strcmp(readers[i].name, "end")) {
			break;
		}
	}
	if (!flag) {
		printf("未找到该读者\n");
	}
}

void borrowBook(){
	char bname[20];
	printf("输入书名:\n");
	scanf("%s", bname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			if(books[i].count == 0){
				printf("图书暂时没有库存\n");
				return;
			}else{
				books[i].count--;
				if(!strcmp(borrowerList[i], "end")){
					strcpy(borrowerList[i], rname);	//会把end覆盖掉，哪怕ranme的长度小于3
					strcpy(borrowerList[i+1], "end");
				}else{
					strcat(borrowerList[i], " ");
					strcat(borrowerList[i], rname);
				}
				int j;
				for(j = 0; j < 100; j++){
					if(!strcmp(readers[j].name, rname)){
						if(!strcmp(borrowedBookList[j], "end")){
							//bname把"end"覆盖掉
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
	//更新文件内容
	storeBorrowerList();
	storeBorrowedBookList();
	storeBookLeft();
	if(flag)
		printf("成功\n");
	else
		printf("失败\n");
	loadBooks();
	loadReaders();
}

void returnBook() {
	char bname[20];
	printf("输入书名:\n");
	scanf("%s", bname);
	int i, flag = 0;
	for(i = 0; i < 100; i++){
		if(!strcmp(books[i].name, bname)){
			books[i].count++;
			char *des1 = strstr(borrowerList[i], rname), *des2 = strstr(borrowerList[i], rname);
			char p[100];
			des1 += strlen(rname);	//desc1比desc2字符串少了还书人的人名
			if(des1 != NULL){
				strcpy(p, des1);
				strcpy(des2, p);	//将rname从borrowerList[i]中删除
			}
			int j;
			for(j = 0; j < 100; j++){
				if(!strcmp(readers[j].name, rname)){
					char *des3 = strstr(borrowedBookList[j], bname), *des4 = strstr(borrowedBookList[j], bname);
					char q[100];
					des3 += strlen(bname);	//desc3比desc4少了被还的书的书名
					if(des3 != NULL){
						strcpy(q, des3);
						strcpy(des4, q);	//将bname从borrowedBookList[j]删除
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
	if(flag)	printf("成功\n");
	else	printf("失败\n");
	loadBooks();
	loadReaders();
}

void queryBookById() {
	printf("%s\n", borrowedBookList[id]);
}

//查找是否存在username对应的用户
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

//查找是否存在admin对应的管理员
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

//程序的开始界面
void start(char sign, char* username) {
    int opt = 1;
    if (sign == 'a') {
        if (!existAdmin(username)) {
			printf("用户名不合法\n");
            return;
        }
        while (opt != 0) {
            printf("\n--------图书馆管理系统(admin)-----------\n");
            printf("| 你可以选择以下操作(按下相应数字键):         |\n");
            printf("| 0.退出程序                                  |\n");
            printf("| 1.录入图书信息                              |\n");
            printf("| 2.删除图书信息                              |\n");
            printf("| 3.修改图书信息                              |\n");
            printf("| 4.查询图书信息                              |\n");
            printf("| 5.录入读者信息                              |\n");
            printf("| 6.删除读者信息                              |\n");
            printf("| 7.修改读者信息                              |\n");
            printf("| 8.查询读者信息                              |\n");
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
                    printf("输入不合法");
                    break;
            }
        }
    } else {
		if (!existUser(username)) {
			printf("用户名不合法\n");
			return;
		}
        while (opt != 0) {
            printf("\n--------图书馆管理系统(reader)------------------\n");
            printf("| 你可以选择以下操作(按下相应数字键):           |\n");
            printf("| 0.退出程序                                  |\n");
            printf("| 1.借书                                      |\n");
            printf("| 2.还书                                      |\n");
            printf("| 3.查询图书                                  |\n");
			printf("| 4.查询自己所借图书                           |\n");
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
                    printf("输入不合法");
                    break;
            }
        }
    }
}

/*
Libsim -a(-u) xxxx
第一个参数为可执行程序名称；第二个参数为用户身份，-a表示管理员，-u表示读者；第三个参数为用户名
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
        printf("输入参数不合法\n");
    }
	printf("再见\n");
}
