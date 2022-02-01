// UML.cpp 
#include <iostream>
#include<string>
using namespace std;
#define MAX_TANK_VOLUME 80
#define MIN_TANK_VOLUME 40
#define MIN_ENGINE_CONSUMPTION 4
#define MAX_ENGINE_CONSUMPTION 25

class Tank // бак
{
protected:
	const unsigned int VOLUME; // объем бака
	double fuel_level; // уровень топлива
public:
	const unsigned int get_VOLUME()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	double fill(double fuel)
	{
		if (fuel_level + fuel < 0)return fuel_level = 0;
		if (fuel_level + fuel > VOLUME)return fuel_level = VOLUME;
		//if (fuel_level+fuel>=0 && fuel_level + fuel <= VOLUME)fuel_level += fuel;
		else return fuel_level+=fuel;
	}
	double give_fuel(double fuel)
	{
		fuel_level -= fuel;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	Tank(unsigned int volume):VOLUME(volume>=MIN_TANK_VOLUME&&volume<=MAX_TANK_VOLUME?volume:MAX_TANK_VOLUME), 
		fuel_level(0)
	{
		//this->VOLUME = volume;
		cout << "Tank is ready\t" << this << endl;
	}
	~Tank()
	{
		cout << "Tank is gone\t" << this << endl;
	}
	void info_Tank()const
	{
		cout << "Tank volume:\t" << VOLUME << endl;
		cout << "Fuel level:\t" << fuel_level << endl;
	}
};

class Engine:public Tank // двигатель
{
protected:
	double consumption;             //расход
	double consumption_per_second; // расход в секунду
	bool is_started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	bool started()const
	{
		return is_started;
	}
	bool start(char M)
	{
		if (M == 'Y'&&get_fuel_level()!=0)
			return true;
		else return false;
	}
	bool stop()
	{
		is_started = false;
	}
	void started(char M)
	{
		if (start(M))is_started = true;
		else is_started = false;
	}
	void set_consumption(double consuption)
	{
		if (consuption >= MIN_ENGINE_CONSUMPTION && consuption <= MAX_ENGINE_CONSUMPTION)
			this->consumption = consuption;
		else
			this->consumption = MAX_ENGINE_CONSUMPTION / 2;
		consumption_per_second = consuption * 3e-4;
	}
	explicit Engine(unsigned int volume, double consumption):Tank(volume)
	{
		set_consumption(consumption);
		is_started = false;
		cout << "Engine is ready:\t" << this << endl;
	}
	~Engine()
	{
		cout << "Engine is gone:\t" << this << endl;
	}
	void info_Engine()const
	{
		cout << "Consumption:\t" << consumption << endl;
		cout << "Consumption per sec:\t" << consumption_per_second << endl;
		cout << "Engine is " << (is_started ? "started" : "stopped") << endl;
	}
};
class Car:public Engine
{
	string model;
	string color;
	long long int price;
public:
	const string& get_model()const
	{
		return model;
	}
	const string& get_color()const
	{
		return color;
	}

	double get_price()const
	{
		return price;
	}
	void set_model(const string& model)
	{
		this->model = model;
	}
	void set_color(const string& color)
	{
		this->color = color;
	}
	void set_price(double price)
	{
		this->price = price;
	}
	Car(unsigned int volume, double consumption, const string& model,const string& color, long long int price) : Engine(volume, consumption)
	{
		set_model(model);
		set_color(color);
		set_price(price);
		cout << "CarConstructor:\t" << this << endl;
	}
	~Car()
	{
		cout << "CarDestructor:\t" << this << endl;
	}
	void info_Car()const
	{
		cout << "Model: " << model << endl;
		cout << "Color: " << color << endl;
		cout << "price: " << price << endl;
		info_Tank();
		info_Engine();
	}
};
//#define TANK_CHECK
void main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(120);
	tank.info();
	int fuel;
	while (true)
	{
		cout << "Введите объем: ";cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif//TANK CHECK
	//Engine engine(9);
	//engine.info();
	Car A(60, 10, "Toyota", "White", 1500000);
	A.info_Car();
	A.fill(20);
	char M;
	cout << "Завести автомобиль? (Y/N): "; cin >> M;
	A.start(M);
	A.started(M);
	A.info_Car();
}

