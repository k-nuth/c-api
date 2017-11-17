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

function increment_py_version {
    while read p; do
        if [[ $p == "__version__ ="* ]]; then
            # echo "$1: $2" >> version.py.t
            # echo "__version__ = '1.1.9'" | perl -pe 's/\b(\d+)(?=\D*$)/$1+1/e'
            echo $p | perl -pe 's/\b(\d+)(?=\D*$)/$1+1/e' >> version.py.t
        else
            echo $p >> version.py.t
        fi
    done <version.py
    mv version.py{.t,}
}  


# --------------------------------------------------------------------------------------------------------------------


set -e
set -x

git config --global user.email "ci@bitprim.org"
git config --global user.name "Bitprim CI"

mkdir temp
cd temp

# --------------------------------------------------------------------------------------------------------------------


# --------------------------------------------------------------------------------------------------------------------
# bitprim-py-native
# --------------------------------------------------------------------------------------------------------------------
git clone https://github.com/bitprim/bitprim-py-native.git

cd bitprim-py-native
echo "Travis branch: ${TRAVIS_BRANCH}"
git checkout ${TRAVIS_BRANCH}

replace_versions bitprim-node-cint $BITPRIM_BUILD_NUMBER
increment_py_version

cat versions.txt
cat version.py

git add . versions.txt
git add . version.py
git commit --message "Travis bitprim-node-cint build: $BITPRIM_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER" || true
git remote add origin-commit https://${GH_TOKEN}@github.com/bitprim/bitprim-py-native.git > /dev/null 2>&1
git push --quiet --set-upstream origin-commit ${TRAVIS_BRANCH}  || true

cd ..

# --------------------------------------------------------------------------------------------------------------------
# bitprim-js-native
# --------------------------------------------------------------------------------------------------------------------
git clone https://github.com/bitprim/bitprim-js-native.git

cd bitprim-js-native
echo "Travis branch: ${TRAVIS_BRANCH}"
git checkout ${TRAVIS_BRANCH}

npm version patch
replace_versions bitprim-node-cint $BITPRIM_BUILD_NUMBER
# increment_py_version

cat versions.txt
# cat version.py

git add . versions.txt
# git add . version.py
git commit --message "Travis bitprim-node-cint build: $BITPRIM_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER" || true
git remote add origin-commit https://${GH_TOKEN}@github.com/bitprim/bitprim-py-native.git > /dev/null 2>&1
git push --quiet --set-upstream origin-commit ${TRAVIS_BRANCH}  || true

cd ..

# --------------------------------------------------------------------------------------------------------------------
