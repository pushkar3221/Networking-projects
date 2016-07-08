from scapy.all import *

portlist = range (0,101) #range of port addresses 0-100

ip = "10.10.111.1"
openp = []
openf = []
closed = []
filtered = []

for val in portlist:
	source = RandShort()
	conf.verb = 0 #stops logs from printing
	udppacket = sr1(IP(dst = ip)/UDP(sport = source, dport = val), timeout = 10) #creates a SYN packet and sends packet and recieves the reply
	if str(type(udppacket)) == "<type 'NoneType'>":
		openf.append(val)
		print "port: ",val,": Open|Filtered"
	elif (udppacket.haslayer(UDP)):
		openp.append(val)
		print "port: ",val,": Open"
	elif (udppacket.haslayer(ICMP)):
		if (int(udppacket.getlayer(ICMP).type) == 3 and int(udppacket.getlayer(ICMP).code) in [1, 2, 9, 10, 13]):
			filtered.append(val)
			print "port: ",val,": Filtered"
		elif (int(udppacket.getlayer(ICMP).type) == 3 and int(udppacket.getlayer(ICMP).code) == 3):
			closed.append(val)



print "Number of Open ports are: ", len(openp)
print "Number of Open|Filtered ports are: ", len(openf)
print "Number of Closed ports are: ", len(closed)
print "Number of Filtered ports are: ", len(filtered)

chkport = 53
dnspacket = sr1(IP(dst = ip)/UDP(sport = source, dport = chkport)/DNS(rd =1, qd = DNSQR(qname = "www.nyu.edu")))
print "Port 53 DNS reply: ", dnspacket[DNS].summary
			
