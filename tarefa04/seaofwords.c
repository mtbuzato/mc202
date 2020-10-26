#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lookAround(char c, char **linhas, int n, int m, int *x, int *y, int **visited) {
    for(int i = 0; i < 4; i++) {
        int a = *x;
        int b = *y;

        switch(i) {
            case 0:
                a--;
                break;
            case 1:
                a++;
                break;
            case 2:
                b--;
                break;
            case 3:
                b++;
                break;
        }
        
        if(a < m && a >= 0 && b < n && b >= 0 && !visited[b][a] && linhas[b][a] == c) {
            *x = a;
            *y = b;
            return 1;
        }
    }

    return 0;
}

int search(char word[], char **linhas, int n, int m, int x, int y, int **visited) {
    int found = 0;

    visited[y][x] = 1;
    while(found < strlen(word) - 1 && lookAround(word[found + 1], linhas, n, m, &x, &y, visited)) {
        visited[y][x] = 1;
        found++;
    }

    if(found >= strlen(word) - 1) {
        return 1;
    } else {
        found--;

        if(found > 0) {
            return search(word, linhas, n, m, x, y, visited);
        } else {
            return 0;
        }
    }
}

int find(char word[], char **linhas, int n, int m) {
    int x, y = 0;

    int **visited = malloc(n * sizeof(int *));
    if(visited == NULL) {
        printf("Erro! Não há memória disponível!\n");
        exit(0);
    }

    for(int i = 0; i < n; i++) {
        visited[i] = malloc(m * sizeof(int));
        if(visited[i] == NULL) {
            printf("Erro! Não há memória disponível!\n");
            exit(0);
        }
    }

    for(x = 0; x < m; x++) {
        for(y = 0; y < n; y++) {
            if(word[0] == linhas[y][x]) {
                for(int i = 0; i < n; i++) {
                    for(int x = 0; x < m; x++) {
                        visited[i][x] = 0;
                    }
                }

                int searchResult = search(word, linhas, n, m, x, y, visited);

                if(searchResult) {
                    for(int i = 0; i < n; i++) {
                        free(visited[i]);
                    }
                    free(visited);
                    
                    return 1;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        free(visited[i]);
    }
    free(visited);

    return 0;
}

int main() {
    int n, m, q, i, x = 0;

    scanf("%d %d %d", &n, &m, &q);

    char **linhas = malloc(n * sizeof(char *));
    if(linhas == NULL) {
        printf("Erro! Não há memória disponível!\n");
        exit(0);
    }
    for(i = 0; i < n; i++) {
        linhas[i] = malloc(m * sizeof(char));
        if(linhas[i] == NULL) {
            printf("Erro! Não há memória disponível!\n");
            exit(0);
        }

        for(x = 0; x < m; x++) {
            scanf(" %c", &linhas[i][x]);
        }
    }

    for(i = 0; i < q; i++) {
        char word[20];
        scanf("%s ", word);

        if(find(word, linhas, n, m)) {
            printf("sim\n");
        } else {
            printf("nao\n");
        }
    }

    for(i = 0; i < n; i++) {
        free(linhas[i]);
    }
    free(linhas);

    return 0;
}