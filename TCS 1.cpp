#include <iostream>
using namespace std;



class Smarthphone {
private:
	string model;
protected:
	Smarthphone(string model) : model(model) {}
public:
	string getModel() { return model; }		
};

enum TYPE {
	J7_,
	G5_,
	IPHONE6_
};

class Factory {
public:
	virtual Smarthphone* createSmarthphone(TYPE type) = 0;
};

class G5 : public Smarthphone {
public:
	G5() : Smarthphone("G5") {}
};

class J7 : public Smarthphone {
public:
	J7() : Smarthphone("J7") {}	
};

class iPhone6 : public Smarthphone {
public:
	iPhone6() : Smarthphone("iPhone6") {}
};
	
class Samsung : public Factory {
private: 
	static Factory* factory;
	Samsung(){}
public:
	Smarthphone* createSmarthphone(TYPE type)
	{
		switch (type)
		{
			case J7_:
				return new J7;
			break;
			default:
				return 0;
		}
	}	
	static Factory* getFactory() 
	{
		return factory = (factory ? factory : new Samsung);
	}
};

class Apple : public Factory {
private:	
	Apple() {}
	static Factory* factory;
public:
	Smarthphone* createSmarthphone(TYPE type)
	{
		switch (type)
		{
			case IPHONE6_:
				return new iPhone6;
			break;
			default:
				return 0;
		};
	}
	static Factory* getFactory() 
	{
		return factory = (factory ? factory : new Apple);
	}	
};

class LG : public Factory {
private:
	static Factory* factory;
	LG() {}
public:
	Smarthphone* createSmarthphone(TYPE type)
	{
		switch (type)
		{
			case G5_:
				return new G5;
			break;
			default:
				return 0;
		}
	}	
	static Factory* getFactory() 
	{
		return factory = (factory ? factory : new LG);
	}	
};

Factory* LG::factory = 0;
Factory* Apple::factory = 0;
Factory* Samsung::factory = 0;


int main( void ) {
	cout <<((Samsung::getFactory())->createSmarthphone(J7_))->getModel();
	return 0;

}
