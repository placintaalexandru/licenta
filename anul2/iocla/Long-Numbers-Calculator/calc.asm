; decomment according to platform (Linux or Windows)
;%include "include/io.lin.inc"
%include "include/io.win.inc"

section .data

    rezultat:  times 300 db 0
    transport: times 1 db 0
    mycarry:   times 1 db 0
    inmultitor: times 1 db 0
    
section .text

global do_operation

; TODO dissasemble the main.o file. Be sure not to overwrite registers used
; by main.o that he does not save himself.
; If you see your program going nuts, consider looking in the main.o disassembly
; for the causes mentioned earlier.

do_operation:

	; TODO

        push ebp
        mov ebp, esp
        
        xor edi, edi
        xor esi, esi
        xor eax, eax
        xor ebx, ebx
        xor edx, edx
        xor ecx, ecx
        
        mov edi, dword [ebp + 8]          ; parametrul 1
        mov esi, dword [ebp + 12]         ; parametrul 2
        mov edx, dword [ebp + 16]         ; operatia, voi compara valoarea din edx cu valorile in codul ASCII ale caracterelor pt operatie
        
        cmp [edx + 0], byte 124           ; operatia este de sau pe biti
        je  sau_pe_biti                    
        
        cmp [edx + 0], byte 38            ; operatia este de si pe biti
        je  si_pe_biti
        
        cmp [edx + 0], byte 60            ; operatie este de shiftare la la stanga
        je  shiftare_la_stanga      
        
        cmp [edx + 0], byte 62            ; operatie de shiftare la dreapta
        je shiftare_la_dreapta
        
        cmp [edx + 0], byte 43            ; operatie de adunare
        je  adunare
        
        cmp [edx + 0], byte 42            ; operatia de inmultire
        jmp inmultire
        
        jmp afara                         ; daca nu e nicio similitudine ies din functie

        
sau_pe_biti:

       mov ecx, 0                  
       
sau_pe_octeti:

        cmp ecx, dword [esi + 4]         ; efectuez operatia cat timp am octeti in al 2 lea parametru
        je  redimensioneaza              ; daca al 2 lea paraemtru are mai multi octeti redimensionez rezultatul, il maresc
        
        mov al, [esi + 8 + ecx]              
        or [edi + 8 + ecx], byte al
        
        inc ecx
        jmp sau_pe_octeti

redimensioneaza:

        mov eax, dword [esi + 4]        ; verific cele 2 dimensiuni
        mov ebx, dword [edi + 4]
        
        cmp eax, dword ebx              ; daca dimensiunea numarului 2 e mai mare, atunci ajustez dimensiunea rezultatului
        jg  maresc_rezultatul
        
        jmp afara
        
maresc_rezultatul:

        mov [edi + 4], dword ebx        ; maresc dimensiunea rezultatului
        jmp afara                       ; ies din functie
                
si_pe_biti:

       mov ecx, 0                  
       
si_pe_octeti:

        cmp ecx, dword [esi + 4]         ; efectuez operatia cat timp am octeti in al 2 lea parametru
        je  redimensionare_dupa_si       ; restul de octeti din primul parametru vor deveni 0
        
        mov al, [esi + 8 + ecx]              
        and [edi + 8 + ecx], byte al
        
        inc ecx
        jmp si_pe_octeti
        
redimensionare_dupa_si:

        mov eax, dword [edi + 4]
        mov ecx, [esi + 4]               ; la si pe biti daca am octeti de 0, lungimea din primul parametru devine cea din al 2 lea
        
        cmp eax, dword ecx               ; daca primul numar are cel mult la fel de multi octeti nu modific dimensiunea
        jle afara
          
        mov [edi + 4], ecx               ; actualizez dimensiunea numarului din rezultat
        
        jmp afara

                          
shiftare_la_stanga:

        xor edx, edx

shl_o_pozitie:
 
        cmp edx, dword [esi + 8]        ; compar a cata shiftare o fac  cu numarul total de shiftari stanga
        jge afara                       ; pt mai mare ies din functie
        
        inc edx
        mov ecx, dword [edi + 4]
        
parcurgere_octeti_shl:                  ; parcurg octetii in ordine inversa

        cmp ecx, [edi + 4]              ; daca sunt pe pozitia maxima, verificc o posibila marire a vectorului de contine numarul
        je  posibila_marire
        
        cmp ecx, 0                          ; daca sunt pe octetul 0 din numar, il shiftez simplu la stanga
        je  cel_mai_nesemnificativ_shl
        
        mov bl, byte [edi + 8 + ecx]        ; daca sunt undeva la mijloc iau si octetul anterior celui curent sa vad daca este mai mare decat 0x80
        mov al, byte [edi + 7 + ecx]
        
        shl bl, 1
        
        and al, 0x80                        ; compar cu 0x80, caz in care dup shiftare adun 1 la octetul curent, apare 1-ul din octetulanterior
        cmp al, 0x80
        je  octet_anterior_cu_unu
        
revenire_shl:

        mov [edi + 8 + ecx], byte bl        ; mut octetul curent modificat in vectorul de octeti
        dec ecx
        jmp parcurgere_octeti_shl
                
octet_anterior_cu_unu:

        inc bl                              ; pun acel 1 de la octetul anterior
        jmp revenire_shl            
        
cel_mai_nesemnificativ_shl:

        shl byte [edi + 8], 1               ; shiftez cel mai nesemnificativ octet si dupa ma intorc la reluarea iteratiei de shiftare a intregului numar
        jmp shl_o_pozitie
                
posibila_marire:

        dec ecx                            ; verific o posibila marire a numarului dupa inmultire
        mov al, byte [edi + 8 + ecx]
        
        and al, 0x80                        ; acest lucru il fac pentru a vedea daca octetul este 10000000 caz in care 1 se duce mai in stanga
        cmp al, 0x80
        je  marire_capacitate               ; maresc capacitatea
        jmp parcurgere_octeti_shl           ; altfel reiau parcurgerea octetilor
        
marire_capacitate:

        inc dword [edi + 4]                 ; incrementez cei 4 octeti care retin lungimea numarului
        
        add [edi  + 8 + ecx + 1], byte 1    ; reiau parcurgerea de octeti
        
        jmp parcurgere_octeti_shl

          
shiftare_la_dreapta: 
        
        xor edx, edx
        xor ecx, ecx
        
shr_o_pozitie:

       cmp edx, dword [esi + 8]             ; verific la a cata shiftare sunt
       jge  afara                           ; daca am shiftat de cate ori trebuie, sau mai mult in pt a asigura iesirea, ies din functie
       
       inc edx                              ; cresc numarul de shiftari, deoarece urmeaza operatia in sine
       mov ecx, dword 0                     ; contrar celei la stanga, pt shift la dreapta, parcurg vectorul de octeri de la inceput spre final
        
parcurgere_octeti_shr:

       cmp ecx, 0                           ; shiftez cel mai nesemnificativ octet
       je  cel_mai_nesemnificativ_shr
       
       mov eax, dword [edi + 4]             ; verific daca am ajuns pe octeul cel mai semnificativ, eventual o posibila reducere a numarului de octeti
       
       dec eax      
       
       cmp ecx, eax
       je  posibila_micsorare               ; efectuez reducerea numarului de octeti
       
       mov al, byte [edi + 8 + ecx]         ; iau octetul curent si octetul imediat mai semnificativ decat el
       mov bl, byte [edi + 8 + ecx + 1]
       
       shr byte al, 1                       ; shiftez octetul curent
       
       and bl, byte 0x1                     ; verific daca octetul imediat mai semnificativ are cel mai nesemnificativ bit 1
       cmp bl, byte 0x1
       je  coboara_unu                      ; caz in care acel 1 "coboara" in octetul curent
       
actualizare_octet_curent:

       mov [edi + 8 + ecx], byte al          ; actualizez octetul curent din vectorul de octeti
       inc ecx
       jmp parcurgere_octeti_shr
             
coboara_unu:

       or al, 0x80                          ; acel 1 care coboara il introduc efectuand un "sau" cu 10000000, 0x80 in hexa
       jmp actualizare_octet_curent        
       
posibila_micsorare:

       mov al, byte [edi + 8 + ecx]         ; o micsorare apare cand dupa shiftare celui mai semnificativ octet acesta ramane 0
       shr al, 1
       mov [edi + 8 + ecx], byte al
       
       cmp al, 0x0                          ; verific daca ramane 0
       je  micsorare_capacitate             ; micsorez capacitatea
       
       jmp shr_o_pozitie                    ; reiau operatia de shiftare
       
micsorare_capacitate:

       dec dword [edi + 4]                  ; decrementez cei 4 octeti care contin lungimea numarului
       jmp shr_o_pozitie                    ; reiau operatia de shiftare
                           
cel_mai_nesemnificativ_shr:

        inc ecx                             ; cresc indecele octetului pe care ma aflu
        mov al, byte [edi + 8]              ; iau cel mai nesemnificativ octec si cel de langa el
        mov bl, byte [edi + 9]
        
        shr al, 1                            ; shiftez octetul la drapta
        
        and bl, byte 0x1                     ; pt octetul de langa el, verific daca are cel mai nesemnificativ bit 1, caz in care o sa treaca jos
        cmp bl, byte 0x1
        je  trece_unu

revenire_shr:

        mov [edi + 8], byte al              ; actualizez octetul curent din vectorul de octeti
        jmp parcurgere_octeti_shr
                       
trece_unu:

        or al, byte 0x80                    ; adaug acel 1 printr-un "sau" logic cu 10000000
        jmp revenire_shr
    
adunare:

       mov eax, dword [edi]
       mov ebx, dword [esi]
       xor  eax, ebx
       
       cmp eax, 0
       je  ambele_au_acelasi_semn           ; daca ambele au acelasi semn le adun pur si simplu octet cu octet
       
       cmp eax, 0xFFFFFFFF
       je semne_diferite
       
       jmp afara
       
ambele_au_acelasi_semn:

       xor edx, edx
       xor ecx, ecx                         ; retin carry-ul
       
adunare_octet_cu_octet:

       cmp edx, dword [esi + 4]
       je  continuare_in_rezultat
       
       xor eax, eax
       xor ebx, ebx
       
       mov al, byte [edi + 8 + edx]         ; adun octetii de pe aceleasi pozitii
       mov bl, byte [esi + 8 + edx]
       
       add ax, word bx
       add ax, word cx                      ; adun si carry-ul
       
       xor ecx, ecx
       
       cmp ax, word 0x100                   ; verifica daca rezultatul trece de un octet
       jge am_carry_la_adunare
       
actualizare_octet_dupa_add:

       mov [edi + 8 + edx], byte al
       inc edx
       jmp adunare_octet_cu_octet

              
am_carry_la_adunare:

        inc cx                              ; actualizez carry-ul
        sub ax, word 0x100                  ; iau numai partea care depaseste un octet
        jmp actualizare_octet_dupa_add      ; actualizez octetul din nuamrul 1
        
continuare_in_rezultat:

        cmp cx, word 0                      ; daca nu mai am carry verific o posibila marire de rezultat
        je posibila_marire_dupa_adunare     ; daca nu verifica daca trebuie sa maresc rezultatul
        
        xor eax, eax                        
        
        mov al, byte [edi + 8 + edx]         
        add ax, word cx                     ; adun la octetul din primul parametru, carry-ul ramas, posibil sa adun 0 daca nu ramane
        
        xor ecx, ecx                        ; restez carry-ul
        
        cmp ax, 0x100                       ; verific daca rezultatul adunarii precedent depaseste un octet
        jge actualizare_octet_rezultat

actualizare_in_continuare:

        mov [edi + 8 + edx], byte al
        
        inc edx                                 ; incrementez numarul de octeti parcursi
        
        jmp continuare_in_rezultat
                        
actualizare_octet_rezultat:                 

         inc cx                                 ; actualizez in continuare cel mai semnificativ octet din rezultat, din primul numar
         sub ax, word 0x100                     ; pastrez daor partea care incape pe un octet
         mov [edi + 8 + edx], byte al           ; mute octetul in primul numar
         jmp actualizare_in_continuare            
                                        
posibila_marire_dupa_adunare:

         cmp edx, dword [edi + 4]               ; compar numarul de octeti parcursi cu numarul initial de octeti din numarul 1
         jg  marire_rezultat                    ; daca e mai mare actualizez numarul de octeti
         
marire_rezultat:

         mov [edi + 4], dword edx               ; daca este mai mare nuamrul de octeti parcursi, atunci maresc rezultatul
         jmp afara                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
        
semne_diferite:                                 ; pentru semne diferite vad care este negativ, iar apoi cine este mai mare

         xor edx, edx
         xor ecx, ecx
        
         cmp ebx, 0xFFFFFFFF                     ; compar semnul celui de-al 2 lea pentru a vedea cine e pozitiv si cine e negativ  
         je  primul_poz_doi_negativ
         jmp primul_e_negativ

primul_poz_doi_negativ:

        mov ecx, dword [edi + 4]                ; numarul de octeti ai primului numar
        mov edx, dword [esi + 4]                ; numarul de octeti ai celui de-al 2 lea numar
        
        cmp ecx, dword edx                      ; pentru a vedea cine e mai mare compar mai intai numarul de octeti
        jl  primul_e_mai_mic                    ; daca numarul de octeti ai primului e mai mic, atunci primul numar e , mai mic
        
        cmp ecx, dword edx
        jg al_doilea_e_mai_mic                 ; daca nuamrul de octeti ai celui de-al 2 lea e mai mic, atunci al 2 lea e mai mic
        
        xor eax, eax
        xor ebx, ebx
        
        dec edx
        jmp comparatie_octet_cu_octet           ; daca au numar egal de octeti, compar octet cu octet, de la cel mai semnificativ
        
comparatie_octet_cu_octet:                      ; compar octet cu octet sa vad cine e mai mare pana dau de o inegalitate sau epuizez toti octetii

        cmp edx, dword 0
        jl  numerele_sunt_egale                 ; daca am ajuns sa comapr toti octetii, inseamna ca numerele sunt egale       
               
        mov al, byte [edi + 8 + edx]            ; octetul primul numar
        mov bl, byte [esi + 8 + edx]            ; octetul celui de-al 2 lea numar
        
        cmp al, byte bl                         ; daca octeul primului e mai mic, atunci primul numar e mai mic
        jg  al_doilea_e_mai_mic
        
        cmp al, byte bl                         ; daca octetul celui de-al 2 lea e mai mic, atunci al 2 lea e mai mic
        jl  primul_e_mai_mic
        
        dec edx                                 ; daca sunt egale, trec la octetul urmator, al 2 lea cel mai semnificativ si reiau comparatia
        jmp comparatie_octet_cu_octet
                                                                
primul_e_mai_mic:                               ; daca primul e mai mic scad din octetii celui de-al doilea si pun semnul ceui de-al doilea

        mov  [edi], dword 0xFFFFFFFF
        jmp  iteratie2
        
al_doilea_e_mai_mic:                            ; am trecut numarul 2 in complement fata de 2 si am efecctuat aceleasi operatii ca si la adunare
 
        mov [edi], dword 0
        jmp  iteratie1                          

iteratie1:                                      

        xor edx, edx
        mov ecx, dword 1
                                                          
scadere_octet_cu_octet:             ; scad octet cu octete, dar de fapt adun octetii numarului pozitiv cu cei trecuti in complement fata de 2

        cmp edx, dword [esi + 4]                    ; daca am parcurs toti aoctetii, am terminat adunarea si ies din functie
        je  afara
        
        xor eax, eax
        xor ebx, ebx
        
        mov al, byte [edi + 8 + edx]                ; octetul primului numar, numar care e pozitiv
        mov bl, byte [esi + 8 + edx]                ; octetul celui de-al doilea numar, numar care e pozitiv
     
        neg bl                                      ; neg octetul scazatorului si il void aduna la octetul descazutului
        dec bl

        add ax, bx                                  ; adun la octetul numarului pozitiv negatul octetului numarului negativ
        add ax, cx                                  ; adun carry-ul
        xor ecx, ecx

        cmp ax, word 0x100                          ; verific daca am obtinut o valoare care depaseste un octet
        jge  imprumutare                            ; imprumuatrea va corespunde in acest caz incrementarii octetului mai semnificativ

actualizare_dupa_imprumut:                
        
        mov [edi + 8 + edx], byte al                ; mut octetul dupa prelucrare in rezultat
        inc edx
        jmp scadere_octet_cu_octet                  ; raiau scaderea octet cu octet

imprumutare:

        sub ax, word 0x100                          ; pastrez doar partea care incape pe un cotet
        inc cx                                      ; incremrntez carry-u;    
        jmp actualizare_dupa_imprumut
        
iteratie2:

        xor edx, edx
        
parcurgere_octeti:                                  ; scad din octetii numarului mare pe cei ai umarului mic

        cmp edx, [esi + 4]
        je  afara
        
        xor eax, eax
        xor ebx, ebx
        
        mov al, byte [edi + 8 + edx]                ; octetii de pe pozitiile corespunzatoare din cele 2 numere
        mov bl, byte [esi + 8 + edx]        
        
        cmp bl, byte al
        jc  imprumut                                ; daca am carry din scaderea precedenta, ma imprumut la octetul mai semnificativ
        
        sub bl, byte al                             ; scad octetii de pe poztiile curente, daca nu am carry
                
revin:

        mov [edi + 8 + edx], byte bl                ; revin si actualizez octetul ce va fi pus in rezultat
        add edx, 1
        jmp parcurgere_octeti
               
imprumut:

        sub bl, al                                  ; scad octetii de pe pozitiile curente
        mov cl, byte [esi + 8 + edx + 1]            ; scad 1 din octetul mai smenificativ
        sub cl, 1
        mov [esi + 8 + edx + 1], cl                 ; mut octetul mai semnificativ la locul lui dupa imprumut
        jmp revin                  
                                                                                    
primul_e_negativ:

        mov ecx, dword [edi + 4]                    ; numarul de octeti ai primului numar
        mov edx, dword [esi + 4]                    ; numarul de octeti ai celui de-al 2 lea numar
        
        cmp ecx, dword edx                                ; compar numarul de octeti pe care sunt reprezentate cele 2 numere        
        jl  primul_e_mic
        
        cmp ecx, dword edx
        jg al_doilea_e_mic
        
        xor eax, eax
        xor ebx, ebx
        
        dec edx
        jmp comparare_octet_cu_octet
                
comparare_octet_cu_octet:

        cmp edx, dword 0                        ; daca am epuizat toti octetii, numerele sunt egale si scad octet cu octet
        jl  numerele_sunt_egale
        
        mov al, byte [edi + 8 + edx]            ; compar octetii de pe pozitiile corespunzatoare
        mov bl, byte [esi + 8 + edx]
        
        cmp al, byte bl                        ; daca am gasit o inegalitate sar la label-ul corespunzator
        jg  al_doilea_e_mic
        
        cmp al, byte bl
        jl  primul_e_mic
        
        dec edx                                 ; daca octetii sunt egali, ii compar pe urmatorii cei mai semnificativi
        jmp comparare_octet_cu_octet
                
numerele_sunt_egale:                            ; daca numerele sunt egale fac rezultatul sa fie 0

        mov [edi], dword 0                      ; modific semnul
        mov [edi + 4], dword 1                  ; modfici lungimea rezultatului
        mov [edi + 8], byte 0                   ; modific cel mai nesemnificativ octet
        
        jmp afara                               ; ies in functie
                
primul_e_mic:                                   ; fac acelasi lucru ca si in cazul cand al doilea e mai mic, numar mare minus numar mic

        mov  [edi], dword 0
        jmp  iterare_octeti
        
al_doilea_e_mic:

        mov [edi], dword 0xFFFFFFFF               
        jmp iterare_octeti
                
iterare_octeti:

        xor edx, edx
        xor ecx, ecx
        cmp edx, dword [esi + 4]
        jl  parcurgere_octeti_primul_negativ  
           
parcurgere_octeti_primul_negativ:                   ; parcurg octetii si scad octet cu octet

        cmp edx, dword [esi + 4]
        je  verifica_dimensiunea
        
        xor eax, eax
        xor ebx, ebx
        
        mov al, byte [edi + 8 + edx]
        mov bl, byte [esi + 8 + edx]
        
        sub bx, ax
        sub bx, cx
        xor ecx, ecx
        
        cmp bx, word 0
        jl  imprumut_primul_negativ
 
revenire:

        mov [edi + 8 + edx], byte bl
        
        inc edx
        
        jmp parcurgere_octeti_primul_negativ
                       
imprumut_primul_negativ:                        ; efectuez imrpumutul

        inc cx
        
        neg bx
        
        jmp revenire      
                 
verifica_dimensiunea:                           ; calculez noua dimensiunea numarul 1 dupa operatie

        mov edx, dword [edi + 4]
        
        cmp edx, 1
        je afara
        
        dec edx
        
        cmp [edi + 8 + edx], byte 0
        jne  afara
        
micsorez:                                       ; micsorez daca dupa operatie am unu numarul cu 0-uri in fata

        dec dword [edi + 4]
        
        jmp verifica_dimensiunea        
        
        jmp afara
                
inmultire:

        xor edx, edx
        
parcurgere_octeti_param2:

        cmp edx, dword [esi + 4]
        jge verifica_carry_transport
        
        xor ecx, ecx
        
parcurgere_octeti_param1:
                              
        cmp ecx, dword [edi + 4]
        jge verifica_carry_transport            ; verific daca mai am la final carry sau transport
                 
        xor eax, eax
        xor ebx, ebx
                                                  
        mov al, byte [transport]
        mov bl, byte [mycarry]
        
        add ax, word bx                         ; am adunat carry + transport
        
        mov [mycarry], byte 0
        mov [transport], byte 0
        
        xor ebx, ebx
        
        mov bl, byte [rezultat + ecx + edx]
        add ax, word bx                         
        mov bx, word ax                         ; in bx am carry, transport s-i octetul de pana acum
        
        xor eax, eax
        mov al, byte [edi + 8 + ecx]            ; efectuez inmultirea
        mul byte [esi + 8 + edx]

        mov [transport], byte ah                ; pastrez transportul curent
        
        and ax, word 0xFF
        add bx, word ax                         ; adun si partea inferioara
        
        mov ax, bx
        
        and ax, 0xFF00                          ; verifica daca am obtinut o valoare care nu incape doar pe un octet
        cmp ax, 0
        jne actualizare_mycarry
        
revenire_din_actualizare:

        mov [rezultat + ecx + edx], byte bl     ; mut suma adunata pana acum
        inc ecx                                 ; trec la octetul urmator din primul numar
        jmp parcurgere_octeti_param1            ; reiau parcurgerea primului numar
        
actualizare_mycarry:

         mov ax, word bx                        ; pun in carry de cate ori e mai mare ax fata de 0x100, catul lor care e chiar valoarea lui ah
         mov [mycarry], byte ah
                   
         and bx, 0xFF                           ; pastrez doar partea inferioara
         jmp revenire_din_actualizare           ; revin pentru a actualiza rezultatul
                                       
verifica_carry_transport:                       ; verific la final daca am carry si tranpsort

        xor eax, eax
        xor ebx, ebx
        
        mov al, byte [mycarry]                  ; adun carry-ul si transportul
        mov bl, byte [transport]

        mov [mycarry], byte 0                   ; restez transportul si carry-ul
        mov [transport], byte 0
        
        add ax, word bx
        
        cmp ax, word 0
        jne am_transport_in_plus                ; daca rezultatul e mai amre decat 0 se transporta
        
        inc edx
        cmp edx, dword [esi + 4]
        jl  parcurgere_octeti_param2
        
        jmp pregatire_mutare                    ; pregatesc sa mut toul in primul parametru
        
am_transport_in_plus:

        mov bx, ax                              ; pastrez doar partea inferioara
        and bx, 0xFF00                          ; poate dupa ce adun carry-ul si tranpsortul e posibil sa am ramas inca un carry        
        cmp bx, word 0
        jne mai_adun

revenire_din_aunare_trasport:                   
                
        add [rezultat + ecx + edx], byte al     ; pun octetul corespunzator in rezultat
        inc edx
        jmp parcurgere_octeti_param2       
             
mai_adun:

        inc byte [rezultat + ecx + edx + 1]
        jmp revenire_din_aunare_trasport
            
pregatire_mutare:                               ; mut octetii din reultat in numarul 1
       
       mov eax, dword [edi + 4]
       add eax, dword [esi + 4]

       mov [edi + 4], dword eax                 ; aflu noua lungime a nuamrului 1
      
       cmp [rezultat + eax + 1], byte 0         ; daca octetul de dupa ultimul e 0 atunci nu mai lungesc, atfle maresc dimensiunea numarului 1
       jne mai_lungesc
       jmp mutare                               ; mut octetii in numarul 1
       
mai_lungesc:

       inc eax
       jmp mutare
              
mutare:                                         ; parcurg octetii din rezultat si ii mut in numarul 1
         
       cmp eax, 0
       jl  afara_inmultire
       
       mov bl, byte [rezultat + eax]            ; mut octet cu octet
       mov [edi + 8 + eax], byte bl
       dec eax
       jmp mutare
               
afara_inmultire:                                ; actualizez semnul corespunzator dupa terminarea inmultirii

       mov eax, dword [esi] 
       xor [edi], dword eax
                                                 
afara:                       
                
       leave                   
       ret
