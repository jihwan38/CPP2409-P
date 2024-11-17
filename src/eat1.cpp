#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//식당 클래스 작성
class Restaurant{
private:
    string name; //식당의 이름
    char location; //식당의 위치 a. 기숙사 b.후문 c. 공대쪽문 d. 상대
    vector<string> foodmenu; //식당의 대표음식메뉴
    int distance; //대표건물에서의 거리 
public:
    
};
//사용자에게 제시할 음식 리스트
vector<string> foodTypeList =
{//더 추가 예정 or text로 만들 예정
"치킨", "짜장면", "짬뽕", "탕수육", "피자", 
"볶음밥", "김치찌개", "떡볶이", "초밥", "뼈해장국", 
"햄버거", "족발", "곱창", "삼겹살", "파스타"
};

int SelectMenu();
void ShowCategory(); 
void line5Show(vector<string> v);
bool FindE(vector<string> v, string userChoice);


int main(){
    /*
    
    
    
    텍스트 받아들이는 코드블록
    
    
    
    */
    
    srand(time(NULL));
    
    //기능1. 세부기능1. 사용자의 선호음식 조사
    vector<string> userData;
    int accesstry = 0; //UserData 텍스트에서 받아들일 예정, accesstry가 0일 경우 처음 프로그램을 실행한 것, accesstry = 1일 경우 처음 프로그램을 실행한 것이 아님
    if(accesstry == 0){
        line5Show(foodTypeList); //사용자에게 제시할 음식 리스트의 음식을 한 줄에 5개씩 출력
        
        //사용자의 선호음식 입력을 받아들이는 코드블록
        while(1){
            string userChoice;
            cout << "선호음식을 입력해주세요(입력을 다 했다면 -1을 입력해주세요)";
            cin >> userChoice;
            bool found = FindE(foodTypeList, userChoice); //제시한 음식 리스트에 사용자의 입력값이 들어있는지 확인하는 코드

            //사용자가 더 이상 입력을 원치 않는 경우
            if(userChoice == "-1"){
                break;
            }
            //사용자가 올바른 음식 입력을 한 경우
            else if(found){
                cout << userChoice << "을/를 선호음식에 추가합니다." << endl;
                userData.push_back(userChoice);
            }
            //사용자가 이상한 입력을 한 경우
            else{
                cout << "리스트에 있는 음식만 입력해주세요" << endl;
            }
        }
    }
    //userData --> 텍스트 블록
    
    //메인 화면
    while(1){
        vector<string> userData_paste = userData; //유저 데이터 텍스트에서 불러오는 것으로 바꿀 예정
        int userSelectCategory; //유저가 선택한 목록 변수
        ShowCategory(); //메인화면의 목록을 보여주는 함수
        userSelectCategory = SelectMenu(); //유저의 입력이 정수가 아닐 경우를 대비하여 SelectMenu 함수를 이용하여 입력값 받아들임
        
        //목록
        switch(userSelectCategory){
            //기능1. 세부 기능2. 선호 메뉴 추천
            case 1:{ 
                cout << "선호 메뉴 추천" << endl;
                string userSelectFood; //추천한 음식 중에서 유저가 선택한 음식을 저장할 변수
                
                //랜덤 음식 추천 코드블록
                while(1){
                    //더 이상 추천할 음식이 없는 경우
                    if(userData_paste.size() == 0){
                        cout << "더 이상 추천드릴 음식이 없습니다. 메뉴로 돌아갑니다." << endl;
                        break;
                        }
                    
                    //랜덤값 범위 --> 인덱스 범위로 조정
                    int i = rand() % userData_paste.size();
                    int select;
                    
                    //음식 추천 문구 출력
                    cout << userData_paste[i] << "는 어떠신가요?" << "0. 선택 1. 다시 추천";
                    
                    //해당 음식에 대한 사용자의 선택입력 코드블록
                    while(1){
                        select = SelectMenu(); //안전성을 위해 SelectMenu()로 입력값 받아들임
                        
                        //사용자가 해당 음식을 선택한 경우
                        if(select == 0) {
                            userSelectFood = userData_paste[i];
                            break;
                        }
                        //사용자가 다시 추천을 선택한 경우
                        else if(select == 1){
                            userData_paste.erase(userData_paste.begin() + i);
                            break;
                        }
                        //사용자가 잘못된 정수 입력을 한 경우
                        else{
                            cout << "잘못된 입력입니다. 다시 입력해주세요" << endl;
                        }
                    }
                    if(select == 0) break; //그 다음 식당 추천 기능으로 넘어가야 하지만 아직 구현 X 따라서 일단 메인화면으로 복귀
                    
                }
            }
                break;
            case 2:
                cout << "해장 메뉴 추천" << endl;
                break;
            case 3:
                cout << "선호 음식 재선택" << endl;
                break;
            case 4:
                cout << "프로그램 종료" << endl;
                return 0;
            default:
                cout << "목록에 있는 정수를 입력해주세요." << endl;
        }

    }
}


//사용자의 입력이 정수가 아닐 경우를 대비한 함수
int SelectMenu(){
    int userSelectCategory;
    while(!(cin >> userSelectCategory)){  
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "잘못된 입력입니다. 정수를 입력해주세요" << endl;
    }
    return userSelectCategory;
}
//메인화면의 목록을 보여주는 함수
void ShowCategory(){
    cout << "메인 화면" << endl;
    cout << "1. 선호 메뉴 추천" << endl;
    cout << "2. 해장 메뉴 추천" << endl;
    cout << "3. 선호 음식 재선택" << endl;
    cout << "4. 프로그램 종료" << endl;
}
//벡터 요소 5개씩 출력하는 함수
void line5Show(vector<string> v){
    int countPerLine = 5;
    int i = 0;
    for(string e : v){
        cout << e;
        if((i+1) % countPerLine == 0) {
            cout << endl;
        }
        else{
            cout << " ";
        }
        i++;
    }
    cout << endl;
}
//벡터에서 사용자의 입력 음식을 찾을 경우 true를 반환하는 함수
bool FindE(vector<string> v, string userChoice){
    for (string e : foodTypeList){
        if(e == userChoice){
            return true;
                }
            }
    return false;
}
 