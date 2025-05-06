# nov/16/2023 09:01:07 by RouterOS 6.47.10
# software id = QVJD-RL6J
#
# model = RB3011UiAS
# serial number = E7E60FF4F4DD
/interface bridge
add name=bridge1
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/interface bridge port
add bridge=bridge1 interface=ether2
add bridge=bridge1 interface=ether3
add bridge=bridge1 interface=sfp1
/ip address
add address=192.168.37.1/24 interface=ether2 network=192.168.37.0
/ip dhcp-client
add disabled=no interface=ether1
/ip firewall nat
add action=masquerade chain=srcnat out-interface=ether1
/system clock
set time-zone-name=Europe/Prague
