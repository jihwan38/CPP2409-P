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

Restaurant::Restaurant(string name, char location, float rating, vector<string> foodmenu)        
: name(name), location(location), rating(rating), foodmenu(foodmenu) {}



vector<string> food_type_list = LoadData("food_data.txt");



string Restaurant::GetName() const {return name;}
char Restaurant::GetLocation() const {return location;}
float Restaurant::GetRating() const {return rating;}
vector<string> Restaurant::GetMenu() const {return foodmenu;}

string Restaurant::toString() const {
    stringstream ss;
    ss << name << "/" << location << "/" << rating;
    for (const auto& food : foodmenu){
        ss << "/" << food;
    }
    return ss.str();
}

void Restaurant::Print() const {
    cout << "식당 이름: " << name << endl;
    cout << "위치: ";
    switch (location) {
        case 'a': cout << "기숙사"; break;
        case 'b': cout << "후문"; break;
        case 'c': cout << "공대쪽문"; break;
        case 'd': cout << "상대"; break;
        default: cout << "알 수 없음";
    }
    cout << endl;
    cout << "평점: " << rating << endl;
    cout << "대표 음식: ";
    for (const auto& food : foodmenu) {
        cout << food << " ";
    }
    cout << endl << "----------------------" << endl;
}







vector<Restaurant> LoadRestaurantData(const string& filename) {
    vector<Restaurant> restaurants;
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string name, location_str, rating_str, menu_item;
            vector<string> foodmenu;

            // 1. 식당 이름
            getline(ss, name, '/');

            // 2. 위치
            getline(ss, location_str, '/');
            char location = location_str[0];

            // 3. 평점
            getline(ss, rating_str, '/');
            float rating = stof(rating_str);

            // 4. 음식 메뉴
            while (getline(ss, menu_item, '/')) {
                foodmenu.push_back(menu_item);
            }

            // 식당 객체 생성 및 벡터에 추가
            restaurants.emplace_back(name, location, rating, foodmenu);
        }
        inFile.close();
    } else {
        cout << "식당 데이터를 불러오는 데 실패했습니다: " << filename << endl;
    }
    return restaurants;
}

void Line5Show(const vector<string>& v) {
    int countPerLine = 5;
    int i = 0;
    for (const auto& e : v) {
        cout << e;
        if ((i + 1) % countPerLine == 0) {
            cout << endl;
        } else {
            cout << " ";
        }
        i++;
    }
    cout << endl;
}

bool FindE(const vector<string>& v, const string& user_choice) {
    for (const auto& e : v) {
        if (e == user_choice) {
            return true;
        }
    }
    return false;
}

int SelectMenu() {
    int userSelectCategory;
    while (!(cin >> userSelectCategory)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "잘못된 입력입니다. 정수를 입력해주세요." << endl;
    }
    return userSelectCategory;
}

void ShowCategory() {
    cout << "메인 화면" << endl;
    cout << "1. 선호 메뉴 추천" << endl;
    cout << "2. 해장 메뉴 추천" << endl;
    cout << "3. 선호 음식 재선택" << endl;
    cout << "4. 프로그램 종료" << endl;
}

void RemoveRecentFoods(vector<User>& user_foods) {
    time_t now = time(0);

    // 인덱스를 사용하여 벡터 순회
    for (size_t i = 0; i < user_foods.size(); ) {
        if (now - user_foods[i].GetSelectedTime() < 2 * 24 * 60 * 60) {
            user_foods.erase(user_foods.begin() + i); // 해당 원소 삭제
        } else {
            ++i; // 삭제되지 않은 원소는 인덱스 증가
        }
    }
}

User::User(string name, time_t time)
: food_name(name), selected_time(time) {}
string User::GetFoodName() const{
    return food_name;
}
void User::SetFoodName(string name){
    food_name = name;
}

time_t User::GetSelectedTime() const{
    return selected_time;
}
void User::SetSelectedTime(time_t time){
    selected_time = time;
}

vector<User> LoadUserData(const string& filename){
    vector<User> user_data;
    ifstream inFile(filename);
    if(inFile.is_open()){
        string food_name;
        time_t selected_time;
        while (inFile >> food_name >> selected_time) {
            user_data.emplace_back(food_name, selected_time);  // 생성자 사용
        }
        inFile.close();
    } else {
        cout << "사용자 데이터를 불러오는 데 실패했습니다." << endl;
    }
    return user_data;
}

void SaveUserData(const vector<User>& user_data, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& user_food : user_data) {
            outFile << user_food.GetFoodName() << " " 
                    << user_food.GetSelectedTime() << endl;
        }
        outFile.close();
    } else {
        cout << "사용자 데이터를 저장하는 데 실패했습니다: " << filename << endl;
    }
}

bool FindE(const vector<User>& v, const string& user_choice) {
    for (const auto& e : v) {
        if (e.GetFoodName() == user_choice) {
            return true;
        }
    }
    return false;
}

void UpdateFoodSelectionTime(vector<User>& user_data, const string& food_name) {
    time_t now = time(0);  // 현재 시간
    for (auto& food : user_data) {
        if (food.GetFoodName() == food_name) {
            food.SetSelectedTime(now);  // 선택한 음식의 시간을 현재 시간으로 변경
            cout << "선택한 음식 '" << food_name << "'의 선택 시간이 업데이트되었습니다." << endl;
            break;
        }
    }
}

vector<string> LoadData(const string& filename){
    vector<string> food_data;
    ifstream inFile(filename);
    if(inFile.is_open()){
        string food_name;
        while (inFile >> food_name) {
            food_data.push_back(food_name);
        }
        inFile.close();
    } else {
        cout << "사용자 데이터를 불러오는 데 실패했습니다." << endl;
    }
    return food_data;    
}

void InputUserPreferences(vector<User>& user_data, const vector<string>& food_type_list) {
    Line5Show(food_type_list);

    while (true) {
        string user_choice;
        cout << "선호 음식을 입력해주세요(입력을 다 했다면 -1을 입력): ";
        cin >> user_choice;

        if (user_choice == "-1") break;

        if (FindE(food_type_list, user_choice)) {
            if (FindE(user_data, user_choice)) {  // 중복 확인
                cout << "이미 선호 음식에 추가된 항목입니다. 다시 입력해주세요." << std::endl;
            } else {
                cout << user_choice << "을/를 선호 음식에 추가합니다." << std::endl;
                user_data.push_back(User(user_choice, time(nullptr) - (3 * 24 * 60 * 60)));
            }
        } else {
            cout << "리스트에 있는 음식만 입력해주세요." << std::endl;
        }
    }
}
