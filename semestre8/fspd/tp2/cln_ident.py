from __future__ import print_function # usado internamente nos stubs
import sys
import grpc

import identity_pb2, identity_pb2_grpc # módulos gerados pelo compilador de gRPC

token = None # Token de Autenticação

# Irei ser mais breve nos comentários do cliente pois o código
# é bem mais simples. Basicamente as funções repassam a entrada
# para o servidor usando o stub que é passado a elas como argumento
# e imprimem a resposta obtida.

def auth(stub, id, password):
    global token

    message  = identity_pb2.AuthRequest(id=id, password=password)
    response = stub.auth(message)

    if(response.response == 0): # Autenticação bem sucedida
        token = response.token
    else: # Falha na autenticação
        token = None

def create_user(stub, id, password, permission):
    global token

    if token is None:
        print('-9')
        return

    message   = identity_pb2.CreateUserRequest(id=id, password=password, permission=permission, token=token)
    response = stub.create_user(message)
    print(response.value)

def get_permission(stub):
    global token
    
    if token is None:
        print('-9')
        return
    
    message  = identity_pb2.Bytes(value=token)
    response = stub.get_permission(message)
    print(response.value)

def exit(stub):
    response = stub.exit(identity_pb2.Empty())
    print(response.value)

def run(address):
    # Abrindo um canal para o servidor
    channel = grpc.insecure_channel(address)
    # Criando o stub
    stub = identity_pb2_grpc.IdentityStub(channel)

    while(1):
        try:
            action = input()
        except:
            break
        if action[0] == 'A': # Autenticação
            _, id, password = action.split()
            auth(stub, id, int(password))
        elif action[0] == 'C': # Criar usuário
            _, id, password, permission = action.split()
            create_user(stub, id, int(password), permission)
        elif action[0] == 'V': # Verificação de acesso
            get_permission(stub)
        elif action[0] == 'F': # Fim de execução
            exit(stub)
            break
    
    # Terminando a saída com EOF e fechando o canal
    channel.close()

if __name__ == '__main__':
    address = sys.argv[1]
    run(address)
