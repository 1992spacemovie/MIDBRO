# jan/02/1970 01:13:22 by RouterOS 6.48.6
# software id = MD76-GAZY
#
# model = CRS112-8G-4S
# serial number = HDA08CK31RV
/interface bridge
add name=bridge1 vlan-filtering=yes
/interface ethernet
set [ find default-name=ether1 ] name=ether1-MGMT
set [ find default-name=ether3 ] name=ether3-VLAN1000
set [ find default-name=ether4 ] name=ether4-VLAN1000
set [ find default-name=ether5 ] name=ether5-VLAN2000
set [ find default-name=ether6 ] name=ether6-VLAN2000
set [ find default-name=ether7 ] name=ether7-VLAN3000
set [ find default-name=ether8 ] name=ether8-VLAN3000
set [ find default-name=sfp12 ] name=sfp12-uplink
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/interface bridge port
add bridge=bridge1 interface=ether1-MGMT
add bridge=bridge1 interface=ether3-VLAN1000 pvid=1000
add bridge=bridge1 interface=ether4-VLAN1000 pvid=1000
add bridge=bridge1 interface=ether5-VLAN2000 pvid=2000
add bridge=bridge1 interface=ether6-VLAN2000 pvid=2000
add bridge=bridge1 interface=ether7-VLAN3000 pvid=3000
add bridge=bridge1 interface=ether8-VLAN3000 pvid=3000
add bridge=bridge1 interface=sfp12-uplink
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/interface bridge vlan
add bridge=bridge1 tagged=sfp12-uplink untagged=\
    ether3-VLAN1000,ether4-VLAN1000 vlan-ids=1000
add bridge=bridge1 tagged=sfp12-uplink untagged=\
    ether5-VLAN2000,ether6-VLAN2000 vlan-ids=2000
add bridge=bridge1 tagged=sfp12-uplink untagged=\
    ether7-VLAN3000,ether8-VLAN3000 vlan-ids=3000
/ip address
add address=192.168.69.2/24 interface=sfp12-uplink network=192.168.69.0
/ip route
add distance=1 gateway=192.168.69.1
/system identity
set name=INET.Switch
