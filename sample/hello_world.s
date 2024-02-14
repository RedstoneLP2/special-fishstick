.setcpu "65C02"
.segment "HELLOWORLD"

HELLOWORLD:
        lda #72         ; 'H' Screen Code
        jsr CHROUT
        lda #69         ; 'E' Screen Code
        jsr CHROUT
        lda #76         ; 'L' Screen Code
        jsr CHROUT
        lda #76         ; 'L' Screen Code
        jsr CHROUT
        lda #79         ; 'O' Screen Code
        jsr CHROUT
        lda #32        ; ' ' Screen Code
        jsr CHROUT
        lda #87         ; 'W' Screen Code
        jsr CHROUT
        lda #79         ; 'O' Screen Code
        jsr CHROUT
        lda #82         ; 'R' Screen Code
        jsr CHROUT
        lda #76         ; 'L' Screen Code
        jsr CHROUT
        lda #68         ; 'D' Screen Code
        jsr CHROUT
        lda #33         ; '!' Screen Code
        jsr CHROUT
        lda #10         ; '\n' Screen Code
        jsr CHROUT

        JMP RESET