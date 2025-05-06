# jan/02/1970 00:27:54 by RouterOS 6.48.6
# software id = 61ZZ-EASG
#
# model = CRS112-8G-4S
# serial number = HDA082C621N
/interface bridge
add name=bridge1 vlan-filtering=yes
/interface ethernet
set [ find default-name=ether3 ] name=ether3-666
set [ find default-name=ether4 ] name=ether4-666
set [ find default-name=ether5 ] name=ether5-420
set [ find default-name=ether6 ] name=ether6-420
set [ find default-name=sfp9 ] name=sfp9-uplink
set [ find default-name=sfp11 ] name=sfp11-downlink
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/interface bridge port
add bridge=bridge1 interface=sfp9-uplink
add bridge=bridge1 interface=sfp11-downlink
add bridge=bridge1 interface=ether3-666 pvid=666
add bridge=bridge1 interface=ether4-666 pvid=666
add bridge=bridge1 interface=ether5-420 pvid=420
add bridge=bridge1 interface=ether6-420 pvid=420
/interface bridge vlan
add bridge=bridge1 tagged=sfp9-uplink,sfp11-downlink untagged=\
    ether3-666,ether4-666 vlan-ids=666
add bridge=bridge1 tagged=sfp9-uplink,sfp11-downlink untagged=\
    ether5-420,ether6-420 vlan-ids=420
/ip address
add address=192.168.1.2/24 interface=bridge1 network=192.168.1.0
/ip route
add distance=1 gateway=192.168.1.1
/system identity
set name=Switch1
