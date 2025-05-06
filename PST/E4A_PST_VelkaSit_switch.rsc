# jan/02/2023 09:01:19 by RouterOS 6.48.6
# software id = 61ZZ-EASG
#
# model = CRS112-8G-4S
# serial number = HDA082C621N
/interface bridge
add name=bridge1
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip hotspot profile
set [ find default=yes ] html-directory=hotspot
/interface bridge port
add bridge=bridge1 interface=all
/ip neighbor discovery-settings
set discover-interface-list=!dynamic
/ip address
add address=192.168.37.10/24 interface=bridge1 network=192.168.37.0
/system identity
set name=RouterOS
