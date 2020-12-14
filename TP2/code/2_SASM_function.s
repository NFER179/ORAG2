extern printf
global hola

section .data
    myvar: db 0x42

    img01_pointer: db 0x00
    img02_pointer: db 0x00
    mask_pointer: db 0x00
    out_pointer: db 0x00

    index: dd 0; para recorrer las columnas.
    rgb_per_byte: dd 3;Cantidad de colores por byte.
    total_bites: dd 0
    char_per_bite: dd 3

    columns: dd 0.0; Cantidad de columnas.
    rows: dd 0.0;Cantidad de filas.
    padding: dd 0.0; Cantidad de padding.
    array_len: dd 0.0; Cantidad de elementos en los arrays pasados por parametros.

    msg: db "print msg",10,13,0 

    msg_bien_venida: db "Entranste en SASM",10,13,0
    msg_test: db " Char: %c, %d ",13,10,0
    msg_eax: db "Int: %d",13,10,0
    msg_total_bites: db "Total Bites: %d",13,10,0
    msg_despedida: db "Saliste de SASM",13,10,0

;To debug
    msg_count_columnas: db "Columnas: %d",13,10,0
    msg_count_rows: db "Filas: %d",13,10,0
    msg_padding: db "Padding: %d",13,10,0

section .bss

section .text
hola:

    push ebp
    mov ebp,esp

    ;Get parameters
    ;Tomo los valores desde C
    ;            +----------------------+
    ;esp, ebp -> |         ...          |
    ;            +----------------------+
    ;            |         hola         | +4
    ;            +----------------------+
    ;            | Img01 Buffer pointer | +8
    ;            +----------------------+
    ;            | Img02 Buffer pointer | +12
    ;            +----------------------+
    ;            |  Mask Buffer pointer | +16
    ;            +----------------------+
    ;            |  Out buffer pointer  | +20
    ;            +----------------------+
    ;            |       Columns        | +24
    ;            +----------------------+
    ;            |        rows          | +28
    ;            +----------------------+
    ;            |       Padding        | +32
    ;            +----------------------+

    mov edi, [ ebp + 8 ]
    mov [ img01_pointer ], edi
    mov edi, [ ebp + 12 ]
    mov [ img02_pointer ], edi
    mov edi, [ ebp + 16 ]
    mov [ mask_pointer ], edi
    mov edi, [ ebp + 20 ]
    mov [ out_pointer ], edi
    mov eax, [ ebp + 24 ]
    mov [ columns ], eax
    mov eax, [ ebp + 28 ]
    mov [ rows ], eax
    mov eax, [ ebp + 32 ]
    mov [ padding ], eax

    mov esp, ebp
    pop ebp

    ; call debug_print

    ;Obtenemos el largo de todos los arrays.
    mov eax, [ columns ]
    imul eax, 3
    add eax, [ padding ]
    imul eax, [ rows ]
    mov [ array_len ], eax


    ;Movemos todos los arrays a los registros mmx
    movd mm0, [ img01_pointer ]

    ; ; push dword[ array_len + 4 ]
    ; ; push dword[ array_len ]
    ; ; push msg_eax
    ; ; call printf
    ; ; add esp, 12

    ; mov eax, 0
    ; mov [ index ], eax

    call main_loop

    xor eax, eax
    ret

main_loop:

    ;Empecemos de nuevo
    ;->

    ret
    ;<-

    ;corremos un bit para todos los arreglos;
    ;call read_mask_colors



    ; mov ebx, [ img01_pointer ]
    ; mov ecx, [  ]
    ; push eax
    ; push msg_test
    ; call printf
    ; add esp, 12

;    fld qword[ columns ]
;    fld qword[ 3 ]
;    fmulp

;    fstp qword[ total_bites ]
;    mov ebx, '3'
 ;   mul ebx

;    mov [total_bites], eax

    ; push dword [total_bites]
    ; push msg_eax
    ; call printf
    ; add esp, 8

    ;cmp ecx, 

;    mov eax, [ index ]
;    inc eax,
;    mov [ index ], eax

;    cmp eax, index
;    jg main_loop

;    xor edx, edx; reseteo el index del loop
;    je loop_padding

    ;ret

loop_padding:

    ;Recorremos los bits agregados para que el largo sea divisible por 4.

    inc edx
    cmp [ padding ], edx


    ret

return_main_loop:
    xor edx, edx; Reseteamos el indez del loop

    call main_loop

read_mask_colors:

    ; Leemos los tres bytes de la mascara.

    mov eax, [ mask_pointer + ecx ]


    cmp ecx, rgb_per_byte
    inc ecx
    jl read_mask_colors

    ret

debug_print:

    push msg_bien_venida
    call printf
    add esp, 4

    push dword [ columns + 4 ]
    push dword [ columns ]
    push msg_count_columnas
    call printf
    add esp, 12

    push dword [ rows + 4 ]
    push dword [ rows ]
    push msg_count_rows
    call printf
    add esp, 12

    push dword [ padding + 4 ]
    push dword [ padding ]
    push msg_padding
    call printf
    add esp, 12

    push msg_despedida
    call printf
    add esp, 4

    ret