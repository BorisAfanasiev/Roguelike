#pragma once
#include <cassert>
#include <iostream>
#include <string>

class Creature
{
protected:
	std::string m_name;
	char m_symbol;
	int m_health;
	int m_damage;
	int m_gold;
public:
	Creature(const std::string& name, char symbol, int health, int damage, int gold)
		: m_name{ name }, m_symbol{ symbol }, m_health{ health }, m_damage{ damage }, m_gold{ gold } {}

	const std::string& getName() { return m_name; }
	const char getSymbol() { return m_symbol; }
	const int getHealth() { return m_health; }
	const int getDamage() { return m_damage; }
	const int getGold() { return m_gold; }

	void reduceHealth(int damage) { m_health -= damage; }
	bool isDead() { return (m_health <= 0); }
	void addGold(int amount) { m_gold += amount; }
};

class Player : public Creature
{
protected:
	int m_level = 1;
public:
	Player(const std::string& name) : Creature(name, '@', 10, 1, 0) {}

	const int getLevel() { return m_level; }

	void levelUp() { m_level++; m_damage++; }
	bool isWon() { return (m_level >= 20); }
	void reset() { m_level = 1; m_health = 10; m_damage = 1; m_gold = 0; }
};

class Monster : public Creature
{
public:
	enum Type
	{
		DRAGON,
		ORC,
		SLIME,
		MAX_TYPES
	};
	struct MonsterParameters
	{
		std::string name;
		char symbol;
		int health;
		int damage;
		int gold;
	};
	static MonsterParameters monsterData[MAX_TYPES];

	Monster(Type type)
		: Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health, monsterData[type].damage, monsterData[type].gold) {}

	static Monster getRandomMonster()
	{
		int randomType{ rand() % MAX_TYPES };
		return Monster(static_cast<Type>(randomType));
	}
};
