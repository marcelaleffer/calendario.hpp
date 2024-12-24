#include "calendario.hpp"

// Função para cadastrar uma nova disciplina
Disciplina cadastrarDisciplina() {
    Disciplina disciplina;
    cout<<"-------------- CADASTRAR DISCIPLINA --------------"<<endl;
    cout << "Nome da disciplina: ";
    getline(cin, disciplina.nomeDisciplina);
    cout << "Nome do professor: ";
    getline(cin, disciplina.nomeProfessor);
    return disciplina;
}

// Função para cadastrar um novo evento
Evento cadastrarEvento(Disciplina& disciplina) {
    Evento evento;
    bool dataValida = false;
    cout<<"-------------- CADASTRAR EVENTO --------------"<<endl;
    
    while(!dataValida){
        cout << "Dia: ";
        cin >> evento.dia;
        
        cout << "Mes: ";
        cin >> evento.mes;
        
        cout << "Ano: ";
        cin >> evento.ano;
    
        dataValida = validaData(evento.dia, evento.mes, evento.ano);
    }
    cout<<dataValida<<endl;
    
    cout << "Opcao (1: Prova, 2: Trabalho, 3: Seminario, 4: Outro): ";
    cin >> evento.opcao;
    cin.ignore();  // Limpar buffer
    cout << "Conteudo: ";
    getline(cin, evento.conteudo);
    
    disciplina.eventos.push_back(evento);
    
    switch (evento.opcao) {
        case 1:
            disciplina.historicoProvasDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplinaOpcao.push_back(evento.opcao);
            break;
        case 2:
            disciplina.historicoTrabalhosDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplinaOpcao.push_back(evento.opcao);
            break;
        case 3:
            disciplina.historicoSeminariosDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplinaOpcao.push_back(evento.opcao);
            break;
        default:
            disciplina.historicoDisciplina.push_back(evento.conteudo);
            disciplina.historicoDisciplinaOpcao.push_back(evento.opcao);
            break;
    }
    
    return evento;
}

// Função para apresentar as  Disciplinas cadastradas 
void imprimirDisciplinas(vector<Disciplina> disciplinas){
    cout<<"-------------- DISCIPLINAS CADASTRADAS --------------\n";
    for(int i = 0; disciplinas.size() > i ; i++){
        cout<<i+1<<". "<<disciplinas[i].nomeDisciplina<<endl;
    }
}

// Funções para imprimir os históricos da disciplina
void imprimirHistoricoDisciplina(Disciplina& disciplina) {
    cout << "# HITÓRICO DA DISCIPLINA GERAL: " << disciplina.nomeDisciplina << ":\n";
    string tipoEvento;
    
    for(int i=0; disciplina.historicoDisciplina.size() > i; i++){
        switch(disciplina.historicoDisciplinaOpcao[i]){
            case 1:
                tipoEvento = "Prova";
                break;
            case 2:
                tipoEvento = "Trabalho";
                break;
            case 3:
                tipoEvento = "Seminário";
                break;
            default:
                tipoEvento = "Outros";
                break;
        }
        cout<<"[ "<<tipoEvento<<" ] "<<disciplina.historicoDisciplina[i]<<"\n";
    }
}

void imprimirHistoricoProvaDisciplina(Disciplina& disciplina) {
    cout << "# HISTÓRICO DE PROVAS DA DISCIPLINA: " << disciplina.nomeDisciplina << ":\n";
    for (const auto& item : disciplina.historicoProvasDisciplina) {
        cout << "- " << item << endl;
    }
}

void imprimirHistoricoTrabalhoDisciplina(Disciplina& disciplina) {
    cout << "# HISTÓRICO DE TRABALHOS DA DISCIPLINA: " << disciplina.nomeDisciplina << ":\n";
    for (const auto& item : disciplina.historicoTrabalhosDisciplina) {
        cout << "- " << item << endl;
    }
}

void imprimirHistoricoSeminarioDisciplina(Disciplina& disciplina) {
    cout << "# HISTÓRICO DE SEMINÁRIOS DA DISCIPLINA: " << disciplina.nomeDisciplina << ":\n";
    for (const auto& item : disciplina.historicoSeminariosDisciplina) {
        cout << "- " << item << endl;
    }
}

// Função para buscar eventos no mês especificada 
void buscarEventosMensaisDisciplina(Disciplina& disciplina, int mes, int ano) {
    cout << "Eventos do mês " << mes << " do ano " << ano << " na disciplina " << disciplina.nomeDisciplina << ":\n";
    for (const auto& evento : disciplina.eventos) {
        if (evento.ano == ano && evento.mes == mes) {
            cout << "> [" << evento.dia << "/" << evento.mes << "/" << evento.ano << "] - " << evento.conteudo << endl;
        }
    }
}

// Funções de validação 
bool validaData(int dia, int mes, int ano) {
    // Verifica se o ano é válido
    if (ano < 1) {
        cout << "\nAno inválido\n\n";
        return false;
    }

    // Verifica se o mês é válido
    if (mes < 1 || mes > 12) {
        cout << "\nMês inválido\n\n";
        return false;
    }

    // Vetor com o número de dias em cada mês
    vector<int> diasPorMes = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ajusta para ano bissexto
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasPorMes[1] = 29; // Fevereiro tem 29 dias em ano bissexto
    }

    // Verifica se o dia é válido
    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        cout << "\nDia inválido\n\n";
        return false;
    }

    return true;
}

bool validaMes(int mes){
    bool valido = true;
    if(mes > 12 || mes < 1){
        cout<<"\nMês inválido\n\n";
        valido = false;
    }
    return valido;
}

bool validaAno(int ano){
    bool valido = true;
    if(ano < 1){
        cout<<"\nAno inválido\n\n";
        valido = false;
    }
    return valido;
}

// Função para registrar uma disciplina em um arquivo de texto
void registrarDisciplina(const string& enderecoArq, Disciplina& disciplina) {
    string tipoEvento;
    
    // Abre o arquivo especificado pelo endereço -> enderecoArq
    ofstream arquivo(enderecoArq, ios::app);
    
    // Verifica se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }
    
    // Escreve o nome da disciplina e o nome do professor no arquivo
    arquivo << disciplina.nomeDisciplina << "," << disciplina.nomeProfessor << endl;
    //arquivo << "DISCIPLINA: " << disciplina.nomeDisciplina << "| PROFESSOR: " << disciplina.nomeProfessor << endl;
    for (const auto& evento : disciplina.eventos) {
        
        switch(evento.opcao){
            case 1:
                tipoEvento = "Prova";
                break;
            case 2:
                tipoEvento = "Trabalho";
                break;
            case 3:
                tipoEvento = "Seminário";
                break;
            default:
                tipoEvento = "Outros";
                break;
        }
        
        //arquivo << evento.dia << "/" << evento.mes << "/" << evento.ano << "  | TIPO: " << tipoEvento << "  | CONTEÚDO: " << evento.conteudo << endl;
        arquivo << evento.dia << "," << evento.mes << "," << evento.ano << "," << evento.opcao << "," << evento.conteudo << endl;
    }
    
    //fecha arquivo;
    arquivo.close();
}

// Função para recuperar disciplinas de um arquivo de texto
vector<Disciplina> recuperarDisciplinas(const string& enderecoArq) {
    
    vector<Disciplina> disciplinas; // Vetor para armazenar as disciplinas lidas do arquivo
    ifstream arquivo(enderecoArq); // Abre o arquivo especificado para leitura
    string linha; // // Variável para armazenar cada linha lida do arquivo
    
    // Loop para ler cada linha do arquivo até o final
    while (getline(arquivo, linha)) {
        
        stringstream ss(linha); // Cria um stringstream para processar a linha atual
        string token; // Variável para armazenar cada token (campo) extraído da linha
        
        Disciplina disciplina; // Cria uma nova disciplina para armazenar os dados
        getline(ss, disciplina.nomeDisciplina, ',');
        getline(ss, disciplina.nomeProfessor, ',');
        
        // Loop para ler e processar os eventos da disciplina enquanto houver linhas não vazias
        while (getline(arquivo, linha) && !linha.empty()) {
            
            Evento evento;  // Cria um novo evento para armazenar os dados do evento atual
            stringstream ss(linha); // Cria um stringstream para processar a linha atual
            
            // Extrai cada campo do evento da linha atual
            getline(ss, token, ','); evento.dia = stoi(token);
            getline(ss, token, ','); evento.mes = stoi(token);
            getline(ss, token, ','); evento.ano = stoi(token);
            getline(ss, token, ','); evento.opcao = stoi(token);
            getline(ss, token, ','); evento.conteudo = token;
            
            // // Adiciona o evento à lista de eventos da disciplina
            disciplina.eventos.push_back(evento);
            
             // Dependendo do tipo de evento, adiciona o conteúdo aos respectivos históricos
            switch (evento.opcao) {
                case 1:
                    disciplina.historicoProvasDisciplina.push_back(evento.conteudo);
                    disciplina.historicoDisciplina.push_back(evento.conteudo);
                    break;
                case 2:
                    disciplina.historicoTrabalhosDisciplina.push_back(evento.conteudo);
                    disciplina.historicoDisciplina.push_back(evento.conteudo);
                    break;
                case 3:
                    disciplina.historicoSeminariosDisciplina.push_back(evento.conteudo);
                    disciplina.historicoDisciplina.push_back(evento.conteudo);
                    break;
                default:
                    disciplina.historicoDisciplina.push_back(evento.conteudo);
                    break;
            }
        }
        // Adiciona a disciplina lida ao vetor de disciplinas
        disciplinas.push_back(disciplina);
    }
    return disciplinas;
}
