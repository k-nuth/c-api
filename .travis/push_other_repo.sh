#!/bin/bash

function replace_versions {
    # echo $1 #project name
    # echo $2 #build number
    if [ ! -f versions.txt ]; then
        echo "$1: $2" >> versions.txt
    else
        while read p; do
            if [[ $p == *"$1:"* ]]; then
                echo "$1: $2" >> versions.txt.t
            else
                echo $p >> versions.txt.t
            fi
        done <versions.txt
        mv versions.txt{.t,}
    fi
}  

set -e
set -x

# git config --global user.email "ci@bitprim.org"
# git config --global user.name "Bitprim CI"

# mkdir temp
# cd temp

# # git clone https://github.com/bitprim/bitprim-node-exe.git --depth 1
# git clone https://github.com/bitprim/bitprim-node-exe.git

# cd bitprim-node-exe
# echo "Travis branch: ${TRAVIS_BRANCH}"
# git checkout ${TRAVIS_BRANCH}

# replace_versions bitprim-node-cint $BITPRIM_BUILD_NUMBER

# cat versions.txt
# git add . versions.txt
# git commit --message "Travis bitprim-node-cint build: $BITPRIM_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER" || true
# git remote add origin-commit https://${GH_TOKEN}@github.com/bitprim/bitprim-node-exe.git > /dev/null 2>&1
# git push --quiet --set-upstream origin-commit ${TRAVIS_BRANCH}  || true
