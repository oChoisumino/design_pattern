#include <iostream>

using namespace std;

class FlyBehavior {
    public:
        virtual ~FlyBehavior() = default;
        virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior {
    public:
        void fly() { 
            cout << "날고 있어요!" << endl;
        }
};

class FlyNoWay : public FlyBehavior {
    public:
        void fly() {
            cout << "날지 못해요" << endl;
        }
};

class FlyRocketPowered : public FlyBehavior {
    public:
        void fly() {
            cout << "로켓 추진" << endl;
        }
};

class QuackBehavior {
    public:
        virtual ~QuackBehavior() = default;
        virtual void quack() = 0;
};

class Quack : public QuackBehavior {
    public:
        void quack() {
            cout << "꽥" << endl;
        }
};

class MuteQuack : public QuackBehavior {
    public:
        void quack() {
            cout << "<<조용>>" << endl;
        }
};

class Squeak : public QuackBehavior {
    public:
        void quack() {
            cout << "삑" << endl;
        }
};

class Duck {
    public:
        QuackBehavior *quackBehavior;
        FlyBehavior *flyBehavior;

        virtual ~Duck() = default;

        void performFly() { flyBehavior->fly(); }
        void performQuack() { quackBehavior->quack(); }
        void swim() { cout << "모든 오리는 물에 뜬다" << endl; }

        void setFlyBehavior(FlyBehavior *fb) { flyBehavior = fb; }
        void setQuackBehavior(QuackBehavior *qb) { quackBehavior = qb; }

        virtual void display() = 0;
};

class MallardDuck : public Duck {
    public:
        MallardDuck() {
            quackBehavior = new Quack();
            flyBehavior = new FlyWithWings();
        }

        void display() { cout << "청둥오리" << endl; }
};

class ModelDuck : public Duck {
    public:
        ModelDuck() {
            flyBehavior = new FlyNoWay();
            quackBehavior = new Quack();
        }
        void display() {
            cout << "모형 오리" << endl;
        }
};
int main (void) {
    Duck *mallard = new MallardDuck();

    mallard->performQuack();
    mallard->performFly();

    Duck *model = new MallardDuck();

    model->performFly();
    model->setFlyBehavior(new FlyRocketPowered());

    model->performFly();

    return 0;
}
