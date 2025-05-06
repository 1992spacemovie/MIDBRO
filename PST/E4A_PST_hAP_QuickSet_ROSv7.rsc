# nov/02/2023 08:50:02 by RouterOS 7.8
# software id = ZQK8-Y4BN
#
# model = RB952Ui-5ac2nD
# serial number = 71AF09A208A1
/interface bridge
add name=bridge1
/interface wireless
set [ find default-name=wlan1 ] country="czech republic" disabled=no mode=\
    ap-bridge ssid=Rada.Zapotocky wireless-protocol=802.11
set [ find default-name=wlan2 ] country="czech republic" disabled=no mode=\
    ap-bridge ssid=Rada.Zapotocky.5G wireless-protocol=802.11
/interface list
add name=WAN
add name=LAN
/interface wireless security-profiles
set [ find default=yes ] authentication-types=wpa-psk,wpa2-psk mode=\
    dynamic-keys supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/ip pool
add name=dhcp ranges=192.168.13.50-192.168.13.100
/ip dhcp-server
add address-pool=dhcp interface=bridge1 name=dhcp1
/interface bridge port
add bridge=bridge1 interface=ether2
add bridge=bridge1 interface=ether3
add bridge=bridge1 interface=ether4
add bridge=bridge1 interface=ether5
add bridge=bridge1 interface=wlan2
add bridge=bridge1 interface=wlan1
/interface list member
add interface=ether1 list=WAN
add interface=bridge1 list=LAN
/ip address
add address=192.168.13.1/24 interface=bridge1 network=192.168.13.0
/ip dhcp-client
add interface=ether1
/ip dhcp-server network
add address=0.0.0.0/24 dns-server=10.10.10.2 gateway=0.0.0.0 netmask=24
add address=192.168.13.0/24 dns-server=10.10.10.2 gateway=192.168.13.1 \
    netmask=24
/ip firewall nat
add action=masquerade chain=srcnat out-interface-list=WAN
/system clock
set time-zone-name=Europe/Prague
