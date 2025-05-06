# jan/02/1970 01:01:34 by RouterOS 6.47.10
# software id = QVJD-RL6J
#
# model = RB3011UiAS
# serial number = E7E60FF4F4DD
/interface ethernet
set [ find default-name=ether1 ] name=ether1-ISP
set [ find default-name=sfp1 ] name=sfp1-LAN
/interface vlan
add interface=sfp1-LAN name=vlan100 vlan-id=100
add interface=sfp1-LAN name=vlan200 vlan-id=200
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip pool
add name=pool-mngmt ranges=192.168.69.100-192.168.69.200
add name=pool100 ranges=192.168.10.100-192.168.10.200
add name=pool200 ranges=192.168.20.100-192.168.20.200
/ip dhcp-server
add address-pool=pool100 disabled=no interface=vlan100 name=serverVLAN100
add address-pool=pool200 disabled=no interface=vlan200 name=serverVLAN200
add address-pool=pool-mngmt disabled=no interface=sfp1-LAN name=serverMNGMT
/ip address
add address=192.168.69.1/24 interface=sfp1-LAN network=192.168.69.0
add address=192.168.10.1/24 interface=vlan100 network=192.168.10.0
add address=192.168.20.1/24 interface=vlan200 network=192.168.20.0
/ip dhcp-client
add disabled=no interface=ether1-ISP
/ip dhcp-server network
add address=192.168.10.0/24 dns-server=10.10.10.3 gateway=192.168.10.1
add address=192.168.20.0/24 dns-server=10.10.10.3 gateway=192.168.20.1
add address=192.168.69.0/24 dns-server=10.10.10.3 gateway=192.168.69.1
/ip firewall nat
add action=masquerade chain=srcnat out-interface=ether1-ISP
/system identity
set name=Unor.RB1
