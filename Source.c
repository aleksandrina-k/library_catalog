#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STR_MAX ((size_t) 20)
#define ADR_MAX ((size_t) 80)
#define EGN_MAX ((size_t) 10)
#define ID_MAX ((size_t) 8)

typedef struct Name {
	char first[STR_MAX];
	char middle[STR_MAX];
	char last[STR_MAX];
}t_name;

typedef struct Person {
	char ID[ID_MAX];
	t_name name;
	char adress[ADR_MAX];
	char EGN[EGN_MAX];
	int taken_books;
}t_person;

typedef struct Node {
	t_person info;
	struct Node* next;
}t_node;

t_node* Register();
void PrintOne(t_node* p);
void PrintAll(t_node* p_head);
t_node* CreateList(t_node* p_head);
int CheckForID(t_node* p_head, char* id);
unsigned MostBooksTaken(t_node* p_head);
void FindByName(t_node* p_head, const char* pname);
void DeleteByID(t_node** p_head, char* id);
int GetInt();
int CheckForChar(char* str);
int CheckForNum(char* str);
void WriteInBinary(const char* fname, t_node* p_head);
void ReadFromBinary(const char* fname);
unsigned CntInBinFIle(const char* fname);
void read_and_create_list(const char* file_name, t_node** p_head, unsigned len);
void FreeList(t_node** p_head);
int CheckForEGN(t_node* p_head, char* egn);

int main()
{
	int command = 7;
	unsigned max, size;
	t_node* head = NULL, * cur = head;
	char* str;
	str = (char*)malloc(sizeof(char) * STR_MAX);
	if (str == NULL)
	{
		printf("Memory error...");
		exit(0);
	}
	size = CntInBinFIle("binary.dat");
	read_and_create_list("binary.dat", &head, size);

	while (command)
	{
		printf("\t\t\MENU\n");
		printf("\t0.EXIT\n");
		printf("\t1.REGISTER\n");
		printf("\t2.PRINT info\n");
		printf("\t3.SHOW the readers with MOST TAKEN BOOKS\n");
		printf("\t4.SEARCH by LAST name\n");
		printf("\t5.DELETE data\n");
		printf("\t6.WRITE the data in BINARY FILE\n");
		printf("\t*********************\n");
		printf("\tYour choice:");
		scanf("%d", &command);

		switch (command)
		{
		case 0:
			FreeList(&head);
			printf("Bye! =)\n");
			break;
		case 1:
			head = CreateList(head);
			break;
		case 2:
			if (head == NULL)
				printf("No data.\n");
			else {
				printf("\n==INFO==\n");
				PrintAll(head);
			}
			break;
		case 3:
			if (head == NULL)
				printf("No data.\n");
			else {
				max = MostBooksTaken(head);
				printf("\n\n===The readers with most taken books [%u]===\n", max);
				for (cur = head; cur != NULL; cur = cur->next)
					if (cur->info.taken_books == max)
						PrintOne(cur);
			}
			break;
		case 4:
			if (head == NULL)
				printf("No data.\n");
			else {
				str = (char*)malloc(sizeof(char) * 15);
				if (str == NULL)
				{
					perror(NULL);
					exit(5);
				}
				printf("\n\n====Find by name====\n");
				printf("Input last name:");
				scanf("%s", str);
				FindByName(head, str);
			}
			break;
		case 5:
			if (head == NULL)
				printf("No data.\n");
			else {
				str = (char*)malloc(sizeof(char) * 8);
				if (str == NULL)
				{
					perror(NULL);
					exit(6);
				}
				printf("\nInput the ID of the reader you want to DELETE:");
				scanf("%s", str);
				DeleteByID(&head, str);
			}
			break;
		case 6:
			if (head == NULL)
				printf("No data.\n");
			else {
				WriteInBinary("binary.dat", head);
				printf("\n==The data written in the file==\n");
				ReadFromBinary("binary.dat");
			}
			break;
		default:
			printf("Wrong command. :(\n");
			break;
		}
	}
	free(str);
	return 0;
}

t_node* Register()
{
	t_node* new = NULL;
	new = (t_node*)malloc(sizeof(t_node));
	if (new == NULL)
	{
		printf("Memory error...\n");
		exit(0);
	}

	printf("\nID: ");
	scanf("%s", new->info.ID);
	while (CheckForChar(new->info.ID) == 1)
	{
		printf("Invalid input!\n(only numbers allowed)\n");
		printf("ID: ");
		scanf("%s", new->info.ID);
	}

	printf("First name: ");
	scanf("%s", new->info.name.first);
	while (CheckForNum(new->info.name.first) == 1)
	{
		printf("Invalid input!\n(only letters allowed)\n");
		printf("First name: ");
		scanf("%s", new->info.name.first);
	}

	printf("Middle name: ");
	scanf("%s", new->info.name.middle);
	while (CheckForNum(new->info.name.middle) == 1)
	{
		printf("Invalid input!\n(only letters allowed)\n");
		printf("Second name: ");
		scanf("%s", new->info.name.middle);
	}

	printf("Last name: ");
	scanf("%s", new->info.name.last);
	while (CheckForNum(new->info.name.last) == 1)
	{
		printf("Invalid input!\n(only letters allowed)\n");
		printf("Last name: ");
		scanf("%s", new->info.name.last);
	}

	printf("Adress: ");
	getchar();
	gets(new->info.adress);

	printf("EGN: ");
	scanf("%s", new->info.EGN);
	while (CheckForChar(new->info.EGN) == 1)
	{
		printf("Invalid input!\n(only numbers allowed)\n");
		printf("EGN: ");
		scanf("%s", new->info.EGN);
	}

	new->info.taken_books = GetInt();
	while (new->info.taken_books < 0)
	{
		printf("Invalid number!\n");
		new->info.taken_books = GetInt();
	}

	new->next = NULL;

	return new;
}

int GetInt()
{
	int x;
	char c;

	printf("Number of taken books: ");
	while (scanf("%d", &x) != 1) {
		c = getchar();

		printf("You have entered ");
		putchar(c);
		printf(" in the input which is not an integer");

		while (getchar() != '\n');

		printf("\nNumber of taken books: ");
	}
	return x;
}
int CheckForChar(char* str)
{
	for (int i = 0; i < strlen(str); i++)
		if (str[i] < '0' || str[i]>'9')
			return 1;
	return 0;
}
//ako nameri char vrushta 1
int CheckForNum(char* str)
{
	for (int i = 0; i < strlen(str); i++)
		if (str[i] >= '0' && str[i] <= '9')
			return 1;
	return 0;
}
//ako nameri chislo vrushta 1

void PrintOne(t_node* p)
{
	printf("------------------\n");
	printf("ID: %s\n", p->info.ID);
	printf("Name: %s %s %s\n", p->info.name.first, p->info.name.middle, p->info.name.last);
	printf("Adress: %s\n", p->info.adress);
	printf("EGN: %s\n", p->info.EGN);
	printf("Taken books: %u\n", p->info.taken_books);
	printf("------------------\n");
}
void PrintAll(t_node* p_head)
{
	t_node* cur = p_head;
	for (; cur != NULL; cur = cur->next)
		PrintOne(cur);
}

t_node* CreateList(t_node* p_head)
{
	t_node* temp = p_head;
	if (p_head == NULL)
	{
		temp = Register();
		return temp;
	}

	t_node* new = Register();

	while (CheckForID(p_head, new->info.ID) == 1)
	{
		printf("\nThere is already a person with this ID\n");
		new = Register();
	}
	while (CheckForEGN(p_head, new->info.EGN) == 1)
	{
		printf("There's a person with the same EGN.\n");
		new = Register();
	}

	new->next = temp;
	temp = new;

	return temp;
}
int CheckForID(t_node* p_head, char* id)
{
	t_node* cur = p_head;
	for (; cur != NULL; cur = cur->next)
		if (strcmp(cur->info.ID, id) == 0)
			return 1;
	return 0;
}
//vrushta 1 pri suotvetstvie i 0 pri nesuotvetstvie

unsigned MostBooksTaken(t_node* p_head)
{
	unsigned max = 0;
	t_node* cur = p_head;

	for (; cur != NULL; cur = cur->next)
		if (max < cur->info.taken_books)
			max = cur->info.taken_books;
	return max;
}
void FindByName(t_node* p_head, const char* pname)
{
	t_node* cur = p_head;
	int cnt = 0;

	for (; cur != NULL; cur = cur->next)
		if (strcmp(pname, cur->info.name.last) == 0)
		{
			PrintOne(cur);
			cnt = 1;
		}

	if (cnt == 0)
		printf("There are no people with such a last name.\n");
}
void DeleteByID(t_node** p_head, char* id)
{
	t_node* cur = *p_head, * p = *p_head;

	if (cur != NULL && strcmp(cur->info.ID, id) == 0)
	{
		if (cur->info.taken_books == 0)
		{
			*p_head = cur->next;
			cur->next = NULL;
			free(cur);
			printf("Successfully Deleted!\n");
		}
		else
			printf("He/She needs to return the books first.\n");
		return;
	}
	while (cur != NULL && strcmp(cur->info.ID, id) != 0)
	{
		p = cur;
		cur = cur->next;
	}

	if (cur == NULL)
	{
		printf("There aren't readers with such ID.\n");
		return;
	}
	if (cur->info.taken_books == 0)
	{
		p->next = cur->next;
		cur->next = NULL;
		free(cur);
		printf("Successfully Deleted!\n");
	}
	else
		printf("He/She needs to return the books first.\n");
	return;
}
void FreeList(t_node** p_head)
{
	t_node* temp = NULL;

	for (; *p_head != NULL; *p_head = temp)
	{
		temp = (*p_head)->next;
		free(*p_head);
	}

	*p_head = NULL;
	temp = NULL;
}

void WriteInBinary(const char* fname, t_node* p_head)
{
	FILE* fp_b = fopen(fname, "wb");
	if (fp_b == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	t_node* cur = p_head;
	for (; cur != NULL; cur = cur->next)
	{
		if (fwrite(&cur->info, sizeof(t_person), 1, fp_b) != 1)
		{
			printf("Error writing in the file.\n");
			fclose(fp_b);
			return;
		}
	}
	printf("\nWriting complete!\n");
	fclose(fp_b);
	fp_b = NULL;
}
void ReadFromBinary(const char* fname)
{
	t_person temp;
	FILE* fp_b = fopen(fname, "rb");
	if (fp_b == NULL)
	{
		printf("Error opening file!\n");
		exit(0);
	}

	while (fread(&temp, sizeof(t_person), 1, fp_b) == 1)
	{
		printf("------------------\n");
		printf("ID: %s\n", temp.ID);
		printf("Name: %s %s %s\n", temp.name.first, temp.name.middle, temp.name.last);
		printf("Adress: %s\n", temp.adress);
		printf("EGN: %s\n", temp.EGN);
		printf("Taken books: %u\n", temp.taken_books);
		printf("------------------\n");
	}
}
unsigned CntInBinFIle(const char* fname)
{
	t_person temp;
	unsigned cnt = 0;
	FILE* fp_b = fopen(fname, "rb");
	if (fp_b == NULL)
	{
		printf("Error opening file!\n");
		return 0;
	}

	while (fread(&temp, sizeof(t_person), 1, fp_b) == 1)
		cnt++;

	return cnt;
}

void read_and_create_list(const char* file_name, t_node** p_head, unsigned len)
{
	t_node* temp = NULL;

	FILE* fp_b = fopen(file_name, "rb");
	if (fp_b == NULL)
	{
		perror("Error");
		exit(0);
	}

	for (int i = 0; i < len; i++)
	{
		if (*p_head == NULL)
		{
			*p_head = (t_node*)malloc(sizeof(t_node));
			if (*p_head == NULL)
			{
				printf("Memory error...\n");
				exit(0);
			}

			(void)fread(&(*p_head)->info, sizeof(t_person), 1, fp_b);
			(*p_head)->next = NULL;

			temp = *p_head;
		}
		else
		{
			temp->next = (t_node*)malloc(sizeof(t_node));
			if (temp->next == NULL)
			{
				printf("Memory error...\n");
				FreeList(p_head);
				exit(0);
			}

			(void)fread(&temp->next->info, sizeof(t_person), 1, fp_b);
			temp->next->next = NULL;

			temp = temp->next;
		}
	}
	temp = NULL;
	fclose(fp_b);
	fp_b = NULL;
}

int CheckForEGN(t_node* p_head, char* egn)
{
	t_node* cur = p_head;
	for (; cur != NULL; cur = cur->next)
		if (strcmp(cur->info.EGN, egn) == 0)
			return 1;
	return 0;
}
//pri suotvetstvie vrushta 1