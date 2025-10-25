

################
## Variables
#################
#
## Keyboard input name
keyboard_input_name="1:1:AT_Translated_Set_2_keyboard"
#
## Date and time
date_and_week=$(date "+(week %-V) %Y.%m.%d")
current_time=$(date "+%H:%M:%S")

#commands
#############
#
## Battery or charger
battery_charge=$(upower --show-info $(upower --enumerate | grep 'BAT') | egrep "percentage" | awk '{print $2}')
battery_status=$(upower --show-info $(upower --enumerate | grep 'BAT') | egrep "state" | awk '{print $2}')
#
## Audio and multimedia
audio_volume=$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $2 }')
audio_status=$(amixer sget Master | grep 'Right:' | awk -F'[][]' '{ print $4 }') 
loadavg_5min=$(cat /proc/loadavg | awk -F ' ' '{print $2}')

# Network
network=$(ip route get 1.1.1.1 | grep -Po '(?<=dev\s)\w+' | cut -f1 -d ' ')
# interface_easyname grabs the "old" interface name before systemd renamed it
interface_easyname=$(dmesg | grep $network | grep renamed | awk 'NF>1{print $NF}')
gateway=$(ip route | awk '/default/ {print $3}')
ping=$(ping -c 1 $gateway | tail -1| awk '{print $4}' | cut -d '/' -f 2 | cut -d '.' -f 1)



if [ $audio_status = "on" ];
then
    if [ $audio_volume == "100%" ];
    then
        audio_active=""
    elif [ $audio_volume == "0%" ];
    then
        audio_active=""
    else
        audio_active=""
    fi
else
    audio_active=""
fi


batter_percentage=${battery_charge%\%}


if [ $battery_status = "discharging" ];
then
    if [ $batter_percentage -ge 80 ] && [ $batter_percentage -le 100 ];
    then
        battery_pluggedin=""
    elif [ $batter_percentage -ge 60 ] && [ $batter_percentage -lt 80 ];
    then
        battery_pluggedin=""
    elif [ $batter_percentage -ge 40 ] && [ $batter_percentage -lt 60 ];      
    then
        battery_pluggedin=""
    elif [ $batter_percentage -ge 20 ] && [ $batter_percentage -lt 40 ];
    then
        battery_pluggedin=""
    else
        battery_pluggedin=""
    fi
else
    battery_pluggedin=''
fi

if ! [ $network ]
then
   network_active=""
else
   network_active=""
fi

echo "$network_active $interface_easyname ($ping ms) |  $loadavg_5min% | $audio_active $audio_volume | $battery_pluggedin $battery_charge | $date_and_week  $current_time "


