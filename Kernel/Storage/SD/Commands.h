/*
 * Copyright (c) 2023, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h>

namespace Kernel::SD {

// Relevant Specifications:
// * (SDHC): SD Host Controller Simplified Specification (https://www.sdcard.org/downloads/pls/)
// * (PLSS) Physical Layer Simplified Specification (https://www.sdcard.org/downloads/pls/)

// PLSS 4.7.4: "Detailed Command Description"
enum class CommandIndex : u8 {
    GoIdleState = 0,
    AllSendCid = 2,
    SendRelativeAddr = 3,
    AppSetBusWidth = 6,
    SelectCard = 7,
    SendIfCond = 8,
    SendCsd = 9,
    SetBlockLen = 16,
    ReadSingleBlock = 17,
    ReadMultipleBlock = 18,
    WriteSingleBlock = 24,
    WriteMultipleBlock = 25,
    AppSendOpCond = 41,
    AppSendScr = 51,
    AppCmd = 55,
};

enum class CommandType : u8 {
    Normal,
    Suspend,
    Resume,
    Abort
};

enum class ResponseType : u8 {
    NoResponse,
    ResponseOf136Bits,
    ResponseOf48Bits,
    ResponseOf48BitsWithBusy
};

enum class DataTransferDirection : u8 {
    HostToCard,
    CardToHost
};

enum class SendAutoCommand : u8 {
    Disabled,
    Command12,
    Command23
};

// SDHC 2.2.5 & 2.2.6: "Transfer Mode Register" & "Command Register"
union Command {
    u32 raw;

    struct {
        u32 reserved0 : 1;
        u32 block_counter : 1;
        SendAutoCommand auto_command : 2;
        DataTransferDirection direction : 1;
        u32 multiblock : 1;
        u32 reserved1 : 10;
        ResponseType response_type : 2;
        u32 reserved2 : 1;
        u32 crc_enable : 1;
        u32 idx_enable : 1;
        u32 is_data : 1;
        CommandType type : 2;
        CommandIndex index : 6;
        u32 reserved3 : 2;
    };

    bool requires_dat_line() const
    {
        return is_data;
    }

    bool uses_transfer_complete_interrupt() const
    {
        // FIXME: I don't know how to determine this.
        return false;
    }
};
static_assert(AssertSize<Command, 4>());

namespace Commands {

constexpr Command go_idle_state = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::NoResponse,
    .reserved2 = 0,
    .crc_enable = 0,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::GoIdleState,
    .reserved3 = 0
};

constexpr Command all_send_cid = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf136Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::AllSendCid,
    .reserved3 = 0
};

constexpr Command send_relative_addr = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::SendRelativeAddr,
    .reserved3 = 0
};

constexpr Command app_set_bus_width = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::AppSetBusWidth,
    .reserved3 = 0
};

constexpr Command select_card = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48BitsWithBusy,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::SelectCard,
    .reserved3 = 0
};

constexpr Command send_if_cond = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::SendIfCond,
    .reserved3 = 0
};

constexpr Command send_csd = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf136Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::SendCsd,
    .reserved3 = 0
};

constexpr Command set_block_len = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::SetBlockLen,
    .reserved3 = 0
};

constexpr Command read_single_block = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::CardToHost,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 1,
    .type = CommandType::Normal,
    .index = CommandIndex::ReadSingleBlock,
    .reserved3 = 0
};

constexpr Command read_multiple_block = {
    .reserved0 = 0,
    .block_counter = 1,
    .auto_command = SendAutoCommand::Command12,
    .direction = DataTransferDirection::CardToHost,
    .multiblock = 1,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 1,
    .type = CommandType::Normal,
    .index = CommandIndex::ReadMultipleBlock,
    .reserved3 = 0
};

constexpr Command write_single_block = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 1,
    .type = CommandType::Normal,
    .index = CommandIndex::WriteSingleBlock,
    .reserved3 = 0
};

constexpr Command write_multiple_block = {
    .reserved0 = 0,
    .block_counter = 1,
    .auto_command = SendAutoCommand::Command12,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 1,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 1,
    .type = CommandType::Normal,
    .index = CommandIndex::WriteMultipleBlock,
    .reserved3 = 0
};

constexpr Command app_send_op_cond = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 0,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::AppSendOpCond,
    .reserved3 = 0
};

constexpr Command app_send_scr = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::CardToHost,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 0,
    .idx_enable = 0,
    .is_data = 1,
    .type = CommandType::Normal,
    .index = CommandIndex::AppSendScr,
    .reserved3 = 0
};

constexpr Command app_cmd = {
    .reserved0 = 0,
    .block_counter = 0,
    .auto_command = SendAutoCommand::Disabled,
    .direction = DataTransferDirection::HostToCard,
    .multiblock = 0,
    .reserved1 = 0,
    .response_type = ResponseType::ResponseOf48Bits,
    .reserved2 = 0,
    .crc_enable = 1,
    .idx_enable = 0,
    .is_data = 0,
    .type = CommandType::Normal,
    .index = CommandIndex::AppCmd,
    .reserved3 = 0
};

}

}
