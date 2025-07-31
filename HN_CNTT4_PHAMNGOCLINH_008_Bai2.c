#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Student {
    int id;
    int age;
    char name[50];
    struct Student *left;
    struct Student *right;

}Student;

Student *createStudent(int id,int age, char name[]) {
    Student *node =(Student*)malloc(sizeof(Student));
    strcpy(node->name,name);
    node -> age=age;
    node -> id=id;
    node ->left=node ->right=NULL;
    return node;

}
Student*insertStudent(Student*root,int id,int age, char name[]) {
    if (root==NULL) return createStudent(id,age, name);
    int cmp=strcmp(id,root->  id);
    if (cmp<0)
        root -> left=insertStudent(root->left,id,age, name);
    else if (cmp>0)

        root -> right=insertStudent(root->right,id,age, name);
    else
        printf("ko co ma sinh vien nay");
    return root;
}
void inOrder(Student*root) {
    if (root==NULL) return;
    inOrder(root-> left);
    printf("ID:%d,Name:%s,age:%d\n",root->id,root-> name,root->age);
    inOrder(root-> right);
}

Student*searchStudent(Student*root,int id) {
    if (root==NULL) return NULL;
    int cmp=strcmp(id,root-> id);
    if (cmp==0)
        return root;
    if (cmp<0)
        return searchStudent(root->left,id);
    else if (cmp>0)

         return searchStudent(root->right,id);
    else
        printf("ko co ma sinh vien nay");


}


//neu node co 2 con khi truong hop xoa
Student*findMin(Student *root) {
    while (root && root ->left !=NULL)
        root=root -> left;
    return root;
}

Student*deleteStudent(Student*root,int id) {
    if (root==NULL) return NULL;
    int cmp=strcmp(id,root-> id);
    if (cmp<0)
        return deleteStudent(root->left,id);
    else if (cmp>0)

        return deleteStudent(root->right,id);
    else {
        if (root-> left==NULL) {
            Student *temp=root-> right;
            free(root);
            return temp;
        }
       else if (root-> right==NULL) {
            Student *temp=root-> left;
            free(root);
            return temp;
        }
        Student *minRight=findMin(root->right);
        strcpy(root-> name,minRight-> name);
        root->right=deleteStudent(root->right,minRight->id);


    }
    return root;
}



int main() {
    Student *root =NULL;
    int choice;
    int id;
    char name[50];
    int age;
    do{
    printf("============MENU==========\n");
    printf("1: them sinh vien \n");
    printf("2: hien thi danh sach sinh vien \n");
    printf("3:tim kiem sinh vien \n");
    printf("4:xoa sinh vien \n");
    printf("5: thoat\n");
    printf("moi ban nhap vao lua chon:\n");
    scanf("%d",&choice);
    getchar();
    switch (choice) {
        case 1:
            printf("moi ban nhap vao id sinh vien:\n");
            scanf("%d",&id);
            printf("moi ban nhap vao ten sinh vien:\n");
            gets(name);
            printf("moi ban nhap vao tuoi sinh vien:\n");
            scanf("%d",&age);
            root =insertStudent(root,id,age,name);



            break;
        case 2:
            printf("danh sach sinh vien\n");
            inOrder(root);
            break;
        case 3:
            printf("nhap ma id can tim :\n");
           scanf("%d",&id);
            printf(" ko tim thay sinh vien\n");
            break;
        case 4:
            printf("nhap ma id can xoa :\n");
            scanf("%d",&id);
           root=deleteStudent(root,id);
            printf(" da xoa sinh vien\n");
            break;
        case 5:
            printf("cam on ban da su dung dich vu \n");
            break;
        default:
            printf("lua chon ko hop le\n");
            break;
    }


    }while (choice!=5);
return 0;
}
