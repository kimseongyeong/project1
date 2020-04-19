#include "restaurant.h"

void create_record();//완료
void read_record();//완료
void update_record();//완료
void delete_record_byname();//완료
void delete_byavg();//완료
void list_record();//완료
void search_type();//완료
void search_avg();//완료
void load_file();//완료
void save_file();//완료
void op();//완료
void sort_avg();//완료


    int main(){
    r_init();
        int menu;
        while(1){
                printf("\nMenu\n");
                printf("1.Create 2.Read 3.Update 4.Delete(name)\n");
                printf("5.Delete(avg)6.List 7.Search(type) 8.Search(avg)\n") ;
                printf("9.Load 10.Save 11.Optimize Record 12.Sort 0.Quit\n");
                printf("\nplease input a menu number:");
                scanf("%d", &menu);
                printf("\n");
                switch(menu){
                        case 1:
                            create_record();
                            break;
                        case 2:
                            read_record();
                            break;
                        case 3:
                            update_record();
                            break;
                        case 4:
                            delete_record_byname();
                            break;
                        case 5:
                            delete_byavg();
                            break;
                        case 6:
                            list_record();
                            break;
                        case 7:
                            search_type();
                            break;
                        case 8:
                            search_avg();
                            break;
                        case 9:
                            load_file();
                            break;
                        case 10:
                            save_file();
                            break;
                        case 11:
                            op();
                            break;
                        case 12:
                            sort_avg();
                            break;
                        case 0:
                        default :
                        return 0;
                        }
                 }

        return 0;
    }

void create_record(){
        int ty;
       char name[100];
        int tat;
        int mon;
        int atm;
        float avg=0;

        printf("Input a restaurant's info.\n");
        while(1){
        printf("한식[1] 중식[2] 일식[3] 양식[4]>");
        scanf("%d",&ty);
        if (ty<0 || ty>4)
                printf("Wrong number!\n");
        else
                break;
        }
        printf("Name?  >");
        scanf("%s" , name);
        if(r_search_by_name(name)){
                printf("duplicated!\n");
                return;
        }

        while(1){
        printf("How delicious is it? (0~5) >");
        scanf("%d",&tat);
        if (tat<0 || tat>5)
            printf("wrong number!\n");
        else
            break;
        }

        while(1){
        printf("How was the quality for the price? (0~5) >");
        scanf("%d",&mon);
        if (mon<0 || mon>5)
            printf("wrong number!\n");
        else
            break;
        }

        while(1){
        printf("How was the atmosphere? (0~5) >");
        scanf("%d",&atm);
        if (atm<0 || atm>5)
            printf("wrong number!\n");
        else
            break;
        }
        avg=(float)( tat + mon + atm)/3.0;
        printf("The average is %.1f.\n",avg);
        r_create(ty,name,tat,mon,atm,avg);

        }
void read_record(){
        char name[100];

        while(1){
        printf("Name? > ");
        scanf("%s",name);
        T_Record* p = r_search_by_name(name);


        if(p){
                printf("restaurant's info.\n");
                if(r_gettype(p)==1)
                printf("== Normal == \n");
                else if(r_gettype(p)==2)
                printf("== Cafe ==\n");
                else if (r_gettype(p)==3)
                printf("== Bakery ==\n");
                printf("Name : %s\n", r_getname(p));
                printf("Taste : %d\n", r_gettat(p));
                printf("Cost-effective :%d\n", r_getmon(p));
                printf("Atmosphere :%d\n", r_getatm(p));
                printf("average :%.1f\n", r_getavg(p));
                printf("Star score >> ");
                for (int j=0 ; j<r_getavg(p) ; j++)
                    printf("*");
                break;

        }
        else
                printf("There is no such restaurant.\n");
                break;
        }
}


void list_record(){
    // 전체 리스트 출력
    printf("\tAll List\n");
    printf("=========================\n");
    int size = r_count();
    T_Record* records[MAX_MEMBERS];
    r_get_all(records);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, r_to_string(p));
    }
}
void load_file(){
    // 데이터파일 읽기
    printf("All data will be deleted and new records will be reloaded.\n");
    printf("1.Yes 0.No > ");
    int yesno;
    scanf("%d", &yesno);
    if (yesno == 0) return;
    r_init();   // 레코드 모두 제거

    FILE* f = fopen("members.txt", "r");
    char name[100];
    int ty,mon,atm,tat;
    float  avg;
    while(!feof(f)){
        if(!r_is_available()) {
            printf("[Load] There is no space!\n");
            break;
        }
        int n = fscanf(f,"%s %d %d %d %d %f",name,&ty, &tat,&mon,&atm,&avg);
        if (n<5) break;
        if(r_search_by_name(name)) {
            printf("[Load] Duplicated name(%s)! loading.\n", name);
            continue;
        }

        r_create(ty,name,tat,mon,atm,avg);
        printf("[Load] %s\n", name);
    }
    printf("%d records are read from file!\n", r_count());
    fclose(f);
}

void save_file(){
    // 데이터파일 저장
    FILE* f = fopen("members.txt", "w");
    printf("All records.\n");
    int size = r_count();
    T_Record* records[MAX_MEMBERS];
    r_get_all(records);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        fprintf(f,"%s\n", r_to_string_save(p));
    }
    fclose(f);
}

void search_type(){
    //이름 일부문자열로 검색
    int type;
    printf("한식[1] 중식[2] 일식[3] 양식[4] > ");
    scanf("%d",&type);

    T_Record* records[MAX_MEMBERS];
    int size = r_get_all_by_type(records, type);
    printf("%d records found.\n", size);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, r_to_string(p));
    }
}

void search_avg(){
    // 입력받은 평균보다 높은 평균점수를 가진 회원 출력
    float av;
    printf("Enter an average > ");
    scanf("%f",& av);

    T_Record* records[MAX_MEMBERS];
    int size = r_get_all_by_avg(records, av);
    printf("%d records found.\n", size);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, r_to_string(p));
    }
}
void update_record(){
    char name[100];
    int ty, tat,mon,atm;
    float  avg;
    
    printf("Enter a name > ");
    scanf("%s", name);

	 T_Record* p = r_search_by_name(name);
	if(p) {
	
		
	while(1){
        printf("한식[1] 중식[2] 일식[3] 양식[4] >");
        scanf("%d",&ty);
        if (ty<0 || ty>4)
                printf("Wrong number!\n");
        else
                break;
	}

        while(1){
        printf("How delicious is it? (0~5) >");
        scanf("%d",&tat);
        if (tat<0 || tat>5)
            printf("wrong number!\n");
        else
            break;
        }

        while(1){
        printf("How was the quality for the price? (0~5) >");
        scanf("%d",&mon);
        if (mon<0 || mon>5)
            printf("wrong number!\n");
        else
            break;
        }

        while(1){
        printf("How was the atmosphere? (0~5) >");
        scanf("%d",&atm);
        if (atm<0 || atm>5)
            printf("wrong number!\n");
        else
            break;
        }
        avg=(float)( tat + mon + atm)/3.0;
       
		
	r_update(p,ty, tat, mon, atm, avg);
												    }
	 else {
		 printf("No such member!\n");
					        }
}


void delete_record_byname(){

    char name[100];
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = r_search_by_name(name);
    if(p) {
       r_delete(p);
        printf("The record is deleted!\n");
    }
    else {
        printf("No such member!\n");
    }
}
 
void delete_byavg(){
	float avg;
	int count = r_count();
	T_Record* a[MAX_MEMBERS];
	printf("Enter an average > ");
	scanf("%f",&avg);
	for(int i=0;i<count;i++){
	a[i] = r_search_by_avg(avg);
	if(a[i]){
	r_delete(a[i]);
	}
	
}
	printf("Completed!!");
	
}
void op(){
	
	r_optimize();
	printf("Optimized!");
 
}
void sort_avg(){
	//r_optimize();
	r_sort();
	printf("Sorted!");
}                                                                                                                        
