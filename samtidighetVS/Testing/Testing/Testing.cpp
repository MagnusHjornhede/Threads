/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
//using namespace std;
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "Testing.h"

class Account {
public:
	std::string name{ "Account" };
	double balance{ 0.0 };

	bool deposit(double);
	bool withdraw(double);

	std::string getName() {
		return name;
	}

};

class Player {
public:
	std::string name{ "Player" };
	int health{ 100 };
	int xp{ 3 };

	void talk(std::string text_to_say) { std::cout << name << " Says " << text_to_say << std::endl; };
	bool is_dead();

	Player();
	Player(std::string name_val);
	Player(std::string, int health_val, int xp_val);
	
	std::string getName()  { return name; };
	int getHealth() { return health; }
	int getXp() { return xp; }

	// Copy constructor
	Player(const Player &source);
	//Destructor
	~Player() { std::cout << "Destructor called for: " << name << std::endl; }
};











int main()
{

	Account franc_account;
	//Account jim_account;

	Player frank;
	Player hero;
	Player testArgs{ "TestArgs" };

	frank.name = "Frank";
	frank.health = 100;
	frank.xp = 12;


	Player *enemy{ nullptr };

	delete enemy;

	std::cout<< franc_account.getName()<<std::endl;

	return 0;
}

bool Player::is_dead()
{
	return health<0;
}

Player::Player():Player{"None", 1,4}
{
	std::cout << "Zero arg constructor" << std::endl;
}

Player::Player(std::string name_val):Player{name_val,0,0}
{
	std::cout << "One arg constructor" << std::endl;
}

Player::Player(std::string name_val, int health_val, int xp_val) : name{ name_val }, health{ health_val },xp{xp_val}
{
	name = name_val;
	
	std::cout << "Three arg constructor" << std::endl;

}

Player::Player(const Player & source) : name(source.name),health(source.health),xp(source.xp)
{
	std::cout << "Copy construct- made a copy of "+ source.name << std::endl;
}

void display_player(Player p) {
	std::cout << "Name: " << p.getName() << std::endl;
	std::cout << "Health: " << p.getHealth() << std::endl;
	std::cout << "Xp: " << p.getXp() << std::endl;
}