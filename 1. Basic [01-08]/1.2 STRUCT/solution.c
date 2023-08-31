#include <stdio.h>

struct dob_age {
    char dob[10];
    int age;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob_age DOB;
};


void take_info(struct student_info *s){
    printf("\nEnter student information\n");
    printf("Roll: \t");
    scanf("%d",&s->roll_no);
    printf("Name: \t");
    scanf("%s", s->name);
    printf("CGPA: \t");
    scanf("%f",&s->CGPA);
    printf("DOB: \t");
    scanf("%s", s->DOB.dob);
    printf("Age: \t");
    scanf("%d",&s->DOB.age);
}

void print_info(struct student_info s){
    printf("\nPrinting Student Information\n");
    printf("Roll: \t %d\n", s.roll_no);
    printf("Name: \t %s\n", s.name);
    printf("CGPA: \t %.2f\n", s.CGPA);
    printf("DOB: \t %s\n", s.DOB.dob);
    printf("Age: \t %d\n", s.DOB.age);
}

int main(){
    struct student_info student;

    take_info(&student);
    print_info(student);

}