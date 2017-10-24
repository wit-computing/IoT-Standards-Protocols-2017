from network import Sigfox
import socket
import time
from pysense import Pysense

from SI7006A20 import SI7006A20

from LTR329ALS01 import LTR329ALS01

py = Pysense()

si = SI7006A20(py)

lt = LTR329ALS01(py)


# init Sigfox for RCZ1 (Europe)
sigfox = Sigfox(mode=Sigfox.SIGFOX, rcz=Sigfox.RCZ1)

# create a Sigfox socket
s = socket.socket(socket.AF_SIGFOX, socket.SOCK_RAW)

# make the socket blocking
s.setblocking(True)

# configure it as uplink only
s.setsockopt(socket.SOL_SIGFOX, socket.SO_RX, False)

while True:
    message = "temp:"+str(si.temperature())
    print(message)
    time.sleep(5)
