#include "stdafx.h"
#include <iostream>

#include <vector>
#include <string>
#include <algorithm>

// OO Design Principles
/*
- Encapsulate what varies
- Favour composition over inheritance
- Program to interfaces
- Loose coupling, high cohesion
- Classes should be open for extension, but closed for motification
- Depend upon abstractions and not concrete classes
*/

// Gang Of Four Types
/*
Creational
- Factory				Creates objects without specifying an exist class to create.
- Abstract Factory		Groups object factories that have a common theme.
- Singleton				Restricts object creation for a class to only one instance.
- Builder				Constructs complex objects by seperating construction and representation.

Structual
- Decorator				Dynamically adds/overrides behaviour in an existing method of an object.
- Adapter				Allows classes with incompatible interfaces to work together.
- Facade				Provides a simplified interface to a large body of code.
- Flyweight				Reduces the cost of creating and manipulating a large number of similar objects.
- Proxy					Provides a placeholder for another object to control access.

Behavioural
- Strategy				Allows one of a family of algorithms to be selected on-the-fly at runtime.
- Observer				Publish/Subscribe pattern which allows a number of observer objects to see an event.
- Iterator				Access the elements of an object squentially without exposing its representation.
- Template				Deinfes the skeleton of an algorithm as an abstract class, allowing subclasses to provide behaviour.
- Command				Creates an object which encapsulates actions and parameters.
*/

// The Singleton Pattern
// Ensures a class only has one instance
// Provides a global point of access to it
class Singleton
{
public:
	static Singleton* getInstance()
	{
		if (!_instance)
		{
			_instance = new Singleton();
		}
		return _instance;
	}
private:
	static Singleton* _instance;
	Singleton() {};
};

Singleton* Singleton::_instance = nullptr;

// The Strategy Pattern
// Defines a family of algorithms, encapsulates them
// and makes them interchangable
class QuackBehaviour
{
public:
	virtual void quack()
	{
		std::cout << "Quack" << std::endl;
	}
};

class LouderQuackBehaviour : public QuackBehaviour
{
public:
	void quack()
	{
		std::cout << "QUACK!!!" << std::endl;
	}
};

class Duck
{
public:
	Duck()
	{
		_quacker = new QuackBehaviour();
	}
	~Duck()
	{
		delete _quacker;
	}
	void quack()
	{
		_quacker->quack();
	}
	void setQuack(QuackBehaviour* quackBehaviour)
	{
		_quacker = quackBehaviour;
	}
private:
	QuackBehaviour* _quacker;
};

// The Decorator Pattern
// Attach additional responsibilities to an object dynamically
// Provide a flexible alternative to subclassing for extended functionality
class Beverage
{
public:
	virtual std::string describe() = 0;
};

class RumAndCoke : public Beverage
{
public:
	std::string describe()
	{
		return "I am a rum and coke";
	}
};

class RumAndCokeDecorator : public Beverage
{
public:
	RumAndCokeDecorator(Beverage* rc)
	{
		rumAndCoke = rc;
	}
	std::string describe()
	{
		return rumAndCoke->describe();
	}
private:
	Beverage* rumAndCoke;
};

class Lime : public RumAndCokeDecorator
{
public:
	Lime(Beverage* r) : RumAndCokeDecorator(r) { }
	std::string describe()
	{
		return RumAndCokeDecorator::describe() + ", with a lime!";
	}
};


class Umbrella : public RumAndCokeDecorator
{
public:
	Umbrella(Beverage* r) : RumAndCokeDecorator(r) {}
	std::string describe()
	{
		return RumAndCokeDecorator::describe() + ", with an umbrella!";
	}
};

// Builder Pattern
// Allows the client to assemble an object with selected components
// As opposed to complex constructors
class Pizza
{
public:
	void setBase(std::string base)
	{
		_base = base;
	}
	void setSauce(std::string sauce)
	{
		_sauce = sauce;
	}
	void setTopping(std::string topping)
	{
		_topping = topping;
	}
	void describe()
	{
		std::cout << "Pizza with " << _base.c_str() << " base, " <<
			_sauce.c_str() << " sauce, " << _topping.c_str() << " topping" << std::endl;
	}
private:
	std::string _base;
	std::string _sauce;
	std::string _topping;
};

class PizzaBuilder
{
public:
	Pizza* getPizza()
	{
		return _pizza;
	}
	void bakePizza()
	{
		_pizza = new Pizza();
	}
	virtual void chooseBase() = 0;
	virtual void chooseSauce() = 0;
	virtual void chooseTopping() = 0;
protected:
	Pizza* _pizza;
};

class MeatFeastBuilder : public PizzaBuilder
{
	virtual void chooseBase()
	{
		_pizza->setBase("deep pan");
	}
	virtual void chooseSauce()
	{
		_pizza->setSauce("bbq");
	}
	virtual void chooseTopping()
	{
		_pizza->setTopping("all the meat");
	}
};

class SpicyPizzaBuilder : public PizzaBuilder
{
	virtual void chooseBase()
	{
		_pizza->setBase("thin crust");
	}
	virtual void chooseSauce()
	{
		_pizza->setSauce("tomato");
	}
	virtual void chooseTopping()
	{
		_pizza->setTopping("ground beef and jalapenos");
	}
};

class Cook
{
public:
	void setPizzaBuilder(PizzaBuilder* pb)
	{
		_pizzaBuilder = pb;
	}
	Pizza* getPizza()
	{
		return _pizzaBuilder->getPizza();
	}
	void bakePizza()
	{
		_pizzaBuilder->bakePizza();
		_pizzaBuilder->chooseBase();
		_pizzaBuilder->chooseSauce();
		_pizzaBuilder->chooseTopping();
	}
private:
	PizzaBuilder* _pizzaBuilder;
};

// The Factory Pattern
// Define an interface for creating an object
// Let subclasses decide which class to instantiate
// Deferred instantiation
enum Type {
	CIRCLE,
	SQUARE
};

class Shape
{
public:
	virtual void draw() = 0;
};

class Circle : public Shape
{
public:
	Circle()
	{
		this->_name = "Circle";
	}
	~Circle()
	{
		std::cout << this->_name.c_str() << " destructor called" << std::endl;
	}
	void draw()
	{
		std::cout << "drawing " << this->_name.c_str() << std::endl;
	}
private:
	std::string _name;
};

class Square : public Shape
{
public:
	Square()
	{
		this->_name = "Square";
	}
	~Square()
	{
		std::cout << this->_name.c_str() << " destructor called" << std::endl;
	}
	void draw()
	{
		std::cout << "drawing " << this->_name.c_str() << std::endl;
	}
private:
	std::string _name;
};

class ShapeFactory
{
public:
	Shape* getShape(Type type)
	{
		Shape* shape;
		switch (type)
		{
		case CIRCLE:
			shape = new Circle();
			break;
		case SQUARE:
			shape = new Square();
			break;
		default:
			shape = new Circle();
			break;
		}
		return shape;
	}
};

// Observer Pattern
// One to many dependancy between objects
// Dependants are notified and updated automatically when the subject changes
class Observer
{
public:
	virtual void update() = 0;
};

class Observee
{
public:
	virtual void registerListener(Observer* o) = 0;
	virtual void unregisterListener(Observer* o) = 0;
};

class Database : public Observee
{
public:
	void registerListener(Observer* o)
	{
		observers.push_back(o);
	}
	void unregisterListener(Observer* o)
	{
		observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
	}
	void update()
	{
		for (Observer* o : observers)
		{
			o->update();
		}
	}

private:
	std::vector<Observer*> observers;
};

class Listener : public Observer
{
public:
	void update()
	{
		std::cout << "received notification" << std::endl;
	}
};

int main()
{
	// Singleton Pattern
	Singleton* instance = Singleton::getInstance();
	delete instance;

	// Strategy Pattern
	Duck duck;

	QuackBehaviour* loudQuack = new LouderQuackBehaviour();
	duck.setQuack(loudQuack);
	duck.quack();

	delete loudQuack;

	// Decorator Pattern
	Beverage* drink = new Lime(new Umbrella(new RumAndCoke()));

	std::cout << drink->describe() << std::endl;

	delete drink;

	// Builder Pattern
	Cook cook;
	PizzaBuilder* meatFeatBuilder = new MeatFeastBuilder();

	cook.setPizzaBuilder(meatFeatBuilder);
	cook.bakePizza();

	Pizza* meatFeastPizza = cook.getPizza();
	meatFeastPizza->describe();

	delete meatFeatBuilder;
	delete meatFeastPizza;

	// Factory Pattern
	ShapeFactory shapeFactory;
	Shape* circle = shapeFactory.getShape(CIRCLE);
	circle->draw();

	Shape* square = shapeFactory.getShape(SQUARE);
	square->draw();

	delete circle;
	delete square;

	// Observer Pattern
	Database* db = new Database();
	Listener* l = new Listener();

	db->registerListener(l);
	db->update();

	delete db;
	delete l;

	getchar();
	return 0;
}