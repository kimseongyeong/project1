#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 1000


typedef  struct _rest{
        int type; // 한식,중식,양식,일식 구분
        char name[100]; //식당 이름
        int  tat; //맛0~5 사이 입력
        int mon;//가성비 0~5 사이 입력
        int atm; // 분위기 0~5 사이 입력
        float avg; //맛+ 분위기+ 가성비 의 평균
} T_Record;


int r_is_available();       // 현재 추가할 수 있는 데이터 공간이 있는가?
//Create
int r_first_available();// 추가 할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
void r_create(int t, char*n, int ta , int m, int a , float avg); // 신규 레코드 >추가
//Read
T_Record* r_search_by_name(char *n); //타입이 일치하는 맛집 레코드 포인터 찾기
char* r_to_string(T_Record* p); // 특정 레코드의 내용을 문자열로 가져오기
int  r_gettype(T_Record* p); // 특정  레코드의 타입 가져오기
char* r_getname(T_Record* p);   // 특정  레코드의 이름 가져오기
int r_gettat(T_Record* p);  // 특정  레코드의 맛 정보 가져오기
int r_getmon(T_Record* p);// 특정  레코드의 가성비 정보 가져오기
int r_getatm(T_Record* p);// 특정  레코드의 분위기 정보 가져오기
float r_getavg(T_Record* p);   // 특정 레코드의 평균 가져오기

//List
void r_get_all(T_Record* a[]);  // 회원정보가 들어있는 모든 레코드 포인터의 배열을 만들기
int r_count();  // 현재 저장된 회원 레코드의 갯수 가져오기
void r_init(); // 모든 레코드

//File
char* r_to_string_save(T_Record* p); // 특정 회원 레코드의 내용을 파일저장용 문자열로 가져오기
int r_is_available();       // 현재 추가할 수 있는 데이터 공간이 있는가?

 void r_update(T_Record* p,int ty,  int ta, int m, int a, float  av);
int r_get_all_by_type(T_Record* a[], int ty);  // 회원이름에 문자열이 포함된 모든 레코드 포인터의 배열 만들기 
int r_get_all_by_avg(T_Record* a[], float  av);  // 회원거주도시가 문자열과 일치하는 모든 레코드 포인터의 배열 만들기 
void r_delete(T_Record* p);     // 특정 회원 레코드의 회원정보 제거
T_Record * r_search_by_avg(float avg);//특정 평균이하를 가진 레코드를 찾는다.
void r_sort();// 평균순으로 정렬해주는 함수
void r_optimize();// 조각모음 해주는  함수
