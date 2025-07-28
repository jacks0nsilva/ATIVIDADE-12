#include "ssd1306.h"
#include "FreeRTOS.h"
#include "task.h"
#include "config.h"
#include <stdio.h>

void vTaskDisplay(void *params){
    ssd1306_t ssd;

    // Configuração do display SSD1306
    i2c_init(I2C_PORT_DISPLAY, 400 * 1000);
    gpio_set_function(I2C_SDA_DISPLAY, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_DISPLAY, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_DISPLAY);
    gpio_pull_up(I2C_SCL_DISPLAY);

    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ADDRESS_DISPLAY, I2C_PORT_DISPLAY);
    ssd1306_config(&ssd);
    ssd1306_fill(&ssd, false); // Limpa o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    while(true)
    {
        switch (estado_sistema)
        {
        case PRONTO:
            ssd1306_fill(&ssd, false); // Limpa o display
            ssd1306_draw_string(&ssd, "Sistema Pronto", 0, 0);
            ssd1306_draw_string(&ssd, "SD:", 0, 12);
            ssd1306_draw_string(&ssd, cartao_montado ? "MONTADO" : "DESMONTADO", 33, 12);
            ssd1306_send_data(&ssd);
            break;
        case CAPTURANDO:
            ssd1306_fill(&ssd, false); 
            ssd1306_draw_string(&ssd, "Capturando", 0, 0);
            ssd1306_draw_string(&ssd, "Amostras:", 0, 12);
            char qnt_str[30];
            snprintf(qnt_str, sizeof(qnt_str), "%d", quantidade_coletada);
            ssd1306_draw_string(&ssd, qnt_str, 81, 12);
            ssd1306_send_data(&ssd);
            break;
        case GRAVANDO_SD:
            ssd1306_fill(&ssd, false); 
            ssd1306_draw_string(&ssd, "Gravando no SD", 0, 0);
            ssd1306_draw_string(&ssd, "Amostras:", 0, 12);
            snprintf(qnt_str, sizeof(qnt_str), "%d", quantidade_coletada);
            ssd1306_draw_string(&ssd, qnt_str, 81, 12);
            ssd1306_send_data(&ssd);
            break;
        case MONTANDO_SD:
            ssd1306_fill(&ssd, false); 
            ssd1306_draw_string(&ssd, "Montando SD", 0, 0);
            ssd1306_draw_string(&ssd, "Aguarde...", 0, 12);
            ssd1306_send_data(&ssd);
            break;
        case DESMONTANDO_SD:
            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "Desmontando SD", 0, 0);
            ssd1306_draw_string(&ssd, "Aguarde...", 0, 12);
            ssd1306_send_data(&ssd);
            break;
        case ERRO:
            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "Erro no Sistema", 0, 0);
            ssd1306_draw_string(&ssd, "Verifique o SD", 0, 12);
            ssd1306_send_data(&ssd);
            break;
        case FEEDBACK:
            ssd1306_fill(&ssd, false);
            ssd1306_draw_string(&ssd, "Dados Gravados!", 0, 0);
            ssd1306_send_data(&ssd);
            break;
        default:
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}