#include "Core/HUDManager.hpp"

#include <iostream>
#include <utility>


//============================================================
// HUDManager
// -----------------------------------------------------------
// Implementação responsável pela criação, atualização e
// renderização dos elementos textuais do HUD.
//============================================================


//------------------------------------------------------------
// Construtor
//------------------------------------------------------------

HUDManager::HUDManager()
{
    
}


//------------------------------------------------------------
// Initialize
//------------------------------------------------------------

bool HUDManager::Initialize()
{
    // Carrega a fonte utilizada por todos os elementos do HUD.
    //
    // O arquivo precisa estar disponível no diretório de assets
    // esperado pelo jogo.
    if (!m_Font.openFromFile("assets/fonts/arial.ttf"))
    {
        std::cout << "Erro ao carregar fonte!"
                  << std::endl;

        return false;
    }


    // Cria os elementos iniciais do HUD.
    //
    // Cada elemento recebe:
    // - um identificador;
    // - um rótulo;
    // - uma posição na tela.
    CreateText(
        "Score",
        "Score",
        {15.f, 15.f});

    CreateText(
        "Health",
        "Vida",
        {15.f, 45.f});

    CreateText(
        "Time",
        "Tempo",
        {15.f, 75.f});

    CreateText(
        "Enemies",
        "Inimigos",
        {15.f, 105.f});

    CreateText(
        "Wave",
        "Wave",
        {15.f, 135.f});


    return true;
}


//------------------------------------------------------------
// CreateText
//------------------------------------------------------------

void HUDManager::CreateText(
    const std::string& id,
    const std::string& label,
    const sf::Vector2f& position,
    unsigned int characterSize)
{
    // Cria um novo item do HUD.
    HUDItem item;


    // Armazena o rótulo separadamente do texto exibido.
    //
    // Isso permite atualizar apenas o valor posteriormente,
    // mantendo o rótulo original do elemento.
    item.Label = label;


    // Cria o sf::Text utilizando a fonte previamente carregada.
    //
    // O texto começa com valor zero, pois o valor real será
    // atualizado pelo sistema responsável pela informação.
    item.Text = std::make_unique<sf::Text>(
        m_Font,
        label + ": 0",
        characterSize);


    // Define a posição do elemento na tela.
    item.Text->setPosition(position);


    // Armazena o item utilizando seu identificador.
    //
    // std::move transfere a propriedade do sf::Text para o HUDItem
    // armazenado no unordered_map.
    m_Texts[id] = std::move(item);
}



//------------------------------------------------------------
// SetText
//------------------------------------------------------------

void HUDManager::SetText(
    const std::string& id,
    const std::string& text)
{
    // Procura o elemento utilizando seu identificador.
    auto it = m_Texts.find(id);


    // Caso o elemento não exista, simplesmente ignora a solicitação.
    //
    // Isso evita acessar um elemento inexistente no mapa.
    if (it == m_Texts.end())
    {
        return;
    }


    // Atualiza diretamente o conteúdo visual do elemento.
    it->second.Text->setString(text);
}


//------------------------------------------------------------
// SetValue
//------------------------------------------------------------

void HUDManager::SetValue(
    const std::string& id,
    int value)
{
    // Procura o elemento utilizando seu identificador.
    auto it = m_Texts.find(id);


    // Se o identificador não existir, não há nada para atualizar.
    if (it == m_Texts.end())
    {
        return;
    }


    // Combina o rótulo armazenado com o valor recebido.
    //
    // Exemplo:
    //
    // Label = "Vida"
    // Value = 85
    //
    // Resultado:
    //
    // "Vida: 85"
    it->second.Text->setString(
        it->second.Label +
        ": " +
        std::to_string(value));
}


//------------------------------------------------------------
// Render
//------------------------------------------------------------

void HUDManager::Render(sf::RenderWindow& window)
{
    // Percorre todos os elementos registrados no HUD.
    //
    // O uso de structured binding permite acessar diretamente
    // o identificador e o HUDItem armazenados no unordered_map.
    for (const auto& [id, item] : m_Texts)
    {
        // Renderiza o texto associado ao elemento.
        window.draw(*item.Text);
    }
}