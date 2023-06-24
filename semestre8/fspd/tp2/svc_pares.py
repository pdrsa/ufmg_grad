# João Antonio Oliveira Pedrosa - 2019006752

from concurrent import futures # Usado na definição do pool de threads
import threading
import grpc
import sys
from secrets import token_bytes
import identity_pb2, identity_pb2_grpc, pairs_pb2, pairs_pb2_grpc # Módulos gerados pelo compilador de gRPC

# Definindo variável global estática para representar um token vazio
EMPTY_TOKEN = bytes(32)

class Pairs(pairs_pb2_grpc.PairsServicer):
   """Provê métodos que implementam um serviço de armazenamento"""

   def __init__(self, stop_event, stub):
      self.stop_event = stop_event # Evento para terminar a execução do servidor
      self.stub = stub # O stub para a comunicação com o servidor de autenticação
      self.db = dict() # Dicionário contendo as chaves e valores armazenadas
      
   def insert(self, request, context):
      """Função de inserção"""
      # Dicionário de Retornos
      # Utilizado para decidir o que retornar de acordo com a resposta da autenticação
      # assim, evitamos o uso extensivo de ifs
      ret_dict = {
         "RO":-1,
         "NE":-2,
         "SP":-3
         }

      # Recuperando a permissão do usuário no servidor de autenticação
      message  = identity_pb2.Bytes(value=request.token)
      auth_response = self.stub.get_permission(message)
      permission = auth_response.value

      if permission == "RW":
         self.db[request.key] = request.value # Inserindo no banco de dados
         response = 0
      else:
         response = ret_dict[permission]
      
      # Montando a mensagem e retornando
      return pairs_pb2.Integer(value=response)

   def query(self, request, context):
      """Função de consulta"""
      
      # Recuperando a permissão do usuário no servidor de autenticação
      message  = identity_pb2.Bytes(value=request.token)
      auth_response = self.stub.get_permission(message)
      permission = auth_response.value
      response = ""
      
      # Checando a permissão do usuário
      if permission == "RW" or permission == "RO":
         if request.key in self.db: # Checando se existe a chave no banco de dados
            response = self.db[request.key] # Recuperando o valor do banco de dados
      
      # Montando a mensagem e retornando
      return pairs_pb2.String(value=response)

   def exit(self, request, context):
      """Função de fim da execução"""
      
      self.stop_event.set() # Definindo o evento que encerrará o servidor
      # Montando a mensagem e retornando
      return identity_pb2.Integer(value=0)



def serve(port, auth_address):
   # Abrindo um canal para o servidor de autenticação
   channel = grpc.insecure_channel(auth_address)
   # Criando o stub
   stub = identity_pb2_grpc.IdentityStub(channel)
   # Definindo o evento de parada
   stop_event = threading.Event() 
   server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
   
   # Ligando o servidor ao objeto que identifica os
   # procedimentos a serem executados.
   pairs_pb2_grpc.add_PairsServicer_to_server(Pairs(stop_event, stub), server)
   server.add_insecure_port('localhost:'+port)

   server.start()
   stop_event.wait() # Aqui nós esperamos a captura do evento que definimos
   server.stop(None) # Após o evento ser detectado, encerramos o servidor

if __name__ == '__main__':
   port = sys.argv[1]
   auth_address = sys.argv[2]
   serve(port, auth_address)