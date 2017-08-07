#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

#define LINKED_LIST_MAX_ELEMENT        20
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
// QUY DINH: 0XFF la lop A; 0X00 la lop B

typedef struct sinhvien{
    uint8_t Class; 
    uint8_t GPA;
    uint32_t ID;
    struct sinhvien *sNext; 
} Student;

Student student_list[LINKED_LIST_MAX_ELEMENT];

Student *tail = NULL, *first = NULL;

void linkedlist_init(void)// Khoi tao cho tat ca cac phan tu trong mang
{
    uint8_t index = 0;
    for (index = 0; index < LINKED_LIST_MAX_ELEMENT; index ++)
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
    for(i = 0; i < LINKED_LIST_MAX_ELEMENT; i++)
    {
        if(0xFFFFFFFF == student_list[i].ID)
        {
            retBuff = (Student *)&student_list[i];
            break;
        } 
    }

    return retBuff;
}

void Add_SV(Student **first, uint8_t Class, uint8_t GPA, uint32_t ID){

    if(check(*first, ID)){
        Student *new_stu = cap_phat();
        new_stu->Class = Class;
        new_stu->GPA = GPA;
        new_stu->ID = ID;
        new_stu->sNext = NULL;

        if(*first == NULL) *first = new_stu;
            
        Student *ptr = *first;
        for(; ptr; ptr = ptr->sNext){
            if(ptr->sNext == NULL){
                ptr->sNext = new_stu;
                break;
            }
        }

    }
}

void SV_Remove(Student **first, uint32_t ID){

    if(!check(*first, ID)){
        Student *ptr = *first, *ptr2 = NULL;

        if(ID == ptr->ID){
            ptr->Class = 0xFF;
            ptr->GPA = 0xFF;
            ptr->ID = 0xFFFFFFFF;
            *first = ptr->sNext;
            ptr->sNext = NULL;
        }

        for(;ptr; ptr = ptr->sNext){
            if(ID == ptr->ID){
                ptr2->sNext = ptr->sNext;
                ptr->Class = 0xFF;
                ptr->GPA = 0xFF;
                ptr->ID = 0xFFFFFFFF;
            }
            ptr2 = ptr;
        }
    }
}

void swapNodes(Student **first, uint8_t GPA1, uint8_t GPA2)
{
   if (GPA1 == GPA2) return;
 
   Student *prevX = NULL, *currX = *first;
   while (currX && currX->GPA != GPA1)
   {
       prevX = currX;
       currX = currX->sNext;
   }

   Student *prevY = NULL, *currY = *first;
   while (currY && currY->GPA != GPA2)
   {
       prevY = currY;
       currY = currY->sNext;
   }

   if (currX == NULL || currY == NULL)
       return;
 
   if (prevX != NULL) prevX->sNext = currY;
   else *first = currY;  
 
   if (prevY != NULL) prevY->sNext = currX;
   else *first = currX;
 
   Student *temp = currY->sNext;
   currY->sNext = currX->sNext;
   currX->sNext  = temp;
}
/*
Student * Sap_xep(Student *first){
    Student *ptr1 = NULL, *ptr2, *ptr3 = NULL, *ptr4 = NULL, *ptr5, *ptr6 = NULL;
    for(ptr2 = first; ptr2 ; ptr2 = ptr2->sNext){
        ptr3 = ptr2->sNext;
        for(ptr5 = ptr2->sNext; ptr5 ; ptr5 = ptr5->sNext){
            ptr6 = ptr5->sNext;
            if((ptr2->GPA < ptr5->GPA) || ((ptr2->GPA == ptr5->GPA)&&(ptr2->Class == 0x00&&ptr5->Class == 0xff))){ // neu gpa cua sv i nho hon gpa cua sv j thi doi cho hoac neu gpa cua sv i va j bang nhau nhung sv j thuoc lop A con sv i thuoc lop B thi doi cho i va j
                if(ptr2->sNext == ptr5){
                    ptr2->sNext = ptr6;
                    ptr5->sNext = ptr2;
                    if(ptr1 != NULL) ptr1->sNext = ptr5;
                }else if((ptr3 != NULL)&&(ptr3 == ptr4)){
                    ptr2->sNext = ptr6;
                    ptr5->sNext = ptr3;
                    if(ptr1 != NULL) ptr1->sNext = ptr5;
                    ptr3->sNext = ptr2;
                }else{
                    ptr2->sNext = ptr6;
                    if(ptr4 != NULL) ptr4->sNext = ptr2;
                    if(ptr1 != NULL) ptr1->sNext = ptr5;
                    ptr5->sNext = ptr3;
                }
            }
            ptr4 = ptr5;
        }
        ptr1 = ptr2;
    }
    return first;
}
*/
void sort_SV(Student **first){
    Student *ptr1, *ptr2;
    for(ptr1 = *first; ptr1; ptr1 = ptr1->sNext){
        for(ptr2 = ptr1->sNext; ptr2; ptr2 = ptr2->sNext){
            if((ptr1->GPA < ptr2->GPA) || ((ptr1->GPA == ptr2->GPA)&&(ptr1->Class == 0x00&&ptr2->Class == 0xff))){
                swapNodes(first, ptr1->GPA, ptr2->GPA);
            }
        }
    }
}

void Nhap_SV(Student **first){
    uint8_t Class, GPA;
    uint32_t ID;
    
    printf("\nNhap sinh vien:");
    printf("\nNhap GPA:"); scanf("%hhd", &GPA);
    printf("\nNhap Class:"); scanf("%hhd", &Class);
    printf("\nNhap ID:"); scanf("%ld", &ID);
    
    Add_SV(first, Class, GPA, ID);
}

int check(Student *first, uint32_t ID){
    Student *ptr = first;
    for(;ptr; ptr = ptr->sNext){
        if(ptr->ID == ID) return 0;
    }
    return 1;
}

void print_sv(Student *first){
    int count = 0;
    Student *ptr = first;
    for(;ptr;ptr=ptr->sNext){
        printf("\nSinh vien thu %d:", count++ + 1);
        printf("\nID cua sinh vien:  %ld", ptr->ID);
        printf("\nLop sinh vien:  ");
        if(ptr->Class == 0xff) printf("Fresher A");
        else if(ptr->Class == 0x00) printf("Fresher B");
        printf("\nGPA cua sinh vien: %hhd", ptr->GPA);
    }
}

int main() {
	
    int i;
    linkedlist_init();
    Student *first = NULL;
    
    for(i = 0; i < 5; i++){
    	Nhap_SV(&first);
	}
    
    sort_SV(&first);
    print_sv(first);
    
    getch();
    return 0;
}
