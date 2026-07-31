#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>

//============================================================
// HUDItem
// -----------------------------------------------------------
// Representa um elemento de texto pertencente ao HUD.
//
// Cada item possui:
//
// - Um identificador utilizado pelo HUDManager.
// - Um rótulo utilizado na apresentação do valor.
// - Um objeto sf::Text responsável pela renderização.
//
// A estrutura permite que o HUDManager gerencie diferentes
// elementos de interface de forma genérica, sem precisar criar
// uma variável específica para cada informação exibida.
//============================================================

struct HUDItem
{
    // Texto utilizado como identificação/descrição do elemento.
    std::string Label;

    // Objeto responsável pela representação visual do elemento.
    std::unique_ptr<sf::Text> Text;
};


//============================================================
// HUDManager
// -----------------------------------------------------------
// Responsável pelo gerenciamento e renderização das informações
// apresentadas no HUD (Heads-Up Display) do jogo.
//
// O HUDManager não é responsável por calcular ou armazenar os
// dados reais do jogo. Ele recebe valores dos demais sistemas e
// cuida apenas de sua apresentação visual.
//
// Responsabilidades:
// - Carregar e manter a fonte utilizada pelo HUD.
// - Criar elementos de texto.
// - Atualizar o conteúdo dos elementos.
// - Formatar valores para exibição.
// - Renderizar todos os elementos do HUD.
//
// Os elementos são armazenados em um unordered_map utilizando
// identificadores textuais, permitindo adicionar novas
// informações sem criar uma variável específica para cada uma.
//
// Exemplos de elementos:
//
// - Score
// - Vida
// - Tempo
// - Inimigos
// - Wave
//
// Não é responsabilidade desta classe:
// - Calcular a pontuação.
// - Controlar a vida do jogador.
// - Controlar o sistema de Waves.
// - Gerenciar entidades do jogo.
//============================================================

class HUDManager
{
public:

    // Construtor responsável por inicializar o estado inicial
    // do gerenciador do HUD.
    HUDManager();


    // Carrega os recursos necessários e cria os elementos
    // iniciais do HUD.
    //
    // Retorna true quando a inicialização é concluída com sucesso
    // e false quando algum recurso necessário não pôde ser carregado.
    bool Initialize();


    // Atualiza o valor do Score exibido pelo HUD.
    //
    // Este método mantém compatibilidade com a implementação
    // específica de Score existente no sistema.
    void SetScore(int score);


    // Renderiza todos os elementos atualmente registrados
    // no HUD.
    void Render(sf::RenderWindow& window);


    // Cria um novo elemento de texto no HUD.
    //
    // id            -> identificador utilizado para localizar o item.
    // label         -> rótulo exibido junto ao valor.
    // position      -> posição do elemento na tela.
    // characterSize -> tamanho dos caracteres.
    void CreateText(
        const std::string& id,
        const std::string& label,
        const sf::Vector2f& position,
        unsigned int characterSize = 24);


    // Atualiza diretamente o texto de um elemento existente.
    //
    // Se o identificador não existir, nenhuma alteração é realizada.
    void SetText(
        const std::string& id,
        const std::string& text);


    // Atualiza o valor numérico de um elemento existente.
    //
    // O valor é combinado com o rótulo do HUDItem antes de ser
    // apresentado na tela.
    void SetValue(
        const std::string& id,
        int value);


private:

    // Fonte utilizada por todos os elementos de texto do HUD.
    sf::Font m_Font;

    // Armazena todos os elementos de texto do HUD identificados
    // por uma chave textual.
    //
    // Exemplo:
    //
    // "Score"   -> HUDItem
    // "Health"  -> HUDItem
    // "Time"    -> HUDItem
    // "Wave"    -> HUDItem
    std::unordered_map<std::string, HUDItem> m_Texts;

    // Valor do Score mantido pela implementação atual do HUD.
    //
    // Esse membro existe devido à versão anterior do sistema,
    // que possuía gerenciamento específico da pontuação.
    int m_Score;
};