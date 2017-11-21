from pysense import Pysense
import time
from network import Sigfox
import socket

py = Pysense()


# init Sigfox for RCZ1 (Europe)
sigfox = Sigfox(mode=Sigfox.SIGFOX, rcz=Sigfox.RCZ1)

# create a Sigfox socket
s = socket.socket(socket.AF_SIGFOX, socket.SOCK_RAW)

# make the socket blocking
s.setblocking(True)

# configure it as uplink only
s.setsockopt(socket.SOL_SIGFOX, socket.SO_RX, False)

while True:
    #temperature = int(round(si.temperature()*100))
    temperature = 24
    light = 350
    print(str(temperature) + ":"+str(light))
    messageBytes=bytes((temperature & 0xff, ((temperature >> 8) & 0xff),light & 0xff, ((light >> 8) & 0xff)))
    s.send(messageBytes)
    time.sleep(30)
