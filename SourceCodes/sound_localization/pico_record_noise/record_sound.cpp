#include <I2S.h>
#include <math.h> // fabsf
#include <limits> // max int

I2S i2s_in(INPUT);

const int sampleRate = 48000;

#define NUMBER_OF_SAMPLES_TO_RECORD 12800
#define NOISE_ACTUAL_LENGTH 10000

uint16_t recorded_sound[NUMBER_OF_SAMPLES_TO_RECORD] = {0};

size_t sound_in_ind = NUMBER_OF_SAMPLES_TO_RECORD; // start disabled

uint64_t last_interrupt_ticks = 0;
uint32_t samples_to_skip = 0;

void onReceive()
{
  last_interrupt_ticks = rp2040.getCycleCount64();
  while (true)
  {
    int32_t l, r;
    int read_successful = i2s_in.read(&l, false);
    if (!read_successful)
    {
      break;
    }
    i2s_in.read(&r, false);
    int16_t good_bits = ((l << 4) & 0xFFFF0000) >> 16; // This seems to sound the best? Trial and error

    if (sound_in_ind < NUMBER_OF_SAMPLES_TO_RECORD && samples_to_skip == 0)
    {
      recorded_sound[sound_in_ind] = good_bits;
      sound_in_ind += 1;
    }
    else if (samples_to_skip > 0)
    {
      samples_to_skip -= 1;
    }
  }
}

void setup_sound_in()
{
  i2s_in.setBCLK(12); // WS / LRCLK has to be 13, BCLK+1
  i2s_in.setDATA(11);
  i2s_in.setBitsPerSample(32);
  i2s_in.onReceive(onReceive);
  i2s_in.setBuffers(3, 0, 0); // 3 buffers (minimum), 0 buffer length (it will set the default), 0 silence sample

  if (!i2s_in.begin(48000))
  {
    Serial.println("Failed to initialize I2S in!");
    while (1)
      ; // do nothing
  }
}
void start_recording_sound()
{
  sound_in_ind = 0;
  uint64_t tick_diff = rp2040.getCycleCount64() - last_interrupt_ticks;
  float skip = ((float)tick_diff * ((float)sampleRate / (float)rp2040.f_cpu()));
  samples_to_skip = (uint32_t)skip;
}

bool is_done_recording_sound()
{
  return sound_in_ind >= NUMBER_OF_SAMPLES_TO_RECORD;
}

void print_recorded_sound_to_serial()
{
  Serial.printf("bytes\n");
  int num_bytes = NUMBER_OF_SAMPLES_TO_RECORD*2;// 16-bit per in, 2 bytes
  Serial.printf("%i\n", num_bytes);
  Serial.write((byte *)recorded_sound, num_bytes); 
}
