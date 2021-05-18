
class Observer():
    def update(self):
        raise NotImplementedError
    
class Subject():
    def registerObserver(self):
        raise NotImplementedError
    def removeObserver(self):
        raise NotImplementedError
    def notifyObservers(self):
        raise NotImplementedError
    
class DisplayElement():
    def display(self):
        raise NotImplementedError
    

class WeatherData(Subject):
    
    def __init__(self):
        self._observers = []
        self._temperature = None
        self._humidity = None
        self._pressure = None
        
    
    def registerObserver(self, o : Observer):
        self._observers.append(o)
         
    def removeObserver(self, o : Observer):
        self._observers.remove(o)
    
    def notifyObservers(self):
        for o in self._observers:
            o.update()
    
    def setMeasurement(self, temp, humi, press):
        self._temperature = temp
        self._humidity = humi
        self._pressure = press
        self.notifyObservers()
        
class CurrentConditionsDisplay(Observer, DisplayElement):
    def __init__(self, wd : WeatherData):
        self._wd : WeatherData = wd
        self._wd.registerObserver(self)
        self._temperature = 0
        self._humidity = 0
        self._pressure = 0
    
    def display(self):
        print(f"Current conditions: \n  Temperature: {self._temperature}\n  Humidity:{self._humidity}\n  Pressure:{self._pressure}")
    
    def update(self):
        self._temperature = self._wd._temperature
        self._humidity = self._wd._humidity
        self._pressure = self._wd._pressure
        
wd = WeatherData()
ccDisplay = CurrentConditionsDisplay (wd)

wd.setMeasurement(50, 58, 58)

ccDisplay.display()

