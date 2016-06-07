echo "#ifndef "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> ${1}.hpp
echo "# define "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> ${1}.hpp
echo "" >> ${1}.hpp
echo "class	"`echo ${1^}` >> ${1}.hpp
echo "{" >> ${1}.hpp
echo "public:" >> ${1}.hpp
cat ${1}.cpp | grep `echo ${1^}"::"` | sed s/`echo ${1^}"::"`// >> ${1}.hpp
echo "};" >> ${1}.hpp
echo "" >> ${1}.hpp
echo "#endif // "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> ${1}.hpp
