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
#include <map>
#include <stdexcept>
using namespace std;

int main() //메인함수
{
    try
    {
        string user_file = "user_data.txt";
        string restaurant_file = "restaurant_data.txt";
        string hangover_file = "hang_over.txt";
        
        // 사용자 데이터 불러오기
        vector<User> user_data = LoadUserData(user_file); 

        //선호도 조사1
        if (user_data.empty())
        {
            cout << "---------------------------------------------------------------------------------------" << endl;
            cout << "반갑습니다 :)" << endl;
            cout << "전남대 학생을 위한 밥 추천 프로그램입니다. 리스트를 보고 선호하는 음식을 입력해주세요." << endl;
            cout << "---------------------------------------------------------------------------------------" << endl;
            InputUserPreferences(user_data, food_type_list); //선호도 조사
            SaveUserData(user_data, user_file); //사용자 데이터 user_file에 저장
        }

        // 식당 데이터 불러오기X
        vector<Restaurant> restaurants = LoadRestaurantData(restaurant_file);

        srand(time(nullptr));

        // 메인 메뉴
        while (true)
        {
            cout << "---------------------------------------------------------------------------------------" << endl;
            ShowCategory(); //목록 제시
            cout << "---------------------------------------------------------------------------------------" << endl;
            cout << "수를 입력하세요.(1, 2, 3, 4): ";

            int user_select_category = SelectMenu(); //SelectMenu()를 통해 안전하게 정수를 입력받기
            cout << "---------------------------------------------------------------------------------------" << endl;
            switch (user_select_category)
            {
            case 1: //사용자 입력: 1
            {
                cout << "선호 메뉴 추천" << endl;

                // 사용자 선호 메뉴 데이터에서 랜덤으로 추천
                vector<User> user_data_paste = user_data; // 복사본
                string select_food; //사용자가 선택한 음식
                RemoveRecentFoods(user_data_paste);

                // 유저 벡터의 음식들 --> string 벡터로 변환
                vector<string> user_food_list;
                for (const auto &user : user_data_paste)
                {
                    user_food_list.push_back(user.GetFoodName());
                }

                select_food = RecommendFood(user_food_list); //사용자에게 음식 추천 --> 사용자가 고른 음식 반환

                if (!select_food.empty()) //사용자가 음식을 골랐을 경우
                {
                    UpdateFoodSelectionTime(user_data, select_food); //해당 음식 시간 정보 업데이트
                    SaveUserData(user_data, user_file); //사용자 데이터 user_file에 저장
                    cout << "---------------------------------------------------------------------------------------" << endl;
                    RecommendRestaurant(restaurants, select_food); //식당 추천
                }
            }

            break; // case문 break

            case 2:
            {
                vector<string> hang_over_item = LoadData(hangover_file);
                string select_food;
                cout << "해장 메뉴 추천" << endl;

                select_food = RecommendFood(hang_over_item);

                cout << "---------------------------------------------------------------------------------------" << endl;

                if (!select_food.empty())
                {
                    RecommendRestaurant(restaurants, select_food);
                }
            }
            break; // case문 break

            case 3:
                // 선호 음식 재선택(선호도 조사2)
                user_data.clear(); //사용자 데이터 clear
                cout << "선호 음식 재선택" << endl;
                cout << "---------------------------------------------------------------------------------------" << endl;
                cout << "선호 음식을 다시 입력해주세요." << endl;
                InputUserPreferences(user_data, food_type_list); //선호도 조사
                SaveUserData(user_data, user_file); //사용자 데이터 user_file에 저장
                break;
            case 4:
                cout << "프로그램을 종료합니다." << endl;
                return 0;
            default:
                cout << "목록에 있는 정수를 입력해주세요." << endl;
            }
        }
    }
    catch (const exception &e)
    {
        cerr << "실행 중 에러 발생" << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cerr << "에러 발생" << endl;
        return 1;
    }
}
