import socket

localip_addr= "192.168.56.104"
port= 20001
buffer= 1024

msgFromServer= "Terima Kasih!"
c= str.encode(msgFromServer)

#create udp socket
UDPserver_sock= socket.socket(family= socket.AF_INET, type= socket.SOCK_DGRAM)
print ("Berjaya buat sokett")

#bind
UDPserver_sock.bind((localip_addr, port))

#listen
print("Soket sedang menunggu client!")

while True:
	bytesAddrPair= UDPserver_sock.recvfrom(buffer)
	
	msg= bytesAddrPair
	addr= bytesAddrPair[1]

	clientMsg= "Dapat capaian dari: "+ str(addr).format(msg)
	print(clientMsg)

	#send reply
	UDPserver_sock.sendto(c, addr)
	buffer= c.recv(1024)
	print(buffer)

	#close
	c.close()
