 LOAD   quant      ; 3   26
 CMP    zero       ; 8   27
 JZ     final:      ; 9   25
 IN                 ; 2
 STORE  100        ; 4   100
 IN                 ; 2
 STORE  101       ; 4   101
 LOAD   100       ; 3   100
 SUB    101       ; 6   101
 OUT                ; 1
 LOAD   quant     ; 3   26
 SUB   um        ; 6   28
 STORE quant     ; 4   26
 JMP   INICIO:  ; 7   0
final:
	 HALT 	 ; 0  
              
 quant=3            ; 3
 zero=0             ; 0
 um=1         ; 1

