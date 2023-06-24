# Study Hall: Plataforma para Criação de Grupos de Estudo

## :raising_hand_man: Membros e Papéis :raising_hand_man:

  * Heitor de Paula Santos Damasceno (Front-end Developer)

  * Antônio Isaac Silva Lima (Full-stack Developer)

  * João Antônio Oliveira Pedrosa (Back-end Developer)
  
  * Evaldo Martins de Souza (Back-end Developer)


## :bulb: Funcional (objetivo do sistema, principais features, etc) :bulb:

### Objetivo do Sistema

 Plataforma web que permite a criação e busca fácil de grupos de estudos, além da administração de tais grupos.

### Principais Features

- Criação de grupos de estudo.

- Criação de perfil de aluno customizável.

- Ferramenta de pesquisa por grupos com filtros customizáveis.

- Sistema de criação de cronograma para o grupo.

- Página do grupo para "posts" dos membros. 

## :wrench: Tecnologias :wrench:

  * Vue.js (Front-end)

  * Python + FastAPI (Back-end)

  * MySQL (Banco de Dados)

## :book: Backlog do Produto :book:

- Como aluno, eu quero criar, customizar e administrar um grupo de estudo.

- Como aluno, eu quero receber sugestões de grupos de acordo com minhas preferências.

- Como aluno, eu quero ter um perfil pessoal com informações.

- Como aluno, eu quero poder pesquisar grupos de acordo com meus interesses.

- Como membro de um grupo, eu gostaria de criar postagens na página do grupo de estudos.

- Como administrador de um grupo, eu quero criar um cronograma para meu grupo de estudos.

- Como usuário, eu quero possuir uma página inicial com os grupos que faço parte.

- Como administrador de um grupo, eu quero poder decidir se um grupo é público ou privado.

- Como administrador de um grupo, eu quero poder decidir os privilégios de cada membro.

- Como usuário, eu quero receber notificações de posts dos grupos que eu estou afiliado.

## :book: Backlog da Sprint :book:
- Tarefas técnicas:

       - Preparar ambiente de desenvolvimento frontend (Heitor e Isaac)
        
       - Preparar ambiente de desenvolvimento backend (João e Evaldo)
       
       - Configurar o SGBD (Evaldo) 

- História: Como aluno, eu quero criar, customizar e administrar um grupo de estudo.
- Tarefas:
 
       - Criar rota para criação de grupos. (João)
       
       - Criar tela para criação de grupos. (Isaac)
      
       - Criar rota para atualização de grupos. (João)
       
       - Criar rota para remoção de grupos. (Isaac)
       
       - Criar tela inicial dos grupos. (Heitor)
       
       - Criar tabela de grupos. (Evaldo)
       
       - Criar tabela de ligação usuário-grupo (Evaldo)

- História: Como aluno, eu quero ter um perfil pessoal com informações.
- Tarefas:

       - Criar rota para criar perfil. (João)
       
       - Criar rota para atualizar perfil. (João)
       
       - Criar tela para cadastro. (Heitor)
       
       - Criar tela para login. (Isaac)
       
       - Criar tabela de usuários. (Evaldo)
       
       - Criar tela de perfil de usuário. (Isaac)
       
- História: Como aluno, eu quero poder pesquisar grupos de acordo com meus interesses.
- Tarefas:

       - Criar tela para pesquisar grupos. (Isaac)
        
       - Criar rota para pesquisa de grupos. (João)
       
- História: Como membro de um grupo, eu gostaria de criar postagens na página do grupo de estudos.
- Tarefas:

       - Criar rota para leitura de posts. (João)
         
       - Criar rota para a criação de posts. (João)
       
       - Criar rota para a remoção de posts. (João)
       
       - Criar tabela de posts por grupo. (Evaldo)
       
       - Criar tabela de ligação post-usuário. (Evaldo)
       
- História: Como administrador de um grupo, eu quero criar um cronograma para meu grupo de estudos.
- Tarefas:

       - Criar rota para criação de eventos.   (João)
       
       - Criar rota para a remoção de eventos. (João)
       


- História: Como usuário, eu quero possuir uma página inicial com os grupos que faço parte.
- Tarefas:

       - Criar tela inicial. (Heitor)
       
       - Criar links da tela inicial para os grupos. (Heitor)
