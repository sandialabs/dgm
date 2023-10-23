#!/usr/bin/env bash

# This script is from the Sandia FAST project.
# Old repo: svn+ssh://software.sandia.gov/svn/public/fast/hudson/common
# New repo: svn checkout --username guest https://teamforge.sandia.gov/svn/repos/fast

PIPEFAIL_OFF=`set -o | grep pipefail | grep off | wc -l`
if test $PIPEFAIL_OFF -gt 0; then
    set -o pipefail
fi

echo
echo "Building on `hostname`:"
echo
echo "  Workspace: ${WORKSPACE}"
echo
echo "  Package: ${PACKAGE}"
echo
echo "  Environment:"
/usr/bin/env 2>&1 | sort | sed 's/^/    /'
echo
echo "  Python:"
python -c 'import sys; print sys.version' 2>&1 | sed 's/^/    /'
echo
echo "  Java:"
java -version 2>&1 | sed 's/^/    /'
echo

# The following executables are required (missing app yields build failure)
for app in gcc autoconf automake m4; do
echo "  $app:"
$app --version 2>&1 | grep -v '^$' | sed 's/^/    /' || exit 1
echo
done

# Libtool is a required special case: the "version" option is different
# on Mac, so we will do two checks
echo "  libtool:"
ver_info=`libtool --version 2>&1`
if test $? -ne 0; then
    ver_info1=`libtool -V 2>&1`
    if test $? -ne 0; then
        echo "$ver_info" | grep -v '^$' | sed 's/^/    /' 
        echo
        echo "$ver_info1" | grep -v '^$' | sed 's/^/    /' 
        exit 1
    fi
    ver_info="$ver_info1"
fi
echo "$ver_info" | grep -v '^$' | sed 's/^/    /'  
echo

# The following executables are "nice to have" (missing does not fail build)
set +o pipefail
for app in svn; do
    echo "  $app:"
    $app --version 2>&1 | grep -v '^$' | sed 's/^/    /'
    echo
done

if test $PIPEFAIL_OFF -eq 0; then
    set -o pipefail
fi
