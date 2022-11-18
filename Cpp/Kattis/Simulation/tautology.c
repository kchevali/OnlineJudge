#include "stdio.h"
#define BIN_COUNT 5

char line[110];
int binaries[BIN_COUNT];

void solve(int* idx, int* result){
    char ch = line[*idx];
    (*idx) += 1;
    if(ch >= 'p' && ch <= 't'){
        (*result) = binaries[ch - 'p'];
        return;
    }

    solve(idx, result);
    int a = (*result);
    if(ch == 'N'){
        (*result) = ~a;
        return;
    }
    solve(idx, result);
    int b = (*result);
    
    switch(ch){
        case 'K': (*result) = a & b; break;
        case 'A': (*result) = a | b; break;
        case 'C': (*result) = (~a) | b; break;
        default:  (*result) = ~(a^b); break;
    }
    // fprintf(stderr, "%c: %x %x = %x\n", ch, a, b, *result);
}

int main() {
    for(int i = 0; i < (1 << BIN_COUNT); i++){
        for(int k = 0; k < BIN_COUNT; k++){
            binaries[k] |= ((i >> k) & 1) << i;
        }
    }

    while(scanf("%s", line) && line[0] != '0'){
        int idx = 0, result = 0;
        solve(&idx, &result);
        // fprintf(stderr, "%d\n", result);
        printf("%s\n", result == -1 ? "tautology" : "not");
    }
}
