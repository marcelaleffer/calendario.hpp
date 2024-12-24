#include "calendario.hpp"

void mostrarMenu() {
    cout << "\n-------------- MENU --------------\n";
    cout << "1. Cadastrar nova disciplina\n";
    cout << "2. Cadastrar novo evento em uma disciplina\n";
    cout << "3. Imprimir histórico geral de uma disciplina\n";
    cout << "4. Imprimir histórico de provas de uma disciplina\n";
    cout << "5. Imprimir histórico de trabalhos de uma disciplina\n";
    cout << "6. Imprimir histórico de seminários de uma disciplina\n";
    cout << "7. Buscar eventos de uma mês\n";
    cout << "8. Salvar disciplinas em arquivo\n";
    cout << "9. Sair\n";
    cout << "Escolha uma opção: ";
}

int main() {
    // variavél que define nome do arquivo
    string enderecoArq = "disciplinas.txt"; 
    
    //vetor que armazena todos os objetos de Disciplina em disciplinas
    vector<Disciplina> disciplinas = recuperarDisciplinas(enderecoArq); 
    
    //MENU----------------------------------------------------------------
    int opcao;

    //executa enquanto for diferente de 9 (opção para sair)
    do {
        mostrarMenu(); 
        cin >> opcao; 
        cin.ignore(); // Limpar buffer
        cout<<"\n\n";

        switch (opcao) {
            case 1: { // Cadastrar disciplina
                Disciplina novaDisciplina = cadastrarDisciplina(); 
                disciplinas.push_back(novaDisciplina); // guarda novaDisciplina no vetor disciplinas
                break;
            }
            case 2: { // Cadastrar evento
                int index;
                imprimirDisciplinas(disciplinas); // Mostra as disciplinas já cadastradas
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                
                // número digitado por usuário inicia em 1 enquanto indíce do vetor inicia em 0
                // por isso é necessário realizar o decremento
                index --;
                
                if (index >= 0 && index < disciplinas.size()) {
                    cadastrarEvento(disciplinas[index]);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 3: { // Histórico Geral Disciplina
                int index;
                imprimirDisciplinas(disciplinas);
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                index --;
                
                if (index >= 0 && index < disciplinas.size()) {
                    imprimirHistoricoDisciplina(disciplinas[index]);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 4: { // Histórico Provas Disciplina
                int index;
                imprimirDisciplinas(disciplinas);
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                index --;
                
                if (index >= 0 && index < disciplinas.size()) {
                    imprimirHistoricoProvaDisciplina(disciplinas[index]);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 5: { // Histórico trabalhos disciplina
                int index;
                imprimirDisciplinas(disciplinas);
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                index --;
                
                if (index >= 0 && index < disciplinas.size()) {
                    imprimirHistoricoTrabalhoDisciplina(disciplinas[index]);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 6: { // Histórico Seminários Disciplina
                int index;
                imprimirDisciplinas(disciplinas);
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                index --;
                
                if (index >= 0 && index < disciplinas.size()) {
                    imprimirHistoricoSeminarioDisciplina(disciplinas[index]);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 7: { // Buscar eventos mês na disciplina
                int index;
                imprimirDisciplinas(disciplinas);
                cout << "\nEscolha a disciplina: \n";
                cin >> index;
                cin.ignore(); // Limpar buffer
                cout<<"\n\n";
                index --;
                
                cout<<"# BUSCAR EVENTOS DE UM MÊS\n";
                if (index >= 0 && index < disciplinas.size()) {
                    int mes, ano;
                    bool mesValido=false, anoValido = false;
                    
                    while(!mesValido){
                        cout << "Digite um mês (1 a 12)? ";
                        cin >> mes;
                        mesValido = validaMes(mes);
                    }
                    
                    while(!anoValido){
                        cout << "Digite o ano: ";
                        cin >> ano;
                        anoValido = validaAno(ano);
                    }
                    
                    buscarEventosMensaisDisciplina(disciplinas[index], mes, ano);
                } else {
                    cout << "Disciplina não cadastrada.\n";
                }
                break;
            }
            case 8: { // Gerar relatório
            
                // for itera sobre o vetor disciplinas que contém todas as disciplinas cadastradas
                //auto& é usada para criar uma referência a cada elemento do vetor -> disciplina
                for (auto& disciplina : disciplinas) {
                    registrarDisciplina(enderecoArq, disciplina);
                }
                cout << "Disciplinas salvas com sucesso.\n";
                break;
            }
            case 9:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opção inválida. Tente novamente.\n\n";
                mostrarMenu();
                break;
        }
    } while (opcao != 9);

    return 0;
}
