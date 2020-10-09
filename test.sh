#!/bin/bash

EVENTS=3

MAX_LENTH=20
echo "________________________________________________________________________________"
echo "------------------------------ MD5 TEST (STDIN/STRING) -------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-40s%-20s%-20s\e[0m\n" "STRING" "MD5SUM_OUTPUT" "ft_ssl-STDIN_OUT" "ft_ssl-STRING_OUT"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl md5 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl md5 -q -s $STRING`
	MD5SUM_OUTPUT=`echo -n "$STRING" | md5sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-40s" "$STRING" "$MD5SUM_OUTPUT"
	if [[ $FT_SSL_STDIN_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi

	if [[ $FT_SSL_STRING_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________"
echo "----------------------------------- MD5 TEST (FILE) ----------------------------"

printf "\e[1m%-40s%-20s\e[0m\n" "MD5SUM_OUTPUT" "ft_ssl-OUTPUT"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl md5 -q test1`
	MD5SUM_OUTPUT=`md5sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $MD5SUM_OUTPUT ]]
	then
		printf "\e[32m%-40s\e[1m%-20s\e[0m\n" "$MD5SUM_OUTPUT" "OK"
	else
		printf "\e[31m%-40s\e[1m%-20s\e[0m\n" "$MD5SUM_OUTPUT" "Fail"
	fi
done

MAX_LENTH=20
echo "________________________________________________________________________________"
echo "-------------------------------- SHA256 TEST -----------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-70s%-20s%-20s\e[0m\n" "STRING" "SHA256SUM_OUTPUT" "ft_ssl-STDIN_OUT" "ft_ssl-STRING_OUT"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha256 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha256 -q -s $STRING`
	SHA256SUM_OUTPUT=`echo -n "$STRING" | sha256sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-70s" "$STRING" "$SHA256SUM_OUTPUT"
	if [[ $FT_SSL_STDIN_OUTPUT == $SHA256SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi

	if [[ $FT_SSL_STRING_OUTPUT == $SHA256SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________"
echo "---------------------------------- SHA256 TEST (FILE) ----------------------------"

printf "\e[1m%-70s%-20s\e[0m\n" "SHA256SUM_OUTPUT" "ft_ssl-OUTPUT"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha256 -q test1`
	SHA256SUM_OUTPUT=`sha256sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $SHA256SUM_OUTPUT ]]
	then
		printf "\e[32m%-70s\e[1m%-20s\e[0m\n" "$SHA256SUM_OUTPUT" "OK"
		# cp test1 sucsess_test_$i
	else
		printf "\e[31m%-70s\e[1m%-20s\e[0m\n" "$SHA256SUM_OUTPUT" "Fail"
		cp test1 fail_test_$i
	fi
done


MAX_LENTH=20
echo "________________________________________________________________________________"
echo "-------------------------------- SHA224 TEST -----------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-70s%-20s%-20s\e[0m\n" "STRING" "SHA224SUM_OUTPUT" "ft_ssl-STDIN_OUT" "ft_ssl-STRING_OUT"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha224 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha224 -q -s $STRING`
	SHA224SUM_OUTPUT=`echo -n "$STRING" | sha224sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-70s" "$STRING" "$SHA224SUM_OUTPUT"
	if [[ $FT_SSL_STDIN_OUTPUT == $SHA224SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi

	if [[ $FT_SSL_STRING_OUTPUT == $SHA224SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________"
echo "---------------------------------- SHA224 TEST (FILE) ----------------------------"

printf "\e[1m%-70s%-20s\e[0m\n" "SHA224SUM_OUTPUT" "ft_ssl-OUTPUT"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha224 -q test1`
	SHA224SUM_OUTPUT=`sha224sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $SHA224SUM_OUTPUT ]]
	then
		printf "\e[32m%-70s\e[1m%-20s\e[0m\n" "$SHA224SUM_OUTPUT" "OK"
		# cp test1 sucsess_test_$i
	else
		printf "\e[31m%-70s\e[1m%-20s\e[0m\n" "$SHA224SUM_OUTPUT" "Fail"
		cp test1 fail_test_$i
	fi
done


MAX_LENTH=20
echo "________________________________________________________________________________"
echo "-------------------------------- SHA512 TEST -----------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-140s%-20s%-20s\e[0m\n" "STRING" "SHA512SUM_OUTPUT" "ft_ssl-STDIN_OUT" "ft_ssl-STRING_OUT"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha512 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha512 -q -s $STRING`
	SHA512SUM_OUTPUT=`echo -n "$STRING" | sha512sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-140s" "$STRING" "$SHA512SUM_OUTPUT"
	if [[ $FT_SSL_STDIN_OUTPUT == $SHA512SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi

	if [[ $FT_SSL_STRING_OUTPUT == $SHA512SUM_OUTPUT ]]
	then
		printf "\e[1;32m%-20s\e[0m" "OK"
	else
		printf "\e[1;31m%-20s\e[0m" "Fail"
	fi
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________"
echo "---------------------------------- SHA512 TEST (FILE) ----------------------------"

printf "\e[1m%-140s%-20s\e[0m\n" "SHA512SUM_OUTPUT" "ft_ssl-OUTPUT"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha512 -q test1`
	SHA512SUM_OUTPUT=`sha512sum test1 | awk '{print $1}'`

	if [[ $FT_SSL_OUTPUT == $SHA512SUM_OUTPUT ]]
	then
		printf "\e[32m%-140s\e[1m%-20s\e[0m\n" "$SHA512SUM_OUTPUT" "OK"
		# cp test1 sucsess_test_$i
	else
		printf "\e[31m%-140s\e[1m%-20s\e[0m\n" "$SHA512SUM_OUTPUT" "Fail"
		cp test1 fail_test_$i
	fi
done
