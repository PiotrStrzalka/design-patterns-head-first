#include <iostream>
#include <memory>

class FlyBehaviour
{
    public:
        virtual void fly() = 0;
        virtual ~FlyBehaviour()
        {
            std::cout << "FlyBehaviour destructor" << std::endl;
        }
};

class FlyWithWings : public FlyBehaviour
{
    public:
        void fly() override
        {
            std::cout << "I am flying" << std::endl;
        }
        ~FlyWithWings()
        {
            std::cout << "Fly with wings destructor" << std::endl;
        }
};

class FlyNoWay : public FlyBehaviour
{
    public:
        void fly() override
        {
            std::cout << "I can not fly :(" << std::endl;
        }
        ~FlyNoWay()
        {
            std::cout << "FlyNoWay destructor" << std::endl;
        }
};

class QuackBehaviour
{
    public:
        virtual void quack() = 0;
        virtual ~QuackBehaviour()
        {
            std::cout << "QuackBehaviour destructor" << std::endl;
        }
};

class Quack : public QuackBehaviour
{
    public:
        void quack() override
        {
            std::cout << "Quack" << std::endl;
        }
        ~Quack()
        {
            std::cout << "Quack destructor" << std::endl;
        }
};

class MuteQuack : public QuackBehaviour
{
    public:
        void quack() override
        {
            std::cout << "<< Silence >>" << std::endl;
        }
        ~MuteQuack()
        {
            std::cout << "MuteQuack destructor" << std::endl;
        }
};

class Squeak : public QuackBehaviour
{
    public:
        void quack() override
        {
            std::cout << "Squeak" << std::endl;
        }
        ~Squeak()
        {
            std::cout << "Squeak destructor" << std::endl;
        }
};

class Duck
{
    public:
        Duck(){}
        virtual ~Duck(){}
        std::unique_ptr<FlyBehaviour> flyBehaviour;
        std::unique_ptr<QuackBehaviour> quackBehaviour;

        void setFlyBehaviour(std::unique_ptr<FlyBehaviour> fb)
        {
            this->flyBehaviour.swap(fb);
        }

        // void setQuackBehaviour(std::unique_ptr<QuackBehaviour> qb)
        // {
        //     this->quackBehaviour = qb;
        // }

        void performFly()
        {
            flyBehaviour->fly();
        }

        void performQuack()
        {
            quackBehaviour->quack();
        }
        
        void swim()
        {
            std::cout << "All ducks can swim!" << std::endl;
        }
};

class MallardDuck : public Duck 
{
    public:
        MallardDuck() 
        {
            this->flyBehaviour = std::make_unique<FlyWithWings>();
            this->quackBehaviour = std::make_unique<Quack>();
        }

        ~MallardDuck()
        {
            std::cout << "MallardDuck destructor called!" << std::endl;
        }
};

int main(int argc, char * argv[])
{
    std::cout << "Hello world" << std::endl;
    {
        std::unique_ptr<Duck> duck = std::make_unique<MallardDuck>();

        duck->performFly();
        duck->performQuack();

        duck->setFlyBehaviour(std::make_unique<FlyNoWay>());
        duck->performFly();
    }

    std::cout << "--------After block----------" << std::endl;
    

    return 0;
}