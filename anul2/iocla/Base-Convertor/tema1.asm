%include "io.inc"
%include "input.inc"

section .data

    deimpartit dq 0
    impartitor dd 0    
    
section .text
global CMAIN
CMAIN:
    
    xor eax, eax
    mov ebx, 0
  
    mov eax, dword [numar]
    mov [deimpartit], dword eax
    
    mov eax, [deimpartit]
    mov edx, [deimpartit + 4]
    
    mov ecx, dword [baza]
    mov [impartitor], dword ecx 
    
    
verificare_baza:        ; verifica daca baza este valida, in caz contrar termin programul

    cmp ecx, 2
    jl  exit
    
    cmp ecx, 16
    jg  exit
    
conversie:              ; incep procesul de impartire si verific mai intai daca numarul este diferit de 0

    mov eax, 0
    cmp [deimpartit], eax
    jg impartire
    mov ecx, ebx            ; daca s-a terinat impartirea retin in registrul ecx numarul de resturi din stiva pe care le voi afisa
    jmp afisare
    ret
       
impartire:              ; impart tinand cont ca numarul si baza sunt pe 32 de biti

    inc ebx
    
    mov eax, dword [deimpartit]     ; mut primii 4 octeti in eax, urmand ca restul sa ii mut in registrul edx si sa efectuez impartirea
    mov edx, dword [deimpartit + 4]
    div ecx
    mov [deimpartit], eax
   
    push edx                    ; introduc restul pe stiva si cresc valoarea din registrul ebx in care retin numarul de resturi
    jmp conversie
    ret
    
afisare:            ; ccompar valoare extrasa de pe stiva pentru a sti daca scriu caracter cifra sau caracter litera litera

    dec ecx
    pop ebx
       
    cmp ebx, 10
    jl  afisare_cifra 
    jmp afisare_litera   
          
reluare:                ; in acest label, daca ecx este mai mare ca 0 reiau procesul de afisare
  
    cmp ecx, 0
    jg  afisare
    ret

afisare_litera:         ; daca valoarea din registru ebx este mai mare sau egal cu 10, adun 87 la acea valoarea pt a obtine caracterului in ASCII 

    add ebx, 87
    PRINT_CHAR ebx
    jmp reluare 
    
afisare_cifra:          ; daca valoarea din registrul ebx este mai mica decat 10, adun 48 pt a obtine valoarea caracterului in ASCII

    add ebx, 48
    PRINT_CHAR ebx
    jmp reluare                               
                                                                                                                                           
exit:
     PRINT_STRING "Baza incorecta"
     ret             