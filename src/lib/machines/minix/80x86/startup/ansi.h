#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow

/* esto deber�a hacerlo tcc, pero lo hacemos nosotros por si acaso,
   ya se quejar� si no le gusta; es importante porque las caracter�sticas
   ansi, que se seleccionan con la definici�n _ANSI, se ponen cuando
   esta definici�n vale 1 (ver /usr/include/ansi.h) */

#define __STDC__	1

/* todo lo siguiente es absolutamente necesario, ya que lo hace el ACD,
   y las macros _EM_*SIZE se utilizan expl�citamente en muchas cabeceras,
   tanto ansi como posix */

#define __minix		1
#define __i386		1

#define _EM_WSIZE	4
#define _EM_PSIZE	4
#define _EM_SSIZE	2
#define _EM_LSIZE	4
#define _EM_FSIZE	4
#define _EM_DSIZE	8

/* esto se necesita en algunos sitios, pero s�lo se asigna (en minix/config.h)
   si __ACK__ est� definido, y ese no es nuestro caso, as�que tenemos que
   hacerlo manualmente */

#define _WORD_SIZE	_EM_WSIZE

/* finalmente, recordemos que estos ficheros startup ser�n los que usar� el
   compilador para predefinir macros en la instalaci�n final, as� que conviene
   disponer de estas otras dos macros */

#define unix		1
#define __unix		1
