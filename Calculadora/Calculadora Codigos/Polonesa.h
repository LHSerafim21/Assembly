#pragma once
#include "tabela.h"
#include <stack>
#include <queue>
#include <vector>
#include "AssemblyFunctions.h"
#include <string>

using namespace std;

class Polonesa
{

private: 

public:

	Polonesa()
	{
	}

	~Polonesa()
	{
	}

	vector<string, allocator<string>> conversaoNotacao(vector<string, allocator<string>> *expressaoOriginal) {
		int tipoToken;
		vector<string, allocator<string>> pilhaAuxiliar;
		vector<string, allocator<string>> filaSaida;
		string tokenAtual,topoPilha;
		unsigned int posiAtual = 0;

		while (posiAtual < expressaoOriginal->size()) {
			tokenAtual = expressaoOriginal->at(posiAtual);
			posiAtual++;
			if (tokenAtual.empty() == true)continue;
			tipoToken = getTipoToken(tokenAtual);
			
			switch (tipoToken) {
			case _NUMERO:
				if (tokenAtual.at(0) == _PI)tokenAtual = to_string(CONSTPI);
				filaSaida.push_back(tokenAtual);
				break;
			case _NUMEROSINAL:
				topoPilha = _OP;
				pilhaAuxiliar.push_back(topoPilha);
				pilhaAuxiliar.push_back(tokenAtual.substr(1));
				break;
			case _OPERADOR: 
				if (pilhaAuxiliar.empty() == true)pilhaAuxiliar.push_back(tokenAtual);
				else {
					while (pilhaAuxiliar.empty() == false) {
						topoPilha = pilhaAuxiliar.back();
						if (topoPilha.front() == '(')break;
						if (tokenAtual.front() == '^' && precedencia(tokenAtual, topoPilha) > 0) {
							filaSaida.push_back(topoPilha);
							pilhaAuxiliar.pop_back();
						}else if (precedencia(tokenAtual, topoPilha) >= 0) {
							filaSaida.push_back(topoPilha);
							pilhaAuxiliar.pop_back();
						}
						else break;
					}
					pilhaAuxiliar.push_back(tokenAtual);
				}
				break;
			case _FUNCAO:
				pilhaAuxiliar.push_back(tokenAtual);
				tokenAtual = _OP;
				pilhaAuxiliar.push_back(tokenAtual);
				break;
			case _ABRIR_PARENTESES:
				pilhaAuxiliar.push_back(tokenAtual);
				break;
			case _FECHAR_PARENTESES: 
				topoPilha = pilhaAuxiliar.back();
				while (topoPilha.front() != _OP) {
					filaSaida.push_back(topoPilha);
					pilhaAuxiliar.pop_back();
					topoPilha = pilhaAuxiliar.back();
				}
				pilhaAuxiliar.pop_back();
				if (pilhaAuxiliar.empty() == true)break;
				topoPilha = pilhaAuxiliar.back();
				if (getTipoToken(topoPilha) == _FUNCAO) {
					filaSaida.push_back(topoPilha);
					pilhaAuxiliar.pop_back();
				}
				break;

			}
		}

		while (pilhaAuxiliar.empty() == false) {
			filaSaida.push_back(pilhaAuxiliar.back());
			pilhaAuxiliar.pop_back();
		}
		
		return filaSaida;
	}

	//menor que zero 'a' possui maior precedencia
	//igual a zero  'a' e 'b' possuem a mesma precedencia
	//maior que zero 'b' possui maior precedencia
	int precedencia(string a, string b) {
		int precedenciaA, precedenciaB;
		char operador;
		
		operador = a.front();
		if (operador == _ADD || operador == _SUB)precedenciaA = 1;
		else if (operador == _MUL || operador == _DIV)precedenciaA = 2;
		else if (operador == _XPOWY || operador == _POW2) precedenciaA = 3;
		else if (operador == _FAT)precedenciaA = 4;

		operador = b.front();
		if (operador == _ADD || operador == _SUB)precedenciaB = 1;
		else if (operador == _MUL || operador == _DIV)precedenciaB = 2;
		else if (operador == _XPOWY) precedenciaB = 3;
		else if (operador == _FAT)precedenciaB = 4;

		return precedenciaB - precedenciaA;
	}

	int getTipoToken(string tokenAtual) {
		char primeiroCharString = tokenAtual.at(0);

		if (primeiroCharString == '(')return _NUMEROSINAL;

		if ( (primeiroCharString >= '0' && primeiroCharString <= '9')
			|| primeiroCharString == _PI || primeiroCharString == '-')return _NUMERO;

		if (primeiroCharString == _OP)return _ABRIR_PARENTESES;

		if (primeiroCharString == _CP)return _FECHAR_PARENTESES;

		if ((primeiroCharString >= 'a' && primeiroCharString <= 'i'))return _OPERADOR;

		return _FUNCAO;
	}

	string calcularPolonesa(vector<string, allocator<string>> filaExp,int isRadiano) {
		vector<string, allocator<string>> pilhaDeCalculo;
		string tokenAtual,operadorA,operadorB;
		AssemblyFunctions operacoes;
		int tipoToken;

		while (filaExp.empty() == false) {
			tokenAtual = filaExp.front();
			filaExp.erase(filaExp.begin());
			tipoToken = getTipoToken(tokenAtual);
			switch (tipoToken) {
			case _NUMERO:
				pilhaDeCalculo.push_back(tokenAtual);
				break;
			case _OPERADOR:
				if (tokenAtual.front() != _FAT && tokenAtual.front() != _POW2){
					operadorB = pilhaDeCalculo.back();
					pilhaDeCalculo.pop_back();
				}
			case _FUNCAO:
				if ((tokenAtual.front() == _NROOT || tokenAtual.front() == _XPOWY) && tipoToken == _FUNCAO) {
					operadorB = pilhaDeCalculo.back();
					pilhaDeCalculo.pop_back();
				}
				operadorA = pilhaDeCalculo.back();
				pilhaDeCalculo.pop_back();
				
				switch (tokenAtual.front()) {					
					case _ADD:
						pilhaDeCalculo.push_back(to_string(operacoes.soma(stof(operadorA), stof(operadorB))));
						break;
					case _MUL:		
						pilhaDeCalculo.push_back(to_string(operacoes.multiplicacao(stof(operadorA), stof(operadorB))));
						break;
					case _SUB:
						pilhaDeCalculo.push_back(to_string(operacoes.subtracao(stof(operadorA), stof(operadorB))));
						break;
					case _DIV:
						pilhaDeCalculo.push_back(to_string(operacoes.divisao(stof(operadorA), stof(operadorB))));
						break;
					case _POW2:
						pilhaDeCalculo.push_back(to_string(operacoes.xElevadoAoQuadrado(stof(operadorA))));
						break;
					case _XPOWY:
						pilhaDeCalculo.push_back(to_string(operacoes.xElevadoAy(stof(operadorA), stof(operadorB))));
						break;
					case _FAT:
						pilhaDeCalculo.push_back(to_string(operacoes.fatorial(stof(operadorA))));
						break;
					case _EXP:
						pilhaDeCalculo.push_back(to_string(operacoes.xElevadoAy(euler, stof(operadorA))));
						break;
					case _TG:
						pilhaDeCalculo.push_back(to_string(operacoes.tg(stof(operadorA), isRadiano)));
						break;
					case _LN:
						pilhaDeCalculo.push_back(to_string(operacoes.log(stof(operadorA), euler)));
						break;
					case _SIN:
						pilhaDeCalculo.push_back(to_string(operacoes.sin(stof(operadorA),isRadiano)));
						break;
					case _COS:
						pilhaDeCalculo.push_back(to_string(operacoes.cos(stof(operadorA), isRadiano)));
						break;
					case _LOG:
						pilhaDeCalculo.push_back(to_string(operacoes.log(stof(operadorA),10)));
						break;
					case _NROOT:
						pilhaDeCalculo.push_back(to_string(operacoes.RaizNdeX(stof(operadorA),stof(operadorB))));
						break;
					case _SQRT:
						pilhaDeCalculo.push_back(to_string(operacoes.sqrt(stof(operadorA))));
						break;
					case _ARCTG:
						pilhaDeCalculo.push_back(to_string(operacoes.arctg(stof(operadorA), isRadiano)));
						break;
					case _ARCCOS:
						pilhaDeCalculo.push_back(to_string(operacoes.arccos(stof(operadorA), isRadiano)));
						break;
					case _ARCSIN:
						pilhaDeCalculo.push_back(to_string(operacoes.arcsin(stof(operadorA), isRadiano)));
						break;
				}
				break;
			}
		}
		return pilhaDeCalculo.back();
		
	}

};

