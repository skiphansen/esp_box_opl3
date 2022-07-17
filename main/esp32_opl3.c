#include "bsp_board.h"
#include "bsp_storage.h"
#include "bsp_i2s.h"
#include "bsp_codec.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
   ESP_ERROR_CHECK(bsp_board_init());
   ESP_ERROR_CHECK(bsp_board_power_ctrl(POWER_MODULE_AUDIO, true));

   ESP_ERROR_CHECK(bsp_spiffs_init("storage", "/spiffs", 2));
   ESP_ERROR_CHECK(bsp_codec_init(AUDIO_HAL_44K_SAMPLES));
   ESP_ERROR_CHECK(bsp_i2s_init(I2S_NUM_0, 44100));
   i2s_set_clk(I2S_NUM_0,44100,16,I2S_CHANNEL_MONO);
// i2s_write(I2S_NUM_0, output, output_size, &i2s_bytes_written, portMAX_DELAY);

   while(true) {
      vTaskDelay(1);
   }
}
