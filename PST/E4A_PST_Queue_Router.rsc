# 2024-03-21 09:29:19 by RouterOS 7.13.2
# software id = DZAF-5NSU
#
# model = RB3011UiAS
# serial number = E7E60F556BAB
/interface ethernet
set [ find default-name=ether1 ] name=ether1-WAN
set [ find default-name=ether9 ] name=ether9-MGMT
set [ find default-name=sfp1 ] name=sfp1-Switch-LAN
/interface vlan
add interface=sfp1-Switch-LAN name=VLAN1000-Pomale vlan-id=1000
add interface=sfp1-Switch-LAN name=VLAN2000-Stredni vlan-id=2000
add interface=sfp1-Switch-LAN name=VLAN3000-Rychle vlan-id=3000
/ip pool
add name=pool1-VLAN1000 ranges=192.168.10.10-192.168.10.100
add name=pool2-VLAN2000 ranges=192.168.20.10-192.168.20.100
add name=pool3-VLAN3000 ranges=192.168.30.10-192.168.30.100
add name=pool4-MGMT ranges=192.168.69.250-192.168.69.254
/ip dhcp-server
add address-pool=pool1-VLAN1000 interface=VLAN1000-Pomale name=\
    server1-VLAN1000
add address-pool=pool2-VLAN2000 interface=VLAN2000-Stredni name=\
    server2-VLAN2000
add address-pool=pool3-VLAN3000 interface=VLAN3000-Rychle name=\
    server3-VLAN3000
add address-pool=pool4-MGMT interface=sfp1-Switch-LAN name=server4-MGMT
/port
set 0 name=serial0
/queue simple
add limit-at=10M/10M max-limit=10M/10M name=queue1-VLAN1000 target=\
    VLAN1000-Pomale total-limit-at=100M total-max-limit=100M
add limit-at=150M/150M max-limit=150M/150M name=queue2-VLAN2000 target=\
    VLAN2000-Stredni
add limit-at=300M/300M max-limit=300M/300M name=queue3-VLAN3000 target=\
    VLAN3000-Rychle
/queue type
add kind=pcq name=PCQ-Upload pcq-classifier=src-address pcq-rate=10M
add kind=pcq name=PCQ-Download pcq-classifier=dst-address pcq-rate=10M
/queue simple
add disabled=yes limit-at=1G/1G max-limit=1G/1G name=queue4-VLAN1000-PerUser \
    queue=PCQ-Upload/PCQ-Download target=VLAN1000-Pomale
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=192.168.10.1/24 interface=VLAN1000-Pomale network=192.168.10.0
add address=192.168.20.1/24 interface=VLAN2000-Stredni network=192.168.20.0
add address=192.168.30.1/24 interface=VLAN3000-Rychle network=192.168.30.0
add address=192.168.69.1/24 interface=sfp1-Switch-LAN network=192.168.69.0
/ip dhcp-client
add interface=ether1-WAN
/ip dhcp-server network
add address=192.168.10.0/24 gateway=192.168.10.1 netmask=24
add address=192.168.20.0/24 gateway=192.168.20.1 netmask=24
add address=192.168.30.0/24 gateway=192.168.30.1 netmask=24
add address=192.168.69.0/24 gateway=192.168.69.1 netmask=24
/ip firewall nat
add action=masquerade chain=srcnat out-interface=ether1-WAN
/system clock
set time-zone-name=Europe/Prague
/system identity
set name=INET.Router
/system note
set show-at-login=no
