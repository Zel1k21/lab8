#include <iostream>
#include <string>
#include <vector>
#include <locale>
#include <cctype>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <iomanip>

template <class T>
void printVector(std::vector<T>);

void task1() {
	std::cout << "Задание 1:" << std::endl;
	std::string line, firstSentence, lastSentence;
	std::getline(std::cin, line);
	const size_t pointer = line.find('.', 0), firstLetter = line.find_first_not_of(' '), lastLetter = line.find_last_not_of(' ');
	firstSentence = line.substr(firstLetter, pointer);
	lastSentence = line.substr(pointer + 2, lastLetter);
	std::swap(firstSentence[0], lastSentence[0]);
	line = firstSentence + ' ' + lastSentence;
	std::cout << line << std::endl << std::endl;
}

void task2() {
	std::cout << "Задание 2: " << std::endl;
	std::string line, newLine;
	std::getline(std::cin, line);
	for (const char letter : line)
		if (isalpha(letter) || isdigit(letter))
			newLine.push_back(letter);
	std::cout << newLine << std::endl << std::endl;
}

void task3() {
	std::cout << "Задание 3: " << std::endl;
	std::ifstream inStream("in.txt");
	std::ofstream outStream("out.txt");
	std::string line;
	while (std::getline(inStream, line))
		if (line.find('"') != -1)
			outStream << line << std::endl;
}

void task4() {
	std::cout << "Задание 4: " << std::endl;
	std::string line = " ";
	std::vector<std::string> array;
	while(line != "\0") {
		std::getline(std::cin, line);
		array.push_back(line);
	}
	array.erase(array.end() - 1);
	printVector(array);
	std::cout << std::endl;
	array.erase(array.begin() + 2);
	printVector(array);
}

template <class T>
void printVector(std::vector<T> array) {
	for (int i = 0; i < array.size(); i++)
		std::cout << i + 1 << ". " << array[i] << std::endl;
}


class Date {
private:
	int day;
	int month;
	int year;
public:
	Date() : day(01), month(01), year(1970) {};
	Date(int d, int m, int y) : day(d), month(m), year(y) {};
	friend std::ostream& operator << (std::ostream&, const Date&);
	friend bool operator < (const Date&, const Date&);
};

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	if (date.day < 10)
		out << '0';
	std::cout << date.day << '.';
	if (date.month < 10)
		out << '0';
	out << date.month << '.' << date.year;
	return out;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.year < rhs.year)
		return true;
	if (lhs.year == rhs.year && (lhs.month < rhs.month || (lhs.month == rhs.month && lhs.day << rhs.day)))
		return true;
	return false;
}

void task5() {
	std::cout << "Задани 5: " << std::endl;
	const std::vector<Date> dates{ {1,2,1963}, {14,7,1995}, {7,12,2088}, {5,3,2030}, {24,9,2013}, {19,9,2020} };
	printVector(dates);
	Date todayDate(20, 05, 2024);
	std::vector<Date> futureDates;
	for (int i = 0; i < dates.size(); i++)
		if (todayDate < dates[i])
			futureDates.push_back(dates[i]);
	std::cout << std::endl;
	printVector(futureDates);
}

template <class T>
void printList(const std::list<T> list) {
	auto iter = list.begin();
	for (int i = 0; i < list.size(); i++) {
		std::cout << i + 1 << ". " << *iter;
		iter++;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void task6() {
	std::cout << "Задание 6: " << std::endl;
	std::string line;
	std::list<std::string> array;
	do {
		std::getline(std::cin, line);
		array.push_back(line);
	} while (line != "");
	array.pop_back();
	printList(array);
	std::cout << std::endl;
	auto i = array.begin();
	std::advance(i, 2);
	array.erase(i);
	printList(array);
}

class Time {
private:
	int seconds;
	int minutes;
	int hours;
public:
	Time() : seconds(0), minutes(0), hours(0) {};
	Time(int h, int m, int s);
	friend bool operator < (const Time&, const Time&);
	friend std::ostream& operator << (std::ostream&, const Time&);
};

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s)
{
	if (seconds > 60) {
		minutes += seconds / 60;
		seconds %= 60;
	}
	if (minutes > 60) {
		hours += minutes / 60;
		minutes %= 60;
	}
}

bool operator<(const Time& lhs, const Time& rhs)
{
	if (lhs.hours < rhs.hours)
		return true;
	if (lhs.hours == rhs.hours && (lhs.minutes < rhs.minutes || (lhs.minutes == rhs.minutes && lhs.seconds << rhs.seconds)))
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& out, const Time& time)
{
	out << time.hours << ':' << time.minutes << ':' << time.seconds;
	return out;
}

void task7() {
	std::cout << "Задани 7: " << std::endl;
	const std::list<Time> times{ {1,2,63}, {14,57,19}, {7,32,20}, {5,13,23}, {10,19,45}, {19,9,59} };
	printList(times);
	Time Night(6, 0, 0);
	std::list<Time> notNight;
	auto iter = times.begin();
	for (int i = 0; i < times.size(); i++) {
		if (*iter < Night)
			notNight.push_back(*iter);
		iter++;
	}
	printList(notNight);
}

void task8() {
	std::cout << "Задание 8: " << std::endl;
	std::map<std::string, int> Inventory = { {"Отвертка", 0}, {"Молоток", 10}, {"Гайки", 100}, {"Профиль", 0}, {"Уголок", 9},
	{"Доска", 17} };
	for (auto& x : Inventory)
		if (x.second > 0)
			std::cout << x.first << ": " << x.second << std::endl;
	std::cout << std::endl;
}

void task9() {
	std::cout << "Задание 9: " << std::endl;
	std::map<std::string, int> school = { {"1а", 21}, {"1б", 20}, {"2", 25}, {"3а", 20}, {"3б", 23}, {"4а", 25}, {"4б", 25},
		{"5а", 26}, {"5б", 25}, {"6a", 19}, {"6б", 18}, {"7а", 26}, {"7б", 25}, {"8", 25}, {"9", 17}, {"10", 15}, {"11", 14}};
	int sum = 0;
	for (auto& x : school) {
		sum += x.second;
		std::cout << std::setw(2) << x.first << ": " << x.second << std::endl;
	}
	std::cout << "Всего в школе " << sum << " учеников";
}

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	//task1();
	//task2();
	//task3();
	//task4();
	//task5();
	//task6();
	//task7();
	//task8();
	task9();
	return 0;
}