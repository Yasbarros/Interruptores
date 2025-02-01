#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "ws2812.h"

// Definição dos pinos para o Wokwi
#define LED_R 13
#define LED_G 11
#define LED_B 12
#define BTN_A 5
#define BTN_B 6
#define MATRIX_PIN 7
#define INTENSIDADE 10
#define MATRIX_SIZE 25

// Declarações das variáveis
uint32_t leds[MATRIX_SIZE];
int numero_atual = 0;
PIO pio = pio0;
int sm;
bool led_state = false;

// Matriz de números
const uint32_t numeros[10][25] = {
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1}};

// Função para exibir números na matriz
void exibir_numero(int num) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        leds[i] = (numeros[num][i] == 1) ? (INTENSIDADE << 16) : 0x000000;
    }

    // Envia os valores para a matriz de LEDs
    for (int i = 0; i < MATRIX_SIZE; i++) {
        pio_sm_put_blocking(pio, sm, leds[i]);
    }
}

// Função de debounce para os botões
bool debounce_callback(struct repeating_timer *t) {
    int pin = (int)t->user_data;
    if (gpio_get(pin) == 0) {
        if (pin == BTN_A) {
            numero_atual = (numero_atual + 1) % 10;
        } else if (pin == BTN_B) {
            numero_atual = (numero_atual - 1 + 10) % 10;
        }
        exibir_numero(numero_atual);
    }
    return false;
}

// Função de interrupção para os botões
void gpio_callback(uint gpio, uint32_t events) {
    static struct repeating_timer debounce_timer;
    add_repeating_timer_ms(50, debounce_callback, (void *)gpio, &debounce_timer);
}

// Função de configuração inicial
void setup() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);
    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    // Configuração dos botões
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);
    gpio_init(BTN_B);
    gpio_set_dir(BTN_B, GPIO_IN);
    gpio_pull_up(BTN_B);

    // Inicialização do WS2812
    uint offset = pio_add_program(pio, &ws2812_program);
    sm = pio_claim_unused_sm(pio, true);
    ws2812_program_init(pio, sm, offset, MATRIX_PIN, 800000, false);

    // Configuração das interrupções para os botões
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BTN_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
}

// Função principal
int main() {
    setup();
    while (1) {
        tight_loop_contents();
    }
}
