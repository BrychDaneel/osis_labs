#!/usr/bin/awk -f

NF==3 \
&& $1~/^[А-Яа-яa-zA-Z]*$/ \
&& $2~/^[1-9][0-9]*$/ \
&& $3~/^[0-9]*(.[0-9]+)?$/ \
    {count[$1]+=$2; sum[$1]+=$3}

END {
    for (good in count){
        print(good " " count[good] " " sum[good]/count[good] " " sum[good])
    }
}
