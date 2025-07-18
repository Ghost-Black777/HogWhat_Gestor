#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TURMAS 4
#define ALUNOS_POR_TURMA 5

typedef struct {
    char nome[50];
    int inteligencia;
    int destreza;
    int carisma;
} Bruxo;

typedef struct {
    char nome[50];
    int totalCarisma;
    int totalDestreza;
    int pontos;
    Bruxo alunos[ALUNOS_POR_TURMA];
} Turma;

int gerarHab() {
    return rand() % 6;
}

void cadastrarBruxo(Bruxo *b) {
    printf("Nome do bruxo: ");
    fgets(b->nome, sizeof(b->nome), stdin);
    strtok(b->nome, "\n");

    b->inteligencia = gerarHab();
    b->destreza = gerarHab();
    b->carisma = gerarHab();
}

void cadastrarTurma(Turma tur[], int qtdTur) {
    int j;

    printf("\nCadastro da Turma %d\n", qtdTur + 1);

    printf("\nDigite o nome da turma %d: ", qtdTur+ 1);
    fgets(tur[qtdTur].nome, sizeof(tur[qtdTur].nome), stdin);
    tur[qtdTur].nome[strcspn(tur[qtdTur].nome, "\n")] = '\0';
    tur[qtdTur].pontos = 0;

    for (j = 0; j < ALUNOS_POR_TURMA; j++) {
            printf("\nBruxo %d:\n", j + 1);
            cadastrarBruxo(&tur[qtdTur].alunos[j]);
        }

}

void imprimirTurmas(Turma tur[]) {
    printf("\n--- Dados das turmas ---\n");
    for (int i = 0; i < MAX_TURMAS; i++) {
        printf("\nTurma: %s\n", tur[i].nome);
        printf("Pontos: %d\n", tur[i].pontos);
    }
}

void imprimirAlunosDaTurma(Turma tur[]) {
    char nomeBusca[50];
    printf("Digite o nome da turma: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    strtok(nomeBusca, "\n");

    for (int i = 0; i < MAX_TURMAS; i++) {
        if (strcmp(tur[i].nome, nomeBusca) == 0) {
            printf("\n--- Alunos da turma %s ---\n", tur[i].nome);
            for (int j = 0; j < ALUNOS_POR_TURMA; j++) {
                Bruxo b = tur[i].alunos[j];
                printf("Nome: %s | Inteligencia: %d | Destreza: %d | Carisma: %d\n", b.nome, b.inteligencia, b.destreza, b.carisma);
            }
            return;
        }
    }
    printf("Turma não encontrada.\n");
}

void calcularatributos(Turma *turma){

    turma-> totalCarisma = 0;
    turma-> totalDestreza = 0;

    for(int i = 0; i < ALUNOS_POR_TURMA; i++){

        turma-> totalCarisma += turma-> alunos[i].carisma;
        turma-> totalDestreza += turma-> alunos[i].destreza;
    }
}

void quadrilol(Turma tur[], int qtdTur){

    int maiorCarisma = -1;
    int maiorDestreza = -1;
    int indiceTurmaMaiorCarisma = -1;
    int indiceTurmaMaiorDestreza = -1;

    //calcular
    for (int i = 0; i < qtdTur; i++) {
        calcularatributos(&tur[i]);
    }

    //Encontrar a turma com maior carisma e destreza
    for (int i = 0; i < qtdTur; i++) {
        if (tur[i].totalCarisma > maiorCarisma) {
            maiorCarisma = tur[i].totalCarisma;
            indiceTurmaMaiorCarisma = i;
        }
        if (tur[i].totalDestreza > maiorDestreza) {
            maiorDestreza = tur[i].totalDestreza;
            indiceTurmaMaiorDestreza = i;
        }
    }
    if(indiceTurmaMaiorCarisma != -1){

        tur[indiceTurmaMaiorCarisma].pontos += 5;
    }
    if(indiceTurmaMaiorDestreza != -1){

        tur[indiceTurmaMaiorDestreza].pontos += 10;
    }
}

void artesArcanistas(Turma tur[]) {
    int idx1 = rand() % MAX_TURMAS;
    int idx2;
    do {
        idx2 = rand() % MAX_TURMAS;
    } while (idx2 == idx1);

    int aluno1 = rand() % ALUNOS_POR_TURMA;
    int aluno2 = rand() % ALUNOS_POR_TURMA;

    Bruxo b1 = tur[idx1].alunos[aluno1];
    Bruxo b2 = tur[idx2].alunos[aluno2];

    printf("\nDesafio entre %s (%s) vs %s (%s)\n", b1.nome, tur[idx1].nome, b2.nome, tur[idx2].nome);
    if (b1.inteligencia > b2.inteligencia) {
        tur[idx1].pontos += 10;
        printf("Vencedor: %s (+10 pontos)\n", tur[idx1].nome);
    } else if (b2.inteligencia > b1.inteligencia) {
        tur[idx2].pontos += 10;
        printf("Vencedor: %s (+10 pontos)\n", tur[idx2].nome);
    } else {
        printf("Empate! Ninguém pontua.\n");
    }
}

void buscarPedraFloatzal(Turma turmas[]) {
    int idxMenor = -1, menorSoma = 999;

    for (int i = 0; i < MAX_TURMAS; i++) {
        int soma = 0;
        int escolhidos[3];
        for (int j = 0; j < 3; j++) {
            escolhidos[j] = rand() % ALUNOS_POR_TURMA;
            soma += turmas[i].alunos[escolhidos[j]].destreza;
        }

        if (soma < menorSoma) {
            menorSoma = soma;
            idxMenor = i;
        }
    }

    printf("\nTurma pega pelo Valdechar: %s\n", turmas[idxMenor].nome);
    for (int i = 0; i < 3; i++) {
        int idxAluno = rand() % ALUNOS_POR_TURMA;
        turmas[idxMenor].alunos[idxAluno].carisma = 0;
        turmas[idxMenor].alunos[idxAluno].destreza = 0;
        turmas[idxMenor].alunos[idxAluno].inteligencia = 0;
    }

    for (int i = 0; i < MAX_TURMAS; i++) {
        if (i == idxMenor) continue;
        if (rand() % 10 == 0) { // 10% chance
            turmas[i].pontos += 20;
            printf("Turma %s encontrou a Pedra Floatzal! (+20 pontos)\n", turmas[i].nome);
        }
    }
}

void aplicarBonusGrifinoria(Turma turmas[]) {
    for (int i = 0; i < MAX_TURMAS; i++) {
        if (strcmp(turmas[i].nome, "Grifinoria") == 0) {
            turmas[i].pontos += 20;
            printf("\nBônus secreto: Grifinoria ganhou +20 pontos!\n");
            break;
        }
    }
}

int main(){
    srand(time(NULL));
    Turma turmas[MAX_TURMAS];
    int desafiosExecutados = 0;
    int opcao;
    int nTurma = MAX_TURMAS;

    // Loop para cadastrar as 4 turmas
    for (int i = 0; i < MAX_TURMAS; i++) {
        cadastrarTurma(turmas, i);
    }

    do {
        printf("\n--- Gerenciador Ultra Mega Blaster da Escola de Bruxos 2.0 ---\n");
        printf("1. Imprimir dados das turmas\n");
        printf("2. Imprimir alunos de uma turma\n");
        printf("3. Executar desafio\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

        switch (opcao) {
            case 1:
                imprimirTurmas(turmas);
                break;
            case 2:
                imprimirAlunosDaTurma(turmas);
                break;
            case 3:
                if (desafiosExecutados >= 5) {
                    printf("Você já executou 5 desafios.\n");
                    break;
                }
                printf("\nEscolha o desafio:\n");
                printf("1. QuadriLOL\n");
                printf("2. Artes Arcanistas Arcanas\n");
                printf("3. Buscando a Pedra 'Floatzal'\n");
                int desafio;
                scanf("%d", &desafio);
                getchar(); // limpar \n

                switch (desafio) {
                    case 1: quadrilol(turmas, nTurma); break;
                    case 2: artesArcanistas(turmas); break;
                    case 3: buscarPedraFloatzal(turmas); break;
                    default: printf("Desafio inválido!\n"); continue;
                }
                desafiosExecutados++;
                imprimirTurmas(turmas);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    aplicarBonusGrifinoria(turmas);
    printf("\n--- Pontuação Final ---\n");
    imprimirTurmas(turmas);

    return 0;
}

//Nomes: Eduardo Félix, Hugo Felipe, Fábio Miguel e Lukas
