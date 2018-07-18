mkdir /tmp/.dot.sh/ 2> /dev/null

if [ $# == 0 ]; then
	A=`mktemp /tmp/.dot.sh/XXXXXXXX.dot`
	cat > $A
else
	A=$1
fi

B=`mktemp /tmp/.dot.sh/XXXXXXXX.png`
dot $A -Tpng -o $B && gnome-open $B 2> /dev/null > /dev/null

