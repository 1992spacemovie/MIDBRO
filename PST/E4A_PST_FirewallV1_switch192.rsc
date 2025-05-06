# jan/02/1970 01:03:10 by RouterOS 6.48.6
# software id = 61ZZ-EASG
#
# model = CRS112-8G-4S
# serial number = HDA082C621N
/interface bridge
add name=bridge1
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/interface bridge port
add bridge=bridge1 interface=all
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=192.168.101.2/24 interface=bridge1 network=192.168.101.0
/ip route
add distance=1 gateway=192.168.101.1
/system identity
set name=RouterOS
