# Projeto Interruptores

Este repositório contém um projeto para controle de interrupções utilizando a placa **BitDogLab** com **Raspberry Pi Pico W**. O objetivo do projeto é controlar uma matriz de LEDs 5x5 utilizando um módulo WS2812 e interagir com ela por meio de dois botões. O número exibido na matriz de LEDs pode ser alterado pressionando os botões.

## Funcionalidades

- Exibe números de 0 a 9 em uma matriz de LEDs 5x5.
- Permite navegar entre os números pressionando os botões:
  - **BTN_A**: Avança para o próximo número (de 0 a 9).
  - **BTN_B**: Retrocede para o número anterior (de 9 a 0).
- Utiliza um debounce para evitar múltiplos acionamentos indesejados.

## Materiais Necessários

- Placa **BitDogLab** com **Raspberry Pi Pico W**.
- Matriz de LEDs **WS2812** (5x5).
- Dois botões físicos para interação.
- Fios de conexão para a matriz de LEDs e os botões.

## Como Usar

1. Conecte a matriz de LEDs e os botões aos pinos especificados no código.
2. Compile e faça o upload do código para a sua placa **Raspberry Pi Pico W**.
3. Ao inicializar o projeto, o número 0 será exibido na matriz de LEDs.
4. Pressione **BTN_A** para avançar para o próximo número.
5. Pressione **BTN_B** para retroceder para o número anterior.

## Estrutura do Código

- O código utiliza a linguagem **C** para a programação da **Raspberry Pi Pico W**.
- **GPIOs** são configurados para controlar os LEDs e os botões.
- A função `exibir_numero()` é responsável por acender os LEDs da matriz conforme o número selecionado.
- **Debounce** é implementado para os botões, evitando múltiplos acionamentos.

## Requisitos

- **Ambiente de desenvolvimento**: Placa **BitDogLab** com **Raspberry Pi Pico W** e **C SDK**.
- **Dependências**:
  - Biblioteca para controle de LEDs **WS2812**.

## Como Contribuir

1. Faça um fork deste repositório.
2. Crie uma branch para suas modificações (`git checkout -b feature/nova-funcionalidade`).
3. Faça as modificações desejadas.
4. Commit suas mudanças (`git commit -m 'Adiciona nova funcionalidade'`).
5. Envie para o repositório remoto (`git push origin feature/nova-funcionalidade`).
6. Abra um pull request.

## Licença

Este projeto está licenciado sob a Licença MIT - consulte o arquivo [LICENSE](LICENSE) para mais detalhes.
