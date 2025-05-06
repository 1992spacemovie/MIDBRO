# jan/11/2024 09:23:29 by RouterOS 6.47.10
# software id = QFN1-1XB6
#
# model = RB3011UiAS
# serial number = E7E60F831919
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip pool
add name=pool-dhcp ranges=192.168.68.10-192.168.68.200
add name=pool-management ranges=172.30.69.5-172.30.69.10
/ip dhcp-server
add address-pool=pool-dhcp disabled=no interface=ether4 name=server1
add address-pool=pool-management disabled=no interface=ether9 name=server2
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=192.168.68.1/24 interface=ether4 network=192.168.68.0
add address=192.168.70.1/24 interface=ether5 network=192.168.70.0
add address=172.30.69.1/24 interface=ether9 network=172.30.69.0
/ip dhcp-client
add disabled=no interface=ether1
/ip dhcp-server network
add address=172.30.69.0/24 gateway=172.30.69.1 netmask=24
add address=192.168.68.0/24 gateway=192.168.68.1 netmask=24
/ip firewall filter
add action=reject chain=forward in-interface=ether4 log=yes out-interface=\
    ether1 reject-with=icmp-admin-prohibited
/ip firewall nat
add action=masquerade chain=srcnat log=yes out-interface=ether1
/system clock
set time-zone-name=Europe/Prague
/system identity
set name=Mlejnek.Rada.Router
