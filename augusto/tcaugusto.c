#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{

    char *bairro, *cidade, *estado, *logradouro, *num;

} SPlace;

typedef struct
{
    int dia, mes, ano;

} SData;

typedef struct
{
    char *nome;
    SData datanasc;
    char *apelido;
    char *email;
    char *telefone;

} SAmigo;

typedef struct
{
    char *nomelocal;
    SPlace local;
} SLocal;

typedef struct
{
    char *nomecat;

} SCategoria;

typedef struct
{
    int hora, minuto;
} SHora;

typedef struct
{
    char *nomeencontro;
    SData dataencontro;
    SHora horaencontro;
    char *localencontro;
    char **amigoencontro;
    int enumamigos;
    char *categoriaencontro;
    char *descricao;

} SEncontro;

// aperte Ctrl K + Ctrl 0 para minimizar e acessar funcões mais facilmente ;)
// aperte Ctrl K + Ctrl J para maximizar (desdobrar) TODAS as funcões
// - dicas do otavio augusto :))

SEncontro *GEncontro;
int NEncontro = 0;

SAmigo *GAmigo;
int Namigo = 0;

SLocal *GLocal;
int Nlocal = 0;

SCategoria *GCategoria;
int NCat = 0;

//augsuto

// A U X I L I A R
void limparTela();
void flushs();
int desejaAlterar();
int validaData(int dd, int mm, int yy);
void mensagemErro(int erro);
void pause();
int validaHora(int hora, int min);
void salvandoAviso();

// A R Q U I V O
void salvaAmigo();
void limpaAmigo();
void recuperaAmigo();
void salvaLocal();
void limpaLocal();
void recuperaLocal();
void salvaCat();
void limpaCat();
void recuperaCat();
void recuperaDado();
void salvaDado();
void limpaDado();

// I M P R E S S O R A S   A U X I L I A R E S
void listaNomesAmigo();
void listaNomesLocal();
void listaNomesCategoria();

// M E N U
int menuPrincipal();
void menuAmigo();
void listaMenu();
void menuLocal();
void menuCategoria();
void menuEncontro();
void relaCat();

// A M I G O
SAmigo cadastraAmigo(int num);
void imprimeAmigo(SAmigo a, int num);
void listaTodosAmigos();
void editaAmigo();
void switchAmigo(int op, int amigo);
void incluiAmigo();
void excluiAmigo();
void listaAmigo();

// L O C A L
SLocal cadastraLocal(int num);
void incluiLocal();
void imprimeLocal(SLocal a, int num);
void listaTodosLocais();
void editaLocal();
void switchLocal(int op, int local);
void excluiLocal();
void listaLocal();

// C A T E G O R I A
void listaCat();
void imprimeCategoria(SCategoria c, int num);
void listaTodasCategorias();
void editaCategoria();
void switchCat(int op, int cat);
void excluiCat();
void incluiCategoria();
SCategoria cadastraCategoria(int num);

// E N C O N T R O
void imprimeEncontro(SEncontro e, int enc);
void listaNomesEncontros();
void listaTodosEncontros();
void editaEncontro();
void switchEncontro();
void excluiEncontro();
void listaAmigosDoEncontro(SEncontro e);
void listaEnc();
void recuperaEncontro();
void salvaEncontro();
void limpaEncontro();
void incluiEncontro();
SEncontro cadastraEncontro(int num);
SEncontro menuEditaAmigoEncontro(int numemc, SEncontro e);

//       C        O        D        I        G        O            -----------------------------------------------------------

// M A I N   E   A U X
int main()
{
    int op;
    recuperaDado();
    while (op != 6)
    {
        op = menuPrincipal();

        if (op != 5 && op != 6)
        {
            salvaDado();
            salvandoAviso();
        }
        limparTela();
    }

    limpaDado();
}

void salvandoAviso()
{
    limparTela();
    printf("Salvando. . . ");
    sleep(1);
}
int TodosOuUmLista()
{
    int op = 0;

    do
    {
        limparTela();
        printf("+--------------------------------------------------+\n");
        printf("| Deseja listar todos ou apenas um específico?    |\n");
        printf("+--------------------------------------------------+\n");
        printf("| 1. Todos                                         |\n");
        printf("| 2. Especifico                                    |\n");
        printf("+--------------------------------------------------+\n");
        printf("\n");

        scanf("%d", &op);
        limparTela();
        if (op == 1)
        {
            return 1;
        }
        else if (op == 2)
        {
            return 2;
        }
        else
        {
            mensagemErro(-1);
        }

    } while (op < 1 || op > 2);

    return 0;
}
void limparTela()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux e macOS
#endif
}
void flushs()
{
#ifdef _WIN32
    fflush(stdin); // Windows
#else
    __fpurge(stdin); // Linux e macOS
#endif
}
void pause()
{
#ifdef _WIN32
    system("pause");
#else
    printf("\nPressione qualquer tecla para continuar. . .");
    flushs();
    getchar();
#endif
}
int validaHora(int hora, int min)
{
    if (hora < 0 || hora >= 24 || min < 0 || min >= 60)
    {
        return -5;
    }
    return 0;
}
int desejaAlterar()
{

    char opc = 0;
    do
    {
        printf("\nDeseja alterar mais alguma coisa? (S/N): ");
        flushs();
        scanf(" %c", &opc);
        flushs();
        if (opc == 'N' || opc == 'n')
        {

            limparTela();
            printf("Voce escolheu [N], Voltando. . . \n");
            pause();
            return 0;
        }
        else if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Voce escolheu [S]. . . ");
            printf("\n");
            pause();
            return 1;
        }
        else
        {
            mensagemErro(-1);
            limparTela();
        }

    } while (opc == 'N' || opc == 'n' || opc == 'S' || opc == 's');

    return 0;
}
int validaData(int dd, int mm, int yy)
{
    if (yy >= 1900 && yy <= 9999)
    {
        if (mm >= 1 && mm <= 12)
        {
            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
            {
                return 1;
            }
            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
            {
                return 1;
            }
            else if ((dd >= 1 && dd <= 28) && (mm == 2))
            {
                return 1;
            }
            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
            {
                return 1;
            }
            else
            {
                return -2;
            }
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -2;
    }
}
void mensagemErro(int erro)
{
    limparTela();
    printf("\n===============================================================================\n");
    switch (erro)
    {
    default:
        printf("ERRO!. . . ");
        break;
    case -1:
        printf("ERRO! opcao invalida!\n");
        break;
    case -2:
        printf("ERRO! Data Invalida!\n");
        break;
    case -3:
        printf("ERRO! Ja existe um amigo com esse nome!\n");
        break;
    case -4:
        printf("Erro ao alocar memória\n");
        break;
    case -5:
        printf("Hora invalida!!\n");
        break;
    case -6:
        printf("ERRO! Nao e possivel executar a acao, pois esta vinculado a um encontro!\n");
        printf("Remova do encontro antes de fazer qualquer coisa.\n");
        break;
    case -7:
        printf("ERRO! Nao ha nenhum amigo disponivel!\n");
        printf("Adicione!\n");
        break;
    case -8:
        printf("ERRO! Nao ha nenhum local disponivel!\n");
        printf("Adicione!\n");
        break;
    case -9:
        printf("ERRO! Nao ha nenhuma categoria disponivel!\n");
        printf("Adicione!\n");
        break;
    case -10:
        printf("ERRO! Nao ha nenhum encontro disponivel!\n");
        printf("Adicione!\n");
        break;
    }
    printf("===============================================================================\n\n");
    pause();
    limparTela();
}

// M E N U S
int menuPrincipal()
{
    limparTela();
    printf("+------/  \\--------------------------/  \\------+\n");
    printf("|                MENU  PRINCIPAL               |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Manter amigo                              |\n");
    printf("< 2. Manter local                              >\n");
    printf("| 3. Manter categoria                          |\n");
    printf("< 4. Manter encontro                           >\n");
    printf("| 5. Relatorios                                |\n");
    printf("| 6. Sair                                      |\n");
    printf("+----------------------------------------------+\n\n");

    int op = 0;
    printf("Insira sua opcao: ");
    scanf("%d", &op);

    switch (op)
    {
    default:
        mensagemErro(-1);
    case 1:
        menuAmigo();
        break;
    case 2:
        menuLocal();
        break;
    case 3:
        menuCategoria();
        break;
    case 4:
        menuEncontro();
        break;
    case 5:
        listaMenu();
        break;
    case 6:
        break;
    }
    return op;
}
void menuAmigo()

{

    limparTela();
    int op = 0;
    while (op != 4)
    {

        limparTela();
        printf("+----------------------------------------------+\n");
        printf("|                 MENU DE AMIGOS               |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Adicionar Amigo                           |\n");
        printf("| 2. Editar Amigo                              |\n");
        printf("| 3. Excluir Amigo                             |\n");
        printf("| 4. Voltar                                    |\n");
        printf("+----------------------------------------------+\n\n");

        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        switch (op)
        {
        default:
            op = -1;
            mensagemErro(op);
        case 1:
            incluiAmigo();
            return;
        case 2:
            editaAmigo();
            return;
        case 3:
            excluiAmigo();
            return;
        case 4:
            return;
        }
    }
}
void menuLocal()

{

    limparTela();
    int op = 0;
    while (op != 4)
    {

        limparTela();
        printf("+---------------------------------------------+\n");
        printf("|                 MENU DE LOCAIS              |\n");
        printf("+---------------------------------------------+\n");
        printf("| 1. Adicionar Local                          |\n");
        printf("| 2. Editar Local                             |\n");
        printf("| 3. Excluir Local                            |\n");
        printf("| 4. Voltar                                   |\n");
        printf("+---------------------------------------------+\n");
        printf("\n");

        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        if (op > 4 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        switch (op)
        {
        case 1:
            incluiLocal();
            return;
        case 2:
            editaLocal();
            return;
        case 3:
            excluiLocal();
            return;
        case 4:
            return;
        }
    }
}
void menuCategoria()
{

    int op = 0;
    while (op != 4)
    {
        limparTela();
        printf("+----------------------------------------------+\n");
        printf("|              MENU DE CATEGORIAS              |\n");
        printf("+----------------------------------------------+\n");
        printf("| 1. Adicionar Categoria                       |\n");
        printf("| 2. Editar Categoria                          |\n");
        printf("| 3. Excluir Categoria                         |\n");
        printf("| 4. Voltar                                    |\n");
        printf("+----------------------------------------------+\n");
        printf("\n");

        printf("Insira sua opcao: ");
        scanf("%d", &op);

        switch (op)
        {
        default:
            op = -1;
            mensagemErro(op);
        case 1:
            incluiCategoria();
            return;
        case 2:
            editaCategoria();
            return;
        case 3:
            excluiCat();
            return;
        case 4:
            return;
        }
    }
}
void menuEncontro()
{

    limparTela();
    printf("+----------------------------------------------+\n");
    printf("|                MENU DE ENCONTROS             |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Adicionar Encontro                        |\n");
    printf("| 2. Editar Encontro                           |\n");
    printf("| 3. Excluir Encontro                          |\n");
    printf("| 4. Voltar                                    |\n");
    printf("+----------------------------------------------+\n");
    printf("\n");

    int op = 0;
    printf("Insira sua opcao:\n");
    scanf("%d", &op);

    switch (op)
    {
    default:
        op = -1;
        mensagemErro(op);
    case 1:
        incluiEncontro();
        break;
    case 2:
        editaEncontro();
        break;
    case 3:
        excluiEncontro();
        break;
    case 4:
        break;
    }
}
void listaMenu()
{

    limparTela();
    printf("+----------------------------------------------+\n");
    printf("|                 MENU DE LISTAS               |\n");
    printf("+----------------------------------------------+\n");
    printf("| 1. Listar amigos                             |\n");
    printf("| 2. Listar locais                             |\n");
    printf("| 3. Listar categorias                         |\n");
    printf("| 4. Listar encontros                          |\n");
    printf("| 5. Relatorio de Encontros por Categoria      |\n");
    printf("| 6. Voltar                                    |\n");
    printf("+----------------------------------------------+\n");
    printf("\n");

    int op = 0;
    printf("Insira sua opcao:\n");
    scanf("%d", &op);

    switch (op)
    {
    default:
        op = -1;
        mensagemErro(op);
    case 1:
        listaAmigo();
        return;
    case 2:
        listaLocal();
        return;
    case 3:
        listaCat();
        return;
    case 4:
        listaEnc();
        return;
    case 5:
        relaCat();
        return;
    case 6:
        return;
    }
}
SEncontro menuEditaAmigoEncontro(int numenc, SEncontro e){
    int op = 0, amigop = 0;
    char opc;
    int saida = 1;

    while (saida)
    {
        limparTela();
        printf("+----------------------------------------------+\n");
        printf("|                 ENCONTRO [ %02d ]              |\n", numenc + 1);
        printf("+----------------------------------------------+\n");
        printf("| 1. Adicionar Amigo                           |\n");
        printf("| 2. Remover Amigo                             |\n");
        printf("| 3. Voltar                                    |\n");
        printf("+----------------------------------------------+\n");
        printf("\n");

        flushs();
        scanf("%d", &op);
        flushs();

        printf("\n");
        switch (op)
        {
        case 1:
            while (saida)
            {
                limparTela();

                if (e.enumamigos == Namigo)
                {
                    printf("nao ha mais amigos a adicionar!\n");
                    saida = 0;
                }
                else
                {

                    listaNomesAmigo();
                    printf("| %02d. Voltar                                        |\n", Namigo + 1);
                    printf("+---------------------------------------------------+\n");
                    printf("\nInsira amigo para adicionar ao encontro: ");
                    scanf("%d", &op);

                    if (op == Namigo + 1)
                    {
                        return e;
                    }
                    if (op <= 0 || op > Namigo + 1)
                    {
                        mensagemErro(-1);
                    }
                    else
                    {
                        int amigoDuplicado = 0;

                        for (int i = 0; i < e.enumamigos; i++)
                        {
                            if (strcmp(e.amigoencontro[i], GAmigo[op - 1].nome) == 0)
                            {
                                amigoDuplicado = 1;
                                break;
                            }
                        }

                        if (amigoDuplicado)
                        {
                            printf("\nEsse amigo ja foi adicionado ao encontro.\n");
                            printf("Selecione outro amigo.\n");
                            pause();
                        }

                        else
                        {
                            e.amigoencontro = (char **)realloc(e.amigoencontro, (e.enumamigos + 1) * sizeof(char *));
                            if (e.amigoencontro == NULL)
                            {
                                mensagemErro(-4);
                                break;
                            }

                            e.amigoencontro[e.enumamigos] = (char *)malloc(strlen(GAmigo[op - 1].nome) + 1);
                            if (e.amigoencontro[e.enumamigos] == NULL)
                            {
                                mensagemErro(-4);
                                break;
                            }

                            strcpy(e.amigoencontro[e.enumamigos], GAmigo[op - 1].nome);
                            e.enumamigos++;

                            printf("\nAmigo adicionado no encontro!\n");

                            printf("Selecionar mais um amigo?\n1. Sim\n2. Nao\n");
                            scanf("%d", &op);

                            if (op != 1)
                            {
                                saida = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;

        case 2:
            while (saida)
            {
                limparTela();

                if (e.enumamigos == 1)
                {
                    printf("Nao e possivel remover amigo do encontro. Existe apenas 1 amigo nesse encontro.\n");
                    return e;
                }
                else
                {
                    listaAmigosDoEncontro(e);
                    printf("| %02d. Voltar                                        |\n", e.enumamigos + 1);
                    printf("+---------------------------------------------------+\n");
                    printf("\nInsira amigo para remover do encontro: ");
                    scanf("%d", &amigop);

                    if (amigop <= 0 || amigop > e.enumamigos + 1)
                    {
                        mensagemErro(-1);
                    }
                    else if (op == e.enumamigos + 1)
                    {
                        return e;
                    }
                    else
                    {
                        limparTela();
                        printf("\nDeseja realmente remover [ %s ]? (S/N)\n", e.amigoencontro[amigop - 1]);
                        scanf(" %c", &opc);

                        if (opc == 'N' || opc == 'n')
                        {
                            printf("Voce escolheu [N]; Voltando...\n");
                            pause();
                            break;
                        }
                        else if (opc == 'S' || opc == 's')
                        {
                            free(e.amigoencontro[amigop - 1]);

                            for (int i = amigop - 1; i < e.enumamigos - 1; i++)
                            {
                                e.amigoencontro[i] = e.amigoencontro[i + 1];
                            }

                            e.enumamigos--;

                            if (e.enumamigos == 0)
                            {
                                free(e.amigoencontro);
                                e.amigoencontro = NULL;
                            }
                            else
                            {
                                e.amigoencontro = (char **)realloc(e.amigoencontro, e.enumamigos * sizeof(char *));
                            }

                            printf("Exclusao bem sucedida!\n");
                            saida = 0;
                            break;
                        }
                        else
                        {
                            printf("Opcao invalida. Por favor, escolha 'S' para Sim ou 'N' para Nao.\n");
                        }
                    }
                }
            }
            break;

        case 3:
            saida = 0;
            break;
        }
    }
    return e;
}

// A R Q U I V O
void recuperaDado()
{
    recuperaAmigo();
    recuperaLocal();
    recuperaCat();
    recuperaEncontro();
}
void recuperaAmigo()
{
    int i, sep = 0;
    char str[200], c;

    FILE *pArq;
    pArq = fopen("amigos.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '#'))
            {
                str[i] = c;
                i++;
            }
            else if (c == '#' || c == '\n')
            {

                str[i] = '\0';
                i = 0;

                // nome
                if (sep == 0)
                {
                    if (Namigo == 0)
                    {
                        GAmigo = (SAmigo *)malloc(1 * sizeof(SAmigo));
                    }
                    else
                    {
                        GAmigo = (SAmigo *)realloc(GAmigo, (Namigo + 1) * sizeof(SAmigo));
                    }

                    GAmigo[Namigo].nome = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].nome, str);
                }
                else if (sep == 1)
                { // apelido
                    GAmigo[Namigo].apelido = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].apelido, str);
                }
                else if (sep == 2)
                { // telefone
                    GAmigo[Namigo].telefone = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].telefone, str);
                }
                else if (sep == 3)
                { // email
                    GAmigo[Namigo].email = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GAmigo[Namigo].email, str);
                }
                else if (sep == 4)
                { // dia nasc
                    GAmigo[Namigo].datanasc.dia = atoi(str);
                }
                else if (sep == 5)
                { // mes nasc
                    GAmigo[Namigo].datanasc.mes = atoi(str);
                }
                else if (sep == 6)
                { // ano nasc
                    GAmigo[Namigo].datanasc.ano = atoi(str);
                }
                sep++;

                if (c == '\n')
                {
                    Namigo++;
                    sep = 0;
                }
            }
        }
    }
    fclose(pArq);
}
void recuperaLocal()
{
    int i, sep = 0;
    char str[200], c;

    FILE *pArq;
    pArq = fopen("locais.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '#'))
            {
                str[i++] = c;
            }
            else if (c == '#' || c == '\n')
            {

                str[i] = '\0';
                i = 0;

                if (sep == 0)
                { // nome
                    if (Nlocal == 0)
                    {
                        GLocal = (SLocal *)malloc(1 * sizeof(SLocal));
                    }
                    else
                    {
                        GLocal = (SLocal *)realloc(GLocal, (Nlocal + 1) * sizeof(SLocal));
                    }

                    GLocal[Nlocal].nomelocal = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].nomelocal, str);
                    sep++;
                }
                else if (sep == 1)
                { // bairro
                    GLocal[Nlocal].local.bairro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.bairro, str);
                    sep++;
                }
                else if (sep == 2)
                { // cidade
                    GLocal[Nlocal].local.cidade = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.cidade, str);
                    sep++;
                }
                else if (sep == 3)
                { // estado
                    GLocal[Nlocal].local.estado = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.estado, str);
                    sep++;
                }
                else if (sep == 4)
                { // logradouro
                    GLocal[Nlocal].local.logradouro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.logradouro, str);
                    sep++;
                }
                else if (sep == 5)
                { // num
                    GLocal[Nlocal].local.num = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GLocal[Nlocal].local.num, str);
                    sep++;
                }

                if (c == '\n')
                {
                    Nlocal++; // Incrementa o numero de locais após processar uma linha
                    sep = 0;  // Resetar para a próxima linha
                }
            }
        }
    }
    fclose(pArq);
}
void recuperaCat()
{
    int i;
    char str[100], c;

    FILE *pArq;
    pArq = fopen("cat.txt", "r");
    if (pArq)
    {
        i = 0;

        while ((c = fgetc(pArq)) != EOF)

        {

            if ((c != '\n') && (c != '#') && (c != EOF))
            {
                str[i++] = c;
            }

            else if ((c == '#') || (c == '\n'))
            {
                str[i] = '\0';
                i = 0;

                if (c == '#') // nome
                {
                    if (NCat == 0)
                    {
                        GCategoria = (SCategoria *)malloc(1 * sizeof(SCategoria));
                    }
                    else
                    {
                        GCategoria = (SCategoria *)realloc(GCategoria, (NCat + 1) * sizeof(SCategoria));
                    }

                    GCategoria[NCat].nomecat = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GCategoria[NCat].nomecat, str);
                }
                else if (c == '\n')
                {
                    NCat++;
                }
            }
        }
    }
    fclose(pArq);
}
void recuperaEncontro()
{
    int i, sep = 0;
    char str[200], c;

    FILE *pArq;
    pArq = fopen("encontros.txt", "r");
    if (pArq)
    {
        i = 0;
        while ((c = fgetc(pArq)) != EOF)
        {
            if ((c != '\n') && (c != '#') && (c != '$'))
            {
                str[i++] = c;
            }
            else if (c == '#' || c == '\n' || c == '$')
            {
                str[i] = '\0';
                i = 0;

                if (sep == 0) // nome encontro eba
                {
                    if (NEncontro == 0)
                    {
                        GEncontro = (SEncontro *)malloc(1 * sizeof(SEncontro));
                    }
                    else
                    {
                        GEncontro = (SEncontro *)realloc(GEncontro, (NEncontro + 1) * sizeof(SEncontro));
                    }

                    GEncontro[NEncontro].nomeencontro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GEncontro[NEncontro].nomeencontro, str);
                    GEncontro[NEncontro].enumamigos = 0;
                }

                if (sep == 1 && c != '$')
                {
                    sep = 2;
                }
                if ((sep == 1) && (c == '$')) // amigos
                {
                    if (GEncontro[NEncontro].enumamigos == 0)
                    {
                        GEncontro[NEncontro].amigoencontro = (char **)malloc(sizeof(char *));
                    } 
                    else
                    {
                        GEncontro[NEncontro].amigoencontro = (char **)realloc(GEncontro[NEncontro].amigoencontro, (GEncontro[NEncontro].enumamigos + 1) * sizeof(char *));
                    }

                    GEncontro[NEncontro].amigoencontro[GEncontro[NEncontro].enumamigos] = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GEncontro[NEncontro].amigoencontro[GEncontro[NEncontro].enumamigos], str);
                    GEncontro[NEncontro].enumamigos++;
                    sep = 0;
                }

                else if (sep == 2) // local encontro
                {
                    GEncontro[NEncontro].localencontro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GEncontro[NEncontro].localencontro, str);
                }
                else if (sep == 3) // dia
                {
                    GEncontro[NEncontro].dataencontro.dia = atoi(str);
                }
                else if (sep == 4) // mes
                {
                    GEncontro[NEncontro].dataencontro.mes = atoi(str);
                }
                else if (sep == 5) // ano
                {
                    GEncontro[NEncontro].dataencontro.ano = atoi(str);
                }
                else if (sep == 6) // cat
                {
                    GEncontro[NEncontro].categoriaencontro = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GEncontro[NEncontro].categoriaencontro, str);
                }
                else if (sep == 7) // hora
                {
                    GEncontro[NEncontro].horaencontro.hora = atoi(str);
                }
                else if (sep == 8) // min
                {
                    GEncontro[NEncontro].horaencontro.minuto = atoi(str);
                }
                else if (sep == 9) // descr
                {
                    GEncontro[NEncontro].descricao = (char *)malloc((strlen(str) + 1) * sizeof(char));
                    strcpy(GEncontro[NEncontro].descricao, str);
                }

                sep++;

                if (c == '\n')
                {
                    NEncontro++; // adiciona o numero de locais após processar uma linha
                    sep = 0;     // reseta para a próxima linha
                }
            }
        }
        fclose(pArq);
    }
}

void salvaDado()
{
    salvaEncontro();
    salvaAmigo();
    salvaLocal();
    salvaCat();
}
void salvaAmigo()
{
    FILE *pArq;

    pArq = fopen("amigos.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informacões.\n");
        exit(0);
    }

    for (int i = 0; i < Namigo; i++)
    {
        fprintf(pArq, "%s#", GAmigo[i].nome);
        fprintf(pArq, "%s#", GAmigo[i].apelido);
        fprintf(pArq, "%s#", GAmigo[i].email);
        fprintf(pArq, "%s#", GAmigo[i].telefone);
        fprintf(pArq, "%i#", GAmigo[i].datanasc.dia);
        fprintf(pArq, "%i#", GAmigo[i].datanasc.mes);
        fprintf(pArq, "%i#", GAmigo[i].datanasc.ano);
        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void salvaLocal()
{

    FILE *pArq;

    pArq = fopen("locais.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informaceos");
        exit(0);
    }

    for (int i = 0; i < Nlocal; i++)
    {
        fprintf(pArq, "%s#", GLocal[i].nomelocal);
        fprintf(pArq, "%s#", GLocal[i].local.bairro);
        fprintf(pArq, "%s#", GLocal[i].local.cidade);
        fprintf(pArq, "%s#", GLocal[i].local.estado);
        fprintf(pArq, "%s#", GLocal[i].local.logradouro);
        fprintf(pArq, "%s#", GLocal[i].local.num);
        fprintf(pArq, "%c", '\n');
    }

    fclose(pArq);
}
void salvaCat()
{

    FILE *pArq;

    pArq = fopen("cat.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informaceos");
        exit(0);
    }

    for (int i = 0; i < NCat; i++)
    {
        fprintf(pArq, "%s#", GCategoria[i].nomecat);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}
void salvaEncontro()
{

    FILE *pArq;

    pArq = fopen("encontros.txt", "w");

    if (pArq == NULL)
    {
        printf("ERRO: Nao foi possivel salvar as informaceos");
        exit(0);
    }

    for (int i = 0; i < NEncontro; i++)
    {
        fprintf(pArq, "%s#", GEncontro[i].nomeencontro);
        for (int k = 0; k < GEncontro[i].enumamigos; k++)
        {
            fprintf(pArq, "%s$", GEncontro[i].amigoencontro[k]);
        }
        fprintf(pArq, "%s#", GEncontro[i].localencontro);
        fprintf(pArq, "%02d#", GEncontro[i].dataencontro.dia);
        fprintf(pArq, "%02d#", GEncontro[i].dataencontro.mes);
        fprintf(pArq, "%04d#", GEncontro[i].dataencontro.ano);
        fprintf(pArq, "%s#", GEncontro[i].categoriaencontro);
        fprintf(pArq, "%02i#%02i#", GEncontro[i].horaencontro.hora, GEncontro[i].horaencontro.minuto);
        fprintf(pArq, "%s#", GEncontro[i].descricao);
        fprintf(pArq, "%c", '\n');
    }
    fclose(pArq);
}

void limpaDado()
{
    limpaAmigo();
    limpaLocal();
    limpaCat();
    limpaEncontro();
}
void limpaAmigo()
{
    if (Namigo == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < Namigo; i++)
        {
            free(GAmigo[i].nome);
            free(GAmigo[i].apelido);
            free(GAmigo[i].email);
            free(GAmigo[i].telefone);
        }

        free(GAmigo);
    }
}
void limpaCat()
{
    if (NCat == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < NCat; i++)
        {
            free(GCategoria[i].nomecat);
        }

        free(GCategoria);
    }
}
void limpaLocal()
{
    if (Nlocal == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < Nlocal; i++)
        {
            free(GLocal[i].nomelocal);
            free(GLocal[i].local.bairro);
            free(GLocal[i].local.cidade);
            free(GLocal[i].local.estado);
            free(GLocal[i].local.logradouro);
            free(GLocal[i].local.num);
        }

        free(GLocal);
    }
}
void limpaEncontro()
{
    if (NEncontro == 0)
    {
        return;
    }

    else
    {
        for (int i = 0; i < NEncontro; i++)
        {
            free(GEncontro[i].nomeencontro);
            free(GEncontro[i].localencontro);
            free(GEncontro[i].categoriaencontro);
            free(GEncontro[i].descricao);
        }

        free(GEncontro);
    }
}

// I M P R E S S O R A S   &   L I S T A S
void imprimeEncontro(SEncontro e, int enc)
{
    printf("+--------------------------------------------------+\n");
    printf("|                   Encontro %02d                    |\n", enc + 1);
    printf("+--------------------------------------------------+\n");
    printf("| Nome: %-42s |\n", e.nomeencontro);
    printf("+--------------------------------------------------+\n");
    printf("| Amigos no encontro: %-28d |\n", e.enumamigos);
    if (e.enumamigos > 0)
    {
        for (int i = 0; i < e.enumamigos; i++)
        {
            printf("| %02d. %-45s|\n", i + 1, e.amigoencontro[i]);
        }
    }
    printf("+--------------------------------------------------+\n");

    printf("| Local: %-41s |\n", e.localencontro);
    printf("| Categoria: %-37s |\n", e.categoriaencontro);
    printf("| Data: [ %02d / %02d / %04d ]                         |\n", e.dataencontro.dia, e.dataencontro.mes, e.dataencontro.ano);
    printf("| Hora: [%02i : %02i]                                  |\n", e.horaencontro.hora, e.horaencontro.minuto);
    printf("| Desc: %-43s|\n", e.descricao);
    printf("+--------------------------------------------------+\n");
}
void imprimeAmigo(SAmigo a, int num)
{
    printf("+--------------------------------------------------+\n");
    printf("|                     Amigo [%02d]                   |\n", num + 1);
    printf("+--------------------------------------------------+\n");
    printf("| Nome: %-42s |\n", a.nome);
    printf("| Apelido: %-39s |\n", a.apelido);
    printf("| Telefone: %-38s |\n", a.telefone);
    printf("| E-Mail: %-40s |\n", a.email);
    printf("| Data de Nascimento: %02d / %02d / %04d               |\n", a.datanasc.dia, a.datanasc.mes, a.datanasc.ano);
    printf("+--------------------------------------------------+\n");
}
void imprimeLocal(SLocal a, int num)
{
    printf("+--------------------------------------------------+\n");
    printf("|                   Local [%d]                      |\n", num + 1);
    printf("+--------------------------------------------------+\n");
    printf("| Nome do Local: %-33s |\n", a.nomelocal);
    printf("| Bairro: %-40s |\n", a.local.bairro);
    printf("| Cidade: %-40s |\n", a.local.cidade);
    printf("| Estado: %-40s |\n", a.local.estado);
    printf("| Logradouro: %-36s |\n", a.local.logradouro);
    printf("| Numero: %-40s |\n", a.local.num);
    printf("+--------------------------------------------------+\n");
}
void imprimeCategoria(SCategoria c, int num)
{
    printf("+--------------------------------------------------+\n");
    printf("| %02d. %-45s|\n", num + 1, c.nomecat);
    printf("+--------------------------------------------------+\n");
}

void listaNomesEncontros()
{
    printf("+---------------------------------------------------+\n");
    printf("|                  Lista de Encontros               |\n");
    printf("+---------------------------------------------------+\n");

    for (int i = 0; i < NEncontro; i++)
    {
        printf("| %02d. %-46s|\n", i + 1, GEncontro[i].nomeencontro);
    }

    printf("+---------------------------------------------------+\n");
}
void listaNomesAmigo()
{
    if (Namigo < 1)
    {
        printf("nao existe nada adicionado! adicione!!");
        return;
    }

    printf("+---------------------------------------------------+\n");
    printf("|                      AMIGOS                       |\n");
    printf("+---------------------------------------------------+\n");

    for (int i = 0; i < Namigo; i++)
    {
        printf("| %02d. %-45s |\n", i + 1, GAmigo[i].nome);
    }

    printf("+---------------------------------------------------+\n");
}
void listaNomesLocal()
{
    printf("+----------------------------------------------------+\n");
    printf("|                    Lista de Locais                 |\n");
    printf("+----------------------------------------------------+\n");

    for (int i = 0; i < Nlocal; i++)
    {
        printf("| %02d. %-46s |\n", i + 1, GLocal[i].nomelocal);
    }

    printf("+----------------------------------------------------+\n");
}
void listaNomesCategoria()
{
    printf("+---------------------------------------------------+\n");
    printf("|                 Lista de Categorias               |\n");
    printf("+---------------------------------------------------+\n");

    for (int i = 0; i < NCat; i++)
    {
        printf("| %02d.  %-44s |\n", i + 1, GCategoria[i].nomecat);
    }

    printf("+---------------------------------------------------+\n");
}
void listaAmigo()
{
    int op;
    if (Namigo < 1)
    {
        mensagemErro(-7);
        return;
    }
    else if (Namigo == 1)
    {
        limparTela();
        imprimeAmigo(GAmigo[0], 0);
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodosAmigos();
        flushs();
    }
    else
    {
        listaNomesAmigo();
        printf("\nInsira sua opcao: ");
        scanf("%d", &op);
        op--;
        limparTela();
        imprimeAmigo(GAmigo[op], op);
        flushs();
    }
    pause();
    return;
}
void listaLocal()
{
    int op;
    if (Nlocal < 1)
    {
        mensagemErro(-8);
        return;
    }
    else if (Nlocal == 1)
    {
        limparTela();
        imprimeLocal(GLocal[0], 0);
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodosLocais();
        flushs();
    }
    else
    {
        listaNomesLocal();
        printf("\nInsira sua opcao: ");
        scanf("%d", &op);
        op--;
        limparTela();
        imprimeLocal(GLocal[op], op);
        flushs();
    }
    pause();
    return;
}
void listaCat()
{
    int op;
    if (NCat < 1)
    {
        mensagemErro(-9);
        return;
    }

    else if (NCat == 1)
    {
        limparTela();
        imprimeCategoria(GCategoria[0], 0);
        pause();
        return;
    }
    if (TodosOuUmLista() == 1)
    {
        listaNomesCategoria();
        flushs();
    }

    else
    {
        listaNomesCategoria();
        printf("\nInsira sua opcao: ");
        scanf("%d", &op);
        op--;
        limparTela();
        imprimeCategoria(GCategoria[op], op);
        flushs();
    }

    pause();

    return;
}
void listaEnc()
{
    int op;
    if (NEncontro < 1)
    {
        mensagemErro(-10);
        return;
    }

    else if (NEncontro == 1)
    {
        limparTela();
        imprimeEncontro(GEncontro[0], 0);
        pause();
        return;
    }

    if (TodosOuUmLista() == 1)
    {
        listaTodosEncontros();
        flushs();
    }

    else
    {
        listaNomesEncontros();
        printf("\nInsira sua opcao: \n");
        scanf("%d", &op);
        op--;
        limparTela();
        imprimeEncontro(GEncontro[op], op);
        flushs();
    }

    pause();

    return;
}

void listaTodosEncontros()
{
    limparTela();
    if (NEncontro < 1)
    {
        printf("nao existem encontros! adicione um!\n");
    }
    else
    {
        for (int i = 0; i < NEncontro; i++)
        {
            imprimeEncontro(GEncontro[i], i);
            printf("\n");
        }
    }
}
void listaAmigosDoEncontro(SEncontro e)
{
    printf("+---------------------------------------------------+\n");
    printf("|             Lista de Amigos do Encontro           |\n");
    printf("+---------------------------------------------------+\n");
    for (int i = 0; i < e.enumamigos; i++)
    {
        printf("| %02d.  %-43s  |\n", i + 1, e.amigoencontro[i]);
    }
    printf("+---------------------------------------------------+\n\n");
}

void listaTodosAmigos()
{
    limparTela();
    if (Namigo < 1)
    {
        printf("Nao existem amigos! adicione um amigo!\n");
    }
    else
    {
        for (int i = 0; i < Namigo; i++)
        {
            imprimeAmigo(GAmigo[i], i);
            printf("\n");
        }
    }
}
void listaTodosLocais()
{
    limparTela();
    if (Nlocal < 1)
    {
        printf("+--------------------------------------------------+\n");
        printf("|               Não existem locais!                |\n");
        printf("|               Adicione um local!                 |\n");
        printf("+--------------------------------------------------+\n");
    }
    else
    {
        for (int i = 0; i < Nlocal; i++)
        {
            imprimeLocal(GLocal[i], i);
            printf("\n");
        }
    }
}
void listaTodasCategorias()
{
    limparTela();
    if (NCat < 1)
    {
        printf("nao existem cateogiras! adicione!\n");
    }
    else
    {
        for (int i = 0; i < NCat; i++)
        {
            imprimeCategoria(GCategoria[i], i);
        }

        printf("\n");
    }
}

void relaCat()
{
    int cont[NCat];
    int indices[NCat];

    if (NEncontro < 1)
    {
        mensagemErro(-10);
        return;
    }

    limparTela();
    printf("Relatorio por categoria:\n\n");

    for (int i = 0; i < NCat; i++)
    {
        cont[i] = 0;
        indices[i] = i;
    }

    for (int i = 0; i < NCat; i++)
    {
        for (int k = 0; k < NEncontro; k++)
        {
            if (strcmp(GCategoria[i].nomecat, GEncontro[k].categoriaencontro) == 0)
            {
                cont[i]++;
            }
        }
    }

    for (int i = 0; i < NCat - 1; i++)
    {
        for (int j = i + 1; j < NCat; j++)
        {
            if (cont[indices[i]] < cont[indices[j]])
            {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    } // ordena sem alterar a ordem do meu gcategoria rs

    printf("+========================================+\n");
    printf("| Num  | Categoria            |   Enc    |\n");
    printf("+========================================+\n");

    for (int i = 0; i < NCat; i++)
    {
        int idx = indices[i];
        printf("| %-4d | %-20s |    %-6d|\n", i + 1, GCategoria[idx].nomecat, cont[idx]);
    }

    printf("+========================================+\n\n");

    pause();
}

// C A D A S T R O
void incluiEncontro()
{
    limparTela();
    if (Namigo == 0 || Nlocal == 0 || NCat == 0)
    {
        printf("Voce ainda nao possui ");

        if (Namigo == 0 && Nlocal == 0 && NCat == 0)
        {
            printf("nenhum amigo, nenhum local e nenhuma categoria adicionados.\n");
        }
        else
        {
            if (Namigo == 0)
            {
                printf("nenhum amigo adicionado");
            }

            if (Nlocal == 0)
            {
                if (Namigo == 0)
                {
                    printf(", "); // Adiciona uma virgula entre os itens se ja houver algo antes
                }
                printf("nenhum local adicionado");
            }

            if (NCat == 0)
            {
                if (Namigo == 0 || Nlocal == 0)
                {
                    printf(" e "); // Adiciona 'e' entre os itens, quando necessario
                }
                printf("nenhuma categoria adicionada");
            }

            printf(".\n");
        }

        printf("\nVolte ao menu e crie as opcões necessarias!\n");
        pause();
    }

    else
    {

        if (NEncontro == 0)
        {
            GEncontro = (SEncontro *)malloc(1 * sizeof(SEncontro));
        }
        else
        {
            GEncontro = (SEncontro *)realloc(GEncontro, (NEncontro + 1) * sizeof(SEncontro));
        }

        GEncontro[NEncontro] = cadastraEncontro(NEncontro);
        NEncontro++;
    }
}
SEncontro cadastraEncontro(int num)
{
    SEncontro e;
    char strAux[100];

    int erro = 0, op = 0;

    limparTela();
    printf("-- Adicionando Encontro --\n\n");
    while (erro != 1)
    {
        printf("Digite o nome do encontro: ");
        flushs();
        gets(strAux);
        flushs();
        e.nomeencontro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(e.nomeencontro, strAux);
        erro = 1;
    }

    erro = 0;

    // amg no encontro
    e.enumamigos = 0;
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        listaNomesAmigo();
        if (Namigo > 1)
        {
            printf("| %02d. Todos                                         |\n", Namigo + 1);
            printf("+---------------------------------------------------+\n");
        }
        printf("\nQual amigo deseja adicionar no encontro?\n");
        printf("Insira sua opcao: ");
        scanf("%d", &op);

        if (op < 1 || ((op > Namigo && Namigo == 1) || (op > Namigo + 1)))
        {
            mensagemErro(-1);
            erro = 0;
            break;
        }
        else if (op == Namigo + 1)
        {
            for (int s = 0; s < Namigo; s++)
            {
                if (e.enumamigos == 0)
                {
                    e.amigoencontro = (char **)malloc(sizeof(char *));
                }
                else
                {
                    e.amigoencontro = (char **)realloc(e.amigoencontro, (e.enumamigos + 1) * sizeof(char *));
                }

                if (e.amigoencontro == NULL)
                {
                    mensagemErro(-4);
                    break;
                }

                e.amigoencontro[e.enumamigos] = (char *)malloc(strlen(GAmigo[s].nome) + 1);

                if (e.amigoencontro[e.enumamigos] == NULL)
                {
                    mensagemErro(-4);
                    break;
                }

                strcpy(e.amigoencontro[e.enumamigos], GAmigo[s].nome);
                e.enumamigos++;
            }
            printf("\nAmigos adicionados ao encontro!\n");
            erro = 1;
            pause();
        }
        else
        {
            int amigoDuplicado = 0;

            for (int i = 0; i < e.enumamigos; i++)
            {
                if (strcmp(e.amigoencontro[i], GAmigo[op - 1].nome) == 0)
                {
                    amigoDuplicado = 1;
                    break;
                }
            }

            if (amigoDuplicado)
            {
                printf("\nEsse amigo ja foi adicionado ao encontro.\n");
                printf("Selecione outro amigo.\n\n");
                pause();
            }

            else
            {
                if (e.enumamigos == 0)
                {
                    e.amigoencontro = (char **)malloc(sizeof(char *));
                }
                else
                {
                    e.amigoencontro = (char **)realloc(e.amigoencontro, (e.enumamigos + 1) * sizeof(char *));
                }

                if (e.amigoencontro == NULL)
                {
                    mensagemErro(-4);
                    break;
                }

                e.amigoencontro[e.enumamigos] = (char *)malloc(strlen(GAmigo[op - 1].nome) + 1);

                if (e.amigoencontro[e.enumamigos] == NULL)
                {
                    mensagemErro(-4);
                    break;
                }

                strcpy(e.amigoencontro[e.enumamigos], GAmigo[op - 1].nome);
                e.enumamigos++;

                printf("\nAmigo adicionado no encontro!\n");
                pause();
                if (Namigo > 1 && e.enumamigos != Namigo)
                {
                    limparTela();
                    printf("+--------------------------------------------------+\n");
                    printf("| Deseja adicionar mais um amigo?                  |\n");
                    printf("+--------------------------------------------------+\n");
                    printf("| 1. Sim                                           |\n");
                    printf("| 2. Nao                                           |\n");
                    printf("+--------------------------------------------------+\n");
                    printf("\n");
                    scanf("%d", &op);

                    if (op == 1)
                    {
                        erro = 0;
                    }
                    else if (op == 2)
                    {
                        erro = 1;
                    }
                    else
                    {
                        mensagemErro(-1);
                    }
                }
                else
                {
                    limparTela();
                    printf("Nao tem mais amigos para adicionar!\n");
                    pause();
                    erro = 1;
                }
            }
        }
    }
    erro = 0;
    // Dia do encontro
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        printf("Data do Encontro (DD MM AAAA):  ");
        scanf("%02d%02d%04d", &e.dataencontro.dia, &e.dataencontro.mes, &e.dataencontro.ano);
        flushs();

        erro = validaData(e.dataencontro.dia, e.dataencontro.mes, e.dataencontro.ano);

        if (erro != 1)
        {
            mensagemErro(erro);
        }
    }
    erro = 0;

    // loc do encontro
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        listaNomesLocal();
        printf("Qual e o local do encontro?\n");
        printf("Insira sua opcao: ");
        scanf("%d", &op);

        if (op <= 0 || op > Nlocal)
        {
            mensagemErro(-1);
        }
        else
        {
            e.localencontro = (char *)malloc(strlen(GLocal[op - 1].nomelocal) + 1);
            if (e.localencontro == NULL)
            {
                mensagemErro(-4);
                break;
            }
            strcpy(e.localencontro, GLocal[op - 1].nomelocal);
            erro = 1;
        }
    }
    erro = 0;

    // cat do encontro
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        listaNomesCategoria();
        printf("Qual e a categoria do encontro?\n");
        printf("Insira sua opcao: ");
        scanf("%d", &op);

        if (op <= 0 || op > NCat)
        {
            mensagemErro(-1);
        }
        else
        {
            e.categoriaencontro = (char *)malloc(strlen(GCategoria[op - 1].nomecat) + 1);
            if (e.categoriaencontro == NULL)
            {
                mensagemErro(-4);
                break;
            }
            strcpy(e.categoriaencontro, GCategoria[op - 1].nomecat);
            erro = 1;
        }
    }
    erro = 0;

    // hr do encontro
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        printf("Digite a hora do encontro em formato 24h (HH MM): ");
        scanf("%2d%2d", &e.horaencontro.hora, &e.horaencontro.minuto);

        int verificadorhora = validaHora(e.horaencontro.hora, e.horaencontro.minuto);

        if (verificadorhora == -5)
        {
            mensagemErro(-5);
        }
        else
        {
            erro = 1;
        }
    }

    erro = 0;
    // descricao do encontro
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Encontro --\n\n");
        printf("De uma breve descricao a respeito do encontro: ");
        flushs();
        gets(strAux);
        flushs();
        e.descricao = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
        strcpy(e.descricao, strAux);
        erro = 1;
    }

    limparTela();
    imprimeEncontro(e, num);
    printf("\nEncontro adicionado!\n");
    pause();
    return e;
}
void incluiAmigo()
{
    if (Namigo == 0)
    {
        GAmigo = (SAmigo *)malloc(1 * sizeof(SAmigo));
    }
    else
    {
        GAmigo = (SAmigo *)realloc(GAmigo, (Namigo + 1) * sizeof(SAmigo));
    }

    GAmigo[Namigo] = cadastraAmigo(Namigo);
    Namigo++;
}
SAmigo cadastraAmigo(int num)
{
    SAmigo a;
    char strAux[100];
    int erro = 0;

    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Amigo --\n\n");
        printf("Nome do amigo: ");
        flushs();
        gets(strAux);
        flushs();

        if (Namigo > 0)
        {
            int amigoDuplicado = 0;

            for (int i = 0; i < Namigo; i++)
            {
                if (strcmp(strAux, GAmigo[i].nome) == 0)
                {
                    amigoDuplicado = 1;
                    break;
                }
            }

            if (amigoDuplicado)
            {
                mensagemErro(-3);
                erro = 2;
            }
            else
            {
                a.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
                if (a.nome == NULL)
                {
                    mensagemErro(-4);
                    break;
                }
                strcpy(a.nome, strAux);
                erro = 1;
            }
        }
        else
        {
            a.nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));

            if (a.nome == NULL)
            {
                mensagemErro(-4);
                break;
            }
            strcpy(a.nome, strAux);
            erro = 1;
        }
    }

    limparTela();
    printf("-- Adicionando Amigo --\n\n");
    printf("Apelido do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.apelido, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Amigo --\n\n");
    printf("Telefone do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.telefone, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Amigo --\n\n");
    printf("Email do amigo: ");
    flushs();
    gets(strAux);
    flushs();
    a.email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(a.email, strAux);
    flushs();

    erro = 0;
    while (erro != 1)
    {
        limparTela();
        printf("-- Adicionando Amigo --\n\n");
        printf("Data de nascimento do amigo (DD MM AAAA):  ");
        scanf("%02d%02d%04d", &a.datanasc.dia, &a.datanasc.mes, &a.datanasc.ano);
        flushs();

        erro = validaData(a.datanasc.dia, a.datanasc.mes, a.datanasc.ano);

        if (erro != 1)
        {
            mensagemErro(erro);
        }
    }

    limparTela();
    imprimeAmigo(a, num);
    printf("Amigo adicionado!\n");
    pause();

    return a;
}
void incluiLocal()
{
    if (Nlocal == 0)
    {
        GLocal = (SLocal *)malloc(1 * sizeof(SLocal));
    }
    else
    {
        GLocal = (SLocal *)realloc(GLocal, (Nlocal + 1) * sizeof(SLocal));
    }

    GLocal[Nlocal] = cadastraLocal(Nlocal);
    Nlocal++;
}
SLocal cadastraLocal(int num)
{
    SLocal l;
    char strAux[100];
    int erro = 0;
    do
    {
        limparTela();
        printf("-- Adicionando Local --\n\n");
        printf("Nome do local: ");
        flushs();
        gets(strAux);
        flushs();

        erro = 0;

        for (int i = 0; i < Nlocal; i++)
        {
            if (strcmp(GLocal[i].nomelocal, strAux) == 0)
            {
                erro = 1;
                printf("\nLocal com este nome ja existe!\n");
                pause();
                break;
            }
        }

        if (!erro)
        {
            break;
        }

    } while (1);

    l.nomelocal = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.nomelocal, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Local --\n\n");
    printf("Bairro do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.bairro, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Local --\n\n");
    printf("Cidade do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.cidade, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Local --\n\n");
    printf("Estado do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.estado, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Local --\n\n");
    printf("Logradouro [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.logradouro, strAux);
    flushs();

    limparTela();
    printf("-- Adicionando Local --\n\n");
    printf("Numero do local [%s]: ", l.nomelocal);
    flushs();
    gets(strAux);
    flushs();
    l.local.num = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(l.local.num, strAux);
    flushs();

    limparTela();
    imprimeLocal(l, num);
    printf("Local adicionado!\n");
    pause();

    return l; // Retorna o local cadastrado
}
void incluiCategoria()
{
    if (NCat == 0)
    {
        GCategoria = (SCategoria *)malloc(1 * sizeof(SCategoria));
    }
    else
    {
        GCategoria = (SCategoria *)realloc(GCategoria, (NCat + 1) * sizeof(SCategoria));
    }

    GCategoria[NCat] = cadastraCategoria(NCat);
    NCat++;
}
SCategoria cadastraCategoria(int num)
{
    SCategoria c;
    char strAux[100];
    int erro = 1;
    while (erro)
    {

        limparTela();
        printf("-- Adicionando Categoria --\n\n");
        printf("Nome da categoria: ");
        flushs();
        gets(strAux);
        flushs();

        if (NCat > 0)
        {
            for (int i = 0; i < NCat; i++)
            {
                if (strcmp(GCategoria[i].nomecat, strAux) == 0)
                {
                    printf("\nCategoria com este nome ja existe!\n");
                    pause();
                    erro = 1;
                }
                else
                {
                    erro = 0;
                }
            }
        }
        else
        {
            erro = 0;
        }
    }
    c.nomecat = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
    strcpy(c.nomecat, strAux);
    flushs();

    limparTela();
    imprimeCategoria(c, num);
    printf("Categoria adicionada!\n");
    pause();

    return c;
}

// E D I T O R E S
void editaAmigo()
{
    int auxEdita = 1, amgencontro[NEncontro], linked = 0;

    while (auxEdita)
    {
        int op = 0;
        if (Namigo == 0)
        {
            mensagemErro(-7);
            return;
        }

        while (op < 1 || op > Namigo)
        {
            limparTela();
            listaNomesAmigo();
            printf("| %02d. Voltar                                        |\n", Namigo + 1);
            printf("+---------------------------------------------------+\n");
            printf("Escolha um amigo: ");
            scanf("%d", &op);
            if (op < 1 || op > Namigo + 1)
            {
                op = -1;
                mensagemErro(op);
            }
            else if (op == Namigo + 1)
            {
                return;
            }
            else
            {
                for (int i = 0; i < NEncontro; i++)
                {
                    for (int k = 0; k < GEncontro[i].enumamigos; k++)
                    {
                        if (strcmp(GEncontro[i].amigoencontro[k], GAmigo[op - 1].nome) == 0)
                        {
                            linked = 1;
                            amgencontro[i] = 1;
                        }
                    }
                }
            }
            if (linked)
            {
                printf("Erro! Esse amigo esta envolvido nos seguintes encontros: ");
                for (int i = 0; i < NEncontro; i++)
                {
                    if (amgencontro[i])
                    {
                        printf("[ %02d ]; ", i + 1);
                    }
                }
                printf("\nNao e possivel editar dados que estao atrelados a um encontro!\n");
                pause();
                return;
            }
        }
        limparTela();

        imprimeAmigo(GAmigo[op - 1], op - 1);

        int amigo = op;

        printf("\nO que voce deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Apelido\n");
        printf("3. Telefone\n");
        printf("4. Email\n");
        printf("5. Data Nasc\n");
        printf("6. Voltar\n");
        op = 0;
        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        if (op > 6 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 6)
        {
            limparTela();
            return;
        }
        limparTela();
        switchAmigo(op, amigo - 1);

        auxEdita = desejaAlterar();
    }

    limparTela();
}
void switchAmigo(int op, int amigo)
{
    char strAux[100];
    int opaux = 0, auxdata = 0;
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].nome);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].nome = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].nome, strAux);
            printf("Nome alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 2:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].apelido);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o apelido para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].apelido = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].apelido, strAux);
            printf("Apelido alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 3:
        printf("Alterar [ %s ] para: ", GAmigo[amigo].telefone);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o telefone para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].telefone = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].telefone, strAux);
            printf("Telefone alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 4:

        printf("Alterar [ %s ] para: ", GAmigo[amigo].email);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o email para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GAmigo[amigo].email = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GAmigo[amigo].email, strAux);
            printf("Email alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 5:
        while (opaux < 1 || opaux > 3)
        {
            limparTela();
            printf("O que deseja editar na data de nascimento?\n");
            printf("1. Dia\n2. Mes\n3. Ano\nEscolha: ");
            scanf("%d", &opaux);
            if (opaux < 1 || opaux > 3)
            {
                mensagemErro(-1);
            }
        }

        printf("Insira o novo valor: ");
        scanf("%d", &auxdata);
        if ((auxdata > 0 && auxdata <= 31 && opaux == 1) || (auxdata > 0 && auxdata <= 12 && opaux == 2) || (auxdata > 0 && auxdata <= 9999 && opaux == 3))
        {

            switch (opaux)
            {
            case 1:
                printf("Deseja realmente alterar o dia para %02d? (S/N): ", auxdata);
                break;
            case 2:
                printf("Deseja realmente alterar o mes para %02d? (S/N): ", auxdata);
                break;
            case 3:
                printf("Deseja realmente alterar o ano para %d? (S/N): ", auxdata);
                break;
            }
            flushs();
            scanf("%c", &opc);
            if (opc == 'S' || opc == 's')
            {
                switch (opaux)
                {
                case 1:
                    GAmigo[amigo].datanasc.dia = auxdata;
                    break;
                case 2:
                    GAmigo[amigo].datanasc.mes = auxdata;
                    break;
                case 3:
                    GAmigo[amigo].datanasc.ano = auxdata;
                    break;
                }
                printf("Data de nascimento alterada com sucesso!\n");
            }
            else
            {
                printf("Alteracao cancelada.\n");
            }
        }
        else
        {
            limparTela();
            printf("Valor invalido para data! [ %d ]\nRetornando...", auxdata);
        }
        break;

    case 6:
        printf("Voltando ao menu principal...\n");
        pause();
        break;

    default:
        mensagemErro(-1);
        break;
    }
    return;
}
void editaLocal()
{
    int auxEdita = 1;
    int locencontro[NEncontro], linked = 0;
    while (auxEdita)
    {
        int op = 0;
        if (Nlocal == 0)
        {
            mensagemErro(-8);
            return;
        }
        while (op < 1 || op > Nlocal)
        {

            limparTela();
            listaNomesLocal();
            printf("| %02d. Voltar                                         |\n", Nlocal + 1);
            printf("+----------------------------------------------------+\n");
            printf("\nEscolha um Local: ");
            scanf("%d", &op);
            if (op < 1 || op > Nlocal + 1)
            {
                op = -1;
                mensagemErro(op);
            }
            else if (op == Nlocal + 1)
            {
                return;
            }
            else
            {
                for (int i = 0; i < NEncontro; i++)
                {
                    if (strcmp(GEncontro[i].localencontro, GLocal[op - 1].nomelocal) == 0)
                    {
                        linked = 1;
                        locencontro[i] = 1;
                    }
                    else
                    {
                        locencontro[i] = 0;
                    }
                }
            }
            if (linked)
            {
                printf("Erro! Esse local esta envolvido nos seguintes encontros: ");
                for (int i = 0; i < NEncontro; i++)
                {
                    if (locencontro[i])
                    {
                        printf("[ %02d ]; ", i + 1);
                    }
                }
                printf("\nNao e possivel editar dados que estao atrelados a um encontro!\n");
                pause();
                return;
            }
        }

        limparTela();

        imprimeLocal(GLocal[op - 1], op - 1);

        int Local = op;

        printf("\nO que voce deseja editar?\n");
        printf("1. Nome do local\n");
        printf("2. bairro\n");
        printf("3. Cidade\n");
        printf("4. Estado\n");
        printf("5. Logradouro\n");
        printf("6. Numero\n");
        printf("7. Voltar\n");
        op = 0;
        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        if (op > 7 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 7)
        {
            limparTela();
            return;
        }
        limparTela();
        switchLocal(op, Local - 1);

        auxEdita = desejaAlterar();
    }

    limparTela();
}
void switchLocal(int op, int Local)
{
    char strAux[100];
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GLocal[Local].nomelocal);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].nomelocal = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].nomelocal, strAux);
            printf("\nNome do local alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 2:
        printf("Alterar [ %s ] para: ", GLocal[Local].local.bairro);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o bairro para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.bairro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.bairro, strAux);
            printf("bairro alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 3:
        printf("Alterar [ %s ] para: ", GLocal[Local].local.cidade);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar a cidade do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.cidade = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.cidade, strAux);
            printf("\ncidade alterada com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 4:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.estado);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o estado para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.estado = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.estado, strAux);
            printf("\nEstado alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 5:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.logradouro);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o logradouro para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.logradouro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.logradouro, strAux);
            printf("\nLogradouro alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;
    case 6:

        printf("Alterar [ %s ] para: ", GLocal[Local].local.num);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o numero do local para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GLocal[Local].local.num = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GLocal[Local].local.num, strAux);
            printf("\nNumero alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 7:

        printf("Voltando ao menu principal...\n");
        pause();
        break;

    default:
        mensagemErro(-1);
        break;
    }

    return;
}
void editaCategoria()
{
    int auxEdita = 1;
    int catencontro[NEncontro], linked = 0;
    while (auxEdita)
    {
        int op = 0;
        if (NCat == 0)
        {
            mensagemErro(-9);
            return;
        }
        while (op < 1 || op > NCat)
        {
            limparTela();

            listaNomesCategoria();
            printf("| %02d. Voltar                                        |\n", NCat + 1);
            printf("+---------------------------------------------------+\n");
            printf("Escolha um para editar: ");
            scanf("%d", &op);
            if (op < 1 || op > NCat + 1)
            {
                op = -1;
                mensagemErro(op);
            }
            else if (op == NCat + 1)
            {
                return;
            }
            else
            {
                for (int i = 0; i < NEncontro; i++)
                {
                    if (strcmp(GEncontro[i].categoriaencontro, GCategoria[op - 1].nomecat) == 0)
                    {
                        linked = 1;
                        catencontro[i] = 1;
                    }
                    else
                    {
                        catencontro[i] = 0;
                    }
                }
            }
            if (linked)
            {
                printf("Erro! Essa categoria esta envolvida nos seguintes encontros: ");
                for (int i = 0; i < NEncontro; i++)
                {
                    if (catencontro[i])
                    {
                        printf("[ %02d ]; ", i + 1);
                    }
                }
                printf("\nNao e possivel editar dados que estao atrelados a um encontro!\n");
                pause();
                return;
            }
        }

        limparTela();

        imprimeCategoria(GCategoria[op - 1], op - 1);

        int categoria = op;

        printf("\nO que voce deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Voltar\n\n");
        op = 0;

        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        if (op > 2 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 2)
        {
            limparTela();
            return;
        }

        limparTela();
        switchCat(op, categoria - 1);

        auxEdita = desejaAlterar();
    }

    limparTela();
}
void switchCat(int op, int cat)
{
    char strAux[100];
    char opc;

    switch (op)
    {
    case 1:
        printf("Alterar [ %s ] para: ", GCategoria[cat].nomecat);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar o nome da categoria para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GCategoria[cat].nomecat = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GCategoria[cat].nomecat, strAux);
            printf("\nNome alterado com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 2:
        printf("Voltando ao menu principal...\n");
        pause();
        break;

    default:
        mensagemErro(-1);
        break;
    }

    return;
}
void editaEncontro()
{
    int auxEdita = 1;

    while (auxEdita)
    {
        int op = 0;
        if (NEncontro == 0)
        {
            mensagemErro(-10);
            return;
        }

        while (op < 1 || op > NEncontro)
        {
            flushs();
            limparTela();
            listaNomesEncontros();
            printf("| %02d. Voltar                                        |\n", NEncontro + 1);
            printf("+---------------------------------------------------+\n");
            printf("Escolha um encontro para editar: ");
            scanf("%d", &op);
            flushs();
            if (op < 1 || op > NEncontro + 1)
            {
                op = -1;
                mensagemErro(op);
            }
            else if (op == NEncontro + 1)
            {
                return;
            }
        }
        limparTela();
        imprimeEncontro(GEncontro[op - 1], op - 1);

        int enc = op;

        printf("\n\nO que voce deseja editar?\n");
        printf("1. Nome\n");
        printf("2. Amigos\n");
        printf("3. Local\n");
        printf("4. Categoria\n");
        printf("5. Data\n");
        printf("6. Hora\n");
        printf("7. Descricao\n");
        printf("8. Voltar\n");
        op = 0;
        printf("Insira sua opcao:\n");
        scanf("%d", &op);

        if (op > 8 || op < 1)
        {
            op = -1;
            mensagemErro(op);
        }
        if (op == 8)
        {
            limparTela();
            return;
        }
        printf("\n\n");
        switchEncontro(op, enc - 1);

        auxEdita = desejaAlterar();
    }
}
void switchEncontro(int op, int encontro)
{
    char strAux[100];
    int duplo = 0, erro = 0, ad, am, aa, ah, amin;
    char opc;

    switch (op)
    {
    case 1: // nome
        do
        {
            printf("Alterar o nome [ %s ] para: ", GEncontro[encontro].nomeencontro);
            flushs();
            gets(strAux);
            flushs();

            if (strcmp(GEncontro[encontro].nomeencontro, strAux) == 0)
            {
                printf("\nEsse ai ja eh o mesmo nome ne querido, beleza ne\n");
            }
            else
            {
                for (int i = 0; i < NEncontro; i++)
                {
                    if (i == encontro)
                    {
                        i++;
                    }
                    if (strcmp(GEncontro[i].nomeencontro, strAux) == 0)
                    {
                        duplo = 1;
                        break;
                    }
                }

                if (duplo)
                {
                    printf("\nIsso ai ja eh de outro encontro seu bobinho.\n");
                    printf("Selecione outro nome AGORAAAAAAA.\n");
                    pause();
                }

                else
                {

                    printf("Deseja realmente alterar o nome para [ %s ]? (S/N): ", strAux);
                    flushs();
                    scanf("%c", &opc);
                    if (opc == 'S' || opc == 's')
                    {
                        GEncontro[encontro].nomeencontro = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
                        strcpy(GEncontro[encontro].nomeencontro, strAux);
                        printf("Nome alterado com sucesso!\n");
                    }
                    else
                    {
                        printf("Alteracao cancelada.\n");
                    }
                }
            }

        } while (duplo);

        break;

    case 2: // amigo

        GEncontro[encontro] = menuEditaAmigoEncontro(encontro, GEncontro[encontro]);
        break;

    case 3: // local

        if (Nlocal == 1)
        {
            limparTela();
            printf("Nao ha mais locais para alterar entre o atual!\n");
        }
        else
        {
            int erro = 0;

            while (erro != 1)
            {
                limparTela();
                listaNomesLocal();
                printf("Insira o novo local do encontro: ");
                scanf("%d", &op);

                if (op <= 0 || op > Nlocal)
                {
                    mensagemErro(-1);
                }
                else
                {
                    if (strcmp(GEncontro[encontro].localencontro, GLocal[op - 1].nomelocal) == 0)
                    {
                        printf("\nIsso ai ja eh a mesma coisa de antes neh flor, perda de tempo mesmo. . . ");
                    }
                    else
                    {

                        GEncontro[encontro].localencontro = (char *)malloc(strlen(GLocal[op - 1].nomelocal) + 1);
                        if (GEncontro[encontro].localencontro == NULL)
                        {
                            mensagemErro(-4);
                            break;
                        }
                        strcpy(GEncontro[encontro].localencontro, GLocal[op - 1].nomelocal);
                    }
                    erro = 1;
                }
            }
        }
        break;

    case 4: // categoria

        if (NCat == 1)
        {
            limparTela();
            printf("Nao ha mais cateogrias para alterar entre a atual!\n");
        }
        else
        {
            int erro = 0;

            while (erro != 1)
            {
                limparTela();
                listaNomesCategoria();
                printf("Insira a nova categoria do encontro: ");
                scanf("%d", &op);

                if (op <= 0 || op > NCat)
                {
                    mensagemErro(-1);
                }
                else
                {
                    if (strcmp(GEncontro[encontro].categoriaencontro, GCategoria[op - 1].nomecat) == 0)
                    {
                        printf("\nIsso ai ja eh a mesma coisa de antes neh flor, perda de tempo mesmo. . .");
                    }

                    else
                    {
                        GEncontro[encontro].categoriaencontro = (char *)malloc(strlen(GCategoria[op - 1].nomecat) + 1);
                        if (GEncontro[encontro].categoriaencontro == NULL)
                        {
                            mensagemErro(-4);
                            break;
                        }
                        strcpy(GEncontro[encontro].categoriaencontro, GCategoria[op - 1].nomecat);
                        printf("\nCategoria Alterada com sucesso!! :)");
                    }
                    erro = 1;
                }
            }
        }
        break;
    case 5: // data
        while (erro != 1)
        {
            limparTela();
            printf("\nData do encontro atual: [ %02d / %02d / %02d ]\n", GEncontro[encontro].dataencontro.dia, GEncontro[encontro].dataencontro.mes, GEncontro[encontro].dataencontro.ano);
            printf("Insira a nova data (DD MM AAAA): ");
            scanf("%02d %02d %4d", &ad, &am, &aa);
            erro = validaData(ad, am, aa);
            if (!erro)
            {
                mensagemErro(erro);
            }
        }
        GEncontro[encontro].dataencontro.dia = ad;
        GEncontro[encontro].dataencontro.mes = am;
        GEncontro[encontro].dataencontro.ano = aa;

        printf("\nData do encontro alterada para (%02d / %02d / %02d) com sucesso!\n", GEncontro[encontro].dataencontro.dia, GEncontro[encontro].dataencontro.mes, GEncontro[encontro].dataencontro.ano);
        break;
    case 6: // hora
        while (erro != 1)
        {
            printf("\nHora do encontro atual: [ %02d : %02d ]\n", GEncontro[encontro].horaencontro.hora, GEncontro[encontro].horaencontro.minuto);
            printf("Insira o novo horario (HH MM): ");
            scanf("%2d %2d", &ah, &amin);
            erro = validaHora(ah, amin);
            if (!erro)
            {
                mensagemErro(-5);
            }
        }
        GEncontro[encontro].horaencontro.hora = ah;
        GEncontro[encontro].horaencontro.minuto = amin;
        printf("\nHora do encontro alterada com sucesso para [ %02d : %02d ]\n", GEncontro[encontro].horaencontro.hora, GEncontro[encontro].horaencontro.minuto);
        break;

    case 7:
        printf("Alterar [ %s ]: ", GEncontro[encontro].descricao);
        flushs();
        gets(strAux);
        flushs();

        printf("Deseja realmente alterar a descricao para '%s'? (S/N): ", strAux);
        flushs();
        scanf("%c", &opc);
        if (opc == 'S' || opc == 's')
        {
            GEncontro[encontro].descricao = (char *)malloc((strlen(strAux) + 1) * sizeof(char));
            strcpy(GEncontro[encontro].descricao, strAux);
            printf("Descricao alterada com sucesso!\n");
        }
        else
        {
            printf("Alteracao cancelada.\n");
        }
        break;

    case 8:

        printf("Voltando ao menu principal...\n");
        pause();
        break;

    default:
        mensagemErro(-1);
        break;
    }
    return;
}

// L I X E I R A
void excluiAmigo()
{
    int amgencontro[NEncontro], linked = 0;
    if (Namigo < 1)
    {
        mensagemErro(-7);
        return;
    }

    int op = 0;
    while (op < 1 || op > Namigo)
    {
        limparTela();
        listaNomesAmigo();
        printf("| %02d. Voltar                                        |\n", Namigo + 1);
        printf("+---------------------------------------------------+\n");
        printf("Escolha um para EXCLUIR [ 01 - %02d ]: ", Namigo + 1);
        scanf("%d", &op);
        if (op == Namigo + 1)
        {
            return;
        }

        if (op > Namigo + 1 || op < 1)
        {
            mensagemErro(-1);
        }
        else if (NEncontro > 0)
        {
            for (int i = 0; i < NEncontro; i++)
            {
                for (int k = 0; k < GEncontro[i].enumamigos; k++)
                {
                    if (strcmp(GEncontro[i].amigoencontro[k], GAmigo[op - 1].nome) == 0)
                    {
                        linked = 1;
                        amgencontro[i] = 1;
                    }
                }
            }
        }
        if (linked)
        {
            printf("Erro! Esse amigo esta envolvido nos seguintes encontros: ");
            for (int i = 0; i < NEncontro; i++)
            {
                if (amgencontro[i])
                {
                    printf("[ %02d ]; ", i + 1);
                }
            }
            printf("\nRemova antes de fazer qualquer coisa!\n");
            pause();
            return;
        }
    }

    int amigo = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa acao sera IRREVERSiVEL. (S/N)\n", GAmigo[amigo].nome);
        scanf(" %c", &opc);
        if (opc == 'N' || opc == 'n')
        {

            limparTela();
            printf("Voce escolheu [N]; Voltando para menu principal. . . ");
            printf("\n");
            pause();
            return;
        }
        else if (opc == 'S' || opc == 's')
        {
            if (Namigo == 1)
            {
                free(GAmigo);
            }
            else
            {
                for (int i = amigo; i < Namigo - 1; i++)
                {
                    GAmigo[i] = GAmigo[i + 1];
                }
                GAmigo = (SAmigo *)realloc(GAmigo, (Namigo - 1) * sizeof(SAmigo));
            }

            Namigo--;
            printf("Exclusao bem sucedida!\n");
            pause();
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}
void excluiLocal()
{

    int locencontro[NEncontro], linked = 0;
    if (Nlocal < 1)
    {
        mensagemErro(-8);
        return;
    }

    int op = 0;
    while (op < 1 || op > Nlocal)
    {
        limparTela();
        listaNomesLocal();
        printf("| %02d. Voltar                                         |\n", Nlocal + 1);
        printf("+----------------------------------------------------+\n");
        printf("Escolha um para EXCLUIR [ 01 - %02d ]: ", Nlocal + 1);
        scanf("%d", &op);
        if (op == Nlocal + 1)
        {
            return;
        }

        if (op > Nlocal || op < 1)
        {
            mensagemErro(-1);
        }
        else if (NEncontro > 0)
        {
            for (int i = 0; i < NEncontro; i++)
            {
                if (strcmp(GEncontro[i].localencontro, GLocal[op - 1].nomelocal) == 0)
                {
                    linked = 1;
                    locencontro[i] = 1;
                }
                else
                {
                    locencontro[i] = 0;
                }
            }
        }
        if (linked)
        {
            printf("Erro! Esse local esta envolvido nos seguintes encontros: ");
            for (int i = 0; i < NEncontro; i++)
            {
                if (locencontro[i])
                {
                    printf("[ %02d ]; ", i + 1);
                }
            }
            printf("\nNao e possivel editar dados que estao atrelados a um encontro!\n");
            pause();
            return;
        }
    }

    int local = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa acao sera IRREVERSiVEL.\n\n(S/N)", GLocal[local].nomelocal);
        scanf(" %c", &opc);
        if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Voce escolheu [S]; Excluindo. . . ");

            if (Nlocal == 1)
            {
                free(GLocal);
            }
            else
            {

                for (int i = local; i < Nlocal - 1; i++)
                {
                    GLocal[i] = GLocal[i + 1];
                }

                GLocal = (SLocal *)realloc(GLocal, (Nlocal - 1) * sizeof(SLocal));
            }

            Nlocal--;

            limparTela();
            printf("exclusao bem sucedida!\n");
            pause();
            return;
        }

        else if (opc == 'N' || opc == 'n')
        {
            limparTela();
            printf("Voce escolheu [N]; Voltando para menu principal. . . ");
            printf("\n");
            pause();
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}
void excluiCat()
{
    int catencontro[NEncontro], linked = 0;
    if (NCat < 1)
    {
        mensagemErro(-9);
        return;
    }

    int op = 0;
    while (op < 1 || op > NCat)
    {
        limparTela();
        listaNomesCategoria();
        printf("| %02d. Voltar                                        |\n", NCat + 1);
        printf("+---------------------------------------------------+\n");
        printf("Escolha um para EXCLUIR [ 01 - %02d ]: ", NCat + 1);
        scanf("%d", &op);
        if (op == NCat + 1)
        {
            return;
        }
        if (op > NCat || op < 1)
        {
            mensagemErro(-1);
        }
        else if (NEncontro > 0)
        {
            for (int i = 0; i < NEncontro; i++)
            {
                if (strcmp(GEncontro[i].categoriaencontro, GCategoria[op - 1].nomecat) == 0)
                {
                    linked = 1;
                    catencontro[i] = 1;
                }
                else
                {
                    catencontro[i] = 0;
                }
            }
        }
        if (linked)
        {
            printf("Erro! Essa categoria esta envolvida nos seguintes encontros: ");
            for (int i = 0; i < NEncontro; i++)
            {
                if (catencontro[i])
                {
                    printf("[ %02d ]; ", i + 1);
                }
            }
            printf("\nNao e possivel editar dados que estao atrelados a um encontro!\n");
            pause();
            return;
        }
    }

    int cat = op - 1;

    char opc;

    do
    {
        limparTela();
        printf("Deseja mesmo excluir [ %s ]?\nEssa acao sera IRREVERSiVEL.\n\n(S/N)", GCategoria[cat].nomecat);
        scanf(" %c", &opc);
        if (opc == 'S' || opc == 's')
        {
            limparTela();
            printf("Voce escolheu [S]; Excluindo. . . ");

            if (NCat == 1)
            {
                free(GCategoria);
            }
            else
            {

                for (int i = cat; i < NCat - 1; i++)
                {
                    GCategoria[i] = GCategoria[i + 1];
                }

                GCategoria = (SCategoria *)realloc(GCategoria, (NCat - 1) * sizeof(SCategoria));
            }
            NCat--;

            limparTela();
            printf("exclusao bem sucedida!\n");
            pause();
            return;
        }
        else if (opc == 'N' || opc == 'n')
        {
            limparTela();
            printf("Voce escolheu [N]; Voltando para menu. . . ");
            printf("\n");
            pause();
            return;
        }
        else

        {
            op = -1;
            mensagemErro(op);
            limparTela();
            return;
        }

    } while (opc != 'S' || opc != 's' || opc != 'N' || opc != 'n');
}
void excluiEncontro()
{
    int op = 0, opaux = 0;
    int erro = 1;
    limparTela();

    if (NEncontro == 0)
    {
        mensagemErro(-10);
        return;
    }
    else
    {
        while (erro)
        {
            listaNomesEncontros();
            printf("| %02d. Voltar                                        |\n", NEncontro + 1);
            printf("+---------------------------------------------------+\n");
            printf("Escolha um para EXCLUIR [ 01 - %02d ]: ", NEncontro + 1);
            scanf("%d", &op);
            if (op == NEncontro + 1)
            {
                return;
            }

            if (op < 1 || op > NEncontro + 1)
            {
                mensagemErro(-1);
            }
            else
            {
                erro = 0;
                if (op == NEncontro + 1)
                {
                    return;
                }
                else
                {
                    limparTela();
                    printf("Deseja mesmo excluir encontro [ %s ]?\n1. Sim\n2.Nao\n", GEncontro[op - 1].nomeencontro);
                    scanf("%d", &opaux);

                    if (opaux != 1)
                    {
                        printf("\n\nVoce escolheu voltar!");
                        pause();
                        return;
                    }
                    else
                    {
                        if (NEncontro == 1)
                        {
                            free(GEncontro);
                            GEncontro = NULL;
                        }

                        else
                        {

                            for (int i = op - 1; i < NEncontro - 1; i++)
                            {
                                GEncontro[i] = GEncontro[i + 1];
                            }

                            GEncontro = (SEncontro *)realloc(GEncontro, (NEncontro - 1) * sizeof(SEncontro));
                        }

                        NEncontro--;

                        limparTela();
                        printf("exclusao bem sucedida!\n");
                        pause();
                        return;
                    }
                }
            }
        }
    }
}