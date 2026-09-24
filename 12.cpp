#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Student{
    int id;
    char name[11];

    int size_score;
    float* score; // آرایه ای از نمره ها
    float avg;
    int grade;

    int size_sport;
    char** sports; // آرایه ای از رشته ها

};

struct Student* get_data(int n) {
        
        struct Student* students = (struct Student*) malloc(n * sizeof(struct Student)); // آرایه ای از دانش آموز
        
        for (int i = 0; i < n; i++) {
        

        //---------------------------(personal_info)    
        students[i].id = i + 1;
        scanf("%s " , students[i].name);
        //---------------------------


        //---------------------------(get_scores)
        scanf("%d" , &students[i].size_score);

        students[i].score = (float*) malloc(students[i].size_score * sizeof(float));
        
        for (int j = 0; j < students[i].size_score; j++) {
            scanf("%f" , &students[i].score[j]);
        }
      
        students[i].avg = 0;
        for (int j = 0; j < students[i].size_score; j++) {
            students[i].avg += students[i].score[j];
        }
        
        students[i].avg = students[i].avg / students[i].size_score;
        students[i].grade = (int)students[i].avg;
        //---------------------------

        //---------------------------(get_sport)

        scanf("%d" , &students[i].size_sport);
        students[i].sports = (char**) malloc(students[i].size_sport * sizeof(char*));
        
        for (int j = 0; j < students[i].size_sport; j++) {
            students[i].sports[j] = (char*) malloc(11 * sizeof(char));
            scanf("%s" , students[i].sports[j]);
        }
        //---------------------------
        
    }
    return students;
}

void print_sort_data_detail(struct Student* students ,int size){

    printf("id    avg    sport     name\n");
    printf("-----------------------------\n");
    for (int  i = size-1; i >=0; i--) {
        printf("%d     %d     %d     %s\n",students[i].id,students[i].grade,students[i].size_sport,students[i].name);
    }
}

bool compare(struct Student s1 ,struct Student s2) {   // کی بهتره ؟        
    if(s1.grade > s2.grade)
        return 1;
    
    else if(s1.grade < s2.grade)
        return 0;
    else{
        if(s1.size_sport > s2.size_sport)   
            return 1;
        else if(s1.size_sport < s2.size_sport)
            return 0;
        else{
            if(s1.id < s2.id)   
                return 1;
            else {
                return 0;
            }
                
        }
    }
}

int main(){

    int n;
    scanf("%d" , &n);

    struct Student* students = get_data(n);
    
    

    // sort by avg : insertion sort
    // مانند مرتب سازی انتخابی سوژه بر اساس جایگاه است اما اینجا با جایگاه های قبلی مقایسه می شود 
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j > 0 && compare(students[j-1],students[j])) {    // تعیین شرط مرتب سازی
                struct Student temp = students[j];
                students[j] = students[j-1];
                students[j-1] = temp;
                j--;
            }
        }

        print_sort_data_detail(students,n);

        // for (int i = n-1; i >=0; i--) {
        //     printf("%s\n" , students[i].name);
        // }
       
    

        // آزادسازی حافظه
        for (int i = 0; i < n; i++) {
            free(students[i].score);
            for (int j = 0; j < students[i].size_sport; j++)
                free(students[i].sports[j]);
            free(students[i].sports);
        }
        free(students);
        return 0;

    
}