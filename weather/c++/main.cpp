#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>


class Observer;

class Subject
{
    public:
        virtual void registerObserver(Observer * o) = 0;
        virtual void removeObserver(Observer * o) = 0;
        virtual void notifyObservers() = 0;

        virtual ~Subject(){}
};

class Observer
{
    public:
        virtual void update() = 0;
        
        virtual ~Observer(){}
};

class DisplayElement
{
    public:
        virtual void display() = 0;

        virtual ~DisplayElement(){}
};

class WeatherData : public Subject
{
    public:
        void registerObserver(Observer * o) override
        {
            observers.push_back(o);
        }

        void removeObserver(Observer * o) override
        {
            // std::erase(observers, o);
            // observers.erase(o);
            observers.erase(std::remove_if(observers.begin(), observers.end(), 
                [&o](auto const & elem){ return elem == o; }));            
        }

        void notifyObservers()
        {
            for( auto o : observers)
            {
                o->update();
            }
        }

        void measurementChanged()
        {
            notifyObservers();
        }

        void setMeasurement(float temperature, float humidity, float pressure)
        {
            this->temperature = temperature;
            this->humidity = humidity;
            this->pressure = pressure;
            measurementChanged();
        }

        float getTemperature(){ return temperature; }
        float getHumidity(){ return humidity; }
        float getPressure(){ return pressure; }

    private:
        float temperature;
        float humidity;
        float pressure;
        std::vector<Observer *> observers;
};

class CurrentConditionDisplay : public Observer, public DisplayElement
{
    public:
        /* implicit const this as a first argument !!!!!!!!!! */
        CurrentConditionDisplay(WeatherData& wd)
        {
            weatherData = &wd;
            wd.registerObserver(this);
        }

        void display() override
        {
            std::cout << "Current temperature is: " << temperature
                        << " and current humidity is: " << humidity << std::endl;
        }
        
        void update() override 
        {
            this->temperature = weatherData->getTemperature();
            this->humidity = weatherData->getHumidity();
            display();
        }

    private:
        float temperature;
        float humidity;
        WeatherData * weatherData;
};

class ForecastDisplay : public Observer, public DisplayElement
{
    public:
        ForecastDisplay(WeatherData& wd)
        {
            weatherData = &wd;
            wd.registerObserver(this);
        }

        void update() override
        {
            this->pressure = weatherData->getPressure();
            display();
        }

        void display() override
        {
            std::string weatherStatus = pressure > 1000.0 ? "good" : "bad";
            std::cout << "The weather is going to be " << weatherStatus << std::endl;
        }
        
    private:
        float pressure;
        WeatherData * weatherData;
};


int main(int argc, char * argv[])
{
    WeatherData weatherData;
    CurrentConditionDisplay currentDisplay{weatherData};
    ForecastDisplay forecastDisplay{weatherData};

    weatherData.setMeasurement(10.0, 20.0, 999.0);
}
