# jan/25/2024 08:54:42 by RouterOS 6.47.10
# software id = QVJD-RL6J
#
# model = RB3011UiAS
# serial number = E7E60FF4F4DD
/interface vlan
add interface=sfp1 name=vlan420-hulici vlan-id=420
add interface=sfp1 name=vlan666-pekelnici vlan-id=666
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip pool
add name=dhcp_pool1 ranges=192.168.42.2-192.168.42.254
add name=dhcp_pool2 ranges=192.168.66.2-192.168.66.254
/ip dhcp-server
add address-pool=dhcp_pool1 disabled=no interface=vlan420-hulici name=dhcp1
add address-pool=dhcp_pool2 disabled=no interface=vlan666-pekelnici name=\
    dhcp2
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=192.168.66.1/24 interface=vlan666-pekelnici network=192.168.66.0
add address=192.168.42.1/24 interface=vlan420-hulici network=192.168.42.0
add address=192.168.1.1/24 interface=sfp1 network=192.168.1.0
/ip dhcp-client
add disabled=no interface=ether1
/ip dhcp-server network
add address=192.168.42.0/24 gateway=192.168.42.1
add address=192.168.66.0/24 gateway=192.168.66.1
/ip firewall filter
add action=drop chain=forward in-interface=vlan420-hulici out-interface=\
    ether1
/ip firewall nat
add action=masquerade chain=srcnat
/system clock
set time-zone-name=Europe/Prague
/system identity
set name=Router
