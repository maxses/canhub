CANServer is an server-client apllication for distributing CAN messages via ethernet.
There is one central server application with optiona real CAN interface.

Multiple clients can connect to server to send and receive CAN messages. Each client
receives messages from other clients.

Configure CAN

enable the service:
$ systemctl enable systemd-networkd
$ systemctl start systemd-networkd

check configuration:
$ ip -detail link show dev can0