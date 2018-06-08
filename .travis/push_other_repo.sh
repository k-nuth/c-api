#!/bin/bash

function replace_versions {
    # echo $1 #project name
    # echo $2 #build number
    if [ ! -f versions.txt ]; then
        echo "$1: $2" >> versions.txt
    else
        #cat versions.txt
        while read p; do
            if [[ $p == *"$1:"* ]]; then
                echo "$1: $2" >> versions.txt.t
            else
                echo $p >> versions.txt.t
            fi
        done <versions.txt

        #cat versions.txt
        #cat versions.txt.t

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

echo "Travis branch: ${TRAVIS_BRANCH}"
echo "Travis tag: ${TRAVIS_TAG}"

if [[ ${TRAVIS_BRANCH} == ${TRAVIS_TAG} ]]; then
    export BITPRIM_BRANCH=master
else
    export BITPRIM_BRANCH=${TRAVIS_BRANCH}
fi
echo "Bitprim branch: ${BITPRIM_BRANCH}"

echo "Travis branch: ${TRAVIS_BRANCH}"
echo "Travis tag: ${TRAVIS_TAG}"

if [[ ${TRAVIS_BRANCH} == ${TRAVIS_TAG} ]]; then
    export BITPRIM_BRANCH=master
else
    export BITPRIM_BRANCH=${TRAVIS_BRANCH}
fi
echo "Bitprim branch: ${BITPRIM_BRANCH}"

# --------------------------------------------------------------------------------------------------------------------
# bitprim-cs
# --------------------------------------------------------------------------------------------------------------------

body="{
    \"accountName\": \"bitprim\",
    \"projectSlug\": \"bitprim-cs\",
    \"branch\": \"$BITPRIM_BRANCH\",
    \"environmentVariables\": {
       \"SKIP_NUGET\": \"true\"
    }
}"

curl -s -d "$body" -X POST -H "Authorization: Bearer $APPVEYOR_TOKEN" -H "Content-Type: application/json" https://ci.appveyor.com/api/builds


body="{
\"request\": {
\"branch\":\"$BITPRIM_BRANCH\"
}}"


curl -s -X POST \
   -H "Content-Type: application/json" \
   -H "Accept: application/json" \
   -H "Travis-API-Version: 3" \
   -H "Authorization: token MKay9Pzmsyb4MCeZj9Fb6g" \
   -d "$body" \
   https://api.travis-ci.org/repo/bitprim%2Fbitprim-cs/requests


# --------------------------------------------------------------------------------------------------------------------



# --------------------------------------------------------------------------------------------------------------------
# bitprim-py-native
# --------------------------------------------------------------------------------------------------------------------
git clone https://github.com/bitprim/bitprim-py-native.git

cd bitprim-py-native
git checkout ${BITPRIM_BRANCH}

replace_versions bitprim-node-cint $BITPRIM_BUILD_NUMBER
increment_py_version

cat versions.txt
cat version.py

git add . versions.txt
git add . version.py
git commit --message "Travis bitprim-node-cint build: $BITPRIM_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER" || true
git remote add origin-commit https://${GH_TOKEN}@github.com/bitprim/bitprim-py-native.git > /dev/null 2>&1
git push --quiet --set-upstream origin-commit ${BITPRIM_BRANCH}  || true

cd ..

# --------------------------------------------------------------------------------------------------------------------


# --------------------------------------------------------------------------------------------------------------------
# bitprim-js-native
# --------------------------------------------------------------------------------------------------------------------
git clone https://github.com/bitprim/bitprim-js-native.git

cd bitprim-js-native
git checkout ${BITPRIM_BRANCH}
git pull

# npm version patch
replace_versions bitprim-node-cint $BITPRIM_BUILD_NUMBER

cat versions.txt

git add . versions.txt
git commit --message "Travis bitprim-node-cint build: $BITPRIM_BUILD_NUMBER, $TRAVIS_BUILD_NUMBER [skip ci]" || true
git remote add origin-commit https://${GH_TOKEN}@github.com/bitprim/bitprim-js-native.git > /dev/null 2>&1
git push --quiet --set-upstream origin-commit ${BITPRIM_BRANCH}  || true

npm version patch
git push --quiet --set-upstream origin-commit ${BITPRIM_BRANCH}  || true

cd ..

# --------------------------------------------------------------------------------------------------------------------

