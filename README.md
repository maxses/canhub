# CANHub

CANHub is an server-client library/apllication for distributing CAN messages over ethernet.
There is one central server application with optional real CAN interface.

Multiple clients can connect to the server to send and receive CAN messages. Each client
also receives messages from other clients.

# Compile CANHub

CANHub is a CMake project. it requires the needs the qt libraries/headers and catch/catch2 installed.
<pre>
mkdir build
cd build
cmake ..
make -j32
</pre>

# Configure CAN

Enable the service:
<pre>
$ systemctl enable systemd-networkd
$ systemctl start systemd-networkd
</pre>

Check configuration:
<pre>
$ ip -detail link show dev can0
</pre>

# Test via virtual CAN interface
<pre>
modprobe vcan
ip link add dev vcan0 type vcan
ip link set vcan0 mtu 16
ip link set up vcan0
ifconfig vcan0
candump vcan0
cansend vcan0 5A1#11.2233.44556677.88
</pre>

Send an TDT message
<pre>
cansend vcan0 419#18.04.14.00.90.0C.00.00
</pre>
