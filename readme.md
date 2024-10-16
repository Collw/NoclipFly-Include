# Guia de Integração do NoclipFly

Este README fornece um guia passo a passo sobre como integrar o sistema `NoclipFly` em seu gamemode SA:MP. 

Siga as instruções cuidadosamente para garantir que o sistema funcione corretamente em seu projeto.

## 1. **Requisitos**
- **Pacote do Servidor SA:MP** (Certifique-se de ter a versão mais recente do servidor SA:MP).
- **Compilador Pawno** (Incluído no pacote SA:MP).
- **ZCMD** Processador de Comandos (usado para gerenciar comandos de forma eficiente).
- **MapAndreas Plugin** (para ajudar na posicionamento, embora isso seja opcional).

## 2. **Arquivos Necessários**
- `noclipfly.inc`: O arquivo de inclusão com todas as funções necessárias para ativar o modo de voo (noclip).
- Seu arquivo de gamemode `.pwn` onde o sistema noclip será integrado.

## 3. **Passos de Instalação**

### Passo 1: Adicionar o `noclipfly.inc`
1. Coloque o `noclipfly.inc` no diretório **`/pawno/include/`** do seu servidor SA:MP.
2. Certifique-se de que a inclusão está referenciada corretamente no seu arquivo de gamemode (`.pwn`).

### Passo 2: Modificando Seu Gamemode
1. Abra seu arquivo de gamemode `.pwn` no Pawno.
2. No topo do seu gamemode, inclua as bibliotecas necessárias adicionando as seguintes linhas:

    ```pawn
    #include <a_samp>
    #include <noclipfly>
    #include <zcmd>
    ```

3. No callback `OnGameModeInit()`, inicialize o sistema Noclip:

    ```pawn
    public OnGameModeInit()
    {
        SetGameModeText("Nome do Seu Gamemode");
        AddPlayerClass(0, 1958.3783, 1343.1572, 15.3746, 269.1425, 0, 0, 0, 0, 0, 0);
        
        NoclipInit(); // Inicializa o modo noclip para todos os jogadores

        return 1;
    }
    ```

4. No callback `OnPlayerConnect()`, inicialize os dados Noclip para cada jogador:

    ```pawn
    public OnPlayerConnect(playerid)
    {
        NoclipConnect(playerid); // Inicializa os dados noclip quando um jogador se conecta
        return 1;
    }
    ```

5. No callback `OnPlayerUpdate()`, atualize o status noclip do jogador:

    ```pawn
    public OnPlayerUpdate(playerid)
    {
        NoclipUpdate(playerid); // Atualiza o movimento do jogador se ele estiver no modo de voo
        return 1;
    }
    ```

6. Adicione o comando `fly` para ativar ou desativar o modo de voo:

    ```pawn
    CMD:fly(playerid)//Coloque o nome que achar melhor para o comando.
    {
        if(GetPVarType(playerid, "FlyMode")) 
            CancelFlyMode(playerid); // Desativa o modo de voo
        else 
            FlyMode(playerid); // Ativa o modo de voo
        
        return 1;
    }
    ```

### Passo 3: Compilação
1. Salve o arquivo `.pwn`.
2. Abra o Pawno e compile seu gamemode. Certifique-se de que não há erros.
3. Coloque o arquivo `.amx` compilado no diretório **`/gamemodes/`**.

### Passo 4: Configuração
1. Abra o arquivo **`server.cfg`** na raiz do seu servidor SA:MP.
2. Defina seu gamemode para o que você acabou de compilar. Por exemplo:

    ```
    gamemode0 seugamemode 1
    ```

3. Salve o arquivo `server.cfg`.

### Passo 5: Testando
1. Inicie seu servidor SA:MP.
2. Conecte-se ao seu servidor e digite `/fly` para ativar o modo de voo.

## 4. **Sobre o NoclipFly**
O sistema **NoclipFly** permite que os jogadores do SA:MP ativem um modo de voo, permitindo que eles se movam livremente pelo ambiente, ignorando as colisões com objetos e terrenos. Ao ativar o modo, os jogadores podem utilizar as teclas de movimentação para subir, descer e se mover em todas as direções. O sistema é projetado para ser simples de usar e fácil de integrar em qualquer gamemode.

## 5. **Comandos Disponíveis**
- **/fly**: Ativa ou desativa o modo de voo (noclip) para o jogador.

## 6. **Notas**
- O sistema redefine automaticamente o status noclip quando o jogador se conecta ou o servidor é inicializado.
- O modo de voo permite que o jogador se mova livremente no ar usando o controle da câmera e os inputs do teclado.

## 7. **Contribuições**
Sinta-se à vontade para contribuir para este projeto. Você pode adicionar melhorias ou novas funcionalidades, e enviar suas alterações para revisão.

## 8. **Créditos**
Desenvolvedores: [Collw](https://github.com/Collw)  
Base: [Southclawns](https://github.com/Southclawns).
