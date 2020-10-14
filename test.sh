#!/bin/bash

function setColor {
	if [[ "$1" = "OK" ]]; then
		echo "1;32"; else
		echo "1;31";
	fi
}

function funcCompare {
	if [[ $1 == $2 ]]; then
		echo "OK"; else
		echo "Fail";
	fi
}

function funcCompareStatus {
	STATUS=$( funcCompare $1 $2);
	echo -e "\e[$( setColor $STATUS)m$STATUS\e[0m";
}

EVENTS=3

HASH_LENTH=40
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "------------------------------ MD5 TEST (STDIN/STRING) ---------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "MD5SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl md5 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl md5 -q -s $STRING`
	MD5SUM_OUTPUT=`echo -n "$STRING" | md5sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$MD5SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $MD5SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $MD5SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "----------------------------------- MD5 TEST (FILE) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "MD5SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl md5 -q test1`
	MD5SUM_OUTPUT=`md5sum test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$MD5SUM_OUTPUT" $( funcCompareStatus $MD5SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=70
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "------------------------- SHA256 TEST (STDIN/STRING) -----------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA256SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha256 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha256 -q -s $STRING`
	SHA256SUM_OUTPUT=`echo -n "$STRING" | sha256sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA256SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA256SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA256SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "---------------------------------- SHA256 TEST (FILE) ----------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA256SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha256 -q test1`
	SHA256SUM_OUTPUT=`sha256sum test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA256SUM_OUTPUT" $( funcCompareStatus $SHA256SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=60
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "-------------------------- SHA224 TEST (STDIN/STRING) ----------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA224SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha224 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha224 -q -s $STRING`
	SHA224SUM_OUTPUT=`echo -n "$STRING" | sha224sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA224SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA224SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA224SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "---------------------------------- SHA224 TEST (FILE) ----------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA224SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha224 -q test1`
	SHA224SUM_OUTPUT=`sha224sum test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA224SUM_OUTPUT" $( funcCompareStatus $SHA224SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=130
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "----------------------- SHA512 TEST (STDIN/STRING) -------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA512SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha512 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha512 -q -s $STRING`
	SHA512SUM_OUTPUT=`echo -n "$STRING" | sha512sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA512SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA512SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA512SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "-------------------------------- SHA512 TEST (FILE) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA512SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha512 -q test1`
	SHA512SUM_OUTPUT=`sha512sum test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA512SUM_OUTPUT" $( funcCompareStatus $SHA512SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=100
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "------------------------ SHA384 TEST (STDIN/STRING) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA384SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha384 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha384 -q -s $STRING`
	SHA384SUM_OUTPUT=`echo -n "$STRING" | sha384sum | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA384SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA384SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA384SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "-------------------------------- SHA384 TEST (FILE) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA384SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha384 -q test1`
	SHA384SUM_OUTPUT=`sha384sum test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA384SUM_OUTPUT" $( funcCompareStatus $SHA384SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=60
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "--------------------- SHA512-224 TEST (STDIN/STRING) -----------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA512-224SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha512-224 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha512-224 -q -s $STRING`
	SHA512_224SUM_OUTPUT=`echo -n "$STRING" | openssl sha512-224 -r | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA512_224SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA512_224SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA512_224SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "---------------------------- SHA512-224 TEST (FILE) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA512-224SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha512-224 -q test1`
	SHA512_224SUM_OUTPUT=`openssl sha512-224 -r test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA512_224SUM_OUTPUT" $( funcCompareStatus $SHA512_224SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done

HASH_LENTH=70
MAX_LENTH=20
echo "________________________________________________________________________________________________________________________________________________________________"
echo "-------------------- SHA512-256 TEST (STDIN/STRING) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$MAX_LENTH"s %-"$HASH_LENTH"s%-10s\e[0m\n" "STRING" "SHA512-256SUM_OUTPUT" "ft_ssl"

for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	STRING=`head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) ; echo ''`
	FT_SSL_STDIN_OUTPUT=`echo -n $STRING | ./ft_ssl sha512-256 -q`
	FT_SSL_STRING_OUTPUT=`./ft_ssl sha512-256 -q -s $STRING`
	SHA512_256SUM_OUTPUT=`echo -n "$STRING" | openssl sha512-256 -r | awk '{print $1}'`

	printf "%-"$MAX_LENTH"s %-"$HASH_LENTH"s" "$STRING" "$SHA512_256SUM_OUTPUT"

	printf "%-16s" $( funcCompareStatus $SHA512_256SUM_OUTPUT $FT_SSL_STDIN_OUTPUT)
	printf "%-16s" $( funcCompareStatus $SHA512_256SUM_OUTPUT $FT_SSL_STRING_OUTPUT)
	printf "\n"
done

MAX_LENTH=1000
echo "________________________________________________________________________________________________________________________________________________________________"
echo "---------------------------- SHA512-256 TEST (FILE) ------------------------------------------------------------------------------------------------------------"

printf "\e[1m%-"$HASH_LENTH"s%-10s\e[0m\n" "SHA512-256SUM_OUTPUT" "ft_ssl"
for (( i=1; i <= $EVENTS; i++ ))
do
	# генерим случайную строку длиной от 1 до MAX_LENTH символов
	head /dev/urandom | tr -dc A-Za-z0-9 | head -c $((1 + RANDOM % $MAX_LENTH)) > test1
	FT_SSL_OUTPUT=`./ft_ssl sha512-256 -q test1`
	SHA512_256SUM_OUTPUT=`openssl sha512-256 -r test1 | awk '{print $1}'`

	printf "%-"$HASH_LENTH"s%-16s" "$SHA512_256SUM_OUTPUT" $( funcCompareStatus $SHA512_256SUM_OUTPUT $FT_SSL_OUTPUT)
	printf "\n"
done
