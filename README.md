## Download do Arquivo LaTeX

Clique no link abaixo para baixar o arquivo `.tex`:
[Baixar arquivo.tex](https://raw.githubusercontent.com/Ak4ai/AEDS2_Atividades_Sobre_Arvores/refs/heads/main/conference_101719.tex?token=GHSAT0AAAAAACY2C3BJ34LUYHHUPL63K75CZZZI4DA)

Clique no link abaixo para baixar o arquivo `.pdf`:
[Baixar arquivo.pdf](https://github.com/Ak4ai/AEDS2_Atividades_Sobre_Arvores/blob/main/Pratica_03_AEDS_2.pdf)

# Exercícios de Prática № 1

**Autor**: Michel Pires  
**Instituição**: Centro Federal de Educação Tecnológica de Minas Gerais  
**Data**: 18 de outubro de 2024  

## Descrição

Este repositório contém exercícios práticos relacionados a árvores binárias e suas operações fundamentais, como inserção, remoção, pesquisa e caminhamento. O objetivo é aprofundar os conceitos teóricos e práticos dessas estruturas de dados, com desafios que incluem análises de desempenho e otimização.

---

## Problema 1: Operações em Árvores Binárias de Busca

### Tópicos abordados:
- Inserção, remoção, pesquisa e caminhamento.

### Tarefas:
1. **Construção de Árvores**:  
   Inserir elementos em quatro árvores binárias de busca e desenhar a estrutura após cada inserção.  
   - Conjuntos para inserção:  
     - Árvore 1: `{88, 22, 45, 33, 22, 90, 27, 59, 13}`  
     - Árvore 2: `{65, 47, 21, 11, 72, 23, 05, 34, 28}`  
     - Árvore 3: `{65, 34, 89, 23, 60, 54, 81, 95, 39}`  
     - Árvore 4: `{15, 10, 20, 05, 12, 18, 25, 98, 44}`  

2. **Remoção de Nós**:  
   Realizar remoções específicas, redesenhando a árvore após cada operação e discutindo o impacto estrutural:  
   - Conjuntos para remoção:  
     - Árvore 1: `{33, 90, 33, 45}`  
     - Árvore 2: `{11, 72, 65, 23}`  
     - Árvore 3: `{34, 89, 81, 95}`  
     - Árvore 4: `{20, 05, 18, 44}`  

3. **Pesquisa e Caminhamento**:  
   Selecionar um elemento em cada árvore e aplicar os quatro tipos de caminhamento:  
   - Determinar o número de interações necessárias para localizar o elemento.  
   - Destacar a ordem de visitação dos nós e o caminho percorrido.  
   - Analisar a eficiência de cada estratégia.  

4. **Desafio adicional**:  
   Identificar subconjuntos de elementos em cada árvore cujas remoções resultem no maior número de rotações (rebalanceamentos) em uma árvore AVL.

---

## Problema 2: Cálculo da Altura de Árvores Binárias

### Tópicos abordados:
- Altura da árvore, visualização interativa e análise de crescimento.

### Tarefas:
1. Implementar uma função que calcule a altura máxima de uma árvore binária.  
2. Atualizar e exibir a altura após cada inserção ou remoção de nós.  
3. Comparar o crescimento da altura em árvores mais desbalanceadas versus mais equilibradas.  
4. Identificar e mostrar o caminho mais longo da raiz até a folha mais distante.  

**Desafio adicional**:  
Propor rotações ou reordenações manuais que reduzam a profundidade da árvore, analisando sua eficácia.

---

## Problema 3: Dicionário com Árvore Binária de Busca

### Tópicos abordados:
- Autocompletar, eficiência de busca e otimizações.

### Tarefas:
1. Projetar uma estrutura de árvore binária para buscas rápidas em um dicionário eletrônico.  
2. Implementar recursos de autocompletar e sugestões inteligentes.  
3. Discutir otimizações para manter a eficiência da árvore com grandes volumes de dados.  
4. Elaborar testes de desempenho com inserções e buscas em diferentes tamanhos de dicionários.

---

## Como Executar

1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/exercicios-arvores-binarias.git

## Organização do Repositório

O repositório está organizado da seguinte forma:

- **Exe 4/**: Contém os arquivos e configurações para o exercício 4.
  - **.vscode/**: Configurações específicas do Visual Studio Code.
  - **build/**: Diretório de saída para os arquivos compilados.
  - **src/**: Código-fonte do exercício 4.
  - **Makefile**: Arquivo para automação da compilação.

- **Exe 5/**: Contém os arquivos e configurações para o exercício 5.
  - **.vscode/**: Configurações específicas do Visual Studio Code.
  - **build/**: Diretório de saída para os arquivos compilados.
  - **src/**: Código-fonte do exercício 5.
  - **Makefile**: Arquivo para automação da compilação.
  - **datasetia.py**: Script Python relacionado ao exercício.
  - **dicionario.txt**: Arquivo de texto com um dicionário.
  - **google-10000-english-usa.txt**: Arquivo de texto com palavras em inglês.
  - **palavras_portugues.txt**: Arquivo de texto com palavras em português.
  - **testeopenai.py**: Script Python para testes.

- **conference_101719.tex**: Arquivo LaTeX do projeto.
- **README.md**: Este arquivo de descrição do repositório.
