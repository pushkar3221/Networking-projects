from scapy.all import *

portlist = range (0,101) #range of port addresses 0-100

ip = "10.10.111.1"
syn = 0x12
rst = 0x14
openp = []
closed = []
filtered = []

for val in portlist:
	source = RandShort()
	conf.verb = 0 #stops logs from printing
	synpacket = sr1(IP(dst = ip)/TCP(sport = source, dport = val, flags = 'S')) #creates a SYN packet and sends packet and recieves the reply
	flags = synpacket.getlayer(TCP).flags
	if flags == syn:
		openp.append(val)
		print "port: ",val,": Open"
	else:
		closed.append(val)
	resetpacket = IP(dst = ip)/TCP(sport = source, dport = val, flags = 'R') #creates RST packet to release port and moves to next loop
	send(resetpacket)

print "Number of Open ports are: ", len(openp)
print "Number of Closed ports are: ", len(closed)
			
