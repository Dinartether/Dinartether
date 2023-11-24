 #!/usr/bin/env bash

 # Execute this file to install the dinartether cli tools into your path on OS X

 CURRENT_LOC="$( cd "$(dirname "$0")" ; pwd -P )"
 LOCATION=${CURRENT_LOC%Dinartether-Qt.app*}

 # Ensure that the directory to symlink to exists
 sudo mkdir -p /usr/local/bin

 # Create symlinks to the cli tools
 sudo ln -s ${LOCATION}/Dinartether-Qt.app/Contents/MacOS/dinartetherd /usr/local/bin/dinartetherd
 sudo ln -s ${LOCATION}/Dinartether-Qt.app/Contents/MacOS/dinartether-cli /usr/local/bin/dinartether-cli
