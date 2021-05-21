#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <windows.h>
#include <string>
#include <random>
#include <ostream>
#include <cwchar>
#include <graphics.h>
#include <map>
#define _WIN32_WINNT 0x0500

using namespace std;

HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE );

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setFontSize(int FontSize)
{
    int newWidth, newHeight;
    newWidth=FontSize,
    newHeight=FontSize;
    CONSOLE_FONT_INFOEX fontStructure={0};
    fontStructure.cbSize=sizeof(fontStructure);
    fontStructure.dwFontSize.X=0;
    fontStructure.dwFontSize.Y=newHeight;
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
    SetCurrentConsoleFontEx(hConsole, true, &fontStructure);
}

char** Alocar_matriz_real(int m, int n)
{
    char** v;  /* ponteiro para a matriz */
    int   i;    /* variavel auxiliar      */
    if (m < 1 || n < 1) { /* verifica parametros recebidos */
        cout << ("** Erro: Parametro invalido **\n") << endl;
        return (NULL);
    }
    /* aloca as linhas da matriz */
    v = (char**)calloc(n, sizeof(char*)); // Um vetor de m ponteiros para char* /
        if (v == NULL) {
            cout << printf("** Erro: Memoria Insuficiente **") << endl;
            return (NULL);
        }
    /* aloca as colunas da matriz */
    for (i = 0; i < m; i++) {
        v[i] = (char*)calloc(m, sizeof(char));  /* m vetores de n floats */
        if (v[i] == NULL) {
            cout << ("** Erro: Memoria Insuficiente **") << endl;
            return (NULL);
        }
    }
    return (v); /* retorna o ponteiro para a matriz */
}

char** Liberar_matriz_real(int m, int n, char** v)
{
    int  i;  /* variavel auxiliar */
    if (v == NULL) return (NULL);
    if (m < 1 || n < 1) {  /* verifica parametros recebidos */
        cout << ("** Erro: Parametro invalido **\n") << endl;
        return (v);
    }
    for (i = 0; i < m; i++)
        free(v[i]); /* libera as linhas da matriz */
    free(v);      /* libera a matriz (vetor de ponteiros) */
    return (NULL); /* retorna um ponteiro nulo */
}

char Competicao(char i, char j, char** v, int p, int q)
{
    char win;
    char vet[2]={i,j};
    if(i==(char)(48)){  // caso o espaco for 0, nada acontece
        v[p][q]=(char)(48);
        return win = j;
    }
    else if(j==(char)(48)){
        return win = vet[rand()%2]; // chance de 50% de se reproduzir ao achar espaco vazio
    }
    else if(i==j){
        return win = j;    // caso forem iguais, nada acontece
    }
    else{
        v[p][q]=(char)(48);
        return win = vet[rand()%2]; // chance de 50% de cada especie ganhar
    }
}

void Movimentos(int l, int c, char** matrix)
{
    int m, n, i, j;
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            m=i+(-1+rand()%3);
            n=j+(-1+rand()%3);
            if(m<0){
                m=i+rand()%2;
            }
            else if(m>l-1){
                m=i+(-1+rand()%2);
            }
            else if(n<0){
                n=i+rand()%2;
            }
            else if(n>c-1){
                n=i+(-1+rand()%2);
            }
            matrix[m][n]=Competicao(matrix[i][j],matrix[m][n], matrix, i, j);
        }
    }
}

int Contador(int l,int c,char** matrix, char k){
    int cont=0;
    for(int i=0;i<l;i++){
        for(int j=0; j<c;j++){
            if(matrix[i][j]==k){
                cont++;
            }
        }
    }
    return cont;
}

void color( int s )
{
   SetConsoleTextAttribute( h, s );        // need to add some checking ... job for another day
}

int main()
{
    int l, c, i, j, fim;
    int qnt;
    int times=0;
    // Declarando a matriz
    char** matrix;
    std::srand(std::time(nullptr));

    setFontSize(16);

    cout << "Digite o numero de linhas" << endl;
    scanf("%d",&l);
    cout << "Digite o numero de colunas" << endl;
    scanf("%d",&c);
    cout << "Digite o numero de geracoes" << endl;
    scanf("%d",&times);
    matrix = Alocar_matriz_real(l, c);
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            matrix[i][j] = (char)(48+rand()%3);
        }
    }
    if(c>=650){
        setFontSize(1);
    }
    else if(c>=330 && c<650){
        setFontSize(2);
    }
    else if(c>=250 && c<330){
        setFontSize(3);
    }
    else if(c>=100 && c<250){
        setFontSize(5);
    }
    else{
        setFontSize(12);
    }

    //Imprimindo a matriz aleatoria
    resizeConsole(1400, 900);
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            //Mudando os caracteres que irao aparecer no console
            if(matrix[i][j]==(char)(48)){
                cout << (char)(255) << " ";
            }
            else if(matrix[i][j]==(char)(49)){
                color(1);
                cout << (char)(254) << " ";
            }
            else{
                color(4);
                cout << (char)(254) << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;

    //Fazendo as especies interagirem entre si
    for(int k=0;k<times;k++){
        Movimentos(l,c,matrix);
    }

    //Imprimindo a matriz depois das geracoes
    for(i=0; i<l; i++){
        for(j=0; j<c; j++){
            if(matrix[i][j]==(char)(48)){
                cout << (char)(255) << " ";
            }
            else if(matrix[i][j]==(char)(49)){
                color(1);
                cout << (char)(254) << " ";
            }
            else{
                color(4);
                cout << (char)(254) << " ";
            }
        }
        cout << endl;
    }
    system("pause");
     setFontSize(16);
     resizeConsole(1400, 900);
    //Contando quantos membros sobraram de cada especie
    qnt = Contador(l, c, matrix, (char)(48));
    cout << "Existem " << qnt << " espacos vazios" << endl;
    qnt = Contador(l, c, matrix, (char)(49));
    cout << "Existem " << qnt << " da especie " << (char)(254) << endl;
    qnt = Contador(l, c, matrix, (char)(50));
    cout << "Existem " << qnt << " da especie " << (char)(153) << endl;
    system("pause");
    matrix = Liberar_matriz_real(l, c, matrix);
    return 0;
}
