# jan/02/1970 00:54:55 by RouterOS 6.48.6
# software id = Q5RG-A4VX
#
# model = CRS112-8G-4S
# serial number = HDA084YC4RM
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
set [ find default-name=ether8 ] name=ether8-MGMT
set [ find default-name=sfp12 ] name=sfp12-Unor.Router-uplink
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/interface bridge port
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether1-VLAN100 pvid=100
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether2-VLAN200 pvid=200
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether3-VLAN100 pvid=100
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether4-VLAN200 pvid=200
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether5-VLAN100 pvid=100
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether6-VLAN200 pvid=200
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether7-VLAN100 pvid=100
add bridge=bridge1 interface=sfp12-Unor.Router-uplink
add bridge=bridge1 frame-types=admit-only-untagged-and-priority-tagged \
    interface=ether8-MGMT
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/interface bridge vlan
add bridge=bridge1 tagged=sfp12-Unor.Router-uplink untagged=\
    ether1-VLAN100,ether3-VLAN100,ether5-VLAN100,ether7-VLAN100 vlan-ids=100
add bridge=bridge1 tagged=sfp12-Unor.Router-uplink untagged=\
    ether2-VLAN200,ether4-VLAN200,ether6-VLAN200 vlan-ids=200
/ip address
add address=192.168.69.3/24 interface=bridge1 network=192.168.69.0
/system identity
set name=Unor.SW2
