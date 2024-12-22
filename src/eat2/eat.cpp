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

Restaurant::Restaurant(string name, char location, string open_time, string close_time, map<string, int> foodmenu)
    : name(name), location(location), open_time(open_time), close_time(close_time), foodmenu(foodmenu) {}

vector<string> food_type_list = LoadData("food_data.txt");

string Restaurant::GetName() const { return name; }
char Restaurant::GetLocation() const { return location; }
map<string, int> Restaurant::GetMenu() const { return foodmenu; }

void Restaurant::Print() const
{
    cout << "식당 이름: " << name << endl;
    cout << "위치: ";
    switch (location)
    {
    case 'a':
        cout << "정문";
        break;
    case 'b':
        cout << "후문";
        break;
    case 'c':
        cout << "상대";
        break;
    default:
        cout << "알 수 없음";
    }
    cout << endl;
    cout << "영업시간: " << open_time << " - " << close_time << endl;

    cout << "대표 음식: " << endl;

    for (const auto &it : foodmenu)
    {
        cout << "- " << it.first << " (" << it.second << "원)" << endl;
    }
}

vector<Restaurant> LoadRestaurantData(const string &filename)
{
    vector<Restaurant> restaurants;

    try
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            throw runtime_error("식당 데이터를 불러오는 데 실패했습니다: " + filename);
        }

        string line;
        while (getline(inFile, line))
        {
            try
            {
                stringstream ss(line);
                string name, location_str, rating_str, menu_item, hours_str;
                map<string, int> foodmenu;

                // 1. 식당 이름
                if (!getline(ss, name, '/'))
                    throw runtime_error("식당 이름이 누락되었습니다.");

                // 2. 위치
                if (!getline(ss, location_str, '/'))
                    throw runtime_error("위치 데이터가 누락되었습니다.");
                char location = location_str[0];

                if (!getline(ss, hours_str, '/'))
                    throw runtime_error("영업시간 데이터가 누락되었습니다.");
                int bar_index = hours_str.find('-');
                if (bar_index == string::npos)
                    throw runtime_error("잘못된 영업시간 형식: " + hours_str);
                string open_time = hours_str.substr(0, bar_index);   // 시작 시간
                string close_time = hours_str.substr(bar_index + 1); // 종료 시간

                // 3. 음식 메뉴
                while (getline(ss, menu_item, '/'))
                {
                    int start_index = menu_item.find('(');
                    int end_index = menu_item.find(')');
                    if (start_index != string::npos && end_index != string::npos)
                    {
                        string food_name = menu_item.substr(0, start_index);
                        int price = stoi(menu_item.substr(start_index + 1, end_index - start_index - 1));
                        foodmenu[food_name] = price;
                    }
                    else
                    {
                        throw runtime_error("잘못된 데이터 형식: " + menu_item);
                    }
                }

                // 식당 객체 생성 및 벡터에 추가
                restaurants.emplace_back(name, location, open_time, close_time, foodmenu);
            }
            catch (const exception &e)
            {
                cerr << "한 줄 처리 중 오류 발생: " << e.what() << endl;
            }
        }

        inFile.close();
    }
    catch (const exception &e)
    {
        cerr << "파일 처리 중 오류 발생: " << e.what() << endl;
    }

    return restaurants;
}

void Line10Show(const vector<string> &v)
{
    int countPerLine = 10;
    int i = 0;
    for (const auto &e : v)
    {
        cout << e;
        if ((i + 1) % countPerLine == 0)
        {
            cout << endl;
        }
        else
        {
            cout << " ";
        }
        i++;
    }
    cout << endl;
}

bool FindE(const vector<string> &v, const string &user_choice)
{
    for (const auto &e : v)
    {
        if (e == user_choice)
        {
            return true;
        }
    }
    return false;
}

int SelectMenu()
{
    int userSelectCategory;
    while (!(cin >> userSelectCategory))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "잘못된 입력입니다. 정수를 입력해주세요: ";
    }
    return userSelectCategory;
}

void ShowCategory()
{
    cout << "전남대 학생을 위한 밥 추천 프로그램 :)" << endl;
    cout << "1. 선호 메뉴 추천" << endl;
    cout << "2. 해장 메뉴 추천" << endl;
    cout << "3. 선호 음식 재선택" << endl;
    cout << "4. 프로그램 종료" << endl;
}

void RemoveRecentFoods(vector<User> &user_foods)
{
    time_t now = time(0);

    // 인덱스를 사용하여 벡터 순회
    for (size_t i = 0; i < user_foods.size();)
    {
        if (now - user_foods[i].GetSelectedTime() < 2 * 24 * 60 * 60)
        {
            user_foods.erase(user_foods.begin() + i); // 해당 원소 삭제
        }
        else
        {
            ++i; // 삭제되지 않은 원소는 인덱스 증가
        }
    }
}

User::User(string name, time_t time)
    : food_name(name), selected_time(time) {}
string User::GetFoodName() const
{
    return food_name;
}
void User::SetFoodName(string name)
{
    food_name = name;
}

time_t User::GetSelectedTime() const
{
    return selected_time;
}
void User::SetSelectedTime(time_t time)
{
    selected_time = time;
}

vector<User> LoadUserData(const string &filename)
{
    vector<User> user_data;

    try
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            throw runtime_error("파일 열기 실패: " + filename);
        }

        string food_name;
        time_t selected_time;

        while (inFile >> food_name >> selected_time)
        {
            try
            {
                if (food_name.empty())
                {
                    throw invalid_argument("잘못된 데이터: 음식 이름이 비어 있습니다.");
                }

                if (selected_time < 0)
                {
                    throw invalid_argument("잘못된 데이터: 선택 시간이 음수입니다.");
                }

                user_data.emplace_back(food_name, selected_time); // User 객체 생성 및 벡터에 추가
            }
            catch (const invalid_argument &e)
            {
                cerr << "데이터 오류: " << e.what() << " (음식: " << food_name << ", 시간: " << selected_time << ")" << endl;
            }
        }

        inFile.close();
    }
    catch (const exception &e)
    {
        cerr << "사용자 데이터를 불러오는 중 오류 발생: " << e.what() << endl;
    }

    return user_data;
}

void SaveUserData(const vector<User> &user_data, const string &filename)
{
    ofstream outFile(filename);
    if (outFile.is_open())
    {
        for (const auto &user_food : user_data)
        {
            outFile << user_food.GetFoodName() << " "
                    << user_food.GetSelectedTime() << endl;
        }
        outFile.close();
        cout << "사용자 데이터 저장을 완료했습니다." << endl;
    }
    else
    {
        cerr << "사용자 데이터를 저장하는 데 실패했습니다: " << filename << endl;
    }
}

bool FindE(const vector<User> &v, const string &user_choice)
{
    for (const auto &e : v)
    {
        if (e.GetFoodName() == user_choice)
        {
            return true;
        }
    }
    return false;
}

void UpdateFoodSelectionTime(vector<User> &user_data, const string &food_name)
{
    time_t now = time(0); // 현재 시간
    for (auto &food : user_data)
    {
        if (food.GetFoodName() == food_name)
        {
            food.SetSelectedTime(now); // 선택한 음식의 시간을 현재 시간으로 변경
            cout << "선택한 음식 '" << food_name << "'의 선택 시간이 업데이트되었습니다." << endl;
            break;
        }
    }
}

vector<string> LoadData(const string &filename)
{
    vector<string> food_data;

    try
    {
        ifstream inFile(filename);
        if (!inFile.is_open())
        {
            throw runtime_error("파일 열기 실패: " + filename);
        }

        string food_name;
        while (inFile >> food_name)
        {
            try
            {
                if (food_name.empty())
                {
                    throw invalid_argument("잘못된 데이터: 음식 이름이 비어 있습니다.");
                }

                food_data.push_back(food_name); // 유효한 데이터 추가
            }
            catch (const invalid_argument &e)
            {
                cerr << "데이터 오류: " << e.what() << " (음식: " << food_name << ")" << endl;
            }
        }

        inFile.close();
    }
    catch (const exception &e)
    {
        cerr << "데이터를 불러오는 중 오류 발생: " << e.what() << endl;
    }

    return food_data;
}

void InputUserPreferences(vector<User> &user_data, const vector<string> &food_type_list)
{
    Line10Show(food_type_list);

    while (true)
    {
        string user_choice;
        cout << "선호 음식을 입력해주세요(입력을 다 했다면 -1을 입력): ";
        cin >> user_choice;

        if (user_choice == "-1")
        {
            if (!user_data.empty())
            {
                break;
            }
            else
            {
                cout << "음식을 하나 이상 입력해주세요. ^^" << endl;
            }
        }
        else
        {

            if (FindE(food_type_list, user_choice))
            {
                if (FindE(user_data, user_choice))
                { // 중복 확인
                    cout << "이미 선호 음식에 추가된 항목입니다. 다시 입력해주세요." << std::endl;
                }
                else
                {
                    cout << user_choice << "을/를 선호 음식에 추가합니다." << std::endl;
                    user_data.push_back(User(user_choice, time(nullptr) - (3 * 24 * 60 * 60)));
                }
            }
            else
            {
                cout << "리스트에 있는 음식만 입력해주세요." << std::endl;
            }
        }
    }
}

void RecommendRestaurant(const vector<Restaurant> &restaurants, const string &select_food)
{

    cout << "식당 추천" << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;

    // 사용자 위치 입력
    char user_location;
    cout << "현재 위치를 입력해주세요 (a: 정문, b: 후문, c: 상대): ";
    while (true)
    {
        cin >> user_location;
        if (user_location == 'a' || user_location == 'b' || user_location == 'c')
        {
            break; // 올바른 입력이면 루프 종료
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 입력해주세요 (a, b, c): ";
        }
    }

    cout << "---------------------------------------------------------------------------------------" << endl;

    // 사용자의 위치와 음식에 맞는 식당 필터링
    vector<Restaurant> filtered_restaurants;
    for (const auto &restaurant : restaurants)
    {
        if (restaurant.GetLocation() == user_location)
        {
            const auto &menu = restaurant.GetMenu();
            if (menu.find(select_food) != menu.end())
            { // 음식 이름이 메뉴에 존재하면
                filtered_restaurants.push_back(restaurant);
            }
        }
    }

    // 식당 추천 로직
    while (!filtered_restaurants.empty())
    {
        int random_index = rand() % filtered_restaurants.size();
        const auto &recommended_restaurant = filtered_restaurants[random_index];

        recommended_restaurant.Print();
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << "이 식당을 선택하시겠습니까? (0: 선택, 1: 다시 추천): ";

        int choice = SelectMenu();

        if (choice == 0)
        {
            cout << recommended_restaurant.GetName() << "을(를) 선택하셨습니다!" << endl;
            return; // 추천 완료
        }
        else if (choice == 1)
        {
            filtered_restaurants.erase(filtered_restaurants.begin() + random_index); // 이미 추천된 식당 제외
        }
        else
        {
            cout << "잘못된 입력입니다. 다시 시도해주세요.";
        }
    }

    if (filtered_restaurants.empty())
    {
        cout << "추천할 식당이 더 이상 없습니다. 메뉴로 돌아갑니다." << endl;
    }
}

string RecommendFood(vector<string> &food_list)
{
    string selected_food;

    while (!food_list.empty())
    {
        int random_index = rand() % food_list.size();
        string recommended_food = food_list[random_index];
        cout << "---------------------------------------------------------------------------------------" << endl;
        cout << "추천 메뉴: " << recommended_food << endl;
        cout << "이 메뉴를 선택하시겠습니까? (0: 선택, 1: 다시 추천): ";
        int choice;
        while (true)
        {
            choice = SelectMenu(); // 안전 입력 처리
            if (choice == 0)
            {

                cout << recommended_food << "을(를) 선택하셨습니다!" << endl;
                selected_food = recommended_food;
                break; // 선택 완료 후 종료
            }
            else if (choice == 1)
            {
                food_list.erase(food_list.begin() + random_index); // 이미 추천된 메뉴 제외
                break;
            }
            else
            {
                cout << "잘못된 입력입니다. 0이나 1을 입력해주세요: ";
            }
        }

        if (choice == 0) //입력문 나감
            break;
    }

    if (food_list.empty())
    {
        cout << "추천할 메뉴가 더 이상 없습니다. 메뉴로 돌아갑니다." << endl;
    }

    return selected_food;
}