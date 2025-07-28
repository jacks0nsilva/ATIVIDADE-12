#include "tasks.h"
#include "config.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"

void vTaskBuzzer(void *params)
{
    // Configura o pino do buzzer como saída
    gpio_set_function(BUZZER_B, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_B);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (5000 * 4096));  // Frequência do PWM
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(BUZZER_B, 0);  // Inicializa com o PWM desligado

    // Variável para guardar o estado anterior.
    // 'static' garante que ela mantenha seu valor entre as execuções do loop.
    static ESTADO_SISTEMA estado_anterior = PRONTO;

    while(true)
    {
        // 1. Detecta a TRANSIÇÃO para o estado CAPTURANDO
        if (estado_sistema == CAPTURANDO  && estado_anterior != CAPTURANDO) {
            // Toca o buzzer por 200ms APENAS UMA VEZ
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(500));
            pwm_set_gpio_level(BUZZER_B, 0);
        }
        // 2. Detecta a TRANSIÇÃO para o estado ERRO
        else if (estado_sistema == ERRO && estado_anterior != ERRO) {
            // Toca o buzzer por 500ms DUAS VEZES
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(500));
            pwm_set_gpio_level(BUZZER_B, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(500));
            pwm_set_gpio_level(BUZZER_B, 0);
        } else if (estado_sistema == GRAVANDO_SD && estado_anterior != GRAVANDO_SD) {
            // Toca o buzzer por 300ms APENAS UMA VEZ
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(300));
            pwm_set_gpio_level(BUZZER_B, 0);
        } else if (estado_sistema == FEEDBACK && estado_anterior != FEEDBACK) {
            // Toca o buzzer por 200ms DUAS VEZES
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(200));
            pwm_set_gpio_level(BUZZER_B, 0);
            vTaskDelay(pdMS_TO_TICKS(200));
            pwm_set_gpio_level(BUZZER_B, 2048);
            vTaskDelay(pdMS_TO_TICKS(200));
            pwm_set_gpio_level(BUZZER_B, 0);
        }



        // 3. Atualiza o estado anterior no final do loop
        estado_anterior = estado_sistema;
        
        // 4. Delay para não sobrecarregar a CPU
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}