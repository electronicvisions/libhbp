#include <jtag.h>

const RMA2_NLA RF_CMD = 0x400;
const RMA2_NLA RF_STATUS = 0x408;
const RMA2_NLA RF_SEND = 0x480;
const RMA2_NLA RF_RECEIVE = 0x500;

const uint8_t RESET = 0;
const uint8_t READ_INSTRUCTION = 1;
const uint8_t READ_DATA = 2;
const uint16_t CMD_SHIFT_WIDTH = 64 << 3;
const uint16_t DATA_SHIFT_WIDTH = 32 << 3;
const uint16_t PAUSE_BIT = (1 << 13);
const uint16_t EXECUTE_BIT = (1 << 14);

const uint64_t READ_INSTRUCTION_EXECUTE = READ_INSTRUCTION | CMD_SHIFT_WIDTH | EXECUTE_BIT;
const uint64_t READ_INSTRUCTION_PAUSE = READ_INSTRUCTION | CMD_SHIFT_WIDTH | PAUSE_BIT;
const uint64_t READ_DATA_EXECUTE = READ_DATA | DATA_SHIFT_WIDTH | EXECUTE_BIT;
const uint64_t READ_DATA_PAUSE = READ_DATA | DATA_SHIFT_WIDTH | PAUSE_BIT;
const uint64_t RESET_EXECUTE = RESET | EXECUTE_BIT;

uint64_t JTag::read(uint8_t read_command)
{
    write_noblock(RF_SEND, static_cast<uint64_t>(read_command));
    write_noblock(RF_CMD, READ_INSTRUCTION | CMD_SHIFT_WIDTH);

    wait_for_n_notifications(2);
    wait_until_finished();

    write_noblock(RF_SEND, 0);
    write_noblock(RF_CMD, READ_DATA_EXECUTE);

    wait_for_n_notifications(2);
    wait_until_finished();

    return RegisterFile::read(RF_RECEIVE);
}

uint64_t JTag::read(jtag::Readable read_command)
{
    return JTag::read(static_cast<uint8_t>(read_command));
}

uint64_t JTag::read(jtag::ReadWrite read_command)
{
    return JTag::read(static_cast<uint8_t>(read_command));
}


void JTag::wait_until_finished() const
{

    while (RegisterFile::read(RF_CMD) & EXECUTE_BIT);
    while (RegisterFile::read(RF_STATUS) & 2);

}

void JTag::write(uint8_t write_command, uint64_t argument)
{
    write_noblock(RF_SEND, write_command);
    write_noblock(RF_CMD, READ_INSTRUCTION_PAUSE);

    write_noblock(RF_SEND, argument);
    write_noblock(RF_CMD, READ_DATA_EXECUTE);

    wait_for_n_notifications(4);
    wait_until_finished();
}

void JTag::write(jtag::ReadWrite write_command, uint64_t argument)
{
    write(static_cast<uint8_t>(write_command), argument);
}

void JTag::write(jtag::Writable write_command, uint64_t argument)
{
    write(static_cast<uint8_t>(write_command), argument);
}

void JTag::reset()
{
    write_noblock(RF_CMD, RESET_EXECUTE);
    wait_for_notification();
    wait_until_finished();
}
