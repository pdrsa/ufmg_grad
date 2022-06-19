import socket
from random import seed
from random import random
import sys

variables = {"01": set(), "02": set(), "03": set(), "04": set()}

def terminate(client, answer):
    client.send(bytes(answer, "ascii"))
    client.close()

def send(client, answer):
    client.send(bytes(answer, "ascii"))

def receive(client):
    string = client.recv(500)
    string = string.decode("ascii")

    return string

def parseCommand(string):
    message         = string.split()
    action, message = message[0], message[1:]
    equipment = message[-1]
    sensors   = message[1:-2] if action != "read" else message[:-2]

    return action, sensors, equipment

def addSensors(sensors, equipment):
    check = False
    answer = "sensor "
    for s in sensors:
        if len(variables['01']) + len(variables['02']) + len(variables['03']) + len(variables['04']) >= 15:
            return "limit exceeded"
        if s in variables[equipment]:
            check = True
        variables[equipment].add(s)
        answer += s + " "
    answer += "added"

    # Check if all sensors are new
    if check:
        return f"sensor {s} already exists in {equipment}"
    
    return answer

def readSensors(sensors, equipment):
    # Check if all sensors are installed
    for s in sensors:
        if s not in variables[equipment]:
            return f"sensor(s) {s} not installed"
    
    answer = ""
    for s in sensors:
        answer += str(int(random() * 1000)/100) + " "
    return answer 

def removeSensors(sensors, equipment):
    check = False    
    answer = "sensor "
    for s in sensors:
        if s not in variables[equipment]:
            check = True
        variables[equipment].discard(s)
        answer += s + " "
    answer += "removed"

    # Check if all sensors are installed
    if check:
        return f"sensor {s} does not exist in {equipment}"
    
    return answer 

def listSensors(equipment):
    answer = ""
    if len(variables[equipment]) == 0:
        return "none"
    for s in variables[equipment]:
        answer += s + " "
    return answer

def checkCommand(sensors, equipment):
    for sensor in sensors:
        if sensor not in variables:
            return False, "invalid sensor"
    if equipment not in variables:
        return False, "invalid equipment"
    return True, ""

if __name__ == "__main__":
    
    if len(sys.argv) < 3:
        print("Argumentos insuficientes")
        sys.exit()

    ipv  = sys.argv[1]
    port = int(sys.argv[2])

    if ipv == "v6":
        server = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
        server.bind(('', port))
    else:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(('', port))

    server.listen(1)
    
    server_online = True
    while server_online:
        client, address = server.accept()

        # Receiving messages
        while True:
            string = receive(client)
            print(string)
            answer = ""

            # Killing command
            if(string == 'kill'):
                terminate(client, "")
                server_online = False
                break

            # Spliting command and defining variables
            action, sensors, equipment = parseCommand(string)

            # Checking if variables are okay       
            ok, answer = checkCommand(sensors, equipment)
            if not ok:
                send(client, answer)
                continue

            # Performing actions
            if   action == "add":
                answer = addSensors(sensors, equipment)
            elif action == "read":
                answer = readSensors(sensors, equipment)
            elif action == "remove":
                answer = removeSensors(sensors, equipment)
            elif action == "list":
                answer = listSensors(equipment)
            else:
                terminate(client, answer)
                break

            # Send message
            send(client, answer)
        client.close()