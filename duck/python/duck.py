

class FlyBehaviour():
    def fly(self):
        raise NotImplementedError

class QuackBehaviour():
    def quack(self):
        raise NotImplementedError

class Duck():
    def __init__(self):
        self._flyBehaviour = None
        self._quackBehaviour = None

    def swim(self):
        raise NotImplementedError

    def display():
        raise NotImplementedError
    
    def setFlyBehaviour(self, newFlyBehaviour):
        self._flyBehaviour = newFlyBehaviour

    def setQuackBehaviour(self, newQuackBehaviour):
        self._quackBehaviour = newQuackBehaviour

    def performFly(self):
        self._flyBehaviour.fly()
    
    def performQuack(self):
        self._quackBehaviour.quack()

class FlyWithWings(FlyBehaviour):
    def fly(self):
        print("I am flying with wings!!!")

class FlyNoFly(FlyBehaviour):
    def fly(self):
        print("I cannot fly :(")

class Quack(QuackBehaviour):
    def quack(self):
        print("Quack!!")

class Squeak(QuackBehaviour):
    def quack(self):
        print("Squeak!!")

class MuteQuack(QuackBehaviour):
    def quack(self):
        print("I cannot quack :(")
        
        
        
        
        

class MallardDuck(Duck):
    def __init__(self):
        super().__init__()
        self._quackBehaviour = Quack()
        self._flyBehaviour = FlyWithWings()
    
    def display(self):
        print("Hello, I am Mallard Duck, and I am proud of it!")
    
    

mallard = MallardDuck()
mallard.display()
mallard.performFly()
mallard.performQuack()

mallard.setFlyBehaviour(FlyNoFly())
mallard.performFly()