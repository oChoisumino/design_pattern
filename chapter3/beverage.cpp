#include <iostream>
#include <string>

using namespace std;

class Beverage {
public:
    string description;

    virtual ~Beverage() = default;
    virtual string getDescription() {
        return description;
    }
    virtual double cost() = 0;
};

class Espresso : public Beverage {
public:
    Espresso() {
        description = "에스프레소";
    }
    double cost() {
        return 1.99;
    }
};

class HouseBlend : public Beverage {
public:
    HouseBlend() {
        description = "하우스 블렌드";
    }
    double cost() {
        return 0.89;
    }
};

class DarkRoast : public Beverage {
public:
    DarkRoast() {
        description = "다크 로스트";
    }
    double cost() {
        return 0.99;
    }
};

class CondimentDecorator : public Beverage {
public:
    Beverage *beverage;
};

class Mocha : public CondimentDecorator {
public:
    Mocha(Beverage *b) {
        beverage = b;
    }
    string getDescription() {
        return beverage->getDescription() + ", 모카";
    }
    double cost() {
        return beverage->cost() + 0.20;
    }
};

class Soy : public CondimentDecorator {
public:
    Soy(Beverage *b) {
        beverage = b;
    }
    string getDescription() {
        return beverage->getDescription() + ", 두유";
    }
    double cost() {
        return beverage->cost() + 0.15;
    }
};

class whip: public CondimentDecorator {
public:
    whip(Beverage *b) {
        beverage = b;
    }
    string getDescription() {
        return beverage->getDescription() + ", 휘핑 크림";
    }
    double cost() {
        return beverage->cost() + 0.10;
    }
};

int main(void)
{
    Beverage *beverage = new Espresso();
    cout << beverage->getDescription() << ", $" << beverage->cost() << endl;

    Beverage *beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new whip(beverage2);
    cout << beverage2->getDescription() << ", $" << beverage2->cost() << endl;

    Beverage *beverage3 = new HouseBlend();
    beverage3 = new Soy(beverage3);
    beverage3 = new Mocha(beverage3);
    beverage3 = new whip(beverage3);
    cout << beverage3->getDescription() << ", $" << beverage3->cost() << endl;

    return 0;
}