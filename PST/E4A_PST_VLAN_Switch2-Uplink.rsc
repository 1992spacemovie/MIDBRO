# jan/02/1970 00:15:25 by RouterOS 6.48.6
# software id = Q5RG-A4VX
#
# model = CRS112-8G-4S
# serial number = HDA084YC4RM
/interface bridge
add name=bridge1 vlan-filtering=yes
/interface ethernet
set [ find default-name=ether3 ] name=ether3-420
set [ find default-name=ether4 ] name=ether4-420
set [ find default-name=ether5 ] name=ether5-666
set [ find default-name=ether6 ] name=ether6-666
set [ find default-name=sfp9 ] name=sfp9-uplink
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/interface bridge port
add bridge=bridge1 interface=sfp9-uplink
add bridge=bridge1 interface=ether3-420 pvid=420
add bridge=bridge1 interface=ether4-420 pvid=420
add bridge=bridge1 interface=ether5-666 pvid=666
add bridge=bridge1 interface=ether6-666 pvid=666
/interface bridge vlan
add bridge=bridge1 tagged=sfp9-uplink untagged=ether5-666,ether6-666 \
    vlan-ids=666
add bridge=bridge1 tagged=sfp9-uplink untagged=ether3-420,ether4-420 \
    vlan-ids=420
/ip address
add address=192.168.1.3/24 interface=bridge1 network=192.168.1.0
/ip route
add distance=1 gateway=192.168.1.1
/system identity
set name=Switch2
