import socket
import sys

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Argumentos insuficientes")
        sys.exit()

    ip  = sys.argv[1]
    port = int(sys.argv[2])

    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.connect((ip, port))
    except:
        server = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
        server.connect((ip, port))
        
    while True:
        string = input()
        server.send(bytes(string, "ascii"))
        
        # Killing command
        if(string == "kill"):
            break
        buffer = server.recv(500)
        buffer = buffer.decode("ascii")

        print(buffer)