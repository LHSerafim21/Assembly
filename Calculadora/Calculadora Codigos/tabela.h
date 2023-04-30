#pragma once

//Opera��es que usam 1 char na string de exibi��o
#define _DIV 'a' //precedencia 2
#define _MUL 'b' //precedencia 2
#define _SUB 'c' //precedencia 1
#define _ADD 'd' //precedencia 1
#define _OP  'e' 
#define _CP  'f'
#define _XPOWY 'g' //precedencia 3
#define _FAT	'h' //precedencia 4

//Opera��es que usam 2 char na string de exibi��o
#define _POW2	'i'
#define _PI	'j'

//Opera��es que usam 3 char na string de exibi��o
#define _EXP 'k'
#define _TG	'l'
#define _LN	'm'


//Opera��es que usam 4 char na string de exibi��o
#define _SIN 'n'
#define _COS 'o'
#define _LOG 'p'
#define _NROOT 'q'

//Opera��es que usam 5 char na string de exibi��o
#define _SQRT 'r'

//Opera��es que usam 6 char na string de exibi��o
#define _ARCTG 's'
//Opera��es que usam 7 char na string de exibi��o
#define _ARCCOS 't'
#define _ARCSIN 'u'

//Tipos de tokens
#define _OPERADOR 1
#define _ABRIR_PARENTESES 2
#define _FECHAR_PARENTESES 3
#define _NUMERO 4
#define _FUNCAO 5
#define _NUMEROSINAL 6


#define euler 2.7182818284
#define CONSTPI	3.14159265359