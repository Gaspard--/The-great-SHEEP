head ${1} -n ${2}
echo ${3}
tail ${1} -n $((`cat ${1} | wc -l` - ${2}))
