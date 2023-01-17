/*
  xnrg_10_sdm630.ino - Eastron SDM630-Modbus energy meter support for Tasmota

  Copyright (C) 2021  Gennaro Tortone and Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef USE_ENERGY_SENSOR
#ifdef USE_MIRTEK
/*********************************************************************************************\
 * MIRTEK - CC1101 energy meter
 *
 * Based on:
\*********************************************************************************************/

#define XNRG_24             24

byte rfSettings[] = {
  0x0D,  // IOCFG2              GDO2 Output Pin Configuration
  0x2E,  // IOCFG1              GDO1 Output Pin Configuration
  0x06,  // IOCFG0              GDO0 Output Pin Configuration
  0x4F,  // FIFOTHR             RX FIFO and TX FIFO Thresholds
  0xD3,  // SYNC1               Sync Word, High Byte
  0x91,  // SYNC0               Sync Word, Low Byte
  0x3C,  // PKTLEN              Packet Length
  0x00,  // PKTCTRL1            Packet Automation Control
  0x41,  // PKTCTRL0            Packet Automation Control
  0x00,  // ADDR                Device Address
  0x16,  // CHANNR              Channel Number
  //0x0B,  // CHANNR              Channel Number
  0x0F,  // FSCTRL1             Frequency Synthesizer Control
  0x00,  // FSCTRL0             Frequency Synthesizer Control
  0x10,  // FREQ2               Frequency Control Word, High Byte
  0x8B,  // FREQ1               Frequency Control Word, Middle Byte
  0x54,  // FREQ0               Frequency Control Word, Low Byte
  0xD9,  // MDMCFG4             Modem Configuration
  0x83,  // MDMCFG3             Modem Configuration
  0x13,  // MDMCFG2             Modem Configuration
  0xD2,  // MDMCFG1             Modem Configuration
  0xAA,  // MDMCFG0             Modem Configuration
  0x31,  // DEVIATN             Modem Deviation Setting
  0x07,  // MCSM2               Main Radio Control State Machine Configuration
  0x0C,  // MCSM1               Main Radio Control State Machine Configuration
  0x08,  // MCSM0               Main Radio Control State Machine Configuration
  0x16,  // FOCCFG              Frequency Offset Compensation Configuration
  0x6C,  // BSCFG               Bit Synchronization Configuration
  0x03,  // AGCCTRL2            AGC Control
  0x40,  // AGCCTRL1            AGC Control
  0x91,  // AGCCTRL0            AGC Control
  0x87,  // WOREVT1             High Byte Event0 Timeout
  0x6B,  // WOREVT0             Low Byte Event0 Timeout
  0xF8,  // WORCTRL             Wake On Radio Control
  0x56,  // FREND1              Front End RX Configuration
  0x10,  // FREND0              Front End TX Configuration
  0xE9,  // FSCAL3              Frequency Synthesizer Calibration
  0x2A,  // FSCAL2              Frequency Synthesizer Calibration
  0x00,  // FSCAL1              Frequency Synthesizer Calibration
  0x1F,  // FSCAL0              Frequency Synthesizer Calibration
  0x41,  // RCCTRL1             RC Oscillator Configuration
  0x00,  // RCCTRL0             RC Oscillator Configuration
  0x59,  // FSTEST              Frequency Synthesizer Calibration Control
  0x59,  // PTEST               Production Test
  0x3F,  // AGCTEST             AGC Test
  0x81,  // TEST2               Various Test Settings
  0x35,  // TEST1               Various Test Settings
  //0x0B,  // TEST0               Various Test Settings
  0x09,  // TEST0               Various Test Settings
};

void packetSender() {
    ELECHOUSE_cc1101.SpiStrobe(0x33);  //Calibrate frequency synthesizer and turn it off
    ELECHOUSE_cc1101.SpiStrobe(0x3B);  // Flush the TX FIFO buffer
    ELECHOUSE_cc1101.SpiStrobe(0x36);  // Exit RX / TX, turn off frequency synthesizer and exit
    ELECHOUSE_cc1101.SpiWriteReg(0x3e, 0xC4); //выставляем мощность 10dB
    ELECHOUSE_cc1101.SendData(transmitt_byte, transmitt_byte[0]+1); //отправляем пакет
    ELECHOUSE_cc1101.SpiStrobe(0x3A);  // Flush the RX FIFO buffer
    ELECHOUSE_cc1101.SpiStrobe(0x34);  // Enable RX
}

//функция приёма пакета (помещает его в resultbuffer[])
void packetReceiver() {
    tmr.start();
    int PackCount = 0; //счётчик принятых из эфира пакетов
    bytecount = 0;     //указатель байтов в результирующем буфере
    while (!tmr.tick() && PackCount != packetType) { // wait for 2 sec
        if (ELECHOUSE_cc1101.CheckReceiveFlag()) {
            //Get received Data and calculate length
            int len = ELECHOUSE_cc1101.ReceiveData(buffer);
            for (int i = 1; i < len; i++) {
                resultbuffer[bytecount] = buffer[i];
                bytecount++;
            }
            ELECHOUSE_cc1101.SpiStrobe(0x36);  // Exit RX / TX, turn off frequency synthesizer and exit
            ELECHOUSE_cc1101.SpiStrobe(0x3A);  // Flush the RX FIFO buffer
            ELECHOUSE_cc1101.SpiStrobe(0x3B);  // Flush the TX FIFO buffer
            ELECHOUSE_cc1101.SpiStrobe(0x34);  // Enable RX
        }
    }
    crc.reset();
    crc.setPolynome(0xA9);
    for (int i = 2; i < (bytecount - 2); i++) {
        crc.add(resultbuffer[i]);
    }
    myCRC = crc.getCRC();
}

/*********************************************************************************************/
void packetParser_5() {
// struct ENERGY : xdrv_03_energy.ino

  if ( (resultbuffer[0]==0x73) and (resultbuffer[1]==0x55) and (resultbuffer[2]==0x1E) and (resultbuffer[6]==(atoi(MeterAdressValue) & 0xff)) and (resultbuffer[7]==((atoi(MeterAdressValue) >> 8) & 0xff)) and (resultbuffer[8]==0x5) and (resultbuffer[17]==0x1) and (resultbuffer[44]==0x55) )
  {
    //float sum = float((resultbuffer[25] << 16) | (resultbuffer[24] << 8) | resultbuffer[23]) / 100;
	Energy.active_power[0]  = float((resultbuffer[29] << 16) | (resultbuffer[28] << 8) | resultbuffer[27]) / 100;
	Energy.active_power[1]  = float((resultbuffer[33] << 16) | (resultbuffer[32] << 8) | resultbuffer[31]) / 100;
  }else{
    Serial.println("PARSING ERROR!");
  }
}

void packetParser_7() {
  if ( (bytecount == 45) and (resultbuffer[0]==0x73) and (resultbuffer[1]==0x55) and (resultbuffer[2]==0x1E) and (resultbuffer[6]==(atoi(MeterAdressValue) & 0xff)) and (resultbuffer[7]==((atoi(MeterAdressValue) >> 8) & 0xff)) and (resultbuffer[8]==0x2B) and (resultbuffer[12]==0x0) )
  {
    Energy.frequency[0] = float((resultbuffer[24] | (resultbuffer[25] << 8)))/100;
    //float cos  = float((resultbuffer[26] | (resultbuffer[27] << 8))) / 1000;
    Energy.voltage[0] = float((resultbuffer[28] | (resultbuffer[29] << 8))) / 100;   
    Energy.voltage[1]   = float((resultbuffer[30] | (resultbuffer[31] << 8))) / 100;
	Energy.voltage[2]   = float((resultbuffer[32] | (resultbuffer[33] << 8))) / 100;

    Energy.current[0]   = float(resultbuffer[34] | (resultbuffer[35] << 8) | (resultbuffer[36] << 16)) / 1000;
	Energy.current[1]   = float(resultbuffer[37] | (resultbuffer[38] << 8) | (resultbuffer[39] << 16)) / 1000;
	Energy.current[2]   = float(resultbuffer[40] | (resultbuffer[41] << 8) | (resultbuffer[42] << 16)) / 1000;
  }else{
    Serial.println("PARSING ERROR!");
  }
}

void MirtekEverySecond(void)
{
  bool data_ready = Sdm630Modbus->ReceiveReady();

  if (data_ready) {

      Energy.data_valid[0] = 0;
      Energy.data_valid[1] = 0;
      Energy.data_valid[2] = 0;

      RequestPacket_5();
      packetSender();    //отправляем пакет
      packetReceiver();  //принимаем и склеиваем пакет
      packetParser_5();
        

      delay(1000);
      RequestPacket_9();
      packetSender();   //отправляем пакет
      packetReceiver(); //принимаем и склеиваем пакет
      packetParser_7();

      EnergyUpdateTotal();

      Sdm630.read_state++;
      if (sizeof(sdm630_start_addresses)/2 == Sdm630.read_state) {
        Sdm630.read_state = 0;
      }
    }
  } // end data ready
}

void MirtekSnsInit(void)
{
    ELECHOUSE_cc1101.setGDO0(gdo0);
    if (ELECHOUSE_cc1101.getCC1101()) {    // Check the CC1101 Spi connection.
      Energy.phase_count = 3;
      Energy.frequency_common = true;      // Use common frequency
    }
    else {
      TasmotaGlobal.energy_driver = ENERGY_NONE;
    }
    //Инициализируем cc1101
    ELECHOUSE_cc1101.SpiStrobe(0x30);  //reset
    ELECHOUSE_cc1101.SpiWriteBurstReg(0x00, rfSettings, 0x2F);
    ELECHOUSE_cc1101.SpiStrobe(0x33);  //Calibrate frequency synthesizer and turn it off
    ELECHOUSE_cc1101.SpiStrobe(0x3A);  // Flush the RX FIFO buffer
    ELECHOUSE_cc1101.SpiStrobe(0x3B);  // Flush the TX FIFO buffer
    ELECHOUSE_cc1101.SpiStrobe(0x34);  // Enable RX
}

void MirtekDrvInit(void)
{
  //Pin(GPIO_CC1101_GDO2);              // Output port for transmission
  //Pin(GPIO_CC1101_GDO0);              // Input port for reception

//TODO cc1101 pin used
  if (PinUsed(GPIO_CC1101_GDO2) && PinUsed(GPIO_CC1101_GDO0)) {
    TasmotaGlobal.energy_driver = XNRG_24;
  }
}

/*********************************************************************************************\
 * Interface
\*********************************************************************************************/

bool Xnrg24(uint8_t function)
{
  bool result = false;

  switch (function) {
    case FUNC_ENERGY_EVERY_SECOND:
      MirtekEverySecond();
      break;
    case FUNC_INIT:
      MirtekSnsInit();
      break;
    case FUNC_PRE_INIT:
      MirtekDrvInit();
      break;
  }
  return result;
}

#endif  // USE_MIRTEK
#endif  // USE_ENERGY_SENSOR
