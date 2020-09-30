#!/bin/bash

MAX_LENTH=20

echo "________________________________________________________________________________"
echo "----------------------------------- MD5 TEST -----------------------------------"

for (( i=1; i <= 20; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_OUTPUT=`echo -n $STRING | ./ft_ssl`
	MD5SUM_OUTPUT=`echo -n "$STRING" | md5sum | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[32m%-"$MAX_LENTH"s %-40s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "OK"
	else
		printf "\e[31m%-"$MAX_LENTH"s %-40s\e[1m%-10s\e[0m\n" "$STRING" "$MD5SUM_OUTPUT" "Fail"
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
