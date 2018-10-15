#  
#  algorithm - some algorithms in "Introduction to Algorithms", third edition
#  Copyright (C) 2018  lxylxy123456
#  
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Affero General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#  
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Affero General Public License for more details.
#  
#  You should have received a copy of the GNU Affero General Public License
#  along with this program.  If not, see <https:#www.gnu.org/licenses/>.
#  

mkdir /tmp/.dot.sh/ 2> /dev/null

if [ $# == 0 ]; then
	A=`mktemp /tmp/.dot.sh/XXXXXXXX.dot`
	cat > $A
else
	A=$1
fi

B=`mktemp /tmp/.dot.sh/XXXXXXXX.png`
dot $A -Tpng -o $B && gnome-open $B 2> /dev/null > /dev/null

