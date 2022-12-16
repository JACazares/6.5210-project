if [ $# -eq 0 ]
then
	g++ main.cpp -o main -std=c++20 -Wall -Wextra -Wshadow -DLOCAL -O2
elif [ $# -eq 1 ]
then
	g++ $1.cpp -o $1 -std=c++20 -Wall -Wextra -Wshadow -DLOCAL -O2
else
	echo "Too many arguments"
fi
