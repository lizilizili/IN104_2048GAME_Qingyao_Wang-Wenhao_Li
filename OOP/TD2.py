class Animal:

    def __init__(self, name, weight, height):

        self.name = name
        self.weight = weight
        self.__height = height

    def getHeight(self):
        return self.__height


class Sheep(Animal):

    def __init__(self, name, weight, height):

        Animal.__init__(self, name, weight, height)
        self.sound='baa baa'
        self.state='sleep'
        print(self.name,"is a sheep")

    def run(self):
        print(self.name,"is running")
        self.state='run'

    def makeSound(self):
        print(self.name,":",self.sound)



class Wolf(Animal):

    def __init__(self, name, weight, height , color):
        Animal.__init__(self, name, weight, height)
        self.color=color
        self.friend=None
        print(self.name,"is a wolf")

    def eat(self,sheep):
        if self.friend==sheep:
            print(self.name,"can't eat", sheep.name, "because they are friends")
        else:
            print(self.name,"ate",sheep.name)
            self.weight += sheep.weight
            print(self.name," weights ",self.weight)

    def friendship(self,friend):
        self.friend=friend
        print(self.name,"and", friend.name, "are friends")


if __name__ == '__main__':
    sheep1 = Sheep("Amy", 20.0, 1.2)
    sheep2 = Sheep("Wanda",15.0, 1.0)
    wolf = Wolf("Jack",50.0,1.5,"gray")

    sheep1.makeSound()
    sheep1.run()
    wolf.eat(sheep1)
    wolf.friendship(sheep2)
    wolf.eat(sheep2)

