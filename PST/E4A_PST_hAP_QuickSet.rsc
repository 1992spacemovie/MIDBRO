# oct/05/2023 14:01:11 by RouterOS 6.49.7
# software id = AXQU-D0HY
#
# model = RB952Ui-5ac2nD
# serial number = 71AF09393A2A
/interface bridge
add name=bridge1
/interface wireless
set [ find default-name=wlan1 ] disabled=no mode=ap-bridge ssid=\
    Rada.Zapotocky wireless-protocol=802.11
set [ find default-name=wlan2 ] disabled=no mode=ap-bridge ssid=\
    Rada.Zapotocky wireless-protocol=802.11
/interface list
add name=WAN
add name=LAN
/interface wireless security-profiles
set [ find default=yes ] authentication-types=wpa-psk,wpa2-psk mode=\
    dynamic-keys supplicant-identity=MikroTik wpa-pre-shared-key=12345678 \
    wpa2-pre-shared-key=12345678
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/ip pool
add name=dhcp ranges=192.168.103.10-192.168.103.200
/ip dhcp-server
add address-pool=dhcp disabled=no interface=bridge1 name=dhcp1
/interface bridge port
add bridge=bridge1 interface=ether2
add bridge=bridge1 interface=ether3
add bridge=bridge1 interface=ether4
add bridge=bridge1 interface=ether5
add bridge=bridge1 interface=wlan2
add bridge=bridge1 interface=wlan1
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/interface list member
add interface=ether1 list=WAN
add interface=bridge1 list=LAN
/ip address
add address=192.168.103.1/24 interface=bridge1 network=192.168.103.0
/ip dhcp-client
add disabled=no interface=ether1
/ip dhcp-server network
add address=0.0.0.0/24 gateway=0.0.0.0 netmask=24
add address=192.168.103.0/24 gateway=192.168.103.1 netmask=24
/ip firewall nat
add action=masquerade chain=srcnat out-interface-list=WAN
/system clock
set time-zone-name=Europe/Prague
