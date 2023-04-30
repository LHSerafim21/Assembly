#pragma once
class AssemblyFunctions
{
public:

	AssemblyFunctions()
	{
	}

	~AssemblyFunctions()
	{
	}

	float soma(float a, float b) {
		__asm {
			finit
			fld a
			fld b
			faddp st(1),st(0)
			fstp a
		}
		return a;
	}

	float subtracao(float a, float b) {
		__asm {
			finit
			fld a
			fld b
			fsubp st(1), st(0)
			fstp a
		}
		return a;
	}

	float divisao(float a, float b) {
		__asm {
			finit
			fld a
			fld b
			fdivp st(1), st(0)
			fstp a
		}
		return a;
	}

	float multiplicacao(float a, float b) {
		__asm {
			finit
			fld a
			fld b
			fmulp st(1), st(0)
			fstp a
		}
		return a;
	}

	float sin(float a,int isRadiano) {
		__asm {
			finit
			fld a
			mov eax, isRadiano
			sub eax, 1
			jz _GRAU
			JMP _RADIANO
			
			_GRAU:
				call AssemblyGrauRaidano
				JMP _RADIANO
			
			_RADIANO:
				fsin
				fstp a
		}
		return a;
	}

	float cos(float a,int isRadiano) {
		__asm {
			finit
			fld a
			mov eax, isRadiano
			sub eax, 1
			jz _GRAU
			JMP _RADIANO

			_GRAU :
				call AssemblyGrauRaidano
				JMP _RADIANO

			_RADIANO :

				fcos
				fstp a
		}
		return a;
	}

	float tg(float a,int isRadiano){
		__asm {
			finit
			fld a
			mov eax, isRadiano
			sub eax, 1
			jz _GRAU
			JMP _RADIANO

			_GRAU :
				call AssemblyGrauRaidano
				JMP _RADIANO

			_RADIANO :
				
				fsincos
				fdivp st(1), st(0)
				fstp a
		}
		return a;
	}

	float sqrt(float a) {
		__asm {
			finit
			fld a
			fsqrt
			fstp a
		}
		return a;
	}

	float xElevadoAoQuadrado(float a) {
		__asm {
			finit
			fld a
			fld a
			fmulp st(1), st(0)
			fstp a
		}
		return a;
	}


	float RaizNdeX(float x, float n) {
		__asm {
			finit
				fld1
				fld n
				fdiv
				fstp n
		}

		x = xElevadoAy(x, n);
		return x;
	}

	float log(float x,float a) {
		__asm {
			finit
				fld1
				fld a
				fyl2x
				fld1
				fdiv st, st(1)
				fld1
				fld x
				fyl2x
				fmul
				fstp x
		}

		return x;
	}

	float xElevadoAy(float x, float y) {
		__asm {
			finit
				fld y
				fld1
				fld x
				fyl2x
				fmul
				fld st
				frndint
				fsub st(1), st
				fxch
				f2xm1
				fld1
				fadd
				fscale
				fstp x
		}
		return x;
}

	float fatorial(int x) {
		float result;
		__asm {
				finit
					fld1
					fldz
					mov ecx, x

					_loop :
					fld1
					faddp st(1), st(0)
					fmul st(1), st(0)

					dec ecx
					jnz _loop

					fstp x
					fstp result
			}
			return result;
	}

	float arctg(float x, int isRadiano) {
		__asm {
			finit
				fld x
				fld1
				fpatan
				mov eax, isRadiano
				sub eax, 1
				jz _GRAU
				jmp _RADIANO
				
				_GRAU:
					call AssemblyRadianoGrau
					JMP _RADIANO

				_RADIANO:
					fst x
		}
		return x;
	}

	float arcsin(float x, int isRadiano) {
		__asm {
			finit
				fld x
				fld x
				fmulp st(1), st(0)
				fld1
				fld st(1)
				fsubp st(1), st(0)
				fdivp st(1), st(0)

				fsqrt
				fld1
				fpatan

				mov eax, isRadiano
				sub eax, 1
				jz _GRAU
				jmp _RADIANO

				_GRAU :
			call AssemblyRadianoGrau
				JMP _RADIANO

				_RADIANO :
			fst x
		}
		return x;
	}

	float arccos(float x, int isRadiano) {
		int y;
		__asm {
			
			finit
				fld1
				fld x
				fld x
				fmulp st(1), st(0)
				fst y
				fsubp st(1), st(0)
				fld y
				fdivp st(1), st(0)
				fsqrt
				fld1
				fpatan

				mov eax, isRadiano
				sub eax, 1
				jz _GRAU
				jmp _RADIANO

				_GRAU :
			call AssemblyRadianoGrau
				JMP _RADIANO

				_RADIANO :
			fst x
		}
		return x;
	}

	void AssemblyGrauRaidano() {
		float constante = 180;
		__asm {
			fldpi
			fmulp st(1), st(0)
			fld constante
			fdivp st(1), st(0)
		}
		return;
	}

	void AssemblyRadianoGrau() {
		float constante = 180;
		__asm {
			fld constante
			fmulp st(1), st(0)
			fldpi
			fdivp st(1), st(0)
		}
	}
};

