


void DAwrite(uchar data)
{
    I2CStart();

    I2CSendByte(0x90);
    I2CWaitAck();

    I2CSendByte(0x40);
    I2CWaitAck();

    I2CSendByte(data);
    I2CSendAck();
    
    I2CStop();
}



// 0x40 0100 0000
// 0x01 
void ADread(uchar channel)
{


    uchar ans;

    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();

    I2CSendByte(channel);
    I2CWaitAck();

    

    I2CStart();
    I2CSendsByte(0x90);
    I2CWaitAck();

    ans = I2CReceiveByte();
    I2CSendAck();

    I2CStop();

    return ans;
    

}