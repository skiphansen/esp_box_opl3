#include "bsp_board.h"
#include "bsp_storage.h"
#include "bsp_i2s.h"
#include "bsp_codec.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "opl.h"
#include "log.h"

#define SAMPLING_RATE   44100

#define AUDIO_BUF_LEN   1024
int16_t gAudioBuffer[AUDIO_BUF_LEN];

// initialize OPL3 registers for a 1kHz sine wave
struct {
   uint8_t Reg;
   uint8_t Value;
} InitData[] = {
   {0x20, 0x21 }, // OP1 Control Flags/Multiplier
   {0x23, 0x21 }, // OP2 Control Flags/Multiplier
   {0x28, 0x21 }, // OP3 Control Flags/Multiplier
   {0x2b, 0x21 }, // OP4 Control Flags/Multiplier

   {0x40, 0x00 }, // OP1 KSL/TL
   {0x43, 0x3f }, // OP2 KSL/TL (muted)
   {0x48, 0x3f }, // OP3 KSL/TL (muted)
   {0x4b, 0x3f }, // OP4 KSL/TL (muted)

   {0x60, 0x88 }, // OP1 AR/DR
   {0x63, 0x88 }, // OP2 AR/DR
   {0x68, 0x88 }, // OP3 AR/DR
   {0x6b, 0x88 }, // OP4 AR/DR

   {0x80, 0x00 }, // OP1 SL/RR
   {0x83, 0x00 }, // OP2 SL/RR
   {0x88, 0x00 }, // OP3 SL/RR
   {0x8b, 0x00 }, // OP4 SL/RR

   {0xe0, 0x00 }, // OP1 Waveform
   {0xe3, 0x00 }, // OP2 Waveform
   {0xe8, 0x00 }, // OP3 Waveform
   {0xeb, 0x00 }, // OP4 Waveform

   {0xc0, 0xf1 }, // Channels/Connections/Feedback
   {0xc3, 0xf0 }, // Channels/Connections/Feedback

   {0xa0, 0xa4 }, // FNUM        $freq = ($fnum / (1 << (20-$block))) * 49715.0;
   {0xb0, 0x3c }, // KON/Block/FNUM_H
   {0}            // end of table
};

void SinTest()
{
   int i;

   for(i = 0; InitData[i].Reg != 0; i++) {
      adlib_write(InitData[i].Reg,InitData[i].Value);
   }
}

void app_main(void)
{
   ESP_ERROR_CHECK(bsp_board_init());
   ESP_ERROR_CHECK(bsp_board_power_ctrl(POWER_MODULE_AUDIO, true));

   ESP_ERROR_CHECK(bsp_spiffs_init("storage", "/spiffs", 2));
   ESP_ERROR_CHECK(i2s_set_clk(I2S_NUM_0,SAMPLING_RATE,16,I2S_CHANNEL_MONO));
   ESP_ERROR_CHECK(i2s_start(I2S_NUM_0));
   LOG("Calling adlib_init()\n");
   adlib_init(SAMPLING_RATE);
   LOG("Calling SinTest()\n");
   SinTest();
// Init the sample buffer
   LOG("Calling adlib_getsample()\n");
   adlib_getsample(gAudioBuffer,AUDIO_BUF_LEN);

   LOG("Entering forever loop\n");
   while(true) {
//      ESP_ERROR_CHECK(i2s_write(I2S_NUM_0,gAudioBuffer,sizeof(gAudioBuffer) output_size, &i2s_bytes_written, portMAX_DELAY);

      vTaskDelay(1);
   }
}
