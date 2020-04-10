#include "restaurant.h"
//#define DEBUG

T_Record* members[MAX_MEMBERS];
int _count = 0;

int r_is_available(){
    int i;
    for(i=0; i<MAX_MEMBERS; i++){
        if(members[i]==NULL) return 1;
    }
    return 0;
}
int r_first_available(){
        int i;
        for(i=0;i<MAX_MEMBERS;i++){
        if(members[i]==NULL) return i;
        }
         return -1;
}

void r_create(int t, char *n, int ta, int m, int a, float avg){
        int index = r_first_available();
        members[index] = (T_Record*)malloc(sizeof(T_Record));

        T_Record* p = members[index];
        p->type = t;
        strcpy(p->name,n);
        p->tat = ta;
        p->mon =m;
        p->atm =a;
        p->avg = avg;
        _count++;
#ifdef DEBUG
	printf("DEBUG");
#endif
}

T_Record* r_search_by_name(char *n){
        int i;
        for(i=0; i<MAX_MEMBERS; i++){
                if(members[i]!=NULL && strcmp(members[i]->name,n)== 0) return members[i];
        }
       
#ifdef DEBUG
	printf("DEBUG");
#endif
 return NULL;
}

char* r_to_string(T_Record* p){
    static char str[80];
    sprintf(str, " %s \n맛: %d 가성비: %d 분위기: %d\n평균 %.1f", p->name, p->tat, p->mon, p->atm, p->avg);

#ifdef DEBUG
	printf("DEBUG");
#endif
    return str;

}

void r_get_all(T_Record* a[]){
    int i, c=0;

#ifdef DEBUG
	printf("DEBUG");
#endif
    for(i=0; i<MAX_MEMBERS; i++){
        if(members[i]!=NULL){
            a[c]=members[i];
            c++;
        }
    }
}

int r_gettype(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->type;
}
char* r_getname(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->name;
}
int r_gettat(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->tat;
}
int r_getatm(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->atm;
}
int r_getmon(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->mon;
}
float r_getavg(T_Record* p){

#ifdef DEBUG
	printf("DEBUG");
#endif
        return p->avg;
}

int r_count()
{
#ifdef DEBUG
	printf("DEBUG");
#endif
        return _count;
}

void r_init(){
    int i;
    for(i=0; i<MAX_MEMBERS; i++){
        if(members[i]!=NULL) {
            free(members[i]);
        }
        members[i] = NULL;
    }
    _count = 0;

#ifdef DEBUG
	printf("DEBUG");
#endif
}
char* r_to_string_save(T_Record* p){
    static char str[80];
    sprintf(str, "%s %d %d %d %d %.1f ", p->name, p->type, p->tat, p->mon, p->atm,p->avg);
   
#ifdef DEBUG
	printf("DEBUG");
#endif
 return str;
}

void r_update(T_Record* p ,int ty,  int ta, int m, int a, float  av){
    p-> type = ty;
	p->tat = ta;
    p->mon = m;
    p->atm = a;
    p->avg = av;
}

void r_delete(T_Record* p){
    int i, index;
    for(i=0; i<MAX_MEMBERS; i++)
        if(members[i]==p) {
            index=i;
            break;
        }
    free(p);
    members[index] = NULL;
    _count--;

}

int r_get_all_by_name(T_Record* a[], char* n){
    // 회원이름에 문자열이 포함된 모든 레코드 포인터의 배열 만들기    
    int i, c=0;
    for(i=0; i<MAX_MEMBERS; i++){
        if(members[i]!=NULL && strstr(members[i]->name, n)){
            a[c]=members[i];
            c++;
        }
    }
    return c;
} 

int r_get_all_by_avg(T_Record* a[], float av){
     // 입력한 평균보다 높은 평균을 가진 모든 레코드 포인터의 배열 만들기 
    int i, c=0;
    for(i=0; i<MAX_MEMBERS; i++){
        if(members[i]!=NULL &&( members[i]->avg > av) ){
            a[c]=members[i];
            c++;
        }
    }
    return c;
}



