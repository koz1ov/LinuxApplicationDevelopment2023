SLEEP_TIME="${1:-0.05}"
x=0
y=0
re="[[:space:]]"
points=()
while IFS= read -n1 -d "" ch; do
  if [[ ! $ch =~ $re ]]; then
    points+=("$y,$x,$ch")
  fi
  if [ "$ch" = $'\n' ]; then 
    x=0
    y=$((y+1))
  else
    x=$((x+1))
  fi
done

shuffled_points=( $(shuf -e "${points[@]}") )

clear
for value in "${shuffled_points[@]}";
do
  point=($(echo "$value" | tr ',' '\n'))
  tput cup ${point[0]} ${point[1]} 
  echo -n ${point[2]}
  sleep $SLEEP_TIME
done

tput cup $[$(tput lines)-1] 0 
