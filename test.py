import PyPhoenix5
import time

def test_SRX():
    talon = PyPhoenix5.TalonSRX(1)
    print(talon)
    print(talon.get_device_id())
    talon.set_power(0.5)
    for i in range(100):
        PyPhoenix5.feed_enable(100)
        time.sleep(0.05)
    talon.set_power(0.0)

if __name__ == '__main__':
    test_SRX()

