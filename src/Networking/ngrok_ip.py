# run ngrok http 8080 on command line
import ngrok
import sys
import os
from dotenv import load_dotenv

load_dotenv()

client = ngrok.Client(os.getenv('NGROK_TOKEN'))

# check for command line arguments
port = 8080
if len(sys.argv) == 2:
    port = sys.argv[1]

# get the open tunnels
while len(list(client.endpoints.list())) == 0:
    pass

for e in client.endpoints.list():
    print(e.public_url)