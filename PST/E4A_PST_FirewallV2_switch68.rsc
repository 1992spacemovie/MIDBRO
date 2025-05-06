# jan/02/1970 01:07:33 by RouterOS 6.48.6
# software id = 7CG7-XA6F
#
# model = CRS112-8G-4S
# serial number = HDA0805BH10
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
add address=192.168.68.2/24 interface=bridge1 network=192.168.68.0
/system identity
set name=Mlejnek_Rada_Switch_E4
