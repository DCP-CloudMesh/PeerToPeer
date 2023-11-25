# run ngrok http 8080 on command line
from pyngrok import ngrok as ngk
import ngrok
import sys
import os

client = ngrok.Client(os.environ['NGROK_TOKEN'])

# check for command line arguments
port = 8080
if len(sys.argv) == 2:
    port = sys.argv[1]

# get the open tunnels
for e in client.endpoints.list():
    print(e.public_url)

