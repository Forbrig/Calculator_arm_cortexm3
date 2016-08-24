void main() {
/*
VITOR GUILHERME FORBRIG & LEONARDO BIANCHINI

O registrador que recebe as entradas � o r0, a cada laco em que passa por pelo rotulo
COMP deve ser setado manualmente o que se quer fazer

*/
/*    int i;
    int value;
    char entrada[] = "44 1 +";
    for (i = 0; entrada[i] != '\0'; i++) { //enqanto o vetor tiver
        value = 0;
        if (entrada[i] == '+') {
            value = 43;
        } else if (entrada[i] == '*') {
            value = 42;
        } else if (entrada[i] == '-') {
            value = 45;
        } else if (entrada[i] == '/') {
            value = 47;
        } else if (entrada[i] == 'S') {
            value = 83;
        } else if (entrada[i] == 'Q') {
            value = 81;
        } else if (entrada[i] == 'C') {
            value = 67;
        } else if (entrada[i] == ' ') {
            i++;
        } else {
            value = atoi(&entrada[i]);
            i++;
            if (value > 9) {
                i++;
            }
        }
        if (value == 0) {
            i++;
        }
        R0 = value;
*/
        asm {
            INIT:
                 ;Todas as opera��es ser�o salvadas com seus equivalentes ASCII em decimal
                 ;OPERA��ES ALG�BRICAS
                 LDR R3, =42 ; (MULTIPLICA��O '*')
                 LDR R4, =47 ; (DIVIS�O '/')
                 LDR R5, =43 ; (ADI��O '+')
                 LDR R6, =45 ; (SUBTRA��O '-')
                 
                 ;OPERA��ES ADICIONAIS
                 LDR R7, =83 ; (STACK 'S') -> EXIBE O CONTE�DO DA PILHA
                 LDR R8, =67 ; (CLEAR 'C') -> LIMPA OS VALORES DA PILHA
                 LDR R9, =81 ; (QUIT 'Q') -> TERMINA O PROGRAMA
                 
            COMP:
                 ;Testa qual opera��o ou n�mero est� no registrador de leitura (definido como r0)
                 ;Se n�o for opera��o o valor ser� adicionado a pilha
                 CMP R0, R3 ;
                 IT EQ
                 BEQ MULT ; (cai no r�tulo de MULTIPLICA��O '*')
                 CMP R0, R4;
                 IT EQ
                 BEQ DIV ; (cai no r�tulo de DIVIS�O '/')
                 CMP R0, R5;
                 IT EQ
                 BEQ SUM ; (cai no r�tulo de ADI��O '+')
                 CMP R0, R6;
                 IT EQ
                 BEQ SUB ; (cai no r�tulo de SUBTRA��O '-')

            ;;;;;;;;;;;;;;;;;;;OPERA��ES ADICIONAIS

                 CMP R0, R7;
                 IT EQ
                 BEQ STACK_LAST_ADRESS ; (cai no r�tulo de STACK 'S')
                 CMP R0, R8;
                 IT EQ
                 BEQ  CLEAR ; (cai no r�tulo de CLEAR 'C')
                 CMP R0, R9;
                 IT EQ
                 BEQ QUIT ; (cai no r�tulo de QUIT 'Q')
                 CMP R0, R10;
                 IT EQ
                 BEQ END ; (� um espa�o, termina o la�o atual)
                 B ADD_STACK ; Se n�o caiu em nenhuma operacao deve adicionar o numero na pilha

            ADD_STACK:
                 PUSH (R0) ; Se entrou aqui � porque � um valor que entra na pilha
                 B END ; Termina a iteracao do laco
                 
            SUM:
                ;Soma r2 de r1 e coloca na pilha
                POP (R2)
                POP (R1)
                ADD R1, R1, R2
                PUSH (R1);
                B END

            SUB:
                ;Subtrai r2 de r1 e coloca na pilha
                POP (R2)
                POP (R1)
                SUB R1, R1, R2
                PUSH (R1);
                B END

            MULT:
                 ;Multiplica r2 de r1 e coloca na pilha
                POP (R2)
                POP (R1)
                MUL R1, R1, R2
                PUSH (R1);
                B END
                
            DIV:
                ;Divide r2 de r1 e coloca na pilha
                POP (R2)
                POP (R1)
                UDIV R1, R1, R2
                PUSH (R1);
                B END
                
            STACK_LAST_ADRESS:
                ;
                MOV R1, SP ; le o endereco do stack pointer
                LDR R0, [R1] ; le qual o valor do endereco contido em r11
                CMP R0, #0
                IT NE
                BNE STACK_LOOP
                B END         ; se n�o tiver nada ele j� cai fora
            
            STACK_LOOP:
                LDR R0, [R1] ; le qual o valor do endereco contido em r11
                ADD R1, #4
                CMP R0, #0
                IT NE
                BNE STACK_LOOP
                B END
            
            CLEAR:
                 ; Compara e se n�o for '0' o ultimo valor da pilha, ele volta pra funcao para tirar outro valor
                 ; Quando a pilha estiver zerada quer dizer que no ultimo pop r0 vai receber 0
                 POP (R0)
                 CMP R0, #0
                 IT NE
                 BNE CLEAR
                 ;compara se n�o for zero
                 ;se passou ele cai no END
            
            END:
                 B COMP ; Volta pro laco de comparacao
            
            QUIT:
    }
}