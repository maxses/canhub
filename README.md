# CANHub

CANHub is an server-client apllication/library for distributing CAN messages via ethernet.
There is one central server application with optional real CAN interface.

Multiple clients can connect to the server to send and receive CAN messages. Each client
also receives messages from other clients.

# Configure CAN

Enable the service:
$ systemctl enable systemd-networkd
$ systemctl start systemd-networkd

Check configuration:
$ ip -detail link show dev can0

# Test

modprobe vcan
ip link add dev vcan0 type vcan
ip link set vcan0 mtu 16
ip link set up vcan0
ifconfig vcan0
candump vcan0
cansend vcan0 5A1#11.2233.44556677.88

Send an TDT message

cansend vcan0 419#18.04.14.00.90.0C.00.00

