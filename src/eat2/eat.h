#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <ctime>
#include <sstream>
using namespace std;

class Restaurant{
private:
    string name;
    char location;
    float rating;
    vector<string> foodmenu;
public:
    Restaurant(string name, char location, float rating, vector<string> foodmenu);

    string GetName() const;
    char GetLocation() const;
    float GetRating() const;
    vector<string> GetMenu() const;

    string toString() const;

    void Print() const;

};

class User{
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
extern vector<string> hangover_food_list;


void SaveUserData(const vector<User>& user_data, const string& filename);

vector<User> LoadUserData(const string& filename);

vector<Restaurant> LoadRestaurantData(const string& filename);

void Line5Show(const vector<string>& v);

bool FindE(const vector<string>& v, const string& user_choice);

int SelectMenu();

void ShowCategory();

void RemoveRecentFoods(vector<User>& user_food);

bool FindE(const vector<User>& user_data, const string& user_choice);

void UpdateFoodSelectionTime(vector<User>& userData, const string& food_name);

vector<string> LoadData(const string& filename);

void InputUserPreferences(vector<User>& user_data, const vector<string>& food_type_list);