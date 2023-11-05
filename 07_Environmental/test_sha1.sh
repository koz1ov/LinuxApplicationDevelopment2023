FILENAME="check.test"
echo fgdfgdafddbxvvbxcbsdgag  > $FILENAME

REAL_SHA1=($(sha1sum ${FILENAME}))
SHA1=$(echo "SHA1 ${FILENAME}" | ./rhasher)

test $REAL_SHA1 = $SHA1;
