# ISA 2020: Odpovědní arch pro cvičení č. 2

## Vzdálený terminál - SSH, Secure Shell

### (2.) Bezpečné připojení na vzdálený počítač bez autentizačních klíčů

*Verze OpenSSH*: SSH-2.0-OpenSSH_7.4

*Vybraná podporovaná šifra*: curve25519-sha256@libssh.org

*Co lze zjistit o obsahu komunikace?*: the content of the communication is encrypted: ".......... W .." .. u ........ |. (.. S.5 .... "

### (3.) Vytvoření veřejného a privátního klíče

*Jak se liší práva mezi souborem s privátním a veřejným klíčem?*: we have 600 permission on private key -> because we want to save it secure and be readable/writeable only for owner user. And we have 644 permission on public key -> because we can share it with other users and it will be readable for everyone.

To be sure in permissions SSh client can print out some warning about wrong permissions on keys to ensure that you do not share your private key with every user on a server.

### (4.) Distribuce klíčů

*Jaká hesla bylo nutné zadat při kopírovaní klíčů?*: user password (user4lab) or root password during key copy

*Jaká hesla bylo nutné zadat při opětovném přihlášení?*: after key copying and all settings it was enough for user to enter passphrase for key or nothing for root

### (6.) Pohodlné opakované použití klíče

*Museli jste znovu zadávat heslo?*: user - only passphrase for key (with SSH_AUTH_SOCK we can remember passphrase). root - no, 

## Zabezpečení transportní vrstvy - TLS, Transport Layer Security

### (1.) Nezabezpečený přenos dat

*Je možné přečíst obsah komunikace?*: HTTP/80 -> Yes

### (2.) Přenos dat zabezpečený TLS

*Je možné přečíst obsah komunikace?*: HTTPS/443 -> No
