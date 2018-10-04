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

uint64_t JTag::get(uint8_t read_command)
{
    set_noblock(RF_SEND, static_cast<uint64_t>(read_command));
    set_noblock(RF_CMD, READ_INSTRUCTION | CMD_SHIFT_WIDTH);

    wait_for_n_notifications(2);
    wait_until_finished();

    set_noblock(RF_SEND, 0);
    set_noblock(RF_CMD, READ_DATA_EXECUTE);

    wait_for_n_notifications(2);
    wait_until_finished();

    return RegisterFile::get(RF_RECEIVE);
}

uint64_t JTag::get(jtag::Readable read_command)
{
    return JTag::get(static_cast<uint8_t>(read_command));
}

uint64_t JTag::get(jtag::ReadWrite read_command)
{
    return JTag::get(static_cast<uint8_t>(read_command));
}


void JTag::wait_until_finished() const
{

    while (RegisterFile::get(RF_CMD) & EXECUTE_BIT);
    while (RegisterFile::get(RF_STATUS) & 2);

}

void JTag::set(uint8_t write_command, uint64_t argument)
{
    set_noblock(RF_SEND, write_command);
    set_noblock(RF_CMD, READ_INSTRUCTION_PAUSE);

    set_noblock(RF_SEND, argument);
    set_noblock(RF_CMD, READ_DATA_EXECUTE);

    wait_for_n_notifications(4);
    wait_until_finished();
}

void JTag::set(jtag::ReadWrite write_command, uint64_t argument)
{
    set(static_cast<uint8_t>(write_command) , argument);
}

void JTag::set(jtag::Writable write_command, uint64_t argument)
{
    set(static_cast<uint8_t>(write_command) , argument);
}

void JTag::reset()
{
    set_noblock(RF_CMD, RESET_EXECUTE);
    wait_for_notification();
    wait_until_finished();
}
