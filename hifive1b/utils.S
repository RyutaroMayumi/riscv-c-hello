    .global start
start:
    lui sp, 0x80004
    jal main
    j .

    .global dummy
dummy:
    ret

    .global put32
put32:
    sw x11,(x10)
    ret

    .global get32
get32:
    lw x10,(x10)
    ret

