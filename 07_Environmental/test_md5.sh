FILENAME="check.test"
echo fgdfgdafddbxvvbxcbsdgag  > $FILENAME

REAL_MD5=($(md5sum ${FILENAME}))
MD5=$(echo "MD5 ${FILENAME}" | ./rhasher)

test $REAL_MD5 = $MD5;
