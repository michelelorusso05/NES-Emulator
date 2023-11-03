#include "apu.h"

#define STATUS_ENABLE_PULSE_1       0x01
#define STATUS_ENABLE_PULSE_2       0x02
#define STATUS_ENABLE_TRIANGLE      0x04
#define STATUS_ENABLE_NOISE         0x08
#define STATUS_ENABLE_DMC           0x10

#define CONTROL_PULSE_1_ENABLED     0x01
#define CONTROL_PULSE_2_ENABLED     0x02
#define CONTROL_TRIANGLE_ENABLED    0x04
#define CONTROL_NOISE_ENABLED       0x08
#define CONTROL_DMC_ENABLED         0x10
#define CONTROL_FRAME_INTERRUPT     0x40
#define CONTROL_DMC_INPERRUPT       0x80

#define INTERRUPT_INHIBIT           0x40
#define FRAME_COUNTER_MODE          0x80

static constexpr double pulseLookupTable[31] = {0, 0.011609139523578026, 0.022939481268011527, 0.03400094921689606, 0.04480300187617261, 0.05535465924895688, 0.06566452795600367, 0.07574082464884459, 0.08559139784946236, 0.09522374833850243, 0.10464504820333041, 0.11386215864759427, 0.12288164665523155, 0.13170980059397538, 0.14035264483627205, 0.1488159534690486, 0.15710526315789472, 0.16522588522588522, 0.1731829170024174, 0.18098125249301955, 0.18862559241706162, 0.19612045365662886, 0.20347017815646784, 0.21067894131185272, 0.21775075987841944, 0.2246894994354535, 0.2314988814317673, 0.23818248984115256, 0.2447437774524158, 0.2511860718171926, 0.25751258087706685};

static constexpr double tndLookupTable[203] = {
    0, 0.006699823979696262, 0.01334502018019487, 0.01993625400950099, 0.026474180112418616, 0.032959442587297105, 0.03939267519756107, 0.04577450157816932, 0.05210553543714433, 0.05838638075230885, 0.06461763196336215, 0.07079987415942428, 0.07693368326217241, 0.08301962620468999, 0.08905826110614481, 0.09505013744240969, 0.10099579621273477, 0.10689577010257789, 0.11275058364269584, 0.11856075336459644, 0.12432678795244785, 0.1300491883915396, 0.13572844811338536, 0.1413650531375568, 0.1469594822103333, 0.15251220694025122, 0.15802369193063237, 0.16349439490917161, 0.16892476685465738, 0.1743152521209005, 0.1796662885579421, 0.18497830763060993, 0.19025173453449087, 0.19548698830938505, 0.20068448195030472, 0.20584462251608032, 0.2109678112356332, 0.2160544436119733, 0.2211049095239788, 0.22611959332601225, 0.2310988739454269, 0.23604312497801538, 0.24095271478145042, 0.24582800656676793, 0.25066935848793903, 0.25547712372957787, 0.2602516505928307, 0.26499328257948945, 0.26970235847437257, 0.27437921242601526, 0.27902417402570834, 0.28363756838492643, 0.2882197162111822, 0.292770933882345, 0.29729153351945914, 0.3017818230580978, 0.3062421063182866, 0.31067268307302937, 0.31507384911547015, 0.3194458963247213, 0.32378911273039, 0.3281037825758322, 0.3323901863801631, 0.33664860099905314, 0.3408792996843372, 0.34508255214246325, 0.349258624591807, 0.3534077798188791, 0.3575302772334479, 0.36162637292260397, 0.3656963197037888, 0.3697403671768112, 0.3737587617748739, 0.37775174681463214, 0.38171956254530554, 0.38566244619686446, 0.3895806320273106, 0.3934743513690717, 0.3973438326745308, 0.40118930156070615, 0.405010980853104, 0.4088090906287582, 0.41258384825847705, 0.4163354684483128, 0.42006416328027124, 0.4237701422522769, 0.42745361231741014, 0.4311147779224318, 0.4347538410456096, 0.43837100123386197, 0.4419664556392331, 0.44554039905471293, 0.44909302394941686, 0.4526245205031371, 0.45613507664027986, 0.4596248780632002, 0.4630941082849479, 0.4665429486614358, 0.46997157842304194, 0.47338017470565896, 0.4767689125811996, 0.48013796508757145, 0.48348750325813084, 0.48681769615062515, 0.49012871087563703, 0.493420712624537, 0.49669386469695664, 0.49994832852779125, 0.5031842637137408, 0.5064018280393993, 0.5096011775029012, 0.5127824663411329, 0.5159458470545188, 0.5190914704313901, 0.5222194855719443, 0.5253300399118033, 0.528423279245178, 0.5314993477476477, 0.5345583879985607, 0.5376005410030638, 0.5406259462137686, 0.5436347415520602, 0.5466270634290563, 0.5496030467662235, 0.5525628250156552, 0.5555065301800212, 0.5584342928321915, 0.5613462421345432, 0.5642425058579547, 0.5671232104004943, 0.5699884808058077, 0.5728384407812124, 0.5756732127155, 0.5784929176964575, 0.5812976755281083, 0.5840876047476803, 0.5868628226423054, 0.5896234452654553, 0.5923695874531196, 0.595101362839729, 0.5978188838738291, 0.6005222618335111, 0.6032116068415997, 0.6058870278806079, 0.6085486328074569, 0.6111965283679723, 0.6138308202111536, 0.6164516129032258, 0.6190590099414757, 0.6216531137678758, 0.6242340257825014, 0.6268018463567424, 0.6293566748463153, 0.6318986096040777, 0.6344277479926501, 0.6369441863968464, 0.6394480202359187, 0.6419393439756177, 0.6444182511400732, 0.6468848343234979, 0.6493391852017159, 0.6517813945435207, 0.6542115522218658, 0.6566297472248885, 0.659036067666773, 0.6614306007984521, 0.6638134330181533, 0.6661846498817908, 0.6685443361132047, 0.670892575614252, 0.6732294514747513, 0.6755550459822829, 0.6778694406318475, 0.6801727161353863, 0.6824649524311629, 0.684746228693012, 0.6870166233394548, 0.6892762140426848, 0.6915250777374256, 0.693763290629662, 0.6959909282052493, 0.6982080652383982, 0.7004147758000423, 0.7026111332660865, 0.70479721032554, 0.7069730789885358, 0.7091388105942369, 0.7112944758186339, 0.7134401446822323, 0.7155758865576349, 0.7177017701770176, 0.7198178636395035, 0.7219242344184336, 0.7240209493685391, 0.7261080747330146, 0.7281856761504939, 0.7302538186619317, 0.7323125667173908, 0.734361984182737, 0.7364021343462434, 0.7384330799251054, 0.7404548830718675, 0.742467605380763
};

static constexpr uint8_t lengthCounterLoadTable[32] = 
{
        10, 254,  20,   2,  40,   4,  80,   6, 160,   8,  60,  10,  14,  12,  26,  14,
        12,  16,  24,  18,  48,  20,  96,  22, 192,  24,  72,  26,  16,  28,  32,  30
};

APU::APU()
{
    reset();
}

APU::~APU()
{

}

void APU::writeRegisters(uint8_t reg, uint8_t value)
{
    switch (reg)
    {
        // Pulse 1
        case 0x00:
            squareChannel1.dutyCycleSelect = ((value & 0xC0) >> 6);
            squareChannel1.lengthCounterHalt = (value & 0x20);
            squareChannel1.envelopeLoop = (value & 0x20);
            squareChannel1.constantVolume = (value & 0x10);
            squareChannel1.volume_envelopeReload = (value & 0x0F);
            break;
        case 0x01:
            squareChannel1.sweepEnabled = ((value & 0x80) > 0);
            squareChannel1.sweepPeriodReload = ((value >> 4) & 0x07) - 1;
            squareChannel1.sweepNegate = ((value & 0x08) > 0);
            squareChannel1.sweepShift = (value & 0x07);

            // Side effect - sweep is reloaded
            squareChannel1.reloadSweep = true;
            squareChannel1.SweepUpdatePeriod();
            break;
        case 0x02:
            squareChannel1.SetPeriod((squareChannel1.sequencerReload & 0x0700) | value);
            break;
        case 0x03:
            if (squareChannel1.enabled)
                squareChannel1.lengthCounter = lengthCounterLoadTable[((value & 0xF8) >> 3)];

            squareChannel1.SetPeriod((squareChannel1.sequencerReload & 0x00FF) | ((value & 0x07) << 8));

            // Side effect - envelope is restarted
            squareChannel1.envelopeStart = true;
            // Side effect - phase is reset
            squareChannel1.sequencerCounter = 0;
            break;
        
        // Pulse 2
        case 0x04:
            squareChannel2.dutyCycleSelect = ((value & 0xC0) >> 6);
            squareChannel2.lengthCounterHalt = (value & 0x20);
            squareChannel2.envelopeLoop = (value & 0x20);
            squareChannel2.constantVolume = (value & 0x10);
            squareChannel2.volume_envelopeReload = (value & 0x0F);
            break;
        case 0x05:
            squareChannel2.sweepEnabled = ((value & 0x80) > 0);
            squareChannel2.sweepPeriodReload = ((value & 0x70) >> 4) - 1;
            squareChannel2.sweepNegate = ((value & 0x08) > 0);
            squareChannel2.sweepShift = (value & 0x07);

            // Side effect - sweep is reloaded
            squareChannel2.reloadSweep = true;
            squareChannel2.SweepUpdatePeriod();
            break;
        case 0x06:
            squareChannel2.SetPeriod((squareChannel2.sequencerReload & 0x0700) | value);
            break;
        case 0x07:
            if (squareChannel2.enabled)
                squareChannel2.lengthCounter = lengthCounterLoadTable[((value & 0xF8) >> 3)];

            squareChannel2.SetPeriod((squareChannel2.sequencerReload & 0x00FF) | ((value & 0x07) << 8));

            // Side effect - envelope is restarted
            squareChannel2.envelopeStart = true;
            // Side effect - phase is reset
            squareChannel2.sequencerCounter = 0;
            break;
        
        // Triangle
        case 0x08:
            triangleChannel.control = (value & 0x80);
            triangleChannel.linearCounterReloadValue = (value & 0x7F);
            break;
        case 0x0A:
            triangleChannel.sequencerReload = ((triangleChannel.sequencerReload & 0xFF00) | value);
            break;
        case 0x0B:
            triangleChannel.sequencerReload = ((triangleChannel.sequencerReload & 0xFF) | ((value & 0x03) << 8));
            if (triangleChannel.enabled)
                triangleChannel.lengthCounter = lengthCounterLoadTable[((value & 0xF8) >> 3)];
            triangleChannel.linearCounterReload = true;
            break;

        // Noise
        case 0x0C:
            noiseChannel.lengthCounterHalt = (value & 0x20);
            noiseChannel.constantVolume = (value & 0x10);
            noiseChannel.volume_envelopeReload = (value & 0x0F);
            break;
        case 0x0E:
            noiseChannel.mode = (value & 0x80);
            noiseChannel.LoadPeriod(value & 0x0F);
            break;
        case 0x0F:
            if (noiseChannel.enabled)
                noiseChannel.lengthCounter = lengthCounterLoadTable[((value & 0xF8) >> 3)];
            noiseChannel.envelopeStart = true;
            break;

        // DMC
        case 0x10:
            break;
        case 0x11:
            break;
        case 0x12:
            break;
        case 0x13:
            break;

        // Other
        case 0x15:
            control = value;

            squareChannel1.enabled = ((control & 0x01) > 0);
            if (!squareChannel1.enabled)
                squareChannel1.lengthCounter = 0;

            squareChannel2.enabled = ((control & 0x02) > 0);
            if (!squareChannel2.enabled)
                squareChannel2.lengthCounter = 0;

            triangleChannel.enabled = ((control & 0x04) > 0);
            if (!triangleChannel.enabled)
                triangleChannel.lengthCounter = 0;

            noiseChannel.enabled = ((control & 0x08) > 0);
            if (!noiseChannel.enabled)
                noiseChannel.lengthCounter = 0;
            
            break;
        case 0x17:
            modeAndInterrupt = value;

            if ((modeAndInterrupt & 0x80) > 0)
            {
                triangleChannel.ClockLengthCounter();
                triangleChannel.ClockLinearCounter();

                squareChannel1.ClockLengthCounter();
                squareChannel1.ClockSweep();
                squareChannel1.ClockEnvelope();
                
                squareChannel2.ClockLengthCounter();
                squareChannel2.ClockSweep();
                squareChannel2.ClockEnvelope();

                noiseChannel.ClockLengthCounter();
                noiseChannel.ClockEnvelope();
            }

            if (modeAndInterrupt & 0x40)
                irq = false;

            frameClockCounter = 0;
            break;
    }
}

uint8_t APU::readRegisters(uint8_t reg)
{
    // Other registers are write only
    if (reg == 0x15)
    {
        bool irqState = irq;
        irq = false;
        return   (squareChannel1.lengthCounter > 0)         | 
                ((squareChannel2.lengthCounter > 0) << 1)   |
                ((triangleChannel.lengthCounter > 0) << 2)  |
                ((noiseChannel.lengthCounter > 0) << 3)  |
                (irqState << 6);
    }
    return 0;
}

// a: Frame counter, b: half frame
#define FRAME_COUNT(a) (static_cast<uint16_t>(a * 2))
void APU::clock()
{
    bool quarterFrameClock = false;
    bool halfFrameClock = false;
    bool fireInterrupt = false;

    bool reset = false;

    switch (frameClockCounter)
    {
        case FRAME_COUNT(3728.5):
            quarterFrameClock = true;
            break;
            
        case FRAME_COUNT(7456.5):
            quarterFrameClock = true;
            halfFrameClock = true;
            break;

        case FRAME_COUNT(11185.5):
            quarterFrameClock = true;
            break;

        case FRAME_COUNT(14914):
            if ((modeAndInterrupt & 0xC0) == 0)
                fireInterrupt = true;
            break;

        case FRAME_COUNT(14914.5):
            if ((modeAndInterrupt & 0x80) == 0)
            {
                quarterFrameClock = true;
                halfFrameClock = true;

                if ((modeAndInterrupt & 0x40) == 0)
                    fireInterrupt = true;
            }
            break;

        case FRAME_COUNT(14915):
            if ((modeAndInterrupt & 0x80) == 0)
            {
                reset = true;

                if ((modeAndInterrupt & 0x40) == 0)
                    fireInterrupt = true;
            }
            break;
        
        case FRAME_COUNT(18640.5):
            quarterFrameClock = true;
            halfFrameClock = true;
            break;
        
        case FRAME_COUNT(18641):
            reset = true;
            break;
    }

    if (quarterFrameClock)
    {
        squareChannel1.ClockEnvelope();
        squareChannel2.ClockEnvelope();
        noiseChannel.ClockEnvelope();

        triangleChannel.ClockLinearCounter();
    }

    if (halfFrameClock)
    {
        squareChannel1.ClockLengthCounter();
        squareChannel2.ClockLengthCounter();
        triangleChannel.ClockLengthCounter();
        noiseChannel.ClockLengthCounter();

        squareChannel1.ClockSweep();
        squareChannel2.ClockSweep();
    }

    triangleChannel.Clock();

    // Square channels are actually clocked every APU cycle but their timers are reloaded with (seq_reload + 1) << 1
    squareChannel1.Clock();
    squareChannel2.Clock();
    noiseChannel.Clock();

    if ((frameClockCounter & 0x01) == 1)
    {
    }

    if (fireInterrupt)
        irq = true;

    frameClockCounter = reset ? 0 : frameClockCounter + 1;
}

//#define USE_LINEAR_APPROX

double APU::getOutput()
{
#ifdef USE_LINEAR_APPROX
    double pulse_out = 0.00752 * (squareChannel1.GetOutput() + squareChannel2.GetOutput());
    double tnd_out = 0.00851 * triangleChannel.GetOutput() + 0.00494 * noiseChannel.GetOutput();
    double output = pulse_out + tnd_out;

    return output;
#else
    return pulseLookupTable[squareChannel1.GetOutput() + squareChannel2.GetOutput()] + tndLookupTable[3 * triangleChannel.GetOutput() + 2 * noiseChannel.GetOutput() + sampleChannel.GetOutput()];
#endif
}

void APU::reset()
{
    squareChannel1.Reset();
    squareChannel2.Reset();
    triangleChannel.Reset();
    noiseChannel.Reset();
    sampleChannel.Reset();
    irq = false;

    writeRegisters(0x15, 0);
    writeRegisters(0x17, 0);
}

double APU::getDebugOutput(uint8_t channel)
{
    switch (channel)
    {
        case 0:
            return ((double) squareChannel1.GetOutput()) / 15.0;
            break;
        case 1:
            return ((double) squareChannel2.GetOutput()) / 15.0;
            break;
        case 2:
            return triangleChannel.active() ? ((double)triangleChannel.GetOutput()) / 15.0 : 0;
            break;
        case 3:
            return ((double) noiseChannel.GetOutput()) / 15.0;
            break;
        default:
            return 0;
            break;
    }
}