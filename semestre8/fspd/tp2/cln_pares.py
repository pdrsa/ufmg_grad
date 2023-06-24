# João Antonio Oliveira Pedrosa - 2019006752

from __future__ import print_function # usado internamente nos stubs
import sys
import grpc

import identity_pb2, identity_pb2_grpc, pairs_pb2, pairs_pb2_grpc # módulos gerados pelo compilador de gRPC

token = None # Token de Autenticação

def auth(stub, id, password):
    global token

    # Enviando requisição de autenticação
    message  = identity_pb2.AuthRequest(id=id, password=password)
    response = stub.auth(message)

    if(response.response == 0): # Autenticação bem sucedida
        token = response.token
    else: # Falha na autenticação
        token = None

def insert(stub, key, value):
    global token
    if token is None:
        print('-9')
        return
    
    # Enviando requisição de inserção
    message  = pairs_pb2.InsertRequest(key=key, value=value, token=token)
    response = stub.insert(message)
    print(response.value)

def query(stub, key):
    global token
    if token is None:
        print('')
        return
    
    # Enviando requisição de consulta
    message  = pairs_pb2.QueryRequest(key=key, token=token)
    response = stub.query(message)
    print(response.value)

def exit_auth(stub):
    response = stub.exit(identity_pb2.Empty())
    print(response.value)

def exit_pairs(stub):
    stub.exit(pairs_pb2.Empty())

def run(address_auth, address_pairs):
    # Abrindo um canal para o servidor de autenticação
    channel_auth = grpc.insecure_channel(address_auth)
    # Criando o stub
    stub_auth = identity_pb2_grpc.IdentityStub(channel_auth)
    # Abrindo um canal para o servidor de autenticação
    channel_pairs = grpc.insecure_channel(address_pairs)
    # Criando o stub
    stub_pairs = pairs_pb2_grpc.PairsStub(channel_pairs)

    while(1):
        try:
            action = input()
        except:
            break
        if action[0] == 'A': # Autenticação
            _, id, password = action.split()
            auth(stub_auth, id, int(password))
        elif action[0] == 'I': # Criar chave
            _, key, value = action.split()
            insert(stub_pairs, int(key), value)
        elif action[0] == 'C': # Consulta chave
            _, key = action.split()
            query(stub_pairs, int(key))
        elif action[0] == 'T': # Finaliza o servidor de pares
            exit_pairs(stub_pairs)
            break
        elif action[0] == 'F': # Finaliza o servidor de identificação
            exit_auth(stub_auth)
            break
    
    # Terminando a saída com EOF e fechando o canal
    channel_pairs.close()
    channel_auth.close()

if __name__ == '__main__':
    address_auth  = sys.argv[1]
    address_pairs = sys.argv[2]
    run(address_auth, address_pairs)
