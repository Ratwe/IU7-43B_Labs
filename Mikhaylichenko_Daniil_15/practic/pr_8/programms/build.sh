file=$1
opt="s"
size=10000

if [ ! -z $2 ]; then
	opt=$1
fi

if [ ! -z $3 ]; then
	size=$3
fi


gcc -g3 -O"$opt" -std=c99 -Wall -Werror -Wpedantic -Wextra -DMAX_SIZE="$size" -o app.exe "$file"
