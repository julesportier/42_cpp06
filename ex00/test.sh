#!/usr/bin/env bash

test() {
	echo -e "\e[1mCONVERT ${1}:\e[0m"
	./convert "${1}"
}

# fails
# parsing
test '0'
test '-10'
# formating
# test '42.00002'
# test '42.000002'
# test '42.0000002'
# test '42.00000002'
# test '42.00000000000002'

# succeeds
# test '42'
# test '*'
# test '42.0'
# test '42.02'
# test '42.002'
# test '42.0002'
# test '42.000000000000002'
#
# test 'nan'
# test 'nanf'
# test '+inf'
# test '+inff'
# test '-inf'
# test '-inff'
#
# test '127'
# test '128'
# test '2147483647' #INT_MAX
# test '2147483648' #INT overflow
# test '-2147483647' #INT_MIN
# test '-2147483648' #INT_MIN
# test '9223372036854775807' #LLONG_MAX
# test '-9223372036854775807' #LLONG_MIN
