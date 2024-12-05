#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXMUSICA 100

typedef struct
{
    int min;
    int seg;
} Duracao;

typedef struct
{
    char *nome;
    char **artista;
    int numArtista;
    char *album;
    char **estilo;
    int numEstilo;
    Duracao duracao;
} Musica;

Musica *_PlayList;
int _NumMusica = 0;

/* funcoes */
void mensagemError(int codigoErro);                // imprime os erros do programa
void menu();                                       // mostrar as opcoes do menu
void opcao_menu(int op);                           // disparar a funcionalidade escolhida
int inclusao();                                    // dispara funcao para incluir musica
int alteracao();                                   // dispara funcao alterar musica
int exclusao();                                    // dispara funcao excluir musica
Musica criaMusica();                               // criar musica digitada pelo usuario
void imprimeMusica(Musica m);                      // imprime musica
int validaDuracao(int min, int seg);               // valida duracao
void salvarArquivo();                              // salvar os dados da memoria em uma arquivo
void recurperaDado();                              // recupera dados do arquivo
void menu_listar();                                // lista sub listar
void opcao_menu_listar(int op);                    // dispara uma das funcoes de listar
int listarPlaylist(int pause);                     // listar todas as musica
int alterarFaixa(int faixa);                       // funcionalid. de alterar uma faixa
int menuAlterarAtributo();                         // menu de escolha do atributo a ser alterado
void disparaTpAlteracaoArtista(int op, int faixa); // dispara tp alteracao p/ artista
void adicionarArtista(int faixa);                  // adicionar um novo artista
void alterarArtista(int faixa);                    // alterar um artista
void imprimeArtistaMusica(Musica m);               // imprime os artistas de uma musica
void excluirArtista(int faixa);                    // excluir um artita
void menuAlterarOpcoes(char *str);                 // menu de opcoes para operacao Editar
void disparaTpAlteracaoEstilo(int op, int faixa);  // dispara tp alteracao p/ estilo
void adicionarEstilo(int faixa);                   // adicionar um novo estilo
void alterarEstilo(int faixa);                     // alterar um estilo
void imprimeEstiloMusica(Musica m);                // imprime os estilos de uma musica
void excluirEstilo(int faixa);                     // excluir um estilo
void limpaMemoria();                               // limpa toda memoria alocada dinamicamente
void limparPonteiros();                            // limpa os ponteiros para ponteiros
void limpaPonteiroArtista(int faixa);              // limpa ponteiro de artistas
void limpaPonteiroEstilo(int faixa);               // limpa ponteiro de estilo
void excluirFaixa(int faixa);                      // excluir faixa
void reorganizarPlaylist(int faixa);               // reorganiza lista de musica pos exclusao

int main()
{
    int op = 1;
    recurperaDado();
    while (op != 5)
    {
        menu();
        scanf("%d", &op);
        fflush(stdin);
        system("cls");
        opcao_menu(op);
    }

    limpaMemoria();

    return 0;
}

void menu()
{
    system("cls");
    printf(" - (1) Incluir Musica\n");
    printf(" - (2) Excluir Musica\n");
    printf(" - (3) Alterar Musica\n");
    printf(" - (4) Listar\n");
    printf(" - (5) Sair\n\n");

    printf(" ** Digite a opcao: ");
}

void opcao_menu(int op)
{
    int erro, opS = -1;
    if (op < 1 || op > 5)
    {
        mensagemError(0);
    }
    else if (op < 5)
    {

        if (op == 1) // incluir
        {
            erro = inclusao();
        }
        else if (op == 2) // excluir
        {
            erro = exclusao();
        }
        else if (op == 3) // alterar
        {
            erro = alteracao();
        }
        else if (op == 4) // listar
        {
            if (_NumMusica <= 0)
            {
                erro = -2;
                opS = 3;
            }

            while (opS != 3)
            {
                if (_NumMusica > 1)
                {
                    menu_listar();
                    scanf("%d", &opS);
                    fflush(stdin);
                    opcao_menu_listar(opS);
                }
                else
                {
                    opS = 3;
                    opcao_menu_listar(2);
                }
            }
        }

        // em caso de erro em alguma operacao
        // mostrar na tela o erro
        if (erro < 0)
        {
            mensagemError(erro);
        }
    }
    else
    {
        // condicional para opcao sair
        if (_NumMusica >= 0)
        {
            salvarArquivo();
        } 
    }
}

int inclusao()
{

    if (_NumMusica >= MAXMUSICA)
    {
        return -1;
    }

    if (_NumMusica == 0) // se a lista de musica esta vazia
    {
        _PlayList = (Musica *)malloc(1 * sizeof(Musica));
    }
    else
    {
        _PlayList = (Musica *)realloc(_PlayList, (_NumMusica + 1) * sizeof(Musica));
    }

    if (!_PlayList)
    {
        return -10;
    }

    _PlayList[_NumMusica] = criaMusica();
    system("cls");
    imprimeMusica(_PlayList[_NumMusica]);
    _NumMusica++;
    system("PAUSE");
    return 1;
}

Musica criaMusica()
{

    Musica m;
    char strAux[100], op;
    int adicionar;
    int erro = -1;

    printf("Nome da Musica: ");
    gets(strAux);
    m.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(m.nome, strAux);
    fflush(stdin);

    printf("Album: ");
    gets(strAux);
    m.album = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(m.album, strAux);
    fflush(stdin);

    /* adicionando artista*/
    adicionar = 1;
    m.numArtista = 0;
    while (adicionar)
    {
        printf("Artista: ");
        gets(strAux);

        if (m.numArtista == 0)
        {
            m.artista = (char **)malloc(1 * sizeof(char *));
        }
        else
        {
            m.artista = (char **)realloc(m.artista, (m.numArtista + 1) * sizeof(char *));
        }

        if (!m.artista)
        {
            printf("Erro na Criacao do Vetor Artista!!!\n");
            exit(1);
        }

        m.artista[m.numArtista] = (char *)malloc(strlen(strAux + 1) * sizeof(char));
        if (!m.artista[m.numArtista])
        {
            printf("Erro na Criacao do Artista [%d]!!!\n", m.numArtista);
            exit(1);
        }

        strcpy(m.artista[m.numArtista++], strAux);

        op = 'x';
        while (op != 's' && op != 'n')
        {
            printf("** Adicionar Artista(S/N)? ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
            if (op == 's' || op == 'n')
            {
                break;
            }
            mensagemError(0);
        }

        if (op == 'n')
        {
            adicionar = 0;
        }
    }

    /* adicionando estilo*/
    adicionar = 1;
    m.numEstilo = 0;
    while (adicionar)
    {
        printf("Estilo: ");
        gets(strAux);

        if (m.numEstilo == 0)
        {
            m.estilo = (char **)malloc(1 * sizeof(char *));
        }
        else
        {
            m.estilo = (char **)realloc(m.estilo, (m.numEstilo + 1) * sizeof(char *));
        }

        if (!m.estilo)
        {
            printf("Erro na Criacao do Vetor Estilo!!!\n");
            exit(1);
        }

        m.estilo[m.numEstilo] = (char *)malloc(strlen(strAux + 1) * sizeof(char));
        if (!m.estilo[m.numEstilo])
        {
            printf("Erro na Criacao de Estilo [%d]!!!\n", m.numEstilo);
            exit(1);
        }

        strcpy(m.estilo[m.numEstilo++], strAux);

        op = 'x';
        while (op != 's' && op != 'n')
        {
            printf("** Adicionar Estilo (S/N)? ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);
            if (op == 's' || op == 'n')
            {
                break;
            }
            mensagemError(0);
        }

        if (op == 'n')
        {
            adicionar = 0;
        }
    }

    erro = -1;
    while (erro < 0)
    {
        printf("Duracao (MM SS): ");
        scanf("%d%d", &m.duracao.min, &m.duracao.seg);
        fflush(stdin);
        erro = validaDuracao(m.duracao.min, m.duracao.seg);
        if (erro < 0)
        {
            mensagemError(erro);
        }
    }

    return m;
}

void imprimeMusica(Musica m)
{
    int i;
    printf("- Nome da Musica: %s\n", m.nome);
    printf("- Album: %s\n", m.album);
    printf("- Artista: ");
    for (i = 0; i < m.numArtista; i++)
    {
        if (i < (m.numArtista - 1))
        {
            printf("%s, ", m.artista[i]);
        }
        else
        {
            printf("%s\n", m.artista[i]);
        }
    }
    printf("- Estilo: ");
    for (i = 0; i < m.numEstilo; i++)
    {
        if (i < (m.numEstilo - 1))
        {
            printf("%s, ", m.estilo[i]);
        }
        else
        {
            printf("%s\n", m.estilo[i]);
        }
    }
    printf("- Duraca (MM:SS): %d:%d\n", m.duracao.min, m.duracao.seg);
}

int validaDuracao(int min, int seg)
{
    if (min < 0)
    {
        return -5;
    }
    else if (seg >= 60 || seg < 0)
    {
        return -6;
    }
    else if (seg == 0 && min == 0)
    {
        return -7;
    }
    else
    {
        return 1;
    }
}

void menu_listar()
{
    system("cls");
    printf(" - (1) Listar APENAS UMA Musica \n");
    printf(" - (2) Listar TODAS as Musica \n");
    printf(" - (3) Voltar para Menu Anterior \n\n");

    printf(" ** Digite Opcao: ");
}

void opcao_menu_listar(int op)
{
    int erro, faixa;
    if (op < 1 || op > 3)
    {
        mensagemError(0);
    }
    else if (op < 3)
    {
        system("cls");
        if (op == 1) // listar uma musica especifica
        {
            if (_NumMusica == 1)
            {
                imprimeMusica(_PlayList[0]);
                system("PAUSE");
                return;
            }

            faixa = -1;
            while (faixa < 1 || faixa > _NumMusica)
            {
                printf("Digite a n. da Faixa [%d - %d]: ", 1, _NumMusica);
                scanf("%d", &faixa);
                if (faixa < 1 || faixa > _NumMusica)
                {
                    mensagemError(-8);
                    system("cls");
                    continue;
                }

                imprimeMusica(_PlayList[faixa - 1]);
                system("PAUSE");
            }
        }
        else if (op == 2) // listar todas as musicas
        {
            erro = listarPlaylist(1);
        }

        if (erro < 0)
        {
            mensagemError(erro);
        }
    }
}

int listarPlaylist(int pause)
{
    int i;

    if (_NumMusica <= 0)
    {
        return -2;
    }

    system("cls");

    for (i = 0; i < _NumMusica; i++)
    {
        printf("*** FAIXA[%d] ***\n", i + 1);
        imprimeMusica(_PlayList[i]);
        printf("\n");
    }

    if (pause)
    {
        system("PAUSE");
    }

    return 1;
}

void salvarArquivo()
{
    int i, j;
    FILE *pArq;
    
    // abrir arquivo
    pArq = fopen("musicaBD.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel criar o arquivo");
        exit(0);
    }

    for (i = 0; i < _NumMusica; i++)
    {
        fprintf(pArq, "%s;", _PlayList[i].nome);
        fprintf(pArq, "%s;", _PlayList[i].album);
        fprintf(pArq, "%d;", _PlayList[i].duracao.min);
        fprintf(pArq, "%d;", _PlayList[i].duracao.seg);

        for (j = 0; j < _PlayList[i].numArtista; j++)
        {
            fprintf(pArq, "%s@", _PlayList[i].artista[j]);
        }

        for (j = 0; j < _PlayList[i].numEstilo; j++)
        {
            fprintf(pArq, "%s#", _PlayList[i].estilo[j]);
        }

        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void recurperaDado()
{
    int i, sep, j;
    char str[100], c;

    FILE *pArq;
    // abrindo arquivo
    pArq = fopen("musicaBD.txt", "r");
    if (pArq)
    {
        i = 0;   // i usado para indexar str
        sep = 0; // usada para contar os separador ";/@/#"

        // percorre o arquivo ate o fim
        while (!feof(pArq))
        {
            c = fgetc(pArq);

            if ((c != '\n') && (c != ';') && (c != '@') && (c != '#') && (c != EOF))
            {
                str[i++] = c;
            }
            else if ((c == ';') || (c == '@') || (c == '#') || (c == '\n'))
            {
                str[i] = '\0';
                i = 0;

                if (c == ';')
                {
                    if (sep == 0)
                    {
                        if (_NumMusica == 0)
                        {
                            _PlayList = (Musica *)malloc(1 * sizeof(Musica));
                        }
                        else
                        {
                            _PlayList = (Musica *)realloc(_PlayList, (_NumMusica + 1) * sizeof(Musica));
                        }

                        _PlayList[_NumMusica].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].nome, str);
                        _PlayList[_NumMusica].numArtista = 0;
                        _PlayList[_NumMusica].numEstilo = 0;
                        sep++;
                    }
                    else if (sep == 1)
                    {
                        _PlayList[_NumMusica].album = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].album, str);
                        sep++;
                    }
                    else if (sep == 2)
                    {
                        _PlayList[_NumMusica].duracao.min = atoi(str);
                        sep++;
                    }
                    else if (sep == 3)
                    {
                        _PlayList[_NumMusica].duracao.seg = atoi(str);
                        sep = 0;
                    }
                }
                else if (c == '@')
                {
                    if (sep == 0)
                    {
                        _PlayList[_NumMusica].artista = (char **)malloc(1 * sizeof(char *));
                        j = _PlayList[_NumMusica].numArtista;
                        _PlayList[_NumMusica].artista[j] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].artista[j], str);
                        _PlayList[_NumMusica].numArtista++;
                    }
                    else
                    {
                        j = _PlayList[_NumMusica].numArtista;
                        _PlayList[_NumMusica].artista = (char **)realloc(_PlayList[_NumMusica].artista, (j + 1) * sizeof(char *));
                        _PlayList[_NumMusica].artista[j] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].artista[j], str);
                        _PlayList[_NumMusica].numArtista++;
                    }
                    sep = -1;
                }
                else if (c == '#')
                {
                    if (sep == -1)
                    {
                        _PlayList[_NumMusica].estilo = (char **)malloc(1 * sizeof(char *));
                        j = _PlayList[_NumMusica].numEstilo;
                        _PlayList[_NumMusica].estilo[j] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].estilo[j], str);
                        _PlayList[_NumMusica].numEstilo++;
                    }
                    else
                    {
                        j = _PlayList[_NumMusica].numEstilo;
                        _PlayList[_NumMusica].estilo = (char **)realloc(_PlayList[_NumMusica].estilo, (j + 1) * sizeof(char *));
                        _PlayList[_NumMusica].estilo[j] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                        strcpy(_PlayList[_NumMusica].estilo[j], str);
                        _PlayList[_NumMusica].numEstilo++;
                    }
                    sep = -2;
                }
                else
                {
                    sep = 0;
                    _NumMusica++;
                }
            }
        }
    }
    fclose(pArq);
}

int alteracao()
{
    int faixa = -1, resp;

    if (_NumMusica <= 0)
    {
        return -2;
    }

    while (faixa < 0 || faixa >= _NumMusica)
    {
        listarPlaylist(0);
        if (_NumMusica > 1)
        {
            printf("Digite a faixa que deseja altera [ %d - %d]: ", 1, _NumMusica);
            scanf("%d", &faixa);
            fflush(stdin);
            printf("\n");
        }
        else
        {
            faixa = 1;
        }

        faixa--;
        if (faixa < 0 || faixa >= _NumMusica)
        {
            mensagemError(-8);
        }
        else
        {
            resp = alterarFaixa(faixa);
        }
    }

    system("cls");
    if (resp > 0)
    {
        imprimeMusica(_PlayList[faixa]);
    }
    system("PAUSE");
}

int alterarFaixa(int faixa)
{
    int atributo = 1, erro = -1, opTpAlteracao;
    char op, strAux[100];

    while (atributo > 0)
    {
        atributo = menuAlterarAtributo();
        switch (atributo)
        {
        case 1:
            system("cls");
            printf(" ** Dados da Faixa\n");
            imprimeMusica(_PlayList[faixa]);
            printf("\nNovo Nome da Musica: ");
            gets(strAux);
            _PlayList[faixa].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(_PlayList[faixa].nome, strAux);
            fflush(stdin);
            break;
        case 2:
            system("cls");
            printf(" ** Dados da Faixa\n");
            imprimeMusica(_PlayList[faixa]);
            printf("\nNovo Nome do Album: ");
            gets(strAux);
            _PlayList[faixa].album = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(_PlayList[faixa].album, strAux);
            fflush(stdin);
            break;
        case 3:

            opTpAlteracao = 1;
            while (1)
            {
                menuAlterarOpcoes("Artista: ");
                scanf("%d", &opTpAlteracao);
                fflush(stdin);
                disparaTpAlteracaoArtista(opTpAlteracao, faixa);

                if (opTpAlteracao == 5)
                {
                    break;
                }
            }

            system("cls");
            printf(" ** Dados da Faixa\n");
            imprimeMusica(_PlayList[faixa]);
            fflush(stdin);
            break;

        case 4:

            opTpAlteracao = 1;
            while (1)
            {
                menuAlterarOpcoes("Estilo: ");
                scanf("%d", &opTpAlteracao);
                fflush(stdin);
                disparaTpAlteracaoEstilo(opTpAlteracao, faixa);

                if (opTpAlteracao == 5)
                {
                    break;
                }
            }

            system("cls");
            printf(" ** Dados da Faixa\n");
            imprimeMusica(_PlayList[faixa]);
            fflush(stdin);
            break;

        case 5:
            system("cls");
            printf(" ** Dados da Faixa\n");
            imprimeMusica(_PlayList[faixa]);

            while (erro < 0)
            {
                printf("\nNova Duracao (MM SS): ");
                scanf("%d%d", &_PlayList[faixa].duracao.min, &_PlayList[faixa].duracao.seg);
                fflush(stdin);
                erro = validaDuracao(_PlayList[faixa].duracao.min, _PlayList[faixa].duracao.seg);
                if (erro < 0)
                {
                    mensagemError(erro);
                }
            }

            break;
        case 6:
            return -1;
            break;
        }

        op = 'x';
        while (op != 's' && op != 'n')
        {
            printf("\nDeseja alterar outro atributo (s/n): ");
            scanf("%c", &op);
            fflush(stdin);
            op = tolower(op);

            if (op != 's' && op != 'n')
            {
                mensagemError(0);
            }
        }

        if (op == 'n')
        {
            atributo = -1;
        }
    }

    return 1;
}

int menuAlterarAtributo()
{
    int op = -1;

    while (op < 1 || op > 5)
    {
        system("cls");
        printf("*** Digite o Codigo do Atributo a Alterar\n");
        printf(" - (1) Nome da Musica \n");
        printf(" - (2) Album\n");
        printf(" - (3) Artista\n");
        printf(" - (4) Estilo\n");
        printf(" - (5) Duracao\n");
        printf(" - (6) Voltar para Menu Anterior\n\n");
        printf(" ** Digite a Opcao: ");
        scanf("%d", &op);
        fflush(stdin);
        if (op < 1 || op > 6)
        {
            mensagemError(0);
        }
        else
        {
            return op;
        }
    }
}

void menuAlterarOpcoes(char *str)
{
    system("cls");
    printf(" - (1) Incluir %s\n", str);
    printf(" - (2) Alterar %s\n", str);
    printf(" - (3) Excluir %s\n", str);
    printf(" - (4) Listar %s\n", str);
    printf(" - (5) Volta ao Menu Anterior\n\n");
    printf(" ** Digite a Opcao: ");
}

void disparaTpAlteracaoArtista(int op, int faixa)
{
    int erro = 1, opS = -1;
    if (op < 1 || op > 5)
    {
        mensagemError(0);
    }
    else if (op < 5)
    {
        if (op == 1)
        {
            adicionarArtista(faixa);
            printf("\n** ARTISTA ADICIONADO!!!\n");
            system("PAUSE");
        }
        else if (op == 2)
        {
            alterarArtista(faixa);
            system("PAUSE");
        }
        else if (op == 3)
        {
            if (_PlayList[faixa].numArtista == 1)
            {
                erro = -9;
            }
            else
            {
                excluirArtista(faixa);
                system("PAUSE");
            }
        }
        else if (op == 4)
        {
            system("cls");
            printf("** LISTA DE ARTISTAS!!!\n");
            imprimeArtistaMusica(_PlayList[faixa]);
            system("PAUSE");
        }
    }
    if (erro <= 0)
    {
        mensagemError(erro);
    }
}

void excluirArtista(int faixa)
{
    int opArtista = -1, i;
    char op_sn;
    while (1)
    {
        system("cls");
        imprimeArtistaMusica(_PlayList[faixa]);
        printf("\nEscolha o Artista que Deseja Excluir: ");
        scanf("%d", &opArtista);
        fflush(stdin);

        if ((opArtista < 1) || (opArtista > _PlayList[faixa].numArtista))
        {
            mensagemError(0);
            continue;
        }
        else
        {
            op_sn = 'n';
            while (1)
            {
                printf("*** Confirma Exclusao do Artista [ %d ]? (s/n): ", opArtista);
                scanf("%c", &op_sn);
                fflush(stdin);
                op_sn = tolower(op_sn);

                if ((op_sn != 'n') && (op_sn != 's'))
                {
                    mensagemError(0);
                    continue;
                }
                break;
            }

            if (op_sn == 's')
            {
                if (_PlayList[faixa].numArtista == opArtista)
                {
                    free(_PlayList[faixa].artista[opArtista - 1]);
                    _PlayList[faixa].numArtista--;
                }
                else
                {
                    for (i = opArtista - 1; i < (_PlayList[faixa].numArtista - 1); i++)
                    {
                        _PlayList[faixa].artista[i] = _PlayList[faixa].artista[i + 1];
                    }

                    // printf("num artist %d\n", _PlayList[faixa].numArtista);

                    // free(_PlayList[faixa].artista[_PlayList[faixa].numArtista]);
                    _PlayList[faixa].numArtista--;
                }
                printf("\n** ARTISTA EXCLUIDO!!!\n");
            }
            break;
        }
    }
}

void adicionarArtista(int faixa)
{
    char strAux[100];
    printf("\nNovo Artista: ");
    gets(strAux);
    _PlayList[faixa].artista = (char **)realloc(_PlayList[faixa].artista, (_PlayList[faixa].numArtista + 1) * sizeof(char *));

    if (!_PlayList[faixa].artista)
    {
        printf("Erro na Adicao de Um Novo Artista (1)!!!\n");
        exit(1);
    }

    _PlayList[faixa].artista[_PlayList[faixa].numArtista] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

    if (!_PlayList[faixa].artista[_PlayList[faixa].numArtista])
    {
        printf("Erro na Adicao de Um Novo Artista (2)!!!\n");
        exit(1);
    }

    strcpy(_PlayList[faixa].artista[_PlayList[faixa].numArtista], strAux);
    _PlayList[faixa].numArtista++;
}
void alterarArtista(int faixa)
{
    int opArtista;
    char op_sn, strAux[100];

    while (1)
    {
        system("cls");
        imprimeArtistaMusica(_PlayList[faixa]);

        if (_PlayList[faixa].numArtista > 1)
        {
            printf("\nEscolha o Artista que Deseja Alterar: ");
            scanf("%d", &opArtista);
            fflush(stdin);
        }
        else
        {
            opArtista = 1;
        }

        if ((opArtista < 1) || (opArtista > _PlayList[faixa].numArtista))
        {
            mensagemError(0);
        }
        else
        {
            op_sn = 'n';
            while (1)
            {
                printf("\nAlteracao do Artista [%d]: ", opArtista);
                gets(strAux);
                fflush(stdin);

                printf("Confirma a Alteracao [%d]? (s/n): ", opArtista);
                scanf("%c", &op_sn);
                fflush(stdin);
                op_sn = tolower(op_sn);

                if (op_sn != 'n' && op_sn != 's')
                {
                    mensagemError(0);
                    continue;
                }
                break;
            }
            if (op_sn == 's')
            {

                _PlayList[faixa].artista[opArtista - 1] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

                if (!_PlayList[faixa].artista[opArtista - 1])
                {
                    printf("Erro na Alteracao de Um Artista!!!\n");
                    exit(1);
                }
                strcpy(_PlayList[faixa].artista[opArtista - 1], strAux);
                printf("\n**ARTISTA ALTERADO!!!\n");
            }
            break;
        }
    }
}
void imprimeArtistaMusica(Musica m)
{
    int i;
    for (i = 0; i < m.numArtista; i++)
    {
        printf("[ %d ] - %s\n", i + 1, m.artista[i]);
    }
}

void disparaTpAlteracaoEstilo(int op, int faixa)
{
    int erro = 1, opS = -1;
    if (op < 1 || op > 5)
    {
        mensagemError(0);
    }
    else if (op < 5)
    {
        if (op == 1)
        {
            adicionarEstilo(faixa);
            printf("\n** ESTILO ADICIONADO!!!\n");
            system("PAUSE");
        }
        else if (op == 2)
        {
            alterarEstilo(faixa);
            system("PAUSE");
        }
        else if (op == 3)
        {
            if (_PlayList[faixa].numEstilo == 1)
            {
                erro = -11;
            }
            else
            {
                excluirEstilo(faixa);
                system("PAUSE");
            }
        }
        else if (op == 4)
        {
            system("cls");
            printf("** LISTA DE ESTILO!!!\n");
            imprimeEstiloMusica(_PlayList[faixa]);
            system("PAUSE");
        }
    }
    if (erro <= 0)
    {
        mensagemError(erro);
    }
}
void adicionarEstilo(int faixa)
{
    char strAux[100];
    printf("\nNovo Estilo: ");
    gets(strAux);
    
    _PlayList[faixa].estilo = (char **)realloc(_PlayList[faixa].estilo, (_PlayList[faixa].numEstilo + 1) * sizeof(char *));

    if (!_PlayList[faixa].estilo)
    {
        printf("Erro na Adicao de Um Novo Estilo (1)!!!\n");
        exit(1);
    }

    _PlayList[faixa].estilo[_PlayList[faixa].numEstilo] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

    if (!_PlayList[faixa].estilo[_PlayList[faixa].numEstilo])
    {
        printf("Erro na Adicao de Um Novo Estilo (2)!!!\n");
        exit(1);
    }

    strcpy(_PlayList[faixa].estilo[_PlayList[faixa].numEstilo], strAux);
    _PlayList[faixa].numEstilo++;
}
void alterarEstilo(int faixa)
{
    int opEstilo;
    char op_sn, strAux[100];

    while (1)
    {
        system("cls");
        imprimeEstiloMusica(_PlayList[faixa]);

        if (_PlayList[faixa].numEstilo > 1)
        {
            printf("\nEscolha o Estilo que Deseja Alterar: ");
            scanf("%d", &opEstilo);
            fflush(stdin);
        }
        else
        {
            opEstilo = 1;
        }

        if ((opEstilo < 1) || (opEstilo > _PlayList[faixa].numEstilo))
        {
            mensagemError(0);
        }
        else
        {
            op_sn = 'n';
            while (1)
            {
                printf("\nAlteracao do Estilo [%d]: ", opEstilo);
                gets(strAux);
                fflush(stdin);

                printf("Confirma a Alteracao [%d]? (s/n): ", opEstilo);
                scanf("%c", &op_sn);
                fflush(stdin);
                op_sn = tolower(op_sn);

                if (op_sn != 'n' && op_sn != 's')
                {
                    mensagemError(0);
                    continue;
                }
                break;
            }
            if (op_sn == 's')
            {

                _PlayList[faixa].estilo[opEstilo - 1] = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

                if (!_PlayList[faixa].estilo[opEstilo - 1])
                {
                    printf("Erro na Alteracao de Um Estilo!!!\n");
                    exit(1);
                }
                strcpy(_PlayList[faixa].estilo[opEstilo - 1], strAux);
                printf("\n**ESTILO ALTERADO!!!\n");
            }
            break;
        }
    }
}

void imprimeEstiloMusica(Musica m)
{
    int i;
    for (i = 0; i < m.numEstilo; i++)
    {
        printf("[ %d ] - %s\n", i + 1, m.estilo[i]);
    }
}

void excluirEstilo(int faixa)
{
    int opEstilo = -1, i;
    char op_sn;
    while (1)
    {
        system("cls");
        imprimeEstiloMusica(_PlayList[faixa]);
        printf("\nEscolha o Artista que Deseja Excluir: ");
        scanf("%d", &opEstilo);
        fflush(stdin);

        if ((opEstilo < 1) || (opEstilo > _PlayList[faixa].numEstilo))
        {
            mensagemError(0);
            continue;
        }
        else
        {
            op_sn = 'n';
            while (1)
            {
                printf("*** Confirma Exclusao do Artista [ %d ]? (s/n): ", opEstilo);
                scanf("%c", &op_sn);
                fflush(stdin);
                op_sn = tolower(op_sn);

                if ((op_sn != 'n') && (op_sn != 's'))
                {
                    mensagemError(0);
                    continue;
                }
                break;
            }

            if (op_sn == 's')
            {
                if (_PlayList[faixa].numEstilo == opEstilo)
                {
                    free(_PlayList[faixa].estilo[opEstilo - 1]);
                    _PlayList[faixa].numEstilo--;
                }
                else
                {
                    for (i = opEstilo - 1; i < (_PlayList[faixa].numEstilo - 1); i++)
                    {
                        _PlayList[faixa].estilo[i] = _PlayList[faixa].estilo[i + 1];
                    }

                    // free(_PlayList[faixa].estilo[_PlayList[faixa].numEstilo]);
                    _PlayList[faixa].numEstilo--;
                }
                printf("\n** ESTILO EXCLUIDO!!!\n");
            }
            break;
        }
    }
}

int exclusao()
{
    int faixa = -1, exc = 0;
    char op;

    if (_NumMusica <= 0)
    {
        return -2;
    }

    while (faixa < 0 || faixa >= _NumMusica)
    {
        system("cls");
        if (_NumMusica == 1)
        {
            op = 'x';
            while (op != 's' && op != 'n')
            {
                system("cls");
                imprimeMusica(_PlayList[0]);
                printf("\nDeseja Escluir a Faixa [1]? (s/n): ");
                scanf("%c", &op);
                fflush(stdin);
                op = tolower(op);

                if (op != 's' && op != 'n')
                {
                    mensagemError(-8);
                }
            }

            if (op == 's')
            {
                excluirFaixa(0);
                exc = 1;
            }

            break;
        }
        else
        {
            listarPlaylist(0);
            printf("Digite a Faixa que Deseja Excluir [%d-%d]: ", 1, _NumMusica);
            scanf("%d", &faixa);
            fflush(stdin);
            printf("\n");
            faixa--;

            if ((faixa < 0) || (faixa >= _NumMusica))
            {
                mensagemError(-8);
            }
            else
            {

                op = 'x';
                while (op != 's' && op != 'n')
                {
                    system("cls");
                    imprimeMusica(_PlayList[faixa]);
                    printf("\nDeseja Excluir a Faixa [%d]: (s/n): ", faixa + 1);
                    scanf("%c", &op);
                    fflush(stdin);
                    op = tolower(op);

                    if (op != 's' && op != 'n')
                    {
                        mensagemError(-8);
                    }
                }

                if (op == 's')
                {
                    excluirFaixa(faixa);
                    exc = 1;
                }
                break;
            }
        }
    }

    if (exc)
    {
        system("cls");
        printf("EXCLUSAO BEM SUCEDIDA!!!\n");
        system("PAUSE");
    }
}
void excluirFaixa(int faixa)
{
    if ((_NumMusica == 1) && (faixa == _NumMusica))
    {
        limpaPonteiroArtista(faixa);
        limpaPonteiroEstilo(faixa);
        _NumMusica--;
    }
    else
    {
        reorganizarPlaylist(faixa);
    }
}
void reorganizarPlaylist(int faixa)
{
    int i;
    for (i = faixa; i < (_NumMusica - 1); i++)
    {
        _PlayList[i] = _PlayList[i + 1];
    }
    _NumMusica--;
}

void limpaMemoria()
{
    limparPonteiros();
    free(_PlayList);
}
void limparPonteiros()
{
    int i;
    for (i = 0; i < _NumMusica; i++)
    {
        limpaPonteiroArtista(i);
        limpaPonteiroEstilo(i);
    }
}
void limpaPonteiroArtista(int faixa)
{
    int i;
    for (i = 0; i < _PlayList[faixa].numArtista; i++)
    {
        free(_PlayList[faixa].artista[i]);
    }
}

void limpaPonteiroEstilo(int faixa)
{
    int i;
    for (i = 0; i < _PlayList[faixa].numEstilo; i++)
    {
        free(_PlayList[faixa].estilo[i]);
    }
}

void mensagemError(int codigoErro)
{
    switch (codigoErro)
    {
    case 0:
        printf("ERRO: Opcao Invalida!!!\n");
        break;

    case -1:
        printf("ERRO: Lista de Musica Atingiu Seu Limite!!!\n");
        break;

    case -2:
        printf("ERRO: Lista de Musica Vazia!!!\n");
        break;

    case -5:
        printf("ERRO: Digite Minuto Corretamente!!!\n");
        break;

    case -6:
        printf("ERRO: Digite Segundo Corretamente!!!\n");
        break;

    case -7:
        printf("ERRO: Digite Minuto e Segundo Corretamente!!!\n");
        break;

    case -8:
        printf("ERRO: Faixa Invalida!!!\n");
        break;

    case -9:
        printf("ERRO: Exclusao de Artista Nao Permitida!!!\n");
        break;

    case -10:
        printf("ERRO: Erro de Alocacao de Memoria!!!\n");
        break;

    case -11:
        printf("ERRO: Exclusao de Estilo Nao Permitida!!!\n");
        break;

    default:
        printf("ERRO!!!\n");
        break;
    }

    system("PAUSE");
}
