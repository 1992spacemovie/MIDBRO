# jan/02/1970 01:20:06 by RouterOS 6.48.6
# software id = Q5RG-A4VX
#
# model = CRS112-8G-4S
# serial number = HDA084YC4RM
/interface bridge
add name=bridge1
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/interface bridge port
add bridge=bridge1 interface=all
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=172.30.101.2/24 interface=bridge1 network=172.30.101.0
/ip route
add distance=1 gateway=172.30.101.1
/system identity
set name=RouterOS
