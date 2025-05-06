# jan/02/1970 01:01:44 by RouterOS 6.48.6
# software id = G8RE-R9JV
#
# model = CRS112-8G-4S
# serial number = HDA08452TXT
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
add address=192.168.70.2/24 interface=bridge1 network=192.168.70.0
/system identity
set name=Mlejnek.Rada.SW70
