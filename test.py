import PyPhoenix5
import time

def test_SRX():
  PyPhoenix5.set_phoenix_diagnostics_start_time(0)
  talon = PyPhoenix5.TalonSRX(1)
  print(talon)
  print(talon.get_device_id())
  if True:
    talon.set_power(0.1)
    if True:
      for i in range(100):
        PyPhoenix5.feed_enable(100)
        time.sleep(0.05)
        # print(talon.get_position(), talon.get_output_current())
    talon.set_power(0.0)
  while True:
    PyPhoenix5.feed_enable(200)
    time.sleep(0.05)
    print(talon.get_position(), talon.is_fwd_limit_switch_closed(), talon.is_rev_limit_switch_closed())


if __name__ == '__main__':
  try:
    test_SRX()
  except KeyboardInterrupt:
    pass

