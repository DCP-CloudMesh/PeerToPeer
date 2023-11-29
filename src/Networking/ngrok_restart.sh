# grabs the PID for the current running ngrok
ngrok_pid=$(pgrep ngrok)

# kills ngrok if ngrok running
if [ $ngrok_pid ]; then
echo "Current ngrok PID = ${ngrok_pid}"
kill_ngrok_pid=$(kill -9 $ngrok_pid)

# get exit status code for last command
check=$?
fi

# re-start ngrok
$(ngrok tcp 8181 &)
