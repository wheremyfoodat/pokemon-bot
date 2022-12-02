#ifndef GB_HEADLESSWRAPPER_HXX
#define GB_HEADLESSWRAPPER_HXX
#include <GameboyTKP/gb_addresses.h>
#include <GameboyTKP/gb_cpu.h>
#include <GameboyTKP/gb_ppu.h>
#include <GameboyTKP/gb_bus.h>
#include <GameboyTKP/gb_timer.h>
#include <GameboyTKP/gb_apu.h>
#include <GameboyTKP/gb_apu_ch.h>

enum class Command {
    Reset,
    Left,
    Up,
    Right,
    Down,
    A,
    B,
    Start,
    Select,
    Frame,
    Screenshot,
    Second,
    Exit,
    Save,
    Load,
    ReadSingle,
    ReadString,
    Error,
};

class Gameboy {
private:
    using GameboyPalettes = std::array<std::array<float, 3>,4>;
    using GameboyKeys = std::array<uint32_t, 4>;
    using CPU = TKPEmu::Gameboy::Devices::CPU;
    using PPU = TKPEmu::Gameboy::Devices::PPU;
    using APU = TKPEmu::Gameboy::Devices::APU;
    using ChannelArrayPtr = TKPEmu::Gameboy::Devices::ChannelArrayPtr;
    using ChannelArray = TKPEmu::Gameboy::Devices::ChannelArray;
    using Bus = TKPEmu::Gameboy::Devices::Bus;
    using Timer = TKPEmu::Gameboy::Devices::Timer;
    using Cartridge = TKPEmu::Gameboy::Devices::Cartridge;
public:
    Gameboy(std::string path);
    void ExecuteCommand(Command command);
    void SetValue(std::string val) { value_ = val; }
    std::string GetRes() { return res_; }
private:
    ChannelArrayPtr channel_array_ptr_;
    Bus bus_;
    APU apu_;
    PPU ppu_;
    Timer timer_;
    CPU cpu_;
    GameboyKeys direction_keys_;
    GameboyKeys action_keys_;
    uint8_t& interrupt_flag_;

    void reset();
    void frame();
    void update();
    void screenshot();
    void save();
    void load();

    std::mutex DrawMutex;
    int frame_clk_ = 0;
    std::string value_;
    std::string res_;
};
#endif