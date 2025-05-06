# jan/02/1970 01:22:17 by RouterOS 6.48.6
# software id = 61ZZ-EASG
#
# model = CRS112-8G-4S
# serial number = HDA082C621N
/interface bridge
add name=bridge1 vlan-filtering=yes
/interface ethernet
set [ find default-name=ether1 ] name=ether1-downlink
set [ find default-name=ether2 ] name=ether2-uplink
set [ find default-name=ether3 ] name=ether3-VLAN200
set [ find default-name=ether4 ] name=ether4-VLAN100
set [ find default-name=ether5 ] name=ether5-VLAN200
set [ find default-name=ether6 ] name=ether6-VLAN100
set [ find default-name=ether8 ] name=ether8-MGMT
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/interface bridge port
add bridge=bridge1 interface=ether1-downlink
add bridge=bridge1 interface=ether2-uplink
add bridge=bridge1 interface=ether3-VLAN200 pvid=200
add bridge=bridge1 interface=ether4-VLAN100 pvid=100
add bridge=bridge1 interface=ether5-VLAN200 pvid=200
add bridge=bridge1 interface=ether6-VLAN100 pvid=100
add bridge=bridge1 interface=ether8-MGMT
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/interface bridge vlan
add bridge=bridge1 tagged=ether1-downlink,ether2-uplink untagged=\
    ether3-VLAN200,ether5-VLAN200 vlan-ids=200
add bridge=bridge1 tagged=ether1-downlink,ether2-uplink untagged=\
    ether4-VLAN100,ether6-VLAN100 vlan-ids=100
/ip address
add address=192.168.69.2/24 interface=bridge1 network=192.168.69.0
/ip route
add distance=1 gateway=192.168.69.1
/system identity
set name=B315.SW1
