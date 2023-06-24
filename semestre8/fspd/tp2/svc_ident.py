# João Antonio Oliveira Pedrosa - 2019006752

from concurrent import futures # Usado na definição do pool de threads
import threading
import grpc
import sys
from secrets import token_bytes
import identity_pb2, identity_pb2_grpc # Módulos gerados pelo compilador de gRPC

# Definindo variável global estática para representar um token vazio
EMPTY_TOKEN = bytes(32)

class Identity(identity_pb2_grpc.IdentityServicer):
   """Provê métodos que implementam um serviço de autenticação"""

   def __init__(self, stop_event, super_password):
      self.stop_event = stop_event # Evento para terminar a execução do servidor
      self.passwords = dict() # Dicionário contendo as senhas de cada usuário
      self.permissions = dict() # Dicionário contendo a permissão de cada usuário
      self.tokens = dict() # Dicionário contendo os tokens de cada usuário
      self.tokens_rev = dict() # O mesmo dicionário anterior com chave e valor invertidas
      
      # O dicionário invertido é necessário para 
      # realizar as buscas por tokens em O(1)

      # Inserindo o usuário super
      self.permissions['super'] = "SP"
      self.passwords['super'] = super_password

   def auth(self, request, context):
      """Função de autenticação"""

      # Checa se o usuário existe e se a senha está correta
      if request.id in self.passwords and self.passwords[request.id] == request.password:
         response = 0
         token = token_bytes(32) # Gerando um token aleatório
         self.tokens[request.id] = token # Armazenando o novo token do usuário
         self.tokens_rev[token] = request.id # Armazenando no dicionário invertido
      else:
         response = -1
         token    = EMPTY_TOKEN
      
      # Montando a mensagem e retornando
      return identity_pb2.AuthReply(response=response, token=token)

   def create_user(self, request, context):
      """Função de criação de usuários"""
      
      # Checa se o token da requisição é igual ao token do usuário super
      if request.token == self.tokens['super']:
         self.passwords[request.id] = request.password # Insere ou modifica o usuário
         self.permissions[request.id] = request.permission # Armazena a permissão do usuário
         response = 0
      else:
         response = -1

      # Montando a mensagem e retornando
      return identity_pb2.Integer(value=response)

   def get_permission(self, request, context):
      """Função de verificação de acesso"""

      if request.value in self.tokens_rev:
         user = self.tokens_rev[request.value] # Recupera o usuário associado ao token
         response = self.permissions[user] # Recupera a permissão do usuário
      else:
         response = "NE"
      
      # Montando a mensagem e retornando
      return identity_pb2.String(value=response)

   def exit(self, request, context):
      """Função de fim da execução"""
      response = len(self.passwords) - 1
      self.stop_event.set() # Definindo o evento que encerrará o servidor

      # Montando a mensagem e retornando
      return identity_pb2.Integer(value=response)



def serve(port, super_password):
   stop_event = threading.Event() # Definindo o evento de parada
   server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
   
   # Ligando o servidor ao objeto que identifica os
   # procedimentos a serem executados.
   identity_pb2_grpc.add_IdentityServicer_to_server(Identity(stop_event, super_password), server)
   server.add_insecure_port('localhost:'+port)

   server.start()
   stop_event.wait() # Aqui nós esperamos a captura do evento que definimos
   server.stop(None) # Após o evento ser detectado, encerramos o servidor

if __name__ == '__main__':
   port = sys.argv[1]
   super_password = int(sys.argv[2])
   serve(port, super_password)
