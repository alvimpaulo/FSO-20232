# Trabalho de implementação de um Pseudo-SO.

## Disciplina: Fundamentos de Sistemas Operacionais
## Semestre: 2023.2
## Professora: Aletéia Patrícia Favacho de Araújo
## Alunos: 
    - Paulo Alvim Alvarenga - 170153657
    - Jonas Soares Rangel - 170146804

O trabalho foi realizado de acordo com as espeificações presentes no arquivo "Trabalho_Implementacao_FSO_2023.pdf". 

A estrutura de pastas desse repositório deve se manter tal qual a fonte, para que o CMake consiga realizar a configuração do projeto corretamente. Foram divididos os arquivos `.cpp` na pasta `src` e os arquivos `.hpp` na pasta `include`, como é o padrão de diversos projetos. Dentro dessas pastas não há mais divisões, devido a ser um projeto relativamente simples e com poucos arquivos a serem divididos.

## Compilação:
Para compilar, espera-se que o usuário tenha em sua máquina o software `CMake`, além de ser capaz de compilar códigos com `gcc` ou `g++`.

Para realizar a compilação, deve-se utilizar o comando `cmake .`, seguindo de `make` na raiz deste diretório.

### Gerencia de processos:
A gerência de processo foi programada majoritariamente pelo aluno Paulo Alvim, e está contida principalmente nos arquivos `src/main.cpp`, e nos arquivos `Processo` e `ProcessoManager` nas suas devidas localizações. 

No arquivo `main`, é feita a leitura do arquivo `processes.txt` que será utilizado para determinar a ordem e atributos dos processos a serem simulados. 
### Módulo de filas:

### Módulo de Memória:

### Módulo de Recurso:

### Módulo de Arquivos: