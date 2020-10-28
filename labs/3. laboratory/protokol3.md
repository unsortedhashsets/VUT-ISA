# ISA 2020: Odpovědní arch pro cvičení č. 3

## (1.) Resolving DNS dotazů

Jaké jsou autoritativní DNS servery pro doménu *vutbr.cz*?\
  \ pipit.cis.vutbr.cz
  \ rhino.cis.vutbr.cz

*Display filter* pro zobrazení pouze DNS provozu: dns

Počet zachycených paketů souvisejících s vyhledáním NS pro doménu *vutbr.cz*: 2: request/answer

Provedený DNS dotaz (vyberte správnou variantu): **rekurzivní**

Podle čeho jste zjistili zakroužkovaný typ DNS dotazu v zachyceném paketu? FLAG - recursive required

Cílová IP adresa paketu s DNS dotazem: 213.46.172.38

Jakému zařízení náleží zapsaná IP adresa? DNS resolver (UPC's router's WAN IP -> http://cz-prg01a-dns03.chello.cz/)

## (2.) Zabezpečení a resolving pomocí DNS over HTTPS

Dokážete zjistit ze zachyceného DNS provozu, jaké domény jste předtím navštívili? Proč?   
  \ Сould not see the pages in the dns communication since HTTPS was used
  \ meduza.io 
  \ facebook.com
  \ gmail.com

*Display filter* pro zobrazení pouze TLS provozu: tls

Jeden řádek z položky *Answers* z libovolné DoH odpovědi:  
  \ api.twitter.com: type CNAME, class IN, cname tpop-api.twitter.com

IP adresa, na kterou směřovaly pakety s DoH dotazem: 193.17.47.1 

Doménové jméno patřící k doplněné IP adrese: odvr.nic.cz


## (3.) Zabezpečení a resolving pomocí DNS over TLS

*Display filter* pro zobrazení pouze provozu využívající TCP port 853: tcp.port == 853

*Display filter* pro zobrazení pouze provozu využívající TCP nebo UDP port 53: tcp.port == 53 || udp.port == 53

Služba běžící nad portem 53: DNS

Počet zachycených paketů se zdrojovým nebo cílovým portem 53: 0


## (4.) Blokování reklam a další

Jaký rozdíl jste zpozorovali na webu *idnes.cz* při jeho načtení s aktivním nástrojem *pi-hole*? ad's banners were not loaded
