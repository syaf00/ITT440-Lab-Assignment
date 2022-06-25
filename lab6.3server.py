import socket
import sys
import math         #math library
from multiprocessing import Process

ok_message= '\nHTTP/1.0 200 OK\n\n'
nok_message= '\nHTTP/1.0 404 NotFound\n\n'

def startprocess(s_sock):
    s_sock.send(str.encode("\t\tOnline Calculator\n\tOPERATIONS: LOG, SQUARE ROOT, EXPONENTIAL\n\t-----How: <log/sqrt/exp> <number>-----\n\t\t*****Example: exp 2*****\n\t\t#To exit, enter E#"))
    while True:
	#get input from client
        data= s_sock.recv(2048)
        data= data.decode("utf-8")
        
        #calculation
        try:
            op, val= data.split()
            o= str(op)
            num= int(val)
        
            if o[0] == 'l':
                o= 'Log'
                ans= math.log10(num)
            elif o[0] == 's':
                o= 'Square root'
                ans= math.sqrt(num)
            elif o[0] == 'e':
                o= 'Exponential'
                ans= math.exp(num)
            else:
                ans= ('[!!]ERROR.INVALID OPERATION')
        
            sendAns= (str(o) + '(' + str(num) + ') = ' + str(ans))
            print ('[/]Calculation done.')
        except:
            print ('[!]Invalid input')
            sendAns= ('[!]Invalid input')
    
        
        if not data:
            break
            
        s_sock.send(str.encode(sendAns))

    s_sock.close()

if __name__ == '__main__':
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("",8080))
    print("Listening...")
    s.listen(28)                                        
    
    try:
        while True:
            try:
                s_sock, s_addr= s.accept()
                p= Process(target= startprocess, args= (s_sock,))
                p.start()

            except socket.error:

                print('[!]Socket error')

            except Exception as e:        
                print("[!]An exception has occurred!")
                print(e)
                sys.exit(1)
    finally:
     	   s.close()
