import PyPhoenix5
from PyPhoenix5 import add, Pet


def test_add():
    assert add(2, 3) == 5


def test_pet():
    my_dog = Pet('Pluto', 5)
    assert my_dog.get_name() == 'Pluto'
    assert my_dog.get_hunger() == 5
    my_dog.go_for_a_walk()
    assert my_dog.get_hunger() == 6

def test_SRX():
    talon = PyPhoenix5.TalonSRX(1)
    print(talon)

if __name__ == '__main__':
    test_SRX()

