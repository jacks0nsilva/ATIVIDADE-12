#ifndef FATFSLIB_H
#define FATFSLIB_H

// Funções para manipulação de sistemas de arquivos FAT

#include "ff.h"
#include "diskio.h"
#include "f_util.h"
#include "hw_config.h"
#include "my_debug.h"
#include "rtc.h"
#include "sd_card.h"

sd_card_t *sd_get_by_name(const char *const name);
FATFS *sd_get_fs_by_name(const char *name);
 void run_setrtc();
 void run_format();
 void run_mount();
 void run_unmount();
 void run_ls();
 void run_cat();
/*
// Função para capturar dados do ADC e salvar no arquivo *.txt
void capture_adc_data_and_save()
{
    printf("\nCapturando dados do ADC. Aguarde finalização...\n");
    FIL file;
    FRESULT res = f_open(&file, filename, FA_WRITE | FA_CREATE_ALWAYS);
    if (res != FR_OK)
    {
        printf("\n[ERRO] Não foi possível abrir o arquivo para escrita. Monte o Cartao.\n");
        return;
    }
    for (int i = 0; i < 128; i++)
    {
        adc_select_input(0);
        uint16_t adc_value = adc_read();
        char buffer[50];
        sprintf(buffer, "%d %d\n", i + 1, adc_value);
        UINT bw;
        res = f_write(&file, buffer, strlen(buffer), &bw);
        if (res != FR_OK)
        {
            printf("[ERRO] Não foi possível escrever no arquivo. Monte o Cartao.\n");
            f_close(&file);
            return;
        }
        sleep_ms(100);
    }
    f_close(&file);
    printf("\nDados do ADC salvos no arquivo %s.\n\n", filename);
}
    */

// Função para ler o conteúdo de um arquivo e exibir no terminal
void read_file(const char *filename);

#endif // FATFSLIB_H