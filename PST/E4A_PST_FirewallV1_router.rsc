# nov/30/2023 09:30:46 by RouterOS 6.47.10
# software id = QVJD-RL6J
#
# model = RB3011UiAS
# serial number = E7E60FF4F4DD
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip address
add address=192.168.101.1/24 interface=ether5 network=192.168.101.0
add address=172.30.101.1/24 interface=ether6 network=172.30.101.0
add address=10.56.65.1/24 interface=ether10 network=10.56.65.0
/ip dhcp-client
add disabled=no interface=ether1
/ip firewall filter
add action=reject chain=forward in-interface=ether6 out-interface=ether1 \
    reject-with=icmp-network-unreachable
/ip firewall nat
add action=masquerade chain=srcnat out-interface=ether1
/system clock
set time-zone-name=Europe/Prague
