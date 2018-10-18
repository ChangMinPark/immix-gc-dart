#!/bin/bash

#
#   This script gives two options to build either DEFAULT or IMMIX
#

if [[ $# -eq 0 ]] ; 
then
    echo 'Please specify a mode to build.'
    exit 1
fi

CURRENT_PATH="$(dirname "$0")"
DEFAULT_PATH="$CURRENT_PATH/default"
IMMIX_PATH="$CURRENT_PATH/immix"
RUNTIME_PATH="$(dirname "$CURRENT_PATH")"
ROOT_PATH="$(dirname "$RUNTIME_PATH")"


if [ "$1" = "-h" ]
then
    echo -e " - Usage: $./buildDart.sh [MODE]\n"
    echo -e "    MODE: default or immix\n"
    exit 1
fi

if [ "$1" = "default" ]
then

    # Building default version.
    echo "Start default building..."
    echo " - Copying default files"
    cp -r $DEFAULT_PATH/* $RUNTIME_PATH/.
    echo " - Building"
    cd $ROOT_PATH
    python tools/build.py --mode release --arch x64 create_sdk
    cd -
    echo "Done."

elif [ "$1" = "immix" ]
then

    # Building Immix version.
    echo "Start Immix building..."
    echo " - Copying Immix files"
    cp -r $IMMIX_PATH/* $RUNTIME_PATH/.
    echo " - Building"
    cd $ROOT_PATH
    python tools/build.py --mode release --arch x64 create_sdk 
    cd -
    echo "Done."

else
    echo "Please specify a correct mode name."
fi


