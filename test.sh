#!/bin/bash

MAX_LENTH=20
echo "________________________________________________________________________________"
echo "----------------------------------- MD5 TEST (STDIN) ---------------------------"

for (( i=1; i <= 20; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_OUTPUT=`echo -n $STRING | ./ft_ssl md5 -q`
	MD5SUM_OUTPUT=`echo -n "$STRING" | md5sum | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[32m%-"$MAX_LENTH"s %-40s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "OK"
	else
		printf "\e[31m%-"$MAX_LENTH"s %-40s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "Fail"
	fi
done

MAX_LENTH=200
echo "________________________________________________________________________________"
echo "----------------------------------- MD5 TEST (FILE) ----------------------------"

for (( i=1; i <= 20; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl md5 -q test1`
	MD5SUM_OUTPUT=`md5sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[32m%-40s\e[1m%-10s\e[0m\n" "$MD5SUM_OUTPUT" "OK"
	else
		printf "\e[31m%-40s\e[1m%-10s\e[0m\n""$MD5SUM_OUTPUT" "Fail"
	fi
done

# echo "________________________________________________________________________________"
# echo "-------------------------------- SHA256 TEST -----------------------------------"

# for (( i=1; i <= 20; i++ ))
# do
# 	# генерим случайную строку длиной от 1 до MAX_LENTH символов
# 	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
# 	FT_SSL_OUTPUT=`echo -n $STRING | ./ft_ssl`
# 	MD5SUM_OUTPUT=`echo -n "$STRING" | sha256sum | awk '{print $1}'`

# 	if [[ $FT_SSL_OUTPUT == $MD5SUM_OUTPUT ]]
# 	then
# 		printf "\e[32m%-"$MAX_LENTH"s %-70s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "OK"
# 	else
# 		printf "\e[31m%-"$MAX_LENTH"s %-70s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "Fail"
# 	fi
# done
