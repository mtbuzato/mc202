#include <stdio.h>
#include "./professor_carlos.h"

int main() {
    Turma t[50];

    int numTurmas, numOps;
    scanf("%d %d ", &numTurmas, &numOps);

    for(int numTurma = 0; numTurma < numTurmas; numTurma++) {
        Turma turma;
        turma.qtd = 0;
        t[numTurma] = turma;

        int qtd;
        scanf("%d ", &qtd);

        for(int n = 0; n < qtd; n++) {
            Aluno aluno;
            scanf("%s %s %d %d %d ", aluno.nome, aluno.sobrenome, &aluno.nascimento.dia, &aluno.nascimento.mes, &aluno.nascimento.ano);

            add_aluno(t, aluno, numTurma);
        }
    }

    for(int op = 0; op < numOps; op++) {
        int cmd;
        scanf(" %d", &cmd);

        if(cmd == 1) {
            int turma;
            scanf(" %d ", &turma);
            printf("%s\n", procura_novo_na_turma(t, numTurmas, turma).nome);
        } else if(cmd == 2) {
            int turma;
            scanf(" %d ", &turma);
            printf("%s\n", procura_velho_na_turma(t, numTurmas, turma).sobrenome);
        } else if(cmd == 3) {
            printf("%s\n", procura_velho_todas_turmas(t, numTurmas).nome);
        } else if(cmd == 4) {
            printf("%s\n", procura_novo_todas_turmas(t, numTurmas).sobrenome);
        } else if(cmd == 5) {
            char sub[5];
            scanf(" %s ", sub);

            printf("%d\n", conta_substrings(t, numTurmas, sub));
        } else if(cmd == 6) {
            int turma;
            Aluno aluno;
            scanf(" %d %s %s %d %d %d ", &turma, aluno.nome, aluno.sobrenome, &aluno.nascimento.dia, &aluno.nascimento.mes, &aluno.nascimento.ano);

            printf("%d\n", add_aluno(t, aluno, turma));
        } else if(cmd == 7) {
            int turma;
            scanf(" %d ", &turma);
            printf("%d\n", remove_aluno(t, turma));
        }
    }

    return 0;
}
