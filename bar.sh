

while :
do
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

    cpu_temperature=$(cat /sys/class/thermal/thermal_zone0/temp | awk '{print $1/1000 "°C"}')

    # Načteme první řádek z /proc/stat
    cpu_line=$(head -n 1 /proc/stat)

    # Extrahujeme jednotlivé hodnoty pro uživatele, system, idle, atd.
    read -r cpu user nice system idle iowait irq softirq < <(echo $cpu_line | awk '{print $1, $2, $3, $4, $5, $6, $7, $8}')

    # Vypočítáme celkový čas CPU a idle čas
    total=$((user + nice + system + idle + iowait + irq + softirq))
    total_idle=$((idle + iowait))

    # Pokud máme předchozí hodnoty, vypočteme změnu a CPU load
    if [[ -n "$prev_total" && -n "$prev_idle" ]]; then
        total_diff=$((total - prev_total))
        idle_diff=$((total_idle - prev_idle))

        # Vypočítáme zatížení CPU
        cpu_usage=$((100 * (total_diff - idle_diff) / total_diff))
    else 
        cpu_usage="N/A"
    fi

    # Uložíme aktuální hodnoty pro příští výpočet
    prev_total=$total
    prev_idle=$total_idle


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

    # Network
    network=$(ip route get 1.1.1.1 | grep -Po '(?<=dev\s)\w+' | cut -f1 -d ' ')
    ssid_name=$(LC_ALL=C nmcli -t -f active,ssid dev wifi | grep '^yes' | cut -d':' -f2)
    gateway=$(ip route | awk '/default/ {print $3}')
    ping=$(ping -W 1 -c 1 $gateway | tail -1| awk '{print $4}' | cut -d '/' -f 2 | cut -d '.' -f 1)


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
       ping="0"
    else
       network_active=""
    fi

    net="$(printf "%s %s %*sms" $network_active $ssid_name 4 $ping)"
    load="$(printf " %*s%%" 3 $cpu_usage)"
    
    temper=$(printf "🌡 %s" $cpu_temperature)
    echo " $net | $load | $audio_active $audio_volume | $temper | $battery_pluggedin $battery_charge | $date_and_week  $current_time "

    sleep 1
done


