# mar/07/2024 09:31:36 by RouterOS 6.47.10
# software id = QVJD-RL6J
#
# model = RB3011UiAS
# serial number = E7E60FF4F4DD
/interface bridge
add name=bridge1
/interface ethernet
set [ find default-name=ether1 ] name=ether1-WAN
set [ find default-name=ether2 ] name=ether2-MGMT
set [ find default-name=ether5 ] name=ether5-LAN
set [ find default-name=ether10 ] name=ether10-backupWAN
/interface vlan
add interface=ether5-LAN name=VLAN100-A100 vlan-id=100
add interface=ether5-LAN name=VLAN200-B100 vlan-id=200
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip pool
add name=pool-VLAN100 ranges=192.168.10.10-192.168.10.200
add name=pool-VLAN200 ranges=192.168.20.10-192.168.20.200
add name=pool-MGMT ranges=192.168.69.245-192.168.69.250
/ip dhcp-server
add address-pool=pool-VLAN100 disabled=no interface=VLAN100-A100 name=\
    server-VLAN100
add address-pool=pool-VLAN200 disabled=no interface=VLAN200-B100 name=\
    server-VLAN200
add address-pool=pool-MGMT disabled=no interface=bridge1 name=server-MGMT
/interface bridge port
add bridge=bridge1 interface=ether2-MGMT
add bridge=bridge1 interface=ether5-LAN
/ip address
add address=192.168.69.1/24 interface=bridge1 network=192.168.69.0
add address=192.168.10.1/24 interface=VLAN100-A100 network=192.168.10.0
add address=192.168.20.1/24 interface=VLAN200-B100 network=192.168.20.0
/ip dhcp-client
add disabled=no interface=ether1-WAN
/ip dhcp-server network
add address=192.168.10.0/24 gateway=192.168.10.1 netmask=24
add address=192.168.20.0/24 gateway=192.168.20.1 netmask=24
add address=192.168.69.0/24 gateway=192.168.69.1 netmask=24
/ip dns
set servers=10.10.10.2,10.10.10.3
/ip firewall filter
add action=log chain=forward dst-address=192.168.69.0/24 log=yes
/ip firewall nat
add action=masquerade chain=srcnat out-interface=ether1-WAN
/ip route
add distance=1 gateway=10.23.7.1
/system clock
set time-zone-name=Europe/Prague
/system identity
set name=B315.Router
