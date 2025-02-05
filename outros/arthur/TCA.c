#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h>
#define CLS (_WIN32 ? system("cls") : system("clear"));
#define SPAUSE                                              \
    printf("Pressione qualquer tecla para continuar. . ."); \
    getch();
#define GTS        \
    fflush(stdin); \
    gets(str);     \
    fflush(stdin);
#pragma GCC optimize("O3")

typedef struct
{

    int hora;
    int minuto;
} tHoraio;
typedef struct
{

    int ano;
    int mes;
    int dia;
} tData;
typedef struct
{

    char *numero;
    char *logradouro;
    char *bairro;
    char *cidade;
    char *estado;

} tEndereco;
typedef struct
{

    char *categoria;

} tCategoria;

typedef struct
{

    tData nascimento;
    char *nome;
    char *apelido;
    char *email;
    char *telefone;

} tAmigo;
typedef struct
{
    tEndereco endereco;
    char *nomelocal;

} tLocal;
typedef struct
{

    tData data;
    tHoraio horario;
    tAmigo **amigos;
    tCategoria *categoria;
    tLocal *local;
    char **idamigos, *idcat, *idlocal;
    char *descricao, *nome;
    int Namigos;

} tEncontro;

tEncontro *Listaencontro = NULL;
tAmigo *Listaamigo = NULL;
tLocal *Listalocal = NULL;
tCategoria *Listacategoria = NULL;

int Numencontro = 0, Numamigo = 0, Numcategoria = 0, Numlocal = 0;

void title();                                                // digita o titulo
void menuprincipal();                                        // explode o menu principal
void switchprincipal(char op);                               // invoca as funoces manter ou relatorios com um SC.
void limpamemoria();                                         // limpa memoria alocada
void end();                                                  // titulo de saida e fim
void mainamigo();                                            // invoca a main amigo
void menuamigo();                                            // invoca as opcoes de acao para com um amigo
void switchamigo(char op);                                   // switchcase do menu amigo
void incluiamigo();                                          // inclui amigos
tAmigo criaamigo();                                          // cria amigos
void orientaexcluiamigo();                                   // orienta a exlusao de amigos
void editaamigo();                                           // edita dados dos amigos
void excluiamigo(int opAmigo);                               // lista negra
void menueditaamigo(int opAmigo);                            // "o que deseja fazer com este amigo?"
void alteraramigo(char editor, int amigo);                   // factualmente muda os dados do amigo
bool validanome(char *nome);                                 // cheks if theres a friend w that name
bool validaemail(char *email);                               // validates emails and checks for doubles
bool validanumero(char *num);                                // checks for doubles
bool validaapelido(char *apelido);                           // checks for doubles
bool validanascimento(int dias, int mes, int ano);           // valida datas de nascimento

void maincat();                                              // invoca a main categoria
void menucategoria();                                        // invoca o menu categoria
void switchcategoria(char op);                               // invoca as opcoes de acao para com uma categoria
void incluicategoria();                                      // inclui categorias
tCategoria criacategoria();                                  // cria categorias
void editacategoria();                                       // orienta a edicao de categoria
void alteracategoria(int cat);                               // edita categorias
void orientaexcluicat();                                     // orienta a exclusao de categorias
void excluicat(int opCat);                                   // exclui categorias

void mainencontro();                                         // invoca a main encontro
void menuencontro();                                         // invoca o menu encontro
void switchencontro(char op);                                // invoca as opcoes de acao para com um encontro
void incluiencontro();                                       // inclui encontros
tEncontro criaencontro();                                    // cria encontros
void orientaeditaencontro();                                 // orienta a edicao de encontros
void editaencontro(int editor, int encontro);                // edita encontros
void orientaexcluiencontro();                                // orienta a exclusao de encontros
void excluiencontro(int opEncontro);                         // exclui encontros
void menueditaencontro(int opEncontro);                      // "o que deseja fazer com este encontro?"
void rereferenciaamigo();                                    // prefiro nao comentar
void rereferenciacategoria();                                // prefiro nao comentar
void rereferencialocal();                                    // prefiro nao comentar
void rereferencia();                                         // prefiro nao comentar
bool validanomenc(char *str);                                // checks for doubles
int showchavfr(tAmigo *vet[], int t);                        // exibe os amigos disponiveis para a incusao num encontro

void mainlocal();                                            // invoca a main local
void menulocal();                                            // invoca o menu local
void switchlocal(char op);                                   // invoca as opcoes de acao para com um local
void incluilocal();                                          // inclui locais
tLocal crialocal();                                          // cria locais
void orientaeditalocal();                                    // orienta a edicao de locais
void editalocal(char editor, int local);                     // edita locais
void orientaexcluilocal();                                   // orienta a exclusao de locais
void excluilocal(int opLocal);                               // exclui locais
void menueditalocal(int opLocal);                            // "o que deseja fazer com este local?"

void mainrelatorios();                                       // invoca a main relatorios
void menurelatorios();                                       // puxa as opcoes de relatorios
void switchrelatorios(char op);                              // invoca as funcoes de relatorio
void exibeamigo(bool prolongar, bool rel);                   // printa os amigos e suas informacoes
void exibecategoria(bool rel);                               // printa as categorias
void exibelocal(bool prolongar, bool rel);                   // printa os locais e suas informacoes
void exibeencontro(bool rel, bool prolongar, bool detalhar); // printa os encontros
void exibeamigoencontro(tEncontro encontro);                 // printa os amigos de um encontro
void exibeumamigo(int a);                                    // printa um amigo
void exibeumencontro(int e);                                 // printa uma encontro
void exibeumlocal(int l);                                    // printa um local
void relpercat(int c);                                       // relatorio por cateogira

bool validadataenc(int dias, int mes, int ano);              // valida datas para encontros
bool validarhorario(int hora, int min);                      // valida horarios
bool validasimnao();                                         // valida sim e nao
bool isstringint(char *str);                                 // checks if a string is an int
bool adviser();                                              // Pergunta se o usuario quer prossegiuir com a ma ideia
char valida15();                                             // valida 1 a 5
char valida13();                                             // valida 1 a 3
char valida12();                                             // valida 1 a 2
char valida16();                                             // valida operador do menu principal
char valida14();                                             // valida operadoeres 1 a 4
void verifica_alocacao(void *v);                             // verifica se alocacao dinamica deu certo
void ERRO(int opErro);                                       // mensagem de erro
void sucesso(int opSucesso);                                 // mensagem de sucesso
int buscaxnome(int op, char *str);                           // buscapelonome
int opvalido(int delimitador);                               // valida todos os operadores
int buscadadovalido(int indice, int delimitador);            // valida todos os operadores

void enviadados();                                           // envia dados para o arquivo
void enviaamigos();                                          // envia amigos para o arquivo
void enviacategoria();                                       // envia categorias para o arquivo
void envialocal();                                           // envia locais para o arquivo
void enviaencontro();                                        // envia encontros para o arquivo
void recolhedados();                                         // recolhe dados do arquivo
void recolheamigo();                                         // recolhe amigos do arquivo
void recolhecategoria();                                     // recolhe categorias do arquivo
void recolhelocal();                                         // recolhe locais do arquivo
void recolheencontro();                                      // recolhe encontros do arquivo

int main()
{
    char op;
    recolhedados();
    title();
    do
    {
        menuprincipal();
        op = valida16();
        switchprincipal(op);

    } while (op != '6');

    rereferencia();
    enviadados();
    limpamemoria();
    end();
}

void excluiencontro(int op)
{
    free(Listaencontro[op].nome);
    free(Listaencontro[op].descricao);
    free(Listaencontro[op].idcat);
    free(Listaencontro[op].idlocal);
    for (int i = 0; i < Listaencontro[op].Namigos; i++)
    {
        Listaencontro[i].amigos[i] = NULL;
        free(Listaencontro[op].idamigos[i]);
    }
    free(Listaencontro[op].idamigos);
    Listaencontro[op].categoria = NULL;
    Listaencontro[op].local = NULL;

    for (int i = op; i < Numencontro - 1; i++)
    {
        Listaencontro[i] = Listaencontro[i + 1];
    }
    Numencontro--;
    Listaencontro = (tEncontro *)realloc(Listaencontro, Numencontro * sizeof(tEncontro));
    verifica_alocacao(Listaencontro);

    sucesso(4);
    return;
}

void orientaexcluiencontro()
{

    int i;
    exibeencontro(false, false, false);
    printf("\nQual encontro deseja excluir?(nome/indice): ");
    i = buscadadovalido(4, Numencontro);
    excluiencontro(i);
    return;
}

void menueditaencontro(int op)
{
    CLS
        printf("Digite 1 para editar o nome (%s).\n", Listaencontro[op].nome);
    printf("Digite 2 para editar a descricao (\"%s\").\n", Listaencontro[op].descricao);
    printf("Digite 3 para editar o local (%s).\n", Listaencontro[op].local->nomelocal);
    printf("Digite 4 para editar os amigos\n{\n\n");
    exibeamigoencontro(Listaencontro[op]);
    printf("\n}\n");
    printf("Digite 5 para editar a categoria (%s).\n", Listaencontro[op].categoria->categoria);
    printf("Digite 6 para editar a data (%d/%d/%d).\n", Listaencontro[op].data.dia, Listaencontro[op].data.mes, Listaencontro[op].data.ano);
    printf("Digite 7 para editar o horario (%d:%d).\n", Listaencontro[op].horario.hora, Listaencontro[op].horario.minuto);
    printf("Digite 8 para sair.\n");
    printf("\nDigite a opcao desejada: ");
}

bool isstringint(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int buscadadovalido(int indice, int delimitador)
{
    char str[100];
    int i;

    do
    {
        GTS if (!isstringint(str))
        {
            i = buscaxnome(indice, str);
            break;
        }
        else
        {
            i = atoi(str);
            if (i < 1 || i > delimitador)
            {
                ERRO(1);
                continue;
            }
            i--;
            break;
        }
    } while (1);
    return i;
}

int showchavpl(tEncontro encontro)
{
    tLocal *locais = NULL;
    int num = 0;

    for (int i = 0; i < Numlocal; i++)
    {
        if (strcmp(encontro.local->nomelocal, Listalocal[i].nomelocal) != 0)
        {
            if (locais == NULL)
            {
                locais = (tLocal *)malloc(1 * sizeof(tLocal));
                printf("Locais disponiveis:\n");
            }
            else
            {
                locais = (tLocal *)realloc(locais, (i + 1) * sizeof(tLocal));
            }
            verifica_alocacao(locais);
            locais[num] = Listalocal[i];
            printf("%d Local: %s\n", num + 1, locais[num].nomelocal);
            num++;
        }
    }

    int op = 0;
    char str[100];
    printf("\n\nQual o local desejado?(indice/nome): ");
    do
    {

        GTS if (isstringint(str))
        {
            op = atoi(str);
            if (op < 1 || op > num)
            {
                ERRO(1);
                continue;
            }
            op--;
        }
        else
        {
            op = buscaxnome(3, str);
        }
        for (int i = 0; i < Numlocal; i++)
        {
            if (strcmp(locais[op].nomelocal, Listalocal[i].nomelocal) == 0)
            {
                free(locais);
                return i;
            }
        }
    } while (1);
}

int showchavcat(tEncontro encontro)
{
    tCategoria *cats = NULL;
    int num = 0;

    for (int i = 0; i < Numcategoria; i++)
    {
        if (strcmp(encontro.categoria->categoria, Listacategoria[i].categoria) != 0)
        {
            if (cats == NULL)
            {
                cats = (tCategoria *)malloc(1 * sizeof(tCategoria));
                printf("Categorias disponiveis:\n");
            }
            else
            {
                cats = (tCategoria *)realloc(cats, (i + 1) * sizeof(tCategoria));
            }
            verifica_alocacao(cats);
            cats[num] = Listacategoria[i];
            printf("%d Categoria: %s\n", num + 1, cats[num].categoria);
            num++;
        }
    }

    int op = 0;
    char str[100];
    printf("\n\nQual a categoria desejada?(indice/nome): ");
    do
    {

        GTS if (isstringint(str))
        {
            op = atoi(str);
            if (op < 1 || op > num)
            {
                ERRO(1);
                continue;
            }
            op--;
        }
        else
        {
            op = buscaxnome(2, str);
        }
        for (int i = 0; i < Numcategoria; i++)
        {
            if (strcmp(cats[op].categoria, Listacategoria[i].categoria) == 0)
            {
                free(cats);
                return i;
            }
        }
    } while (1);
}

void exibeamigoencontro(tEncontro encontro)
{
    for (int i = 0; i < encontro.Namigos; i++)
    {
        printf("[%d] - %s\n", i + 1, encontro.amigos[i]->nome);
    }
    return;
}

void removeamigoencontro(int i, int encontro)
{
    if (i < Listaencontro[encontro].Namigos)
    {
        for (int j = i; j < Listaencontro[encontro].Namigos - 1; j++)
        {
            Listaencontro[encontro].amigos[j] = Listaencontro[encontro].amigos[j + 1];
            verifica_alocacao(Listaencontro[encontro].amigos[j]);
            Listaencontro[encontro].idamigos[j] = (char *)realloc(Listaencontro[encontro].idamigos[j], (strlen(Listaencontro[encontro].idamigos[j + 1]) + 1) * sizeof(char));
            verifica_alocacao(Listaencontro[encontro].idamigos[j]);
            strcpy(Listaencontro[encontro].idamigos[j], Listaencontro[encontro].idamigos[j + 1]);
        }
    }
    Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos - 1) * sizeof(tAmigo *));
    verifica_alocacao(Listaencontro[encontro].amigos);
    Listaencontro[encontro].idamigos = (char **)realloc(Listaencontro[encontro].idamigos, (Listaencontro[encontro].Namigos - 1) * sizeof(char *));
    verifica_alocacao(Listaencontro[encontro].idamigos);
    Listaencontro[encontro].Namigos--;
    printf("Amigo removido com sucesso do encontro!\n");
    return;
}

void editaamigosencontro(int op, int encontro)
{
    int opl, i;
    char str[100];
    CLS switch (op)
    {
    case 1:
        if (Numamigo == Listaencontro[encontro].Namigos)
        {
            printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
            Sleep(3000);
            incluiamigo();
            Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
            verifica_alocacao(Listaencontro[encontro].amigos);
            Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[Numamigo - 1];
            sucesso(1);
        }
        else
        {
            printf("Digite 1 para adicionar um amigo existente.\nDigite 2 para adicionar um novo amigo.\n");
            printf("Opcao: ");
            opl = opvalido(2);
            if (opl == 1)
            {
                Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(Listaencontro[encontro].amigos);
                Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[showchavfr(Listaencontro[encontro].amigos, Listaencontro[encontro].Namigos)];
            }
            else
            {
                printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
                Sleep(3000);
                incluiamigo();
                Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(Listaencontro[encontro].amigos);
                Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[Numamigo - 1];
                sucesso(1);
            }
        }
        Listaencontro[encontro].idamigos = (char **)realloc(Listaencontro[encontro].idamigos, (Listaencontro[encontro].Namigos + 1) * sizeof(char *));
        verifica_alocacao(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos]);
        Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos] = (char *)malloc((strlen(Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos]->nome) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos]);
        strcpy(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos], Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos]->nome);
        Listaencontro[encontro].Namigos++;
        break;
    case 2:
        exibeamigoencontro(Listaencontro[encontro]);
        printf("\n\nQual amigo deseja excluir?(nome/indice): ");
        do
        {
            GTS if (!isstringint(str))
            {
                i = buscaxnome(1, str);
                break;
            }
            else
            {
                i = atoi(str);
                if (i < 1 || i > Listaencontro[encontro].Namigos)
                {
                    ERRO(1);
                    continue;
                }
                i--;
                break;
            }
        } while (1);
        removeamigoencontro(i, encontro);
        break;
    case 3:
        exibeamigoencontro(Listaencontro[encontro]);
        printf("\n\nQual amigo deseja trocar?(nome/indice): ");
        do
        {
            GTS if (!isstringint(str))
            {
                i = buscaxnome(1, str);
                break;
            }
            else
            {
                i = atoi(str);
                if (i < 1 || i > Listaencontro[encontro].Namigos)
                {
                    ERRO(1);
                    continue;
                }
                i--;
                break;
            }
        } while (1);

        if (Numamigo == Listaencontro[encontro].Namigos)
        {
            printf("Nao ha amigos disponiveis para a troca.\n");
            printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
            Sleep(3000);
            incluiamigo();
            Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
            verifica_alocacao(Listaencontro[encontro].amigos);
            Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[Numamigo - 1];
            CLS
                sucesso(1);
        }
        else
        {
            printf("Digite 1 para adicionar um amigo existente.\nDigite 2 para adicionar um novo amigo.\n");
            printf("Opcao: ");
            opl = opvalido(2);
            if (opl == 1)
            {
                Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(Listaencontro[encontro].amigos);
                Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[showchavfr(Listaencontro[encontro].amigos, Listaencontro[encontro].Namigos)];
            }
            else
            {
                printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
                Sleep(3000);
                incluiamigo();
                Listaencontro[encontro].amigos = (tAmigo **)realloc(Listaencontro[encontro].amigos, (Listaencontro[encontro].Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(Listaencontro[encontro].amigos);
                Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos] = &Listaamigo[Numamigo - 1];
                sucesso(1);
            }
        }
        Listaencontro[encontro].idamigos = (char **)realloc(Listaencontro[encontro].idamigos, (Listaencontro[encontro].Namigos + 1) * sizeof(char *));
        verifica_alocacao(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos]);
        Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos] = (char *)malloc((strlen(Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos]->nome) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos]);
        strcpy(Listaencontro[encontro].idamigos[Listaencontro[encontro].Namigos], Listaencontro[encontro].amigos[Listaencontro[encontro].Namigos]->nome);
        Listaencontro[encontro].Namigos++;
        break;
    }
    return;
}

void editaencontro(int editor, int encontro)
{
    char str[100];
    CLS switch (editor)
    {
    case 1:
        printf("Qual o novo nome de %s?: ", Listaencontro[encontro].nome);
        do
        {
            GTS if (validanomenc(str))
            {
                Listaencontro[encontro].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaencontro[encontro].nome);
                strcpy(Listaencontro[encontro].nome, str);
                break;
            }
            else
            {
                ERRO(23);
            }
        } while (1);
        break;
    case 2:
        printf("A antiga descricao de %s era \"%s\".\n", Listaencontro[encontro].nome, Listaencontro[encontro].descricao);
        printf("Qual a nova descricao de %s?: ", Listaencontro[encontro].nome);
        GTS
            Listaencontro[encontro]
                .descricao = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[encontro].descricao);
        strcpy(Listaencontro[encontro].descricao, str);
        break;

    case 3:
        printf("O antigo local de %s era %s.\n", Listaencontro[encontro].nome, Listaencontro[encontro].local->nomelocal);
        printf("Qual o novo local de %s?: ", Listaencontro[encontro].nome);
        Listaencontro[encontro].local = &Listalocal[showchavpl(Listaencontro[encontro])];
        break;
    case 5:
        printf("A antiga categoria de %s era %s.\n", Listaencontro[encontro].nome, Listaencontro[encontro].categoria->categoria);
        printf("Qual a nova categoria de %s?: \n\n", Listaencontro[encontro].nome);
        Listaencontro[encontro].categoria = &Listacategoria[showchavcat(Listaencontro[encontro])];
        break;
    case 6:
        printf("A antiga data de %s era (%d/%d/%d).\n", Listaencontro[encontro].nome, Listaencontro[encontro].data.dia, Listaencontro[encontro].data.mes, Listaencontro[encontro].data.ano);
        printf("Qual a nova data de %s (dd/mm/aaaa)?: ", Listaencontro[encontro].nome);
        do
        {
            scanf("%d/%d/%d", &Listaencontro[encontro].data.dia, &Listaencontro[encontro].data.mes, &Listaencontro[encontro].data.ano);
            if (!validadataenc(Listaencontro[encontro].data.dia, Listaencontro[encontro].data.mes, Listaencontro[encontro].data.ano))
            {
                ERRO(-1);
                continue;
            }
            else
            {
                break;
            }
        } while (1);
        break;
    case 7:
        printf("O antigo horario de %s era (%d:%d).\n", Listaencontro[encontro].nome, Listaencontro[encontro].horario.hora, Listaencontro[encontro].horario.minuto);
        printf("Qual o novo horario de %s (hh:mm)?: ", Listaencontro[encontro].nome);
        do
        {
            scanf("%d:%d", &Listaencontro[encontro].horario.hora, &Listaencontro[encontro].horario.minuto);
            if (!validarhorario(Listaencontro[encontro].horario.hora, Listaencontro[encontro].horario.minuto))
            {
                ERRO(-2);
                continue;
            }
            else
            {
                break;
            }
        } while (1);
        break;
    case 4:
        printf("---------------------------------\n");
        printf("Digite:\n\n");
        printf("[1] para adicionar um amigo.\n");
        printf("[2] para remover um amigo.\n");
        printf("[3] para trocar um amigo.\n");
        printf("-Opcao desejada: ");
        int op = opvalido(3);
        editaamigosencontro(op, encontro);
        break;
    }
    return;
}

void orientaeditaencontro()
{
    int i;
    int op;
    exibeencontro(false, true, false);
    printf("\nQual encontro deseja editar?(nome/indice): ");
    i = buscadadovalido(4, Numencontro);
    menueditaencontro(i);
    op = opvalido(8);
    if (op == 8)
    {
        return;
    }
    editaencontro(op, i);

    CLS
        sucesso(5);
    return;
}

int opvalido(int delimitador)
{
    char str[5];
    do
    {
        GTS if (!isstringint(str))
        {
            ERRO(1);
        }
        else
        {
            if (atoi(str) < 1 || atoi(str) > delimitador)
            {
                ERRO(1);
            }
            else
            {
                return atoi(str);
            }
        }
    } while (1);
}

void rereferencia()
{
    if (Numamigo != 0)
    {
        rereferenciaamigo();
    }
    if (Numcategoria != 0)
    {
        rereferenciacategoria();
    }
    if (Numlocal != 0)
    {
        rereferencialocal();
    }
    return;
}

void rereferenciaamigo()
{
    if (Listaencontro == NULL || Listaamigo == NULL)
    {
        printf("ERRO: Listaencontro ou Listaamigo NULL.\n");
        return;
    }

    for (int i = 0; i < Numencontro; i++)
    {
        if (Listaencontro[i].amigos == NULL || Listaencontro[i].idamigos == NULL)
        {
            printf("ERRO: Listaencontro[%d].amigos ou Listaencontro[%d].idamigos NULL.\n", i, i);
            continue;
        }

        for (int j = 0; j < Listaencontro[i].Namigos; j++)
        {
            Listaencontro[i].amigos[j] = NULL;

            for (int k = 0; k < Numamigo; k++)
            {
                if (strcmp(Listaencontro[i].idamigos[j], Listaamigo[k].nome) == 0)
                {
                    Listaencontro[i].amigos[j] = &Listaamigo[k];
                    break;
                }
            }

            if (Listaencontro[i].amigos[j] == NULL)
            {
                printf("ERRO: ID %s não encontrado em Listaamigo.\n", Listaencontro[i].idamigos[j]);
                exit(1);
            }
        }
    }
}

void rereferenciacategoria()
{
    for (int i = 0; i < Numencontro; i++)
    {
        for (int j = 0; j < Numcategoria; j++)
        {
            if (strcmp(Listaencontro[i].idcat, Listacategoria[j].categoria) == 0)
            {
                Listaencontro[i].categoria = &Listacategoria[j];
                break;
            }
        }
    }
}

void rereferencialocal()
{
    for (int i = 0; i < Numencontro; i++)
    {
        for (int j = 0; j < Numlocal; j++)
        {
            if (strcmp(Listaencontro[i].idlocal, Listalocal[j].nomelocal) == 0)
            {
                Listaencontro[i].local = &Listalocal[j];
                break;
            }
        }
    }
}

void enviaencontro()
{
    FILE *Ponta;
    Ponta = fopen("encontros.txt", "w");
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    for (int i = 0; i < Numencontro; i++)
    {
        fprintf(Ponta, "%s\n", Listaencontro[i].nome);
        fprintf(Ponta, "%s\n", Listaencontro[i].descricao);
        fprintf(Ponta, "%d;%d;%d;\n", Listaencontro[i].data.dia, Listaencontro[i].data.mes, Listaencontro[i].data.ano);
        fprintf(Ponta, "%d:%d\n", Listaencontro[i].horario.hora, Listaencontro[i].horario.minuto);
        fprintf(Ponta, "%s\n%s\n", Listaencontro[i].idlocal, Listaencontro[i].idcat);
        fprintf(Ponta, "%d;\n", Listaencontro[i].Namigos);
        for (int j = 0; j < Listaencontro[i].Namigos; j++)
        {
            fprintf(Ponta, "%s\n", Listaencontro[i].idamigos[j]);
        }
    }
    fclose(Ponta);
    return;
}

void recolheencontro()
{
    FILE *Ponta;
    Ponta = fopen("encontros.txt", "r");
    int max = 200;
    char str[max];

    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }

    while (fgets(str, max, Ponta) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';
        if (Numencontro == 0)
        {
            Listaencontro = (tEncontro *)malloc(1 * sizeof(tEncontro));
        }
        else
        {
            Listaencontro = (tEncontro *)realloc(Listaencontro, (Numencontro + 1) * sizeof(tEncontro));
        }
        Listaencontro[Numencontro].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[Numencontro].nome);
        strcpy(Listaencontro[Numencontro].nome, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaencontro[Numencontro].descricao = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[Numencontro].descricao);
        strcpy(Listaencontro[Numencontro].descricao, str);

        if (fscanf(Ponta, "%d;%d;%d;\n",
                   &Listaencontro[Numencontro].data.dia,
                   &Listaencontro[Numencontro].data.mes,
                   &Listaencontro[Numencontro].data.ano) != 3)
        {
            ERRO(4);
            limpamemoria();
            exit(1);
        }

        if (fscanf(Ponta, "%d:%d\n",
                   &Listaencontro[Numencontro].horario.hora,
                   &Listaencontro[Numencontro].horario.minuto) != 2)
        {
            ERRO(4);
            limpamemoria();
            exit(1);
        }

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaencontro[Numencontro].idlocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[Numencontro].idlocal);
        strcpy(Listaencontro[Numencontro].idlocal, str);

        for (int i = 0; i < Numlocal; i++)
        {
            if (strcmp(Listaencontro[Numencontro].idlocal, Listalocal[i].nomelocal) == 0)
            {
                Listaencontro[Numencontro].local = &Listalocal[i];
                break;
            }
        }

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaencontro[Numencontro].idcat = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaencontro[Numencontro].idcat);
        strcpy(Listaencontro[Numencontro].idcat, str);

        for (int i = 0; i < Numcategoria; i++)
        {
            if (strcmp(Listaencontro[Numencontro].idcat, Listacategoria[i].categoria) == 0)
            {
                Listaencontro[Numencontro].categoria = &Listacategoria[i];
                break;
            }
        }

        fscanf(Ponta, "%d;\n", &Listaencontro[Numencontro].Namigos);
        Listaencontro[Numencontro].amigos = (tAmigo **)malloc(Listaencontro[Numencontro].Namigos * sizeof(tAmigo *));
        Listaencontro[Numencontro].idamigos = (char **)malloc(Listaencontro[Numencontro].Namigos * sizeof(char *));
        for (int i = 0; i < Listaencontro[Numencontro].Namigos; i++)
        {
            fgets(str, max, Ponta);
            str[strcspn(str, "\n")] = '\0';
            Listaencontro[Numencontro].idamigos[i] = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(Listaencontro[Numencontro].idamigos[i]);
            strcpy(Listaencontro[Numencontro].idamigos[i], str);
        }
        for (int i = 0; i < Listaencontro[Numencontro].Namigos; i++)
        {
            for (int j = 0; j < Numamigo; j++)
            {
                if (strcmp(Listaencontro[Numencontro].idamigos[i], Listaamigo[j].nome) == 0)
                {
                    Listaencontro[Numencontro].amigos[i] = &Listaamigo[j];
                    break;
                }
            }
        }

        Numencontro++;
    }
    fclose(Ponta);
    return;
}
void enviaamigos()
{
    FILE *Ponta;
    Ponta = fopen("amigos.txt", "w");
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    for (int i = 0; i < Numamigo; i++)
    {
        fprintf(Ponta, "%s\n", Listaamigo[i].nome);
        fprintf(Ponta, "%s\n", Listaamigo[i].apelido);
        fprintf(Ponta, "%d;%d;%d;\n", Listaamigo[i].nascimento.dia, Listaamigo[i].nascimento.mes, Listaamigo[i].nascimento.ano);
        fprintf(Ponta, "%s\n", Listaamigo[i].email);
        fprintf(Ponta, "%s\n", Listaamigo[i].telefone);
    }
    fclose(Ponta);
    return;
}

void recolheamigo()
{
    FILE *Ponta;
    Ponta = fopen("amigos.txt", "r");
    int max = 100;
    char str[max];
    SPAUSE
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    while (fgets(str, max, Ponta) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';

        if (Numamigo == 0)
        {
            Listaamigo = (tAmigo *)malloc(1 * sizeof(tAmigo));
        }
        else
        {
            Listaamigo = (tAmigo *)realloc(Listaamigo, (Numamigo + 1) * sizeof(tAmigo));
        }
        verifica_alocacao(Listaamigo);

        Listaamigo[Numamigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaamigo[Numamigo].nome);
        strcpy(Listaamigo[Numamigo].nome, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaamigo[Numamigo].apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaamigo[Numamigo].apelido);
        strcpy(Listaamigo[Numamigo].apelido, str);

        if (fscanf(Ponta, "%d;%d;%d;\n",
                   &Listaamigo[Numamigo].nascimento.dia,
                   &Listaamigo[Numamigo].nascimento.mes,
                   &Listaamigo[Numamigo].nascimento.ano) != 3)
        {
            ERRO(4);
            limpamemoria();
            exit(1);
        }

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaamigo[Numamigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaamigo[Numamigo].email);
        strcpy(Listaamigo[Numamigo].email, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listaamigo[Numamigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listaamigo[Numamigo].telefone);
        strcpy(Listaamigo[Numamigo].telefone, str);

        Numamigo++;
    }
    return;
}

void envialocal()
{
    FILE *Ponta;
    Ponta = fopen("locais.txt", "w");
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }

    for (int i = 0; i < Numlocal; i++)
    {
        fprintf(Ponta, "%s\n", Listalocal[i].nomelocal);
        fprintf(Ponta, "%s\n", Listalocal[i].endereco.logradouro);
        fprintf(Ponta, "%s\n", Listalocal[i].endereco.numero);
        fprintf(Ponta, "%s\n", Listalocal[i].endereco.bairro);
        fprintf(Ponta, "%s\n", Listalocal[i].endereco.cidade);
        fprintf(Ponta, "%s\n", Listalocal[i].endereco.estado);
    }
    fclose(Ponta);
    return;
}

void recolhelocal()
{
    FILE *Ponta;
    Ponta = fopen("locais.txt", "r");
    int max = 100;
    char str[max];
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    while (fgets(str, max, Ponta) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';

        if (Numlocal == 0)
        {
            Listalocal = (tLocal *)malloc(1 * sizeof(tLocal));
        }
        else
        {
            Listalocal = (tLocal *)realloc(Listalocal, (Numlocal + 1) * sizeof(tLocal));
        }
        verifica_alocacao(Listalocal);

        Listalocal[Numlocal].nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].nomelocal);
        strcpy(Listalocal[Numlocal].nomelocal, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listalocal[Numlocal].endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].endereco.logradouro);
        strcpy(Listalocal[Numlocal].endereco.logradouro, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listalocal[Numlocal].endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].endereco.numero);
        strcpy(Listalocal[Numlocal].endereco.numero, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listalocal[Numlocal].endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].endereco.bairro);
        strcpy(Listalocal[Numlocal].endereco.bairro, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listalocal[Numlocal].endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].endereco.cidade);
        strcpy(Listalocal[Numlocal].endereco.cidade, str);

        fgets(str, max, Ponta);
        str[strcspn(str, "\n")] = '\0';
        Listalocal[Numlocal].endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[Numlocal].endereco.estado);
        strcpy(Listalocal[Numlocal].endereco.estado, str);

        Numlocal++;
    }
    fclose(Ponta);
    return;
}

void enviacategoria()
{
    FILE *Ponta;
    Ponta = fopen("categorias.txt", "w");
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    for (int i = 0; i < Numcategoria; i++)
    {
        fprintf(Ponta, "%s\n", Listacategoria[i].categoria);
    }
    fclose(Ponta);
    return;
}

void recolhecategoria()
{
    FILE *Ponta;
    Ponta = fopen("categorias.txt", "r");
    int max = 100;
    char str[max];
    if (Ponta == NULL)
    {
        ERRO(4);
        limpamemoria();
        exit(1);
    }
    while (fgets(str, max, Ponta) != NULL)
    {
        str[strcspn(str, "\n")] = '\0';

        if (Numcategoria == 0)
        {
            Listacategoria = (tCategoria *)malloc(1 * sizeof(tCategoria));
        }
        else
        {
            Listacategoria = (tCategoria *)realloc(Listacategoria, (Numcategoria + 1) * sizeof(tCategoria));
        }
        verifica_alocacao(Listacategoria);

        Listacategoria[Numcategoria].categoria = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listacategoria[Numcategoria].categoria);
        strcpy(Listacategoria[Numcategoria].categoria, str);

        Numcategoria++;
    }
    fclose(Ponta);
    return;
}

void enviadados()
{
    if (Numamigo != 0)
    {
        enviaamigos();
    }
    if (Numcategoria != 0)
    {
        enviacategoria();
    }
    if (Numlocal != 0)
    {
        envialocal();
    }
    enviaencontro();
    return;
}

void recolhedados()
{
    recolheamigo();
    recolhecategoria();
    recolhelocal();
    recolheencontro();
    return;
}

bool validanomenc(char *str)
{
    for (int i = 0; i < Numencontro; i++)
    {
        if (strcmp(str, Listaencontro[i].nome) == 0)
        {
            return false;
        }
    }
    return true;
}

void switchencontro(char op)
{
    switch (op)
    {
    case '1':
        incluiencontro();
        break;
    case '2':
        if (Numencontro == 0)
        {
            ERRO(16);
            Sleep(1500);
            return;
        }
        else
        {
            orientaeditaencontro();
        }
        break;
    case '3':
        if (Numencontro == 0)
        {
            ERRO(17);
            Sleep(2500);
            return;
        }
        else if (Numencontro < 2)
        {
            if (adviser())
            {
                orientaexcluiencontro();
            }
            else
            {
                return;
            }
        }
        else
        {
            orientaexcluiencontro();
        }
        break;
    }
    return;
}

void exibeencontro(bool rel, bool prolongar, bool detalhar)
{
    CLS if (!detalhar)
    {
        if (!prolongar)
        {
            printf("ENCONTROS [%d]:\n\n\n", Numencontro);
            printf("------------------------------------------\n\n");
            for (int i = 0; i < Numencontro; i++)
            {
                printf("\n[%d] Encontro: %s\n", i + 1, Listaencontro[i].nome);
                printf("\"%s\"\n", Listaencontro[i].descricao);
                printf("------------------------------------------\n\n");
            }
        }
        else
        {
            printf("ENCONTROS [%d]:\n\n\n", Numencontro);
            printf("------------------------------------------\n\n");
            for (int i = 0; i < Numencontro; i++)
            {
                printf("Encontro [%d]: %s\n", i + 1, Listaencontro[i].nome);
                printf("\"%s\"\n", Listaencontro[i].descricao);
                printf("Local: %s\n", Listaencontro[i].local->nomelocal);
                printf("Amigos:\n\n");
                for (int j = 0; j < Listaencontro[i].Namigos; j++)
                {
                    printf("[%d] %s, (%s)\n", j + 1, Listaencontro[i].amigos[j]->nome, Listaencontro[i].amigos[j]->apelido);
                }
                printf("\n");
                printf("Categoria: %s\n", Listaencontro[i].categoria->categoria);
                printf("Horario: %d:%d\n", Listaencontro[i].horario.hora, Listaencontro[i].horario.minuto);
                printf("Data: %d/%d/%d\n", Listaencontro[i].data.dia, Listaencontro[i].data.mes, Listaencontro[i].data.ano);
                printf("------------------------------------------\n\n\n\n");
            }
        }
    }
    else
    {
        printf("ENCONTROS [%d]:\n\n\n", Numencontro);
        printf("###############################################\n\n");
        for (int i = 0; i < Numencontro; i++)
        {
            printf("Encontro [%d]: %s\n", i + 1, Listaencontro[i].nome);
            printf("Descrito como: \"%s\"\n", Listaencontro[i].descricao);

            printf("Local:\n");
            printf("Nome: %s.\nEndereco: %s, %s.\nBairro: %s.\nCidade: %s.\nEstado: %s.\n\n", Listaencontro[i].nome, Listaencontro[i].local->endereco.logradouro, Listaencontro[i].local->endereco.numero, Listaencontro[i].local->endereco.bairro, Listaencontro[i].local->endereco.cidade, Listaencontro[i].local->endereco.estado);
            printf("Amigos(%d):\n\n", Listaencontro[i].Namigos);
            printf("===============================\n");
            for (int j = 0; j < Listaencontro[i].Namigos; j++)
            {
                printf("[%d] %s, (%s)\n", j + 1, Listaencontro[i].amigos[j]->nome, Listaencontro[i].amigos[j]->apelido);
                printf("Dados:\nNascimento: (%d/%d/%d).\nTelefone: %s.\nE-mail: %s\n", Listaencontro[i].amigos[j]->nascimento.dia, Listaencontro[i].amigos[j]->nascimento.mes, Listaencontro[i].amigos[j]->nascimento.ano, Listaencontro[i].amigos[j]->telefone, Listaencontro[i].amigos[j]->email);
                printf("===============================\n");
            }
            printf("\n");
            printf("Categoria: %s\n", Listaencontro[i].categoria->categoria);
            printf("Horario: %d:%d\n", Listaencontro[i].horario.hora, Listaencontro[i].horario.minuto);
            printf("Data: %d/%d/%d\n", Listaencontro[i].data.dia, Listaencontro[i].data.mes, Listaencontro[i].data.ano);
            printf("###############################################\n\n");
        }
    }
    if (rel)
    {
        SPAUSE
    }
    return;
}
void mainencontro()
{
    char op;
    do
    {
        menuencontro();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchencontro(op);

    } while (op != '4');
    return;
}

void menuencontro()
{

    CLS
        printf("***MENU ENCONTRO***\n\n");
    printf("---------------------------\n");
    printf("Digite:\n\n");
    printf("1. para criar um encontro\n");
    if (Numencontro > 0)
    {
        printf("2. para editar um encontro\n");
        printf("3. para excluir um encontro\n");
    }
    printf("4. para voltar\n");
    printf("\n--O que deseja fazer?: ");
}

void incluiencontro()
{
    if (Numencontro == 0)
    {
        Listaencontro = (tEncontro *)malloc(1 * sizeof(tEncontro));
    }
    else
    {
        Listaencontro = (tEncontro *)realloc(Listaencontro, (Numencontro + 1) * sizeof(tEncontro));
    }

    verifica_alocacao(Listaencontro);
    Listaencontro[Numencontro] = criaencontro();
    Numencontro++;

    CLS
        sucesso(8);
    return;
}

int showchavfr(tAmigo *vet[], int t)
{
    tAmigo *amigos = NULL;
    bool av;
    int num = 0;
    CLS

        for (int i = 0; i < Numamigo; i++)
    {
        av = true;
        for (int j = 0; j < t; j++)
        {
            if (strcmp(Listaamigo[i].nome, vet[j]->nome) == 0)
            {
                av = false;
                break;
            }
        }
        if (av)
        {
            if (num == 0)
            {
                amigos = (tAmigo *)malloc(sizeof(tAmigo));
                printf("Amigos disponiveis:\n\n\n");
            }
            else
            {
                amigos = (tAmigo *)realloc(amigos, (num + 1) * sizeof(tAmigo));
            }
            verifica_alocacao(amigos);
            amigos[num] = Listaamigo[i];
            printf("[%d] Amigo: %s, (%s)\n", num + 1, amigos[num].nome, amigos[num].apelido);
            num++;
        }
    }

    int op = 0;
    char str[100];
    printf("\n\nQual amigo deseja adicionar?(nome/indice): ");
    do
    {

        GTS if (isstringint(str))
        {
            op = atoi(str);
            if (op < 1 || op > num)
            {
                ERRO(1);
                continue;
            }
            op--;
            break;
        }
        else
        {
            op = buscaxnome(1, str);
            break;
        }

    } while (1);

    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(Listaamigo[i].nome, amigos[op].nome) == 0)
        {
            return i;
        }
    }
    end();
    exit(1);
}

tEncontro criaencontro()
{
    char str[100];
    tEncontro encontro;
    CLS

        printf("**CRIACAO DE ENCONTROS***\n\n");
    printf("Voce tem %d encontros no momento\n\n", Numencontro);
    printf("Qual sera o nome de seu encontro?: ");

    do
    {
        GTS if (validanomenc(str))
        {
            encontro.nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
            strcpy(encontro.nome, str);
            break;
        }
        else
        {
            printf("Ja existe um encontro com esse nome! Digite novamente:");
        }

    } while (1);
    /////////////////////////////////////////////////////////////////
    CLS
        printf("Seu encontro precisa de um local.\n\n");
    if (Numlocal == 0)
    {
        printf("Voce precisa criar um local para seu encontro.\n");
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de um local.\n");
        Sleep(3000);

        incluilocal();
        CLS
            encontro
                .local = &Listalocal[Numlocal - 1];
        sucesso(2);
    }
    else
    {
        printf("Digite 1 para adicionar um local existente.\nDigite 2 para adicionar um novo local.\n");
        printf("Opcao: ");
        char op = valida12();
        if (op == '1')
        {
            exibelocal(true, false);
            (Numlocal == 1) ? (printf("\n\nDigite 1 para escolher o local disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numlocal));
            int opl = opvalido(Numlocal);
            encontro.local = &Listalocal[opl - 1];
        }
        else
        {
            incluilocal();
            encontro.local = &Listalocal[Numlocal - 1];
            CLS
                sucesso(2);
        }
    }
    encontro.idlocal = (char *)malloc((strlen(encontro.local->nomelocal) + 1) * sizeof(char));
    verifica_alocacao(encontro.idlocal);
    strcpy(encontro.idlocal, encontro.local->nomelocal);

    /////////////////////////////////////////////////////////////////////

    CLS

        encontro.amigos = (tAmigo **)malloc(1 * sizeof(tAmigo *));
    printf("Seu encontro precisa de pelo menos um amigo.\n");
    if (Numamigo == 0)
    {
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
        Sleep(3000);
        incluiamigo();
        encontro.amigos[0] = &Listaamigo[Numamigo - 1];
        encontro.Namigos = 1;
        encontro.idamigos = (char **)malloc(1 * sizeof(char *));
        verifica_alocacao(encontro.idamigos);
        encontro.idamigos[0] = (char *)malloc((strlen(encontro.amigos[0]->nome) + 1) * sizeof(char));
        verifica_alocacao(encontro.idamigos[0]);
        strcpy(encontro.idamigos[0], encontro.amigos[0]->nome);
        sucesso(1);
    }
    else
    {
        printf("Digite 1 para adicionar um amigo existente.\nDigite 2 para adicionar um novo amigo.\n");
        printf("Opcao: ");
        int op = opvalido(2);
        if (op == 1)
        {
            exibeamigo(false, false);
            (Numamigo == 1) ? (printf("\n\nDigite 1 para escolher o amigo disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numamigo));
            int opl = opvalido(Numamigo);
            encontro.amigos[0] = &Listaamigo[opl - 1];
            encontro.Namigos = 1;
            encontro.idamigos = (char **)malloc(1 * sizeof(char *));
            verifica_alocacao(encontro.idamigos);
            encontro.idamigos[0] = (char *)malloc((strlen(encontro.amigos[0]->nome) + 1) * sizeof(char));
            verifica_alocacao(encontro.idamigos[0]);
            strcpy(encontro.idamigos[0], encontro.amigos[0]->nome);
        }
        else
        {
            printf("Voce esta sendo direcionado tempoarariamente para a criacao de um amigo.\n");
            Sleep(3000);
            incluiamigo();
            encontro.amigos[0] = &Listaamigo[Numamigo - 1];
            encontro.Namigos = 1;
            encontro.idamigos = (char **)malloc(1 * sizeof(char *));
            verifica_alocacao(encontro.idamigos);
            encontro.idamigos[0] = (char *)malloc((strlen(encontro.amigos[0]->nome) + 1) * sizeof(char));
            verifica_alocacao(encontro.idamigos[0]);
            strcpy(encontro.idamigos[0], encontro.amigos[0]->nome);
            sucesso(1);
        }
    }

    bool op;
    do // adicao de novos amigos
    {
        CLS
            printf("Deseja adicionar mais amigos?(S/N): ");
        op = validasimnao();
        if (op)
        {
            if (encontro.Namigos == Numamigo)
            {
                printf("Voce esta sendo direcionado tempoarariamente para a criacao de um novo amigo.\n");
                Sleep(3000);
                incluiamigo();
                encontro.amigos = (tAmigo **)realloc(encontro.amigos, (encontro.Namigos + 1) * sizeof(tAmigo *));
                verifica_alocacao(encontro.amigos);
                encontro.amigos[encontro.Namigos] = &Listaamigo[Numamigo - 1];
                sucesso(1);
            }
            else
            {
                printf("Digite 1 para adicionar um amigo existente.\nDigite 2 para adicionar um novo amigo.\n");
                printf("Opcao: ");
                int op = opvalido(2);
                if (op == 1)
                {
                    encontro.amigos = (tAmigo **)realloc(encontro.amigos, (encontro.Namigos + 1) * sizeof(tAmigo *));
                    verifica_alocacao(encontro.amigos);
                    encontro.amigos[encontro.Namigos] = &Listaamigo[showchavfr(encontro.amigos, encontro.Namigos)];
                }
                else
                {
                    printf("Voce esta sendo direcionado tempoarariamente para a criacao de um novo amigo.\n");
                    Sleep(3000);
                    incluiamigo();
                    encontro.amigos = (tAmigo **)realloc(encontro.amigos, (encontro.Namigos + 1) * sizeof(tAmigo *));
                    verifica_alocacao(encontro.amigos);
                    encontro.amigos[encontro.Namigos] = &Listaamigo[Numamigo - 1];
                    Sleep(2000);
                }
                encontro.idamigos = (char **)realloc(encontro.idamigos, (encontro.Namigos) * sizeof(char *));
                verifica_alocacao(encontro.idamigos);
                encontro.idamigos[encontro.Namigos] = (char *)malloc((strlen(encontro.amigos[encontro.Namigos - 1]->nome) + 1) * sizeof(char));
                verifica_alocacao(encontro.idamigos[encontro.Namigos - 1]);
                strcpy(encontro.idamigos[encontro.Namigos], encontro.amigos[encontro.Namigos]->nome);
                encontro.Namigos++;
                CLS
                    sucesso(1);
                continue;
            }
        }
        else
        {
            break;
        }

    } while (op);
    /////////////////////////////////////////////////////////////////////
    CLS
        printf("Seu encontro precisa de uma categoria.\n");
    if (Numcategoria == 0)
    {
        printf("Voce esta sendo direcionado tempoarariamente para a criacao de uma categoria.\n");
        Sleep(3000);
        incluicategoria();
        encontro.categoria = &Listacategoria[Numcategoria - 1];
        encontro.idcat = (char *)malloc((strlen(encontro.categoria->categoria) + 1) * sizeof(char));
        verifica_alocacao(encontro.idcat);
        strcpy(encontro.idcat, encontro.categoria->categoria);
        sucesso(3);
    }
    else
    {
        printf("Digite 1 para adicionar uma categoria existente.\nDigite 2 para adicionar uma nova categoria.\n");
        printf("Opcao: ");
        int op = opvalido(2);
        if (op == 1)
        {
            exibecategoria(false);
            (Numcategoria == 1) ? (printf("\n\nDigite 1 para escolher a categoria disponivel: ")) : (printf("\n\nDigite um numero de 1 a %d para escolher: ", Numcategoria));
            int opl = opvalido(Numcategoria);
            encontro.categoria = &Listacategoria[opl - 1];
            encontro.idcat = (char *)malloc((strlen(encontro.categoria->categoria) + 1) * sizeof(char));
            verifica_alocacao(encontro.idcat);
            strcpy(encontro.idcat, encontro.categoria->categoria);
            sucesso(9);
        }
        else
        {
            incluicategoria();
            encontro.categoria = &Listacategoria[Numcategoria - 1];
            encontro.idcat = (char *)malloc((strlen(encontro.categoria->categoria) + 1) * sizeof(char));
            verifica_alocacao(encontro.idcat);
            strcpy(encontro.idcat, encontro.categoria->categoria);
            sucesso(3);
        }
    }
    CLS
        printf("Descreva o que acontecera em seu encontro: ");
    GTS
        encontro.descricao = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(encontro.descricao);
    strcpy(encontro.descricao, str);
    CLS
        printf("Que dia sera seu encontro?(dd/mm/aaaa): ");
    do
    {
        scanf("%d/%d/%d", &encontro.data.dia, &encontro.data.mes, &encontro.data.ano);
        if (!validadataenc(encontro.data.dia, encontro.data.mes, encontro.data.ano))
        {
            ERRO(-2);
        }
        else
        {
            break;
        }
    } while (1);
    CLS
        printf("Que horas sera seu encontro?(hh:mm): ");
    do
    {
        scanf("%d:%d", &encontro.horario.hora, &encontro.horario.minuto);
        if (!validarhorario(encontro.horario.hora, encontro.horario.minuto))
        {
            ERRO(-2);
        }
        else
        {
            break;
        }
    } while (1);
    return encontro;
}

bool adviser()
{
    CLS
        ERRO(0);
    return validasimnao();
}

void excluilocal(int opLocal)
{
    free(Listalocal[opLocal].endereco.bairro);
    free(Listalocal[opLocal].endereco.cidade);
    free(Listalocal[opLocal].endereco.estado);
    free(Listalocal[opLocal].endereco.logradouro);
    free(Listalocal[opLocal].endereco.numero);
    free(Listalocal[opLocal].nomelocal);

    for (int i = opLocal; i < Numlocal - 1; i++)
    {
        Listalocal[i] = Listalocal[i + 1];
    }

    Numlocal--;
    Listalocal = (tLocal *)realloc(Listalocal, Numlocal * sizeof(tLocal));
    if (Numlocal != 0)
    {
        verifica_alocacao(Listalocal);
    }
    if (Numencontro != 0)
    {
        rereferencialocal();
    }
    sucesso(10);
    return;
}

void orientaexcluilocal()
{
    int i;
    exibelocal(false, false);
    printf("\nQual local deseja excluir?(nome/indice): ");
    i = buscadadovalido(2, Numlocal);
    for (int j = 0; j < Numencontro; j++)
    {
        if (strcmp(Listaencontro[j].categoria->categoria, Listacategoria[i].categoria) == 0)
        {
            CLS
                printf("Este local localiza o encontro %s, deseja excluir o encontro?(s/n): ", Listaencontro[j].nome);
            if (validasimnao())
            {
                excluiencontro(j);
            }
            else
            {
                return;
            }
        }
    }
    excluilocal(i);
    return;
}

void editalocal(char editor, int local)
{

    char str[100];
    CLS

        switch (editor)
    {
    case '1':
        printf("Qual o novo nome do local %s?: ", Listalocal[local].nomelocal);
        GTS for (int i = 0; i < Numlocal; i++)
        {
            if (strcmp(Listaencontro[i].idlocal, Listalocal[i].nomelocal) == 0)
            {
                Listaencontro[i].idlocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaencontro[i].idlocal);
                strcpy(Listaencontro[i].idlocal, str);
                break;
            }
        }
        Listalocal[local].nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].nomelocal);
        strcpy(Listalocal[local].nomelocal, str);
        break;

    case '2':
        printf("Qual o novo estado para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.estado);
        strcpy(Listalocal[local].endereco.estado, str);
        printf("Qual a nova cidade para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.cidade);
        strcpy(Listalocal[local].endereco.cidade, str);
        printf("Qual o novo bairro para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.bairro);
        strcpy(Listalocal[local].endereco.bairro, str);
        printf("Qual o novo logradouro para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.logradouro);
        strcpy(Listalocal[local].endereco.logradouro, str);
        printf("Qual o novo numero para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.numero);
        strcpy(Listalocal[local].endereco.numero, str);
        break;

    case '3':
        printf("Qual o novo numero para seu encontro?: ");
        GTS
            Listalocal[local]
                .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
        verifica_alocacao(Listalocal[local].endereco.numero);
        strcpy(Listalocal[local].endereco.numero, str);
        break;
    }
    CLS
        Sleep(1500);
    return;
}

void menueditalocal(int opLocal)
{

    CLS
        printf("Digite 1 para alterar o nome (%s)\n", Listalocal[opLocal].nomelocal);
    printf("Digite 2 para alterar a endereco %s, %s, %s, %s, %s\n", Listalocal[opLocal].endereco.estado, Listalocal[opLocal].endereco.cidade, Listalocal[opLocal].endereco.bairro, Listalocal[opLocal].endereco.logradouro, Listalocal[opLocal].endereco.numero);
    printf("Digite 3 para alterar o numero (%s)\n", Listalocal[opLocal].endereco.numero);
    printf("Digite 4 para sair\n");
    printf("\nDigite a opcao desejada: ");
}

char valida12()
{
    char opIn;
    do
    {
        opIn = getch();
        if (opIn != '1' && opIn != '2')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2');

    return opIn;
}
char valida13()
{
    char opIn;
    do
    {
        opIn = getch();
        if (opIn != '1' && opIn != '2' && opIn != '3')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2' && opIn != '3');

    return opIn;
}

char valida14()
{
    char opIn;
    do
    {
        opIn = getch();
        if (opIn != '1' && opIn != '2' && opIn != '3' && opIn != '4')
        {
            ERRO(1);
        }
    } while (opIn != '1' && opIn != '2' && opIn != '3' && opIn != '4');

    return opIn;
}

char valida15()
{
    char op;
    do
    {
        op = getch();
        if (op != '1' && op != '2' && op != '3' && op != '4' && op != '5')
        {
            ERRO(1);
        }
    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5');

    return op;
}
void exibelocal(bool prolongar, bool rel)
{
    CLS

        if (!prolongar)
    {
        printf("LOCAIS:\n\n");
        for (int i = 0; i < Numlocal; i++)
        {
            printf("%d Local: %s\n", i + 1, Listalocal[i].nomelocal);
        }
    }

    else if (prolongar)
    {
        printf("LOCAIS [%d]:\n\n\n", Numlocal);
        printf("------------------------------------------\n\n");
        for (int i = 0; i < Numlocal; i++)
        {
            printf("Nome: %s.\nEndereco: %s, %s.\nBairro: %s.\nCidade: %s.\nEstado: %s.\n\n", Listaencontro[i].local->nomelocal, Listaencontro[i].local->endereco.logradouro, Listaencontro[i].local->endereco.numero, Listaencontro[i].local->endereco.bairro, Listaencontro[i].local->endereco.cidade, Listaencontro[i].local->endereco.estado);
        }
    }

    if (rel)
    {
        printf("\n\n");
        SPAUSE
    }
    return;
}

void orientaeditalocal()
{
    int i;
    int op;
    exibelocal(true, false);
    printf("\nQual local deseja editar?(nome/indice): ");
    i = buscadadovalido(2, Numlocal);
    menueditalocal(i);
    op = opvalido(4);
    if (op == 4)
    {
        return;
    }
    editalocal(op, i);

    CLS
        sucesso(11);
    return;
}

void incluilocal()
{
    CLS
        printf("Voce tem %d locais no momento\n\n", Numlocal);

    if (Numlocal == 0)
    {
        Listalocal = (tLocal *)malloc(1 * sizeof(tLocal));
    }
    else
    {
        Listalocal = (tLocal *)realloc(Listalocal, (Numlocal + 1) * sizeof(tLocal));
        if (Numencontro != 0)
        {
            rereferencialocal();
        }
    }
    verifica_alocacao(Listalocal);

    Listalocal[Numlocal] = crialocal();
    Numlocal++;
    CLS
        sucesso(12);
    return;
}

bool validanomelocal(char *nome)
{
    for (int i = 0; i < Numlocal; i++)
    {
        if (strcmp(Listalocal[i].nomelocal, nome) == 0)
        {
            return false;
        }
    }
    return true;
}

tLocal crialocal()
{
    char str[100];
    tLocal local;
    CLS

        printf("Em qual estado sera seu encontro?: ");
    GTS
        local
            .endereco.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.estado);
    strcpy(local.endereco.estado, str);

    printf("Em qual cidade sera seu encontro?: ");
    GTS
        local
            .endereco.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.cidade);
    strcpy(local.endereco.cidade, str);

    printf("Em qual bairro sera seu encontro?: ");
    GTS
        local
            .endereco.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.bairro);
    strcpy(local.endereco.bairro, str);

    printf("Qual o logradouro ser seu encontro?: ");
    GTS
        local
            .endereco.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.logradouro);
    strcpy(local.endereco.logradouro, str);

    printf("Qual o numero para seu encontro?: ");
    GTS
        local
            .endereco.numero = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(local.endereco.numero);
    strcpy(local.endereco.numero, str);

    printf("Qual o nome do seu local?: ");
    do
    {
        GTS if (!validanomelocal(str))
        {
            printf("Ja existe um local com este nome! Digite novamente:");
        }
        else
        {
            local.nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(local.nomelocal);
            strcpy(local.nomelocal, str);
            break;
        }

    } while (1);

    CLS return local;
}

void switchlocal(char op)
{

    switch (op)
    {
    case '1':
        incluilocal();
        break;
    case '2':
        if (Numlocal < 1)
        {
            ERRO(21);
        }
        else
        {
            orientaeditalocal();
        }
        break;
    case '3':
        if (Numlocal < 1)
        {
            ERRO(22);
        }
        else if (Numlocal < 2)
        {
            if (adviser())
            {
                orientaexcluilocal();
            }
        }
        else
        {
            orientaexcluilocal();
        }
        break;
    }
    return;
}

void mainlocal()
{
    char op;
    do
    {
        menulocal();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchlocal(op);

    } while (op != '4');
    return;
}

void menulocal()
{

    CLS
        printf("***MENU LOCAL***\n\n");
    printf("-------------------------\n");
    printf("Digite:\n\n");
    printf("[1] para criar um local\n");
    if (Numlocal > 0)
    {
        printf("[2] para editar um local\n");
        printf("[3] para excluir um local\n");
    }
    printf("[4] para voltar\n");
    printf("\n--O que deseja fazer?: ");
    return;
}

void excluicat(int opCat)
{

    if (opCat < Numcategoria)
    {
        for (int i = opCat; i < Numcategoria - 1; i++)
        {
            Listacategoria[i] = Listacategoria[i + 1];
        }
    }

    Numcategoria--;
    Listacategoria = (tCategoria *)realloc(Listacategoria, Numcategoria * sizeof(tCategoria));
    if (Numcategoria != 0)
    {
        verifica_alocacao(Listacategoria);
    }
    if (Numencontro != 0)
    {
        rereferenciacategoria();
    }
    sucesso(13);
    return;
}

void orientaexcluicat()
{
    int i;
    exibecategoria(false);
    printf("\nQual categoria deseja excluir?(nome/indice): ");
    i = buscadadovalido(3, Numcategoria);
    for (int j = 0; j < Numencontro; j++)
    {
        if (strcmp(Listaencontro[j].categoria->categoria, Listacategoria[i].categoria) == 0)
        {
            CLS
                printf("Esta categoria categoriza o encontro %s, deseja excluir oencontro?(s/n): ", Listaencontro[j].nome);
            if (validasimnao())
            {
                excluiencontro(j);
            }
            else
            {
                return;
            }
        }
    }
    excluicat(i);
    return;
}

void alteracategoria(int cat)
{
    char str[100];

    printf("Qual novo nome deseja para sua categoria?: ");
    GTS for (int i = 0; i < Numencontro; i++)
    {
        if (strcmp(Listaencontro[i].idcat, Listacategoria[cat].categoria) == 0)
        {
            Listaencontro[i].idcat = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(Listaencontro[i].idcat);
            strcpy(Listaencontro[i].idcat, str);
            break;
        }
    }
    Listacategoria[cat].categoria = (char *)malloc((strlen(str) + 1) * sizeof(char));
    verifica_alocacao(Listacategoria[cat].categoria);
    strcpy(Listacategoria[cat].categoria, str);
    sucesso(14);
    return;
}

void exibecategoria(bool rel)
{

    CLS

        printf("**CATEGORIAS:\n\n");
    printf("---------------------\n\n");
    for (int i = 0; i < Numcategoria; i++)
    {
        printf("-Categoria [%d]: %s\n", i + 1, Listacategoria[i].categoria);
    }
    printf("\n---------------------\n\n");

    if (rel)
    {
        SPAUSE
    }
    return;
}
void editacategoria()
{
    int i;
    exibecategoria(false);
    printf("\nQual categoria deseja editar?(nome/indice): ");
    i = buscadadovalido(3, Numcategoria);
    alteracategoria(i);
    return;
}

bool validasimnao()
{
    char op;

    do
    {
        fflush(stdin);
        op = getch();
        if (op != 's' && op != 'n' && op != 'S' && op != 'N')
        {
            ERRO(1);
        }
    } while (op != 's' && op != 'n' && op != 'S' && op != 'N');

    if (op == 's' || op == 'S')
    {
        return true;
    }
    return false;
}

void incluicategoria()
{
    CLS
        printf("Voce tem %d categorias no momento\n", Numcategoria);

    if (Numcategoria == 0)
    {
        Listacategoria = (tCategoria *)malloc(1 * sizeof(tCategoria));
    }
    else
    {
        Listacategoria = (tCategoria *)realloc(Listacategoria, (Numcategoria + 1) * sizeof(tCategoria));
        if (Numencontro != 0)
        {
            rereferenciacategoria();
        }
    }
    verifica_alocacao(Listacategoria);
    Listacategoria[Numcategoria] = criacategoria();
    Numcategoria++;

    CLS
        sucesso(9);
    return;
}

bool validacat(char *str)
{
    for (int i = 0; i < Numcategoria; i++)
    {
        if (strcmp(Listacategoria[i].categoria, str) == 0)
        {
            return false;
        }
    }
    return true;
}

tCategoria criacategoria()
{
    char str[100];
    tCategoria categoria;

    printf("\nQual nome deseja para sua categoria?: ");
    do
    {
        GTS if (!validacat(str))
        {
            printf("Ja existe uma categoria com este nome! Digite novamente:");
            continue;
        }
        else
        {
            categoria.categoria = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(categoria.categoria);
            strcpy(categoria.categoria, str);
            break;
        }

    } while (1);
    return categoria;
}

void maincat()
{
    char op;
    do
    {
        menucategoria();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchcategoria(op);
    } while (op != '4');
    return;
}

void menucategoria()
{

    CLS
        printf("***MENU CATEGORIA***\n\n");
    printf("------------------------------\n");
    printf("Digite:\n\n");
    printf("[1] para criar uma categoria\n");
    if (Numcategoria > 0)
    {
        printf("[2] para editar uma categoria\n");
        printf("[3] para excluir uma categoria\n");
    }
    printf("[4] para voltar\n");
    printf("\n--O que deseja fazer?: ");
    return;
}

void switchcategoria(char op)
{
    switch (op)
    {
    case '1':
        incluicategoria();
        break;
    case '2':
        if (Numcategoria == 0)
        {
            ERRO(11);
            Sleep(2500);
            return;
        }
        else
        {
            editacategoria();
            break;
        }

    case '3':
        if (Numcategoria == 0)
        {
            ERRO(12);
            Sleep(2500);
            return;
        }
        else if (Numcategoria < 2)
        {
            if (adviser())
            {
                orientaexcluicat();
            }
            else
            {
                return;
            }
        }
        else
        {
            orientaexcluicat();
            break;
        }
    }
    return;
}

void title()
{

    char word[] = "Hello, World!";
    char word2[] = "Eu amo minha namorada!";

    CLS for (int i = 0; word[i] != '\0'; i++)
    {
        printf("%c", word[i]);
        Sleep(100);
    }
    Sleep(900);
    CLS for (int i = 0; word2[i] != '\0'; i++)
    {
        printf("%c", word2[i]);
        Sleep(100);
    }
    Sleep(900);
}

void exibeumamigo(int a)
{
    CLS
        printf("AMIGO[%d]:\n\n", a + 1);
    printf("------------------------------------------\n\n");
    printf("Nome: %s\n", Listaamigo[a].nome);
    printf("Apelido: %s\n", Listaamigo[a].apelido);
    printf("Telefone: %s\n", Listaamigo[a].telefone);
    printf("Email: %s\n", Listaamigo[a].email);
    printf("Data de Nascimento: %d/%d/%d\n", Listaamigo[a].nascimento.dia, Listaamigo[a].nascimento.mes, Listaamigo[a].nascimento.ano);
    printf("------------------------------------------\n\n");
    SPAUSE
}

void exibeumencontro(int e)
{
    CLS
        printf("ENCONTRO[%d]:\n\n\n", e + 1);
    printf("#########################################################\n\n");
    printf("Encontro [%d]: %s\n", e + 1, Listaencontro[e].nome);
    printf("Descrito como: \"%s\"\n", Listaencontro[e].descricao);
    printf("Local:\n");
    printf("Nome: %s.\nEndereco: %s, %s.\nBairro: %s.\nCidade: %s.\nEstado: %s.\n\n", Listaencontro[e].local->nomelocal, Listaencontro[e].local->endereco.logradouro, Listaencontro[e].local->endereco.numero, Listaencontro[e].local->endereco.bairro, Listaencontro[e].local->endereco.cidade, Listaencontro[e].local->endereco.estado);
    printf("Amigos(%d):\n\n", Listaencontro[e].Namigos);
    printf("===============================\n");
    for (int j = 0; j < Listaencontro[e].Namigos; j++)
    {
        printf("[%d] %s, (%s)\n", j + 1, Listaencontro[e].amigos[j]->nome, Listaencontro[e].amigos[j]->apelido);
        printf("Dados:\nNascimento: (%d/%d/%d).\nTelefone: %s.\nE-mail: %s\n", Listaencontro[e].amigos[j]->nascimento.dia, Listaencontro[e].amigos[j]->nascimento.mes, Listaencontro[e].amigos[j]->nascimento.ano, Listaencontro[e].amigos[j]->telefone, Listaencontro[e].amigos[j]->email);
        printf("===============================\n");
    }
    printf("\n");
    printf("Categoria: %s\n", Listaencontro[e].categoria->categoria);
    printf("Horario: %d:%d\n", Listaencontro[e].horario.hora, Listaencontro[e].horario.minuto);
    printf("Data: (%d/%d/%d)\n", Listaencontro[e].data.dia, Listaencontro[e].data.mes, Listaencontro[e].data.ano);
    printf("#########################################################\n\n\n");
    return;
}

void exibeumlocal(int l)
{
    CLS
        printf("LOCAL[%d]:\n\n", l + 1);
    printf("------------------------------------------\n\n");
    printf("Nome: %s\n", Listalocal[l].nomelocal);
    printf("Endereco: %s, %s\n", Listalocal[l].endereco.logradouro, Listalocal[l].endereco.numero);
    printf("Bairro: %s\n", Listalocal[l].endereco.bairro);
    printf("Cidade: %s\n", Listalocal[l].endereco.cidade);
    printf("Estado: %s\n", Listalocal[l].endereco.estado);
    printf("------------------------------------------\n\n");
    SPAUSE
    return;
}

void relpercat(int c)
{
    CLS

        for (int i = 0; i < Numencontro; i++)
    {
        if (strcmp(Listaencontro[i].categoria->categoria, Listacategoria[c].categoria) == 0)
        {
            exibeumencontro(i);
        }
    }
    SPAUSE
    return;
}

void switchrelatorios(char op)
{
    CLS

        switch (op)
    {
    case '1':
        if (Numamigo < 1)
        {
            CLS
                ERRO(7);
            Sleep(1500);
        }
        else
        {
            printf("Digite 1 para exibir UM amigo.\n");
            printf("Digite 2 para exibir TODOS os amigos.\n");
            printf("\nO que deseja fazer?: ");
            int op = opvalido(2);
            if (op == 1)
            {
                exibeamigo(false, false);
                printf("\n\nQual amigo deseja exibir?(nome/indice): ");
                exibeumamigo(buscadadovalido(1, Numamigo));
            }
            else
            {
                exibeamigo(true, true);
            }
        }
        break;

    case '3':
        if (Numcategoria < 1)
        {
            CLS
                ERRO(10);
            Sleep(1500);
        }
        else
        {
            exibecategoria(true);
        }
        break;
    case '2':
        if (Numlocal < 1)
        {
            CLS
                ERRO(18);
            Sleep(1500);
        }
        else
        {
            printf("Digite 1 para exibir UM local.\n");
            printf("Digite 2 para exibir TODOS os locais.\n");
            printf("\nO que deseja fazer?: ");
            int op = opvalido(2);
            if (op == 1)
            {
                exibelocal(false, false);
                printf("\n\nQual local deseja exibir?(nome/indice): ");
                exibeumlocal(buscadadovalido(3, Numlocal));
            }
            else
            {
                exibeamigo(true, true);
            }
        }
        break;

    case '4':
        if (Numencontro < 1)
        {
            CLS
                ERRO(15);
            Sleep(1500);
        }
        else
        {
            printf("Digite 1 para exibir UM encontro.\n");
            printf("Digite 2 para exibir TODOS os encontros.\n");
            printf("\nO que deseja fazer?: ");
            int op = opvalido(2);
            if (op == 1)
            {
                exibeencontro(false, false, false);
                printf("\n\nQual local deseja exibir?(nome/indice): ");
                exibeumencontro(buscadadovalido(4, Numlocal));
                SPAUSE
            }
            else
            {
                exibeencontro(true, true, true);
            }
        }
        break;
    case '5':
        if (Numencontro < 1)
        {
            CLS
                ERRO(15);
            Sleep(1500);
        }
        else
        {
            exibecategoria(false);
            printf("\n\nPor qual das categorias deseja fazer o relatorio?(nome/indice): ");
            char str[100];
            do
            {
                GTS if (!isstringint(str))
                {
                    relpercat(buscaxnome(3, str));
                    break;
                }
                else
                {
                    relpercat(atoi(str) - 1);
                    break;
                }
            } while (1);
        }
        break;
    }

    return;
}

void mainrelatorios()
{
    char op;
    do
    {
        menurelatorios();
        op = valida16();
        if (op == '6')
        {
            break;
        }
        switchrelatorios(op);
    } while (op != '6');
    return;
}

void menurelatorios()
{
    CLS
        printf("***MENU DE RELATORIOS***\n\n");
    printf("----------------------------------------\n");
    printf("Digite:\n\n");
    printf("[1] para exibir o relatorio de amigos\n");
    printf("[2] para exibir o relatorio de locais\n");
    printf("[3] para exibir o relatorio de categorias\n");
    printf("[4] para exibir o relatorio de encontros\n");
    printf("[5] para relatorios por categoria\n");
    printf("[6] para voltar\n");
    printf("\n--O que deseja fazer?: ");
    return;
}

void exibeamigo(bool prolongar, bool rel)
{

    CLS if (!prolongar)
    {
        printf("AMIGOS:\n\n");
        for (int i = 0; i < Numamigo; i++)
        {
            printf("[%d]Amigo: %s, (%s).\n", i + 1, Listaamigo[i].nome, Listaamigo[i].apelido);
        }
    }

    else if (prolongar)
    {
        printf("AMIGOS [%d]:\n\n\n", Numamigo);
        printf("------------------------------------------\n\n");
        for (int i = 0; i < Numamigo; i++)
        {
            printf("Amigo [%d]: \n\n", i + 1);
            printf("Nome: %s\n", Listaamigo[i].nome);
            printf("Apelido: %s\n", Listaamigo[i].apelido);
            printf("Email: %s\n", Listaamigo[i].email);
            printf("Telefone: %s\n", Listaamigo[i].telefone);
            printf("Nascimento: (%d/%d/%d)\n", Listaamigo[i].nascimento.dia, Listaamigo[i].nascimento.mes, Listaamigo[i].nascimento.ano);
            printf("\n------------------------------------------\n\n");
        }
    }

    if (rel)
    {
        printf("\n\n");
        SPAUSE
    }
    return;
}

void editaamigo()
{
    int i;
    int op;
    exibeamigo(false, false);
    printf("\nQual amigo deseja editar?(nome/indice): ");
    i = buscadadovalido(1, Numamigo);
    menueditaamigo(i);
    op = opvalido(6);
    if (op == 6)
    {
        return;
    }
    alteraramigo(op, i);

    CLS
        sucesso(7);
    return;
}

void alteraramigo(char editor, int amigo)
{

    char str[100];

    switch (editor)
    {
    case '1':
        printf("Qual o novo nome de %s?: ", Listaamigo[amigo].nome);
        do
        {
            GTS if (validanome(str))
            {
                bool stop = false;
                for (int i = 0; i < Numencontro; i++)
                {
                    for (int j = 0; j < Numamigo; j++)
                    {
                        if (strcmp(Listaamigo[amigo].nome, Listaencontro[i].idamigos[j]) == 0)
                        {
                            Listaencontro[i].idamigos[j] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                            verifica_alocacao(Listaencontro[i].idamigos[j]);
                            strcpy(Listaencontro[i].idamigos[j], str);
                            stop = true;
                            break;
                        }
                    }
                    if (stop)
                    {
                        break;
                    }
                }
                Listaamigo[amigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[amigo].nome);
                strcpy(Listaamigo[amigo].nome, str);
                break;
            }
            else
            {
                printf("\nJa existe um amigo com este nome.\nAdicione um sobrenome para diferencia-lo: ");
            }
        } while (1);
        break;

    case '2':
        printf("Qual o novo apelido de %s?: ", Listaamigo[amigo].nome);
        GTS
            Listaamigo[amigo]
                .apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
        strcpy(Listaamigo[amigo].apelido, str);
        break;

    case '3':
        do
        {
            GTS if (!validanumero(str))
            {
                printf("Ja existe um amigo com este telefone.\nDigite novamente: ");
            }
            else
            {

                Listaamigo[amigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[amigo].telefone);
                strcpy(Listaamigo[amigo].telefone, str);
                break;
            }

        } while (1);
        break;

    case '4':
        printf("Qual o novo email de %s?: ", Listaamigo[amigo].nome);
        do
        {
            GTS if (validaemail(str))
            {
                Listaamigo[amigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
                verifica_alocacao(Listaamigo[amigo].email);
                strcpy(Listaamigo[amigo].email, str);
                break;
            }

        } while (1);
        break;

    case '5':
        printf("Qual eh a nova data de nascimento de %s? (dd/mm/aaaa): ", Listaamigo[amigo].nome);
        do
        {
            scanf("%d/%d/%d", &Listaamigo[amigo].nascimento.dia, &Listaamigo[amigo].nascimento.mes, &Listaamigo[amigo].nascimento.ano);
            if (!(validanascimento(Listaamigo[amigo].nascimento.dia, Listaamigo[amigo].nascimento.mes, Listaamigo[amigo].nascimento.ano)))
            {
                ERRO(-1);
            }
            else
            {
                break;
            }
        } while (1);
        break;
    }

    sucesso(7);
    return;
}

void menueditaamigo(int opAmigo)
{
    CLS
        printf("Digite 1 para alterar o nome (%s)\n", Listaamigo[opAmigo].nome);
    printf("Digite 2 para alterar o apelido (%s)\n", Listaamigo[opAmigo].apelido);
    printf("Digite 3 para alterar o numero de telefone (%s)\n", Listaamigo[opAmigo].telefone);
    printf("Digite 4 para alterar o email (%s)\n", Listaamigo[opAmigo].email);
    printf("Digite 5 para alterar a data de nasicemnto (%d/%d/%d)\n", Listaamigo[opAmigo].nascimento.dia, Listaamigo[opAmigo].nascimento.mes, Listaamigo[opAmigo].nascimento.ano);
    printf("Digite 6 para voltar\n\nDigite a opcao desejada: ");
}

void excluiamigo(int opAmigo)
{
    free(Listaamigo[opAmigo].nome);
    free(Listaamigo[opAmigo].apelido);
    free(Listaamigo[opAmigo].email);
    free(Listaamigo[opAmigo].telefone);

    if (opAmigo < Numamigo)
    {
        for (int i = opAmigo; i < Numamigo - 1; i++)
        {
            Listaamigo[i] = Listaamigo[i + 1];
        }
    }

    Numamigo--;
    Listaamigo = (tAmigo *)realloc(Listaamigo, Numamigo * sizeof(tAmigo)); // realloca a Lista para o novo tamanho de Numamigo
    if (Numamigo != 0)
    {
        verifica_alocacao(Listaamigo);
    }
    if (Numencontro != 0)
    {
        rereferenciaamigo();
    }
    return;
}

void orientaexcluiamigo()
{
    int i;
    exibeamigo(false, false);
    printf("\nQual amigo deseja excluir?(nome/indice): ");
    i = buscadadovalido(1, Numamigo);
    for (int j = 0; j < Numencontro; j++)
    {
        for (int k = 0; k < Listaencontro[j].Namigos; k++)
        {
            if (strcmp(Listaencontro[j].amigos[k]->nome, Listaamigo[i].nome) == 0)
            {
                CLS
                    printf("Este amigo esta no encontro %s, deseja remove-lo do encontro?(s/n): ", Listaencontro[j].nome);
                if (validasimnao())
                {
                    if (Listaencontro[j].Namigos > 1)
                    {
                        removeamigoencontro(i, j);
                    }
                    else
                    {
                        printf("Este amigo eh o unico no encontro, deseja excluir o encontro?(s/n): ");
                        if (validasimnao())
                        {
                            excluiencontro(j);
                        }
                        else
                        {
                            return;
                        }
                    }
                }
                else
                {
                    return;
                }
            }
        }
    }
    excluiamigo(i);
    sucesso(6);
    return;
}

void limpaamigo()
{
    for (int i = 0; i < Numamigo; i++)
    {
        free(Listaamigo[i].nome);
        free(Listaamigo[i].apelido);
        free(Listaamigo[i].email);
        free(Listaamigo[i].telefone);
    }
    free(Listaamigo);
    return;
}
void limpalocal()
{
    for (int i = 0; i < Numlocal; i++)
    {
        free(Listalocal[i].endereco.estado);
        free(Listalocal[i].endereco.cidade);
        free(Listalocal[i].endereco.bairro);
        free(Listalocal[i].endereco.numero);
        free(Listalocal[i].endereco.logradouro);
        free(Listalocal[i].nomelocal);
    }
    free(Listalocal);
    return;
}
void limpacategoria()
{
    for (int i = 0; i < Numcategoria; i++)
    {
        free(Listacategoria[i].categoria);
    }
    free(Listacategoria);
    return;
}
void limpaencontro()
{
    for (int i = 0; i < Numencontro; i++)
    {
        free(Listaencontro[i].nome);
        free(Listaencontro[i].descricao);
        for (int j = 0; j < Listaencontro[i].Namigos; j++)
        {
            Listaencontro[i].amigos[j] = NULL;
            free(Listaencontro[i].idamigos[j]);
        }
        free(Listaencontro[i].amigos);
        free(Listaencontro[i].idamigos);
        free(Listaencontro[i].idlocal);
        free(Listaencontro[i].idcat);
    }
    free(Listaencontro);
    return;
}

void limpamemoria()
{
    if (Numamigo != 0)
    {
        limpaamigo();
    }

    if (Numlocal != 0)
    {
        limpalocal();
    }

    if (Numcategoria != 0)
    {
        limpacategoria();
    }

    if (Numencontro != 0)
    {
        limpaencontro();
    }
    return;
}

void end()
{
    char word[] = "Obrigado por trabalhar com nossos produtos!";

    CLS for (int i = 0; word[i] != '\0'; i++)
    {
        printf("%c", word[i]);
        Sleep(55);
    }
    Sleep(750);
    exit(0);
}

void verifica_alocacao(void *v)
{
    if (!v)
    {
        ERRO(4);
        Sleep(1000);
        limpamemoria();
        exit(1);
    }
}

char valida16()
{
    char op;
    do
    {
        op = getch();
        if (op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6')
        {
            ERRO(1);
        }
    } while (op != '1' && op != '2' && op != '3' && op != '4' && op != '5' && op != '6');

    return op;
}

bool validadataenc(int dias, int mes, int ano)
{
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano < 2025)
        return false;
    if (mes < 1 || mes > 12)
        return false;
    if (dias < 1 || dias > meses[mes - 1])
        return false;
    if (ano % 4 == 0 && mes == 2 && dias > 29)
        return false;
    if (ano == 2025 && mes == 2 && dias < 6)
        return false;

    return true;
}

bool validanascimento(int dias, int mes, int ano)
{
    int meses[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (ano < 1894 || ano > 2024)
        return false;
    if (dias < 1 || dias > meses[mes - 1])
        return false;
    if (mes == 2 && ano % 4 == 0 && dias > 29)
        return false;
    return true;
}

void incluiamigo()
{
    CLS
        printf("Voce tem [%d] amigo(s) no momento.\n\n", Numamigo);

    if (Numamigo == 0)
    {
        Listaamigo = (tAmigo *)malloc(1 * sizeof(tAmigo));
    }
    else
    {
        Listaamigo = (tAmigo *)realloc(Listaamigo, (Numamigo + 1) * sizeof(tAmigo));
        if (Numencontro != 0)
        {
            rereferenciaamigo();
        }
    }
    verifica_alocacao(Listaamigo);
    Listaamigo[Numamigo] = criaamigo();
    Numamigo++;

    CLS
        sucesso(15);
    return;
}

bool validaapelido(char *apelido)
{
    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(apelido, Listaamigo[i].apelido) == 0)
        {
            return false;
        }
    }
    return true;
}

tAmigo criaamigo()
{
    char str[100];
    tAmigo amigo;

    printf("Qual o nome do seu %d amigo?: ", Numamigo + 1);
    do
    {
        GTS if (!validanome(str))
        {
            printf("\nJa existe um amigo com este nome.\nAdicione um sobrenome para diferencia-lo: ");
        }
        else
        {
            amigo.nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.nome);
            strcpy(amigo.nome, str);
            break;
        }
    } while (1);

    printf("Qual eh o apelido de %s?: ", amigo.nome);
    do
    {
        GTS if (!validaapelido(str))
        {
            printf("\nJa existe um amigo com este apelido.\nDigite novamente: ");
        }
        else
        {
            amigo.apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.apelido);
            strcpy(amigo.apelido, str);
            break;
        }
    } while (1);

    printf("Qual eh o telefone de %s?: ", amigo.nome);
    do
    {
        GTS if (!validanumero(str))
        {
            printf("Ja existe um amigo com este telefone.\nDigite novamente: ");
        }
        else
        {
            amigo.telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.telefone);
            strcpy(amigo.telefone, str);
            break;
        }

    } while (1);

    printf("Qual o email de %s?: ", amigo.nome);
    do
    {
        GTS if (validaemail(str))
        {
            amigo.email = (char *)malloc((strlen(str) + 1) * sizeof(char));
            verifica_alocacao(amigo.email);
            strcpy(amigo.email, str);
            break;
        }
    } while (1);

    printf("Qual eh a data de nascimento de %s? (dd/mm/aaaa): ", amigo.nome);
    do
    {
        scanf("%d/%d/%d", &amigo.nascimento.dia, &amigo.nascimento.mes, &amigo.nascimento.ano);
        if (!(validanascimento(amigo.nascimento.dia, amigo.nascimento.mes, amigo.nascimento.ano)))
        {
            ERRO(-1);
        }
        else
        {
            break;
        }
    } while (1);

    CLS return amigo;
}

void switchamigo(char op)
{
    switch (op)
    {
    case '1':
        incluiamigo();
        break;
    case '2':
        if (Numamigo == 0)
        {
            ERRO(5);
            Sleep(1500);
            return;
        }
        else
        {
            editaamigo();
        }
        break;
    case '3':
        if (Numamigo == 0)
        {
            ERRO(6);
            Sleep(2500);
            return;
        }
        else if (Numamigo < 2)
        {
            if (adviser())
            {
                orientaexcluiamigo();
            }
            else
            {
                return;
            }
        }
        else
        {
            orientaexcluiamigo();
        }
        break;
    }
    return;
}

void mainamigo()
{
    char op;
    while (op != '4')
    {
        menuamigo();
        op = valida14();
        if (op == '4')
        {
            break;
        }
        switchamigo(op);
    }
    return;
}

void menuamigo()
{

    CLS
        printf("***MENU AMIGO***\n\n");
    printf("-------------------------\n");
    printf("Digite:\n\n");
    printf("[1] para criar um amigo\n");
    if (Numamigo > 0)
    {
        printf("[2] para editar um amigo\n");
        printf("[3] para excluir um amigo\n");
    }
    printf("[4] para voltar\n");
    printf("\n--O que deseja fazer?: ");
}

void switchprincipal(char op)
{

    switch (op)
    {
    case '5':
        mainrelatorios();
        break;

    case '1':
        mainamigo();
        break;

    case '2':
        mainlocal();
        break;

    case '3':
        maincat();
        break;

    case '4':
        mainencontro();
        break;
    }
    return;
}

void menuprincipal()
{
    CLS
        printf("***MENU PRINCIPAL***\n\n");
    printf("-------------------------\n");
    printf("Digite:\n\n");
    printf("[1] para abrir o menu amigo\n");
    printf("[2] para abrir o menu local\n");
    printf("[3] para abrir o menu categoria\n");
    printf("[4] para abrir o menu encontro\n");
    printf("[5] para abrir os registros\n");
    printf("[6] para Sair\n");
    printf("\n\n--O que deseja fazer?: ");
}

bool validanome(char *nome)
{

    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(nome, Listaamigo[i].nome) == 0)
        {
            return false;
        }
    }
    return true;
}

bool validaemail(char *email)
{

    int countA = 0, countB = 0;

    // step 1v
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            countA++;
        }
        else if (email[i] == '.')
        {
            countB++;
        }
    }

    if (countA != 1 || countB < 1)
    {
        printf("Email invalido! O email deve conter 1 '@' e ao menos 1 '.'\nDigite novamente: ");
        return false;
    }

    // step 2v
    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(email, Listaamigo[i].email) == 0)
        {
            printf("Email invalido! Este email ja existe!\nDigite novamente: ");
            return false;
        }
    }
    return true;
}

bool validanumero(char *num)
{

    for (int i = 0; i < Numamigo; i++)
    {
        if (strcmp(num, Listaamigo[i].telefone) == 0)
        {
            return false;
        }
    }
    return true;
}

int buscaxnome(int op, char *str)
{
    int i;

    CLS do
    {
        printf("Buscando[%s]", str);
        for (int j = 0; j < 3; j++)
        {
            printf(".");
            Sleep(400);
        }
        CLS switch (op)
        {
        case 1:
            for (int i = 0; i < Numamigo; i++)
            {
                if ((strcmp(Listaamigo[i].nome, str) == 0) || strcmp(Listaamigo[i].apelido, str) == 0)
                {
                    printf("Amigo encontrado!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(3);
            Sleep(1500);
            break;
        case 2:
            for (i = 0; i < Numlocal; i++)
            {
                if (strcmp(Listalocal[i].nomelocal, str) == 0)
                {
                    printf("Local encontrado!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(20);
            Sleep(1500);
            break;
        case 3:
            for (i = 0; i < Numcategoria; i++)
            {
                if (strcmp(Listacategoria[i].categoria, str) == 0)
                {
                    printf("Categoria encontrada!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(9);
            Sleep(1500);
            break;
        case 4:
            for (i = 0; i < Numencontro; i++)
            {
                if (strcmp(Listaencontro[i].nome, str) == 0)
                {
                    printf("Encontro encontrado!");
                    Sleep(1000);
                    CLS return i;
                }
            }
            ERRO(14);
            Sleep(1500);
            break;
        }

        switch (op)
        {
        case 1:
            exibeamigo(false, false);
            break;
        case 2:
            exibelocal(false, false);
            break;
        case 3:
            exibecategoria(false);
            break;
        case 4:
            exibeencontro(false, false, false);
            break;
        }
        GTS continue;
    }
    while (1)
        ;
}

bool validarhorario(int hora, int min)
{

    if (hora < 0 || hora > 23)
    {
        return false;
    }
    if (min < 0 || min > 59)
    {
        return false;
    }
    return true;
}

void ERRO(int opErro)
{

    switch (opErro)
    {
    case -2:
        printf("Horario invalido! Digite novamente: ");
        break;
    case -1:
        printf("Data invalida! Digite novamente: ");
        break;
    case 0:
        printf("Realocar um vetor dinamico para 0 posicoes nao e uma boa ideia.\nTem certeza de que deseja prosseguir?(S/N): ");
        break;
    case 1:
        printf("Operador invalido! Digite novamente: ");
        break;
    case 2:
        printf("Amigo invalido! Digite novamente: "); //
        break;
    case 3:
        printf("Amigo nao encontrado! Digite novamente: "); //
        break;
    case 4:
        printf("ERRO AO ALOCAR MEMORIA!!!"); //
        break;
    case 5:
        printf("Nao existem amigos para serem editados!"); //
        break;
    case 6:
        printf("Nao existem amigos para serem excluidos!"); //
        break;
    case 7:
        printf("Nao existem amigos para serem listados!"); //
        break;
    case 9:
        printf("Categotria nao encontrada! Digite novamente: "); //
        break;
    case 10:
        printf("Nao existem categorias para serem listadas!"); //
        break;
    case 11:
        printf("Nao existem categorias para serem editadas!"); //
        break;
    case 12:
        printf("Nao existem categorias para serem excluidas!"); //
        break;
    case 14:
        printf("Encontro nao encontrado! Digite novamente: "); //
        break;
    case 15:
        printf("Nao existem encontros para serem listados!"); //
        break;
    case 16:
        printf("Nao existem encontros para serem editados!"); //
        break;
    case 17:
        printf("Nao existem encontros para serem excluidos!"); //
        break;
    case 18:
        printf("Nao existem Locais para serem listados!"); //
        break;
    case 20:
        printf("Local nao encontrado! Digite novamente: "); //
        break;
    case 21:
        printf("Nao existem Locais para serem editados!"); //
        break;
    case 22:
        printf("Nao existem Locais para serem excluidos!"); //
        break;
    case 23:
        printf("Ja existe um encontro com este nome! Digite novamente: ");
    default:
        printf("___FUDEU MUITO___");
        limpamemoria();
        end();
    }
}

void sucesso(int opSucesso)
{
    switch (opSucesso)
    {
    case 1:
        printf("O amigo criado foi adicionado com sucesso!\n");
        Sleep(1500);
        break;
    case 2:
        printf("O local criado foi adicionado com sucesso!\n");
        Sleep(1500);
        break;
    case 3:
        printf("A categoria criada foi adicionada com sucesso!\n");
        Sleep(1500);
        break;
    case 4:
        printf("Encontro excluido com sucesso!\n");
        Sleep(1500);
        break;
    case 5:
        printf("Encontro editado com sucesso!\n");
        Sleep(1500);
        break;
    case 6:
        printf("Amigo excluido com sucesso!\n");
        Sleep(1500);
        break;
    case 7:
        printf("Amigo editado com sucesso!\n");
        Sleep(1500);
        break;
    case 8:
        printf("Encontro criado com sucesso!\n");
        Sleep(1500);
        break;
    case 9:
        printf("Categoria criada com sucesso!\n");
        Sleep(1500);
        break;
    case 13:
        printf("Categoria excluida com sucesso!\n");
        Sleep(1500);
        break;
    case 14:
        printf("Categoria editada com sucesso!\n");
        Sleep(1500);
        break;
    case 10:
        printf("Local excluido com sucesso!\n");
        Sleep(1500);
        break;
    case 11:
        printf("Local editado com sucesso!\n");
        Sleep(1500);
        break;
    case 12:
        printf("Local criado com sucesso!\n");
        Sleep(1500);
        break;
    case 15:
        printf("Amigo criado com sucesso!\n");
        Sleep(1500);
        break;
    }
    return;
}