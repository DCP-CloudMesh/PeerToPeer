    #!/bin/bash

    # grabs the PID for the current running ngrok
    ngrok_pid=$(pgrep ngrok)

    # kills ngrok if ngrok running
    if [ $ngrok_pid ]; then
    echo "Current ngrok PID = ${ngrok_pid}"
    kill_ngrok_pid=$(kill -9 $ngrok_pid)    

    # get exit status code for last command
    check=$?
    fi

    # Check if a port is provided as a command line argument
    if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <port>"
    exit 1
    fi

    port=$1

    # re-start ngrok
    $(ngrok tcp $port &)
