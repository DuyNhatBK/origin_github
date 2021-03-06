// aaaa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

#define LINKED_LIST_MAX_ELEMENT        20
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// QUY DINH: 1 la lop A; 0 la lop B

typedef struct sinhvien{
	uint8_t Class;
	uint8_t GPA;
	uint32_t ID;
	struct sinhvien *sNext;
} Student;

Student student_list[LINKED_LIST_MAX_ELEMENT];

Student *first = NULL;

int check(Student *first, uint32_t ID){
	Student *ptr = first;
	for (; ptr; ptr = ptr->sNext){
		if (ptr->ID == ID) return 0;
	}
	return 1;
}

void linkedlist_init(void)// Khoi tao cho tat ca cac phan tu trong mang
{
	uint8_t index = 0;
	for (index = 0; index < LINKED_LIST_MAX_ELEMENT; index++)
	{
		student_list[index].Class = 0xFF;
		student_list[index].GPA = 0xFF;
		student_list[index].ID = 0xFFFFFFFF;
		student_list[index].sNext = NULL;
	}
}

Student *cap_phat(void){ // cap phat bo nho cho cac phan tu sinhvien tu mang 20 phan tu co dinh
	int i;
	Student *retBuff = NULL;
	for (i = 0; i < LINKED_LIST_MAX_ELEMENT; i++)
	{
		if (0xFFFFFFFF == student_list[i].ID)
		{
			retBuff = (Student *)&student_list[i];
			break;
		}
	}

	return retBuff;
}

void Add_SV2(Student **first, uint8_t Class, uint8_t GPA, uint32_t ID){

	if (check(*first, ID)){
		Student *new_stu = cap_phat();
		new_stu->Class = Class;
		new_stu->GPA = GPA;
		new_stu->ID = ID;
		new_stu->sNext = NULL;

		if (*first == NULL) *first = new_stu;//neu list dang rong thi new_stu la phan tu dau tien
		else
		{
			//neu new_stu lon hon phan tu dau tien hoac bang nhung phan tu dau tien thuoc lop B con new_stu thuoc lop A thi cho new_stu la phan tu dau tien
			if ((new_stu->GPA > (*first)->GPA) || ((new_stu->GPA == (*first)->GPA) && ((*first)->Class == 0 && new_stu->Class == 1))){
				new_stu->sNext = *first;
				*first = new_stu;
			}
			else{
				Student *ptr = *first;
				//duyet cac node tiep theo
				for (; ptr->sNext; ptr = ptr->sNext){
					//neu node dang xet co GPA nho hon new_stu hoac bang nhung node dang xet thuoc lop B con new_stu thuoc lop A thi chen new_stu len truoc node dang xet
					if (((ptr->sNext->GPA == new_stu->GPA) && (ptr->sNext->Class == 0 && new_stu->Class == 1)) || (ptr->sNext->GPA < new_stu->GPA)){
						new_stu->sNext = ptr->sNext;
						ptr->sNext = new_stu;
						break;
					}
					// node dang xet co GPA bang new_stu nhung o cac truong hop con lai
					else if (ptr->sNext->GPA == new_stu->GPA){
						new_stu->sNext = ptr->sNext->sNext;
						ptr->sNext->sNext = new_stu;
						break;
					}
				}
				//duyet het danh sach, khong co node nao nho hon new_stu thi chen new_stu o cuoi danh sach
				if (ptr->sNext == NULL){
					ptr->sNext = new_stu;
				}
			}
		}
	}
	else printf("\nTrung ID");
}

void SV_Remove(Student **first, uint32_t ID){

	if (!check(*first, ID)){
		Student *ptr = *first, *ptr2 = NULL;

		if (ID == ptr->ID){
			ptr->Class = 0xFF;
			ptr->GPA = 0xFF;
			ptr->ID = 0xFFFFFFFF;
			*first = ptr->sNext;
			ptr->sNext = NULL;
		}
		else
		{
			for (; ptr; ptr = ptr->sNext){
				if (ID == ptr->ID){
					ptr2->sNext = ptr->sNext;
					ptr->Class = 0xFF;
					ptr->GPA = 0xFF;
					ptr->ID = 0xFFFFFFFF;
					ptr->sNext = NULL;
				}
				ptr2 = ptr;
			}
		}
	}
	else printf("\nSinh vien khong ton tai");
}

void Nhap_SV(Student **first){
	int Class, GPA;
	uint32_t ID;

	printf("\nNhap thong tin sinh vien:\n");
	do{
		printf("\n+ GPA (0<GPA<255):"); scanf_s("%d", &GPA);
	} while (GPA<0 || GPA>255);
	do{
		printf("\n+ Class (0: lop fresher B, 1: lop fresher A):"); scanf_s("%d", &Class);
	} while (Class!=0 && Class!=1);
	do{
		printf("\n+ ID:"); scanf_s("%ld", &ID);
	} while (ID < 0 || ID > 0xffffffff);

	Add_SV2(first, Class, GPA, ID);
}

void print_sv(Student *first){
	int count = 0;
	Student *ptr = first;
	printf("\n|----------------------------------------------------|");
	printf("\n| STT |  ID cua sinh vien  | Lop sinh vien |   GPA   |");
	printf("\n|----------------------------------------------------|");
	for (; ptr; ptr = ptr->sNext){
		printf("\n|%5d|", count++ + 1);
		printf("%20ld|", ptr->ID);
		printf("   ");
		if (ptr->Class == 1) printf("Fresher A");
		else if (ptr->Class == 0) printf("Fresher B");
		printf("   |");
		printf("%9d|", ptr->GPA);
		printf("\n|----------------------------------------------------|");
	}
}

int main() {

	int menu;
	linkedlist_init();

	while (true)
	{
		system("cls");
		printf("\n|------------------------------|");
		printf("\n|             MENU             |");
		printf("\n|------------------------------|");
		printf("\n|1. Them nhan vien moi.        |");
		printf("\n|2. Xoa mot nhan vien.         |");
		printf("\n|3. Danh sach nhan vien.       |");
		printf("\n|4. Thoat.                     |");
		printf("\n|------------------------------|");

		do{
			printf("\n\nChon mot muc: "); scanf_s("%d", &menu);
		} while (menu < 1 || menu > 4);

		switch (menu)
		{
		case 1:
			system("cls");
			Nhap_SV(&first);
			printf("\nThem thanh cong ! \n\n  Nhan phim bat ky de tro lai menu");
			_getch();
			break;
		case 2:
			system("cls");
			uint32_t ID;
			printf("\nNhap ID cua sinh vien can xoa:"); scanf_s("%ld", &ID);
			SV_Remove(&first, ID);
			printf("\nXoa thanh cong ! \n\n  Nhan phim bat ky de tro lai menu");
			_getch();
			break;
		case 3:
			system("cls");
			printf("\nDanh sach sinh vien:");
			print_sv(first);
			printf("\nNhan phim bat ky de tro lai menu");
			_getch();
			break;
		case 4:
			return 0;
		}
	}
}