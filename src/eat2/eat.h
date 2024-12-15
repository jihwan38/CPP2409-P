#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <ctime>
#include <sstream>
#include <map>
#include <stdexcept>
using namespace std;

class Restaurant
{
private:
    string name;
    char location;
    map<string, int> foodmenu;
    string open_time;
    string close_time;

public:
    Restaurant(string name, char location, string open_time, string close_time, map<string, int> foodmenu);

    string GetName() const;
    char GetLocation() const;
    map<string, int> GetMenu() const;
    string GetOpenTime() const;
    string GetCloseTime() const;
    void Print() const;
};

class User
{
private:
    string food_name;
    time_t selected_time;

public:
    User(string name, time_t time);
    string GetFoodName() const;
    void SetFoodName(string name);

    time_t GetSelectedTime() const;
    void SetSelectedTime(time_t time);
};

extern vector<string> food_type_list;

    
void SaveUserData(const vector<User> &user_data, const string &filename);

vector<User> LoadUserData(const string &filename);

vector<Restaurant> LoadRestaurantData(const string &filename);

void Line10Show(const vector<string> &v);

bool FindE(const vector<string> &v, const string &user_choice);

int SelectMenu();

void ShowCategory();

void RemoveRecentFoods(vector<User> &user_food);

bool FindE(const vector<User> &user_data, const string &user_choice);

void UpdateFoodSelectionTime(vector<User> &userData, const string &food_name);

vector<string> LoadData(const string &filename);

void InputUserPreferences(vector<User> &user_data, const vector<string> &food_type_list);

void RecommendRestaurant(const vector<Restaurant> &restaurants, const string &select_food);

string RecommendFood(vector<string> &food_list);