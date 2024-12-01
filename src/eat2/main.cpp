#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <ctime>
#include <sstream>
#include "eat.h"
using namespace std;



// 메인 함수
int main() {
    string user_file = "user_data.txt";
    string restaurant_file = "restaurant_data.txt";

    // 사용자 데이터 불러오기
    vector<User> user_data = LoadUserData(user_file);

    if (user_data.empty()) {
        cout << "사용자 선호 음식 데이터가 없습니다. 새로 입력해주세요." << endl;
        InputUserPreferences(user_data, food_type_list);
        SaveUserData(user_data, user_file);
    }
    
    // 식당 데이터 불러오기
    vector<Restaurant> restaurants = LoadRestaurantData(restaurant_file);

    srand(time(nullptr));
    
    // 메인 메뉴
    while (true) {
        ShowCategory();
        int userSelectCategory = SelectMenu();

        switch (userSelectCategory) {
            case 1: {
                cout << "선호 메뉴 추천" << endl;

                // 사용자 선호 메뉴 데이터에서 랜덤으로 추천
                vector<User> user_data_paste = user_data;  // 복사본

                RemoveRecentFoods(user_data_paste);

                while (!user_data_paste.empty()) {
                    // 랜덤 인덱스 생성
                    int random_index = rand() % user_data_paste.size();
                    string recommended_food = user_data_paste[random_index].GetFoodName();

                    // 사용자에게 추천
                    cout << "추천 메뉴: " << recommended_food << endl;
                    cout << "이 메뉴를 선택하시겠습니까? (0: 선택, 1: 다시 추천): ";
                    int choice;
                    choice = SelectMenu();  // 안전 입력 처리

                    if (choice == 0) {
                        cout << recommended_food << "을(를) 선택하셨습니다!" << endl;
                        UpdateFoodSelectionTime(user_data, recommended_food);
                        SaveUserData(user_data, user_file);
                        break;  // 선택 완료 후 종료
                    } else if (choice == 1) {
                        user_data_paste.erase(user_data_paste.begin() + random_index);  // 이미 추천된 메뉴는 제외
                    } else {
                        cout << "잘못된 입력입니다. 다시 시도해주세요." << endl;
                    }
                }

                if (user_data_paste.empty()) {
                    cout << "추천할 메뉴가 더 이상 없습니다. 메뉴로 돌아갑니다." << endl;
                }
                break;
            }
            case 2:
                // 해장 메뉴 추천
                break;
            case 3:
                // 선호 음식 재선택
                user_data.clear();
                cout << "선호 음식을 다시 입력해주세요." << endl;
                InputUserPreferences(user_data, food_type_list);
                SaveUserData(user_data, user_file);
                break;
            case 4:
                cout << "프로그램을 종료합니다." << endl;
                return 0;
            default:
                cout << "목록에 있는 정수를 입력해주세요." << endl;
        }
    }
}