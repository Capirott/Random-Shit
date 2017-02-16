#include <iostream>
using namespace std;



class Smarthphone {

		
};

enum TYPE {
	J7_,
	G5_,
	IPHONE6_
};

class Factory {
public:
	virtual Smarthphone* create() = 0;
};

class G5 : public Smarthphone {
public:
	void ayylmao() {
		cout << "YOOOOOOO\n";
	}
	
};

class J7 : public Smarthphone {
public:
		void ayylmao() {
		cout << "LIXO\n";
	}
	
};

class iPhone6 : public Smarthphone {
	
	
};
	
class Samsung : public Factory {
	

public:
	static Smarthphone* create(TYPE type){
		switch (type)
		{
			case J7_:
				return new J7;
			break;
			default:
				return 0;
		}
	}	
	
};

class Apple : public Factory {
public:
	static Smarthphone* create(TYPE type){
		switch (type)
		{
			case IPHONE6_:
				return new iPhone6;
			break;
			default:
				return 0;
		};
	}	
	

};

class LG : public Factory {
	
public:
	static Smarthphone* create(TYPE type){
		switch (type)
		{
			case G5_:
				return new G5;
			break;
			default:
				return 0;
		}
	}	
	
};

int main( void ) {
	
	((G5 *)LG::create(G5_))->ayylmao();
	((J7 *)LG::create(J7_))->ayylmao(); 
	return 0;

}
