# jan/02/1970 00:45:38 by RouterOS 6.48.6
# software id = 61ZZ-EASG
#
# model = CRS112-8G-4S
# serial number = HDA082C621N
/interface bridge
add name=bridge1 vlan-filtering=yes
/interface ethernet
set [ find default-name=ether1 ] name=ether1-VLAN100
set [ find default-name=ether2 ] name=ether2-VLAN200
set [ find default-name=ether3 ] name=ether3-VLAN100
set [ find default-name=ether4 ] name=ether4-VLAN200
set [ find default-name=ether5 ] name=ether5-VLAN100
set [ find default-name=ether6 ] name=ether6-VLAN200
set [ find default-name=ether7 ] name=ether7-VLAN100
set [ find default-name=ether8 ] name=ether8-MNGMT
set [ find default-name=sfp11 ] name=sfp11-downlink
set [ find default-name=sfp12 ] name=sfp12-uplink
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/interface bridge port
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether1-VLAN100 pvid=100
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether3-VLAN100 pvid=100
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether5-VLAN100 pvid=100
add bridge=bridge1 interface=ether7-VLAN100 pvid=100
add bridge=bridge1 interface=ether2-VLAN200 pvid=200
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether4-VLAN200 pvid=200
add bridge=bridge1 interface=ether6-VLAN200 pvid=200
add bridge=bridge1 interface=ether8-MNGMT
add bridge=bridge1 interface=sfp12-uplink
add bridge=bridge1 interface=sfp11-downlink
/interface bridge vlan
add bridge=bridge1 tagged=sfp11-downlink,sfp12-uplink untagged=\
    ether1-VLAN100,ether3-VLAN100,ether5-VLAN100,ether7-VLAN100 vlan-ids=100
add bridge=bridge1 tagged=sfp11-downlink,sfp12-uplink untagged=\
    ether2-VLAN200,ether4-VLAN200,ether6-VLAN200 vlan-ids=200
/ip address
add address=192.168.69.2/24 interface=bridge1 network=192.168.69.0
/system identity
set name=Unor.SW1
