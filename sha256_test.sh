#!/bin/bash

MAX_LENTH=100
echo "________________________________________________________________________________"
echo "---------------------------------- SHA256 TEST (FILE) ----------------------------"

printf "\e[1m%-40s%-20s\e[0m\n" "SHA256SUM_OUTPUT" "ft_ssl-OUTPUT"
for (( i=1; i <= 20; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha256 -q test1`
	SHA256SUM_OUTPUT=`sha256sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $SHA256SUM_OUTPUT ]]
	then
		printf "%-10s\e[32m%-70s\e[1m%-20s\e[0m\n" $i "$SHA256SUM_OUTPUT" "OK"
		cp test1 sucsess_test_$i
	else
		printf %-10s"\e[31m%-70s\e[1m%-20s\e[0m\n" $i "$SHA256SUM_OUTPUT" "Fail"
		cp test1 fail_test_$i
	fi
done
