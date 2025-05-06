# jan/02/1970 00:29:11 by RouterOS 6.47.10
# software id = RSGG-8F94
#
# model = RB3011UiAS
# serial number = E7E60F3D9300
/interface ethernet
set [ find default-name=ether1 ] name=ether1-WAN
set [ find default-name=ether10 ] name=ether10-LAN
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip pool
add name=pool1-LAN ranges=192.168.6.9-192.168.66.6
/ip dhcp-server
add address-pool=pool1-LAN disabled=no interface=ether10-LAN name=server1-LAN
/ip address
add address=10.23.7.222/24 interface=ether1-WAN network=10.23.7.0
add address=192.168.66.1/24 interface=ether10-LAN network=192.168.66.0
/ip dhcp-client
add disabled=no interface=ether1-WAN
/ip dhcp-server network
add address=192.168.66.0/24 gateway=192.168.66.1 netmask=24
/ip firewall filter
add action=accept chain=forward dst-address=192.168.66.6 dst-port=80 \
    protocol=tcp
/ip firewall nat
add action=src-nat chain=srcnat to-addresses=10.23.7.5
add action=dst-nat chain=dstnat dst-address=10.23.7.222 dst-port=80 protocol=\
    tcp to-addresses=192.168.66.6 to-ports=80
/ip service
set telnet address=192.168.66.0/24
set ftp address=192.168.66.0/24
set www address=192.168.66.0/24
set ssh address=192.168.66.0/24
set www-ssl address=192.168.66.0/24 disabled=no
set api address=192.168.66.0/24
set winbox address=192.168.66.0/24
set api-ssl address=192.168.66.0/24
/system identity
set name=HeadRouter
