; { dg-do assemble { target epiphany*-*-* } }

add64         r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
add64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
sub64         r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
sub64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
and64         r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
and64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
orr64         r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
orr64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
eor64         r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
eor64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
asr64         r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
asr64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
lsr64         r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
lsr64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
lsl64         r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
lsl64.l       r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }

fmax64        r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmax64.l      r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fadd64        r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fadd64.l      r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fsub64        r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fsub64.l      r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmul64        r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmul64.l      r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmadd64       r11,r20,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmadd64.l     r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmsub64       r10,r20,r31        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
fmsub64.l     r10,r21,r30        ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }

; ldr/str shortregs
ldrD          r3,[r2,r0]         ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
ldrD          r2,[r1,r3]         ; legal
strD          r3,[r2,r0]         ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
strD          r2,[r1,r3]         ; legal

; ldr / str
ldrD          r21,[r20,r30]      ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
ldrD          r10,[r21,r31]      ; legal
ldrD.l        r21,[r20,r30]      ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
ldrD.l        r10,[r21,r31]      ; legal
strD          r21,[r20,r30]      ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
strD          r10,[r21,r31]      ; legal
strD.l        r21,[r20,r30]      ; { dg-error "Error: instruction requires even:odd register pair\\(s\\)" }
strD.l        r10,[r21,r31]      ; legal
