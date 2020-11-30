# ISA 2020: Odpovědní arch pro cvičení č. 1

## Zjišťování konfigurace

### (1.) Rozhraní enp0s3

*MAC adresa*: 08:00:27:64:ed:2e

*IPv4 adresa*: 10.0.2.15

*Délka prefixu*: 24

*Adresa síťe*: 10.0.2.0

*Broadcastová adresa*: 10.0.2.255

### (2.) Výchozí brána

*MAC adresa*: 52:54:00:12:35:02

*IPv4 adresa*: 10.0.2.2

### (4.) DNS servery

*Soubor*: /etc/resolv.conf

*DNS servery*: nameserver 10.45.248.15, nameserver 10.38.5.26, nameserver 213.46.172.38

### (5.) Ping na výchozí bránu

*Soubor*: /etc/hosts

*Úprava*: add new line: "10.0.2.2    gw"

### (6.) TCP spojení

*Záznam + popis*: 

State       Recv-Q Send-Q  Local Address:Port                   Peer Address:Port      

ESTAB       0      0           10.0.2.15:45412                 13.227.156.62:https

State is the connection condition (now it is ESTAB -> established)

Recv-Q is the count of bytes not copied by the user program connected to this socket. 

Send-Q is the count of bytes not acknowledged by the remote host.

Local Address:Port is the local IP/port used for connection.

Peer Address:Port is the remote IP/port (https = 443) used for https connection.

### (8.) NetworkManager události

*Příkaz*: sudo journalctl -u NetworkManager

### (9.) Chybová hláška sudo

*Příkaz*: sudo journalctl -f (to see last 10 messages) OR sudo journalctl | grep '/bin/wireshark' (we can grep wireshark)

*Chybová hláška*: Oct 03 12:09:00 ibm-p8-kvm-03-guest-02.virt.pnr.lab.eng.rdu2.redhat.com sudo[21268]:     user : command not allowed ; TTY=pts/0 ; PWD=/home/user ; USER=root ; COMMAND=/bin/wireshark

## Wireshark

### (1.) Capture filter

*Capture filter*: port 80

### (2.) Zachycená HTTP komunikace

Komu patří nalezené IPv4 adresy a MAC adresy? - enp0s3, gateway, remote server

Vypisovali jste již některé z nich? - Yes

Proč tomu tak je? Due the communication between our enp0s3->gw and remote server. (Example first 3 packets -> TCP 3-Way Handshake Process)

#### Požadavek HTTP

Cílová MAC adresa

  - *Adresa*: 52:54:00:12:35:02
  - *Role zařízení*: gateway

Cílová IP adresa

  - *Adresa*: 147.229.177.179
  - *Role zařízení*: remote server

Zdrojová MAC adresa

  - *Adresa*: 08:00:27:64:ed:2e
  - *Role zařízení*: enp0s3

Zdrojová IP adresa

  - *Adresa*: 10.0.2.15
  - *Role zařízení*: enp0s3


#### Odpověď HTTP

Cílová MAC adresa

  - *Adresa*: 08:00:27:64:ed:2e
  - *Role zařízení*: enp0s3

Cílová IP adresa

  - *Adresa*: 10.0.2.15
  - *Role zařízení*: enp0s3

Zdrojová MAC adresa

  - *Adresa*: 52:54:00:12:35:02
  - *Role zařízení*: gateway

Zdrojová IP adresa

  - *Adresa*: 147.229.177.179
  - *Role zařízení*: remote server

### (3.) Zachycená ARP komunikace

*Display filter*: arp or icmp   (in case only arp - only "arp")

### (6.) Follow TCP stream

Jaký je formát zobrazených dat funkcí *Follow TCP stream*, slovně popište
význam funkce *Follow TCP stream*: 

Display filter which selects all the packets in the current stream in format of actual (compressed) data as a stream of bytes (HTTP stream show in the html format)
