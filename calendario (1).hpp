#ifndef CALENDARIO_HPP //  Verifica se a constante CALENDARIO_HPP não foi definida.
#define CALENDARIO_HPP // Define a constante CALENDARIO_HPP para indicar que o arquivo já foi incluído.

#include <iostream> // Biblioteca para entrada e saída padrão (como cout e cin).
#include <string> // Biblioteca que fornece a classe std::string para manipulação de cadeias de caracteres.
#include <vector> // Biblioteca que fornece a classe std::vector para manipulação de arrays dinâmicos.
#include <fstream> // Biblioteca para manipulação de arquivos, oferecendo as classes std::ifstream e std::ofstream.
#include <sstream> // Biblioteca que fornece classes para manipulação de cadeias de caracteres como fluxos de entrada/saída (útil para conversões de tipos, como std::stringstream).

using namespace std;

struct Evento {
    int dia, mes, ano, opcao;
    string conteudo;
};

struct Disciplina {
    string nomeDisciplina, nomeProfessor;
    vector<Evento> eventos;
    vector<string> historicoDisciplina;
    vector<int> historicoDisciplinaOpcao;
    vector<string> historicoProvasDisciplina;
    vector<string> historicoTrabalhosDisciplina;
    vector<string> historicoSeminariosDisciplina;
};

// Funções de cadastro
Disciplina cadastrarDisciplina();
Evento cadastrarEvento(Disciplina& disciplina);

// Funções para validação
bool validaData(int dia, int mes, int ano);
bool validaDia(int dia);
bool validaMes(int mes);
bool validaAno(int ano);

// Funções de impressão de históricos
void imprimirDisciplinas(vector<Disciplina> disciplinas);
void imprimirHistoricoDisciplina(Disciplina& disciplina);
void imprimirHistoricoProvaDisciplina(Disciplina& disciplina);
void imprimirHistoricoTrabalhoDisciplina(Disciplina& disciplina);
void imprimirHistoricoSeminarioDisciplina(Disciplina& disciplina);

// Funções de busca de eventos e relatórios
void buscarEventosMensaisDisciplina(Disciplina& disciplina, int mes, int ano);

// Funções de arquivo

void registrarDisciplina(const string& enderecoArq, Disciplina& disciplina);
// - const -> garante a não modificação do enderecoArq dentro da função
// - & para passar a referência e não gerar uma nota cópia da string

vector<Disciplina> recuperarDisciplinas(const string& enderecoArq);

#endif // encerra a proteção contra inclusão múltipla do arquivo de cabeçalho
