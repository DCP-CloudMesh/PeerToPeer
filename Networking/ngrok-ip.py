# run ngrok http 8080 on command line
from pyngrok import ngrok as ngk
import ngrok
import sys

client = ngrok.Client("2YBQtBWMx3e6X4XzzhgJLgqWD2O_5oftTaZ13Ag4Hr1ktHc6e")

# check for command line arguments
if len(sys.argv) == 2:
    port = sys.argv[1]

# open a ssh tunnel
# ssh_tunnel = ngk.connect(port, "tcp")

# get the open tunnels
tunnels = ngk.get_tunnels()

for e in tunnels:
    print(e.public_url)

# keep the program running
input("Press Enter to exit...")
