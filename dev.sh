#!/usr/bin/env bash
ARGS=("$@"); ARGC=$#; _TOPDIR=$(dirname `realpath $0`);
source scripts/util.sh

################# Globals #################
_ROUTER_NAME="flumie";
_TC_SLOC="/mmc/home/repos/apps"; _TC_SNAME="mytc.sh";
###########################################
ARG_HELP_ARR=(
	'tcpd' 'run with tcpdump'
	'run '  'run udplog with args'
);
###########################################

main() {
local _a1="${ARGS[@]::1}";
case "$_a1" in
"tcpd") echo "test stuff";
sudo tcpdump -i any udp port 1234 -vv -X
;;
"run") echo "Run program";
./udp -i enp0s31f6
;;
* ) echo "You need to pass an argument. Eg:";
# paint 'wht' '\t./doit.sh '; paint 'ylw' 'arg1 arg2'; paint 'wht' ' .. '; paintln 'ylw' 'argN';
print_help "ARG_HELP_ARR"; exit 1;
;;
esac
}

print_help() { printf "\nAvailable args:\n";
local m; local n; local a; typeset -n a=$1; ((n=${#a[@]},m=n-1)); for ((i=0;i<=m;i++)); do
printf ' * '; paint 'ylw' "${a[i]}"; ((i++)); printf " - %s\n" "${a[((i))]}"; done; echo;
}

main;

echo;


exit 0;

#### end
