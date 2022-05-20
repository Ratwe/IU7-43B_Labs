file=$1
opt=$2
size=$3

gcc -g3 -O"$opt" -std=c99 -Wall -Werror -Wpedantic -Wextra -DMAX_SIZE="$size" -o app.exe "$file"
