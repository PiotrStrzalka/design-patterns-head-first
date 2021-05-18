#include <iostream>
#include <memory>

class Beverage
{
    public:
        virtual std::string getDescription() = 0;
        virtual float cost() = 0;
        virtual ~Beverage(){}
};

class CondimentDecorator : public Beverage
{
    public:
        virtual std::string getDescription() = 0;
        virtual ~CondimentDecorator(){}
    protected:
        Beverage * beverage;
};

class Espresso : public Beverage
{
    public:
        Espresso(){}
        
        float cost() override { return 1.99;}
        std::string getDescription() override {return "Espresso";}
};

class HouseBlend : public Beverage
{
    public:
        HouseBlend(){}
    
        float cost() override { return 0.99;}
        std::string getDescription() override {return "House Blend Coffee";}
};

class Mocha : public CondimentDecorator
{
    public:
        Mocha(Beverage & beverage)
        {
            this->beverage = &beverage;
        }

        std::string getDescription() override
        {
            return this->beverage->getDescription() + ", Mocha";
        }

        float cost() override
        {
            return this->beverage->cost() + 0.2;
        }

    private:
        Mocha(const Mocha&);
};

class Soy : public CondimentDecorator
{
    public:
        Soy(Beverage & beverage)
        {
            this->beverage = &beverage;
        }

        std::string getDescription() override
        {
            return this->beverage->getDescription() + ", Soy";
        }

        float cost() override
        {
            return this->beverage->cost() + 0.15;
        }
};

class Whip : public CondimentDecorator
{
    public:
        Whip(Beverage & beverage)
        {
            this->beverage = &beverage;
        }

        std::string getDescription() override
        {
            return this->beverage->getDescription() + ", Whip";
        }

        float cost() override
        {
            return this->beverage->cost() + 0.2;
        }
};


void printInfo(const std::shared_ptr<Beverage> b)
{
    std::cout << b->getDescription() << " $" << b->cost() << std::endl; 
}

void printInfo(Beverage& b)
{
    std::cout << b.getDescription() << " $" << b.cost() << std::endl; 
}

int main(int argc, char * argv[])
{
    // Beverage * beverage = new Espresso();
    std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
    printInfo(beverage);
   
    HouseBlend hb;
    Mocha m{hb};
    Mocha m2{(Beverage)m};
    Whip w{m2};


    printInfo(m2);

    // auto beverage2 = std::make_shared<Mocha>(hb);
    // beverage2 = std::make_shared<Mocha>(beverage2);
    // printInfo(beverage2);
}