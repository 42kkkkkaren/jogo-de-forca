#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "forca.h"

//Variáveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26]; //Letras do alfabeto
int chutesdados = 0;

int letraexiste(char letra){
  for(int j = 0; j < strlen(palavrasecreta); j++){
    if(letra == palavrasecreta[j]){
      return 1;
    }
  }
  return 0;
}

int chuteserrados(){
  int erros;

  for(int i = 0; i < chutesdados; i++){
    if(!letraexiste(chutes[i])){
      erros++;
    }
  }
  return erros;
}

//Função para verificar se o jogador perdeu
int enforcou(){
  return chuteserrados() >= 5;
}

//Função para verificar se o jogador ganhou
int ganhou(){
  for(int i = 0; i < strlen(palavrasecreta); i++){
    if(!jachutou(palavrasecreta[i])){
        return 0;
    }
  }
  return 1;
}

//Função de abertura do jogo
void abertura(){
  printf("/*****************/\n");
  printf("/* Jogo de Forca */\n");
  printf("/*****************/\n\n");
}

//Função para receber o chute do jogador
void chuta(){
  char chute;
  printf("Qual a letra?\n");
  scanf(" %c", &chute);

  if(letraexiste(chute)){
    printf("Você acertou: a palavra tem a letra %c\n\n", chute);
  }else{
    printf("\nVocê errou: a palavra NÃO tem a letra %c\n\n", chute);
  }

  chutes[chutesdados] = chute;
  chutesdados++;
}

//Só uso o ponteiro no parâmetro se eu for modificar a variável
//Função para verificar se a letra já foi chutada
int jachutou(char letra){
  int achou = 0;

  for(int j = 0; j < chutesdados; j++){
    if(chutes[j] == letra){
      achou = 1;
      break;
    }
  }
  return achou;
}

//Função para desenhar a forca
void desenhaforca(){
  int erros = chuteserrados();

  printf("  _______       \n");
  printf(" |/      |      \n");
  printf(" |      %c%c%c  \n", (erros >= 1?'(':' '), (erros >= 1?'_':' '), (erros >= 1?')':' '));
  printf(" |      %c%c%c  \n", (erros >= 3?'\\':' '), (erros >= 2?'|':' '), (erros >= 3?'/': ' '));
  printf(" |       %c     \n", (erros >= 2?'|':' '));
  printf(" |      %c %c   \n", (erros >= 4?'/':' '), (erros >= 4?'\\':' '));
  printf(" |              \n");
  printf("_|___           \n");
  printf("\n\n");

  //Em caso de perda: varrer a lista de chutes e contar o número de chutes. Comparar com o número de chutes máximo.
  for(int i = 0; i < strlen(palavrasecreta); i++){
    if(jachutou(palavrasecreta[i])){
      printf("%c ", palavrasecreta[i]);
    }else{
      printf("_ ");
    }
  }
  printf("\n");
}

//Função para escolher palavra de um arquivo
void escolhepalavra(){
  FILE* f;
  f = fopen("frutas.txt", "r");
  //Tratamento de arquivos
  //Tudo o que é I/O é preciso ser tratado.
  if(f == 0){
    printf("Desculpe, banco de dados não disponível\n\n");
    exit(1);
    //exit(0), funcionou com sucesso. Número maior que zero é a sacada.
  }

  int qtdpalavras;
  fscanf(f, "%d", &qtdpalavras);

  srand(time(0));
  int randomico = rand() % qtdpalavras;

  for(int i = 0; i <= randomico; i ++){
    fscanf(f, "%s", palavrasecreta);
  }

  fclose(f);
}

void adicionapalavra(){
  char quer;

  printf("Você deseja adicionar uma nova palavra no joso? (S/N)\n");
  //O espaço anterior ao %c avisa que quero pegar um char apenas
  scanf(" %c", &quer);

  if(quer == 'S'){
    char novapalavra[TAMANHO_PALAVRA];
    printf("Qual a nova palavra?");
    scanf("%s", novapalavra);

    FILE* f;

    f = fopen("palavras.txt", "r+");
    if(f == 0){
      printf("Desculpe, banco de dados não disponível\n\n");
      exit(1);
    }

    //Primeira posição do arquivo é o número de palavras
    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;
    //Voltar a apontar pro começo do arquivo e escrever o novo número em cima do número anterior
    fseek(f, 0, SEEK_SET); 
    //Posiciona a cabeça de leitura
    fprintf(f, "%d", qtd);

    //Posicionar a cabeça para o fim do arquivo, onde posicionaremos a palavra
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }
}

int main(){
  abertura();
  escolhepalavra();

  do{
    desenhaforca();
    chuta();
  }while(!ganhou() && !enforcou());

  if(ganhou()){
    printf("\nParabéns, você ganhou!\n\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
  }else{
    printf("\nPuxa, você foi enforcado!\n");
    printf("A palavra era **%s**\n\n", palavrasecreta);

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
  }

  adicionapalavra();
}